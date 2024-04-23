################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Sensors/Bluetooth.c \
../src/Sensors/Buzzer.c \
../src/Sensors/GPIO.c \
../src/Sensors/Motor.c \
../src/Sensors/ToF.c \
../src/Sensors/Ultrasonic.c 

OBJS += \
./src/Sensors/Bluetooth.o \
./src/Sensors/Buzzer.o \
./src/Sensors/GPIO.o \
./src/Sensors/Motor.o \
./src/Sensors/ToF.o \
./src/Sensors/Ultrasonic.o 

C_DEPS += \
./src/Sensors/Bluetooth.d \
./src/Sensors/Buzzer.d \
./src/Sensors/GPIO.d \
./src/Sensors/Motor.d \
./src/Sensors/ToF.d \
./src/Sensors/Ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
src/Sensors/%.o: ../src/Sensors/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"C:\HighTec\toolchains\tricore\v4.9.3.0-infineon-1.0/bin/tricore-gcc" -c @ccompilerincludelist.optfile -fno-common -O0 -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DSHIELDBUDDY_TC275D -fshort-double -mcpu=tc27xx -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


