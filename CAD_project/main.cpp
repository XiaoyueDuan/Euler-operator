/***************************************************************************************

Author: DXY

Date:2016-10

Compiler Version:vs2013

Operating System:WIN7 64BIT

Description: half-edge topology data structure

***************************************************************************************/

#include "topology_struct.h"
#include "Euler_operator.h"
#include "print.h"

using namespace std;
using namespace HALF_EDGE;

void square_triangle_euler(string &filename);
void declineing_sweep(string &filename);

int main()
{
	string filename1 = "../result/square_triangle_euler.brp";
	square_triangle_euler(filename1);

	string filename2 = "../result/declineing_sweep.brp";
	declineing_sweep(filename2);

	return 0;
}

void square_triangle_euler(string &filename)
{
	Vertex *v0 = new Vertex();

	Point *p0 = new Point(0, 0, 0);
	Point *p1 = new Point(8, 0, 0);
	Point *p2 = new Point(8, 0, 8);
	Point *p3 = new Point(0, 0, 8);

	Point *p4 = new Point(0, 6, 0);
	Point *p5 = new Point(8, 6, 0);
	Point *p6 = new Point(8, 6, 8);
	Point *p7 = new Point(0, 6, 8);

	Point *p8 = new Point(2, 0, 1);
	Point *p9 = new Point(6, 0, 1);
	Point *p10 = new Point(6, 0, 3);
	Point *p11 = new Point(2, 0, 3);

	Point *p12 = new Point(2, 6, 1);
	Point *p13 = new Point(6, 6, 1);
	Point *p14 = new Point(6, 6, 3);
	Point *p15 = new Point(2, 6, 3);

	Euler_oper eoper;
	Printer *printer = new Printer();
	Half_edge *he;

	Solid *solid = eoper.mvsf(v0, p0);
	Loop *lp3210 = solid->sface->outloop;
	he = eoper.mev(v0, p1, lp3210);	Vertex *v1 = he->end_hev;
	he = eoper.mev(v1, p2, lp3210);	Vertex *v2 = he->end_hev;
	he = eoper.mev(v2, p3, lp3210);	Vertex *v3 = he->end_hev;
	Loop *lp0123 = eoper.mef(v3, v0, lp3210);

	he = eoper.mev(v0, p4, lp3210); Vertex *v4 = he->end_hev;
	he = eoper.mev(v1, p5, lp3210); Vertex *v5 = he->end_hev;
	he = eoper.mev(v2, p6, lp3210); Vertex *v6 = he->end_hev;
	he = eoper.mev(v3, p7, lp3210); Vertex *v7 = he->end_hev;

	eoper.mef(v4, v5, lp3210);
	eoper.mef(v5, v6, lp3210);
	eoper.mef(v6, v7, lp3210);
	eoper.mef(v7, v4, lp3210);	// a cube is constructed already
	printer->printAll(&eoper, &filename);
	Loop *lp7654 = lp3210;

	// add a hollow cude
	he = eoper.mev(v0, p8, lp0123); Vertex *v8 = he->end_hev;
	he = eoper.mev(v8, p9, lp0123); Vertex *v9 = he->end_hev;
	he = eoper.mev(v9, p10, lp0123); Vertex *v10 = he->end_hev;
	he = eoper.mev(v10, p11, lp0123); Vertex *v11 = he->end_hev;
	Loop * lp8_9_10_11 = eoper.mef(v11, v8, lp0123);
	Face *f0123 = eoper.kemr(v0, v8, lp0123);

	printer->printAll(&eoper, &filename);

	he = eoper.mev(v8, p12, lp8_9_10_11); Vertex *v12 = he->end_hev;
	he = eoper.mev(v9, p13, lp8_9_10_11); Vertex *v13 = he->end_hev;
	he = eoper.mev(v10, p14, lp8_9_10_11);	Vertex *v14 = he->end_hev;
	he = eoper.mev(v11, p15, lp8_9_10_11);	Vertex *v15 = he->end_hev;

	eoper.mef(v12, v15, lp8_9_10_11);
	eoper.mef(v15, v14, lp8_9_10_11);
	eoper.mef(v14, v13, lp8_9_10_11);
	eoper.mef(v13, v12, lp8_9_10_11);
	Loop *lp12_13_14_15 = lp8_9_10_11;

	eoper.kfmrh(lp7654->lface, lp12_13_14_15->lface);

	// add a hollow trianlge
	Point *p16 = new Point(6, 0, 5);
	Point *p17 = new Point(6, 0, 7);
	Point *p18 = new Point(2, 0, 7);

	Point *p19 = new Point(6, 6, 5);
	Point *p20 = new Point(6, 6, 7);
	Point *p21 = new Point(2, 6, 7);

	lp0123 = f0123->outloop;
	he = eoper.mev(v0, p16, lp0123);	 Vertex *v16 = he->end_hev;
	he = eoper.mev(v16, p17, lp0123); Vertex *v17 = he->end_hev;
	he = eoper.mev(v17, p18, lp0123); Vertex *v18 = he->end_hev;
	Loop *lp16_17_18 = eoper.mef(v18, v16, lp0123);
	eoper.kemr(v0, v16, lp0123);

	he = eoper.mev(v16, p19, lp16_17_18); Vertex *v19 = he->end_hev;
	he = eoper.mev(v17, p20, lp16_17_18); Vertex *v20 = he->end_hev;
	he = eoper.mev(v18, p21, lp16_17_18); Vertex *v21 = he->end_hev;

	eoper.mef(v19, v21, lp16_17_18);
	eoper.mef(v21, v20, lp16_17_18);
	eoper.mef(v20, v19, lp16_17_18);
	Loop *lp19_20_21 = lp16_17_18;
	eoper.kfmrh(lp7654->lface, lp19_20_21->lface);

	printer->printAll(&eoper, &filename);
}

