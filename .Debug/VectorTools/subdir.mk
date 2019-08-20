################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../VectorTools/BinValueSortedVec.cpp \
../VectorTools/Clear2DVec.cpp \
../VectorTools/EigenMatToVec2D.cpp \
../VectorTools/MaxCol.cpp \
../VectorTools/MinCol.cpp \
../VectorTools/Vec2DToEigenMat.cpp \
../VectorTools/Mean1D.cpp \
../VectorTools/Std1D.cpp \
../VectorTools/Multiply1D.cpp


OBJS += \
./VectorTools/BinValueSortedVec.o \
./VectorTools/Clear2DVec.o \
./VectorTools/EigenMatToVec2D.o \
./VectorTools/MaxCol.o \
./VectorTools/MinCol.o \
./VectorTools/Vec2DToEigenMat.o \
./VectorTools/Mean1D.o \
./VectorTools/Std1D.o \
./VectorTools/Multiply1D.o

CPP_DEPS += \
./VectorTools/BinValueSortedVec.d \
./VectorTools/Clear2DVec.d \
./VectorTools/EigenMatToVec2D.d \
./VectorTools/MaxCol.d \
./VectorTools/MinCol.d \
./VectorTools/Vec2DToEigenMat.d \
./VectorTools/Mean1D.d \
./VectorTools/Std1D.d \
./VectorTools/Multiply1D.d


# Each subdirectory must supply rules for building sources it contributes
VectorTools/%.o: ../VectorTools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


