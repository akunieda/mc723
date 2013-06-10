//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "ac_tlm_rand.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::ac_tlm_rand;

void ac_tlm_rand::setSeed(uint seed){
	idx = 0;
	mt=new uint[LENGTH];
	mt[0]=seed;
	for(uint i=1;i<LENGTH;i++) mt[i]=(1812433253*(mt[i-1]^(mt[i-1]>>30))+i)&BITMASK_32;
}

void ac_tlm_rand::gen(){
	for(uint i=0;i<LENGTH;i++){
		uint y=(mt[i]&BITPOW_31)+(mt[(i+1)%LENGTH]&(BITPOW_31-1));
		mt[i]=mt[(i+397)%LENGTH]^(y>>1);
		if(y%2) mt[i]^=2567483615;
	}


	return;
}

uint ac_tlm_rand::getRandomNumber(){
	if(idx==0) gen();
	uint y=mt[idx];
	y^= y>>11;
	y^=(y<< 7)&2636928640;
	y^=(y<<15)&4022730752;
	y^= y>>18;
	idx=(idx+1)%LENGTH;

	return y;
}

/// Constructor
ac_tlm_rand::ac_tlm_rand( sc_module_name module_name) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

    srand(time(NULL));
    setSeed((uint)time(NULL));
}


ac_tlm_rsp_status ac_tlm_rand::readm( uint32_t &d )
{
	uint random = getRandomNumber();
	uint32_t rand_number;
	float rand_norm = ((float) random) / ((float) BITMASK_32);
	memcpy(&rand_number, &rand_norm, sizeof(uint32_t));
	d = __builtin_bswap32(rand_number);

	return SUCCESS;
}
