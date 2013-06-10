// ================================================================================================
#ifndef AC_TLM_RAND_H_
#define AC_TLM_RAND_H_

// ================================================================================================
// BIBLIOTECAS
// ================================================================================================
#include <systemc>
#include "ac_tlm_protocol.H"

// ================================================================================================
// DEFINICOES
// ================================================================================================
using tlm::tlm_transport_if;

//#define LENGTH 624
//#define BITMASK_32 0xffffffff
//#define BITPOW_31 0x80000000

// ================================================================================================

//#define DEBUG

/// Namespace to isolate memory from ArchC
namespace user
{

/// A TLM memory
class ac_tlm_rand :
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

	ac_tlm_rsp_status readm( uint32_t & );

	ac_tlm_rsp transport( const ac_tlm_req &request ) {

	ac_tlm_rsp response;

	switch( request.type ) {
	case READ :     // Packet is a READ one
	  response.status = readm( response.data );
	  #ifdef DEBUG  // Turn it on to print transport level messages
	cout << "Trying to get a random number ";
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
   * 
   *
   */
 	ac_tlm_rand( sc_module_name module_name);

private:
	uint *mt;
	uint idx=0;
	static const uint LENGTH=624;
	static const uint BITMASK_32=0xffffffff;
	static const uint BITPOW_31=1<<31;

	void setSeed(uint);
	uint getRandomNumber();
	void gen();

};
};

// ================================================================================================

#endif
// ================================================================================================
