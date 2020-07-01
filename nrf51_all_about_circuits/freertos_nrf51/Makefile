PROJECT_NAME := ble_peripheral

#path variables, customize to your system
SDK_PATH = C:\Nordic\nRF51_SDK_9.0.0_2e23562
OUTPUT_BINARY_DIRECTORY := _build
GNU_INSTALL_ROOT = C:/Program Files (x86)/GNU Tools ARM Embedded/4.9 2015q2

#setup build directories
OBJECT_DIRECTORY = _build
LISTING_DIRECTORY = $(OBJECT_DIRECTORY)
OUTPUT_BINARY_DIRECTORY = $(OBJECT_DIRECTORY)
BUILD_DIRECTORIES := $(sort $(OBJECT_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY) $(LISTING_DIRECTORY) )

#c source files to compile, add files from your project to compile here
C_SOURCE_FILES = main.c
C_SOURCE_FILES += custom_peripheral_service.c

#system files
C_SOURCE_FILES += $(SDK_PATH)/components/toolchain/system_nrf51.c

#drivers C files
C_SOURCE_FILES += $(SDK_PATH)/components/libraries/util/app_error.c
C_SOURCE_FILES += $(SDK_PATH)/components/libraries/fifo/app_fifo.c
C_SOURCE_FILES += $(SDK_PATH)/components/libraries/util/app_util_platform.c
C_SOURCE_FILES += $(SDK_PATH)/components/libraries/util/nrf_assert.c
C_SOURCE_FILES += $(SDK_PATH)/components/libraries/uart/retarget.c
C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/uart/app_uart_fifo.c
C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/hal/nrf_delay.c
C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/common/nrf_drv_common.c
C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/gpiote/nrf_drv_gpiote.c
C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/pstorage/pstorage.c
C_SOURCE_FILES += $(SDK_PATH)/components/libraries/timer/app_timer.c 

#FreeRTOS C files
FREERTOS_PATH = C:\Users\bryan.lee\Documents\FreeRTOSv10.3.1\FreeRTOS
C_SOURCE_FILES += freertos_hooks.c
C_SOURCE_FILES += nrf51_port.c
C_SOURCE_FILES += $(FREERTOS_PATH)/Source/croutine.c
C_SOURCE_FILES += $(FREERTOS_PATH)/Source/event_groups.c
C_SOURCE_FILES += $(FREERTOS_PATH)/Source/list.c
C_SOURCE_FILES += $(FREERTOS_PATH)/Source/queue.c
C_SOURCE_FILES += $(FREERTOS_PATH)/Source/tasks.c
C_SOURCE_FILES += $(FREERTOS_PATH)/Source/timers.c
C_SOURCE_FILES += $(FREERTOS_PATH)/Source/portable/MemMang/heap_4.c

#BLE C files
C_SOURCE_FILES += $(SDK_PATH)/components/ble/common/ble_conn_params.c 
C_SOURCE_FILES += $(SDK_PATH)/components/ble/common/ble_advdata.c 
C_SOURCE_FILES += $(SDK_PATH)/components/ble/common/ble_srv_common.c 
C_SOURCE_FILES += $(SDK_PATH)/components/ble/ble_advertising/ble_advertising.c
C_SOURCE_FILES += $(SDK_PATH)/components/softdevice/common/softdevice_handler/softdevice_handler.c
C_SOURCE_FILES += $(SDK_PATH)/components/ble/ble_services/ble_dis/ble_dis.c

#assembly files to compile
ASM_SOURCE_FILES  += $(SDK_PATH)/components/toolchain/gcc/gcc_startup_nrf51.s

