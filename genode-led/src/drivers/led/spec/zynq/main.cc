/*
 * \brief  Non-Generic LED Driver for Zybo
 * \author Johannes Fischer
 * \date   2018-12-15
 */

#include <led_session/led_session.h>
#include <base/attached_rom_dataspace.h>
//#include <dataspace/client.h>

#include <base/component.h>
#include <base/log.h>
#include <base/heap.h>
#include <root/component.h>
#include <base/rpc_server.h>

#include "driver.h"

namespace Led {
	struct Session_component;
    struct Root_component;
    struct Main;
};


struct Led::Session_component : Genode::Rpc_object<Session>
{
	private:

		Driver &_driver;

	public:
		Session_component(Driver &driver)
		: _driver(driver) {}

		virtual void enable(int led_no) {
          Genode::log("LED is enabled");
			_driver.enable(led_no);
		}

		virtual void disable(int led_no) {
          Genode::log("LED is disabled");
			_driver.disable(led_no);
		}
};


class Led::Root_component
  :
    public Genode::Root_component<Led::Session_component>
{
	private:

		Driver &_driver;

	protected:

		Session_component *_create_session(const char *args)
		{
			Genode::size_t ram_quota = Genode::Arg_string::find_arg(args, "ram_quota").ulong_value(0);

			if (ram_quota < sizeof(Session_component)) {
                Genode::warning("Insufficient dontated ram_quota (", ram_quota, " bytes), "
                                "require ", sizeof(Session_component), " bytes");
			}

			return new (md_alloc()) Session_component(_driver);
		}

	public:

		Root_component(Genode::Entrypoint &ep,
                       Genode::Allocator &alloc,
                       Driver &driver)
        :
            Genode::Root_component<Led::Session_component>(ep, alloc),
		    _driver(driver)
        {
			Genode::log("creating root component");
		}
};


struct Led::Main
{
	Genode::Env         &env;
	Genode::Attached_rom_dataspace config_rom { env, "config" };
	Genode::Sliced_heap sliced_heap { env.ram(), env.rm() };


	Main(Genode::Env &env)
	:
		env(env)
	{

        /*
         * Read config
         */
        Genode::addr_t addr;

        try {
            Genode::Xml_node led_node = config_rom.xml().sub_node("led");
			led_node.attribute("addr").value(&addr);
            Genode::log("LED with memory io address: ", Genode::Hex(addr));
        }
        catch (Genode::Xml_node::Nonexistent_sub_node) {
            Genode::warning("No LED config");
        }

        /*
         * Create Driver
         */
        Led::Driver &driver = Led::Driver::factory(env, addr);
		/*
		 * Announce service
		 */
        static Led::Root_component root(env.ep(), sliced_heap, driver);
		env.parent().announce(env.ep().manage(root));
	}
};


Genode::size_t Component::stack_size() { return 64*1024; }


void Component::construct(Genode::Env &env)
{
	static Led::Main main(env);
}
