/***************************************************************************************

Author: DXY

Date:2016-11

Compiler Version:vs2013

Operating System:WIN7 64BIT

Description: half-edge topology data structure

***************************************************************************************/
#include "print.h"

namespace HALF_EDGE
{
	void Printer::printFace(Face *f)
	{
		// print the index of outer loop of face
		//printf("%d", f->outloop->lid);
		cout << f->outloop->lid;

		// print the number of inner loops of face
		//printf(" %d", f->innum);
		cout << " " << f->innum;

		// print the index of inner loops belonging to the loop
		Loop *lp = f->inloop;
		if (lp != NULL)
		{
			do{
				//printf(" %d", lp->lid);
				cout << " " << lp->lid;
				lp = lp->nextl;
			} while (lp != f->outloop);// f->inloop
		}

		// print the index of solid which face belongs to
		//printf(" %d\n", f->fsolid->sid);
		cout << " " << f->fsolid->sid << endl;
	}

	void Printer::printLoop(Loop *lp)
	{
		// print index of vertexs belonging to the loop
		Half_edge *he = lp->lhe;

		//printf("%d", lp->getNv());
		cout << lp->getNv();

		Vertex *v;
		do{
			v = he->start_hev;
			//printf(" %d", v->vid);
			cout << " " << v->vid;
			he = he->nxt;
		} while (he != lp->lhe);
		//printf("\n");
		cout << endl;
	}

	void Printer::printVertex(Vertex *v)
	{
		//printf("%d %d %d\n", v->x, v->y, v->z);
		cout << v->x << ' ' << v->y << ' ' << v->z << endl;
	}

	int Printer::printAllFace(vector<Face *> &list, int startid)
	{
		int id = startid;
		for (int i = 0; i < list.size(); ++i,++id)
		{
			list[i]->fid = id;
			printFace(list[i]);
		}
		return id + 1;
	}

	int Printer::printAllLoop(vector<Loop *> &list, int startid)
	{
		int id = startid;
		for (int i = 0; i < list.size(); ++i,++id)
		{
			list[i]->lid = id;
			printLoop(list[i]);
		}
		return id + 1;
	}

	int Printer::printAllVertex(vector<Vertex *> &list, int startid)
	{
		int id = startid;
		for (int i = 0; i < list.size(); ++i, ++id)
		{
			list[i]->vid = id;
			printVertex(list[i]);
		}
		return (id + 1);
	}

	void Printer::printAll(Euler_oper *eoper, string *filename)
	{
		ofstream out(*filename);
		streambuf *coutbuf = cout.rdbuf();//save old buf
		cout.rdbuf(out.rdbuf());	//redirect cout to file

		cout << "BRP" << endl;
		//printf("%d %d %d %d\n", eoper->getVertexList().size(), eoper->getLoopList().size()
		//					  , eoper->getFaceList().size(), eoper->getSolidList().size());
		cout << eoper->getVertexList().size() << ' ' << eoper->getLoopList().size()<< ' ' 
			 << eoper->getFaceList().size()   << ' ' << eoper->getSolidList().size() << endl;

		printAllVertex(eoper->getVertexList(), 0);
		printAllLoop(eoper->getLoopList(), 0);
		printAllFace(eoper->getFaceList(), 0);

		cout.rdbuf(coutbuf); //reset to standard output again
	}
}