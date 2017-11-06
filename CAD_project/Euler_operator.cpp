/***************************************************************************************

Author: DXY

Date:2016-11

Compiler Version:vs2013

Operating System:WIN7 64BIT

Description: half-edge topology data structure

***************************************************************************************/

#include "Euler_operator.h"

namespace HALF_EDGE
{
	Solid *Euler_oper::mvsf(Vertex *&v, Point *p)
	{
		Solid *s = new Solid();//ÊÔÒ»ÏÂSolid *s=new Solid()
		Face *f = new Face();
		Loop *outl = new Loop();
		v = new Vertex((*p).x, (*p).y, (*p).z);

		// construct vertex
		//v.vid = s->vnum;
		vertex_list.push_back(v);

		// construct face
		f->fsolid = s;
		f->outloop = outl;
		face_list.push_back(f);
		//f->fid = s->fnum;

		// construct outloop of face
		outl->lface = f;
		outl->lid = f->innum;
		outl->lid = s->lpnum;
		loop_list.push_back(outl);

		// construct solid
		s->sface = f;
		s->vnum += 1;
		s->fnum += 1;
		s->lpnum += 1;
		s->sid = solid_list.size();
		solid_list.push_back(s);

		return s;
	}

	Half_edge *Euler_oper::mev(Vertex *v1, Point *p, Loop *lp)
	{
		Edge *eg = new Edge();
		Half_edge *h1 = new Half_edge(), *h2 = new Half_edge();
		Vertex *v2 = new Vertex((*p).x, (*p).y, (*p).z);

		vertex_list.push_back(v2);

		eg->he1 = h1;
		eg->he2 = h2;

		h1->wloop = h2->wloop = lp;
		h1->start_hev = v1;	h1->end_hev = v2;
		h1->nxt = h2;
		h2->start_hev = v2;	h2->end_hev = v1;
		h1->edg = h2->edg = eg;

		if (lp->lhe == NULL)
		{
			// when only one vertex in this solid
			h2->nxt = h1;
			lp->lhe = h1;// or lp->lhe=h2;
		}
		else
		{
			Half_edge *he = lp->lhe;
			
			while (true)
			{
				if (he->nxt->start_hev == v1)
				{
					h2->nxt = he->nxt;
					he->nxt = h1;
					break;
				}
				he = he->nxt;
			}
		}

		lp->lface->fsolid->vnum += 1;
		lp->lface->fsolid->eenum += 1;

		return h1;
	}

	Loop *Euler_oper::mef(Vertex *v1, Vertex *v2, Loop *lp_old)
	{
		// lp2 is the old loop, lp1 is the new one
		Half_edge *h_old = new Half_edge(), *h_new = new Half_edge();
		Edge *edg = new Edge();
		Loop *lp_new = new Loop();	// outer loop of f2
		Face *f_new = new Face();

		edg->he1 = h_old;		edg->he2 = h_new;//Edge.he1 and Edge.he2

		Face *f_old = lp_old->lface;	//Face.lface		
		f_new->fsolid = f_old->fsolid;//Face.fsolid		
		f_new->outloop = lp_new;		//Face.outloop
		(*f_old).insert_after(f_new);
		face_list.push_back(f_new);

		lp_new->lface = f_new;		//Loop.lface
		lp_new->lhe = h_new;			//Loop.lhe, notification: 1<->2 exchange
		loop_list.push_back(lp_new);

		h_new->wloop = lp_new;	h_old->wloop = lp_old;	//Edge.wloop , notification: 1<->2 exchange
		h_new->start_hev = v1;	h_old->start_hev = v2; //Edge.start_hev
		h_new->end_hev = v2;	h_old->end_hev = v1;
		h_new->edg = h_old->edg = edg;				//Edge.edg

		Half_edge *he = lp_old->lhe;			//link the h1 and h2 to the other half edges
		Half_edge *temp;
		int i = 0;
		while (i != 2)
		{
			if (he->nxt->start_hev == v1)
			{
				++i; 
				temp = he->nxt; 
				h_old->nxt =temp;
				he->nxt = h_new;
				he = temp;				
				continue;
				//h2->nxt = he->nxt;
			}
			else if (he->nxt->start_hev == v2)
			{
				++i; 
				temp = he->nxt;	
				h_new->nxt = temp;
				he->nxt = h_old;
				he = temp;
				continue;
				//h1->nxt = he->nxt;
			}
			he = he->nxt;
		}

		lp_old->lhe = h_old;					// update the linking half_edge, notification: 1<->2 exchange
		f_old->fsolid->eenum += 1;
		f_old->fsolid->fnum += 1;

		return lp_new;
	}

