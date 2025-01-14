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

#ifndef _status_H
#define _status_H

#include <string>

using namespace std;

struct status {
	int		mainX;
	int		mainY;
	int		expertW;
	int		expertH;

	int		wpl; // words per line in radiogram
	bool	open_on_export;
	int		UTC;
	int		dtformat;

	void saveLastState();
	void loadLastState();
	string my_call;
	string my_tel;
	string my_name;
	string my_addr;
	string my_city;
	string my_email;
	bool sernbr_fname;
	bool call_fname;
	int  dt_fname;
	bool rgnbr_fname;
	bool arl_desc;
	string sernbr;
	string rgnbr;
	bool rri;
	bool insert_x;
	int tab;
	string mars_roster_file;
	int charcount;
	bool autowordwrap;
	bool send_original;
	string xmlrpc_addr;
	string xmlrpc_port;

	bool use_compression;
	int  selected_mode;
	int  swx_index_default_state;
	int  swx_index_default_county;
	string swx_default_city;
	string swx_default_location;
	string swx_default_zone;
	string swx_default_profile;
	bool  change_modem_with_autosend;
	bool  sync_modem_to_fldigi;
	bool  caplocal;
	bool  auto_open_url;
	int   retries;
	int   timeout;
	int   exponent;
	bool  ID_on;
	bool  ID_off;
	bool  ID_restore;
	bool  arq_shown;

	bool  UI_expert;
	bool  UI_default;

	int   arq_notify_timeout;
	bool  notify_receipt;
};

extern status progStatus;

#endif
