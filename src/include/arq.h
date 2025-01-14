#ifndef arq_H
#define arq_H

// ----------------------------------------------------------------------------
// arq module arq.h
// Copyright (c) 2007-2009, Dave Freese, W1HKJ
//
//
// This file is part of flmsg.
//
// Fldigi is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Fldigi is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with flmsg.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <cctype>

#include "threads.h"
#include "util.h"
#include "debug.h"
#include "crc16.h"

#include <FL/Fl.H>

using namespace std;

#define arq_Version "arq 0.2"

extern const char *ASCII[];
extern string noCR(string s);
extern string noCTL(string s);

// link layer spec for flmsg_arq
//
// generic Frame format:
// \x01bMYCALL~URCALL~[info])12EF\x04
//   | |  |      |       |    |   |
//   | |  |      |       |    |   +--ASCII <ARQ_EOF> (0x04) character
//   | |  |      |       |    +------checksum (4xAlphaNum)
//   | |  |      |       +-----------Payload
//   | |  |      +-------------------Your callsign
//   | |  +--------------------------My callsign
//   | +-----------------------------Block type
//   +-------------------------------ASCII <ARQ_SOF> (0x01) character
// callsigns max of 12 characters each
// payload size, 16, 32, 64, 128, or 256 characters
// frame overhead = 7

class arq {
public:
//=====================================================================
// Block Types
#define CONREQ		'c' // Connection request
#define CONACK		'C' // Connection acknowledge
#define DISREQ		'd' // Disconnect request
#define DISACK		'D' // Disconnect acknowledge
#define POLL		'p' // Poll for status
#define ACK			'A' // Frame OK
#define NAK			'N' // Frame BAD
#define DATA		'B' // Data block
//=====================================================================
#define ESC_CHR		'~'
#define ARQ_SOF		"~1" // ESC_CHR 1
#define ARQ_EOF		"~4" // ESC_CHR 4
#define ARQ_DLE		";" // '~'  ARQ_DLE must be a single character
//=====================================================================
//ARQ defaults
#define EXPONENT	7	// buffer_length = 2 ^ EXPONENT = 128
//=====================================================================
//link timing defaults
#define	RETRIES		2
#define ARQLOOPTIME	100		// # msec for loop timing
//=====================================================================
//link states

enum LINK_STATES {
	ARQ_DOWN = 0,
	ARQ_CONNECTING,
	ARQ_CONNECTED,
	ARQ_DISCONNECT,
	ARQ_DISCONNECTING
};

//=====================================================================

private:
	bool	arqreset;
	bool	sender;

	string	MyCall;
	string	UrCall;
	string	arqfname;

	int		blknbr;
	size_t	xfrsize;

	string	str_xfrsize;
	string	str_blknbr;

// queues //
	string	TxTextQueue;
	string	RxTextQueue;
	string	RxFrameQueue;
	string	rcvPayLoad;
	string	xmttext;
	string	xmtsent;
	string	payload;
	string	nomFrame;

	int		buffer_length;
	int		last_buffer_length;
	int		maxheaders;
	int		exponent;
	int		lastblock;

// status variables

	int		retrytime;  // time to wait before resending a Frame
	int		retries;    // number of times to retry sending Frame
	int		timeout;    // absolute time before declaring ARQ connection broken
	int		loopcount;
	int		Retries;

	Ccrc16	framecrc;

	int		LinkState;					// status of ARQ link

	bool	arq_exit;
	bool	arq_running;

// Link quality for sending *** used for testing only !! ***
//	double	sendquality;

	void	reset();
	void	resetTx();
	void	resetRx();
	int     rtry();

	void	setbuffer_length();

	void	checkblocks();
	string	upcase(string s);

	string	calls();
	void	connectFrame();
	void	conackFrame();
	void	disackFrame();
	void	ackFrame();
	void	nakFrame();
	void	dataFrame();
	void	resendFrame();
	void	pollFrame();
	void	disconnectFrame();

	void	addToTxQue(string s);

	bool	rightCALLS();

	void	parseCONREQ();
	void	parseCONACK();
	void	parseDISREQ();
	void	parseDISACK();
	void	parsePOLL();
	void	parseDATA();
	void	parseACK();
	void	parseNAK();

	void	parseFrame(string txt);

//----------------------------------------------------------------------
// external functions called by arq class must use Fl::wait(fn,...)
// to isolate the UI thread from the arq thread
//----------------------------------------------------------------------

	string	(*do_trx)();
	int trx() {
		if (do_trx) {
			if (do_trx() == "TX") return 1;
			return 0;
		}
		return 0;
	}

