
#include "mc_hardDisk.h"


void MC_HARD_DISK::move(std::vector<XY> &positions, double L) 
{
		index = rand()%positions.size();	

		new_position.x = positions[index].x + (0.5 - randuni() )*2*delta;
		new_position.y = positions[index].y + (0.5 - randuni() )*2*delta;
		overlap = false;	
		for(unsigned int i=0;i<positions.size(); ++i) {
			if(i != index) {
				if(xy::dist2_sq_pbc(new_position,positions[i],L) < 1.) {
					overlap = true;
				}
			}
			if(overlap) break;
		}

		if( !overlap ) {
			positions[index] = new_position;
			++Naccepted;
		}
		++Nmoves;
}

