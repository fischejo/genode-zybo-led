/*
 * \brief  Non-Generic LED Driver for Zybo
 * \author Johannes Fischer
 * \date   2018-12-15
 */

#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <io_mem_session/connection.h>
#include <timer_session/connection.h>
#include <util/mmio.h>
#include "led.h"

namespace Led {
	using namespace Genode;
	class Driver;
}

class Led::Driver
{
    private:
        Led::Zynq_Led _led;


        
 Driver(Genode::Env &env, Genode::addr_t addr) :
        _led(env, addr)  
        {
            _led.write<Zynq_Led::GPIO_TRI>(0x00);
        }
    public:

        
        static Driver& factory(Genode::Env &env, Genode::addr_t addr);

        void enable(Genode::uint16_t led_no) {
          Genode::log("LED ", led_no, " is enabled");
          _led.write<Zynq_Led::GPIO_DATA>(_led.read<Zynq_Led::GPIO_DATA>() | (0x1 << led_no));
        }

        void disable(Genode::uint16_t led_no) {
          Genode::log("LED ", led_no ," is disabled");
          _led.write<Zynq_Led::GPIO_DATA>(_led.read<Zynq_Led::GPIO_DATA>() & ~(0x1 << led_no));
          //_led.write<Zynq_Led::GPIO_DATA>(0x0);
        }

};


Led::Driver& Led::Driver::factory(Genode::Env &env, Genode::addr_t addr)
{
    static Led::Driver driver(env, addr);
    return driver;
}

#endif /* _DRIVER_H_ */
