//======================================================================
// plaintext templates
//======================================================================

#include "templates.h"

const char pt_html_template[] =
"<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\
<html>\
<head><meta content=\"text/html; charset=ISO-8859-1\" http-equiv=\"content-type\">\
<title>:TITLE:</title>\
</head><body>\
<table WIDTH=1000px BORDER=1 CELLPADDING=0 CELLSPACING=0>\
<tbody>\
<tr ALIGN=center>\
<td COLSPAN=3 VALIGN=top BGCOLOR=#EEEEEE><big><b>:tt:</b></big><br></td>\
</tr>\
<tr><td VALIGN=top>TO: :to:<br></td></tr>\
<tr><td VALIGN=top>FROM: :fm:<br></td></tr>\
<tr><td VALIGN=top>SUBJ: :sb:<br></td></tr>\
<tr><td VALIGN=top>DATE: :dt:<br></td></tr>\
<tr><td VALIGN=top>TIME: :tm:<br></td></tr>\
<tr><td COLSPAN=3 VALIGN=top BGCOLOR=#EEEEEE>MESSAGE:<br></td></tr>\
<tr><td COLSPAN=3 VALIGN=top>:mg:<br></td></tr>\
</table>\
</body></html>";

const char pt_txt_template[] =
"TITLE: :tt:\n\
TO: :to:\n\
FROM: :fm:\n\
SUBJ: :sb:\n\
DATE: :dt:\n\
TIME: :tm:\n\
MESSAGE:\n\
:mg:\n\
";

