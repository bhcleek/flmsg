// =====================================================================
//
// flmsg.cxx
//
// Author: Dave Freese, W1HKJ
// Copyright: 2010, 2011
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  It is
// copyright under the GNU General Public License.
//
// You should have received a copy of the GNU General Public License
// along with the program; if not, write to the Free Software
// Foundation, Inc.
// 59 Temple Place, Suite 330
// Boston, MA  02111-1307 USA
//
// =====================================================================

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Sys_Menu_Bar.H>
#include <FL/x.H>
#include <FL/Fl_Help_Dialog.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_File_Icon.H>

#include "config.h"
#include "flmsg_config.h"

#include "flmsg.h"

#include "templates.h"
#include "debug.h"
#include "util.h"
#include "gettext.h"
#include "flmsg_dialog.h"
#include "flinput2.h"
#include "date.h"
#include "calendar.h"
#include "icons.h"
#include "fileselect.h"
#include "wrap.h"
#include "status.h"
#include "pixmaps.h"

#ifdef WIN32
#  include "flmsgrc.h"
#  include "compat.h"
#  define dirent fl_dirent_no_thanks
#endif

#include <FL/filename.H>
#include "dirent-check.h"

#include <FL/x.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Image.H>

using namespace std;

Fl_Double_Window *mainwindow = 0;
Fl_Double_Window *optionswindow = 0;
Fl_Double_Window *arlwindow = 0;
Fl_Double_Window *config_files_window = 0;
Fl_Double_Window *config_datetime_window = 0;
Fl_Double_Window *config_radiogram_window = 0;
Fl_Double_Window *hxwindow = 0;

bool printme = false;
bool exit_after_print = false;
int  selected_form = NONE;

string title;

string errtext;

// fldigi, flmsg share a common files directory structure

#ifdef __WIN32__
	string FLMSG_dir_default = "$USERPROFILE/NBEMS.files/";
#else
	string FLMSG_dir_default = "$HOME/.nbems/";
#endif

string FLMSG_dir = "";
string ARQ_dir = "";
string ARQ_files_dir = "";
string ARQ_recv_dir = "";
string ARQ_send_dir = "";
string WRAP_dir = "";
string WRAP_recv_dir = "";
string WRAP_send_dir = "";
string WRAP_auto_dir = "";
string ICS_dir = "";
string ICS_msg_dir = "";
string ICS_tmp_dir = "";

string cmd_fname = "";

string TITLE = ":TITLE:";

//string defRTFname = "";

// utility functions

// create header for flmsg data file
string header( const char *msgtype )
{
	static string sout;
	sout = "<flmsg>";
	sout.append (PACKAGE_VERSION).append("\n").append(msgtype).append("\n");
	return sout;
}

// create flmsg line output for string data
string lineout(string &field, string &data)
{
	static string sout;
	static char sznum[80];
	if (data.empty()) return "";
	snprintf(sznum, sizeof(sznum), "%0d", data.length());
	sout = field;
	sout.append(sznum).append(" ").append(data).append("\n");
	return sout;
}
// create flmsg line output for binary data
string binout( string &field, bool &data)
{
	static string sout;
	if (!data) return "";
	sout = field;
	sout.append(" ").append( data ? "T" : "F").append("\n");
	return sout;
}

// find string data associated with a field specifier
string findstr(string &haystack, string &needle)
{
	size_t p = haystack.find(needle, 0);
	if (p == string::npos) return "";
	p += needle.length();
	int nchar;
	sscanf(&haystack[p], "%d", &nchar);
	if (nchar) {
		p = haystack.find(' ', p);
		p++;
		return haystack.substr(p, nchar);
	}
	return "";
}

// find boolean data associated with a field specifier
bool findbin(string &haystack, string &needle)
{
	size_t p = haystack.find(needle, 0);
	if (p == string::npos) return false;
	p += needle.length() + 1;
	if (haystack.find("F", p) == p) return false;
	if (haystack.find("T", p) == p) return true;
	return false;
}

// replace string
void replacestr(string &form, string &where, string &what)
{
	size_t p = form.find(where);
	if (p != string::npos)
		form.replace(p, where.length(), what);
}

void replacelf(string &form, int n)
{
	size_t p = 0;
	int i = 0;
	while ( (p = form.find("\n", p)) != string::npos) {
		form.insert(p, "<br>");
		p += 5;
		i++;
	}
	if (n)
		for (int j = i; j < n; j++)
			form.append("<br>\n");
}

void substitutestr(string &form, string &where, string &what)
{
	size_t p = 0;
	p = form.find(where, p);
	while (p != string::npos) {
		form.replace(p, where.length(), what);
		p++;
		p = form.find(where, p);
	}
}

void strip_html(string &buffer)
{
	string amp = "&";		string amprep = "&#38;";
	string quote = "\"";	string quoterep = "&#34;";
	string less = "<";		string lessrep = "&#60;";
	string more = ">";		string morerep = "&#62;";
	substitutestr(buffer, amp, amprep);
	substitutestr(buffer, quote, quoterep);
	substitutestr(buffer, less, lessrep);
	substitutestr(buffer, more, morerep);
}

void remove_cr(string &buffer)
{
	size_t p = string::npos;
	while ((p = buffer.find('\r')) != string::npos) buffer.erase(p,1);
}

//----------------------------------------------------------------------
void remove_spaces_from_filename(string &fname)
{
	size_t n = fname.length();
	char szfname[n + 1];
	char *p;
	memset(szfname, 0, n + 1);
	strcpy(szfname, fname.c_str());
	p = (char *)fl_filename_name(szfname);
	while (*p) {
		if (*p == ' ') *p = '_';
		p++;
	}
	fname = szfname;
}

char *szTime(int typ)
{
	static char szDt[80];
	time_t tmptr;
	tm sTime;
	time (&tmptr);
	switch (typ) {
		case 0:
			localtime_r(&tmptr, &sTime);
			strftime(szDt, 79, "%H%ML", &sTime);
			break;
		case 1:
			localtime_r(&tmptr, &sTime);
			strftime(szDt, 79, "%H:%ML", &sTime);
			break;
		case 2:
			gmtime_r (&tmptr, &sTime);
			strftime(szDt, 79, "%H%MZ", &sTime);
			break;
		case 3:
			gmtime_r (&tmptr, &sTime);
			strftime(szDt, 79, "%H:%MZ", &sTime);
			break;
		case 4:
			gmtime_r (&tmptr, &sTime);
			strftime(szDt, 79, "%H%M UTC", &sTime);
			break;
		case 5:
			gmtime_r (&tmptr, &sTime);
			strftime(szDt, 79, "%H:%M UTC", &sTime);
			break;
		default:
			localtime_r(&tmptr, &sTime);
			strftime(szDt, 79, "%H%ML", &sTime);
	}
	return szDt;
}

char *szDate()
{
	static char szDt[80];
	time_t tmptr;
	tm sTime;
	time (&tmptr);
	if (progStatus.UTC > 1) {
		gmtime_r (&tmptr, &sTime);
	} else {
		localtime_r(&tmptr, &sTime);
	}
	switch (progStatus.dtformat) {
		case 0: strftime(szDt, 79, "%Y-%m-%d", &sTime); break;
		case 1: strftime(szDt, 79, "%m/%d/%y", &sTime); break;
		case 2: strftime(szDt, 79, "%d/%m/%y", &sTime); break;
		case 3: strftime(szDt, 79, "%Y-%d-%m", &sTime); break;
		default: strftime(szDt, 79, "%Y-%m-%d", &sTime);
	}
	return szDt;
}

char *szAbbrevDate()
{
	static char szDt[80];
	time_t tmptr;
	tm sTime;
	time (&tmptr);
	if (progStatus.UTC) {
		gmtime_r (&tmptr, &sTime);
	} else {
		localtime_r(&tmptr, &sTime);
	}
	strftime(szDt, 79, "%b %d", &sTime);
	for (int i = 0; i < 3; i++) szDt[i] = toupper(szDt[i]);
	return szDt;
}

