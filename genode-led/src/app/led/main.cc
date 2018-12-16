/*
 * \brief  Test client for the Hello RPC interface
 * \author Björn Döbel
 * \author Norman Feske
 * \date   2008-03-20
 */

/*
 * Copyright (C) 2008-2016 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#include <base/component.h>
#include <base/log.h>
#include <led_session/connection.h>
#include <base/sleep.h>
#include <timer_session/connection.h>


Genode::size_t Component::stack_size() { return 64*1024; }


void Component::construct(Genode::Env &env)
{
	Timer::Connection timer { env };
	Led::Connection led(env);

	while(true)
	{
		// enable LED1
		led.enable(0);
		timer.msleep(200);
		led.disable(0);

		// enable LED2
		led.enable(1);
		timer.msleep(200);
		led.disable(1);

		// enable LED3
		led.enable(2);
		timer.msleep(200);
		led.disable(2);	

		// enable LED4
		led.enable(3);
		timer.msleep(200);
		led.disable(3);

		// and back

		// enable LED3
		led.enable(2);
		timer.msleep(200);
		led.disable(2);	

		// enable LED2
		led.enable(1);
		timer.msleep(200);
		led.disable(1);

		// now lets start with LED1 again.
	}
}
