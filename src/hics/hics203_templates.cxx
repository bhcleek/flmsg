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

#include "templates.h"

const char hics203_html_template[] =
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN\"\
                       \"http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd\">\
<html xmlns=\"http://www.w3.org/1999/xhtml\">\
<head profile=\"http://dublincore.org/documents/dcmi-terms/\">\
<!--This file was converted to xhtml by OpenOffice.org -\
    see http://xml.openoffice.org/odf2xhtml for more info.-->\
\
<meta http-equiv=\"Content-Type\" content=\"application/xhtml+xml; charset=utf-8\" />\
<title xml:lang=\"en-US\">ORGANIZATION ASSIGNMENT LIST</title>\
<meta name=\"DCTERMS.title\" content=\"ORGANIZATION ASSIGNMENT LIST\" xml:lang=\"en-US\" />\
<meta name=\"DCTERMS.language\" content=\"en-US\" scheme=\"DCTERMS.RFC4646\" />\
<meta name=\"DCTERMS.source\" content=\"http://xml.openoffice.org/odf2xhtml\" />\
<meta name=\"DCTERMS.creator\" content=\"deguzmno\" />\
<meta name=\"DCTERMS.issued\" content=\"2007-04-23T15:03:00\" scheme=\"DCTERMS.W3CDTF\" />\
<meta name=\"DCTERMS.contributor\" content=\"MedStar Health\" />\
<meta name=\"DCTERMS.modified\" content=\"2007-04-23T15:03:00\" scheme=\"DCTERMS.W3CDTF\" />\
<meta name=\"DCTERMS.provenance\" content=\"\" xml:lang=\"en-US\" />\
<meta name=\"DCTERMS.subject\" content=\",\" xml:lang=\"en-US\" />\
<link rel=\"schema.DC\" href=\"http://purl.org/dc/elements/1.1/\" hreflang=\"en\" />\
<link rel=\"schema.DCTERMS\" href=\"http://purl.org/dc/terms/\" hreflang=\"en\" />\
<link rel=\"schema.DCTYPE\" href=\"http://purl.org/dc/dcmitype/\" hreflang=\"en\" />\
<link rel=\"schema.DCAM\" href=\"http://purl.org/dc/dcam/\" hreflang=\"en\" />\
<style type=\"text/css\">\
	@page {  }\
	table { border-collapse:collapse; border-spacing:0; empty-cells:show }\
	td, th { vertical-align:top; font-size:12pt;}\
	h1, h2, h3, h4, h5, h6 { clear:both }\
	ol, ul { margin:0; padding:0;}\
	li { list-style: none; margin:0; padding:0;}\
	<!-- \"li span.odfLiEnd\" - IE 7 issue-->\
	li span. { clear: both; line-height:0; width:0; height:0; margin:0; padding:0; }\
	span.footnodeNumber { padding-right:1em; }\
	span.annotation_style_by_filter { font-size:95%; font-family:Arial; background-color:#fff000;  margin:0; border:0; padding:0;  }\
	* { margin:0;}\
	.fr1 { font-size:12pt; text-align:center; vertical-align:top; writing-mode:lr-tb; margin-left:0in; margin-right:0in; padding-left:0.0937in; padding-right:0.0937in; padding-top:0.0437in; padding-bottom:0.0437in; border-width:0.018cm; border-style:solid; border-color:#000000; }\
	.gr1 { font-size:12pt; writing-mode:lr-tb; padding-top:0.0902in; padding-bottom:0.0902in; padding-left:0.1736in; padding-right:0.1736in; margin-left:0.1256in; margin-right:0.1256in; vertical-align:middle; text-align:center; }\
	.Footer { font-size:12pt; font-family:Times New Roman; writing-mode:lr-tb; }\
	.P1 { font-size:8pt; font-family:Arial; writing-mode:lr-tb; text-align:right ! important; }\
	.P2 { font-size:8pt; font-family:Arial; writing-mode:lr-tb; }\
	.P3 { font-size:12pt; font-family:Times New Roman; writing-mode:lr-tb; }\
	.P4 { font-size:1pt; font-family:Times New Roman; writing-mode:lr-tb; }\
	.P5 { font-size:10pt; font-family:Arial; writing-mode:lr-tb; text-align:center ! important; font-weight:bold; }\
	.P6 { font-size:11pt; font-family:Arial; writing-mode:lr-tb; font-weight:bold; background-color:#c0c0c0; }\
	.P7 { font-size:11pt; font-family:Arial; writing-mode:lr-tb; font-weight:bold; }\
	.P8 { font-size:11pt; font-family:Arial; writing-mode:lr-tb; text-align:justify ! important; letter-spacing:-0.0016in; }\
	.P9 { font-size:9pt; font-family:Arial; writing-mode:lr-tb; font-weight:bold; background-color:#c0c0c0; }\
	.P10 { font-size:9pt; font-family:Arial; writing-mode:lr-tb; }\
	.P11_borderStart { font-size:9pt; font-family:Arial; writing-mode:lr-tb; margin-top:0.028in; font-weight:bold; background-color:#c0c0c0; padding-bottom:0in;  border-bottom-style:none; }\
	.P11 { font-size:9pt; font-family:Arial; writing-mode:lr-tb; font-weight:bold; background-color:#c0c0c0; padding-top:0.028in; padding-bottom:0in;  border-top-style:none; border-bottom-style:none; }\
	.P11_borderEnd { font-size:9pt; font-family:Arial; writing-mode:lr-tb; margin-bottom:0in; font-weight:bold; background-color:#c0c0c0; padding-top:0.028in;  border-top-style:none;}\
	.P12 { font-size:8pt; font-family:Arial; writing-mode:lr-tb; margin-top:0.028in; margin-bottom:0.028in; text-align:right ! important; }\
	.P13 { font-size:9pt; font-family:Arial; writing-mode:lr-tb; margin-top:0.028in; margin-bottom:0.028in; font-weight:bold; }\
	.P14 { font-size:9pt; font-family:Arial; writing-mode:lr-tb; margin-top:0.028in; margin-bottom:0.028in; }\
	.P15 { font-size:9pt; font-family:Arial; writing-mode:lr-tb; margin-top:0.028in; margin-bottom:0.028in; text-align:center ! important; }\
	.P16 { font-size:9pt; font-family:Arial; writing-mode:lr-tb; margin-top:0.028in; margin-bottom:0.028in; }\
	.Table1 { width:8.1569in; margin-left:-0.0785in; writing-mode:lr-tb; }\
	.Table1_A1 { vertical-align:middle; padding-left:0.075in; padding-right:0.075in; padding-top:0in; padding-bottom:0in; border-left-width:0.0176cm; border-left-style:solid; border-left-color:#000000; border-right-style:none; border-top-width:0.0176cm; border-top-style:solid; border-top-color:#000000; border-bottom-width:0.0176cm; border-bottom-style:solid; border-bottom-color:#000000; writing-mode:lr-tb; }\
	.Table1_A2 { vertical-align:top; padding-left:0.075in; padding-right:0.075in; padding-top:0in; padding-bottom:0in; border-left-width:0.0176cm; border-left-style:solid; border-left-color:#000000; border-right-style:none; border-top-width:0.0176cm; border-top-style:solid; border-top-color:#000000; border-bottom-width:0.0176cm; border-bottom-style:solid; border-bottom-color:#000000; writing-mode:lr-tb; }\
	.Table1_C1 { vertical-align:top; padding-left:0.075in; padding-right:0.075in; padding-top:0in; padding-bottom:0in; border-width:0.0176cm; border-style:solid; border-color:#000000; writing-mode:lr-tb; }\
	.Table1_A { width:2.7167in; }\
	.Table1_B { width:1.4833in; }\
	.Table1_C { width:1.375in; }\
	.Table1_D { width:2.5819in; }\
	.T1 { font-weight:bold; }\
	.T2 { background-color:#c0c0c0; }\
	<!-- ODF styles with no properties representable as CSS -->\
	.Table1.1 .Table1.2 .Table1.3 { }\
</style>\
</head>\
<body dir=\"ltr\" style=\"margin: 0.25in; max-width: 8.5in;\">\
<table class=\"Table1\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\
	<colgroup>\
		<col width=\"302\" />\
		<col width=\"165\" />\
		<col width=\"153\" />\
		<col width=\"287\" />\
	</colgroup>\
	<tbody>\
		<tr class=\"Table11\">\
			<td colspan=\"2\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A1\">\
				<p class=\"P5\">HICS 203 – ORGANIZATION ASSIGNMENT LIST</p>\
			</td>\
			<td colspan=\"2\" style=\"text-align: left; width: 1.375in;\" class=\"Table1_C1\">\
				<p class=\"P12\">&nbsp;</p></td>\
		</tr>\
		<tr class=\"Table12\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P11\">1. &nbsp;INCIDENT NAME</p>\
			</td>\
			<td style=\"text-align: left; width: 1.4833in;\" class=\"Table1_A2\">\
				<p class=\"P11\">2. &nbsp; DATE PREPARED</p>\
			</td>\
			<td style=\"text-align: left; width: 1.375in;\" class=\"Table1_A2\">\
				<p class=\"P11\">3. &nbsp;TIME PREPARED</p>\
			</td>\
			<td style=\"text-align: left; width: 2.5819in;\" class=\"Table1_C1\">\
				<p class=\"P13\"><span class=\"T2\">4. &nbsp;OPERATIONAL PERIOD DATE/TIME</span></p>\
			</td>\
		</tr>\
		<tr class=\"Table12\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P11\">&nbsp;:inc:</p>\
			</td>\
			<td style=\"text-align: left; width: 1.4833in;\" class=\"Table1_A2\">\
				<p class=\"P11\">&nbsp;:dat:</p>\
			</td>\
			<td style=\"text-align: left; width: 1.375in;\" class=\"Table1_A2\">\
				<p class=\"P11\">&nbsp;:tim:</p>\
			</td>\
			<td style=\"text-align: left; width: 2.5819in;\" class=\"Table1_C1\">\
				<p class=\"P11\"><span class=\"T2\">&nbsp;:opp:</span></p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P6\">POSITION</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P7\"><span class=\"T2\">NAME / AGENCY</span></p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td colspan=\"4\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_C1\">\
				<p class=\"P9\">5. &nbsp;Incident Commander and Staff</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Incident Commander</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:icc:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Public Information Officer</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:ici:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Liaison Officer</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:icl:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Safety Officer</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:ics:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Medical/Technical Specialist (Type)</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:tech_spc[0]:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Medical/Technical Specialist (Type)</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:tech_spc[1]:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Medical/Technical Specialist (Type)</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:tech_spc[2]:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Medical/Technical Specialist (Type)</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:tech_spc[3]:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Medical/Technical Specialist (Type)</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:tech_spc[4]:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Medical/Technical Specialist (Type)</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:tech_spc[5]:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td colspan=\"4\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_C1\">\
				<p class=\"P9\">6. &nbsp;Operations Section</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Chief</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:ops_chief:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Staging Manager</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:stg_mgr:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Medical Care Branch</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:med_care_brch:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Infrastructure Branch</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:infr_brch:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Security Branch</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:sec_brch:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Business Continuity Branch</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:bus_brch:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">HazMat Branch</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:hazmat_brch:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Other Branch:</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:ops_other:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td colspan=\"4\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_C1\">\
				<p class=\"P9\">7. &nbsp;Planning Section</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Chief</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:planning_chief:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Resources Unit</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:res_unit:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Situation Unit</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:sit_unit:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Documentation Unit</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:doc_unit:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Demobilization Unit</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:dem_unit:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Other Branch:<br /></p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:planning_other:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td colspan=\"4\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_C1\">\
				<p class=\"P9\">8. &nbsp;Logistics Section</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Chief</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:log_chief:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Service Branch</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:svc_brch:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Support Branch</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:sup_brch:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Other Branch:</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:log_other:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td colspan=\"4\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_C1\">\
				<p class=\"P9\">9. &nbsp;Finance/Administration Section</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Chief</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:fin_chief:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Time Unit</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:time_unit:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Procurement Unit</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:proc_unit:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Compensation/Claims Unit</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:comp_unit:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Cost Unit</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:cost_unit:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P14\">Other Branch:</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;:fin_other:</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td colspan=\"4\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_C1\">\
				<p class=\"P9\">10. &nbsp;Agency Representative (in Hospital Command Center)</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P15\">Agency</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P16\">&nbsp;:hcc_agency: <br /></p>\
				<p class=\"P16\">&nbsp;:hcc_rep:<br /></p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P16\">&nbsp;</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\"><br />\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P16\">&nbsp;</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td colspan=\"4\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_C1\">\
				<p class=\"P9\">11. &nbsp;Hospital Representative (in External EOC)</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P15\">External Location</p>\
			</td>\
		<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
			<p class=\"P16\">&nbsp;:ext_loc:</p>\
			<p class=\"P16\">&nbsp;:ext_rep:</p>\
		</td>\
		</tr><tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P16\">&nbsp;</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td style=\"text-align: left; width: 2.7167in;\" class=\"Table1_A2\">\
				<p class=\"P16\">&nbsp;</p>\
			</td>\
			<td colspan=\"3\" style=\"text-align: left; width: 1.4833in;\" class=\"Table1_C1\">\
				<p class=\"P10\">&nbsp;</p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td colspan=\"4\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_C1\">\
				<p class=\"P9\">12. PREPARED BY (RESOURCES UNIT LEADER) :pre:<br /></p>\
			</td>\
		</tr>\
		<tr class=\"Table13\">\
			<td colspan=\"4\" style=\"text-align: left; width: 2.7167in;\" class=\"Table1_C1\">\
				<p class=\"P9\">13. FACILITY NAME :facility:<br /></p>\
			</td>\
		</tr>\
	</tbody>\
</table>\
<p class=\"P8\">&nbsp;</p>\
</body></html>";

