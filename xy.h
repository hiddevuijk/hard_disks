#ifndef GUARD_XY_H
#define GUARD_XY_H

#include <math.h>

class XY {
public:
	XY(double xx, double yy): x(xx), y(yy) {}
	XY(): x(0.), y(0.) {}
	double x,y;
	void periodic_bc(double L);
};

namespace xy {

double dist2(const XY &c1, const XY &c2);
double dist2_pbc(const XY &c1, const XY &c2, double L);

double dist2_sq(const XY &c1, const XY &c2);
double dist2_sq_pbc(const XY &c1, const XY &c2, double L);


double dot(const XY &c1, const XY &c2);
double cross(const XY &c1, const XY &c2);

};


#endif
