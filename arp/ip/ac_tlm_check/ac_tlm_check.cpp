//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "ac_tlm_check.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::ac_tlm_check;

/// Constructor
ac_tlm_check::ac_tlm_check( sc_module_name module_name) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

    key = 4321;
}

ac_tlm_rsp_status ac_tlm_check::readm( uint32_t a, uint32_t &d )
{
  if (a == key)
        d = 1;
  else
        d = 0;

    return SUCCESS;
}
