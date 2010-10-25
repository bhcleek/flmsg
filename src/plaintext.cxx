// =====================================================================
//
// plaintext.cxx
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

// plaintext fields

const char * pt_title = "<tt:";
const char * pt_to = "<to:";
const char * pt_fm = "<fm:";
const char * pt_subj = "<sb:";
const char * pt_dt = "<dt:";
const char * pt_tm = "<tm:";
const char * pt_msg = "<mg:";

string ptbuffer;
string def_pt_filename = "";
string base_pt_filename = "";
string def_pt_TemplateName = "";

FIELD ptfields[] = {
{ pt_title,	"", (Fl_Widget **)&txt_pt_title,	't' },
{ pt_to,	"", (Fl_Widget **)&txt_pt_to,		't' },
{ pt_fm,	"", (Fl_Widget **)&txt_pt_fm,		't' },
{ pt_dt,	"", (Fl_Widget **)&txt_pt_date,		'd' },
{ pt_tm,	"", (Fl_Widget **)&txt_pt_time,		't' },
{ pt_subj,	"", (Fl_Widget **)&txt_pt_subj,		't' },
{ pt_msg,	"", (Fl_Widget **)&txt_pt_msg,		'e' } };

bool using_pt_template = false;

int num_ptfields = sizeof(ptfields) / sizeof(FIELD);

void cb_set_pt_date()
{
	txt_pt_date->value(szDate());
}

void cb_set_pt_time()
{
	txt_pt_time->value(szTime(progStatus.UTC));
}

void clear_ptfields()
{
	for (int i = 0; i < num_ptfields; i++)
		ptfields[i].f_data.clear();
}

void update_ptfields()
{
	for (int i = 0; i < num_ptfields; i++) {
		if (ptfields[i].w_type == 'd')
			ptfields[i].f_data = ((Fl_DateInput *)(*ptfields[i].w))->value();
		else if (ptfields[i].w_type == 't')
			ptfields[i].f_data = ((Fl_Input2 *)(*ptfields[i].w))->value();
		else if (ptfields[i].f_type == pt_msg) {
			char *txt = txt_pt_msg->buffer()->text();
			ptfields[i].f_data = txt;
			free(txt);
		}
	}
}

void clear_pt_form()
{
	clear_ptfields();
	ptfields[0].f_data = "General Message";
	txt_pt_title->value(ptfields[0].f_data.c_str());
	txt_pt_to->value("");
	txt_pt_fm->value("");
	txt_pt_subj->value("");
	txt_pt_date->value("");
	txt_pt_time->value("");
	txt_pt_msg->clear();
	update_ptfields();
}

void make_ptbuffer()
{
	char sznum[80];
	update_ptfields();
	ptbuffer.clear();
	ptbuffer.append("<flmsg>");
	ptbuffer.append(PACKAGE_VERSION);
	ptbuffer += '\n';
	ptbuffer.append("<plaintext>\n");
	for (int i = 0; i < num_ptfields; i++) {
		snprintf(sznum, sizeof(sznum), "%0d", (int)strlen(ptfields[i].f_data.c_str()));
		ptbuffer.append(ptfields[i].f_type);
		ptbuffer.append(sznum);
		ptbuffer += ' ';
		ptbuffer.append(ptfields[i].f_data);
		ptbuffer += '\n';
	}
}

void read_ptbuffer(string data)
{
	const char *buff, *p1, *p2, *buffend;
	size_t pos = 0;

	while ((pos = data.find('\r', pos)) != string::npos) data.erase(pos, 1);
	p1 = buff = data.c_str();
	buffend = p1 + data.length();
	clear_ptfields();

// search the file buffer for each of the ics fields
	for (int i = 0; i < num_ptfields; i++) {
		p1 = strstr(buff, ptfields[i].f_type);
		if (p1) {
			int nchars;
			p2 = p1 + strlen(ptfields[i].f_type);
			sscanf(p2, "%d", &nchars);
			if (nchars) {
				p2 = strchr(p2, ' ') + 1;
				if (p2 < buffend && p2 + nchars < buffend) {
					ptfields[i].f_data.clear();
					for ( int ch = 0; ch < nchars; ch++, p2++)
						ptfields[i].f_data += *p2;
				}
				if (ptfields[i].w_type == 'd')
					((Fl_DateInput *)(*ptfields[i].w))->value(ptfields[i].f_data.c_str());
				else if (ptfields[i].w_type == 't')
					((Fl_Input2 *)(*ptfields[i].w))->value(ptfields[i].f_data.c_str());
				else if (ptfields[i].f_type == pt_msg) {
					txt_pt_msg->clear();
					txt_pt_msg->addstr(ptfields[i].f_data.c_str());
				}
			}
		}
	}
}

