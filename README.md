# Notes

## Get Started
### Install the prerequisites
For Mac OS X with M1:
```
>> brew tap riscv/riscv
>> brew install riscv-tools
>> vim ~/.zshrc
export PATH=${PATH}:/opt/homebrew/Cellar/riscv-gnu-toolchain/main/bin
>> brew install qemu
```

### Run
To start:
```
>> make clean
>> make qemu
```

To quit: ^a + x
