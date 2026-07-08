################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ASSIGNMENT/%.o: ../ASSIGNMENT/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/TI/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/TURN" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/ASSIGNMENT" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/IRTRACKING" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/UART" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/SERVO" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/SPEED" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/WIT" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/Irtracking" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/Motor" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/BNO08X_UART_RVC" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/Ultrasonic_GPIO" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/Ultrasonic_Capture" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/OLED_Hardware_I2C" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/OLED_Hardware_SPI" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/OLED_Software_I2C" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/OLED_Software_SPI" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/MPU6050" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/PID" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/INTERRUPT/" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/TURN/" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Debug" -I"F:/TI/mspm0_sdk_2_05_00_05/source/third_party/CMSIS/Core/Include" -I"F:/TI/mspm0_sdk_2_05_00_05/source" -I"C:/Users/ROG/workspace_ccstheia/ThreeLegsCar/Drivers/MSPM0" -DMOTION_DRIVER_TARGET_MSPM0 -DMPU6050 -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"ASSIGNMENT/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


