/***************************************************************************************

Author: DXY

Date:2016-11

Compiler Version:vs2013

Operating System:WIN7 64BIT

Description: half-edge topology data structure

***************************************************************************************/

#pragma once
#include "Euler_operator.h"
#include <iostream>
#include <fstream>
#include <string>

namespace HALF_EDGE
{
	class Printer
	{
	private:
		void printFace(Face *f);
		void printLoop(Loop *lp);
		void printVertex(Vertex *v);

		int printAllFace(vector<Face *> &list,int startid);		// return value is the last index of face puls 1
		int printAllLoop(vector<Loop *> &list, int startid);	// return value is the last index of loop puls 1
		int printAllVertex(vector<Vertex *> &list, int startid);// return value is the last index of vertex puls 1
	public:
		void printAll(Euler_oper *, string *filename);
	};
}