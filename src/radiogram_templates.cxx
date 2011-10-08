//======================================================================
// RADIOGRAM templates
//======================================================================

#include "templates.h"

const char rg_html_template[] =
"<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\
<html><head><meta content=\"text/html; charset=ISO-8859-1\" http-equiv=\"content-type\"><title>radiogram</title>\
<meta content=\"w1hkj\" name=\"author\">\
</head><body>\
<table style=\"text-align: left; width: 100%;\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\
<tbody>\
<tr>\
<td style=\"vertical-align: top;\">\
<table style=\"text-align: left; width: 100%; margin-left: auto; margin-right: auto;\" border=\"0\" cellpadding=\"2\" cellspacing=\"0\">\
<tbody>\
<tr>\
<td style=\"vertical-align: top;\">\
<div style=\"text-align: center;\"><font size=\"3\"><b>THE AMERICAN RADIO RELAY LEAGUE</b></font><br>\
</div>\
<div style=\"text-align: center;\"><font size=\"6\"><b>RADIOGRAM</b></font><br>\
</div>\
<div style=\"text-align: center;\"><font size=\"3\"><b>VIA AMATEUR RADIO<br>\
</b></font></div>\
</td>\
</tr>\
</tbody>\
</table>\
<table style=\"text-align: left; width: 100%;\" border=\"1\" cellpadding=\"2\" cellspacing=\"0\">\
<tbody>\
<tr>\
<td style=\"vertical-align: top; text-align: center; width: 7%;\"><font size=\"1\">NUMBER</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 14%;\"><font size=\"1\">PRECEDENCE</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 7%;\"><font size=\"1\">HX</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 20%;\"><font size=\"1\">STATION OF ORIGIN</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 8%;\"><font size=\"1\">CHECK</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 20%;\"><font size=\"1\">PLACE OF ORIGIN</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 10%;\"><font size=\"1\">TIME FILED</font></td>\
<td style=\"vertical-align: top; text-align: center;\"><font size=\"1\">DATE</font></td>\
</tr>\
<tr>\
<td style=\"vertical-align: top; text-align: center;\">:nbr:</td>\
<td style=\"vertical-align: top; text-align: center;\">:prec:</td>\
<td style=\"vertical-align: top; text-align: center;\">:hx:</td>\
<td style=\"vertical-align: top; text-align: center;\">:sta:</td>\
<td style=\"vertical-align: top; text-align: center;\">:ck:</td>\
<td style=\"vertical-align: top; text-align: center;\">:org:</td>\
<td style=\"vertical-align: top; text-align: center;\">:t1:</td>\
<td style=\"vertical-align: top; text-align: center;\">:d1:</td>\
</tr>\
<tr>\
<td colspan=\"4\" style=\"vertical-align: top;\">\
<font size=\"2\">TO<br>\
</font>:to:<br>\
</td>\
<td colspan=\"4\" style=\"vertical-align: top;\">\
<div style=\"text-align: center;\"><font size=\"2\">THIS RADIO MESSAGE WAS RECEIVED AT</font><br>\
</div>\
:rx:<br>\
</td>\
</tr>\
<tr>\
<td colspan=\"8\" style=\"vertical-align: top;\"><font size=\"2\">PHONE NUMBER<br>\
</font>:tel:<br>\
</td>\
</tr>\
<tr>\
<td colspan=\"8\" style=\"vertical-align: top;\"><font size=\"4\">:msg:<br>\
</font>:sig:<br>\
</td>\
</tr>\
</tbody>\
</table>\
<table style=\"text-align: left; width: 100%;\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\">\
<tbody>\
<tr>\
<td style=\"vertical-align: top;\"><br>\
:exp:</td>\
</tr>\
</tbody>\
</table>\
</td>\
</tr>\
</tbody>\
</table>\
<br>\
</body></html>";

