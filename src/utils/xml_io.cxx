// ----------------------------------------------------------------------------
// Copyright (C) 2014
//              David Freese, W1HKJ
//
// This file is part of flmsg
//
// flrig is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// flrig is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include <stdio.h>

#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

#include "flmsg.h"
#include "flmsg_dialog.h"
#include "xml_io.h"
#include "XmlRpc.h"
#include "status.h"
#include "debug.h"
#include "threads.h"

#include "base64.h"

#include <fstream>
#include "flmsg_dialog.h"
#include "flmsg_arq.h"
#include "status.h"

//bool FILEIO = false;

using namespace std;
using XmlRpc::XmlRpcValue;

static bool exit_xmlrpc_flag = false;

static const double TIMEOUT = 1.0;

static const char* modem_get_name       = "modem.get_name";
static const char* modem_get_names      = "modem.get_names";
static const char* io_in_use            = "io.in_use";
static const char* io_enable_arq        = "io.enable_arq";

static const char* rx_get_data          = "rx.get_data";
static const char* tx_send_data         = "text.add_tx_queu";
static const char* tx_ON                = "main.tx";
static const char* trx_state            = "main.get_trx_state";

static const char* main_fldigi_online   = "main.flmsg_online";
static const char* main_flmsg_available = "main.flmsg_available";
static const char* main_flmsg_transfer  = "main.flmsg_transfer";
static const char* main_fldigi_squelch  = "main.flmsg_squelch";

static const char* main_get_txid        = "main.get_txid";
static const char* main_set_txid        = "main.set_txid";  // 0 or 1
//static const char* main_toggle_txid     = "main.toggle_txid";

static const char* main_get_rsid        = "main.get_rsid";
static const char* main_set_rsid        = "main.set_rsid"; // 0 or 1
//static const char* main_toggle_rsid     =  "main.toggle_rsid";

static const char* modem_set_by_name    = "modem.set_by_name";

static XmlRpc::XmlRpcClient* client;

string xml_rxbuffer;

#define XMLRPC_UPDATE_INTERVAL  100

//=====================================================================
// socket ops
//=====================================================================
static bool fldigi_online = false;

static int update_interval = XMLRPC_UPDATE_INTERVAL;

static string xmlcall = "";

void open_xmlrpc()
{
	int server_port = atoi(progStatus.xmlrpc_port.c_str());
	client = new XmlRpc::XmlRpcClient(progStatus.xmlrpc_addr.c_str(),
			server_port );
	XmlRpc::setVerbosity(0); // 0...5
}

void close_xmlrpc()
{
	pthread_mutex_lock(&mutex_xmlrpc);
	delete client;
	client = NULL;

	exit_xmlrpc_flag = true;

	pthread_mutex_unlock(&mutex_xmlrpc);
	pthread_join(*xmlrpc_thread, 0);
}


static inline void execute(const char* name, const XmlRpcValue& param, XmlRpcValue& result)
{
	if (client)
		if (!client->execute(name, param, result, TIMEOUT)) {
			throw XmlRpc::XmlRpcException(name);
			fldigi_online = false;
		}
}

void xfr_via_xmlrpc(string s)
{
	guard_lock xfr_lock(&mutex_xmlrpc);
	XmlRpcValue res;
	XmlRpcValue query;
	XmlRpcValue str = s.append("^r");
	try {
		execute(tx_send_data, str, res);
		execute(tx_ON, query, res);
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
	}
}

void set_fldigi_txid(bool on_off)
{
	guard_lock xfr_lock(&mutex_xmlrpc);
	XmlRpcValue res;
	XmlRpcValue val = on_off;
	try {
		execute(main_set_txid, val, res);
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
	}
}

void set_fldigi_rxid(bool on_off)
{
	guard_lock xfr_lock(&mutex_xmlrpc);
	XmlRpcValue res;
	XmlRpcValue val = on_off;
	try {
		execute(main_set_rsid, val, res);
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
	}
}

int txid_at_start = -1;
int rsid_at_start = -1;

void get_fldigi_txid()
{
	guard_lock xfr_lock(&mutex_xmlrpc);
	XmlRpcValue res;
	XmlRpcValue val;
	try {
		execute(main_get_txid, val, res);
		txid_at_start = res;
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
	}
}

void get_fldigi_rxid()
{
	guard_lock xfr_lock(&mutex_xmlrpc);
	XmlRpcValue res;
	XmlRpcValue val;
	try {
		execute(main_get_rsid, val, res);
		rsid_at_start = res;
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
	}
}

void restore_id()
{
	if (rsid_at_start != -1) {
		set_fldigi_rxid(rsid_at_start);
	}
	if (txid_at_start != -1) {
		set_fldigi_txid(txid_at_start);
	}
}

// --------------------------------------------------------------------
// send functions
// --------------------------------------------------------------------
extern void arqlog(string nom, string s);

void send_new_modem()
{
	pthread_mutex_lock(&mutex_xmlrpc);
	try {
		XmlRpcValue mode(cbo_modes->value()), res;
		execute(modem_set_by_name, mode, res);
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
	}
	pthread_mutex_unlock(&mutex_xmlrpc);
}

