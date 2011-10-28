// =====================================================================
//
// flmsg.h
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

#ifndef FLMSG_H
#define FLMSG_H

#include <string>
#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>

#include "arl_msgs.h"
#include "hx_msgs.h"

using namespace std;

enum MSGTYPE { NONE,
ICS203, ICS205, ICS205A, ICS206, ICS213, ICS214, ICS216,
HICS203, HICS206, HICS213, HICS214,
RADIOGRAM, PLAINTEXT, BLANK,
MARSDAILY, MARSINEEI, MARSNET, MARSARMY, MARSNAVY, REDXSNW };

struct FIELD { string f_type; string f_data; void **w; char w_type; };
extern FIELD fields[];
extern FIELD ptfields[];
extern FIELD rgfields[];

extern void checkdirectories(void);
extern int parse_args(int argc, char **argv, int& idx);
extern void showoptions();

extern Fl_Double_Window *mainwindow;
extern Fl_Double_Window *optionswindow;
extern Fl_Double_Window *arlwindow;
extern Fl_Double_Window *config_files_window;
extern Fl_Double_Window *hxwindow;
extern string flmsgHomeDir;
extern string IcsHomeDir;

extern bool printme;

extern int arl_nbr;

extern string NBEMS_dir;
extern string ARQ_dir;
extern string ARQ_files_dir;
extern string ARQ_recv_dir;
extern string ARQ_send;
extern string WRAP_dir;
extern string WRAP_recv_dir;
extern string WRAP_send_dir;
extern string WRAP_auto_dir;
extern string ICS_dir;
extern string ICS_msg_dir;
extern string ICS_tmp_dir;


extern string title;
extern string buffer;

extern void cb_msg_type();

extern char *named_file();

//menu callbacks
extern void cb_new();
extern void cb_open();
extern void cb_save();
extern void cb_save_as();
extern void cb_text();
extern void cb_import();
extern void cb_export();
extern void cb_wrap_import();
extern void cb_wrap_export();
extern void cb_wrap_autosend();
extern void cb_exit();
extern void cb_load_template();
extern void cb_save_template();
extern void cb_save_as_template();
extern void cb_config_files();
extern void cb_config_date_time();
extern void cb_config_radiogram();
extern void showoptions();
extern void show_help();
extern void cb_About();
extern void cb_html();
extern void cb_html_fcopy();
extern void cb_folders();

extern void open_url(const char* url);

extern void cb_arl();
extern void cb_arl_cancel();
extern void cb_arl_add();

extern void cb_hx();
extern void cb_hx_select();
extern void cb_hx_select_add();
extern void cb_hx_select_cancel();
extern void cb_hx_select_ok();

extern void closeoptions();

extern void remove_spaces_from_filename(string &fname);
extern char *szTime(int typ = 0);
extern char *szDate();
extern char *szAbbrevDate();
extern char *szDateTime();
extern char *szMarsDateTime();

extern void set_main_label();
extern void show_filename(string);
extern void clear_fields();
extern void update_fields();

extern void to_html(string &s);
extern void fm_html(string &html);

extern void drop_box_changed();

// used by all form management

extern string lineout( string &, string & );
extern string binout( string &, bool & );
extern string header( const char * );
extern string findstr(string &, string &);
extern bool   findbin(string &, string &);
extern void   replacestr(string &form, string &where, string &what);
extern void   replacelf(string &form, int n = 0);

// ics205
extern string base_205_filename;
extern string def_205_filename;
extern string def_205_TemplateName;
extern bool using_ics205_template;

extern void cb_205_SetDateTime1();
extern void cb_205_SetDateTime2();
extern void clear_205fields();
extern void update_205fields();
extern void clear_205_form();
extern void make_buff205();
extern string find(string haystack, string needle);
extern void read_205_buffer(string data);
extern void cb_205_new();
extern void cb_205_import();
extern void cb_205_export();
extern void cb_205_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_205_wrap_export();
extern void cb_205_wrap_autosend();
extern void cb_205_load_template();
extern void cb_205_save_template();
extern void cb_205_save_as_template();
extern void cb_205_open();
extern void write_205(string s);
extern void cb_205_save_as();
extern void cb_205_save();
extern void cb_205_html();
extern void cb_205_msg_type();
extern void cb_205_textout();

