################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LammpsIO/NetCDFIO/CloseI.cpp \
../LammpsIO/NetCDFIO/CloseO.cpp \
../LammpsIO/NetCDFIO/DefineDimensions.cpp \
../LammpsIO/NetCDFIO/DefineGlobalAttributes.cpp \
../LammpsIO/NetCDFIO/DefineVariables.cpp \
../LammpsIO/NetCDFIO/GetBB.cpp \
../LammpsIO/NetCDFIO/GetDataCol.cpp \
../LammpsIO/NetCDFIO/GetPos.cpp \
../LammpsIO/NetCDFIO/Gett.cpp \
../LammpsIO/NetCDFIO/NumDims.cpp \
../LammpsIO/NetCDFIO/NumFrames.cpp \
../LammpsIO/NetCDFIO/NumParts.cpp \
../LammpsIO/NetCDFIO/OpenI.cpp \
../LammpsIO/NetCDFIO/OpenNCO.cpp \
../LammpsIO/NetCDFIO/OpenO.cpp \
../LammpsIO/NetCDFIO/SetAtomDim.cpp \
../LammpsIO/NetCDFIO/SetBB.cpp \
../LammpsIO/NetCDFIO/SetDataCol.cpp \
../LammpsIO/NetCDFIO/SetDataColVar.cpp \
../LammpsIO/NetCDFIO/SetDimAtt.cpp \
../LammpsIO/NetCDFIO/SetLabelVariables.cpp \
../LammpsIO/NetCDFIO/SetPos.cpp \
../LammpsIO/NetCDFIO/SetPosVar.cpp \
../LammpsIO/NetCDFIO/Sett.cpp 

OBJS += \
./LammpsIO/NetCDFIO/CloseI.o \
./LammpsIO/NetCDFIO/CloseO.o \
./LammpsIO/NetCDFIO/DefineDimensions.o \
./LammpsIO/NetCDFIO/DefineGlobalAttributes.o \
./LammpsIO/NetCDFIO/DefineVariables.o \
./LammpsIO/NetCDFIO/GetBB.o \
./LammpsIO/NetCDFIO/GetDataCol.o \
./LammpsIO/NetCDFIO/GetPos.o \
./LammpsIO/NetCDFIO/Gett.o \
./LammpsIO/NetCDFIO/NumDims.o \
./LammpsIO/NetCDFIO/NumFrames.o \
./LammpsIO/NetCDFIO/NumParts.o \
./LammpsIO/NetCDFIO/OpenI.o \
./LammpsIO/NetCDFIO/OpenNCO.o \
./LammpsIO/NetCDFIO/OpenO.o \
./LammpsIO/NetCDFIO/SetAtomDim.o \
./LammpsIO/NetCDFIO/SetBB.o \
./LammpsIO/NetCDFIO/SetDataCol.o \
./LammpsIO/NetCDFIO/SetDataColVar.o \
./LammpsIO/NetCDFIO/SetDimAtt.o \
./LammpsIO/NetCDFIO/SetLabelVariables.o \
./LammpsIO/NetCDFIO/SetPos.o \
./LammpsIO/NetCDFIO/SetPosVar.o \
./LammpsIO/NetCDFIO/Sett.o 

CPP_DEPS += \
./LammpsIO/NetCDFIO/CloseI.d \
./LammpsIO/NetCDFIO/CloseO.d \
./LammpsIO/NetCDFIO/DefineDimensions.d \
./LammpsIO/NetCDFIO/DefineGlobalAttributes.d \
./LammpsIO/NetCDFIO/DefineVariables.d \
./LammpsIO/NetCDFIO/GetBB.d \
./LammpsIO/NetCDFIO/GetDataCol.d \
./LammpsIO/NetCDFIO/GetPos.d \
./LammpsIO/NetCDFIO/Gett.d \
./LammpsIO/NetCDFIO/NumDims.d \
./LammpsIO/NetCDFIO/NumFrames.d \
./LammpsIO/NetCDFIO/NumParts.d \
./LammpsIO/NetCDFIO/OpenI.d \
./LammpsIO/NetCDFIO/OpenNCO.d \
./LammpsIO/NetCDFIO/OpenO.d \
./LammpsIO/NetCDFIO/SetAtomDim.d \
./LammpsIO/NetCDFIO/SetBB.d \
./LammpsIO/NetCDFIO/SetDataCol.d \
./LammpsIO/NetCDFIO/SetDataColVar.d \
./LammpsIO/NetCDFIO/SetDimAtt.d \
./LammpsIO/NetCDFIO/SetLabelVariables.d \
./LammpsIO/NetCDFIO/SetPos.d \
./LammpsIO/NetCDFIO/SetPosVar.d \
./LammpsIO/NetCDFIO/Sett.d 


# Each subdirectory must supply rules for building sources it contributes
LammpsIO/NetCDFIO/%.o: ../LammpsIO/NetCDFIO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"$(NETCDFHOME)/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


