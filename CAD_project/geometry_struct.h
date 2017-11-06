/***************************************************************************************

Author: DXY

Date:2016-10

Compiler Version:vs2013

Operating System:WIN7 64BIT

Description: half-edge topology data structure

***************************************************************************************/

#pragma once
#include "topology_struct.h"

namespace HALF_EDGE
{
	class Point
	{
	public:
		int x, y, z;
		Point(){}
		Point(int p[3]) :x(p[0]), y(p[1]), z(p[2]){}
		Point(int a, int b, int c) :x(a), y(b), z(c){}
	};

	class Vector
	{
	public:
		int x, y, z;

		Vector(){}
		Vector(int a, int b, int c) :x(a), y(b), z(c){}

		Vector operator+(Vector &v)
		{
			return Vector(x + v.x, y + v.y, z + v.z);
		}

		Point operator+(Vertex &v)
		{
			return Point(x + v.x, y + v.y, z + v.z);
		}


		Vector operator*(int &length)
		{
			return Vector(x*length, y*length, z*length);
		}
	};
}
