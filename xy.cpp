#include "xy.h"


void XY::periodic_bc( double L)
{
	x -= L*floor(x/L);
	y -= L*floor(y/L);
}

// distance between c1 and c2
double xy::dist2(const XY &c1, const XY &c2)
{
	return std::sqrt( (c1.x - c2.x)*(c1.x - c2.x) +
			(c1.y - c2.y)*(c1.y - c2.y) );
}

// same as dist2, but with periodic boundary conditions
double xy::dist2_pbc(const XY &c1, const XY &c2, double L)
{
	XY d;
	d.x = c1.x - c2.x;
	d.y = c1.y - c2.y;

	d.x -= L*round(d.x/L);
	d.y -= L*round(d.y/L);

	return std::sqrt(d.x*d.x+d.y*d.y);
}


// returns the distance squared
double xy::dist2_sq(const XY &c1, const XY &c2)
{
	return  (c1.x - c2.x)*(c1.x - c2.x) +
			(c1.y - c2.y)*(c1.y - c2.y);
}

// same as dist2_sq, but with periodic boundary conditions
double xy::dist2_sq_pbc(const XY &c1, const XY &c2, double L)
{
	XY d;
	d.x = c1.x - c2.x;
	d.y = c1.y - c2.y;

	d.x -= L*round(d.x/L);
	d.y -= L*round(d.y/L);

	return d.x*d.x + d.y*d.y;
}


// dot produc between c1 and c2
double xy::dot(const XY &c1, const	XY &c2) 
{
	return c1.x*c2.x + c1.y*c2.y;
}

// the cross product, returns a double
double xy::cross(const XY &c1, const XY &c2) 
{
	return c1.x*c2.y - c1.y*c2.x;
}


