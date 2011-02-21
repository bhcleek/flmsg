#ifndef FLMSG_DIALOG_H
#define FLMSG_DIALOG_H

#include <FL/Fl.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Spinner.H>

#include "FTextView.h"
#include "flinput2.h"
#include "calendar.h"
#include "flmsg.h"

extern Fl_Output	*txt_filename;
extern Fl_Tabs	*tabs_msg_type;
extern Fl_Group	*tab_ics;
extern Fl_Tabs	*tab_ics_type;
extern Fl_Input	*drop_box;


extern Fl_Group		*tab_ics203;
extern Fl_Tabs		*tab_ics203_type;
extern Fl_Group		*tab_203_1;
extern Fl_Input2	*txt_203_incident;
extern Fl_Input2	*txt_203_date;
extern Fl_Button	*btn_203_date;
extern Fl_Input2	*txt_203_time;
extern Fl_Button	*btn_203_time;
extern Fl_Input2	*txt_203_op_period;
extern Fl_Input2	*txt_203_incident_commander;
extern Fl_Input2	*txt_203_incident_deputy;
extern Fl_Input2	*txt_203_incident_safety_officer;
extern Fl_Input2	*txt_203_incident_info_officer;
extern Fl_Input2	*txt_203_liaison_officer;
extern Fl_Input2	*txt_203_prepared_by;
extern Fl_Group		*tab_203_agency;
extern Fl_Input2	*txt_203_agency[7];
extern Fl_Input2	*txt_203_agency_name[7];
extern Fl_Group		*tab_203_planning;
extern Fl_Input2	*txt_203_planning_chief;
extern Fl_Input2	*txt_203_planning_deputy;
extern Fl_Input2	*txt_203_resources_unit;
extern Fl_Input2	*txt_203_situation_unit;
extern Fl_Input2	*txt_203_documentation_unit;
extern Fl_Input2	*txt_203_demobilization_unit;
extern Fl_Input2	*txt_203_tech_spc[3];
extern Fl_Group		*tab_203_logistics;
extern Fl_Input2	*txt_203_logistics_chief;
extern Fl_Input2	*txt_203_logistics_deputy;
extern Fl_Input2	*txt_203_support_director;
extern Fl_Input2	*txt_203_supply_unit;
extern Fl_Input2	*txt_203_facilities_unit;
extern Fl_Input2	*txt_203_ground_support;
extern Fl_Input2	*txt_203_service_director;
extern Fl_Input2	*txt_203_communications_unit;
extern Fl_Input2	*txt_203_medical_unit;
extern Fl_Input2	*txt_203_food_unit;
extern Fl_Group		*tab_203_opsA;
extern Fl_Input2	*txt_203_ops_chief;
extern Fl_Input2	*txt_203_ops_deputy;
extern Fl_Input2	*txt_203_b1_director;
extern Fl_Input2	*txt_203_b1_deputy;
extern Fl_Input2	*txt_203_b1_div[5];
extern Fl_Input2	*txt_203_b1_grp[5];
extern Fl_Group		*tab_203_opsB;
extern Fl_Input2	*txt_203_b2_director;
extern Fl_Input2	*txt_203_b2_deputy;
extern Fl_Input2	*txt_203_b2_div[5];
extern Fl_Input2	*txt_203_b2_grp[5];
extern Fl_Group		*tab_203_opsC;
extern Fl_Input2	*txt_203_b3_director;
extern Fl_Input2	*txt_203_b3_deputy;
extern Fl_Input2	*txt_203_b3_div[5];
extern Fl_Input2	*txt_203_b3_grp[5];
extern Fl_Group		*tab_203_opsD;
extern Fl_Input2	*txt_203_air_ops_br_dir;
extern Fl_Input2	*txt_203_air_tactical_group_sup;
extern Fl_Input2	*txt_203_air_support_group_sup;
extern Fl_Input2	*txt_203_helicopter_coordinator;
extern Fl_Input2	*txt_203_air_tanker_fixed_wing;
extern Fl_Group		*tab_203_admin;
extern Fl_Input2	*txt_203_finance_chief;
extern Fl_Input2	*txt_203_finance_deputy;
extern Fl_Input2	*txt_203_time_unit;
extern Fl_Input2	*txt_203_procurement_unit;
extern Fl_Input2	*txt_203_claims_unit;
extern Fl_Input2	*txt_203_cost_unit;

