/*
 * \brief  Non-Generic LED Driver for Zybo
 * \author Johannes Fischer
 * \date   2018-12-16
 */


#ifndef _LED_H_
#define _LED_H_

/* Genode includes */
#include <base/attached_io_mem_dataspace.h>
#include <util/mmio.h>

namespace Led {
	using namespace Genode;
	class Zynq_Led;
}

struct Led::Zynq_Led :  Attached_io_mem_dataspace, Mmio
{
	Zynq_Led(Genode::Env &env, Genode::addr_t const mmio_base) :
		Genode::Attached_io_mem_dataspace(env, mmio_base, 0x32),
		Genode::Mmio((Genode::addr_t)local_addr<void>())
	{
        Genode::log("mmio_base: ", Genode::Hex(mmio_base));
    }

	~Zynq_Led()
	{ }

	/*
	 * Registers
	 */

	// GPIO_TRI configures the GPIO wether if input or output.
	// 0x0 = Output
	// 0x1 = Input
    struct GPIO_TRI  : Register<0x04, 32> {};
    
	// The first 4 bits controls the 4 LEDs on the board.
	// 0x0 = Off
	// 0x1 = on
	struct GPIO_DATA : Register<0x00, 32>
    {
		struct LED4	: Bitfield<3,1> {};
		struct LED3 : Bitfield<2,1> {};
		struct LED2 : Bitfield<1,1> {};
		struct LED1 : Bitfield<0,1> {};
	};

	// The second GPIO bank which is unused by this driver.
    struct GPIO2_TRI  : Register<0x08, 32> {};
	struct GPIO2_DATA : Register<0x0c, 32> {};
};

#endif // _LED_H_
