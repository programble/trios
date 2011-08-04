#include <system.h>
#include <multiboot.h>
#include <devices/output/text/serial.h>
#include <devices/output/text.h>

using namespace Devices::Output::Text;

extern "C"
noreturn main(multiboot_header *multiboot, u32 magic)
{
    Devices::Output::Text::Serial::init();
    panic("the kernel is a lie!");
}