char *szDateTime()
{
	static char szDt[80];
	time_t tmptr;
	tm sTime;
	time (&tmptr);
	if (progStatus.UTC) {
		gmtime_r (&tmptr, &sTime);
		strftime(szDt, 79, "%d%H%MZ %b %Y", &sTime);
	} else {
		localtime_r(&tmptr, &sTime);
		strftime(szDt, 79, "%d%H%ML %b %Y", &sTime);
	}
	for (size_t i = 0; i < strlen(szDt); i++) szDt[i] = toupper(szDt[i]);
	return szDt;
}

char *szMarsDateTime()
{
	static char szDt[80];
	time_t tmptr;
	tm sTime;
	time (&tmptr);
	gmtime_r (&tmptr, &sTime);
	strftime(szDt, 79, "%d%H%MZ %b %Y", &sTime);
	for (size_t i = 0; i < strlen(szDt); i++) szDt[i] = toupper(szDt[i]);
	return szDt;
}

char *named_file()
{
	static char szfname[200];
	static char szDt[80];
	szfname[0] = 0;
	if (!progStatus.call_fname && !progStatus.dt_fname && !progStatus.sernbr_fname)
		return szfname;
	time_t tmptr;
	tm sTime;
	time (&tmptr);
	gmtime_r (&tmptr, &sTime);
	strftime(szDt, 79, "%Y%m%d-%H%M%SZ", &sTime);
	szfname[0] = 0;
	if (progStatus.call_fname) strcat(szfname, progStatus.my_call.c_str());
	if (selected_form == RADIOGRAM  && progStatus.rgnbr_fname) {
		if (szfname[0]) strcat(szfname, "-");
		strcat(szfname, progStatus.rgnbr.c_str());
	} else {
		if (progStatus.dt_fname) {
			if (szfname[0]) strcat(szfname, "-");
			strcat(szfname, szDt);
		}
		if (progStatus.sernbr_fname) {
			if (szfname[0]) strcat(szfname, "-");
			strcat(szfname, progStatus.sernbr.c_str());
		}
	}
	return szfname;
}

void extract_text(string &buffer, const char *fname)
{
	remove_cr(buffer);
	if (buffer.find("<radiogram>") != string::npos) {
		selected_form = RADIOGRAM;
		read_rg_buffer(buffer);
		if (fname) def_rg_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<iaru>") != string::npos) {
		selected_form = IARU;
		iaru_read_buffer(buffer);
		if (fname) iaru_def_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<mars_daily>") != string::npos) {
		selected_form = MARSDAILY;
		read_mars_daily_buffer(buffer);
		if (fname) def_mars_daily_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<mars_ineei>") != string::npos) {
		selected_form = MARSINEEI;
		read_mars_ineei_buffer(buffer);
		if (fname) def_mars_ineei_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<mars_net>") != string::npos) {
		selected_form = MARSNET;
		read_mars_net_buffer(buffer);
		if (fname) def_mars_net_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<mars_army>") != string::npos) {
		selected_form = MARSARMY;
		read_mars_army_buffer(buffer);
		if (fname) def_mars_army_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<mars_navy>") != string::npos) {
		selected_form = MARSNAVY;
		read_mars_navy_buffer(buffer);
		if (fname) def_mars_navy_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<redx_snw>") != string::npos) {
		selected_form = REDXSNW;
		read_redx_snw_buffer(buffer);
		if (fname) def_redx_snw_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<redx_5739>") != string::npos) {
		selected_form = REDX5739;
		read_redx_5739_buffer(buffer);
		if (fname) def_redx_5739_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<hics203>") != string::npos) {
		selected_form = HICS203;
		read_hics203_buffer(buffer);
		if (fname) def_hics203_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<hics206>") != string::npos) {
		selected_form = HICS206;
		h206_read_buffer(buffer);
		if (fname) h206_def_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<hics213>") != string::npos) {
		selected_form = HICS213;
		h213_read_buffer(buffer);
		if (fname) h213_def_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<hics214>") != string::npos) {
		selected_form = HICS214;
		hics214_read_buffer(buffer);
		if (fname) hics214_def_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<ics203>") != string::npos) {
		selected_form = ICS203;
		read_203_buffer(buffer);
		if (fname) def_203_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<ics205>") != string::npos) {
		selected_form = ICS205;
		read_205_buffer(buffer);
		if (fname) def_205_filename= fname;
		select_form(selected_form);
	} else if (buffer.find("<ics205a>") != string::npos) {
		selected_form = ICS205A;
		read_205a_buffer(buffer);
		if (fname) def_205a_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<ics206>") != string::npos) {
		selected_form = ICS206;
		read_206_buffer(buffer);
		if (fname) def_206_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<ics213>") != string::npos) {
		selected_form = ICS213;
		read_213_buffer(buffer);
		if (fname) def_213_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<ics214>") != string::npos) {
		selected_form = ICS214;
		read_214_buffer(buffer);
		if (fname) def_214_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<ics216>") != string::npos) {
		selected_form = ICS216;
		read_216_buffer(buffer);
		if (fname) def_216_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<plaintext>") != string::npos) {
		selected_form = PLAINTEXT;
		read_ptbuffer(buffer);
		if (fname) def_pt_filename = fname;
		select_form(selected_form);
	} else if (buffer.find("<blankform>") != string::npos) {
		selected_form = BLANK;
		read_blankbuffer(buffer);
		if (fname) def_blank_filename = fname;
		select_form(selected_form);
	} else if (!exit_after_print)
		fl_alert2(_("Not an flmsg data file"));
}

//
void read_data_file(string s)
{
	long filesize = 0;
	char *buff, *buffend;
	int retval;
	FILE *icsfile;

	icsfile = fopen (s.c_str(), "r");
	if (!icsfile)
		return;
// determine its size for buffer creation
	fseek (icsfile, 0, SEEK_END);
	filesize = ftell (icsfile);
// test file integrity
	if (filesize == 0) {
		fl_alert2(_("Empty file"));
		return;
	}

	buff = new char[filesize + 1];
	memset(buff, 0, filesize + 1);
// read the entire file into the buffer
	fseek (icsfile, 0, SEEK_SET);
	retval = fread (buff, filesize, 1, icsfile);
	fclose (icsfile);
	buffend = buff + filesize;

	string buffer = buff;
	delete [] buff;

	extract_text(buffer, s.c_str());
}

void cb_new()
{
	switch (selected_form) {
		case ICS203: cb_203_new(); break;
		case ICS205: cb_205_new(); break;
		case ICS205A: cb_205a_new(); break;
		case ICS206: cb_206_new(); break;
		case ICS213: cb_213_new(); break;
		case ICS214: cb_214_new(); break;
		case ICS216: cb_216_new(); break;
		case HICS203: cb_hics203_new(); break;
		case HICS206: h206_cb_new(); break;
		case HICS213: h213_cb_new(); break;
		case HICS214: hics214_cb_new(); break;
		case RADIOGRAM: cb_rg_new(); break;
		case IARU: iaru_cb_new(); break;
		case PLAINTEXT: cb_pt_new(); break;
		case BLANK: cb_blank_new(); break;
		case MARSDAILY: cb_mars_daily_new(); break;
		case MARSINEEI: cb_mars_ineei_new(); break;
		case MARSNET: cb_mars_net_new(); break;
		case MARSARMY: cb_mars_army_new(); break;
		case MARSNAVY: cb_mars_navy_new(); break;
		case REDXSNW: cb_redx_snw_new(); break;
		case REDX5739: cb_redx_5739_new(); break;
		default : ;
	}
}

