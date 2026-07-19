################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/TI/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/TURN" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/AssignmentChoose" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/IRTRACKING" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/UART" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/VisionTracking" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Hostcom" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/GBControl" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Bluetooth" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/SERVO" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/SPEED" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/WIT" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/TrackingModuleIIC" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Motor" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/BNO08X_UART_RVC" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Ultrasonic_GPIO" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Ultrasonic_Capture" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/GBControl" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/TrackingMoudleIIC" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Hardware_I2C" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Hardware_SPI" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Software_I2C" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Software_SPI" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Hostcom" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/MPU6050" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/PID" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/INTERRUPT/" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/TURN/" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Move" -I"D:/Electric/My_TI_Workspace/BalanceCarNew" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Debug" -I"C:/TI/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_04_00_06/source" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/MSPM0" -DMOTION_DRIVER_TARGET_MSPM0 -DMPU6050 -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1319443153: ../mspm0-modules.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/TI/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" -s "C:/TI/mspm0_sdk_2_04_00_06/.metadata/product.json" --script "D:/Electric/My_TI_Workspace/BalanceCarNew/mspm0-modules.syscfg" -o "." --compiler ticlang
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
	"D:/TI/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/TURN" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/AssignmentChoose" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/IRTRACKING" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/UART" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/VisionTracking" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Hostcom" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/GBControl" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Bluetooth" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/SERVO" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/SPEED" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/WIT" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/TrackingModuleIIC" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Motor" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/BNO08X_UART_RVC" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Ultrasonic_GPIO" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Ultrasonic_Capture" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/GBControl" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/TrackingMoudleIIC" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Hardware_I2C" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Hardware_SPI" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Software_I2C" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Software_SPI" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Hostcom" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/MPU6050" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/PID" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/INTERRUPT/" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/TURN/" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Move" -I"D:/Electric/My_TI_Workspace/BalanceCarNew" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Debug" -I"C:/TI/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_04_00_06/source" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/MSPM0" -DMOTION_DRIVER_TARGET_MSPM0 -DMPU6050 -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/TI/mspm0_sdk_2_04_00_06/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/TI/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/TURN" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/AssignmentChoose" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/IRTRACKING" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/UART" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/VisionTracking" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Hostcom" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/GBControl" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Bluetooth" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/SERVO" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/SPEED" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/WIT" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/TrackingModuleIIC" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Motor" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/BNO08X_UART_RVC" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Ultrasonic_GPIO" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Ultrasonic_Capture" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/GBControl" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/TrackingMoudleIIC" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Hardware_I2C" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Hardware_SPI" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Software_I2C" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/OLED_Software_SPI" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/Hostcom" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/MPU6050" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/PID" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/INTERRUPT/" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/TURN/" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Move" -I"D:/Electric/My_TI_Workspace/BalanceCarNew" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Debug" -I"C:/TI/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/TI/mspm0_sdk_2_04_00_06/source" -I"D:/Electric/My_TI_Workspace/BalanceCarNew/Drivers/MSPM0" -DMOTION_DRIVER_TARGET_MSPM0 -DMPU6050 -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


