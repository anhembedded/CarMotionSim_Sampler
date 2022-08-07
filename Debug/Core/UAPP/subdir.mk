################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/UAPP/UAPP_SIMTOOL.cpp 

OBJS += \
./Core/UAPP/UAPP_SIMTOOL.o 

CPP_DEPS += \
./Core/UAPP/UAPP_SIMTOOL.d 


# Each subdirectory must supply rules for building sources it contributes
Core/UAPP/%.o Core/UAPP/%.su: ../Core/UAPP/%.cpp Core/UAPP/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++17 -g -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32F407xx -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -pedantic -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-UAPP

clean-Core-2f-UAPP:
	-$(RM) ./Core/UAPP/UAPP_SIMTOOL.d ./Core/UAPP/UAPP_SIMTOOL.o ./Core/UAPP/UAPP_SIMTOOL.su

.PHONY: clean-Core-2f-UAPP

