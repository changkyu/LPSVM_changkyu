################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/lpsvm_log.cpp \
../src/lpsvm_options.cpp \
../src/lpsvm_parser.cpp \
../src/lpsvm_simplexsolver.cpp \
../src/main.cpp 

OBJS += \
./src/lpsvm_log.o \
./src/lpsvm_options.o \
./src/lpsvm_parser.o \
./src/lpsvm_simplexsolver.o \
./src/main.o 

CPP_DEPS += \
./src/lpsvm_log.d \
./src/lpsvm_options.d \
./src/lpsvm_parser.d \
./src/lpsvm_simplexsolver.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/changkyu/projects/LPsvm_changkyu/include -I/usr/include/eigen3 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


