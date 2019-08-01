################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../RSoft/OpenSFI.cpp \
../RSoft/CheckNCError.cpp \
../RSoft/GetSFParams.cpp \
../RSoft/OpenPlaneI.cpp \
../RSoft/OpenSFO.cpp \
../RSoft/SetSFParams.cpp \
../RSoft/CheckDim.cpp \
../RSoft/CheckNumParts.cpp \
../RSoft/CheckSets.cpp \
../RSoft/CalculateRadialSFs.cpp \
../RSoft/CalculateNListRList.cpp \
../RSoft/GetRcRadial.cpp \
../RSoft/GetRcAngular.cpp \
../RSoft/ResetSets.cpp \
../RSoft/SetPos.cpp \
../RSoft/SetBB.cpp \
../RSoft/SetBC.cpp \
../RSoft/SetType.cpp \
../RSoft/GetRadialSFs.cpp \
../RSoft/CalculateRadialSFs.cpp \
../RSoft/CalculateRadialSF_p_n.cpp \
../RSoft/GetAngularSFs.cpp \
../RSoft/CalculateAngularSFs.cpp \
../RSoft/CalculateAngularSFs_p.cpp \
../RSoft/WriteSFs.cpp \
../RSoft/ReadSFs.cpp \
../RSoft/CloseSFO.cpp \
../RSoft/CloseSFI.cpp \
../RSoft/ClosePlaneI.cpp \
../RSoft/GetSoftness.cpp \
../RSoft/GetMus.cpp \
../RSoft/GetLs.cpp \
../RSoft/GetRadialXs.cpp \
../RSoft/GetRadialYs.cpp \
../RSoft/GetRadialEtol.cpp 

OBJS += \
./RSoft/OpenSFI.o \
./RSoft/CheckNCError.o \
./RSoft/GetSFParams.o \
./RSoft/OpenPlaneI.o \
./RSoft/OpenSFO.o \
./RSoft/SetSFParams.o \
./RSoft/CheckDim.o \
./RSoft/CheckNumParts.o \
./RSoft/CheckSets.o \
./RSoft/CalculateNListRList.o \
./RSoft/GetRcRadial.o \
./RSoft/GetRcAngular.o \
./RSoft/ResetSets.o \
./RSoft/SetPos.o \
./RSoft/SetBB.o \
./RSoft/SetBC.o \
./RSoft/SetType.o \
./RSoft/GetRadialSFs.o \
./RSoft/CalculateRadialSFs.o \
./RSoft/CalculateRadialSF_p_n.o \
./RSoft/GetAngularSFs.o \
./RSoft/CalculateAngularSFs.o \
./RSoft/CalculateAngularSFs_p.o \
./RSoft/WriteSFs.o \
./RSoft/ReadSFs.o \
./RSoft/CloseSFO.o \
./RSoft/CloseSFI.o \
./RSoft/ClosePlaneI.o \
./RSoft/GetSoftness.o \
./RSoft/GetMus.o \
./RSoft/GetLs.o \
./RSoft/GetRadialXs.o \
./RSoft/GetRadialYs.o \
./RSoft/GetRadialEtol.o 

CPP_DEPS += \
./RSoft/SetDim.d \
./RSoft/CheckNCError.d \
./RSoft/GetSFParams.d \
./RSoft/OpenPlaneI.d \
./RSoft/OpenSFO.d \
./RSoft/SetSFParams.d \
./RSoft/CheckDim.d \
./RSoft/CheckNumParts.d \
./RSoft/CheckSets.d \
./RSoft/CalculateNListRList.d \
./RSoft/GetRcRadial.d \
./RSoft/GetRcAngular.d \
./RSoft/ResetSets.d \
./RSoft/SetPos.d \
./RSoft/SetBB.d \
./RSoft/SetBC.d \
./RSoft/SetType.d \
./RSoft/GetRadialSFs.d \
./RSoft/CalculateRadialSFs.d \
./RSoft/CalculateRadialSF_p_n.d \
./RSoft/GetAngularSFs.d \
./RSoft/CalculateAngularSFs.d \
./RSoft/CalculateAngularSFs_p.d \
./RSoft/WriteSFs.d \
./RSoft/ReadSFs.d \
./RSoft/CloseSFO.d \
./RSoft/CloseSFI.d \
./RSoft/ClosePlaneI.d \
./RSoft/GetSoftness.d \
./RSoft/GetMus.d \
./RSoft/GetLs.d \
./RSoft/GetRadialXs.d \
./RSoft/GetRadialYs.d \
./RSoft/GetRadialEtol.d 

# Each subdirectory must supply rules for building sources it contributes
RSoft/%.o: ../RSoft/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I$(NETCDFHOME)/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