// ics205a
extern string base_205a_filename;
extern string def_205a_filename;
extern string def_205a_TemplateName;
extern bool using_ics205a_template;

extern void cb_205a_set_date_fm();
extern void cb_205a_set_time_fm();
extern void cb_205a_set_date_to();
extern void cb_205a_set_time_to();
extern void clear_205afields();
extern void update_205afields();
extern void update_205aform();
extern void clear_205a_form();
extern void make_buff205a();
extern void read_205a_buffer(string data);
extern void cb_205a_new();
extern void cb_205a_import();
extern void cb_205a_export();
extern void cb_205a_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_205a_wrap_export();
extern void cb_205a_wrap_autosend();
extern void cb_205a_load_template();
extern void cb_205a_save_template();
extern void cb_205a_save_as_template();
extern void cb_205a_open();
extern void write_205a(string s);
extern void cb_205a_save_as();
extern void cb_205a_save();
extern void cb_205a_html();
extern void cb_205a_msg_type();
extern void cb_205a_textout();

// ics203
extern string yes;
extern string no;

extern string buff203;
extern string def_203_filename;
extern string base_203_filename;
extern string def_203_TemplateName;
extern bool  using_203_template;

extern void cb_203_set_date();
extern void cb_203_set_time();
extern void clear_203fields();
extern void update_203fields();
extern void clear_203_form();
extern void make_buff203();
extern void read_203_buffer(string data);
extern void cb_203_new();
extern void cb_203_import();
extern void cb_203_export();
extern void cb_203_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_203_wrap_export();
extern void cb_203_wrap_autosend();
extern void cb_203_load_template();
extern void cb_203_save_template();
extern void cb_203_save_as_template();
extern void cb_203_open();
extern void write_203(string s);
extern void cb_203_save_as();
extern void cb_203_save();
extern void cb_203_html();
extern void cb_203_msg_type();
extern void cb_203_textout();

// ics206
extern string yes;
extern string no;

extern string buff206;
extern string def_206_filename;
extern string base_206_filename;
extern string def_206_TemplateName;
extern bool using_ics206_template;

extern void cb_206_setdate();
extern void cb_206_settime();
extern void clear_206fields();
extern void update_206fields();
extern void clear_206_form();
extern void make_buff206();
extern void read_206_buffer(string data);
extern void cb_206_new();
extern void cb_206_import();
extern void cb_206_export();
extern void cb_206_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_206_wrap_export();
extern void cb_206_wrap_autosend();
extern void cb_206_load_template();
extern void cb_206_save_template();
extern void cb_206_save_as_template();
extern void cb_206_open();
extern void write_206(string s);
extern void cb_206_save_as();
extern void cb_206_save();
extern void cb_206_html();
extern void cb_206_msg_type();
extern void cb_206_textout();

// ics213
extern bool using_213Template;
extern string base_213_filename;
extern string def_213_filename;
extern string def_213_TemplateName;

extern void clear_213_form();
extern void read_213(string);
extern void write_213(string);
extern void read_213_buffer(string);

extern void cb_213_new();
extern void cb_213_open();
extern void cb_213_save();
extern void cb_213_save_as();
extern void cb_213_write();
extern void cb_213_html();
extern void cb_213_textout();
extern void cb_213_import();
extern void cb_213_export();
extern void cb_213_wrap_import(string, string);
extern void cb_213_wrap_export();
extern void cb_213_wrap_autosend();
extern void cb_213_load_template();
extern void cb_213_save_template();
extern void cb_213_save_as_template();
extern void cb_SetDate1();
extern void cb_SetDate2();
extern void cb_SetTime1();
extern void cb_SetTime2();

// ics214

