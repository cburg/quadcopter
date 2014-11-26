

# Effective Build Steps:
# 1. Build all Mbed library code to ./out/mbed
# 2. Build all Quadcopter code to ./out/quadcopter
# 3. Build main


################################################################################
# Directories
################################################################################


MCU := NUCLEO_F401RE
TARGET := GCC_ARM

# Add any new directories here. Any .c, .cpp, or .s files within the directory
# will be compiled by default.
DIRS =	mbed/api \
		mbed/cmsis_common \
		mbed/common \
		mbed/hal \
		mbed/targets/$(MCU)/hal \
		mbed/targets/$(MCU)/cmsis \
		quadcopter/libraries/servo \
		quadcopter/libraries/sonars \
		quadcopter/libraries/imu

TOOLCHAIN_DIR = mbed/targets/$(MCU)/cmsis/TOOLCHAIN_GCC_ARM

################################################################################
# Build flags and tools
################################################################################

# Compiler flags based on verbose output from workspace_tools/make.py
# The mbed timestamp define was removed.
GPP_COMPILE_FLAGS := -std=gnu++98 -fno-rtti -c -Wall -Wextra -Wno-unused-parameter \
					-Wno-missing-field-initializers -fmessage-length=0 \
					-fno-exceptions -fno-builtin -ffunction-sections \
					-fdata-sections -MMD -fno-delete-null-pointer-checks \
					-fomit-frame-pointer -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 \
					-mfloat-abi=softfp -O2 -DTARGET_NUCLEO_F401RE -DTARGET_M4 \
					-DTARGET_CORTEX_M -DTARGET_STM -DTARGET_STM32F4 \
					-DTARGET_STM32F401RE -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC \
					-D__CORTEX_M4 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -D__MBED__=1 \
					-DTARGET_FF_ARDUINO -DTARGET_FF_MORPHO

GCC_COMPILE_FLAGS := -std=gnu99 -c -Wall -Wextra -Wno-unused-parameter \
					-Wno-missing-field-initializers -fmessage-length=0 \
					-fno-exceptions -fno-builtin -ffunction-sections \
					-fdata-sections -MMD -fno-delete-null-pointer-checks \
					-fomit-frame-pointer -mcpu=cortex-m4 -mthumb \
					-mfpu=fpv4-sp-d16 -mfloat-abi=softfp -O2 \
					-DTARGET_NUCLEO_F401RE -DTARGET_M4 -DTARGET_CORTEX_M \
					-DTARGET_STM -DTARGET_STM32F4 -DTARGET_STM32F401RE \
					-DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M4 \
					-DARM_MATH_CM4 -D__FPU_PRESENT=1 -D__MBED__=1 \
					-DTARGET_FF_ARDUINO -DTARGET_FF_MORPHO

ASM_COMPILE_FLAGS := -x assembler-with-cpp -c -Wall -Wextra -Wno-unused-parameter \
					-Wno-missing-field-initializers -fmessage-length=0 -fno-exceptions \
					-fno-builtin -ffunction-sections -fdata-sections -MMD \
					-fno-delete-null-pointer-checks -fomit-frame-pointer \
					-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp \
					-O2 -DTARGET_NUCLEO_F401RE -DTARGET_M4 -DTARGET_CORTEX_M \
					-DTARGET_STM -DTARGET_STM32F4 -DTARGET_STM32F401RE \
					-DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M4 -DARM_MATH_CM4 \
					-D__FPU_PRESENT=1 -D__MBED__=1 -DTARGET_FF_ARDUINO -DTARGET_FF_MORPHO

# Linker flags based on verbose output from workspace_tools/make.py
LINKER_PRE_FLAGS := -Wl,--gc-sections -Wl,--wrap,main -mcpu=cortex-m4 -mthumb \
					-mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs \
					-T$(TOOLCHAIN_DIR)/NUCLEO_F401RE.ld 

# Linker flags based on verbose output from workspace_tools/make.py
LINKER_POST_FLAGS := -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -lstdc++ -lsupc++ \
					-lm -lc -lgcc -lnosys

# Binary extraction flags based on verbose output from workspace_tools/make.py
BINARY_FLAGS := -O binary 

# Prepend each directory with the -I include flag
INCLUDE_FLAGS := $(foreach dir,$(DIRS),-I$(dir))

CC := arm-none-eabi-gcc
PP := arm-none-eabi-g++
LD := arm-none-eabi-gcc
OB := arm-none-eabi-objcopy



################################################################################
# Project Source and Object Files
################################################################################


CPP_SOURCE = main.cpp \
			$(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))

C_SOURCE = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

S_SOURCE = $(TOOLCHAIN_DIR)/startup_STM32F40x.s

OBJS = $(patsubst %.cpp, out/%_cpp.o, $(CPP_SOURCE)) \
		$(patsubst %.c, out/%_c.o, $(C_SOURCE)) \
		$(patsubst %.s, out/%_s.o, $(S_SOURCE))



################################################################################
# Targets
################################################################################


out/%_cpp.o: %.cpp
	@echo "Building $<"
	@mkdir -p $(@D)
	@$(PP) $(GPP_COMPILE_FLAGS) $(INCLUDE_FLAGS) -o $@ $<

out/%_c.o: %.c
	@echo "Building $<"
	@mkdir -p $(@D)
	@$(CC) $(GCC_COMPILE_FLAGS) $(INCLUDE_FLAGS) -o $@ $<

out/%_s.o: %.s
	@echo "Building $<"
	@mkdir -p $(@D)
	@$(CC) $(ASM_COMPILE_FLAGS) $(INCLUDE_FLAGS) -o $@ $<


.PHONY: all quadcopter

all: quadcopter

quadcopter: $(OBJS)
	$(LD) $(LINKER_PRE_FLAGS) -o out/quad.elf $(OBJS) $(LINKER_POST_FLAGS)
	@$(OB) $(BINARY_FLAGS) out/quad.elf out/quad.bin

clean: 
	rm -rf out
