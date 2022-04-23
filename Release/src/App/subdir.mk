################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/App/App.cpp 

CPP_DEPS += \
./src/App/App.d 

OBJS += \
./src/App/App.o 


# Each subdirectory must supply rules for building sources it contributes
src/App/%.o: ../src/App/%.cpp src/App/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-App

clean-src-2f-App:
	-$(RM) ./src/App/App.d ./src/App/App.o

.PHONY: clean-src-2f-App