extern string buff214;
extern string def_214_filename;
extern string base_214_filename;
extern string def_214_TemplateName;
extern bool using_ics214_template;

extern void cb_214_set_date();
extern void cb_214_set_time();
extern void clear_214fields();
extern void update_214fields();
extern void clear_214_form();
extern void make_buff214();
extern void read_214_buffer(string data);
extern void cb_214_new();
extern void cb_214_import();
extern void cb_214_export();
extern void cb_214_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_214_wrap_export();
extern void cb_214_wrap_autosend();
extern void cb_214_load_template();
extern void cb_214_save_template();
extern void cb_214_save_as_template();
extern void cb_214_open();
extern void write_214(string s);
extern void cb_214_save_as();
extern void cb_214_save();
extern void cb_214_html();
extern void cb_214_msg_type();
extern void cb_214_textout();

// ics216

extern string buff216;
extern string def_216_filename;
extern string base_216_filename;
extern string def_216_TemplateName;
extern bool using_ics216_template;

extern void cb_216_set_date();
extern void cb_216_set_time();
extern void clear_216fields();
extern void update_216fields();
extern void clear_216_form();
extern void make_buff216();
extern void read_216_buffer(string data);
extern void cb_216_new();
extern void cb_216_import();
extern void cb_216_export();
extern void cb_216_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_216_wrap_export();
extern void cb_216_wrap_autosend();
extern void cb_216_load_template();
extern void cb_216_save_template();
extern void cb_216_save_as_template();
extern void cb_216_open();
extern void write_216(string s);
extern void cb_216_save_as();
extern void cb_216_save();
extern void cb_216_html();
extern void cb_216_msg_type();
extern void cb_216_textout();

// radiogram
extern bool using_rg_template;
extern string base_rg_filename;
extern string def_rg_filename;
extern string def_rg_TemplateName;

extern const char hxitems[];
extern const char precitems[];
extern const char *s_prec[];
extern const char *s_hx[];

extern void cb_rgSetDate1();
extern void cb_rgSetTime1();
extern void cb_rgSetDateTime2();
extern void cb_rgSetDateTime3();
extern void cb_rgSetDateTime4();
extern void cb_rgSetDateTime5();
extern void clear_rgfields();
extern void update_rgfields();
extern void clear_rg_form();
extern void make_rg_buffer();
extern void read_rg_buffer(string data);
extern void cb_rg_new();
extern void cb_rg_import();
extern void cb_rg_export();
extern void cb_rg_wrap_import(string, string);
extern void cb_rg_wrap_export();
extern void cb_rg_wrap_autosend();
extern void cb_rg_load_template();
extern void cb_rg_save_template();
extern void cb_rg_save_as_template();
extern void read_rg(string s);
extern void cb_rg_open();
extern void write_rg(string s);
extern void cb_rg_save_as();
extern void cb_rg_save();
extern void cb_rg_html();
extern void cb_rg_html_fcopy();
extern void cb_rg_rtf();
extern void cb_rg_textout();
extern void set_rg_choices();
extern void cb_rg_check();
extern void cb_rg_nbr(Fl_Widget *);
extern void cb_rg_filter_input(Fl_Widget *);

extern void read_data_file(string);

// plaintext
extern bool using_pt_template;
extern string base_pt_filename;
extern string def_pt_filename;
extern string def_pt_TemplateName;

extern void cb_set_pt_date();
extern void cb_set_pt_time();
extern void clear_ptfields();
extern void update_ptfields();
extern void clear_pt_form();
extern void make_ptbuffer();
extern void read_ptbuffer(string data);
extern void cb_pt_new();
extern void cb_pt_import();
extern void cb_pt_export();
extern void cb_pt_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_pt_wrap_export();
extern void cb_pt_wrap_autosend();
extern void cb_pt_load_template();
extern void cb_pt_save_template();
extern void cb_pt_save_as_template();
extern void read_pt_data_file(string s);
extern void cb_pt_open();
extern void write_pt(string s);
extern void cb_pt_save_as();
extern void cb_pt_save();
extern void cb_pt_html();
extern void cb_pt_msg_type();
extern void cb_pt_textout();

