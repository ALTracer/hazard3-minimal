## hazard3-minimal

This repository contains bare metal C programs with minimal features and no external dependencies, also startup assembly and linkerscript,
for a few examples intended to run on RISC-V RV32I processors, like [Hazard3 example SoC by Luke Wren](https://github.com/Wren6991/Hazard3)
There were no such examples which would run on a real softcore, only `tb_cxxrtl` desktop testbench examples, so I coded this.

Ideas and organization taken from https://github.com/mtkos/rp2350-minimal and other `-minimal` series repos there.
Peripheral headers for UART and TIMER modeled after [CMSIS-4 Device for Cortex-M](https://github.com/ARM-software/CMSIS_4/blob/master/Device/_Template_Vendor/Vendor/Device/Include/Device.h), which is what's familiar to me, unlike [libfpga regblock headers](https://github.com/Wren6991/libfpga/blob/master/peris/uart/uart_regs.h).
Code should be compatible with Newlib, but I aimed to avoid pulling in large amounts of stdio library code referenced by their crt0 `_start`. The goal was to run a blinky (except there's no GPIO peripheral in SoC), a UART Tx hello-world, and some RISC-V Semihosting tests.

[xPack RISC-V GCC-12](https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack) (ideally 14 or newer) is required, as well as Newlib, to compile this code. xPack was tested to be fine, I picked it for size reasons and familiarity, any other should do.

Depending on how you configured and synthesized your Hazard3 instance, compressed instructions may work or will trap. I don't make use of Muldiv, Atomic, Compressed. Other extensions are also disabled because of 5280 LC resource constraints (`_Zicntr`, `_Zcmp` would be nice to have, `_Zmmul` is not supported). You can enable 4 hardware breakpoint triggers for convenient debug, and you should enable System Bus Access (`HAVE_SBA=1`) for debuggers which don't implement progbuf memory access.

Loaded and debugged through Black Magic Debug Application onto [1bitSquared Icebreaker board](https://github.com/icebreaker-fpga/icebreaker) (via FT2232H Interface A, manual PCF remap) on the softcore running on iCE40UP5k. Likewise, loaded and debugged through [Black Magic Firmware](https://github.com/blackmagic-debug/blackmagic/) (`blackpill-f411ce` [platform](https://github.com/WeActStudio/WeActStudio.MiniSTM32F4x1)) when Hazard3 JTAG is manually remapped in PCF to PMOD1B.