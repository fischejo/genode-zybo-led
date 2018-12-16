/*
 * \brief  Non-Generic LED Driver for Zybo
 * \author Johannes Fischer
 * \date   2018-12-15
 */

#ifndef _INCLUDE__LED_SESSION_H__CLIENT_H_
#define _INCLUDE__LED_SESSION_H__CLIENT_H_

#include <led_session/led_session.h>
#include <base/rpc_client.h>
#include <base/log.h>


namespace Led {
  struct Session_client;
}

struct Led::Session_client : Genode::Rpc_client<Session>
{
  
  Session_client(Genode::Capability<Session> cap)
    : Genode::Rpc_client<Session>(cap) { }
  
  
  void enable(int led_no) {
    call<Rpc_led_enable>(led_no);
  }

  void disable(int led_no) {
    call<Rpc_led_disable>(led_no);
  }

};


#endif /* _INCLUDE__LED_SESSION_H__CLIENT_H_ */