void cb_import()
{
	switch (selected_form) {
		case ICS203: cb_203_import(); break;
		case ICS205: cb_205_import(); break;
		case ICS205A: cb_205a_import(); break;
		case ICS206: cb_206_import(); break;
		case ICS213: cb_213_import(); break;
		case ICS214: cb_214_import(); break;
		case ICS216: cb_216_import(); break;
		case HICS203: cb_hics203_import(); break;
		case HICS206: h206_cb_import(); break;
		case HICS213: h213_cb_import(); break;
		case HICS214: hics214_cb_import(); break;
		case RADIOGRAM: cb_rg_import(); break;
		case IARU: iaru_cb_import(); break;
		case PLAINTEXT:
		case BLANK:
		case REDXSNW:
		case REDX5739:
		case MARSDAILY:
		case MARSINEEI:
		case MARSNET:
		case MARSARMY:
		case MARSNAVY:
		default:
			fl_alert2("Not implemented");
	}
}

void cb_export()
{
	switch (selected_form) {
		case ICS203: cb_203_export(); break;
		case ICS205: cb_205_export(); break;
		case ICS205A: cb_205a_export(); break;
		case ICS206: cb_206_export(); break;
		case ICS213: cb_213_export(); break;
		case ICS214: cb_214_export(); break;
		case ICS216: cb_216_export(); break;
		case HICS203: cb_hics203_export(); break;
		case HICS206: h206_cb_export(); break;
		case HICS213: h213_cb_export(); break;
		case HICS214: hics214_cb_export(); break;
		case RADIOGRAM: cb_rg_export(); break;
		case IARU: iaru_cb_export(); break;
		case PLAINTEXT:
		case BLANK:
		case REDXSNW:
		case REDX5739:
		case MARSDAILY:
		case MARSINEEI:
		case MARSNET:
		case MARSARMY:
		case MARSNAVY:
		default:
			fl_alert2("Not implemented");
	}
}

void wrap_import(const char *fname)
{
	string filename;
	string inpbuffer;

	bool isok = import_wrapfile(fname, filename, inpbuffer);

	if (!isok && !exit_after_print) {
		isok = !fl_choice2(_("Checksum failed\n\nIgnore errors?"), "yes", "no", NULL);
	}

	if (isok) {

		remove_cr( inpbuffer );
		if (inpbuffer.find("<flics") != string::npos ||
			inpbuffer.find("<flmsg") != string::npos) {
			if (inpbuffer.find("<ics203>") != string::npos) {
				selected_form = ICS203;
				cb_203_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<hics203>") != string::npos) {
				selected_form = HICS203;
				cb_hics203_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<hics206>") != string::npos) {
				selected_form = HICS206;
				h206_cb_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<hics213>") != string::npos) {
				selected_form = HICS213;
				h213_cb_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<hics214>") != string::npos) {
				selected_form = HICS214;
				hics214_cb_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<ics205>") != string::npos) {
				selected_form = ICS205;
				cb_205_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<ics205a>") != string::npos) {
				selected_form = ICS205A;
				cb_205a_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<ics206>") != string::npos) {
				selected_form = ICS206;
				cb_206_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<ics213>") != string::npos) {
				selected_form = ICS213;
				cb_213_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<ics214>") != string::npos) {
				selected_form = ICS214;
				cb_214_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<ics216>") != string::npos) {
				selected_form = ICS216;
				cb_216_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<radiogram>") != string::npos) {
				selected_form = RADIOGRAM;
				cb_rg_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<iaru>") != string::npos) {
				selected_form = IARU;
				iaru_cb_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<plaintext>") != string::npos) {
				selected_form = PLAINTEXT;
				cb_pt_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<blankform>") != string::npos) {
				selected_form = BLANK;
				cb_blank_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<mars_daily>") != string::npos) {
				selected_form = MARSDAILY;
				cb_mars_daily_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<mars_ineei>") != string::npos) {
				selected_form = MARSINEEI;
				cb_mars_ineei_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<mars_net>") != string::npos) {
				selected_form = MARSNET;
				cb_mars_net_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<mars_army>") != string::npos) {
				selected_form = MARSARMY;
				cb_mars_army_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<mars_navy>") != string::npos) {
				selected_form = MARSNAVY;
				cb_mars_navy_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<redx_snw>") != string::npos) {
				selected_form = REDXSNW;
				cb_redx_snw_wrap_import(filename, inpbuffer);
			} else if (inpbuffer.find("<redx_5739>") != string::npos) {
				selected_form = REDX5739;
				cb_redx_5739_wrap_import(filename, inpbuffer);
			} else if (!exit_after_print) {
				selected_form = NONE;
				if (!fl_choice2(_("Cannot identify file type\n\nOpen as text file?"), "yes", "no", NULL)) {
					filename = fname;
					filename.append(".txt");
					FILE *badfile = fopen(filename.c_str(), "w");
					fwrite(inpbuffer.c_str(), inpbuffer.length(), 1, badfile);
					fclose(badfile);
					open_url(filename.c_str());
				}
			}
		}
		select_form(selected_form);
		return;
	}

	if (printme) {
		string badform = baddata_html_template;
		string mgstr = "<txt:";

		string badfile_name = ICS_dir;
		badfile_name.append("err.");
		badfile_name.append(fl_filename_name(fname));
		badfile_name.append(".html");

		string badbuffer = "Error in file: ";
		badbuffer.append(fname).append("\n\n");
		badbuffer.append(errtext);
		replacelf(badbuffer);

		string title = "Err:";
		title.append(fl_filename_name(fname));
		size_t p = title.rfind('.');
		if (p != string::npos) title.erase(p);

		replacestr(badform, TITLE, title);
		replacestr(badform, mgstr, badbuffer);

		FILE *badfile = fopen(badfile_name.c_str(), "w");
		fprintf(badfile,"%s", badform.c_str());
		fclose(badfile);
		open_url(badfile_name.c_str());
		if (exit_after_print)
			return;
	}

	if (!fl_choice2(_("Open as text file?"), "yes", "no", NULL)) {
		filename = fname;
		filename.append(".txt");
		FILE *badfile = fopen(filename.c_str(), "w");
		fwrite(inpbuffer.c_str(), inpbuffer.length(), 1, badfile);
		fclose(badfile);
		open_url(filename.c_str());
	}
 
}

void cb_wrap_import()
{
	string wrapfilename = WRAP_recv_dir;
	wrapfilename.append("default"WRAP_EXT);
	const char *p = FSEL::select(
		"Import wrapped flmsg file",
		"Wrap file\t*.{wrap,WRAP}",
		wrapfilename.c_str());
	if (p)
		wrap_import(p);
}

void cb_wrap_export()
{
	switch (selected_form) {
		case ICS203: cb_203_wrap_export(); break;
		case ICS205: cb_205_wrap_export(); break;
		case ICS205A: cb_205a_wrap_export(); break;
		case ICS206: cb_206_wrap_export(); break;
		case ICS213: cb_213_wrap_export(); break;
		case ICS214: cb_214_wrap_export(); break;
		case ICS216: cb_216_wrap_export(); break;
		case HICS203: cb_hics203_wrap_export(); break;
		case HICS206: h206_cb_wrap_export(); break;
		case HICS213: h213_cb_wrap_export(); break;
		case HICS214: hics214_cb_wrap_export(); break;
		case RADIOGRAM: cb_rg_wrap_export(); break;
		case IARU: iaru_cb_wrap_export(); break;
		case PLAINTEXT: cb_pt_wrap_export(); break;
		case BLANK: cb_blank_wrap_export(); break;
		case MARSDAILY: cb_mars_daily_wrap_export(); break;
		case MARSINEEI: cb_mars_ineei_wrap_export(); break;
		case MARSNET: cb_mars_net_wrap_export(); break;
		case MARSARMY: cb_mars_army_wrap_export(); break;
		case MARSNAVY: cb_mars_navy_wrap_export(); break;
		case REDXSNW: cb_redx_snw_wrap_export(); break;
		case REDX5739: cb_redx_5739_wrap_export(); break;
		default: return;
	}

	if (!progStatus.open_on_export)
		return;

	string location = wrap_outfilename;
	size_t p = location.rfind('/');
	if (p != string::npos)
		location.erase(p+1);
	open_url(location.c_str());
}