	void	(*do_sendfnc)(const string& s);
	void	sendfnc(const string &s) {
		if (do_sendfnc != NULL) do_sendfnc(s);
	}

	bool	(*do_getc1)(char &);
	bool	getc1(char &c) {
		if (do_getc1 != NULL) return do_getc1(c);
		c = ' ';
		return false;
	}

	void	(*do_rcvfnc)();
	void	rcvfnc() {
		if (do_rcvfnc != NULL) do_rcvfnc();
	}

	void	(*do_printRX)(string s);
	void	printRX(string s) {
		if (do_printRX != NULL) do_printRX(s);
	}

	void	(*do_printTX)(string s);
	void	printTX(string s) {
		if (do_printTX != NULL) do_printTX(s);
	}

	void	(*do_printLOG)(string s1, string s2);
	void	printLOG(string s1, string s2) {
		if (do_printLOG) do_printLOG(s1, s2);
	}

	void	(*do_printTALK)(string s);
	void	printTALK(string s) {
		if (do_printTALK != NULL) do_printTALK(s);
	}

	void	(*do_abortfnc)();
	void	abortfnc() {
		if (do_abortfnc != NULL) do_abortfnc();
	}

	void	(*do_disconnectfnc)();
	void	disconnectfnc() {
		if (do_disconnectfnc != NULL) do_disconnectfnc();
	}

	void	(*do_rxUrCall)(string s);
	void	rxUrCall(string s) {
		if (do_rxUrCall != NULL) do_rxUrCall(s);
	}

	void	(*do_qualityfnc)(float pcnt);
	void	qualityfnc(float pcnt) {
		if (do_qualityfnc != NULL) do_qualityfnc(pcnt);
	}

	void	(*do_printSTATUS)(string s);
	void	printSTATUS(string s) {
		if (do_printSTATUS != NULL) do_printSTATUS(s);
	}

	float		(*do_transmit_time)(string s);
	float		transmit_time(string s) {
		if (do_transmit_time) return do_transmit_time(s);
		else return 0;
	}

	bool	(*do_OK_to_transmit)();
	bool	OK_to_transmit() {
		if (do_OK_to_transmit()) return do_OK_to_transmit();
		else return false;
	}

// execution loop functions
	void	rcv_chars();
	void	exec_arqreset();
	void	sendchars();

public:
	arq();
	~arq() { exit_arq(); }

	friend	void	*arqloop(void *);
	friend	void	sked_reset(void *);

	void	start_arq();
	void	reset_arq();
	void	stop_arq();
	void	exit_arq();

	string	checksum(string &s);

	void	myCall(string s) { 
		MyCall = upcase(s);
		for (size_t n = 0; n < MyCall.length(); n++)
			if (MyCall[n] == ';') MyCall[n] = '-';
		}
	string	myCall() { return MyCall;}

	void	urCall(string s) { 
		UrCall = s;
		for (size_t n = 0; n < UrCall.length(); n++)
			if (UrCall[n] == ';') UrCall[n] = '-';
		}

	string	urCall() { return UrCall;}

	void	escape(bool, string &);

	void	setSendFunc( void (*f)(const string& s)) { do_sendfnc = f;}
	void	setGetCFunc( bool (*f)(char &)) { do_getc1 = f;}
	void	setRcvFunc( void (*f)()) { do_rcvfnc = f;}

	void	setPrintRX( void (*f)(string s)) { do_printRX = f;}
	void	setPrintTX( void (*f)(string s)) { do_printTX = f;}
	void	setPrintTALK (void (*f)(string s)) {do_printTALK = f;}
	void	setPrintLOG (void (*f)(string, string)){do_printLOG = f;}
	void	setPrintSTATUS (void (*f)(string s)) { do_printSTATUS = f;}
	void	setTRX(string (*f)()) { do_trx = f;}
	void	setTransmitTime(float (*f)(string s)) { do_transmit_time = f; }
	void	setOK_to_transmit(bool (*f)()) { do_OK_to_transmit = f; }

	void	setExponent( int exp ) { exponent = exp; setbuffer_length(); }
	int		getExponent() { return (int) exponent;}
	void	setRetries ( int rtries ) {
				Retries = rtries; }
	int		getRetries() { return (int) Retries; }
	void	setrxUrCall( void (*f)(string s)) { do_rxUrCall = f;}
	void	setQualityValue( void (*f)(float)) { do_qualityfnc = f;}
	void	setDisconnected( void (*f)()) { do_disconnectfnc = f;};

	void	connect();

	void	sendtext(string call, string txt);

	bool	connected() { return (LinkState == ARQ_CONNECTED); }
	void	disconnect();

	int		state() { return LinkState;}

	double	quality() {
		return 0;
	}

};

#endif

