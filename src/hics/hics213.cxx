// =====================================================================
//
// hics213.cxx
//
// Author: Dave Freese, W1HKJ
// Copyright: 2010
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
#include "parse_xml.h"

#ifdef WIN32
#  include "flmsgrc.h"
#  include "compat.h"
#  define dirent fl_dirent_no_thanks
#endif

#include <FL/filename.H>
#ifdef __MINGW32__
#  undef dirent
#endif
#include <dirent.h>

#include <FL/x.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Image.H>

using namespace std;

string h213_buffer;
string h213_base_filename = "";
string h213_def_filename = "";
string h213_def_template_name = "";

bool h213_using_template = false;

string h213_tag_to			= ":1:";
string h213_tag_fm			= ":2:";
string h213_tag_date		= ":3:";
string h213_tag_time		= ":4:";
string h213_tag_via_phone	= ":5a:";
string h213_tag_via_radio	= ":5b:";
string h213_tag_via_other	= ":5c:";
string h213_tag_reply_yes	= ":6a:";
string h213_tag_reply_no	= ":6b:";
string h213_tag_reply_to	= ":6c:";
string h213_tag_priority	= ":7:";
string h213_tag_high		= ":7a:";
string h213_tag_medium		= ":7b:";
string h213_tag_low			= ":7c:";
string h213_tag_msg			= ":8:";
string h213_tag_action		= ":9:";
string h213_tag_rcvd_by		= ":10:";
string h213_tag_time_rcvd	= ":11:";
string h213_tag_fwd_to		= ":12:";
string h213_tag_comments	= ":13:";
string h213_tag_rcvd_by2	= ":14:";
string h213_tag_time_rcvd2	= ":15:";
string h213_tag_fwd_to2		= ":16:";
string h213_tag_comments2	= ":17:";
string h213_tag_facility	= ":18:";

FIELD h213_fields[] = {
{ h213_tag_to,			"", (void **)&h213_txt_to,			't' },
{ h213_tag_fm,			"", (void **)&h213_txt_fm,			't' },
{ h213_tag_date,		"", (void **)&h213_txt_date,		'd' },
{ h213_tag_time,		"", (void **)&h213_txt_time,		't' },
{ h213_tag_via_phone,	"", (void **)&h213_btn_phone,		'b' },
{ h213_tag_via_radio,	"", (void **)&h213_btn_radio,		'b' },
{ h213_tag_via_other,	"", (void **)&h213_btn_other,		'b' },
{ h213_tag_reply_yes,	"", (void **)&h213_btn_yes,			'b' },
{ h213_tag_reply_no,	"", (void **)&h213_btn_no,			'b' },
{ h213_tag_reply_to,	"", (void **)&h213_txt_reply_to,	't' },
{ h213_tag_high,		"", (void **)&h213_btn_high,		'b' },
{ h213_tag_medium,		"", (void **)&h213_btn_medium,		'b' },
{ h213_tag_low,			"", (void **)&h213_btn_low,			'b' },
{ h213_tag_msg,			"", (void **)&h213_txt_msg,			'e' },
{ h213_tag_action,		"", (void **)&h213_txt_action,		'e' },
{ h213_tag_rcvd_by,		"", (void **)&h213_txt_rcvd_by,		't' },
{ h213_tag_time_rcvd,	"", (void **)&h213_txt_time_rcvd,	't' },
{ h213_tag_fwd_to,		"", (void **)&h213_txt_fwd_to,		't' },
{ h213_tag_comments,	"", (void **)&h213_txt_comments,	'e' },
{ h213_tag_rcvd_by2,	"", (void **)&h213_txt_rcvd_by2,	't' },
{ h213_tag_time_rcvd2,	"", (void **)&h213_txt_time_rcvd2,	't' },
{ h213_tag_fwd_to2,		"", (void **)&h213_txt_fwd_to2,		't' },
{ h213_tag_comments2,	"", (void **)&h213_txt_comments2,	'e' },
{ h213_tag_facility,	"", (void **)&h213_txt_facility,	't' } };

int h213_numfields = sizeof(h213_fields) / sizeof(FIELD);

void h213_cb_set_date()
{
	h213_txt_date->value(szDate());
}

void h213_cb_set_time0()
{
	h213_txt_time->value(szTime(progStatus.UTC));
}

void h213_cb_set_time1()
{
	h213_txt_time_rcvd->value(szTime(progStatus.UTC));
}

void h213_cb_set_time2()
{
	h213_txt_time_rcvd2->value(szTime(progStatus.UTC));
}

void h213_clear_fields()
{
	for (int i = 0; i < h213_numfields; i++)
		h213_fields[i].f_data.clear();
}