void cb_wrap_autosend()
{
	switch (selected_form) {
		case ICS203: cb_203_wrap_autosend(); break;
		case ICS205: cb_205_wrap_autosend(); break;
		case ICS205A: cb_205a_wrap_autosend(); break;
		case ICS206: cb_206_wrap_autosend(); break;
		case ICS213: cb_213_wrap_autosend(); break;
		case ICS214: cb_214_wrap_autosend(); break;
		case ICS216: cb_216_wrap_autosend(); break;
		case HICS203: cb_hics203_wrap_autosend(); break;
		case HICS206: h206_cb_wrap_autosend(); break;
		case HICS213: h213_cb_wrap_autosend(); break;
		case HICS214: hics214_cb_wrap_autosend(); break;
		case RADIOGRAM: cb_rg_wrap_autosend(); break;
		case IARU: iaru_cb_wrap_autosend(); break;
		case PLAINTEXT: cb_pt_wrap_autosend(); break;
		case BLANK: cb_blank_wrap_autosend(); break;
		case MARSDAILY: cb_mars_daily_wrap_autosend(); break;
		case MARSINEEI: cb_mars_ineei_wrap_autosend(); break;
		case MARSNET: cb_mars_net_wrap_autosend(); break;
		case MARSARMY: cb_mars_army_wrap_autosend(); break;
		case MARSNAVY: cb_mars_navy_wrap_autosend(); break;
		case REDXSNW: cb_redx_snw_wrap_autosend(); break;
		case REDX5739: cb_redx_5739_wrap_autosend(); break;
		default: ;
	}
}

void cb_load_template()
{
	switch (selected_form) {
		case ICS203: cb_203_load_template(); break;
		case ICS205: cb_205_load_template(); break;
		case ICS205A: cb_205a_load_template(); break;
		case ICS206: cb_206_load_template(); break;
		case ICS213: cb_213_load_template(); break;
		case ICS214: cb_214_load_template(); break;
		case ICS216: cb_216_load_template(); break;
		case HICS203: cb_hics203_load_template(); break;
		case HICS206: h206_cb_load_template(); break;
		case HICS213: h213_cb_load_template(); break;
		case HICS214: hics214_cb_load_template(); break;
		case RADIOGRAM: cb_rg_load_template(); break;
		case IARU: iaru_cb_load_template(); break;
		case PLAINTEXT: cb_pt_load_template(); break;
		case BLANK: cb_blank_load_template(); break;
		case MARSDAILY: cb_mars_daily_load_template(); break;
		case MARSINEEI: cb_mars_ineei_load_template(); break;
		case MARSNET: cb_mars_net_load_template(); break;
		case MARSARMY: cb_mars_army_load_template(); break;
		case MARSNAVY: cb_mars_navy_load_template(); break;
		case REDXSNW: cb_redx_snw_load_template(); break;
		case REDX5739: cb_redx_5739_load_template(); break;
		default: ;
	}
}

void cb_save_template()
{
	switch (selected_form) {
		case ICS203: cb_203_save_template(); break;
		case ICS205: cb_205_save_template(); break;
		case ICS205A: cb_205a_save_template(); break;
		case ICS206: cb_206_save_template(); break;
		case ICS213: cb_213_save_template(); break;
		case ICS214: cb_214_save_template(); break;
		case ICS216: cb_216_save_template(); break;
		case HICS203: cb_hics203_save_template(); break;
		case HICS206: h206_cb_save_template(); break;
		case HICS213: h213_cb_save_template(); break;
		case HICS214: hics214_cb_save_template(); break;
		case RADIOGRAM: cb_rg_save_template(); break;
		case IARU: iaru_cb_save_template(); break;
		case PLAINTEXT: cb_pt_save_template(); break;
		case BLANK: cb_blank_save_template(); break;
		case MARSDAILY: cb_mars_daily_save_template(); break;
		case MARSINEEI: cb_mars_ineei_save_template(); break;
		case MARSNET: cb_mars_net_save_template(); break;
		case MARSARMY: cb_mars_army_save_template(); break;
		case MARSNAVY: cb_mars_navy_save_template(); break;
		case REDXSNW: cb_redx_snw_save_template(); break;
		case REDX5739: cb_redx_5739_save_template(); break;
		default: ;
	}
}

void cb_save_as_template()
{
	switch (selected_form) {
		case ICS203: cb_203_save_as_template(); break;
		case ICS205: cb_205_save_as_template(); break;
		case ICS205A: cb_205a_save_as_template(); break;
		case ICS206: cb_206_save_as_template(); break;
		case ICS213: cb_213_save_as_template(); break;
		case ICS214: cb_214_save_as_template(); break;
		case ICS216: cb_216_save_as_template(); break;
		case HICS203: cb_hics203_save_as_template(); break;
		case HICS206: h206_cb_save_as_template(); break;
		case HICS213: h213_cb_save_as_template(); break;
		case HICS214: hics214_cb_save_as_template(); break;
		case RADIOGRAM: cb_rg_save_as_template(); break;
		case IARU: iaru_cb_save_as_template(); break;
		case PLAINTEXT: cb_pt_save_as_template(); break;
		case BLANK: cb_blank_save_as_template(); break;
		case MARSDAILY: cb_mars_daily_save_as_template(); break;
		case MARSINEEI: cb_mars_ineei_save_as_template(); break;
		case MARSNET: cb_mars_net_save_as_template(); break;
		case MARSARMY: cb_mars_army_save_as_template(); break;
		case MARSNAVY: cb_mars_navy_save_as_template(); break;
		case REDXSNW: cb_redx_snw_save_as_template(); break;
		case REDX5739: cb_redx_5739_save_as_template(); break;
		default: ;
	}
}

void cb_open()
{
	switch (selected_form) {
		case ICS203: cb_203_open(); break;
		case ICS205: cb_205_open(); break;
		case ICS205A: cb_205a_open(); break;
		case ICS206: cb_206_open(); break;
		case ICS213: cb_213_open(); break;
		case ICS214: cb_214_open(); break;
		case ICS216: cb_216_open(); break;
		case HICS203: cb_hics203_open(); break;
		case HICS206: h206_cb_open(); break;
		case HICS213: h213_cb_open(); break;
		case HICS214: hics214_cb_open(); break;
		case RADIOGRAM: cb_rg_open(); break;
		case IARU: iaru_cb_open(); break;
		case PLAINTEXT: cb_pt_open(); break;
		case BLANK: cb_blank_open(); break;
		case MARSDAILY: cb_mars_daily_open(); break;
		case MARSINEEI: cb_mars_ineei_open(); break;
		case MARSNET: cb_mars_net_open(); break;
		case MARSARMY: cb_mars_army_open(); break;
		case MARSNAVY: cb_mars_navy_open(); break;
		case REDXSNW: cb_redx_snw_open(); break;
		case REDX5739: cb_redx_5739_open(); break;
		default : ;
	}
}

void cb_save_as()
{
	switch (selected_form) {
		case ICS203: cb_203_save_as(); break;
		case ICS205: cb_205_save_as(); break;
		case ICS205A: cb_205a_save_as(); break;
		case ICS206: cb_206_save_as(); break;
		case ICS213: cb_213_save_as(); break;
		case ICS214: cb_214_save_as(); break;
		case ICS216: cb_216_save_as(); break;
		case HICS203: cb_hics203_save_as(); break;
		case HICS206: h206_cb_save_as(); break;
		case HICS213: h213_cb_save_as(); break;
		case HICS214: hics214_cb_save_as(); break;
		case RADIOGRAM: cb_rg_save_as(); break;
		case IARU: iaru_cb_save_as(); break;
		case PLAINTEXT: cb_pt_save_as(); break;
		case MARSDAILY: cb_mars_daily_save_as(); break;
		case MARSINEEI: cb_mars_ineei_save_as(); break;
		case MARSNET: cb_mars_net_save_as(); break;
		case MARSARMY: cb_mars_army_save_as(); break;
		case MARSNAVY: cb_mars_navy_save_as(); break;
		case REDXSNW: cb_redx_snw_save_as(); break;
		case REDX5739: cb_redx_5739_save_as(); break;
		case BLANK: cb_blank_save_as(); break;
		default: ;
	}
}

