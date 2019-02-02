#ifndef GUARD_MC_HARDDISK_H
#define GUARD_MC_HARDDISK_H 

#include <iostream>
#include <vector>

#include "xy.h"
#include "randuni.h"

class MC_HARD_DISK {
public:

	MC_HARD_DISK (double deltaa) : delta(deltaa)
		{ Nmoves = 0; Naccepted = 0;}

	void move(std::vector<XY> &positions, double L);


	int get_Naccepted() {return Naccepted;}
	int get_Nmoves() {return Nmoves;}
	int get_fraction_accepted_moves()
		{ return ( (double) Naccepted)/( (double) Nmoves); }
private:

	// max step size
	double delta;


	unsigned int Nmoves;
	unsigned int Naccepted;	

	// use for trail moves
	XY new_position;
	// index of trial disk
	unsigned int index;	

	bool overlap;
};


#endif
