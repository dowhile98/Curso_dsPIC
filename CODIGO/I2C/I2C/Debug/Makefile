################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../fonts.c \
../main.c \
../MPU6050.c \
../ssd1306.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
fonts.o \
main.o \
MPU6050.o \
ssd1306.o

OBJS_AS_ARGS +=  \
fonts.o \
main.o \
MPU6050.o \
ssd1306.o

C_DEPS +=  \
fonts.d \
main.d \
MPU6050.d \
ssd1306.d

C_DEPS_AS_ARGS +=  \
fonts.d \
main.d \
MPU6050.d \
ssd1306.d

OUTPUT_FILE_PATH +=I2C.elf

OUTPUT_FILE_PATH_AS_ARGS +=I2C.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./fonts.o: .././fonts.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.32
	$(QUOTE)D:\archivos de programa\Microchip\xc8\v2.32\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328P  -mdfp="D:\archivos de programa\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328P__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.32
	$(QUOTE)D:\archivos de programa\Microchip\xc8\v2.32\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328P  -mdfp="D:\archivos de programa\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328P__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./MPU6050.o: .././MPU6050.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.32
	$(QUOTE)D:\archivos de programa\Microchip\xc8\v2.32\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328P  -mdfp="D:\archivos de programa\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328P__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./ssd1306.o: .././ssd1306.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.32
	$(QUOTE)D:\archivos de programa\Microchip\xc8\v2.32\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328P  -mdfp="D:\archivos de programa\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328P__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking:  XC8 C Linker : 2.32
	$(QUOTE)D:\archivos de programa\Microchip\xc8\v2.32\bin\xc8-cc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mcpu=ATmega328P  -mdfp="D:\archivos de programa\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -Wl,-Map="I2C.map" -funsigned-char -funsigned-bitfields -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums --memorysummary,memoryfile.xml -Wl,-u,vfprintf -lprintf_flt -lm  
	@echo Finished building target: $@
	"D:\archivos de programa\Microchip\xc8\v2.32\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "I2C.elf" "I2C.hex"
	"D:\archivos de programa\Microchip\xc8\v2.32\bin\avr-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "I2C.elf" "I2C.eep" || exit 0
	"D:\archivos de programa\Microchip\xc8\v2.32\bin\avr-objdump.exe" -h -S "I2C.elf" > "I2C.lss"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "I2C.elf" "I2C.hex" "I2C.eep" "I2C.map" "I2C.usersignatures" "I2C.a"  "I2C.lss"
	