void cb_save()
{
	switch (selected_form) {
		case ICS203: cb_203_save(); break;
		case ICS205: cb_205_save(); break;
		case ICS205A: cb_205a_save(); break;
		case ICS206: cb_206_save(); break;
		case ICS213: cb_213_save(); break;
		case ICS214: cb_214_save(); break;
		case ICS216: cb_216_save(); break;
		case HICS203: cb_hics203_save(); break;
		case HICS206: h206_cb_save(); break;
		case HICS213: h213_cb_save(); break;
		case HICS214: hics214_cb_save(); break;
		case RADIOGRAM: cb_rg_save(); break;
		case IARU: iaru_cb_save(); break;
		case PLAINTEXT: cb_pt_save(); break;
		case MARSDAILY: cb_mars_daily_save(); break;
		case MARSINEEI: cb_mars_ineei_save(); break;
		case MARSNET: cb_mars_net_save(); break;
		case MARSARMY: cb_mars_army_save(); break;
		case MARSNAVY: cb_mars_navy_save(); break;
		case REDXSNW: cb_redx_snw_save(); break;
		case REDX5739: cb_redx_5739_save(); break;
		case BLANK: cb_blank_save(); break;
		default: ;
	}
}

void cb_html()
{
	switch (selected_form) {
		case ICS203: cb_203_html(); break;
		case ICS205: cb_205_html(); break;
		case ICS205A: cb_205a_html(); break;
		case ICS206: cb_206_html(); break;
		case ICS213: cb_213_html(); break;
		case ICS214: cb_214_html(); break;
		case ICS216: cb_216_html(); break;
		case HICS203: cb_hics203_html(); break;
		case HICS206: h206_cb_html(); break;
		case HICS213: h213_cb_html(); break;
		case HICS214: hics214_cb_html(); break;
		case RADIOGRAM: cb_rg_html(); break;
		case IARU: iaru_cb_html(); break;
		case PLAINTEXT: cb_pt_html(); break;
		case MARSDAILY: cb_mars_daily_html(); break;
		case MARSINEEI: cb_mars_ineei_html(); break;
		case MARSNET: cb_mars_net_html(); break;
		case MARSARMY: cb_mars_army_html(); break;
		case MARSNAVY: cb_mars_navy_html(); break;
		case REDXSNW: cb_redx_snw_html(); break;
		case REDX5739: cb_redx_5739_html(); break;
		case BLANK: cb_blank_html(); break;
		default: ;
	}
}

void cb_html_fcopy()
{
	switch (selected_form) {
		case ICS203: cb_203_html(); break;
		case ICS205: cb_205_html(); break;
		case ICS205A: cb_205a_html(); break;
		case ICS206: cb_206_html(); break;
		case ICS213: cb_213_html(); break;
		case ICS214: cb_214_html(); break;
		case ICS216: cb_216_html(); break;
		case HICS203: cb_hics203_html(); break;
		case HICS206: h206_cb_html(); break;
		case HICS213: h213_cb_html(); break;
		case HICS214: hics214_cb_html(); break;
		case RADIOGRAM: cb_rg_html_fcopy(); break;
		default:
			fl_alert2("Not implemented for this form type");
	}
}

void cb_text()
{
	switch (selected_form) {
		case ICS203: cb_203_textout(); break;
		case ICS205: cb_205_textout(); break;
		case ICS205A: cb_205a_textout(); break;
		case ICS206: cb_206_textout(); break;
		case ICS213: cb_213_textout(); break;
		case ICS214: cb_214_textout(); break;
		case ICS216: cb_216_textout(); break;
		case HICS203: cb_hics203_textout(); break;
		case HICS206: h206_cb_textout(); break;
		case HICS213: h213_cb_textout(); break;
		case HICS214: hics214_cb_textout(); break;
		case RADIOGRAM: cb_rg_textout(); break;
		case IARU: iaru_cb_textout(); break;
		case PLAINTEXT: cb_pt_textout(); break;
		case MARSDAILY: cb_mars_daily_textout(); break;
		case MARSINEEI: cb_mars_ineei_textout(); break;
		case MARSNET: cb_mars_net_textout(); break;
		case MARSARMY: cb_mars_army_textout(); break;
		case MARSNAVY: cb_mars_navy_textout(); break;
		case REDXSNW: cb_redx_snw_textout(); break;
		case REDX5739: cb_redx_5739_textout(); break;
		case BLANK:
		default: cb_blank_textout();
	}
}

void cb_exit()
{
	progStatus.saveLastState();
	FSEL::destroy();
	debug::stop();
	exit(0);
}

void exit_main(Fl_Widget *w)
{
	if (Fl::event_key() == FL_Escape)
		return;
	cb_exit();
}

void cb_About()
{
	fl_alert2(_("Version "PACKAGE_VERSION));
}

void cb_folders()
{
	open_url(FLMSG_dir.c_str());
}

void show_filename(string p)
{
	switch (selected_form) {
		case ICS203: 
			base_203_filename = fl_filename_name(p.c_str());
			break;
		case ICS205:
			base_205_filename = fl_filename_name(p.c_str());
			break;
		case ICS205A:
			base_205a_filename = fl_filename_name(p.c_str());
			break;
		case ICS206:
			base_206_filename = fl_filename_name(p.c_str());
			break;
		case ICS213:
			base_213_filename = fl_filename_name(p.c_str());
			break;
		case ICS214:
			base_214_filename = fl_filename_name(p.c_str());
			break;
		case ICS216:
			base_216_filename = fl_filename_name(p.c_str());
			break;
		case HICS203:
			base_hics203_filename = fl_filename_name(p.c_str());
			break;
		case HICS206:
			h206_base_filename = fl_filename_name(p.c_str());
			break;
		case HICS213:
			h213_base_filename = fl_filename_name(p.c_str());
			break;
		case HICS214:
			hics214_base_filename = fl_filename_name(p.c_str());
			break;
		case RADIOGRAM:
			base_rg_filename = fl_filename_name(p.c_str());
			break;
		case IARU:
			iaru_base_filename = fl_filename_name(p.c_str());
			break;
		case PLAINTEXT:
			base_pt_filename = fl_filename_name(p.c_str());
			break;
		case MARSDAILY:
			base_mars_daily_filename = fl_filename_name(p.c_str());
			break;
		case MARSINEEI:
			base_mars_ineei_filename = fl_filename_name(p.c_str());
			break;
		case MARSNET:
			base_mars_net_filename = fl_filename_name(p.c_str());
			break;
		case MARSARMY:
			base_mars_army_filename = fl_filename_name(p.c_str());
			break;
		case MARSNAVY:
			base_mars_navy_filename = fl_filename_name(p.c_str());
			break;
		case REDXSNW:
			base_redx_snw_filename = fl_filename_name(p.c_str());
			break;
		case REDX5739:
			base_redx_5739_filename = fl_filename_name(p.c_str());
			break;
		case BLANK:
			base_blank_filename = fl_filename_name(p.c_str());
			break;
		default:
			return;
	}
	txt_filename->value(fl_filename_name(p.c_str()));
	txt_filename->redraw();
}

void set_main_label()
{
	string main_label = PACKAGE_NAME;
	main_label.append(": ").append(PACKAGE_VERSION);
	mainwindow->label(main_label.c_str());
}

#define KNAME "fllog"

#if !defined(__APPLE__) && !defined(__WOE32__) && USE_X
Pixmap  flmsg_icon_pixmap;

