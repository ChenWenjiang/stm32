#include "hw_config.h"

static void JTAG_Disable(void){
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
}
void HW_Config(void){
    SystemInit();
    JTAG_Disable();
    Alarm_Input_Config();
    LED_Output_Config();
    Run_LED_Config();
    GPIOI2C_Config();
    RS485_Config();
    Other_HW_Config();
}

