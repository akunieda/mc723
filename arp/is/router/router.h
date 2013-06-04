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
   * @param *mem memory to be attached to this router
   *
   */
  router_t( sc_module_name module_name, ac_tlm_mem *mem );

  /**
   * Implementation of TLM transport method that
   * handle packets of the protocol doing apropriate actions.
   * This method must be implemented (required by SystemC TLM).
   * @param request is a received request packet
   * @return A response packet to be send
  */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {

    ac_tlm_rsp response;

    switch( request.type ) {
    case READ :     // Packet is a READ one
      #ifdef DEBUG  // Turn it on to print transport level messages
    cout << "Transport READ at 0x" << hex << request.addr << " value ";
    cout << response.data << endl;
      #endif
      response.status = mem->readm( request.addr , response.data );
      break;
    case WRITE:     // Packet is a WRITE
      #ifdef DEBUG
    cout << "Transport WRITE at 0x" << hex << request.addr << " value ";
    cout << request.data << endl;
      #endif
      response.status = mem->writem( request.addr , request.data );
      break;
    default :
      response.status = ERROR;
      break;
    }

    return response;
  }

private:
  ac_tlm_mem *mem;

};

};

#endif //ROUTER_H_