void make_pixmap(Pixmap *xpm, const char **data)
{
	Fl_Window w(0,0, KNAME);
	w.xclass(KNAME);
	w.show();
	w.make_current();
	Fl_Pixmap icon(data);
	int maxd = (icon.w() > icon.h()) ? icon.w() : icon.h();
	*xpm = fl_create_offscreen(maxd, maxd);
	fl_begin_offscreen(*xpm);
	fl_color(FL_BACKGROUND_COLOR);
	fl_rectf(0, 0, maxd, maxd);
	icon.draw(maxd - icon.w(), maxd - icon.h());
	fl_end_offscreen();
}

#endif


void default_form()
{
	selected_form = progStatus.tab;
	select_form(selected_form);
	cb_new();
}

#if FLMSG_FLTK_API_MAJOR == 1 && FLMSG_FLTK_API_MINOR == 3
int default_handler(int event)
{
	if (event != FL_SHORTCUT)
		return 0;

	else if (Fl::event_ctrl())  {
		Fl_Widget* w = Fl::focus();
		return w->handle(FL_KEYBOARD);
	}

	return 0;
}
#endif

void after_start(void *)
{
	checkdirectories();

	string debug_file = FLMSG_dir;
	debug_file.append("debug_log.txt");
	debug::start(debug_file.c_str());

	LOG_INFO("FLMSG_dir     %s", FLMSG_dir.c_str());
	LOG_INFO("ARQ_dir       %s", ARQ_dir.c_str());
	LOG_INFO("ARQ_files_dir %s", ARQ_files_dir.c_str());
	LOG_INFO("ARQ_recv_dir  %s", ARQ_recv_dir.c_str());
	LOG_INFO("ARQ_send_dir  %s", ARQ_send_dir.c_str());
	LOG_INFO("WRAP_dir      %s", WRAP_dir.c_str());
	LOG_INFO("WRAP_recv_dir %s", WRAP_recv_dir.c_str());
	LOG_INFO("WRAP_send_dir %s", WRAP_send_dir.c_str());
	LOG_INFO("WRAP_auto_dir %s", WRAP_auto_dir.c_str());
	LOG_INFO("ICS_dir       %s", ICS_dir.c_str());
	LOG_INFO("ICS_msg_dir   %s", ICS_msg_dir.c_str());
	LOG_INFO("ICS_tmp_dir   %s", ICS_tmp_dir.c_str());

	def_203_filename = ICS_msg_dir;
	def_203_filename.append("default"F203_EXT);
	def_203_TemplateName = ICS_tmp_dir;
	def_203_TemplateName.append("default"T203_EXT);

	def_205_filename = ICS_msg_dir;
	def_205_filename.append("default"F205_EXT);
	def_205_TemplateName = ICS_tmp_dir;
	def_205_TemplateName.append("default"T205_EXT);

	def_205a_filename = ICS_msg_dir;
	def_205a_filename.append("default"F205A_EXT);
	def_205a_TemplateName = ICS_tmp_dir;
	def_205a_TemplateName.append("default"T205A_EXT);

	def_206_filename = ICS_msg_dir;
	def_206_filename.append("default"F206_EXT);
	def_206_TemplateName = ICS_tmp_dir;
	def_206_TemplateName.append("default"T206_EXT);

	def_213_filename = ICS_msg_dir;
	def_213_filename.append("default"F213_EXT);
	def_213_TemplateName = ICS_tmp_dir;
	def_213_TemplateName.append("default"T213_EXT);

	def_214_filename = ICS_msg_dir;
	def_214_filename.append("default"F214_EXT);
	def_214_TemplateName = ICS_tmp_dir;
	def_214_TemplateName.append("default"T214_EXT);

	def_216_filename = ICS_msg_dir;
	def_216_filename.append("default"F216_EXT);
	def_216_TemplateName = ICS_tmp_dir;
	def_216_TemplateName.append("default"T216_EXT);

	def_hics203_filename = ICS_msg_dir;
	def_hics203_filename.append("default"HF203_EXT);
	def_hics203_TemplateName = ICS_tmp_dir;
	def_hics203_TemplateName.append("default"HT203_EXT);

	h206_def_filename = ICS_msg_dir;
	h206_def_filename.append("default"HF206_EXT);
	h206_def_template_name = ICS_tmp_dir;
	h206_def_template_name.append("default"HT206_EXT);

	h213_def_filename = ICS_msg_dir;
	h213_def_filename.append("default"HF213_EXT);
	h213_def_template_name = ICS_tmp_dir;
	h213_def_template_name.append("default"HT213_EXT);

	hics214_def_filename = ICS_msg_dir;
	hics214_def_filename.append("default"HF214_EXT);
	hics214_template_name = ICS_tmp_dir;
	hics214_template_name.append("default"HT214_EXT);

	def_rg_filename = ICS_msg_dir;
	def_rg_filename.append("default"RGFILE_EXT);
	def_rg_TemplateName = ICS_tmp_dir;
	def_rg_TemplateName.append("default"RGTEMP_EXT);
	set_rg_choices();

	iaru_def_filename = ICS_msg_dir;
	iaru_def_filename.append("default"IARU_FILE_EXT);
	iaru_def_template_name = ICS_tmp_dir;
	iaru_def_template_name.append("default"IARU_TEMP_EXT);
	iaru_set_choices();

	def_pt_filename = ICS_msg_dir;
	def_pt_filename.append("default"PTFILE_EXT);
	def_pt_TemplateName = ICS_tmp_dir;
	def_pt_TemplateName.append("default"PTTEMP_EXT);

	def_blank_filename = ICS_msg_dir;
	def_blank_filename.append("default"BLANKFILE_EXT);
	def_blank_TemplateName = ICS_tmp_dir;
	def_blank_TemplateName.append("default"BLANKTEMP_EXT);

	def_mars_daily_filename = ICS_msg_dir;
	def_mars_daily_filename.append("default"FMARSDAILY_EXT);
	def_mars_daily_TemplateName = ICS_tmp_dir;
	def_mars_daily_TemplateName.append("default"TMARSDAILY_EXT);

	def_mars_ineei_filename = ICS_msg_dir;
	def_mars_ineei_filename.append("default"FMARSINEEI_EXT);
	def_mars_ineei_TemplateName = ICS_tmp_dir;
	def_mars_ineei_TemplateName.append("default"TMARSINEEI_EXT);

	def_mars_net_filename = ICS_msg_dir;
	def_mars_net_filename.append("default"FMARSNET_EXT);
	def_mars_net_TemplateName = ICS_tmp_dir;
	def_mars_net_TemplateName.append("default"TMARSNET_EXT);

	def_mars_army_filename = ICS_msg_dir;
	def_mars_army_filename.append("default"FMARSARMY_EXT);
	def_mars_army_TemplateName = ICS_tmp_dir;
	def_mars_army_TemplateName.append("default"TMARSARMY_EXT);

	def_mars_navy_filename = ICS_msg_dir;
	def_mars_navy_filename.append("default"FMARSNAVY_EXT);
	def_mars_navy_TemplateName = ICS_tmp_dir;
	def_mars_navy_TemplateName.append("default"TMARSNAVY_EXT);

	def_redx_snw_filename = ICS_msg_dir;
	def_redx_snw_filename.append("default"FREDXSNW_EXT);
	def_redx_snw_TemplateName = ICS_tmp_dir;
	def_redx_snw_TemplateName.append("default"TREDXSNW_EXT);

	def_redx_5739_filename = ICS_msg_dir;
	def_redx_5739_filename.append("default"FREDX5739_EXT);
	def_redx_5739_TemplateName = ICS_tmp_dir;
	def_redx_5739_TemplateName.append("default"TREDX5739_EXT);

	if (!cmd_fname.empty()) {
		if (cmd_fname.find(WRAP_EXT) != string::npos)
			wrap_import(cmd_fname.c_str());
		else {
			read_data_file(cmd_fname);
			show_filename(cmd_fname);
		}
	} else
		default_form();

}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		if (strcasecmp("--help", argv[1]) == 0) {
			printf("\
  --help\n\
  --version\n\
  --flmsg-dir \"full-path-name-of-folder for all FLMSG folders\"\n\
  --auto-dir \"full-path-name-of-folder for autosend files\"\n\
    auto-dir and flmsg-dir can be separate and unique\n\
  --p FILENAME - print and exit\n\
  --b FILENAME - print and stay open\n\n");
			return 0;
		} 
		if (strcasecmp("--version", argv[1]) == 0) {
			printf("Version: "VERSION"\n");
			return 0;
		}
	}

	Fl::lock();

	int arg_idx;
	if (Fl::args(argc, argv, arg_idx, parse_args) != argc)
		showoptions();

	char dirbuf[FL_PATH_MAX + 1];
	fl_filename_expand(dirbuf, sizeof(dirbuf) - 1, FLMSG_dir_default.c_str());
	FLMSG_dir = dirbuf;
	size_t len = FLMSG_dir.length();
	if (!(FLMSG_dir[len - 1] == '/' || FLMSG_dir[len-1] == '\\'))
		FLMSG_dir += '/';

	mainwindow = flmsg_dialog();
	mainwindow->callback(exit_main);

