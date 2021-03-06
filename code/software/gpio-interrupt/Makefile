# Make gpio-interrupt test program for rosco_m68k
#
# Copyright (c)2020 Xark
# MIT LICENSE

EXTRA_CFLAGS?=-g -Os -fomit-frame-pointer
DEFINES=
SYSINCDIR?=../libs/build/include
SYSLIBDIR?=../libs/build/lib
LIBS=-lmachine -lstart_serial
CFLAGS=-std=c11 -ffreestanding -ffunction-sections -fdata-sections \
				-Wall -Wextra -Werror -pedantic -I$(SYSINCDIR) \
				-mcpu=68010 -march=68010 -mtune=68010 $(DEFINES)
ASFLAGS=-mcpu=68010 -march=68010
LDFLAGS=-T $(SYSLIBDIR)/ld/serial/rosco_m68k_program.ld -L $(SYSLIBDIR) \
				-Map=$(MAP) --gc-sections --oformat=elf32-m68k --defsym=_RAM_SIZE=1M
VASMFLAGS=-Felf -m68010 -quiet -Lnf -showopt $(DEFINES)
CC=m68k-elf-gcc
AS=m68k-elf-as
LD=m68k-elf-ld
NM=m68k-elf-nm
LD=m68k-elf-ld
OBJDUMP=m68k-elf-objdump
OBJCOPY=m68k-elf-objcopy
SIZE=m68k-elf-size
VASM=vasmm68k_mot
RM=rm -f
KERMIT=kermit
SERIAL?=/dev/modem
BAUD?=9600

# Output config (assume name of directory)
PROGRAM_BASENAME=$(shell basename $(CURDIR))

# Set other output files using output basname
ELF=$(PROGRAM_BASENAME).elf
BINARY=$(PROGRAM_BASENAME).bin
DISASM=$(PROGRAM_BASENAME).dis
MAP=$(PROGRAM_BASENAME).map
SYM=$(PROGRAM_BASENAME).sym

# Assume source files in Makefile directory are source files for project
CSOURCES=$(wildcard *.c)
SSOURCES=$(wildcard *.S)
ASMSOURCES=$(wildcard *.asm)
SOURCES=$(CSOURCES) $(SSOURCES) $(ASMSOURCES)

# Assume each source files makes an object file
OBJECTS=$(addsuffix .o,$(basename $(SOURCES)))

all: $(BINARY) $(DISASM)

$(ELF) : $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)
	$(NM) --numeric-sort $@ >$(SYM)
	$(SIZE) $@
	chmod a-x $@

$(BINARY) : $(ELF)
	$(OBJCOPY) -O binary $(ELF) $(BINARY)

$(DISASM) : $(ELF)
	$(OBJDUMP) --disassemble -S $(ELF) >$(DISASM)

$(OBJECTS): Makefile

%.o : %.c
	$(CC) -c $(CFLAGS) $(EXTRA_CFLAGS) -o $@ $<

%.o : %.asm
	$(VASM) $(VASMFLAGS) -L $(basename $@).lst -o $@ $<

# Makefile magic (for "phony" targets that are not real files)
.PHONY: all clean dump disasm load

# remove targets that can be generated by this Makefile
clean:
	$(RM) $(OBJECTS) $(ELF) $(BINARY) $(MAP) $(SYM) $(DISASM) $(addsuffix .lst,$(basename $(SSOURCES) $(ASMSOURCES)))

disasm: $(DISASM)

# hexdump of program binary
dump: $(BINARY)
	hexdump -C $(BINARY)

# upload binary to rosco (if ready and kermit present)
load: $(BINARY)
	kermit -i -l $(SERIAL) -b $(BAUD) -s $(BINARY)