void h213_update_fields()
{
	for (int i = 0; i < h213_numfields; i++) {
		if (h213_fields[i].w_type == 'd')
			h213_fields[i].f_data = ((Fl_DateInput *)(*h213_fields[i].w))->value();
		else if (h213_fields[i].w_type == 't')
			h213_fields[i].f_data = ((Fl_Input2 *)(*h213_fields[i].w))->value();
		else if (h213_fields[i].w_type == 'e')
			h213_fields[i].f_data = ((FTextEdit *)(*h213_fields[i].w))->buffer()->text();
		else if (h213_fields[i].w_type == 'b')
			h213_fields[i].f_data = ((Fl_Check_Button *)(*h213_fields[i].w))->value() ? "X" : "";
	}
}

void h213_clear_form()
{
	h213_clear_fields();
	for (int i = 0; i < h213_numfields; i++) {
		if (h213_fields[i].w_type == 'd')
			((Fl_DateInput *)(*h213_fields[i].w))->value("");
		else if (h213_fields[i].w_type == 'b')
			((Fl_Check_Button *)(*h213_fields[i].w))->value(0);
		else if (h213_fields[i].w_type == 't')
			((Fl_Input2 *)(*h213_fields[i].w))->value("");
		else if (h213_fields[i].w_type == 'e')
			((FTextEdit *)(*h213_fields[i].w))->clear();
	}
	h213_update_fields();
}

void h213_update_form()
{
	for (int i = 0; i < h213_numfields; i++) {
		if (h213_fields[i].w_type == 'd')
			((Fl_DateInput *)(*h213_fields[i].w))->value(h213_fields[i].f_data.c_str());
		else if (h213_fields[i].w_type == 'b')
			((Fl_Check_Button *)(*h213_fields[i].w))->value(h213_fields[i].f_data == "X");
		else if (h213_fields[i].w_type == 't')
			((Fl_Input2 *)(*h213_fields[i].w))->value(h213_fields[i].f_data.c_str());
		else if (h213_fields[i].w_type == 'e') {
			((FTextEdit *)(*h213_fields[i].w))->clear();
			((FTextEdit *)(*h213_fields[i].w))->add(h213_fields[i].f_data.c_str());
		}
	}
}

void h213_make_buffer()
{
	h213_update_fields();
	h213_buffer = header("<hics213>");
	for (int i = 0; i < h213_numfields; i++)
		h213_buffer.append( lineout( h213_fields[i].f_type, h213_fields[i].f_data ) );
}

void h213_read_buffer(string data)
{
	bool data_ok = false;
	h213_clear_fields();
	for (int i = 0; i < h213_numfields; i++) {
		h213_fields[i].f_data = findstr(data, h213_fields[i].f_type);
		if (!h213_fields[i].f_data.empty()) data_ok = true;
	}
	h213_update_form();
}

void h213_cb_new()
{
	h213_clear_form();
	h213_def_filename = ICS_msg_dir;
	h213_def_filename.append("new"HF213_EXT);
	h213_using_template = false;
	show_filename(h213_def_filename);
}

void h213_cb_import()
{
	fl_alert2("Not implemented");
}

void h213_cb_export()
{
	fl_alert2("Not implemented");
}

void h213_cb_wrap_import(string wrapfilename, string inpbuffer)
{
	h213_clear_form();
	h213_read_buffer(inpbuffer);
	h213_def_filename = ICS_msg_dir;
	h213_def_filename.append(wrapfilename);
	h213_using_template = false;
	show_filename(h213_def_filename);
}

void h213_cb_wrap_export()
{
	if (h213_base_filename == "new"HF213_EXT || h213_base_filename == "default"HF213_EXT)
		h213_cb_save_as();

	string wrapfilename = WRAP_send_dir;
	wrapfilename.append(h213_base_filename);
	wrapfilename.append(WRAP_EXT);
	const char *p = FSEL::saveas(
			"Save as wrap file",
			"Wrap file\t*.{wrap,WRAP}",
			wrapfilename.c_str());
	if (p) {
		string pext = fl_filename_ext(p);
		wrapfilename = p;
		h213_make_buffer();
		export_wrapfile(h213_base_filename, wrapfilename, h213_buffer, pext != WRAP_EXT);
	}
}

void h213_cb_wrap_autosend()
{
	if (h213_base_filename == "new"HF213_EXT || h213_base_filename == "default"HF213_EXT)
		h213_cb_save_as();

	string wrapfilename = WRAP_auto_dir;
	wrapfilename.append("wrap_auto_file");
	h213_make_buffer();
	export_wrapfile(h213_base_filename, wrapfilename, h213_buffer, false);
}

