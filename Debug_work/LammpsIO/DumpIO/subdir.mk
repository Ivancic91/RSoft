################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LammpsIO/DumpIO/AnalyzeItemAtomsLine.cpp \
../LammpsIO/DumpIO/GetBB.cpp \
../LammpsIO/DumpIO/GetDataCol.cpp \
../LammpsIO/DumpIO/GetDataColLabels.cpp \
../LammpsIO/DumpIO/GetID.cpp \
../LammpsIO/DumpIO/GetPos.cpp \
../LammpsIO/DumpIO/Getf.cpp \
../LammpsIO/DumpIO/Gett.cpp \
../LammpsIO/DumpIO/InitializeParameters.cpp \
../LammpsIO/DumpIO/InitializeWriteParameters.cpp \
../LammpsIO/DumpIO/LoadAtomData.cpp \
../LammpsIO/DumpIO/LoadHeader.cpp \
../LammpsIO/DumpIO/LoadNextFrame.cpp \
../LammpsIO/DumpIO/NextElem.cpp \
../LammpsIO/DumpIO/NumDataCols.cpp \
../LammpsIO/DumpIO/NumDims.cpp \
../LammpsIO/DumpIO/NumFrames.cpp \
../LammpsIO/DumpIO/NumPartsCurrentf.cpp \
../LammpsIO/DumpIO/OpenI.cpp \
../LammpsIO/DumpIO/OpenO.cpp \
../LammpsIO/DumpIO/SetBB.cpp \
../LammpsIO/DumpIO/SetDataCol.cpp \
../LammpsIO/DumpIO/SetID.cpp \
../LammpsIO/DumpIO/SetPos.cpp \
../LammpsIO/DumpIO/Sett.cpp \
../LammpsIO/DumpIO/SortByID.cpp \
../LammpsIO/DumpIO/WriteItemAtoms.cpp \
../LammpsIO/DumpIO/WriteNextFrame.cpp

OBJS += \
./LammpsIO/DumpIO/AnalyzeItemAtomsLine.o \
./LammpsIO/DumpIO/GetBB.o \
./LammpsIO/DumpIO/GetDataCol.o \
./LammpsIO/DumpIO/GetDataColLabels.o \
./LammpsIO/DumpIO/GetID.o \
./LammpsIO/DumpIO/GetPos.o \
./LammpsIO/DumpIO/Getf.o \
./LammpsIO/DumpIO/Gett.o \
./LammpsIO/DumpIO/InitializeParameters.o \
./LammpsIO/DumpIO/InitializeWriteParameters.o \
./LammpsIO/DumpIO/LoadAtomData.o \
./LammpsIO/DumpIO/LoadHeader.o \
./LammpsIO/DumpIO/LoadNextFrame.o \
./LammpsIO/DumpIO/NextElem.o \
./LammpsIO/DumpIO/NumDataCols.o \
./LammpsIO/DumpIO/NumDims.o \
./LammpsIO/DumpIO/NumFrames.o \
./LammpsIO/DumpIO/NumPartsCurrentf.o \
./LammpsIO/DumpIO/OpenI.o \
./LammpsIO/DumpIO/OpenO.o \
./LammpsIO/DumpIO/SetBB.o \
./LammpsIO/DumpIO/SetDataCol.o \
./LammpsIO/DumpIO/SetID.o \
./LammpsIO/DumpIO/SetPos.o \
./LammpsIO/DumpIO/Sett.o \
./LammpsIO/DumpIO/SortByID.o \
./LammpsIO/DumpIO/WriteItemAtoms.o \
./LammpsIO/DumpIO/WriteNextFrame.o

CPP_DEPS += \
./LammpsIO/DumpIO/AnalyzeItemAtomsLine.d \
./LammpsIO/DumpIO/GetBB.d \
./LammpsIO/DumpIO/GetDataCol.d \
./LammpsIO/DumpIO/GetDataColLabels.d \
./LammpsIO/DumpIO/GetID.d \
./LammpsIO/DumpIO/GetPos.d \
./LammpsIO/DumpIO/Getf.d \
./LammpsIO/DumpIO/Gett.d \
./LammpsIO/DumpIO/InitializeParameters.d \
./LammpsIO/DumpIO/InitializeWriteParameters.d \
./LammpsIO/DumpIO/LoadAtomData.d \
./LammpsIO/DumpIO/LoadHeader.d \
./LammpsIO/DumpIO/LoadNextFrame.d \
./LammpsIO/DumpIO/NextElem.d \
./LammpsIO/DumpIO/NumDataCols.d \
./LammpsIO/DumpIO/NumDims.d \
./LammpsIO/DumpIO/NumFrames.d \
./LammpsIO/DumpIO/NumPartsCurrentf.d \
./LammpsIO/DumpIO/OpenI.d \
./LammpsIO/DumpIO/OpenO.d \
./LammpsIO/DumpIO/SetBB.d \
./LammpsIO/DumpIO/SetDataCol.d \
./LammpsIO/DumpIO/SetID.d \
./LammpsIO/DumpIO/SetPos.d \
./LammpsIO/DumpIO/Sett.d \
./LammpsIO/DumpIO/SortByID.d \
./LammpsIO/DumpIO/WriteItemAtoms.d \
./LammpsIO/DumpIO/WriteNextFrame.d

# Each subdirectory must supply rules for building sources it contributes
LammpsIO/DumpIO/%.o: ../LammpsIO/DumpIO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


