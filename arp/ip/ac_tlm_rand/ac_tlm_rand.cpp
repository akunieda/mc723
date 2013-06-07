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

}

ac_tlm_rsp_status ac_tlm_rand::readm( uint32_t &d )
{
	srand(time(NULL));
	int rand_number = rand();
	*((uint32_t *) &d) = *((uint32_t *) &rand_number);

	return SUCCESS;
}
