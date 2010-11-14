// =====================================================================
//
// ics214.cxx
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

// ---------------------------------------------------------------------
// ics 214 field variables and template variables
// ---------------------------------------------------------------------

string ics214_incident					= ":inc:";
string ics214_date						= ":dat:";
string ics214_time						= ":tim:";
string ics214_op_period					= ":opp:";
string ics214_unit_name					= ":und:";
string ics214_unit_leader				= ":unl:";

string ics214_roster_name				= ":nam[n]:"; // 14
string ics214_roster_position			= ":pos[n]:";
string ics214_roster_home_base			= ":hom[n]:";

string ics214_activity_time				= ":at[n]:"; // 16
string ics214_activity_event			= ":ev[n]:";

string ics214_prepared_by				= ":pre:";

string s214_incident;
string s214_date;
string s214_time;
string s214_op_period;
string s214_unit_name;
string s214_unit_leader;

string s214_roster_name[16];
string s214_roster_position[16];
string s214_roster_home_base[16];
string s214_activity_time[16];
string s214_activity_event[16];

string s214_prepared_by;

// =====================================================================

string buff214;
string def_214_filename = "";
string base_214_filename = "";
string def_214_TemplateName = "";
bool using_ics214_template = false;

void cb_214_set_date()
{
	txt_214_date->value(szDate());
}

void cb_214_set_time()
{
	txt_214_time->value(szTime());
}

void clear_214fields()
{
	s214_incident.clear();
	s214_date.clear();
	s214_time.clear();
	s214_op_period.clear();
	s214_unit_name.clear();
	s214_unit_leader.clear();
	s214_prepared_by.clear();

	for (int i = 0; i < 16; i++) {
		s214_roster_name[i].clear();
		s214_roster_position[i].clear();
		s214_roster_home_base[i].clear();
		s214_activity_time[i].clear();
		s214_activity_event[i].clear();
	}
}

void update_214fields()
{
	s214_incident = txt_214_incident->value();
	s214_date = txt_214_date->value();
	s214_time = txt_214_time->value();
	s214_op_period = txt_214_op_period->value();
	s214_unit_name = txt_214_unit_name->value();
	s214_unit_leader = txt_214_unit_leader->value();
	s214_prepared_by = txt_214_prepared_by->value();

	for (int i = 0; i < 16; i++) {
		s214_roster_name[i] = txt_214_roster_name[i]->value();
		s214_roster_position[i] = txt_214_roster_position[i]->value();
		s214_roster_home_base[i] = txt_214_roster_home_base[i]->value();
		s214_activity_time[i] = txt_214_activity_time[i]->value();
		s214_activity_event[i] = txt_214_activity_event[i]->value();
	}
}

void update_214form()
{
	txt_214_incident->value(s214_incident.c_str());
	txt_214_date->value(s214_date.c_str());
	txt_214_time->value(s214_time.c_str());
	txt_214_op_period->value(s214_op_period.c_str());
	txt_214_unit_name->value(s214_unit_name.c_str());
	txt_214_unit_leader->value(s214_unit_leader.c_str());
	txt_214_prepared_by->value(s214_prepared_by.c_str());

	for (int i = 0; i < 16; i++) {
		txt_214_roster_name[i]->value(s214_roster_name[i].c_str());
		txt_214_roster_position[i]->value(s214_roster_position[i].c_str());
		txt_214_roster_home_base[i]->value(s214_roster_home_base[i].c_str());
		txt_214_activity_time[i]->value(s214_activity_time[i].c_str());
		txt_214_activity_event[i]->value(s214_activity_event[i].c_str());
	}
}

void clear_214_form()
{
	clear_214fields();
	update_214form();
}

string &ics_nn(string & subst, int n)
{
	static string garbage = "#$^*!";
	static string ics;
	ics.clear();
	ics = subst;
	size_t pos = ics.find("[");
	if (pos == string::npos) return garbage;
	pos++;
	if (n < 10)
		ics[pos] = '0' + n;
	else {
		ics[pos] = '1';
		ics[pos+1] = '0' + n % 10;
		ics[pos+2] = ']';
		ics += ':';
	}
	return ics;
}

