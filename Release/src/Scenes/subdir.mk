################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Scenes/GameScene.cpp 

CPP_DEPS += \
./src/Scenes/GameScene.d 

OBJS += \
./src/Scenes/GameScene.o 


# Each subdirectory must supply rules for building sources it contributes
src/Scenes/%.o: ../src/Scenes/%.cpp src/Scenes/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Scenes

clean-src-2f-Scenes:
	-$(RM) ./src/Scenes/GameScene.d ./src/Scenes/GameScene.o

.PHONY: clean-src-2f-Scenes