void cb_pt_new()
{
	clear_pt_form();
	def_pt_filename = ICS_msg_dir;
	def_pt_filename.append("new"PTFILE_EXT);
	show_filename(def_pt_filename);
	using_pt_template = false;
}

void cb_pt_import()
{
	fl_alert2("Not implemented");
/*
	string def_pt_filename = ICS_dir;
	def_pt_filename.append("DEFAULT.XML");
	const char *p = FSEL::select(
		"Open Qptforms xml file",
		"Qptforms xml\t*.{xml,XML}",
		def_pt_filename.c_str());
	if (p){
		clear_pt_ptform();
		qform_pt_import(p);
	}
*/
}

void cb_pt_export()
{
	fl_alert2("Not implemented");
/*
	string def_pt_filename = ICS_dir;
	def_pt_filename.append(base_pt_filename);
	def_pt_filename.append(".XML");
	const char *p = FSEL::saveas(
			"Open Qptforms xml file",
			"Qptforms xml\t*.{xml,XML}",
			def_pt_filename.c_str());
	if (p) {
		const char *pext = fl_filename_ext(p);
		def_pt_filename = p;
		if (strlen(pext) == 0) def_pt_filename.append(".XML");
		qform_pt_export(def_pt_filename);
	}
*/
}

void cb_pt_wrap_import(string wrapfilename, string inpbuffer)
{
	clear_pt_form();
	read_ptbuffer(inpbuffer);
	def_pt_filename = ICS_msg_dir;
	def_pt_filename.append(wrapfilename);
	show_filename(def_pt_filename);
	using_pt_template = false;
}

void cb_pt_wrap_export()
{
	if (base_pt_filename == "new"PTFILE_EXT || base_pt_filename == "default"PTFILE_EXT)
		cb_pt_save_as();

	string wrapfilename = WRAP_send_dir;
	wrapfilename.append(base_pt_filename);
	wrapfilename.append(WRAP_EXT);
	const char *p = FSEL::saveas(
			"Save as wrap file",
			"Wrap file\t*.{wrap,WRAP}",
			wrapfilename.c_str());
	if (p) {
		string pext = fl_filename_ext(p);
		wrapfilename = p;
		make_ptbuffer();
		export_wrapfile(base_pt_filename, wrapfilename, ptbuffer, pext != WRAP_EXT);
	}
}

void cb_pt_wrap_autosend()
{
	if (base_pt_filename == "new"PTFILE_EXT || 
		base_pt_filename == "default"PTFILE_EXT ||
		using_pt_template == true)
		cb_pt_save_as();

	string wrapfilename = WRAP_auto_dir;
	wrapfilename.append("wrap_auto_file");
	make_ptbuffer();
	export_wrapfile(base_pt_filename, wrapfilename, ptbuffer, false);
}

void cb_pt_load_template()
{
	string def_pt_filename = def_pt_TemplateName;
	const char *p = FSEL::select(
			"Open template file",
			"Template file\t*"PTTEMP_EXT,
			def_pt_filename.c_str());
	if (p) {
		clear_pt_form();
		read_data_file(p);
		def_pt_TemplateName = p;
		show_filename(def_pt_TemplateName);
		using_pt_template = true;
	}
}

void cb_pt_save_template()
{
	if (!using_pt_template) {
		cb_pt_save_as_template();
		return;
	}
	string def_pt_filename = def_pt_TemplateName;
	const char *p = FSEL::saveas(
			"Save template file",
			"Template file\t*"PTTEMP_EXT,
			def_pt_filename.c_str());
	if (p)
		write_pt(p);
}