void enable_arq(void)
{
	pthread_mutex_lock(&mutex_xmlrpc);
	try {
		XmlRpcValue res;
		execute(io_enable_arq, 0, res);
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
	}
	pthread_mutex_unlock(&mutex_xmlrpc);
}

static void flmsg_online(void)
{
	try {
		XmlRpcValue res;
		execute(main_fldigi_online, 0, res);
	} catch (const XmlRpc::XmlRpcException& e) {
		throw;
	}
}

// --------------------------------------------------------------------
// receive functions
// --------------------------------------------------------------------

std::string get_io_mode(void)
{
	if (!fldigi_online || !client) return "";

	XmlRpcValue status;
	XmlRpcValue query;
	static string response;

	pthread_mutex_lock(&mutex_xmlrpc);
	try {
		execute(io_in_use, query, status);
		string resp = status;
		response = resp;
	} catch (const XmlRpc::XmlRpcException& e) {
	}
	pthread_mutex_unlock(&mutex_xmlrpc);

	return response;
}

static void set_combo(void *str)
{
	if (!progStatus.sync_modem_to_fldigi) return;
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
	} catch (const XmlRpc::XmlRpcException& e) {
		throw;
	}
}

std::string xml_get_rx_chars()
{
	XmlRpcValue rxdata;
	XmlRpcValue query;
	static string buffer;
	buffer.clear();
	try {
		guard_lock rx(&mutex_xmlrpc);
		execute(rx_get_data, query, rxdata);
		const XmlRpcValue::BinaryData &data = rxdata;
		int n = int(data.size());
		if (n) {
			for (int i = 0; i < n; i++) buffer += data[i];
		}
		return buffer;
	} catch (const XmlRpc::XmlRpcException& e) {
		return "";
	}
	return buffer;
}

void xml_send_tx_chars(std::string s)
{
	if (s.empty()) return;

	string sendstr = "\n";
	sendstr.append(s);
	sendstr.append("\n^r");
	guard_lock xmllock(&mutex_xmlrpc);

	XmlRpcValue res;
	XmlRpcValue query;
	XmlRpcValue str = sendstr;
	try {
		execute(tx_send_data, str, res);
		execute(tx_ON, query, res);
	} catch (const XmlRpc::XmlRpcException& e) {
	}
}

bool fldigi_OK_to_transmit()
{
	guard_lock xmllock(&mutex_xmlrpc);
	XmlRpcValue res;
	XmlRpcValue query;
	try {
		execute(trx_state, query, res);
		string on = res;
		bool isRX = (on == "RX");

		execute(main_fldigi_squelch, query, res);
		bool is_open = res;

		return (isRX && !is_open);
	} catch (const XmlRpc::XmlRpcException& e) {
	}
	return false;
}

// main.get_trx_state returns one of
// "TX", "RX"
//
string xml_fldigi_trx()
{
	if (!fldigi_online || !client) return "RX";

	guard_lock xmllock(&mutex_xmlrpc);

	XmlRpcValue resp;
	XmlRpcValue query;
	try {
		execute(trx_state, query, resp);
		string on = resp;
		return on;
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
		return "RX";
	}
	return "";
}

static void get_fldigi_modems()
{
	XmlRpcValue status, query;
	try {
		string flmsg_modes("");
		execute(modem_get_names, query, status);
		for (int i = 0; i < status.size(); i++) {
			flmsg_modes.append((std::string)status[i]).append("|");
		}
		update_cbo_modes(flmsg_modes);
		fldigi_online = true;
	} catch (...) {
		LOG_ERROR("%s", xmlcall.c_str());
		throw;
	}
}

string auto_msg;

void process_autosend(void *)
{
	direct_payload(auto_msg);
	auto_msg.clear();
}

static void check_for_autosend()
{
	XmlRpcValue resp;
	XmlRpcValue query;
	try {
		execute(main_flmsg_available, query, resp);
		int ready = resp;
		if (ready) {
			execute(main_flmsg_transfer, query, resp);
			string temp = resp;
			auto_msg = temp;
			Fl::awake(process_autosend);
		}
	} catch (const XmlRpc::XmlRpcException& e) {
		LOG_ERROR("%s", e.getMessage().c_str());
	}
}

void * xmlrpc_loop(void *d)
{
	fldigi_online = false;

	exit_xmlrpc_flag = false;

	while(!exit_xmlrpc_flag) {
		MilliSleep(update_interval);
		try {
			guard_lock lock(&mutex_xmlrpc);
			if (client) {
				{
					flmsg_online();
					if (!fldigi_online) {
						get_fldigi_modems();
					} else {
						get_fldigi_modem();
						check_for_autosend();
					}
				}
			}
		} catch (const XmlRpc::XmlRpcException& e) {
			LOG_ERROR("%s", e.getMessage().c_str());
			fldigi_online = false;
		}
	}
	return NULL;
}

