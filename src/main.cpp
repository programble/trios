#include <types.h>
#include <multiboot.h>

extern "C"
void main(multiboot_header *multiboot, u32 magic)
{
    *(u8*)0xB8000 = multiboot->bootloader_name[0];
}
