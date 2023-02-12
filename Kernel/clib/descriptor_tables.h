//http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
   unsigned int limit_low;           // The lower 16 bits of the limit.
   unsigned int base_low;            // The lower 16 bits of the base.
   unsigned char  base_middle;         // The next 8 bits of the base.
   unsigned char  access;              // Access flags, determine what ring this segment can be used in.
   unsigned char  granularity;
   unsigned char  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
   unsigned int limit;               // The upper 16 bits of all selector limits.
   unsigned long int base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

// A struct describing an interrupt gate.
struct idt_entry_struct
{
   unsigned int base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   unsigned int sel;                 // Kernel segment selector.
   unsigned char  always0;             // This must always be zero.
   unsigned char  flags;               // More flags. See documentation.
   unsigned int base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
   unsigned int limit;
   unsigned long int base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

// These extern directives let us access the addresses of our ASM ISR handlers.
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();


// Lets us access our ASM functions from our C code.
extern void gdt_flush(unsigned long int);
extern void idt_flush(unsigned long int);

// Internal function prototypes.
static void init_gdt();
static void init_idt();

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

static void idt_set_gate(unsigned char,unsigned long int,unsigned int,unsigned char);
static void gdt_set_gate(signed long int,unsigned long int,unsigned long int,unsigned char,unsigned char);

void init_descriptor_tables()
{
   // Initialise the global descriptor table.
   init_gdt();
   
   init_idt();
}

static void init_gdt()
{
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (unsigned long int)&gdt_entries;


   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   
   gdt_flush((unsigned long int)&gdt_ptr);

}

// Set the value of one GDT entry.
static void gdt_set_gate(signed long int num, unsigned long int base, unsigned long int limit, unsigned char access, unsigned char gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}

static void init_idt()
{
   idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
   idt_ptr.base  = (unsigned long int)&idt_entries;

   memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

   idt_set_gate( 0, (unsigned long int)isr0 , 0x08, 0x8E);
   idt_set_gate( 1, (unsigned long int)isr1 , 0x08, 0x8E);
   idt_set_gate( 2, (unsigned long int)isr2 , 0x08, 0x8E);
   idt_set_gate( 3, (unsigned long int)isr3 , 0x08, 0x8E);
   idt_set_gate( 4, (unsigned long int)isr4 , 0x08, 0x8E);
   idt_set_gate( 5, (unsigned long int)isr5 , 0x08, 0x8E);
   idt_set_gate( 6, (unsigned long int)isr6 , 0x08, 0x8E);
   idt_set_gate( 7, (unsigned long int)isr7 , 0x08, 0x8E);
   idt_set_gate( 8, (unsigned long int)isr8 , 0x08, 0x8E);
   idt_set_gate( 9, (unsigned long int)isr9 , 0x08, 0x8E);
   idt_set_gate( 10, (unsigned long int)isr10 , 0x08, 0x8E);
   idt_set_gate( 11, (unsigned long int)isr11 , 0x08, 0x8E);
   idt_set_gate( 12, (unsigned long int)isr12 , 0x08, 0x8E);
   idt_set_gate( 13, (unsigned long int)isr13 , 0x08, 0x8E);
   idt_set_gate( 14, (unsigned long int)isr14 , 0x08, 0x8E);
   idt_set_gate( 15, (unsigned long int)isr15 , 0x08, 0x8E);
   idt_set_gate( 16, (unsigned long int)isr16 , 0x08, 0x8E);
   idt_set_gate( 17, (unsigned long int)isr17 , 0x08, 0x8E);
   idt_set_gate( 18, (unsigned long int)isr18, 0x08, 0x8E);
   idt_set_gate( 19, (unsigned long int)isr19 , 0x08, 0x8E);
   idt_set_gate( 20, (unsigned long int)isr20 , 0x08, 0x8E);
   idt_set_gate( 21, (unsigned long int)isr21 , 0x08, 0x8E);
   idt_set_gate( 22, (unsigned long int)isr22 , 0x08, 0x8E);
   idt_set_gate( 23, (unsigned long int)isr23 , 0x08, 0x8E);
   idt_set_gate( 24, (unsigned long int)isr24 , 0x08, 0x8E);
   idt_set_gate( 25, (unsigned long int)isr25 , 0x08, 0x8E);
   idt_set_gate( 26, (unsigned long int)isr26 , 0x08, 0x8E);
   idt_set_gate( 27, (unsigned long int)isr27 , 0x08, 0x8E);
   idt_set_gate( 28, (unsigned long int)isr28 , 0x08, 0x8E);
   idt_set_gate( 29, (unsigned long int)isr29 , 0x08, 0x8E);
   idt_set_gate( 30, (unsigned long int)isr30 , 0x08, 0x8E);
   idt_set_gate(31, (unsigned long int)isr31, 0x08, 0x8E);

   idt_flush((unsigned long int)&idt_ptr);
   asm volatile ("sti");
}

static void idt_set_gate(unsigned char num, unsigned long int base, unsigned int sel, unsigned char flags)
{
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt_entries[num].flags   = flags /* | 0x60 */;
}

void isr_handler()
{
   asm volatile ("cli");
   asm volatile ("hlt");
   print("Interrupt!");
}