################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Shapes/AARectangle.cpp \
../src/Shapes/Circle.cpp \
../src/Shapes/Line2D.cpp \
../src/Shapes/Shape.cpp \
../src/Shapes/Triangle.cpp 

CPP_DEPS += \
./src/Shapes/AARectangle.d \
./src/Shapes/Circle.d \
./src/Shapes/Line2D.d \
./src/Shapes/Shape.d \
./src/Shapes/Triangle.d 

OBJS += \
./src/Shapes/AARectangle.o \
./src/Shapes/Circle.o \
./src/Shapes/Line2D.o \
./src/Shapes/Shape.o \
./src/Shapes/Triangle.o 


# Each subdirectory must supply rules for building sources it contributes
src/Shapes/%.o: ../src/Shapes/%.cpp src/Shapes/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Shapes

clean-src-2f-Shapes:
	-$(RM) ./src/Shapes/AARectangle.d ./src/Shapes/AARectangle.o ./src/Shapes/Circle.d ./src/Shapes/Circle.o ./src/Shapes/Line2D.d ./src/Shapes/Line2D.o ./src/Shapes/Shape.d ./src/Shapes/Shape.o ./src/Shapes/Triangle.d ./src/Shapes/Triangle.o

.PHONY: clean-src-2f-Shapes

