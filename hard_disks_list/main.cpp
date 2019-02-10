
#include "xy.h"
#include "init.h"
//#include "mc_hardDisk.h"
#include "system.h"
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
	double rn = config.get_parameter<double>("rn");
	unsigned int N = config.get_parameter<unsigned int>("N");
	double L = config.get_parameter<double>("L");

	// mc params
	double d = config.get_parameter<double>("d");
	unsigned int t_unit = config.get_parameter<unsigned int>("multiplier");
	unsigned int T_init = config.get_parameter<unsigned int>("T_init");
	unsigned int T = config.get_parameter<unsigned int>("T");
	unsigned int T_sample = config.get_parameter<unsigned int>("T_sample");
	unsigned int T_print = config.get_parameter<unsigned int>("T_print");


	// pc params
	unsigned int Nbin = config.get_parameter<unsigned int>("Nbin");
	double bs = 1.*L/Nbin;
	
	PairCorrelation_2d pc(N,L,Nbin,bs);

	System system(N,L,d);
	system.initialize();
	system.neighbour_update(rn);

	for(unsigned int ti = 0;ti<T_init; ++ti) {
		if( (ti%T_print) ==0){
			cout << (T_init+T) << '\t' << ti << endl;
			cout << ( (double) system.get_Naccepted() ) /
			( (double) system.get_Nmoves() ) << endl;

			cout << endl;
		}
		for( unsigned int tti=0;tti<t_unit;++tti) 
			system.move_nl();

		system.neighbour_update(rn);
	}	
	for(unsigned int ti = 0;ti<T; ++ti) {

		if( (ti%T_print) ==0) {
			cout << (T_init+T) << '\t' << ti+T_init << endl;
			cout << ( (double) system.get_Naccepted() ) /
			( (double) system.get_Nmoves() ) << endl;

			cout << endl;
		}

		for(unsigned int tti=0;tti<t_unit;++tti)
			system.move_nl();

		system.neighbour_update(rn);
		//sample pair correlation
		if(  (ti%T_sample) == 0 ) {
			pc.sample(system.get_positions());
		}

	}
	cout << ( (double) system.get_Naccepted() ) /
			( (double) system.get_Nmoves() ) << endl;

	// normalize pair correlation function
	pc.normalize();

	// write pair correlation function
	pc.write("pc.dat");	


	system.pbc();

	ofstream xyout;
	xyout.open("config.dat");

	// write x y values
	for(unsigned int i=0;i<N;++i) { 
		xyout << system.get_positions()[i].x << ' ';
		xyout << system.get_positions()[i].y ;
		if(i<N-1) xyout << '\n';
	}
	
	xyout.close();
	return 0;
}


