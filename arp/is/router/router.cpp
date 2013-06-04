/*
Grupo 31
Alexandre Luiz Brisighello Filho
Alexandre Nobuo Kunieda
Bruno Gustavo Salomão Agostini

Router.cpp
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes
#include "router.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate router from ArchC
using user::router_t;
using user::ac_tlm_mem;

/// Constructor
router_t::router_t( sc_module_name module_name, ac_tlm_mem *mem, ac_tlm_lock *lock ) :
  sc_module( module_name ),
  target_export("iport"),
  mem( mem ),
  lock( lock )
{
    /// Binds target_export to the memory
    target_export( *this );
}
