//======================================================================
// Blank tab

#include "gettext.h"
#include "status.h"
#include "util.h"

#include "flmsg_dialog.h"
#include "flmsg.h"

Fl_Group	*tab_csv = (Fl_Group *)0;

FTextEdit	*txt_csv_msg = (FTextEdit *)0;
Fl_Button	*btn_csv_import = (Fl_Button *)0;
Fl_Button	*btn_csv_export = (Fl_Button *)0;

static void cb_btn_csv_import(Fl_Button*, void*) {
	cb_csv_import_data();
}

static void cb_btn_csv_export(Fl_Button*, void*) {
	if (Fl::event_button() == FL_RIGHT_MOUSE)
		cb_csv_export_data(true);
	else
		cb_csv_export_data(false);
}

void do_read_cb(const char *fn) {
	csv_set_fname(fn);
}

void create_csv_tab()
{
	tab_csv = new Fl_Group(0, tab_top, 570, 430 - tab_top);
	tab_csv->align(FL_ALIGN_TOP);

	btn_csv_import = new Fl_Button(570/2 - 110, tab_top + 5, 100, 24, _("Import CSV"));
	btn_csv_import->tooltip(_("Import data from spreadsheet CSV file"));
	btn_csv_import->callback((Fl_Callback*)cb_btn_csv_import);

	btn_csv_export = new Fl_Button(570/2 + 10, tab_top + 5, 100, 24, _("Export CSV"));
	btn_csv_export->tooltip(_("Export data to spreadsheet CSV file"));
	btn_csv_export->callback((Fl_Callback*)cb_btn_csv_export);

	txt_csv_msg = new FTextEdit(2, tab_top + 24 + 10, 566, 430 - (tab_top + 24 + 10 + 2));
	txt_csv_msg->box(FL_DOWN_FRAME);
	txt_csv_msg->color((Fl_Color)FL_BACKGROUND2_COLOR);
	txt_csv_msg->selection_color((Fl_Color)FL_SELECTION_COLOR);
	txt_csv_msg->labeltype(FL_NORMAL_LABEL);
	txt_csv_msg->labelfont(0);
	txt_csv_msg->labelsize(14);
	txt_csv_msg->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
	txt_csv_msg->align(FL_ALIGN_TOP_LEFT);
	txt_csv_msg->set_read_cb(do_read_cb);
	txt_csv_msg->when(0);

	tab_csv->end();
	tab_csv->hide();
}