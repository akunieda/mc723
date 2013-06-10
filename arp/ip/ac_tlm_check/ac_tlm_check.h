//////////////////////////////////////////////////////////////////////////////

#ifndef AC_TLM_CHECK_H_
#define AC_TLM_CHECK_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

//#define DEBUG

/// Namespace to isolate memory from ArchC
namespace user
{

/// A TLM memory
class ac_tlm_check :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;

  /**
   * Implementation of TLM transport method that
   * handle packets of the protocol doing apropriate actions.
   * This method must be implemented (required by SystemC TLM).
   * @param request is a received request packet
   * @return A response packet to be send
  */

  ac_tlm_rsp_status readm( uint32_t, uint32_t & );

  ac_tlm_rsp transport( const ac_tlm_req &request ) {

    ac_tlm_rsp response;

    switch( request.type ) {
    case READ :     // Packet is a READ one
      response.status = readm( request.addr - (0xFFFFFFFD - 10000),
			       response.data );
      #ifdef DEBUG  // Turn it on to print transport level messages
    cout << "Is the key ";
    cout << request.addr - (0xFFFFFFFD - 10000);
    cout << " correct? ";
    cout << response.data << endl;
      #endif
      break;

    default :
      response.status = ERROR;
      break;
    }

    return response;
  }


  /**
   * Default constructor.
   *
   */
  ac_tlm_check( sc_module_name module_name);

private:
  uint32_t key;

};

};

#endif //AC_TLM_CHECK_H_
