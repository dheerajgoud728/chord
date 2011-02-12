################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp 

CPP_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
main: ../main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -lglut -lGLU -MMD -MP -MF"$(@:%.o=%.d)" -MT"main.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


