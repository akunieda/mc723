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

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

//#define DEBUG

/// Namespace to isolate memory from ArchC
namespace user
{

/// A TLM memory
class router :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;


  /**
   * Default constructor.
   *
   * @param k Memory size in kilowords.
   *
   */
  router( sc_module_name module_name);

  /**
   * Default destructor.
   */
  ~router();

private:

};

};

#endif //ROUTER_H_
