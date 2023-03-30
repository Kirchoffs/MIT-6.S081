## GDB

```
>> b _entry
>> c
>> si
>> b main
>> b kvminit
>> b kvminithart
>> b syscall
>> layout split
>> p /x (0x10000000 >> 12)
>> p 0x80
```

## Check
```
>> ./grade-lab-pgtbl ugetpid
```
or
```
>> make grade
```

## Code
### Speed up system calls
__ulib.c__
```
#ifdef LAB_PGTBL
int ugetpid(void)
{
  struct usyscall *u = (struct usyscall *) USYSCALL;
  return u->pid;
}
#endif
```
According to the code, we need to write the usyscall structure into the beginning part of USYSCALL. 

__proc.c__
```
// Mapping
pagetable_t proc_pagetable(struct proc *p)
{
    if (mappages(pagetable, TRAMPOLINE, PGSIZE, (uint64) trampoline, PTE_R | PTE_X) < 0) {
        uvmfree(pagetable, 0);
        return 0;
    }
}
```

### Detecting which pages have been accessed
__pgtbltest.c__
```
void pgaccess_test() 
{

}
```

### Inline Assembly
```
asm (assembly instructions : output operands : input operands : clobbered registers)
```
- assembly instructions: This is a string of assembly instructions to be executed. It can include placeholders for input and output operands.
- output operands: This is a list of C/C++ variables that receive output values from the assembly code. The output operands are separated by commas.
- input operands: This is a list of C/C++ variables or constants that are passed as input values to the assembly code. The input operands are also separated by commas.
- clobbered registers: This is a list of registers that are modified by the assembly code and must be saved and restored if needed. The clobbered registers are separated by commas.