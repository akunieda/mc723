/**
 * @file      ac_tlm_lock.h
 * @author    Bruno de Carvalho Albertini
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Defines a ac_tlm memory.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef AC_TLM_LOCK_H_
#define AC_TLM_LOCK_H_

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
class ac_tlm_lock :
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
  ac_tlm_rsp_status writem( uint32_t & );

  ac_tlm_rsp transport( const ac_tlm_req &request ) {

    ac_tlm_rsp response;

    switch( request.type ) {
    case READ :     // Packet is a READ one
      response.status = readm( response.data );
      #ifdef DEBUG  // Turn it on to print transport level messages
    cout << "Trying to get LOCK ";
    cout << response.data << endl;
      #endif
      break;

    case WRITE : 
      response.status = writem( response.data );
      #ifdef DEBUG  // Turn it on to print transport level messages
    cout << "Releasing LOCK ";
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
   * @param k Memory size in kilowords.
   *
   */
  ac_tlm_lock( sc_module_name module_name);



private:
  uint32_t memory;

};

};

#endif //ac_tlm_lock_H_
