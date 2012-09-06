//======================================================================
// flmsg xml_io.cxx
//
// copyright 2012, W1HKJ
//
// xmlrpc interface to fldigi
//
// fetches current list of modem types from fldigi
// fetches current modem in use in fldigi
// sets fldigi modem-by-name when required
//
//======================================================================

#include <stdio.h>

#include <cstdlib>
#include <string>
#include <vector>
#include <queue>

#include "flmsg.h"
#include "flmsg_dialog.h"
#include "xml_io.h"
#include "XmlRpc.h"
#include "status.h"
#include "debug.h"
#include "threads.h"

using namespace std;
using XmlRpc::XmlRpcValue;

static const double TIMEOUT = 1.0;

// these are get only
static const char* modem_get_name       = "modem.get_name";
static const char* modem_get_names      = "modem.get_names";

// these are set only
static const char* modem_set_by_name    = "modem.set_by_name";

static XmlRpc::XmlRpcClient* client;

#define XMLRPC_UPDATE_INTERVAL  200
#define XMLRPC_UPDATE_AFTER_WRITE 1000

//=====================================================================
// socket ops
//=====================================================================
int update_interval = XMLRPC_UPDATE_INTERVAL;

string xmlcall = "";

void open_xmlrpc()
{
	int server_port = atoi(progStatus.xmlrpc_port.c_str());
	client = new XmlRpc::XmlRpcClient(
				progStatus.xmlrpc_addr.c_str(),
				server_port );
//	XmlRpc::setVerbosity(5); // 0...5
}

void close_xmlrpc()
{
	pthread_mutex_lock(&mutex_xmlrpc);

	delete client;
	client = NULL;

	pthread_mutex_unlock(&mutex_xmlrpc);
}

static inline void execute(const char* name, const XmlRpcValue& param, XmlRpcValue& result)
{
	if (client)
		if (!client->execute(name, param, result, TIMEOUT))
			throw XmlRpc::XmlRpcException(name);
}

// --------------------------------------------------------------------
// send functions
// --------------------------------------------------------------------

void send_new_modem()
{
	pthread_mutex_lock(&mutex_xmlrpc);
	try {
		XmlRpcValue mode(cbo_modes->value()), res;
		execute(modem_set_by_name, mode, res);
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
	}
	update_interval = XMLRPC_UPDATE_AFTER_WRITE;
	pthread_mutex_unlock(&mutex_xmlrpc);
}

// --------------------------------------------------------------------
// receive functions
// --------------------------------------------------------------------

static void set_combo(void *str)
{
 	string s = (char *)str;
 	if (s != cbo_modes->value() && valid_mode_check(s)) {
 		cbo_modes->value(s.c_str());
 		estimate();
 	}
}

static void get_fldigi_modem()
{
	XmlRpcValue status;
	XmlRpcValue query;
	static string response;
	try {
		execute(modem_get_name, query, status);
		string resp = status;
		response = resp;
		if (!response.empty()) {
			Fl::awake(set_combo, (void *)response.c_str());
		}
	} catch (...) {
//		LOG_ERROR("%s", modem_get_name);
		throw;
	}
}

bool fldigi_online = false;

static void get_fldigi_modems()
{
	XmlRpcValue status, query;
	try {
		execute(modem_get_names, query, status);
		fldigi_online = true;
	} catch (...) {
//		LOG_ERROR("%s", xmlcall.c_str());
		throw;
	}
}

void * xmlrpc_loop(void *d)
{
	fldigi_online = false;
	for (;;) {
		pthread_mutex_lock(&mutex_xmlrpc);
		try {
			if (fldigi_online)
				get_fldigi_modem();
			else
				get_fldigi_modems();
		} catch (const XmlRpc::XmlRpcException& e) {
//			LOG_ERROR("%s", e.getMessage().c_str());
			fldigi_online = false;
		}
		pthread_mutex_unlock(&mutex_xmlrpc);
		MilliSleep(update_interval);
		if (update_interval != XMLRPC_UPDATE_INTERVAL)
			update_interval = XMLRPC_UPDATE_INTERVAL;
	}
	return NULL;
}
