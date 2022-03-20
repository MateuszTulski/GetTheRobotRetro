################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Graphics/Color.cpp \
../src/Graphics/Screen.cpp \
../src/Graphics/ScreenBuffer.cpp 

CPP_DEPS += \
./src/Graphics/Color.d \
./src/Graphics/Screen.d \
./src/Graphics/ScreenBuffer.d 

OBJS += \
./src/Graphics/Color.o \
./src/Graphics/Screen.o \
./src/Graphics/ScreenBuffer.o 


# Each subdirectory must supply rules for building sources it contributes
src/Graphics/%.o: ../src/Graphics/%.cpp src/Graphics/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Graphics

clean-src-2f-Graphics:
	-$(RM) ./src/Graphics/Color.d ./src/Graphics/Color.o ./src/Graphics/Screen.d ./src/Graphics/Screen.o ./src/Graphics/ScreenBuffer.d ./src/Graphics/ScreenBuffer.o

.PHONY: clean-src-2f-Graphics

