#include <system.h>
#include <multiboot.h>

extern "C"
noreturn main(multiboot_header *multiboot, u32 magic)
{
    *(u8*)0xB8000 = multiboot->bootloader_name[0];
    panic("the kernel is a lie!");
}
