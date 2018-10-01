################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fpga_ports/fpga_ports.c 

OBJS += \
./fpga_ports/fpga_ports.o 

C_DEPS += \
./fpga_ports/fpga_ports.d 


# Each subdirectory must supply rules for building sources it contributes
fpga_ports/fpga_ports.o: ../fpga_ports/fpga_ports.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-gcc -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av\socal" -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"fpga_ports/fpga_ports.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


