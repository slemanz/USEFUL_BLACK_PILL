CC=arm-none-eabi-gcc
MACH=cortex-m4
FLOAT=soft

LINKER_APP=STM32F401_APP.ld

MAP_FILE=Build/final.map
FINAL_FILE=Build/final.elf
FLASH_FILE=Build/flash.bin

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) -std=gnu11 -Wall -O0
#APP_LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) --specs=nano.specs -T $(LINKER_APP) -Wl,-Map=$(MAP_FILE) -ggdb -u _printf_float 
APP_LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) --specs=nano.specs -T $(LINKER_APP) -Wl,-Map=$(MAP_FILE)
OBJCOPY=arm-none-eabi-objcopy

#############################################
#				 INCLUDES					#
#############################################

INCLUDES+= -I Inc/
INCLUDES+= -I Drivers/Inc/ 
INCLUDES+= -I Shared/Inc/ 
INCLUDES+= -I Common/Inc/ 


############################################
# 				OUTPUT FILES

BLINKY		+= Build/blinky.o
COMMAND		+= Build/command.o

OBJS		+= Build/syscalls.o
OBJS		+= Build/startup.o

DRIVERS		+= Build/driver_systick.o
DRIVERS		+= Build/driver_interrupt.o
DRIVERS		+= Build/driver_gpio.o
DRIVERS		+= Build/driver_uart.o

COMMON 		+= Build/init.o
COMMON 		+= Build/ticks.o
COMMON 		+= Build/serial.o

#SHARED 		+= Build/cli.o
SHARED 		+= Build/ring-buffer.o



#############################################
#				RULES						#
#############################################

all: Build/final.elf

blinky: Build/blinky.elf

command: Build/command.elf

Build/%.o: Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Src/$(*).c

Build/%.o: Src/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Src/$(*).S

Build/%.o: Apps/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Apps/$(*).c

Build/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o $(*).c

Build/%.o: Drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Drivers/Src/$(*).c

Build/%.o: Shared/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Shared/Src/$(*).c

Build/%.o: Common/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Common/Src/$(*).c

Build/%.o: Apps/blinky/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Apps/blinky/$(*).c

Build/%.o: Apps/command/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Apps/command/$(*).c

Build/blinky.elf: $(BLINKY) $(OBJS)
	$(CC) $(APP_LDFLAGS) -o $@ $^
	$(CC) $(APP_LDFLAGS) -o Build/flash.elf $^
	$(OBJCOPY) -O binary $@ Build/flash.bin

Build/command.elf: $(COMMAND) $(OBJS) $(DRIVERS) $(SHARED) $(COMMON)
	$(CC) $(APP_LDFLAGS) -o $@ $^
	$(CC) $(APP_LDFLAGS) -o Build/flash.elf $^
	$(OBJCOPY) -O binary $@ Build/flash.bin

Build/final.elf: $(OBJS)
	$(CC) $(APP_LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary Build/flash.elf Build/flash.bin

load:
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c init -c "reset init" \
	-c "flash write_image erase Build/flash.elf" -c "reset run" -c shutdown

debug:
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c init -c "reset init"

reset:
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c init -c "reset run" -c shutdown

clean:
	rm -rf *.o *.map Build/*.o