extern Fl_Group		*tab_ics205;
extern Fl_Input2	*txt_205_name;
extern Fl_Input2	*txt_205_dt_prepared;
extern Fl_Button	*btn_205DateTime1;
extern Fl_Input2	*txt_205_dt_operational;
extern Fl_Button	*btn_205_DateTime2;
extern Fl_Input2	*txt_205_type[8];
extern Fl_Input2	*txt_205_channel[8];
extern Fl_Input2	*txt_205_function[8];
extern Fl_Input2	*txt_205_freqtone[8];
extern Fl_Input2	*txt_205_assignment[8];
extern Fl_Input2	*txt_205_remarks[8];
extern Fl_Input2	*txt_205_preparer;

extern Fl_Group		*tab_ics205a;
extern Fl_Tabs		*tab_ics205a_type;
extern Fl_Group		*tab_205a_1;
extern Fl_Group		*tab_205a_2;

extern Fl_Input2	*txt_205a_incident;
extern Fl_Input2	*txt_205a_date_fm;
extern Fl_Button	*btn_205a_date_fm;
extern Fl_Input2	*txt_205a_date_to;
extern Fl_Button	*btn_205a_date_to;
extern Fl_Input2	*txt_205a_time_fm;
extern Fl_Button	*btn_205a_time_fm;
extern Fl_Input2	*txt_205a_time_to;
extern Fl_Button	*btn_205a_time_to;
extern Fl_Input2	*txt_205a_prepared_by;
extern Fl_Input2	*txt_205a_preparer_position;
extern Fl_Input2	*txt_205a_preparer_date_time;
extern Fl_Input2	*txt_205a_comm_group[32];
extern Fl_Input2	*txt_205a_comm_position[32];
extern Fl_Input2	*txt_205a_comm_name[32];
extern Fl_Input2	*txt_205a_comm_info[32];

extern Fl_Group		*tab_ics206;
extern Fl_Tabs		*tab_ics206_type;
extern Fl_Group		*tab_206_med_plan;
extern Fl_Input2	*txt_206_name;
extern Fl_Input2	*txt_206_op_period;
extern Fl_Input2	*txt_206_time_prepared;
extern Fl_Button	*btn_206_time;
extern Fl_DateInput	*txt_206_date_prepared;
extern Fl_Button	*btn_206_date;
extern Fl_Input2	*txt_206_medaid_sta[5];
extern Fl_Input2	*txt_206_medaid_loc[5];
extern Fl_Check_Button	*btn_206_medaid_paramedics[5];
extern Fl_Input2	*txt_206_preparer;
extern Fl_Input2	*txt_206_reviewer;
extern Fl_Group		*tab_206_transport;
extern Fl_Input2	*txt_206_transport_name[5];
extern Fl_Input2	*txt_206_transport_address[5];
extern Fl_Check_Button	*btn_206_transport_paramedics[5];
extern Fl_Input2	*txt_206_transport_phone[5];
extern Fl_Group		*tab_206_ambulance;
extern Fl_Input2	*txt_206_ambulance_name[5];
extern Fl_Input2	*txt_206_ambulance_loc[5];
extern Fl_Check_Button	*btn_206_ambulance_paramedics[5];
extern Fl_Group		*tab_206_hospital;
extern Fl_Input2	*txt_206_hosp_name[5];
extern Fl_Input2	*txt_206_hosp_address[5];
extern Fl_Input2	*txt_206_hosp_phone[5];
extern Fl_Input2	*txt_206_hosp_airtime[5];
extern Fl_Input2	*txt_206_hosp_gndtime[5];
extern Fl_Check_Button	*btn_206_hosp_helipad[5];
extern Fl_Check_Button	*btn_206_hosp_burn_center[5];
extern Fl_Group		*tab_206_med_proc;
extern FTextEdit	*txt_206_procedure;

