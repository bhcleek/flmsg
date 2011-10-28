// =====================================================================
//
// status.h
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

#ifndef _status_H
#define _status_H

#include <string>

using namespace std;

enum {
	tb_radiogram, tb_plaintext, tb_blank,
	tb_ics203, tb_ics205, tb_ics205a, tb_ics206, tb_ics213, tb_ics214, tb_ics216,
	tb_hics203, tb_hics206, tb_hics213, tb_hics214,
	tb_mars_daily, tb_mars_ineei, tb_mars_net, tb_mars_army, tb_mars_navy, tb_redx_snw };

struct status {
	int		mainX;
	int		mainY;

	int		wpl; // words per line in radiogram
	bool	open_on_export;
	int		UTC;
	int		dtformat;

	void saveLastState();
	void loadLastState();
	string my_call;
	string my_tel;
	string my_name;
	string my_addr;
	string my_city;
	bool sernbr_fname;
	bool call_fname;
	bool dt_fname;
	bool rgnbr_fname;
	bool arl_desc;
	string sernbr;
	string rgnbr;
	bool insert_x;
	int tab;
	string mars_roster_file;
};

extern status progStatus;

#endif
