################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/interrupts.c \
../src/main.c \
../src/system_tc27x.c 

OBJS += \
./src/interrupts.o \
./src/main.o \
./src/system_tc27x.o 

C_DEPS += \
./src/interrupts.d \
./src/main.d \
./src/system_tc27x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"C:\HighTec\toolchains\tricore\v4.9.3.0-infineon-1.0/bin/tricore-gcc" -c @ccompilerincludelist.optfile -fno-common -O0 -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DSHIELDBUDDY_TC275D -fshort-double -mcpu=tc27xx -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


