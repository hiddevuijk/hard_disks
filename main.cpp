
#include "xy.h"
#include "init.h"
#include "mc_hardDisk.h"
#include "pair_correlation.h"
#include "configFile.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{ 

	Config config("input.txt");

	unsigned int N = config.get_parameter<unsigned int>("N");
	double L = config.get_parameter<double>("L");

	// mc params
	double d = config.get_parameter<double>("d");
	unsigned int multiplier = config.get_parameter<unsigned int>("multiplier");
	unsigned int T_init = config.get_parameter<unsigned int>("T_init");
	unsigned int T = config.get_parameter<unsigned int>("T");
	unsigned int T_sample = config.get_parameter<unsigned int>("T_sample");
	unsigned int T_print = config.get_parameter<unsigned int>("T_print");


	// pc params
	unsigned int Nbin = config.get_parameter<unsigned int>("Nbin");
	double bs = 1.*L/Nbin;
	
	PairCorrelation_2d pc(N,L,Nbin,bs);

	vector<XY> positions(N);
	init_particles(positions,N,L);	

	XY new_position;

	MC_HARD_DISK mc_harddisks(d);
	
	for(unsigned int ti = 0;ti<(T_init + T)*multiplier; ++ti) {
		if(  (ti% T_print) == 0) cout<< T+T_init << '\t' << ti/multiplier << endl;
		//if( ti%(multiplier*10) == 0) cout << T+T_init << '\t' << ti/multiplier << endl;
		mc_harddisks.move(positions, L);
		
		//sample pair correlation
		if( (ti > T_init) && ( (ti%T_sample) == 0) ) {
			pc.sample(positions);
		}

	}

	cout << mc_harddisks.get_Naccepted() << endl;
	cout << mc_harddisks.get_Nmoves() << endl;
	cout << ( (double) mc_harddisks.get_Naccepted() ) / 
			( (double) mc_harddisks.get_Nmoves() ) << endl;
	// normalize pair correlation function
	pc.normalize();

	// write pair correlation function
	pc.write("pc.dat");	

	for(unsigned int i=0;i<N;++i) 
		positions[i].periodic_bc(L);

	ofstream xyout;
	xyout.open("config.dat");

	// write x y values
	for(unsigned int i=0;i<N;++i) { 
		xyout << positions[i].x << ' ';
		xyout << positions[i].y ;
		if(i<Nbin-1) xyout << '\n';
	}
	
	xyout.close();
	return 0;
}

