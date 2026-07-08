################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Drivers/TrackingModuleIIC/%.o: ../Drivers/TrackingModuleIIC/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/TI/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/TURN" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/AssignmentChoose" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/IRTRACKING" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/UART" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/SERVO" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/SPEED" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/WIT" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/Irtracking" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/Motor" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/BNO08X_UART_RVC" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/Ultrasonic_GPIO" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/Ultrasonic_Capture" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/TrackingMoudleIIC" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/OLED_Hardware_I2C" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/OLED_Hardware_SPI" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/OLED_Software_I2C" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/OLED_Software_SPI" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/Bluetooth" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/MPU6050" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/PID" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/INTERRUPT/" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/TURN/" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Move" -I"C:/Users/ROG/workspace_ccstheia/LittleCar" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Debug" -I"F:/TI/mspm0_sdk_2_05_00_05/source/third_party/CMSIS/Core/Include" -I"F:/TI/mspm0_sdk_2_05_00_05/source" -I"C:/Users/ROG/workspace_ccstheia/LittleCar/Drivers/MSPM0" -DMOTION_DRIVER_TARGET_MSPM0 -DMPU6050 -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Drivers/TrackingModuleIIC/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


