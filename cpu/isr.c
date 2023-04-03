#include "isr.h"
#include "idt.h"
#include <drivers/VGA/driver.h>
#include <include/iobyte.h>
#include <string.h>

isr_t interrupt_handlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install() {
    set_idt_gate(0, (uintptr_t) isr0);
    set_idt_gate(1, (uintptr_t) isr1);
    set_idt_gate(2, (uintptr_t) isr2);
    set_idt_gate(3, (uintptr_t) isr3);
    set_idt_gate(4, (uintptr_t) isr4);
    set_idt_gate(5, (uintptr_t) isr5);
    set_idt_gate(6, (uintptr_t) isr6);
    set_idt_gate(7, (uintptr_t) isr7);
    set_idt_gate(8, (uintptr_t) isr8);
    set_idt_gate(9, (uintptr_t) isr9);
    set_idt_gate(10, (uintptr_t) isr10);
    set_idt_gate(11, (uintptr_t) isr11);
    set_idt_gate(12, (uintptr_t) isr12);
    set_idt_gate(13, (uintptr_t) isr13);
    set_idt_gate(14, (uintptr_t) isr14);
    set_idt_gate(15, (uintptr_t) isr15);
    set_idt_gate(16, (uintptr_t) isr16);
    set_idt_gate(17, (uintptr_t) isr17);
    set_idt_gate(18, (uintptr_t) isr18);
    set_idt_gate(19, (uintptr_t) isr19);
    set_idt_gate(20, (uintptr_t) isr20);
    set_idt_gate(21, (uintptr_t) isr21);
    set_idt_gate(22, (uintptr_t) isr22);
    set_idt_gate(23, (uintptr_t) isr23);
    set_idt_gate(24, (uintptr_t) isr24);
    set_idt_gate(25, (uintptr_t) isr25);
    set_idt_gate(26, (uintptr_t) isr26);
    set_idt_gate(27, (uintptr_t) isr27);
    set_idt_gate(28, (uintptr_t) isr28);
    set_idt_gate(29, (uintptr_t) isr29);
    set_idt_gate(30, (uintptr_t) isr30);
    set_idt_gate(31, (uintptr_t) isr31);

    // Remap the PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Install the IRQs
    set_idt_gate(32, (uintptr_t)irq0);
    set_idt_gate(33, (uintptr_t)irq1);
    set_idt_gate(34, (uintptr_t)irq2);
    set_idt_gate(35, (uintptr_t)irq3);
    set_idt_gate(36, (uintptr_t)irq4);
    set_idt_gate(37, (uintptr_t)irq5);
    set_idt_gate(38, (uintptr_t)irq6);
    set_idt_gate(39, (uintptr_t)irq7);
    set_idt_gate(40, (uintptr_t)irq8);
    set_idt_gate(41, (uintptr_t)irq9);
    set_idt_gate(42, (uintptr_t)irq10);
    set_idt_gate(43, (uintptr_t)irq11);
    set_idt_gate(44, (uintptr_t)irq12);
    set_idt_gate(45, (uintptr_t)irq13);
    set_idt_gate(46, (uintptr_t)irq14);
    set_idt_gate(47, (uintptr_t)irq15);

    load_idt(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",

        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown Interrupt",

        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",

        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"
};

void isr_handler(registers_t *r) {
    puts("received interrupt: ");
    char s[3];
    intToString(r->int_no, s);
    puts(s);
    puts("\n");
    puts(exception_messages[r->int_no]);
    puts("\n");
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t *r) {
    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }

    // EOI
    if (r->int_no >= 40) {
        outb(0xA0, 0x20); /* follower */
    }
    outb(0x20, 0x20); /* leader */
}