// blank form
extern bool using_blank_template;
extern string base_blank_filename;
extern string def_blank_filename;
extern string def_blank_TemplateName;

extern string TITLE;
extern string errtext;

extern void clear_blankfields();
extern void update_blankfields();
extern void clear_blank_form();
extern void make_blankbuffer();
extern void read_blankbuffer(string data);
extern void cb_blank_new();
extern void cb_blank_import();
extern void cb_blank_export();
extern void cb_blank_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_blank_wrap_export();
extern void cb_blank_wrap_autosend();
extern void cb_blank_load_template();
extern void cb_blank_save_template();
extern void cb_blank_save_as_template();
extern void read_blank_data_file(string s);
extern void cb_blank_open();
extern void write_blank(string s);
extern void cb_blank_save_as();
extern void cb_blank_save();
extern void cb_blank_html();
extern void cb_blank_msg_type();
extern void cb_blank_textout();

extern void print_and_exit();

// mars daily
extern string	def_mars_daily_filename;
extern string	def_mars_daily_TemplateName;
extern string	base_mars_daily_filename;

extern void clear_mars_dailyfields();
extern void update_mars_dailyfields();
extern void clear_mars_daily_form();
extern void make_mars_daily_buffer();
extern void read_mars_daily_buffer(string data);
extern void cb_mars_daily_new();
extern void cb_mars_daily_import();
extern void cb_mars_daily_export();
extern void cb_mars_daily_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_mars_daily_wrap_export();
extern void cb_mars_daily_wrap_autosend();
extern void cb_mars_daily_load_template();
extern void cb_mars_daily_save_template();
extern void cb_mars_daily_save_as_template();
extern void read_mars_daily__data_file(string s);
extern void cb_mars_daily_open();
extern void write_mars_daily(string s);
extern void cb_mars_daily_save_as();
extern void cb_mars_daily_save();
extern void cb_mars_daily_html();
extern void cb_mars_daily_msg_type();
extern void cb_mars_daily_textout();

// mars ineei
extern string	def_mars_ineei_filename;
extern string	def_mars_ineei_TemplateName;
extern string	base_mars_ineei_filename;

extern void cb_mars_ineei_SetDTG();
extern void clear_mars_ineei_fields();
extern void update_mars_ineei_fields();
extern void update_mars_ineeiform();
extern void clear_mars_ineei_form();
extern void make_mars_ineei_buff();
extern void read_mars_ineei_buffer(string data);
extern void cb_mars_ineei_new();
extern void cb_mars_ineei_import();
extern void cb_mars_ineei_export();
extern void cb_mars_ineei_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_mars_ineei_wrap_export();
extern void cb_mars_ineei_wrap_autosend();
extern void cb_mars_ineei_load_template();
extern void cb_mars_ineei_save_template();
extern void cb_mars_ineei_save_as_template();
extern void cb_mars_ineei_open();
extern void write_mars_ineei(string s);
extern void cb_mars_ineei_save_as();
extern void cb_mars_ineei_save();
extern void cb_mars_ineei_html();
extern void cb_mars_ineei_textout();
extern void cb_mars_ineei_html();
extern void cb_mars_ineei_textout();

// mars net
extern string	def_mars_net_filename;
extern string	def_mars_net_TemplateName;
extern string	base_mars_net_filename;

extern void cb_mars_net_SetDTG();
extern void cb_mars_net_SetDTGSTART();
extern void cb_mars_net_SetDTGEND();
extern void clear_mars_net_fields();
extern void update_mars_net_fields();
extern void update_mars_netform();
extern void clear_mars_net_form();
extern void make_mars_buffnet();
extern void read_mars_net_buffer(string data);
extern void cb_mars_net_new();
extern void cb_mars_net_import();
extern void cb_mars_net_export();
extern void cb_mars_net_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_mars_net_wrap_export();
extern void cb_mars_net_wrap_autosend();
extern void cb_mars_net_load_template();
extern void cb_mars_net_save_template();
extern void cb_mars_net_save_as_template();
extern void cb_mars_net_open();
extern void write_mars_net(string s);
extern void cb_mars_net_save_as();
extern void cb_mars_net_save();
extern void cb_mars_net_html();
extern void cb_mars_net_textout();

