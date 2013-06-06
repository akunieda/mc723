/*
Grupo 31
Alexandre Luiz Brisighello Filho
Alexandre Nobuo Kunieda
Bruno Gustavo Salomão Agostini

router.h
*/

//////////////////////////////////////////////////////////////////////////////

#ifndef ROUTER_H_
#define ROUTER_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
// Memory
#include "ac_tlm_mem.h"
// Lock
#include "ac_tlm_lock.h"

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

//#define DEBUG

/// Namespace to isolate memory from ArchC
namespace user
{

/// A TLM memory
class router_t :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;

  /**
   * Default constructor.
   *
   * @param *mem Memory to be attached to this router
   * @param *lock Lock to be attached to this router
   *
   */
  router_t( sc_module_name module_name, ac_tlm_mem *mem, ac_tlm_lock *lock );

  /**
   * Implementation of TLM transport method that
   * handle packets of the protocol doing apropriate actions.
   * This method must be implemented (required by SystemC TLM).
   * @param request is a received request packet
   * @return A response packet to be send
  */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {
    if ( request.addr == 0xFFFFFFFF )
      return lock->transport(request);
    else
      return mem->transport(request);
  }

private:
  ac_tlm_transport_if *mem, *lock;

};

};

#endif //ROUTER_H_