	Face *Euler_oper::kemr(Vertex *v1, Vertex *v2, Loop *lp1)// v1 belongs to outer loop,
		// v2 belongs to inner loop
	{
		Half_edge *he = lp1->lhe;
		Loop *lp2 = new Loop;

		lp2->lface = lp1->lface;	// Loop.lface
		loop_list.push_back(lp2);

		// insert lp2 into inner Loop two-way linked-list of Face's
		// Loop.prel and Loop.nextl
		(*lp1->lface).insert_inlp_list(lp2);//	insert_inlplist(lp1->lface, lp2);

		// seperate two loops
		Half_edge *h1, *h2;
		while (true)
		{
			h1 = he->nxt;
			h2 = (h1->edg->he1 != h1) ? h1->edg->he1 : h1->edg->he2; // another half edge of he

			if (h1->start_hev == v1&&h2->start_hev == v2)
			{
				he->nxt = h2->nxt;
				he = h1->nxt;
				while (true)
				{
					if (he->nxt == h2)
					{
						he->nxt = h1->nxt;
						break;
					}
					he = he->nxt;
				}
				break;
			}
			he = he->nxt;
		}

		lp1->lhe = h2->nxt;
		lp2->lhe = h1->nxt;// Loop.lhe

		// delete two edges
		delete(h1);
		delete(h2);

		lp1->lface->innum += 1;
		lp1->lface->fsolid->eenum -= 1;

		// return the face lp2(inner) belonging to
		return lp2->lface;
	}

	void Euler_oper::kfmrh(Face *fout, Face *fin)
	{
		Loop *lp = fin->outloop;
		lp->lface = fout; //lp->lhe; constant	

		// Loop.prel and Loop.nextl
		(*fout).insert_inlp_list(lp);

		// delete fin in face_list
		delFaceEle(fin);

		fout->fsolid->fnum -= 1;
		fout->fsolid->hnum += 1;
		fout->innum += 1;

		delete(fin);
	}

	void Euler_oper::sweep(Solid *s, Face *f, Vector &v, int length)
	{
		Loop *l = f->outloop;
		do
		{
			Half_edge *he = l->lhe;
			Vertex *firstv = he->start_hev;
			Point *Pfirstup =  &(v*length + (*firstv));

			Half_edge *he_newbulit = mev(firstv, Pfirstup, l);// 3 paras: vertex, vertex, loop

			Vertex *firstup = he_newbulit->end_hev;
			Vertex *prevup = firstup;

			he = he->nxt;
			Vertex *nextv = he->start_hev;

			Point *Pup = new Point();
			Vertex *up = new Vertex();
			while (nextv != firstv)
			{
				Pup = &(v*length + (*nextv));
				he_newbulit = mev(nextv, Pup, l);
				up = he_newbulit->end_hev;
				mef(up, prevup, l);

				prevup = up;
				he = he->nxt;
				nextv = he->start_hev;
			}
			mef(firstup, prevup, l);

			l = l->nextl;
		} while (l != f->outloop);		
	}

	void Euler_oper::delFaceEle(Face *f)
	{
		vector<Face *>::iterator it;

		// delete f from face_list
		for (it = face_list.begin(); (*it) != f; ++it);
		face_list.erase(it);

		f->nextf->prevf = f->prevf;
		f->prevf->nextf = f->nextf;
	}

	void Euler_oper::delLoopEle(Loop *lp)
	{
		vector<Loop *>::iterator it;

		// delete f from face_list
		for (it = loop_list.begin(); (*it) != lp; ++it);
		loop_list.erase(it);

		lp->nextl->prevl = lp->prevl;
		lp->prevl->nextl = lp->nextl;
	}

	void Euler_oper::delVertexEle(Vertex *v)
	{
		vector<Vertex *>::iterator it;

		// delete f from face_list
		for (it = vertex_list.begin(); (*it) != v; ++it);
		vertex_list.erase(it);

		//v->nextv->prev = v->prev;
		//v->prev->nextv = v->nextv;
	}
}