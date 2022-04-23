################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Input/GameController.cpp \
../src/Input/InputController.cpp 

CPP_DEPS += \
./src/Input/GameController.d \
./src/Input/InputController.d 

OBJS += \
./src/Input/GameController.o \
./src/Input/InputController.o 


# Each subdirectory must supply rules for building sources it contributes
src/Input/%.o: ../src/Input/%.cpp src/Input/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Input

clean-src-2f-Input:
	-$(RM) ./src/Input/GameController.d ./src/Input/GameController.o ./src/Input/InputController.d ./src/Input/InputController.o

.PHONY: clean-src-2f-Input

