# Notes

## Get Started
### Install the prerequisites
For Mac OS X:
```
>> brew tap riscv/riscv
>> brew install riscv-tools
>> vim ~/.zshrc
For M1:
export PATH=${PATH}:/opt/homebrew/Cellar/riscv-gnu-toolchain/main/bin

For Intel:
export PATH=${PATH}:/usr/local/Cellar/riscv-gnu-toolchain/main/bin

>> brew install qemu
```

## Run
To start:
```
>> make clean
>> make qemu
```

To quit: ^a + x

## Test
```
>> ./grade-lab-util sleep
>> make GRADEFLAGS=sleep grade
```

## GDB

### Start

On one terminal:
```
>> make CPUS=1 qemu-gdb
```

On another terminal:
```
>> gdb-multiarch
```
If error happens, just follow the hint from the command output, to add `set auto-load safe-path /` to somewhere.

### Run

```
>> b _entry
>> c
>> si
>> b main
>> layout split
```

### GBD Notes
#### Difference between s and si
In GDB, s and si are two different commands used for single-stepping through your program.

s: Short for "step," this command executes the current line of code and stops at the next line. If the current line of code calls a function, s will stop at the first line of that function.

si: Short for "step instruction," this command executes the current machine instruction and stops at the next instruction. If the current line of code calls a function, si will not enter the function, but will execute the call instruction and stop at the first instruction of the function.