// mars army
extern bool using_mars_army_template;
extern string base_mars_army_filename;
extern string def_mars_army_filename;
extern string def_mars_army_TemplateName;

extern void clear_mars_armyfields();
extern void update_mars_armyfields();
extern void update_mars_armyform();
extern void clear_mars_army_form();
extern void make_buffmars_army();
extern void read_mars_army_buffer(string data);
extern void cb_mars_army_new();
extern void cb_mars_army_import();
extern void cb_mars_army_export();
extern void cb_mars_army_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_mars_army_wrap_export();
extern void cb_mars_army_wrap_autosend();
extern void cb_mars_army_load_template();
extern void cb_mars_army_save_template();
extern void cb_mars_army_save_as_template();
extern void cb_mars_army_open();
extern void write_mars_army(string s);
extern void cb_mars_army_save_as();
extern void cb_mars_army_save();
extern void cb_mars_army_html();
extern void cb_mars_army_msg_type();
extern void cb_mars_army_textout();

// mars navy
extern bool using_mars_navy_template;
extern string base_mars_navy_filename;
extern string def_mars_navy_filename;
extern string def_mars_navy_TemplateName;

extern void clear_mars_navyfields();
extern void update_mars_navyfields();
extern void update_mars_navyform();
extern void clear_mars_navy_form();
extern void make_buffmars_navy();
extern void read_mars_navy_buffer(string data);
extern void cb_mars_navy_new();
extern void cb_mars_navy_import();
extern void cb_mars_navy_export();
extern void cb_mars_navy_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_mars_navy_wrap_export();
extern void cb_mars_navy_wrap_autosend();
extern void cb_mars_navy_load_template();
extern void cb_mars_navy_save_template();
extern void cb_mars_navy_save_as_template();
extern void cb_mars_navy_open();
extern void write_mars_navy(string s);
extern void cb_mars_navy_save_as();
extern void cb_mars_navy_save();
extern void cb_mars_navy_html();
extern void cb_mars_navy_msg_type();
extern void cb_mars_navy_textout();

// Red Cross

extern bool using_redx_snw_template;
extern string base_redx_snw_filename;
extern string def_redx_snw_filename;
extern string def_redx_snw_TemplateName;

extern void clear_redx_snwfields();
extern void update_redx_snwfields();
extern void update_redx_snwform();
extern void clear_redx_snw_form();
extern void make_buffredx_snw();
extern void read_redx_snw_buffer(string data);
extern void cb_redx_snw_new();
extern void cb_redx_snw_import();
extern void cb_redx_snw_export();
extern void cb_redx_snw_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_redx_snw_wrap_export();
extern void cb_redx_snw_wrap_autosend();
extern void cb_redx_snw_load_template();
extern void cb_redx_snw_save_template();
extern void cb_redx_snw_save_as_template();
extern void cb_redx_snw_open();
extern void write_redx_snw(string s);
extern void cb_redx_snw_save_as();
extern void cb_redx_snw_save();
extern void cb_redx_snw_html();
extern void cb_snw_msg_type();
extern void cb_redx_snw_textout();

// hics203
extern string hics_buff203;
extern string def_hics203_filename;
extern string base_hics203_filename;
extern string def_hics203_TemplateName;
extern bool   using_hics203_template;

