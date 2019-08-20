################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LammpsIO/DataIO/AddDimension.cpp \
../LammpsIO/DataIO/SetBB.cpp \
../LammpsIO/DataIO/SetDefaults.cpp \
../LammpsIO/DataIO/SetMolecule.cpp \
../LammpsIO/DataIO/SetVel.cpp \
../LammpsIO/DataIO/SetBond.cpp \
../LammpsIO/DataIO/SetID.cpp \
../LammpsIO/DataIO/SetPos.cpp \
../LammpsIO/DataIO/StatementOrderError.cpp \
../LammpsIO/DataIO/OpenO.cpp \
../LammpsIO/DataIO/SetBondType.cpp \
../LammpsIO/DataIO/SetMass.cpp \
../LammpsIO/DataIO/SetType.cpp \
../LammpsIO/DataIO/WriteData.cpp 

OBJS += \
./LammpsIO/DataIO/AddDimension.o \
./LammpsIO/DataIO/SetBB.o \
./LammpsIO/DataIO/SetDefaults.o \
./LammpsIO/DataIO/SetMolecule.o \
./LammpsIO/DataIO/SetVel.o \
./LammpsIO/DataIO/SetBond.o \
./LammpsIO/DataIO/SetID.o \
./LammpsIO/DataIO/SetPos.o \
./LammpsIO/DataIO/StatementOrderError.o \
./LammpsIO/DataIO/OpenO.o \
./LammpsIO/DataIO/SetBondType.o \
./LammpsIO/DataIO/SetMass.o \
./LammpsIO/DataIO/SetType.o \
./LammpsIO/DataIO/WriteData.o

CPP_DEPS += \
./LammpsIO/DataIO/AddDimension.d \
./LammpsIO/DataIO/SetBB.d \
./LammpsIO/DataIO/SetDefaults.d \
./LammpsIO/DataIO/SetMolecule.d \
./LammpsIO/DataIO/SetVel.d \
./LammpsIO/DataIO/SetBond.d \
./LammpsIO/DataIO/SetID.d \
./LammpsIO/DataIO/SetPos.d \
./LammpsIO/DataIO/StatementOrderError.d \
./LammpsIO/DataIO/OpenO.d \
./LammpsIO/DataIO/SetBondType.d \
./LammpsIO/DataIO/SetMass.d \
./LammpsIO/DataIO/SetType.d \
./LammpsIO/DataIO/WriteData.d

# Each subdirectory must supply rules for building sources it contributes
LammpsIO/DataIO/%.o: ../LammpsIO/DataIO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