#include paths
INC_PATHS  = -I.
INC_PATHS += -I$(SDK_PATH)/examples/ble_peripheral/ble_app_hrs/config
INC_PATHS += -I$(SDK_PATH)/components/toolchain/gcc 
INC_PATHS += -I$(SDK_PATH)/components/toolchain 
INC_PATHS += -I$(SDK_PATH)/components/device
INC_PATHS += -I$(SDK_PATH)../../../config
INC_PATHS += -I$(SDK_PATH)/components/drivers_nrf/config
INC_PATHS += -I$(SDK_PATH)/examples/bsp
INC_PATHS += -I$(SDK_PATH)/components/libraries/fifo
INC_PATHS += -I$(SDK_PATH)/components/libraries/util
INC_PATHS += -I$(SDK_PATH)/components/drivers_nrf/pstorage
INC_PATHS += -I$(SDK_PATH)/components/drivers_nrf/uart
INC_PATHS += -I$(SDK_PATH)/components/ble/common
INC_PATHS += -I$(SDK_PATH)/components/libraries/sensorsim
INC_PATHS += -I$(SDK_PATH)/components/ble/device_manager
INC_PATHS += -I$(SDK_PATH)/components/ble/ble_services/ble_dis
INC_PATHS += -I$(SDK_PATH)/components/device
INC_PATHS += -I$(SDK_PATH)/components/libraries/button
INC_PATHS += -I$(SDK_PATH)/components/libraries/timer
INC_PATHS += -I$(SDK_PATH)/components/softdevice/s110/headers
INC_PATHS += -I$(SDK_PATH)/components/drivers_nrf/gpiote
INC_PATHS += -I$(SDK_PATH)/components/drivers_nrf/hal
INC_PATHS += -I$(SDK_PATH)/components/toolchain/gcc
INC_PATHS += -I$(SDK_PATH)/components/toolchain
INC_PATHS += -I$(SDK_PATH)/components/drivers_nrf/common
INC_PATHS += -I$(SDK_PATH)/components/ble/ble_advertising
INC_PATHS += -I$(SDK_PATH)/components/libraries/trace
INC_PATHS += -I$(SDK_PATH)/components/softdevice/common/softdevice_handler
INC_PATHS += -I$(FREERTOS_PATH)/Source/include
INC_PATHS += -I$(FREERTOS_PATH)/Source/portable/GCC\ARM_CM0

#compile flags
CFLAGS = -DSOFTDEVICE_PRESENT
CFLAGS += -DNRF51
CFLAGS += -DBOARD_PCA10031
CFLAGS += -DS110
CFLAGS += -DDEBUG
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs --std=gnu99
CFLAGS += -Wall -O3
CFLAGS += -mfloat-abi=soft
# keep every function in separate section. This will allow linker to dump unused functions
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums

#linker flags
# keep every function in separate section. This will allow linker to dump unused functions
export OUTPUT_FILENAME
LDFLAGS += -Xlinker -Map=$(LISTING_DIRECTORY)/$(OUTPUT_FILENAME).map
LDFLAGS += -mthumb -mabi=aapcs -L $(SDK_PATH)/components/toolchain/gcc -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys

# Assembler flags
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DNRF51

###
# Everything below this line is automatic and typically unneccesary to modify
###
# Toolchain commands
GNU_PREFIX := arm-none-eabi
CC       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gcc"
AS       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-as"
AR       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ar" -r
LD       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ld"
NM       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-nm"
OBJDUMP  		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objdump"
OBJCOPY  		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objcopy"
SIZE    		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-size"

MAKEFILE_NAME := $(MAKEFILE_LIST)
MAKEFILE_DIR := $(dir $(MAKEFILE_NAME) ) 

#command line commands
MK := mkdir
RM := rm -rf

#default target - first one defined
default: clean nrf51422_xxac

#building all targets
all: clean
	$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e cleanobj
	$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e nrf51422_xxac


#function for removing duplicates in a list
remduplicates = $(strip $(if $1,$(firstword $1) $(call remduplicates,$(filter-out $(firstword $1),$1))))

C_SOURCE_FILE_NAMES = $(notdir $(C_SOURCE_FILES))
C_PATHS = $(call remduplicates, $(dir $(C_SOURCE_FILES) ) )
C_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(C_SOURCE_FILE_NAMES:.c=.o) )

ASM_SOURCE_FILE_NAMES = $(notdir $(ASM_SOURCE_FILES))
ASM_PATHS = $(call remduplicates, $(dir $(ASM_SOURCE_FILES) ))
ASM_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(ASM_SOURCE_FILE_NAMES:.s=.o) )

vpath %.c $(C_PATHS)
vpath %.s $(ASM_PATHS)

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

nrf51422_xxac: OUTPUT_FILENAME := $(PROJECT_NAME)
nrf51422_xxac: LINKER_SCRIPT=ble_app_gcc_nrf51.ld
nrf51422_xxac: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e finalize

## Create build directories
$(BUILD_DIRECTORIES):
	echo $(MAKEFILE_NAME)
	$(MK) $@

# Create objects from C SRC files
$(OBJECT_DIRECTORY)/%.o: %.c
	@echo Compiling file: $(notdir $<)
	$(CC) $(CFLAGS) $(INC_PATHS) -c -o $@ $<

# Assemble files
$(OBJECT_DIRECTORY)/%.o: %.s
	@echo Compiling file: $(notdir $<)
	$(CC) $(ASMFLAGS) $(INC_PATHS) -c -o $@ $<


# Link
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out


## Create binary .bin file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

finalize: genbin genhex echosize

genbin:
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
genhex: 
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

echosize:
	-@echo ""
	$(SIZE) $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	-@echo ""

clean:
	$(RM) $(BUILD_DIRECTORIES)

cleanobj:
	$(RM) $(BUILD_DIRECTORIES)/*.o

flash:
	nrf51_program_sd_app.bat