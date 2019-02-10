
#include "init.h"


//CHANGE: why is N here??
void init_particles(std::vector<XY> & p,unsigned int N, double L)
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
		p[i] = vertices[indices[i]];
	}

} 




