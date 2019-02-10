#ifndef GUARD_SYSTEM_H
#define GUARD_SYSTEM_H 

#include <iostream>
#include <vector>

#include "xy.h"
#include "randuni.h"

class System{
public:

	System (unsigned int  N, double L,double deltaa, int ncell_per_dim);

	void move();
	void move_cell();
	void initialize();

	int get_Naccepted() const {return Naccepted;}
	int get_Nmoves() const {return Nmoves;}
	int get_fraction_accepted_moves() const 
		{ return ( (double) Naccepted)/( (double) Nmoves); }
	const std::vector<XY>& get_positions() const	
		{ return positions;}

	void pbc();

	void assign_cell();

//private:

	// system params
	unsigned int N; // number of disks
	double L;	// system size

	// max step size
	double delta;
	unsigned int Nmoves;
	unsigned int Naccepted;	

	std::vector<XY> positions;
	void update_cells();
	// cell data
	unsigned int ncell_per_dim;
	double l; // cell size
	std::vector<unsigned int> particle_cell;
	std::vector<std::vector<unsigned int> > cell_neighbour;
	std::vector<std::vector<unsigned int> > cell_particles;
	std::vector<unsigned int> N_in_cell;	
	// use for trail moves
	XY new_position;
	// index of trial disk
	unsigned int index;	
	bool overlap;

	// get relative position of cell index
	int coll(int i,int n) {return i%n;}
	int row(int i,int n) { return (i- i%n)/n; }
	int right(int i,int n)
	{ 
		int c = coll(i,n);
		int r = row(i,n);
		return (c+1)%n + r*n ;
	}
	int left(int i,int n)
	{
		int c = coll(i,n);
		int r = row(i,n);
		if(c==0) return i+n-1;
		else return (c-1)%n + r*n;
	}
	int up(int i,int n)
	{
		int c = coll(i,n);
		int r = row(i,n);
		int u = c+n*(r+1);
		if(u<(n*n)) return u;
		else return coll(u,n);
	}
	int down(int i,int n) {
		int c = coll(i,n);
		int r = row(i,n);
		if(r>0) return n*(r-1)+c;
		else return c + n*(n-1);
	}
	int ru_d(int i,int n)
	{
		int r = row(up(i,n),n);	
		int c = coll(right(i,n),n);
		return n*r+ c;
	}

	int rd_d(int i, int n)
	{
		int r = row(down(i,n),n);
		int c = coll(right(i,n),n);
		return n*r+c;
	} 

	int lu_d(int i,int n)
	{
		int r = row(up(i,n),n);
		int c = coll(left(i,n),n);
		return n*r+c;
	}

	int ld_d(int i,int n)
	{
		int r = row(down(i,n),n);
		int c = coll(left(i,n),n);
		return n*r+c;
	}	
};

void System::update_cells()
{
	int cell_index;
	double r,c;
	XY temp;

	std::fill(N_in_cell.begin(),N_in_cell.end(),0);
	for(unsigned int i=0;i<N;++i) {
		temp = positions[i];
		temp.pbc(L);
		c = floor(temp.x/l);
		r = floor(temp.y/l);
		cell_index = ncell_per_dim*r+c;
		++N_in_cell[cell_index];	
		cell_particles[cell_index][ N_in_cell[cell_index]-1 ] = i;
		particle_cell[i] = cell_index;
	}

}

void System::pbc()
{
	for(unsigned int i=0;i<N;++i)
		positions[i].pbc(L);
}

System::System(unsigned int NN, double LL, double dd, int ncell_per_dimm)
: N(NN), L(LL), delta(dd), Nmoves(0), Naccepted(0),positions(NN),
	 ncell_per_dim(ncell_per_dimm), l(LL/ncell_per_dimm), particle_cell(NN),
	cell_neighbour(ncell_per_dim*ncell_per_dim,std::vector<unsigned int>(9)),
	cell_particles(ncell_per_dimm*ncell_per_dimm,std::vector<unsigned int>(N)),
	N_in_cell(ncell_per_dim*ncell_per_dimm,0)
{
	int ncell_tot = ncell_per_dim*ncell_per_dim;
	for(int i=0;i<ncell_tot; ++i) {
		cell_neighbour[i][0] = right(i,ncell_per_dim);	
		cell_neighbour[i][1] = left(i,ncell_per_dim);	
		cell_neighbour[i][2] = up(i,ncell_per_dim);	
		cell_neighbour[i][3] = down(i,ncell_per_dim);	

		cell_neighbour[i][4] = ru_d(i,ncell_per_dim);	
		cell_neighbour[i][5] = rd_d(i,ncell_per_dim);	
		cell_neighbour[i][6] = lu_d(i,ncell_per_dim);	
		cell_neighbour[i][7] = ld_d(i,ncell_per_dim);	
		
	}
	
}

void System::move_cell() 
{
		index = rand()%positions.size();	

		new_position.x = positions[index].x + (0.5 - randuni() )*2*delta;
		new_position.y = positions[index].y + (0.5 - randuni() )*2*delta;
		
		overlap = false;	
		unsigned int other_index;
		unsigned int nci;	// neighbour cell index
		unsigned int tci;	// this cell index
		tci = particle_cell[index];
		// loop over neigh. cells
			
		for(unsigned int ci=0;ci<9;++ci) { 
			// loop over particles in cell
			nci = cell_neighbour[tci][ci];	
			for(unsigned int pi=0;pi<N_in_cell[nci];++pi) {
				other_index = cell_particles[nci][pi];
				if(index == other_index) continue;
				if( xy::dist_sq_pbc(new_position,positions[other_index],L) < 1.) {
						overlap = true;
				}
				if(overlap) break;
			}
			if(overlap) break;
		}
	

		if( !overlap ) {
			positions[index] = new_position;
			++Naccepted;
		}
		++Nmoves;
}

void System::move() 
{
		index = rand()%positions.size();	

		new_position.x = positions[index].x + (0.5 - randuni() )*2*delta;
		new_position.y = positions[index].y + (0.5 - randuni() )*2*delta;

		overlap = false;	
		for(unsigned int i=0;i<positions.size(); ++i) {
			if(i != index and 
				xy::dist_sq_pbc(new_position,positions[i],L) < 1.) {
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
	update_cells();
}
#endif
