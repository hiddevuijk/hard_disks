#ifndef GUARD_SYSTEM_H
#define GUARD_SYSTEM_H 

#include <iostream>
#include <vector>

#include "xy.h"
#include "randuni.h"

class System{
public:

	System (unsigned int  N, double L,double deltaa);

	void move();
	void initialize();

	int get_Naccepted() const {return Naccepted;}
	int get_Nmoves() const {return Nmoves;}
	int get_fraction_accepted_moves() const 
		{ return ( (double) Naccepted)/( (double) Nmoves); }
	const std::vector<XY>& get_positions() const	
		{ return positions;}

	void pbc();
private:

	// system params
	unsigned int N; // number of disks
	double L;	// system size

	// max step size
	double delta;
	unsigned int Nmoves;
	unsigned int Naccepted;	

	std::vector<XY> positions;


	// use for trail moves
	XY new_position;
	// index of trial disk
	unsigned int index;	
	bool overlap;
};

void System::pbc()
{
	for(unsigned int i=0;i<N;++i)
		positions[i].pbc(L);
}

System::System(unsigned int NN, double LL, double dd)
: N(NN), L(LL), delta(dd), Nmoves(0), Naccepted(0), positions(NN) 
{}

void System::move() 
{
		index = rand()%positions.size();	

		new_position.x = positions[index].x + (0.5 - randuni() )*2*delta;
		new_position.y = positions[index].y + (0.5 - randuni() )*2*delta;

		overlap = false;	
		for(unsigned int i=0;i<positions.size(); ++i) {
			if(i != index and 
				xy::dist2_sq_pbc(new_position,positions[i],L) < 1.) {
					overlap = true;
			}
			if(overlap) break;
		}

		if( !overlap ) {
			positions[index] = new_position;
			++Naccepted;
		}
		++Nmoves;
}

void System::initialize()
{


	unsigned int p_per_dim = floor(L);
	int k = 0;
	std::vector<XY> vertices(p_per_dim*p_per_dim);
	std::vector<unsigned int> indices(p_per_dim*p_per_dim);	
	for(unsigned int i=0;i<p_per_dim; ++i) {
		for(unsigned int j=0;j<p_per_dim; ++j) {
			indices[ i*p_per_dim + j] = i*p_per_dim + j;	
			vertices[k].x = 0.5 + i;
			vertices[k].y = 0.5 + j;
			++k;
		}
	}

	// randomize indices
	unsigned int temp;
	unsigned int j;
	for(unsigned int i=0;i<indices.size()-1;++i ) {
		j = i + ( rand() % (indices.size() - i) );
		temp = indices[i];
		indices[i] = indices[j];
		indices[j] = temp;
	}
	// assign positions
	for(unsigned int i=0; i<N; ++i) {
		positions[i] = vertices[indices[i]];
	}

}
#endif
