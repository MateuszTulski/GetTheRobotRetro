################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Utils/Utils.cpp \
../src/Utils/Vec2D.cpp 

CPP_DEPS += \
./src/Utils/Utils.d \
./src/Utils/Vec2D.d 

OBJS += \
./src/Utils/Utils.o \
./src/Utils/Vec2D.o 


# Each subdirectory must supply rules for building sources it contributes
src/Utils/%.o: ../src/Utils/%.cpp src/Utils/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Utils

clean-src-2f-Utils:
	-$(RM) ./src/Utils/Utils.d ./src/Utils/Utils.o ./src/Utils/Vec2D.d ./src/Utils/Vec2D.o

.PHONY: clean-src-2f-Utils

