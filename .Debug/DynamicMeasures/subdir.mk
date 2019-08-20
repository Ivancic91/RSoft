################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DynamicMeasures/D2min.cpp \
../DynamicMeasures/D2minAllParticles.cpp \
../DynamicMeasures/J2.cpp \
../DynamicMeasures/J2AllParticles.cpp \
../DynamicMeasures/J2plane.cpp \
../DynamicMeasures/J2planeAllParticles.cpp \
../DynamicMeasures/LambdaMin.cpp \
../DynamicMeasures/Phop.cpp \
../DynamicMeasures/PhopAllParticles.cpp

OBJS += \
./DynamicMeasures/D2min.o \
./DynamicMeasures/D2minAllParticles.o \
./DynamicMeasures/J2.o \
./DynamicMeasures/J2AllParticles.o \
./DynamicMeasures/J2plane.o \
./DynamicMeasures/J2planeAllParticles.o \
./DynamicMeasures/LambdaMin.o \
./DynamicMeasures/Phop.o \
./DynamicMeasures/PhopAllParticles.o

CPP_DEPS += \
./DynamicMeausres/D2min.d \
./DynamicMeasures/D2minAllParticles.d \
./DynamicMeausres/J2.d \
./DynamicMeasures/J2AllParticles.d \
./DynamicMeausres/J2plane.d \
./DynamicMeasures/J2planeAllParticles.d \
./DynamicMeasures/LambdaMin.d \
./DynamicMeasures/Phop.d \
./DynamicMeasures/PhopAllParticles.d


# Each subdirectory must supply rules for building sources it contributes
DynamicMeasures/%.o: ../DynamicMeasures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
