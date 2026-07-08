################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Drivers/MPU6050/%.o: ../Drivers/MPU6050/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/TI/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/TURN" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/ASSIGNMENT" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/IRTRACKING" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/UART" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/SERVO" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/SPEED" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/WIT" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/Irtracking" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/Motor" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/BNO08X_UART_RVC" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/Ultrasonic_GPIO" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/Ultrasonic_Capture" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/OLED_Hardware_I2C" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/OLED_Hardware_SPI" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/OLED_Software_I2C" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/OLED_Software_SPI" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/MPU6050" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/PID" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/INTERRUPT/" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/TURN/" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Debug" -I"F:/TI/mspm0_sdk_2_05_00_05/source/third_party/CMSIS/Core/Include" -I"F:/TI/mspm0_sdk_2_05_00_05/source" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCars/Drivers/MSPM0" -DMOTION_DRIVER_TARGET_MSPM0 -DMPU6050 -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Drivers/MPU6050/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