extern Fl_Group		*tab_ics213;
extern Fl_Tabs		*tab_ics213_type;
extern Fl_Group		*tab_213_originator;
extern Fl_Input2	*txt_213_to;
extern Fl_Input2	*txt_213_p1;
extern Fl_Input2	*txt_213_fm;
extern Fl_Input2	*txt_213_p2;
extern Fl_Input2	*txt_213_subj;
extern Fl_DateInput	*txt_213_d1;
extern Fl_Button	*btn_213_date1;
extern Fl_Input2	*txt_213_t1;
extern Fl_Button	*btn_213_time1;
extern FTextEdit	*txt_213_msg;
extern Fl_Input2	*txt_213_s1;
extern Fl_Input2	*txt_213_p3;
extern Fl_Group		*tab_213_responder;
extern Fl_Input2	*txt_213_s2;
extern Fl_DateInput	*txt_213_d2;
extern Fl_Input2	*txt_213_t2;
extern Fl_Button	*btn_213_time2;
extern FTextEdit	*txt_213_reply;
extern Fl_Input2	*txt_213_p4;
extern Fl_Button	*btn_213_date2;

extern Fl_Group		*tab_ics214;
extern Fl_Tabs		*tab_ics214_type;
extern Fl_Group		*tab_214_1;
extern Fl_Input2	*txt_214_incident;
extern Fl_Input2	*txt_214_date;
extern Fl_Button	*btn_214_date;
extern Fl_Input2	*txt_214_time;
extern Fl_Button	*btn_214_time;
extern Fl_Input2	*txt_214_op_period;
extern Fl_Input2	*txt_214_unit_name;
extern Fl_Input2	*txt_214_unit_leader;
extern Fl_Input2	*txt_214_prepared_by;
extern Fl_Group		*tab_214_2;
extern Fl_Input2	*txt_214_roster_name[16];
extern Fl_Input2	*txt_214_roster_position[16];
extern Fl_Input2	*txt_214_roster_home_base[16];
extern Fl_Group		*tab_214_3;
extern Fl_Input2	*txt_214_activity_time[16];
extern Fl_Input2	*txt_214_activity_event[16];

extern Fl_Group		*tab_ics216;
extern Fl_Group		*tab_ics_216;
extern Fl_Tabs		*tab_ics216_type;
extern Fl_Group		*tab_216_1;
extern Fl_Group		*tab_216_2;
extern Fl_Group		*tab_216_3;
extern Fl_Group		*tab_216_4;
extern Fl_Group		*tab_216_5;
extern Fl_Input2	*txt_216_incident;
extern Fl_Input2	*txt_216_date;
extern Fl_Button	*btn_216_date;
extern Fl_Input2	*txt_216_time;
extern Fl_Button	*btn_216_time;
extern Fl_Input2	*txt_216_branch;
extern Fl_Input2	*txt_216_agc;
extern Fl_Input2	*txt_216_op_period;
extern Fl_Input2	*txt_216_tac_freq;
extern Fl_Input2	*txt_216_prepared_by;
extern Fl_Group		*tab_216_2;
extern Fl_Input2	*txt_216_div_grp[4];
extern Fl_Input2	*txt_216_agency[4];
extern Fl_Group		*tab_216_3;
extern Fl_Input2	*txt_216_ag[36];
extern Fl_Input2	*txt_216_id[36];
extern Fl_Input2	*txt_216_rr[36];

extern Fl_Group		*tab_radiogram;
extern Fl_Tabs		*tabs_radiogram;
extern Fl_Group		*tab_radiogram_message;
extern Fl_Input2	*txt_rg_nbr;
extern Fl_Choice	*sel_rg_prec;
extern Fl_Input2	*txt_rg_hx;
extern Fl_Button	*btn_rg_hx;
extern Fl_Input2	*txt_rg_station;
extern Fl_Input2	*txt_rg_place;
extern Fl_Input2	*txt_rg_t1;
extern Fl_Button	*btn_rgTime1;
extern Fl_Input2	*txt_rg_d1;
extern Fl_Button	*btn_rgDate1;
extern Fl_Input2	*txt_rg_to;
extern Fl_Input2	*txt_rg_phone;
extern Fl_Input2	*txt_rg_opnote;
extern FTextEdit	*txt_rg_msg;
extern Fl_Button	*btn_arl;
extern Fl_Input2	*txt_rg_check;
extern Fl_Button	*btn_rg_check;
extern Fl_Input2	*txt_rg_sig;
extern Fl_Input2	*txt_rg_opnote2;
extern Fl_Check_Button	*btn_rg_svc;
extern Fl_Group		*tab_radiogram_information;
extern Fl_Input2	*txt_rg_orig;
extern Fl_Input2	*txt_rg_dt2;
extern Fl_Button	*btn_rgDateTime2;
extern Fl_Input2	*txt_rg_dt3;
extern Fl_Button	*btn_rgDateTime3;
extern Fl_Input2	*txt_rg_dlvd_to;
extern Fl_Input2	*txt_rg_rcv_fm;
extern Fl_Input2	*txt_rg_rcv_net;
extern Fl_Input2	*txt_rg_dt4;
extern Fl_Button	*btn_rgDateTime4;
extern Fl_Input2	*txt_rg_sent_to;
extern Fl_Input2	*txt_rg_snt_net;
extern Fl_Input2	*txt_rg_dt5;
extern Fl_Button	*btn_rgDateTime5;