extern void cb_hics203_set_date();
extern void cb_hics203_set_time();
extern void clear_hics203fields();
extern void update_hics203fields();
extern void clear_hics203_form();
extern void make_buffhics_203();
extern void read_hics203_buffer(string data);
extern void cb_hics203_new();
extern void cb_hics203_import();
extern void cb_hics203_export();
extern void cb_hics203_wrap_import(string wrapfilename, string inpbuffer);
extern void cb_hics203_wrap_export();
extern void cb_hics203_wrap_autosend();
extern void cb_hics203_load_template();
extern void cb_hics203_save_template();
extern void cb_hics203_save_as_template();
extern void cb_hics203_open();
extern void write_hics203(string s);
extern void cb_hics203_save_as();
extern void cb_hics203_save();
extern void cb_hics203_html();
extern void cb_hics203_msg_type();
extern void cb_hics203_textout();

// ics_h206
extern string h206_buff;
extern string h206_def_filename;
extern string h206_base_filename;
extern string h206_def_template_name;
extern bool   h206_using_template;

extern void h206_cb_setdate();
extern void h206_cb_settime();
extern void h206_clear_fields();
extern void h206_update_fields();
extern void h206_clear__form();
extern void h206_make_buff();
extern void h206_read_buffer(string data);
extern void h206_cb_new();
extern void h206_cb_import();
extern void h206_cb_export();
extern void h206_cb_wrap_import(string wrapfilename, string inpbuffer);
extern void h206_cb_wrap_export();
extern void h206_cb_wrap_autosend();
extern void h206_cb_load_template();
extern void h206_cb_save_template();
extern void h206_cb_save_as_template();
extern void h206_cb_open();
extern void h206_write(string s);
extern void h206_cb_save_as();
extern void h206_cb_save();
extern void h206_cb_html();
extern void h206_cb_msg_type();
extern void h206_cb_textout();

// ics_h213

extern string h213_buffer;
extern string h213_def_filename;
extern string h213_base_filename;
extern string h213_def_template_name;
extern bool   h213_using_template;

extern void h213_cb_set_date();
extern void h213_cb_set_time0();
extern void h213_cb_set_time1();
extern void h213_cb_set_time2();
extern void h213_clear_fields();
extern void h213_update_fields();
extern void h213_clear_form();
extern void h213_update_form();
extern void h213_make_buffer();
extern void h213_read_buffer(string data);
extern void h213_cb_new();
extern void h213_cb_import();
extern void h213_cb_export();
extern void h213_cb_wrap_import(string wrapfilename, string inpbuffer);
extern void h213_cb_wrap_export();
extern void h213_cb_wrap_autosend();
extern void h213_cb_load_template();
extern void h213_cb_save_template();
extern void h213_cb_save_as_template();
extern void h213_cb_open();
extern void h213_write(string s);
extern void h213_cb_save_as();
extern void h213_cb_save();
extern void h213_cb_html();
extern void h213_cb_textout();

// hics 214 variables and functions

extern string hics214_incident;
extern string hics214_date;
extern string hics214_time;
extern string hics214_op_period;
extern string hics214_sec_brch;
extern string hics214_position;
extern string hics214_activity_time[30];
extern string hics214_activity_event[30];
extern string hics214_prepared_by;
extern string hics214_facility;

extern string hics214_buff;
extern string hics214_def_filename;
extern string hics214_base_filename;
extern string hics214_template_name;
extern bool   hics214_using_template;

extern void hics214_cb_set_date();
extern void hics214_cb_set_time();
extern void hics214_clear_fields();
extern void hics214_update_fields();
extern void hics214_update_form();
extern void hics214_clear_form();
extern void hics214_make_buff();
extern void hics214_read_buffer(string data);
extern void hics214_cb_new();
extern void hics214_cb_import();
extern void hics214_cb_export();
extern void hics214_cb_wrap_import(string wrapfilename, string inpbuffer);
extern void hics214_cb_wrap_export();
extern void hics214_cb_wrap_autosend();
extern void hics214_cb_load_template();
extern void hics214_cb_save_template();
extern void hics214_cb_save_as_template();
extern void hics214_cb_open();
extern void hics214_write(string s);
extern void hics214_cb_save_as();
extern void hics214_cb_save();
extern void hics214_cb_html();
extern void hics214_cb_msg_type();
extern void hics214_cb_textout();

#endif
