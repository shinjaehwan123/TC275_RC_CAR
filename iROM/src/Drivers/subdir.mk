################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Drivers/asclin.c \
../src/Drivers/can.c \
../src/Drivers/gpt12.c \
../src/Drivers/vadc.c 

OBJS += \
./src/Drivers/asclin.o \
./src/Drivers/can.o \
./src/Drivers/gpt12.o \
./src/Drivers/vadc.o 

C_DEPS += \
./src/Drivers/asclin.d \
./src/Drivers/can.d \
./src/Drivers/gpt12.d \
./src/Drivers/vadc.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/%.o: ../src/Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"C:\HighTec\toolchains\tricore\v4.9.3.0-infineon-1.0/bin/tricore-gcc" -c @ccompilerincludelist.optfile -fno-common -O0 -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DSHIELDBUDDY_TC275D -fshort-double -mcpu=tc27xx -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


