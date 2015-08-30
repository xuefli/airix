#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef short pid_t;

#define FLAGS_IF (1 << 9)

/* Trap information on stack when interrupt */
struct trap_frame
{
    /* Segment registers */
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;

    /* Registers as pushed by pushad */
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    /* Pushed by CPU when interrupt */
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;

    /* Pushed by CPU when crossing rings */
    uint32_t user_esp;
    uint32_t ss;
};

struct process
{
    pid_t pid;                  /* Process ID */
    void *page_dir;             /* Virtual address space of process */
    struct trap_frame *trap;    /* Pointer to trap frame on stack */
    uint32_t entry;             /* Entry of process */
    uint32_t kernel_stack;      /* End address of process kernel stack */
    uint32_t user_stack;        /* End address of process user stack */
    struct process *parent;     /* Process's parent */
};

void proc_initialize();
struct process * proc_alloc();
void proc_free(struct process *proc);

bool proc_exec(const char *elf, size_t size);

#endif /* PROCESS_H */