const char hics203_text_template[] =
"HICS 203 ORGANIZATION ASSIGNMENT LIST\n\n\
1. INCIDENT NAME: :inc:\n\
2. DATE PREPARED: :dat:\n\
3. TIME PREPARED: :tim:\n\
4. OPERATIONAL PERIOD: :opp:\n\
5. Incident Commander and Staff\n\
   Incident Commander: :icc:\n\
   Public Information Officer: :ici:\n\
   Liaison Officer: :icl:\n\
   Safety Officer: :ics:\n\
   Medical/Technical Specialist (Type)\n\
     :tech_spc[0]:\n\
     :tech_spc[1]:\n\
     :tech_spc[2]:\n\
     :tech_spc[3]:\n\
     :tech_spc[4]:\n\
     :tech_spc[5]:\n\
6. Operations Section\n\
   Chief: :ops_chief:\n\
   Staging Manager: :stg_mgr:\n\
   Medical Care Branch: :med_care_brch:\n\
   Infrastructure Branch: :infr_brch:\n\
   Security Branch: :sec_brch:\n\
   Business Continuity Branch: :bus_brch:\n\
   HazMat Branch: :hazmat_brch:\n\
   Other Ops Branch: :ops_other:\n\
7. Planning Section\n\
   Chief: :planning_chief:\n\
   Resources Unit: :res_unit:\n\
   Situation Unit: :sit_unit:\n\
   Documentation Unit: :doc_unit:\n\
   Demobilization Unit: :dem_unit:\n\
   Other Planning Branch: :planning_other:\n\
8. Logistics Section\n\
   Chief: :log_chief:\n\
   Service Branch: :svc_brch:\n\
   Support Branch: :sup_brch:\n\
   Other Logistics Branch: :log_other:\n\
9. Finance/Administration Section\n\
   Chief: :fin_chief:\n\
   Time Unit: :time_unit:\n\
   Procurement Unit: :proc_unit:\n\
   Compensation/Claims Unit: :comp_unit:\n\
   Cost Unit: :cost_unit:\n\
   Other Finance/Admin Branch: :fin_other:\n\
10. Agency Representative (in Hospital Command Center)\n\
    Agency: :hcc_agency:\n\
    Rep: :hcc_rep:\n\
11. Hospital Representative (in External EOC)\n\
    External Location: :ext_loc:\n\
    Rep: :ext_rep:\n\
12. PREPARED BY (RESOURCES UNIT LEADER): :pre:\n\
13. FACILITY NAME: :facility:\n";
