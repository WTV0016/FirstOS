#include "clib/low_level.h"
#include "clib/mem.h"
#include "clib/print/print.h"
#include "clib/descriptor_tables.h"

void main () {
    init_descriptor_tables();
    
    clear_screen();   
    print("Hello World!\n");
    asm volatile ("int $0x3");
}
