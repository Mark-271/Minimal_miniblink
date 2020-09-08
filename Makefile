APP		:= miniblink
LDSCRIPT	= stm32vl-discovery.ld
ARCH_FLAGS	= -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd

# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q		:= @
endif

CC		:= $(CROSS_COMPILE)gcc
LD		:= $(CROSS_COMPILE)gcc
OBJCOPY		:= $(CROSS_COMPILE)objcopy
STFLASH		= $(shell which st-flash)

OBJS 		+= main.o

CFLAGS		+= -O2 -std=c89 $(ARCH_FLAGS) -fno-common
CPPFLAGS	:= -Wall
LDFLAGS		+= --static -nostartfiles
LDFLAGS		+= -T$(LDSCRIPT)
LDFLAGS		+= $(ARCH_FLAGS)
LDLIBS		+= -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

# ------------------------------------------------------------------------------

all: elf
elf: $(APP).elf
bin: $(APP).bin

%.bin: %.elf
	@printf "  OBJCOPY $(*).bin\n"
	$(Q)$(OBJCOPY) -Obinary $(*).elf $(*).bin

%.elf: $(OBJS) $(LDSCRIPT)
	@printf "  LD      $(*).elf\n"
	$(Q)$(LD) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(*).elf

%.o: %.c
	@printf "  CC      $(*).c\n"
	$(Q)$(CC) $(CFLAGS) $(CPPFLAGS) -o $(*).o -c $(*).c

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) $(APP).elf $(APP).bin $(OBJS) $(OBJS:%.o=%.d)

flash: $(APP).bin
	@printf "  FLASH  $<\n"
	$(STFLASH) write $(APP).bin 0x8000000

.PHONY: clean flash elf bin