#if FLMSG_FLTK_API_MAJOR == 1 && FLMSG_FLTK_API_MINOR == 3
	Fl::add_handler(default_handler);
#endif

	config_files_window = config_files_dialog();
	config_datetime_window = date_time_dialog();
	config_radiogram_window = radiogram_dialog();

	Fl_File_Icon::load_system_icons();
	FSEL::create();

	if (printme) {
		print_and_exit();
		if (exit_after_print)
			return 0;
	}

	progStatus.loadLastState();

	mainwindow->resize( progStatus.mainX, progStatus.mainY, mainwindow->w(), mainwindow->h());

#if defined(__WOE32__)
#  ifndef IDI_ICON
#    define IDI_ICON 101
#  endif
	mainwindow->icon((char*)LoadIcon(fl_display, MAKEINTRESOURCE(IDI_ICON)));
	mainwindow->show (argc, argv);
#elif !defined(__APPLE__)
	make_pixmap(&flmsg_icon_pixmap, flmsg_icon);
	mainwindow->icon((char *)flmsg_icon_pixmap);
	mainwindow->show(argc, argv);
#else
	mainwindow->show(argc, argv);
#endif

	set_main_label();

	Fl::add_timeout(0.10, after_start);

	return Fl::run();
}

void print_and_exit()
{
	if (!cmd_fname.empty()) {

		if (cmd_fname.find(WRAP_EXT) != string::npos) {
			wrap_import(cmd_fname.c_str());
		} else {
			read_data_file(cmd_fname);
		}

		switch (selected_form) {
		case ICS203 :
			cb_203_save();
			cb_203_html();
			break;
		case ICS205 :
			cb_205_save();
			cb_205_html();
			break;
		case ICS205A :
			cb_205a_save();
			cb_205a_html();
			break;
		case ICS206 :
			cb_206_save();
			cb_206_html();
			break;
		case ICS213 :
			cb_213_save();
			cb_213_html();
			break;
		case ICS214 :
			cb_214_save();
			cb_214_html();
			break;
		case ICS216 :
			cb_216_save();
			cb_216_html();
			break;
		case HICS203 :
			cb_hics203_save();
			cb_hics203_html();
			break;
		case HICS206 :
			h206_cb_save();
			h206_cb_html();
			break;
		case HICS213 :
			h213_cb_save();
			h213_cb_html();
			break;
		case HICS214 :
			hics214_cb_save();
			hics214_cb_html();
			break;
		case RADIOGRAM :
			cb_rg_save();
			cb_rg_html();
			break;
		case PLAINTEXT :
			cb_pt_save();
			cb_pt_html();
			break;
		case BLANK :
			cb_blank_save();
			cb_blank_html();
			break;
		case MARSDAILY :
			cb_mars_daily_save();
			cb_mars_daily_html();
			break;
		case MARSINEEI :
			cb_mars_ineei_save();
			cb_mars_ineei_html();
			break;
		case MARSNET :
			cb_mars_net_save();
			cb_mars_net_html();
			break;
		case MARSARMY :
			cb_mars_army_save();
			cb_mars_army_html();
			break;
		case MARSNAVY :
			cb_mars_navy_save();
			cb_mars_navy_html();
			break;
		case REDXSNW :
			cb_redx_snw_save();
			cb_redx_snw_html();
			break;
		case REDX5739 :
			cb_redx_5739_save();
			cb_redx_5739_html();
			break;
		}
	}
}

void drop_box_changed()
{
	string 	buffer = drop_box->value();
	size_t n;
	drop_box->value("");
	drop_box->redraw();
	if ((n = buffer.find("file:///")) != string::npos)
		buffer.erase(0, n + 7);
	if ((buffer.find(":\\")) != string::npos || (buffer.find("/") == 0)) {
		while ((n = buffer.find('\n')) != string::npos)
			buffer.erase(n, 1);
		while ((n = buffer.find('\r')) != string::npos)
			buffer.erase(n, 1);
		if (buffer.find(WRAP_EXT) != string::npos)
			wrap_import(buffer.c_str());
		else 
			read_data_file(buffer.c_str());
	} else // try to extract as a text buffer
		extract_text(buffer, NULL);
}

void drop_file_changed()
{
	string 	buffer = drop_file->value();
	size_t n;
	drop_file->value("");
	drop_file->redraw();
	if ((n = buffer.find("file:///")) != string::npos)
		buffer.erase(0, n + 7);
	if ((buffer.find(":\\")) != string::npos || (buffer.find("/") == 0)) {
		while ((n = buffer.find('\n')) != string::npos)
			buffer.erase(n, 1);
		while ((n = buffer.find('\r')) != string::npos)
			buffer.erase(n, 1);
		if (buffer.find(WRAP_EXT) != string::npos)
			wrap_import(buffer.c_str());
		else 
			read_data_file(buffer.c_str());
	} else // try to extract as a text buffer
		extract_text(buffer, NULL);
}

void checkdirectories(void)
{
	struct DIRS {
		string& dir;
		const char* suffix;
		void (*new_dir_func)(void);
	};
	DIRS FLMSG_dirs[] = {
		{ FLMSG_dir,     0, 0 },
		{ ARQ_dir,       "ARQ", 0 },
		{ ARQ_files_dir, "ARQ/files", 0 },
		{ ARQ_recv_dir,  "ARQ/recv", 0 },
		{ ARQ_send_dir,      "ARQ/send", 0 },
		{ WRAP_dir,      "WRAP", 0 },
		{ WRAP_recv_dir, "WRAP/recv", 0 },
		{ WRAP_send_dir, "WRAP/send", 0 },
		{ WRAP_auto_dir, "WRAP/auto", 0 },
		{ ICS_dir,       "ICS", 0 },
		{ ICS_msg_dir,   "ICS/messages", 0 },
		{ ICS_tmp_dir,   "ICS/templates", 0 },
	};

	int r;

	for (size_t i = 0; i < sizeof(FLMSG_dirs)/sizeof(*FLMSG_dirs); i++) {
		if (FLMSG_dirs[i].dir.empty() && FLMSG_dirs[i].suffix)
			FLMSG_dirs[i].dir.assign(FLMSG_dir).append(FLMSG_dirs[i].suffix).append(PATH_SEP);

		if ((r = mkdir(FLMSG_dirs[i].dir.c_str(), 0777)) == -1 && errno != EEXIST) {
			cerr << _("Could not make directory") << ' ' << FLMSG_dirs[i].dir
			     << ": " << strerror(errno) << '\n';
			exit(EXIT_FAILURE);
		}
		else if (r == 0 && FLMSG_dirs[i].new_dir_func)
			FLMSG_dirs[i].new_dir_func();
	}

}

