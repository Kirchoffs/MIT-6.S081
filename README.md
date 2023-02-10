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