void declineing_sweep(string &filename)
{
	Point *p0 = new Point(0, 0, 0);
	Point *p1 = new Point(8, 0, 0);
	Point *p2 = new Point(8, 0, 8);
	Point *p3 = new Point(0, 0, 8);

	Vertex *v0 = new Vertex();

	Euler_oper eoper;
	Printer *printer = new Printer();
	Half_edge *he;

	Solid *solid = eoper.mvsf(v0, p0);
	Loop *lp3210 = solid->sface->outloop;

	he = eoper.mev(v0, p1, lp3210);		Vertex *v1 = he->end_hev;
	he = eoper.mev(v1, p2, lp3210);		Vertex *v2 = he->end_hev;
	he = eoper.mev(v2, p3, lp3210);		Vertex *v3 = he->end_hev;
	Loop *lp0123 = eoper.mef(v3, v0, lp3210);

	Point *p8 = new Point(2, 0, 1);
	Point *p9 = new Point(6, 0, 1);
	Point *p10 = new Point(6, 0, 3);
	Point *p11 = new Point(2, 0, 3);

	// add a hollow cude
	he = eoper.mev(v0, p8, lp0123);	Vertex *v8 = he->end_hev;
	he = eoper.mev(v8, p9, lp0123);	Vertex *v9 = he->end_hev;
	he = eoper.mev(v9, p10, lp0123);	Vertex *v10 = he->end_hev;
	he = eoper.mev(v10, p11, lp0123);	Vertex *v11 = he->end_hev;
	Loop * lp8_9_10_11 = eoper.mef(v11, v8, lp0123);
	Face *f0123 = eoper.kemr(v0, v8, lp0123);

	eoper.kfmrh(lp3210->lface, lp8_9_10_11->lface);

	// add a hollow trianlge
	Point *p16 = new Point(6, 0, 5);
	Point *p17 = new Point(6, 0, 7);
	Point *p18 = new Point(2, 0, 7);

	he = eoper.mev(v0, p16, lp0123); Vertex *v16 = he->end_hev;
	he = eoper.mev(v16, p17, lp0123); Vertex *v17 = he->end_hev;
	he = eoper.mev(v17, p18, lp0123); Vertex *v18 = he->end_hev;
	Loop *lp16_17_18 = eoper.mef(v18, v16, lp0123);
	Face *f16_17_18 = eoper.kemr(v0, v16, lp0123);

	eoper.kfmrh(lp3210->lface, lp16_17_18->lface);
	//printer->printAll(&eoper, &filename);

	Vector *vector = new Vector(1, 3, 0);
	eoper.sweep(solid, lp3210->lface, *vector, 1);

	printer->printAll(&eoper, &filename);
}
