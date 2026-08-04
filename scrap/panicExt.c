#include <stdlib.h>
#include <stdio.h>

static void *VM;

const unsigned char CALL_OPCODE = 27;

static int USE_PANIC_HANDLER = 0;
static unsigned long long PANIC_HANDLER = 0;

void OSPL_load(void *vm) {
    VM = vm;
}

void panic(char* message)
{
    puts("OSPL panicked!");
    puts("==============");
    puts(message);

    if (!USE_PANIC_HANDLER)
        exit(EXIT_FAILURE);

    else if (VM) {
        void *i = OSPL_inst_new();
        OSPL_inst_set_opcode(i, CALL_OPCODE);
        OSPL_inst_add_index(i, PANIC_HANDLER);
        OSPL_vm_run(VM, i);
        OSPL_inst_destroy(i);
    }

    else { exit(EXIT_FAILURE + 1); }
}
