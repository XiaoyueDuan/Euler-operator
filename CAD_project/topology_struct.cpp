/***************************************************************************************

Author: DXY

Date:2016-11

Compiler Version:vs2013

Operating System:WIN7 64BIT

Description: half-edge topology data structure

***************************************************************************************/

#include "topology_struct.h"

using namespace std;

namespace HALF_EDGE
{
	void Solid::insert_after(Solid *s)
	{
		// insert e2 following e1
		s->nexts = nexts;
		nexts->prevs = s;
		nexts = s;
		s->prevs = this;
	}

	void Face::insert_after(Face *f)
	{
		f->nextf = nextf;
		nextf->prevf = f;
		nextf = f;
		f->prevf = this;
	}

	void Face::insert_inlp_list(Loop *lp)
	{
		if (inloop == NULL)
		{
			inloop = lp;
			(*outloop).insert_after(lp);//new !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
		else
			(*inloop).insert_after(lp);
	}

	void Loop::insert_after(Loop *lp)
	{
		lp->nextl = nextl;
		nextl->prevl = lp;
		nextl = lp;
		lp->prevl = this;
	}

	void Loop::resetNv()
	{
		Half_edge *he = lhe;
		int n = 0;
		do{
			++n;
			he = he->nxt;
		} while (he != lhe);

		nv = n;
	}

	int Loop::getNv()
	{
		resetNv();
		return nv;
	}
}