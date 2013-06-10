//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "ac_tlm_rand.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::ac_tlm_rand;

/// Constructor
ac_tlm_rand::ac_tlm_rand( sc_module_name module_name) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

    srand(time(NULL));
}

ac_tlm_rsp_status ac_tlm_rand::readm( uint32_t &d )
{
	uint32_t rand_number;
	float rand_norm = ((float) rand()) / ((float) RAND_MAX);
	memcpy(&rand_number, &rand_norm, sizeof(uint32_t));
	d = __builtin_bswap32(rand_number);

	return SUCCESS;
}
