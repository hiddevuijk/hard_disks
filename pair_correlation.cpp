
#include "pair_correlation.h"



PairCorrelation_2d::PairCorrelation_2d(unsigned int NN, double LL, 
		unsigned int Nbinn, double bss) :
			N(NN), L(LL),  Nbin(Nbinn),
			bs(bss), bins(Nbinn), pc(Nbinn,0.), Nsamp(0),is_normalized(false)
{

	// set mid points of the bins
	for(unsigned int i=0;i<Nbin;++i)
		bins[i] = (0.5+i)*bs;
}			

void PairCorrelation_2d::sample( const std::vector<XY> &positions )
{

	// only sample before normalization 
	if(is_normalized){
		// quit
	}

	double d;

	for(unsigned int i=0;i<N;++i) {
		for(unsigned int j=i+1;j<N;++j) {
			d = xy::dist2_pbc(positions[i],positions[j],L);
			if(d< 1.*L) pc[ (int)(d/bs) ] += 2.;
		}
	}

	++Nsamp;

}
void PairCorrelation_2d::normalize()
{
	const double pi = 4*std::atan(1.);
	// number of ideal gas particles in bin.
	double Nid;
	// bulk density
	double rhob = N/(L*L);
	for(unsigned int i=0;i<Nbin;++i ) {
		Nid = 2*pi*bs*bins[i]*rhob;
		pc[i] /= N*Nid*Nsamp; 

	}	

	is_normalized = true;
}


void PairCorrelation_2d::write(std::ostream & out)
{
	for(unsigned int i=0;i<Nbin;++i) {
		out << bins[i] << ' ';
		out << pc[i] << '\n';
	}

}


void PairCorrelation_2d::write(std::string outname)
{

	std::ofstream out;
	out.open(outname);
	for(unsigned int i=0;i<Nbin;++i) {
		out << bins[i] << ' ' << pc[i];
		if( i < Nbin-1) out <<  '\n';
	}
	out.close();
	
}