void cb_pt_save_as_template()
{
	string def_pt_filename = def_pt_TemplateName;
	const char *p = FSEL::saveas(
			"Save as template file",
			"Template file\t*"PTTEMP_EXT,
			def_pt_filename.c_str());
	if (p) {
		const char *pext = fl_filename_ext(p);
		def_pt_TemplateName = p;
		if (strlen(pext) == 0) def_pt_TemplateName.append(PTTEMP_EXT);
		remove_spaces_from_filename(def_pt_TemplateName);
		write_pt(def_pt_TemplateName);
		show_filename(def_pt_TemplateName);
		using_pt_template = true;
	}
}

void cb_pt_open()
{
	const char *p = FSEL::select(_("Open data file"), "p2s\t*.p2s",
					def_pt_filename.c_str());
	if (!p) return;
	if (strlen(p) == 0) return;
	clear_pt_form();
	read_data_file(p);
	using_pt_template = false;
	def_pt_filename = p;
	show_filename(def_pt_filename);
}

void write_pt(string s)
{
	FILE *ptfile = fopen(s.c_str(), "w");
	if (!ptfile) return;
	make_ptbuffer();
	fwrite(ptbuffer.c_str(), ptbuffer.length(), 1, ptfile);
	fclose(ptfile);
}

void cb_pt_save_as()
{
	const char *p;
	string newfilename;

	string name = named_file();
	if (!name.empty()) {
		name.append(".p2s");
		newfilename = ICS_msg_dir;
		newfilename.append(name);
	} else
		newfilename = def_pt_filename;

	p = FSEL::saveas(_("Save data file"), "p2s\t*.p2s",
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
	def_pt_filename = p;
	if (strlen(pext) == 0) def_pt_filename.append(".p2s");

	remove_spaces_from_filename(def_pt_filename);
	write_pt(def_pt_filename);

	using_pt_template = false;
	show_filename(def_pt_filename);
}

void cb_pt_save()
{
	if (base_pt_filename == "new.p2s" || 
		base_pt_filename == "default.p2s" ||
		using_pt_template == true) {
		cb_pt_save_as();
		return;
	}
	write_pt(def_pt_filename);
	using_pt_template = false;
}

void cb_pt_html()
{
	string pt_name = ICS_dir;
	string html_text = "";
	pt_name.append("plaintext_doc.html");

	update_ptfields();
	string ptform = pt_html_template;

	string pt_msgtxt = ptfields[num_ptfields-1].f_data;

	int nlines = 0;
	size_t pos = pt_msgtxt.find('\n');
	while (pos != string::npos) {
		pt_msgtxt.replace(pos, 1, "<br>");
		nlines++;
		pos = pt_msgtxt.find( '\n', pos );
	}
	for (int i = nlines; i < 20; i++) pt_msgtxt.append("<br>");
	to_html(pt_msgtxt);

	for (int i = 0; i < num_ptfields - 1; i++) {
		pos = ptform.find(ptfields[i].f_type);
		if (pos != string::npos) {
			html_text = ptfields[i].f_data;
			to_html(html_text);
			ptform.replace( pos, strlen(ptfields[i].f_type), html_text);
		}
	}
	pos = ptform.find(ptfields[num_ptfields-1].f_type);
	if (pos)
		ptform.replace(	pos,
						strlen(ptfields[num_ptfields-1].f_type),
						pt_msgtxt);

	FILE *ptfile = fopen(pt_name.c_str(), "w");
	fprintf(ptfile,"%s", ptform.c_str());
	fclose(ptfile);

	open_url(pt_name.c_str());
}

void cb_pt_msg_type()
{
	if (tabs_msg_type->value() == tab_plaintext ) {
		show_filename(def_pt_filename);
	} else {
		show_filename(def_rg_filename);
	}
}

void cb_pt_textout()
{
	string pt_name = ICS_dir;
	pt_name.append("plaintext.txt");

	update_ptfields();
	string ptform = pt_txt_template;

	size_t pos;
	for (int i = 0; i < num_ptfields; i++) {
		pos = ptform.find(ptfields[i].f_type);
		if (pos != string::npos)
			ptform.replace(	pos,
							strlen(ptfields[i].f_type),
							ptfields[i].f_data );
	}
	FILE *ptfile = fopen(pt_name.c_str(), "w");
	fprintf(ptfile,"%s", ptform.c_str());
	fclose(ptfile);

	open_url(pt_name.c_str());
}
