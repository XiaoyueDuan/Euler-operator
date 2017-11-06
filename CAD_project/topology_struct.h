/***************************************************************************************

Author: DXY

Date:2016-10

Compiler Version:vs2013

Operating System:WIN7 64BIT

Description: half-edge topology data structure

***************************************************************************************/

#pragma once
#include <stdlib.h>  
#include <stdio.h>

namespace HALF_EDGE
{
	class Entity;
	class Solid ;
	class Face;
	class Loop;
	class Edge;
	class Half_edge;
	class Vertex;

	class Solid
	{
	public:
		int sid;				// the ID of solid
		int fnum, eenum, vnum, hnum, lpnum;// nums of faces, holes, edges and vertexs and loops(both in & out) belonging to the solid

		Face *sface;			// one of the face belonging to the solid		
		Solid *prevs, *nexts;	// previous and next solid		

		Solid() :
			sface(NULL), prevs(this), nexts(this),
			fnum(0), hnum(0), eenum(0), vnum(0), lpnum(0){}

		void insert_after(Solid *s);
	};

	class Face
	{
	public:
		int fid;				// the ID of face
		int innum;				// nums of inner loop in this face

		Solid *fsolid;			// the solid the face belonging to
		Loop *inloop, *outloop;	// one of the loop belonging to the face OR the outer loop??????????????????????????
		Face *prevf, *nextf;	// previous and next face

		Face() :innum(0), prevf(this), nextf(this),
			fsolid(NULL), inloop(NULL), outloop(NULL){}

		void insert_after(Face *f);
		void insert_inlp_list(Loop *lp);
	};

	class Loop
	{
	private:
		int nv;					// the number of Vertex belonging to this loop

	public:
		int lid;				// the ID of Loop

		Face *lface;			// the face the loop belongs to
		Half_edge *lhe;			// one of the half_edge belonging to the loop(random)
		Loop *prevl, *nextl;	// previous and next loop

		Loop() : prevl(this), nextl(this), lface(NULL), lhe(NULL){}

		void insert_after(Loop *lp);
		void resetNv();
		int getNv();
	};

	class Edge
	{
	public:
		//physical edge
		Half_edge *he1, *he2;	// two half edges belonging to the edge

		Edge() :he1(NULL), he2(NULL){}
	};

	class Half_edge
	{
	public:
		Loop *wloop;			// the loop half-edge belongs to
		Vertex *start_hev,*end_hev;// vertex at the start of the half-edge
		Edge *edg;				// the physical edge the half-edge belongs to	

		Half_edge *nxt;	// previous and next half-edge

		Half_edge() :
			wloop(NULL), start_hev(NULL), end_hev(NULL), edg(NULL), nxt(NULL){}
	};

	class Vertex
	{
	public:
		int vid;
		int x, y, z;
		Half_edge *vhe;			// one of the half-edge emanating from the vertex 
		//Vertex *prev, *nextv;	// previous and next vertex, those vertex are not required to have related relationship

		Vertex() :vhe(NULL){}
		Vertex(int a, int b, int c) :x(a), y(b), z(c), vhe(NULL){}
									//prev(this), nextv(this){}

		//void insert_after(Vertex *v);
	};
}

