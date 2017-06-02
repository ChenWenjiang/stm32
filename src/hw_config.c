#include "hw_config.h"
#include "eeprom.h"
#include "globalvar.h"
#include "rtu.h"
#include "switch.h"

static void JTAG_Disable(void){
    //GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
}
void HW_Config(void){
    SystemInit();
    JTAG_Disable();
    Switch_Config();
    setInputNumber();
    Alarm_Input_Config();
    LED_Output_Config();
    Run_LED_Config();
    GPIOI2C_Config();
    eeprom_load();
    if(2 & Read_Set_Arg_Switch()){ //key 1
      regsInit(gModbusAddr,2,0);
    }else{
    //gRS485Config = 0x11;
      regsInit(gModbusAddr,(gRS485Config>>4)&0x0f,gRS485Config&0x0f);
    }
    RS485_Config();
    Other_HW_Config();
}

