/*
 * \brief  Non-Generic LED Driver for Zybo
 * \author Johannes Fischer
 * \date   2018-12-15
 */

#ifndef _INCLUDE__LED_SESSION__LED_SESSION_H_
#define _INCLUDE__LED_SESSION__LED_SESSION_H_

#include <session/session.h>
#include <base/rpc.h>

namespace Led {
  struct Session;
}      

struct Led::Session : Genode::Session
{
	static const char *service_name() { return "Led"; }
  virtual void enable(int led_no) = 0;
  virtual void disable(int led_no) = 0;


  /*******************
   ** RPC interface **
   *******************/

  GENODE_RPC(Rpc_led_enable, void, enable, int);
  GENODE_RPC(Rpc_led_disable, void, disable, int);

  GENODE_RPC_INTERFACE(Rpc_led_enable, Rpc_led_disable);
};


#endif /* _INCLUDE__LED_SESSION__LED_SESSION_H_ */
