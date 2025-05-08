TARGET = semihosting

SRC = main.c
SRC += ../common/startup.S ../common/irq.c
SRC += ../common/syscalls.c

include ../build.mk
LDFLAGS += --specs=semihost.specs
