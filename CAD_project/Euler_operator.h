/***************************************************************************************

Author: DXY

Date:2016-10

Compiler Version:vs2013

Operating System:WIN7 64BIT

Description: half-edge topology data structure

***************************************************************************************/

#pragma once

#include "topology_struct.h"
#include "geometry_struct.h"
#include <vector>

using namespace std;

namespace HALF_EDGE
{
	class Euler_oper
	{
	private:
		vector<Solid *> solid_list;
		vector<Face *> face_list;
		vector<Loop *> loop_list;
		vector<Vertex *> vertex_list;

		void delFaceEle(Face *f);
		void delLoopEle(Loop *lp);
		void delVertexEle(Vertex *v);

	public:
		Euler_oper()
		{
			solid_list.clear();
			face_list.clear();
			loop_list.clear();
			vertex_list.clear();
		}

		Solid *mvsf(Vertex *&v, Point *p);					// make a new vertex, solid and face
		Half_edge *mev(Vertex *v1, Point *p, Loop *lp);	// make a new vertex and edge
		Loop *mef(Vertex *v1, Vertex *v2, Loop *lp1); // make edge and face & loop
		Face *kemr(Vertex *v1, Vertex *v2, Loop *lp1);// kill one edge and make a inner loop
		void kfmrh(Face *out, Face *in);		// kill inner face and make a new inner ring, hole
												// OR concatenate two solid

		void sweep(Solid *s, Face *f, Vector &v, int length);

		vector<Solid *> getSolidList()
		{
			return solid_list;
		}

		vector<Face *> getFaceList()
		{
			return face_list;
		}

		vector<Loop *> getLoopList()
		{
			return loop_list;
		}

		vector<Vertex *> getVertexList()
		{
			return vertex_list;
		}
	};
}