const char rg_html_fcopy_template[] = 
"<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\
<html><head><meta content=\"text/html; charset=ISO-8859-1\" http-equiv=\"content-type\"><title>radiogram-file-copy</title>\
<meta content=\"w1hkj\" name=\"author\">\
</head><body>\
<table style=\"text-align: left; width: 100%;\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\
<tbody>\
<tr>\
<td style=\"vertical-align: top;\">\
<table style=\"text-align: left; width: 100%; margin-left: auto; margin-right: auto;\" border=\"0\" cellpadding=\"2\" cellspacing=\"0\">\
<tbody>\
<tr>\
<td style=\"vertical-align: top;\">\
<div style=\"text-align: center;\"><font size=\"3\"><b>THE AMERICAN RADIO RELAY LEAGUE</b></font><br>\
</div>\
<div style=\"text-align: center;\"><font size=\"6\"><b>RADIOGRAM</b></font><br>\
</div>\
<div style=\"text-align: center;\"><font size=\"3\"><b>VIA AMATEUR RADIO<br>\
</b></font></div>\
</td>\
</tr>\
</tbody>\
</table>\
<table style=\"text-align: left; width: 100%;\" border=\"1\" cellpadding=\"2\" cellspacing=\"0\">\
<tbody>\
<tr>\
<td style=\"vertical-align: top; text-align: center; width: 7%;\"><font size=\"1\">NUMBER</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 14%;\"><font size=\"1\">PRECEDENCE</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 7%;\"><font size=\"1\">HX</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 20%;\"><font size=\"1\">STATION OF ORIGIN</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 8%;\"><font size=\"1\">CHECK</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 20%;\"><font size=\"1\">PLACE OF ORIGIN</font></td>\
<td style=\"vertical-align: top; text-align: center; width: 10%;\"><font size=\"1\">TIME FILED</font></td>\
<td style=\"vertical-align: top; text-align: center;\"><font size=\"1\">DATE</font></td>\
</tr>\
<tr>\
<td style=\"vertical-align: top; text-align: center;\">:nbr:</td>\
<td style=\"vertical-align: top; text-align: center;\">:prec:</td>\
<td style=\"vertical-align: top; text-align: center;\">:hx:</td>\
<td style=\"vertical-align: top; text-align: center;\">:sta:</td>\
<td style=\"vertical-align: top; text-align: center;\">:ck:</td>\
<td style=\"vertical-align: top; text-align: center;\">:org:</td>\
<td style=\"vertical-align: top; text-align: center;\">:t1:</td>\
<td style=\"vertical-align: top; text-align: center;\">:d1:</td>\
</tr>\
<tr>\
<td colspan=\"4\" style=\"vertical-align: top;\">\
<font size=\"2\">TO<br>\
</font>:to:<br>\
</td>\
<td colspan=\"4\" style=\"vertical-align: top;\">\
<div style=\"text-align: center;\"><font size=\"2\">THIS RADIO MESSAGE WAS RECEIVED AT</font><br>\
</div>\
:rx:<br>\
</td>\
</tr>\
<tr>\
<td colspan=\"8\" style=\"vertical-align: top;\"><font size=\"2\">PHONE NUMBER<br>\
</font>:tel:<br>\
</td>\
</tr>\
<tr>\
<td colspan=\"8\" style=\"vertical-align: top;\"><font size=\"4\">:msg:<br>\
</font>:sig:<br>\
</td>\
</tr>\
</tbody>\
</table>\
<table style=\"text-align: left; width: 100%;\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\">\
<tbody>\
<tr>\
<td style=\"vertical-align: top; width: 50%\"><br>ORIG - FROM / DATE/TIME<br>:ori:</td>\
<td style=\"vertical-align: top; width: 50%\"><br>DLVD - to / DATE/TIME<br>:dlv:</td>\
</tr>\
</tbody>\
</table>\
</td>\
</tr>\
</tbody>\
</table>\
<br>\
</body></html>";

const char rg_txt_template[] =
":nbr: :prec::hx: :sta: :ck: :org: :t1: :d1:\n\
:to:\n\
:tel::opn:\n\
BT\n\
:msg:\n\
BT\n\
:sig::op2:\n\
AR\n\
";