void make_buff214()
{
	update_214fields();
	buff214.clear();

	buff214 = header("<ics214>");

	buff214.append( lineout( ics214_incident, s214_incident ) );
	buff214.append( lineout( ics214_date, s214_date ) );
	buff214.append( lineout( ics214_time, s214_time ) );
	buff214.append( lineout( ics214_op_period, s214_op_period ) );
	buff214.append( lineout( ics214_unit_name, s214_unit_name) );
	buff214.append( lineout( ics214_unit_leader, s214_unit_leader) );

	buff214.append( lineout( ics214_prepared_by, s214_prepared_by ) );

	for (int i = 0; i < 16; i++) {
		buff214.append( lineout( ics_nn( ics214_roster_name, i ), s214_roster_name[i] ) );
		buff214.append( lineout( ics_nn( ics214_roster_position, i ), s214_roster_position[i] ) );
		buff214.append( lineout( ics_nn( ics214_roster_home_base, i ), s214_roster_home_base[i] ) );
		buff214.append( lineout( ics_nn( ics214_activity_time, i ), s214_activity_time[i] ) );
		buff214.append( lineout( ics_nn( ics214_activity_event, i ), s214_activity_event[i] ) );
	}
}

void read_214_buffer(string data)
{
	clear_214fields();

	s214_incident = findstr(data, ics214_incident);
	s214_date = findstr(data, ics214_date);
	s214_time = findstr(data, ics214_time);
	s214_op_period = findstr(data, ics214_op_period);
	s214_unit_name = findstr(data, ics214_unit_name);
	s214_unit_leader = findstr(data, ics214_unit_leader);
	s214_prepared_by = findstr(data, ics214_prepared_by);

	for (int i = 0; i < 16; i++) {
		s214_roster_name[i]      = findstr(data, ics_nn( ics214_roster_name, i ) );
		s214_roster_position[i]  = findstr(data, ics_nn( ics214_roster_position, i ) );
		s214_roster_home_base[i] = findstr(data, ics_nn( ics214_roster_home_base, i ) );
		s214_activity_time[i]    = findstr(data, ics_nn( ics214_activity_time, i ) );
		s214_activity_event[i]   = findstr(data, ics_nn( ics214_activity_event, i ) );
	}

	update_214form();
}

void cb_214_new()
{
	clear_214_form();
	def_214_filename = ICS_msg_dir;
	def_214_filename.append("new"F214_EXT);
	show_filename(def_214_filename);
	using_ics214_template = false;
}

void cb_214_import()
{
	fl_alert2("Not implemented");
}

void cb_214_export()
{
	fl_alert2("Not implemented");
}

void cb_214_wrap_import(string wrapfilename, string inpbuffer)
{
	clear_214_form();
	read_214_buffer(inpbuffer);
	def_214_filename = ICS_msg_dir;
	def_214_filename.append(wrapfilename);
	show_filename(def_214_filename);
	using_ics214_template = false;
}

void cb_214_wrap_export()
{
	if (base_214_filename == "new"F214_EXT || base_214_filename == "default"F214_EXT)
		cb_214_save_as();

	string wrapfilename = WRAP_send_dir;
	wrapfilename.append(base_214_filename);
	wrapfilename.append(".wrap");
	const char *p = FSEL::saveas(
			"Save as wrap file",
			"Wrap file\t*.{wrap,WRAP}",
			wrapfilename.c_str());
	if (p) {
		string pext = fl_filename_ext(p);
		wrapfilename = p;
		make_buff214();
		export_wrapfile(base_214_filename, wrapfilename, buff214, pext != ".wrap");
	}
}

void cb_214_wrap_autosend()
{
	if (base_214_filename == "new"F214_EXT || 
		base_214_filename == "default"F214_EXT ||
		using_ics214_template == true)
		cb_214_save_as();

	string wrapfilename = WRAP_auto_dir;
	wrapfilename.append("wrap_auto_file");
	make_buff214();
	export_wrapfile(base_214_filename, wrapfilename, buff214, false);
}

void cb_214_load_template()
{
	string def_214_filename = def_214_TemplateName;
	const char *p = FSEL::select(
			"Open template file",
			"Template file\t*"T214_EXT,
			def_214_filename.c_str());
	if (p) {
		clear_214_form();
		read_data_file(p);
		def_214_TemplateName = p;
		show_filename(def_214_TemplateName);
		using_ics214_template = true;
	}
}

void cb_214_save_template()
{
	if (!using_ics214_template) {
		cb_214_save_as_template();
		return;
	}
	string def_214_filename = def_214_TemplateName;
	const char *p = FSEL::saveas(
			"Save template file",
			"Template file\t*"T214_EXT,
			def_214_filename.c_str());
	if (p)
		write_214(p);
}

void cb_214_save_as_template()
{
	string def_214_filename = def_214_TemplateName;
	const char *p = FSEL::saveas(
			"Save as template file",
			"Template file\t*"T214_EXT,
			def_214_filename.c_str());
	if (p) {
		const char *pext = fl_filename_ext(p);
		def_214_TemplateName = p;
		if (strlen(pext) == 0) def_214_TemplateName.append(T214_EXT);
		remove_spaces_from_filename(def_214_TemplateName);
		write_214(def_214_TemplateName);
		show_filename(def_214_TemplateName);
		using_ics214_template = true;
	}
}