void h213_cb_load_template()
{
	string h213_def_filename = h213_def_template_name;
	const char *p = FSEL::select(
			"Open template file",
			"Template file\t*"HT213_EXT,
			h213_def_filename.c_str());
	if (p) {
		h213_clear_form();
		read_data_file(p);
		h213_def_template_name = p;
		show_filename(h213_def_template_name);
		h213_using_template = true;
	}
}

void h213_cb_save_template()
{
	if (!h213_using_template) {
		cb_save_as_template();
		return;
	}
	string h213_def_filename = h213_def_template_name;
	const char *p = FSEL::saveas(
			"Save template file",
			"Template file\t*"HT213_EXT,
			h213_def_filename.c_str());
	if (p)
		h213_write(p);
}

void h213_cb_save_as_template()
{
	string h213_def_filename = h213_def_template_name;
	const char *p = FSEL::saveas(
			"Save as template file",
			"Template file\t*"HT213_EXT,
			h213_def_filename.c_str());
	if (p) {
		const char *pext = fl_filename_ext(p);
		h213_def_template_name = p;
		if (strlen(pext) == 0) h213_def_template_name.append(HT213_EXT);
		remove_spaces_from_filename(h213_def_template_name);
		h213_write(h213_def_template_name);
		show_filename(h213_def_template_name);
		h213_using_template = true;
	}
}

void h213_cb_open()
{
	const char *p = FSEL::select(_("Open data file"), "HICS-213\t*.{H213}",
					h213_def_filename.c_str());
	if (!p) return;
	if (strlen(p) == 0) return;
	h213_clear_form();
	read_data_file(p);
	h213_using_template = false;
	h213_def_filename = p;
	show_filename(h213_def_filename);
}

void h213_write(string s)
{
	FILE *hicsfile = fopen(s.c_str(), "w");
	if (!hicsfile) return;
	h213_make_buffer();
	fwrite(h213_buffer.c_str(), h213_buffer.length(), 1, hicsfile);
	fclose(hicsfile);
}

void h213_cb_save_as()
{
	const char *p;
	string newfilename;

	string name = named_file();
	if (!name.empty()) {
	name.append(HF213_EXT);
		newfilename = ICS_msg_dir;
		newfilename.append(name);
	} else
		newfilename = h213_def_filename;
	p = FSEL::saveas(_("Save data file"), "HICS-213\t*.{H213}",
					newfilename.c_str());
	if (!p) return;
	if (strlen(p) == 0) return;
	if (progStatus.sernbr_fname) {
		string haystack = p;
		if (haystack.find(newfilename) != string::npos) {
			int n = atoi(progStatus.sernbr.c_str());
			n++;
			char szn[10];
			snprintf(szn, sizeof(szn), "%d", n);
			progStatus.sernbr = szn;
			txt_sernbr->value(szn);
			txt_sernbr->redraw();
		}
	}

	const char *pext = fl_filename_ext(p);
	h213_def_filename = p;
	if (strlen(pext) == 0) h213_def_filename.append(HF213_EXT);

	remove_spaces_from_filename(h213_def_filename);
	h213_write(h213_def_filename);

	h213_using_template = false;
	show_filename(h213_def_filename);
}

void h213_cb_save()
{
	if (h213_base_filename == "new"HF213_EXT ||
		h213_base_filename == "default"HF213_EXT ||
		h213_using_template == true) {
		h213_cb_save_as();
		return;
	}
	h213_write(h213_def_filename);
	h213_using_template = false;
}

void h213_cb_html()
{
	string fname_name = fl_filename_name(h213_def_filename.c_str());
	size_t p = fname_name.rfind('.');
	if (p != string::npos) fname_name.erase(p);

	string hicsname = ICS_dir;
	hicsname.append(fname_name);
	hicsname.append(".html");

	string html_text = "";

	h213_update_fields();
	string form = hics213_html_template;

	for (int i = 0; i < h213_numfields; i++)
		replacestr( form, h213_fields[i].f_type, h213_fields[i].f_data );

	FILE *hicsfile = fopen(hicsname.c_str(), "w");
	fprintf(hicsfile,"%s", form.c_str());
	fclose(hicsfile);

	open_url(hicsname.c_str());
}

void h213_cb_textout()
{
	string hicsname = ICS_dir;
	hicsname.append("hics213.txt");

	h213_update_fields();
	string form = hics213_text_template;

	for (int i = 0; i < h213_numfields; i++)
		replacestr( form, h213_fields[i].f_type, h213_fields[i].f_data);

	FILE *hicsfile = fopen(hicsname.c_str(), "w");
	fprintf(hicsfile,"%s", form.c_str());
	fclose(hicsfile);

	open_url(hicsname.c_str());
}