const char *options[] = {\
"-bg\t-background [COLOR]",
"-bg2\t-background2 [COLOR]",
"-di\t-display [host:n.n]",
"-dn\t-dnd : enable drag and drop",
"-nodn\t-nodnd : disable drag and drop",
"-fg\t-foreground [COLOR]",
"-g\t-geometry [WxH+X+Y]",
"-i\t-iconic",
"-k\t-kbd : enable keyboard focus:",
"-nok\t-nokbd : en/disable keyboard focus",
"-na\t-name [CLASSNAME]",
"-s\t-scheme [plastic | gtk+]",
"-ti\t-title [WINDOWTITLE]",
"-to\t-tooltips : enable tooltips",
"-not\t-notooltips : disable tooltips\n",
0
};

const int widths[] = {60, 0};

void showoptions()
{
	if (!optionswindow) {
		optionswindow = optionsdialog();
		brwsOptions->column_widths(widths);
		for (int i = 0; options[i] != 0; i++)
			brwsOptions->add(options[i]);
	}
	optionswindow->show();
}

void closeoptions()
{
	optionswindow->hide();
}

void cb_config_date_time()
{
	btn_dtformat0->value(progStatus.dtformat == 0);
	btn_dtformat1->value(progStatus.dtformat == 1);
	btn_dtformat2->value(progStatus.dtformat == 2);

	btn_utc_format0->value(progStatus.UTC == 0);
	btn_utc_format1->value(progStatus.UTC == 1);
	btn_utc_format2->value(progStatus.UTC == 2);
	btn_utc_format3->value(progStatus.UTC == 3);
	btn_utc_format4->value(progStatus.UTC == 4);
	btn_utc_format5->value(progStatus.UTC == 5);

	config_datetime_window->show();
}

void cb_config_radiogram()
{
	txt_my_call->value(progStatus.my_call.c_str());
	txt_my_name->value(progStatus.my_name.c_str());
	txt_my_addr->value(progStatus.my_addr.c_str());
	txt_my_city->value(progStatus.my_city.c_str());
	txt_my_tel->value(progStatus.my_tel.c_str());

	cnt_wpl->value(progStatus.wpl);

	txt_rgnbr->value(progStatus.rgnbr.c_str());
	btn_rgnbr_fname->value(progStatus.rgnbr_fname);

	config_radiogram_window->show();
}

void cb_config_files()
{
	btn_open_on_export->value(progStatus.open_on_export);
	txt_sernbr->value(progStatus.sernbr.c_str());
	btn_sernbr_fname->value(progStatus.sernbr_fname);
	btn_call_fname->value(progStatus.call_fname);
	btn_dt_fname->value(progStatus.dt_fname);

	txt_mars_roster_file->value(progStatus.mars_roster_file.c_str());

	config_files_window->show();
}

void show_help()
{
	open_url("http://www.w1hkj.com/flmsg-help/index.html");
}

int parse_args(int argc, char **argv, int& idx)
{
// Only handle a filename option

	if (strstr(argv[idx], "--p")) {
		printme = true;
		exit_after_print = true;
		idx++;
		return 1;
	}

	if (strstr(argv[idx], "--b")) {
		printme = true;
		idx++;
		return 1;
	}

	if (strstr(argv[idx], "--flmsg-dir")) {
		idx++;
		string tmp = argv[idx];
		if (!tmp.empty()) FLMSG_dir_default = tmp;
		size_t p = string::npos;
		while ( (p = FLMSG_dir_default.find("\\")) != string::npos)
			FLMSG_dir_default[p] = '/';
		idx++;
		return 1;
	}

	if (strstr(argv[idx], "--auto-dir")) {
		idx++;
		string tmp = argv[idx];
		if (!tmp.empty()) WRAP_auto_dir = tmp;
		size_t p = string::npos;
		while ( (p = WRAP_auto_dir.find("\\")) != string::npos)
			WRAP_auto_dir[p] = '/';
		idx++;
		return 1;
	}

	if ( argv[idx][0] == '-' )
		return 0;

	string fname = argv[idx];
	if (fname.find(DATAFILE_EXT) != string::npos ||
		fname.find(DATATEMP_EXT) != string::npos ||

		fname.find(F203_EXT) != string::npos ||
		fname.find(T203_EXT) != string::npos ||

		fname.find(F205_EXT) != string::npos ||
		fname.find(T205_EXT) != string::npos ||

		fname.find(F205A_EXT) != string::npos ||
		fname.find(T205A_EXT) != string::npos ||

		fname.find(F206_EXT) != string::npos ||
		fname.find(T206_EXT) != string::npos ||

		fname.find(F213_EXT) != string::npos ||
		fname.find(T213_EXT) != string::npos ||

		fname.find(F214_EXT) != string::npos ||
		fname.find(T214_EXT) != string::npos ||

		fname.find(F216_EXT) != string::npos ||
		fname.find(T216_EXT) != string::npos ||

		fname.find(HF203_EXT) != string::npos ||
		fname.find(HT203_EXT) != string::npos ||

		fname.find(HF206_EXT) != string::npos ||
		fname.find(HT206_EXT) != string::npos ||

		fname.find(HF213_EXT) != string::npos ||
		fname.find(HT213_EXT) != string::npos ||

		fname.find(HF214_EXT) != string::npos ||
		fname.find(HT214_EXT) != string::npos ||

		fname.find(RGFILE_EXT) != string::npos ||
		fname.find(RGTEMP_EXT) != string::npos ||

		fname.find(PTFILE_EXT) != string::npos ||
		fname.find(PTTEMP_EXT) != string::npos ||

		fname.find(BLANKFILE_EXT) != string::npos ||
		fname.find(BLANKTEMP_EXT) != string::npos ||

		fname.find(FMARSDAILY_EXT) != string::npos ||
		fname.find(TMARSDAILY_EXT) != string::npos ||

		fname.find(FMARSINEEI_EXT) != string::npos ||
		fname.find(TMARSINEEI_EXT) != string::npos ||

		fname.find(FMARSNET_EXT) != string::npos ||
		fname.find(TMARSNET_EXT) != string::npos ||

		fname.find(FMARSARMY_EXT) != string::npos ||
		fname.find(TMARSARMY_EXT) != string::npos ||

		fname.find(FMARSNAVY_EXT) != string::npos ||
		fname.find(TMARSNAVY_EXT) != string::npos ||

		fname.find(FREDXSNW_EXT) != string::npos ||
		fname.find(TREDXSNW_EXT) != string::npos ||

		fname.find(FREDX5739_EXT) != string::npos ||
		fname.find(TREDX5739_EXT) != string::npos ||

		fname.find(WRAP_EXT) != string::npos ) {
		cmd_fname = fname;
	}
	idx++;
	return 1;
}

void open_url(const char* url)
{
#ifndef __WOE32__
	const char* browsers[] = {
#  ifdef __APPLE__
		getenv("FLDIGI_BROWSER"), // valid for any OS - set by user
		"open"                    // OS X
#  else
		"fl-xdg-open",            // Puppy Linux
		"xdg-open",               // other Unix-Linux distros
		getenv("FLDIGI_BROWSER"), // force use of spec'd browser
		getenv("BROWSER"),        // most Linux distributions
		"sensible-browser",
		"firefox",
		"mozilla"                 // must be something out there!
#  endif
	};
	switch (fork()) {
	case 0:
#  ifndef NDEBUG
		unsetenv("MALLOC_CHECK_");
		unsetenv("MALLOC_PERTURB_");
#  endif
		for (size_t i = 0; i < sizeof(browsers)/sizeof(browsers[0]); i++)
			if (browsers[i])
				execlp(browsers[i], browsers[i], url, (char*)0);
		exit(EXIT_FAILURE);
	case -1:
		fl_alert2(_("Could not run a web browser:\n%s\n\n"
			 "Open this URL manually:\n%s"),
			 strerror(errno), url);
	}
#else
	if ((int)ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL) <= 32)
		fl_alert2(_("Could not open url:\n%s\n"), url);
#endif
}