void cb_214_open()
{
	const char *p = FSEL::select(_("Open data file"), "ICS-214\t*"F214_EXT,
					def_214_filename.c_str());
	if (!p) return;
	if (strlen(p) == 0) return;
	clear_214_form();
	read_data_file(p);
	using_ics214_template = false;
	def_214_filename = p;
	show_filename(def_214_filename);
}

void write_214(string s)
{
	FILE *file214 = fopen(s.c_str(), "w");
	if (!file214) return;
	make_buff214();
	fwrite(buff214.c_str(), buff214.length(), 1, file214);
	fclose(file214);
}

void cb_214_save_as()
{
	const char *p;
	string newfilename;

	string name = named_file();
	if (!name.empty()) {
		name.append(F214_EXT);
		newfilename = ICS_msg_dir;
		newfilename.append(name);
	} else
		newfilename = def_214_filename;

	p = FSEL::saveas(_("Save data file"), "ICS-214\t*"F214_EXT,
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
	def_214_filename = p;
	if (strlen(pext) == 0) def_214_filename.append(F214_EXT);

	remove_spaces_from_filename(def_214_filename);
	write_214(def_214_filename);

	using_ics214_template = false;
	show_filename(def_214_filename);
}

void cb_214_save()
{
	if (base_214_filename == "new"F214_EXT || 
		base_214_filename == "default"F214_EXT ||
		using_ics214_template == true) {
		cb_214_save_as();
		return;
	}
	write_214(def_214_filename);
	using_ics214_template = false;
}

void cb_214_html()
{
	string ics214_fname = ICS_dir;
	string html_text = "";
	ics214_fname.append("ics214_doc.html");

	update_214fields();
	string form214 = ics214_html_template;

	replacestr(form214, ics214_incident, s214_incident );
	replacestr(form214, ics214_date, s214_date );
	replacestr(form214, ics214_time, s214_time );
	replacestr(form214, ics214_op_period, s214_op_period );
	replacestr(form214, ics214_unit_name, s214_unit_name );
	replacestr(form214, ics214_unit_leader, s214_unit_leader );
	replacestr(form214, ics214_prepared_by, s214_prepared_by );

	for (int i = 0; i < 16; i++) {
		replacestr(form214, ics_nn( ics214_roster_name, i ), s214_roster_name[i] );
		replacestr(form214, ics_nn( ics214_roster_position, i ), s214_roster_position[i] );
		replacestr(form214, ics_nn( ics214_roster_home_base, i ), s214_roster_home_base[i] );
		replacestr(form214, ics_nn( ics214_activity_time, i ), s214_activity_time[i] );
		replacestr(form214, ics_nn( ics214_activity_event, i ), s214_activity_event[i] );
	}

	FILE *file214 = fopen(ics214_fname.c_str(), "w");
	fprintf(file214,"%s", form214.c_str());
	fclose(file214);

	open_url(ics214_fname.c_str());
}

void cb_214_msg_type()
{
	if (tabs_msg_type->value() == tab_ics214 ) {
		tab_ics214_type->value(tab_214_1);
		show_filename(def_214_filename);
	}
}

void cb_214_textout()
{
	string ics214_fname = ICS_dir;
	ics214_fname.append("ics214.txt");

	update_214fields();
	string form214 = ics214_text_template;

	replacestr(form214, ics214_incident, s214_incident );
	replacestr(form214, ics214_date, s214_date );
	replacestr(form214, ics214_time, s214_time );
	replacestr(form214, ics214_op_period, s214_op_period );
	replacestr(form214, ics214_unit_name, s214_unit_name );
	replacestr(form214, ics214_unit_leader, s214_unit_leader );
	replacestr(form214, ics214_prepared_by, s214_prepared_by );

	for (int i = 0; i < 16; i++) {
		replacestr(form214, ics_nn( ics214_roster_name, i ), s214_roster_name[i] );
		replacestr(form214, ics_nn( ics214_roster_position, i ), s214_roster_position[i] );
		replacestr(form214, ics_nn( ics214_roster_home_base, i ), s214_roster_home_base[i] );
		replacestr(form214, ics_nn( ics214_activity_time, i ), s214_activity_time[i] );
		replacestr(form214, ics_nn( ics214_activity_event, i ), s214_activity_event[i] );
	}

	FILE *file214 = fopen(ics214_fname.c_str(), "w");
	fprintf(file214,"%s", form214.c_str());
	fclose(file214);

	open_url(ics214_fname.c_str());
}
