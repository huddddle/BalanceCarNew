################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/TI/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/TURN" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/AssignmentChoose" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/IRTRACKING" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/UART" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/SERVO" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/SPEED" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/WIT" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Irtracking" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Motor" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/BNO08X_UART_RVC" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Ultrasonic_GPIO" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Ultrasonic_Capture" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/TrackingMoudleIIC" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Hardware_I2C" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Hardware_SPI" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Software_I2C" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Software_SPI" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Bluetooth" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/MPU6050" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/PID" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/INTERRUPT/" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/TURN/" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Move" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Debug" -I"F:/TI/mspm0_sdk_2_05_00_05/source/third_party/CMSIS/Core/Include" -I"F:/TI/mspm0_sdk_2_05_00_05/source" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/MSPM0" -DMOTION_DRIVER_TARGET_MSPM0 -DMPU6050 -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1319443153: ../mspm0-modules.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"F:/TI/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" -s "F:/TI/mspm0_sdk_2_05_00_05/.metadata/product.json" --script "C:/Users/ROG/workspace_ccstheia/BalanceCarNew/mspm0-modules.syscfg" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1319443153 ../mspm0-modules.syscfg
device.opt: build-1319443153
device.cmd.genlibs: build-1319443153
ti_msp_dl_config.c: build-1319443153
ti_msp_dl_config.h: build-1319443153
Event.dot: build-1319443153

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/TI/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/TURN" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/AssignmentChoose" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/IRTRACKING" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/UART" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/SERVO" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/SPEED" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/WIT" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Irtracking" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Motor" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/BNO08X_UART_RVC" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Ultrasonic_GPIO" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Ultrasonic_Capture" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/TrackingMoudleIIC" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Hardware_I2C" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Hardware_SPI" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Software_I2C" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Software_SPI" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Bluetooth" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/MPU6050" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/PID" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/INTERRUPT/" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/TURN/" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Move" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Debug" -I"F:/TI/mspm0_sdk_2_05_00_05/source/third_party/CMSIS/Core/Include" -I"F:/TI/mspm0_sdk_2_05_00_05/source" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/MSPM0" -DMOTION_DRIVER_TARGET_MSPM0 -DMPU6050 -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: F:/TI/mspm0_sdk_2_05_00_05/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/TI/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/TURN" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/AssignmentChoose" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/IRTRACKING" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/UART" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/SERVO" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/SPEED" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/WIT" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Irtracking" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Motor" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/BNO08X_UART_RVC" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Ultrasonic_GPIO" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Ultrasonic_Capture" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/TrackingMoudleIIC" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Hardware_I2C" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Hardware_SPI" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Software_I2C" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/OLED_Software_SPI" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/Bluetooth" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/MPU6050" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/PID" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/INTERRUPT/" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/TURN/" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Move" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Debug" -I"F:/TI/mspm0_sdk_2_05_00_05/source/third_party/CMSIS/Core/Include" -I"F:/TI/mspm0_sdk_2_05_00_05/source" -I"C:/Users/ROG/workspace_ccstheia/BalanceCarNew/Drivers/MSPM0" -DMOTION_DRIVER_TARGET_MSPM0 -DMPU6050 -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


