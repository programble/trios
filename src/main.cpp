#include <system.h>
#include <multiboot.h>
#include <devices/output/text.h>
#include <devices/output/text/serial.h>
#include <devices/output/text/console.h>

using namespace Devices::Output::Text;

extern "C"
noreturn main(multiboot_header *multiboot, u32 magic)
{
    assert(magic == MULTIBOOT_BOOTLOADER_MAGIC, "This bootloader is not magical enough!"); // No one will ever see this message anyway...

    Devices::Output::Text::Serial::init();
    Devices::Output::Text::Console::init();

    print("booted with ");
    print(multiboot->bootloader_name);
    print("\n");

    panic("the kernel is a lie!");
}
