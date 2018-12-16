/*
 * \brief  Non-Generic LED Driver for Zybo
 * \author Johannes Fischer
 * \date   2018-12-15
 */

#ifndef _INCLUDE__LED_SESSION__CONNECTION_H_
#define _INCLUDE__LED_SESSION__CONNECTION_H_

#include <led_session/client.h>
#include <base/connection.h>

namespace Led {
  struct Connection;
}

struct Led::Connection : Genode::Connection<Session>, Session_client
{
 Connection(Genode::Env &env)
   : Genode::Connection<Session>(session(env.parent(), "ram_quota=8K")),
    Session_client(cap()) { }
};


#endif /* _INCLUDE__LED_SESSION__CONNECTION_H_ */