extern Fl_Group		*tab_plaintext;
extern Fl_Input2	*txt_pt_title;
extern Fl_Input2	*txt_pt_to;
extern Fl_Input2	*txt_pt_fm;
extern Fl_Input2	*txt_pt_subj;
extern FTextEdit	*txt_pt_msg;
extern Fl_DateInput	*txt_pt_date;
extern Fl_Button	*btn_pt_date;
extern Fl_Input2	*txt_pt_time;
extern Fl_Button	*btn_pt_time;

extern Fl_Group		*tab_blank;
extern FTextEdit	*txt_blank_msg;

Fl_Double_Window* ics_dialog();
extern Fl_Menu_Item menu_[];
#define mnuNew (menu_+1)
#define mnuOpen (menu_+2)
#define mnuSave (menu_+3)
#define mnuSaveAs (menu_+4)
#define mnu_html (menu_+6)
#define mnu_html_fcopy (menu_+7)
#define mnu_text (menu_+8)
#define mnu_qimport (menu_+11)
#define mnu_qexport (menu_+12)
#define mnuWrapImport (menu_+15)
#define mnuWrapExport (menu_+16)
#define mnuAutoSend (menu_+17)
#define mnuExit (menu_+19)
#define mnu_load_template (menu_+22)
#define mnu_save_template (menu_+23)
#define mnu_save_as_template (menu_+24)
#define mnuConfig (menu_+26)
#define mnuOptions (menu_+29)
#define mnuOnLineHelp (menu_+30)
#define mnuAbout (menu_+31)

extern Fl_Browser	*brwsOptions;


extern Fl_Return_Button	*btnCloseOptions;

Fl_Double_Window* optionsdialog();
extern Fl_Browser	*select_arl;
extern Fl_Input		*txt_arl_fill1;
extern Fl_Input		*txt_arl_fill2;
extern Fl_Input		*txt_arl_fill3;
extern Fl_Input		*txt_arl_fill4;
extern Fl_Button	*btn_arl_cancel;
extern Fl_Button	*btn_arl_add;
extern FTextEdit	*arl_text;
extern Fl_Check_Button	*btnInsertX;

Fl_Double_Window* arl_dialog();
extern Fl_Round_Button	*btn_dtformat0;
extern Fl_Round_Button	*btn_dtformat1;
extern Fl_Round_Button	*btn_dtformat2;
extern Fl_Round_Button	*btn_utc_format0;
extern Fl_Round_Button	*btn_utc_format1;
extern Fl_Round_Button	*btn_utc_format2;
extern Fl_Round_Button	*btn_utc_format3;
extern Fl_Round_Button	*btn_utc_format4;
extern Fl_Round_Button	*btn_utc_format5;
extern Fl_Button	*btn_close_config;
extern Fl_Input		*txt_my_call;
extern Fl_Input		*txt_my_tel;
extern Fl_Input		*txt_my_name;
extern Fl_Input		*txt_my_addr;
extern Fl_Input		*txt_my_city;

extern Fl_Spinner	*cnt_wpl;
extern Fl_Check_Button	*btn_open_on_export;
extern Fl_Check_Button	*btn_call_fname;
extern Fl_Check_Button	*btn_dt_fname;
extern Fl_Check_Button	*btn_sernbr_fname;
extern Fl_Input		*txt_sernbr;
extern Fl_Check_Button	*btn_rgnbr_fname;
extern Fl_Input		*txt_rgnbr;

Fl_Double_Window* config_dialog();
extern Fl_Choice	*sel_hx_select;
extern Fl_Button	*btn_hx_select_add;
extern Fl_Input2	*txt_hx_select_text;
extern Fl_Button	*btn_hx_select_cancel;
extern Fl_Return_Button	*btn_hx_select_ok;
extern Fl_Output	*txt_hx_instructions;

Fl_Double_Window* hx_dialog();

#endif
