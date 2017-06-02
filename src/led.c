#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "led.h"
#include "globalvar.h"
#include "eeprom.h"

#include "other_hw_config.h"

//uint8_t gSetCnt;

void inputInit(void)
{
    gMap[0].addr = GPIOE;
    gMap[0].loc = GPIO_Pin_4;
    gMap[0].ledloc = 0;

    gMap[1].addr = GPIOE;
    gMap[1].loc = GPIO_Pin_5;
    gMap[1].ledloc = 1;
    
    gMap[2].addr = GPIOE;
    gMap[2].loc = GPIO_Pin_6;
    gMap[2].ledloc = 2;
    
    gMap[3].addr = GPIOC;
    gMap[3].loc = GPIO_Pin_13;
    gMap[3].ledloc = 3;
    
    gMap[4].addr = GPIOF;
    gMap[4].loc = GPIO_Pin_0;
    gMap[4].ledloc = 4;
    
    gMap[5].addr = GPIOF;
    gMap[5].loc = GPIO_Pin_1;
    gMap[5].ledloc = 5;
    
    gMap[6].addr = GPIOF;
    gMap[6].loc = GPIO_Pin_2;
    gMap[6].ledloc = 6;
    
    gMap[7].addr = GPIOF;
    gMap[7].loc = GPIO_Pin_3;
    gMap[7].ledloc = 7;
    
    gMap[8].addr = GPIOF;
    gMap[8].loc = GPIO_Pin_4;
    gMap[8].ledloc = 8;
    
    gMap[9].addr = GPIOF;
    gMap[9].loc = GPIO_Pin_5;
    gMap[9].ledloc = 9;
    
    gMap[10].addr = GPIOF;
    gMap[10].loc = GPIO_Pin_6;
    gMap[10].ledloc = 10;
    
    gMap[11].addr = GPIOF;
    gMap[11].loc = GPIO_Pin_7;
    gMap[11].ledloc = 11;
    
    gMap[12].addr = GPIOF;
    gMap[12].loc = GPIO_Pin_8;
    gMap[12].ledloc = 12;
    
    gMap[13].addr = GPIOF;
    gMap[13].loc = GPIO_Pin_9;
    gMap[13].ledloc = 13;
    
    gMap[14].addr = GPIOF;
    gMap[14].loc = GPIO_Pin_10;
    gMap[14].ledloc = 14;
    
    gMap[15].addr = GPIOC;
    gMap[15].loc = GPIO_Pin_0;
    gMap[15].ledloc = 15;
    
    gMap[16].addr = GPIOC;
    gMap[16].loc = GPIO_Pin_1;
    gMap[16].ledloc = 16;
    
    gMap[17].addr = GPIOC;
    gMap[17].loc = GPIO_Pin_2;
    gMap[17].ledloc = 17;
    
    gMap[18].addr = GPIOC;
    gMap[18].loc = GPIO_Pin_3;
    gMap[18].ledloc = 18;
    
    gMap[19].addr = GPIOA;
    gMap[19].loc = GPIO_Pin_1;
    gMap[19].ledloc = 19;
    
    gMap[20].addr = GPIOA;
    gMap[20].loc = GPIO_Pin_2;
    gMap[20].ledloc = 20;
    
    gMap[21].addr = GPIOA;
    gMap[21].loc = GPIO_Pin_3;
    gMap[21].ledloc = 21;
    
    gMap[22].addr = GPIOA;
    gMap[22].loc = GPIO_Pin_4;
    gMap[22].ledloc = 22;
    
    gMap[23].addr = GPIOA;
    gMap[23].loc = GPIO_Pin_5;
    gMap[23].ledloc = 23;
    
    gMap[24].addr = GPIOA;
    gMap[24].loc = GPIO_Pin_6;
    gMap[24].ledloc = 24;
    
    gMap[25].addr = GPIOA;
    gMap[25].loc = GPIO_Pin_7;
    gMap[25].ledloc = 25;
    
    gMap[26].addr = GPIOC;
    gMap[26].loc = GPIO_Pin_4;
    gMap[26].ledloc = 26;
    
    gMap[27].addr = GPIOC;
    gMap[27].loc = GPIO_Pin_5;
    gMap[27].ledloc = 27;
    
    gMap[28].addr = GPIOB;
    gMap[28].loc = GPIO_Pin_0;
    gMap[28].ledloc = 28;
    
    gMap[29].addr = GPIOB;
    gMap[29].loc = GPIO_Pin_1;
    gMap[29].ledloc = 29;
    
    gMap[30].addr = GPIOB;
    gMap[30].loc = GPIO_Pin_2;
    gMap[30].ledloc = 30;
    
    gMap[31].addr = GPIOF;
    gMap[31].loc = GPIO_Pin_11;
    gMap[31].ledloc = 31;
    
    gMap[ACK].addr = GPIOG;
    gMap[ACK].loc = GPIO_Pin_14;
    gMap[ACK].ledloc = ACK;

    gMap[RST].addr = GPIOG;
    gMap[RST].loc = GPIO_Pin_15;
    gMap[RST].ledloc = RST;

    //gMap[TEST].addr = GPIOB;
    //gMap[TEST].loc = GPIO_Pin_3;
    gMap[TEST].addr = GPIOC;
    gMap[TEST].loc = GPIO_Pin_7;
    gMap[TEST].ledloc = TEST;

    gMap[MEM].addr = GPIOB;
    gMap[MEM].loc = GPIO_Pin_5;
    gMap[MEM].ledloc = MEM;

    gMap[MOV].addr = GPIOB;
    gMap[MOV].loc = GPIO_Pin_9;
    gMap[MOV].ledloc = MOV;
    
    gMap[ADD].addr = GPIOB;
    gMap[ADD].loc = GPIO_Pin_8;
    gMap[ADD].ledloc = ADD;

    gMap[ENT].addr = GPIOB;
    gMap[ENT].loc = GPIO_Pin_4;
    gMap[ENT].ledloc = ENT;
    
    gMap[ACK_IN].addr = GPIOC;
    gMap[ACK_IN].loc = GPIO_Pin_9;
    gMap[ACK_IN].ledloc = ACK_IN;

    gMap[RST_IN].addr = GPIOC;
    gMap[RST_IN].loc = GPIO_Pin_8;
    gMap[RST_IN].ledloc = RST_IN;

    gMap[TEST_IN].addr = GPIOA;
    gMap[TEST_IN].loc = GPIO_Pin_9;
    gMap[TEST_IN].ledloc = TEST_IN;

    gMap[MEM_IN].addr = GPIOA;
    gMap[MEM_IN].loc = GPIO_Pin_8;
    gMap[MEM_IN].ledloc = MEM_IN;

}
uint32_t memColor = 0;
uint32_t testColor = 0;
void setState(void)
{
  static uint8_t mem = 0;
  static uint8_t mem_cnt = 0;

  uint32_t inputFlag = gInputFlag;
  uint32_t inputReleaseFlag = gInputReleaseFlag;
  uint32_t inputDetected = inputFlag & inputReleaseFlag;

  uint16_t buttonInputFlag = gButtonInputFlag;
  uint16_t buttonReleaseFlag = gButtonReleaseFlag;
  uint16_t buttonDetected = buttonInputFlag & buttonReleaseFlag;

  uint8_t doubleButtonFlag = gDoubleButtonFlag;
  uint8_t doubleButtonReleaseFlag = gDoubleButtonReleaseFlag;
  uint8_t doubleButtonDetected = doubleButtonFlag & doubleButtonReleaseFlag;
  static uint32_t colorBackup = 0;
  static uint8_t colorChanged = 0;
  if(inputFlag){  //alarm
    if(colorChanged){
      gColor = colorBackup;
      colorChanged = 0;
    }
    if((gState==SACK)||(gState==SALARM)){
      gLight |= inputFlag;
      gTwink |= inputFlag;
    }else{
      gLight = inputFlag;
      gTwink = inputFlag;
    }
    gState = SALARM;
    if(inputDetected){
      int i = 0;
      for(;i<32;i++){
        if(inputDetected & (1<<i)){
          if(gColor & (1<<i))
            gHistory[gHistoryPointer] = i+32;
          else
            gHistory[gHistoryPointer] = i;
          gHistoryPointer = (gHistoryPointer+1)%256;
          if(gHistoryNum<256)
            gHistoryNum++;
        }
      }
      eeprom_store_history();
      gInputReleaseFlag = 0;
      gInputFlag = 0;
    }
    regs[73].val = 0;
    regs[74].val = 0;
    regs[75].val = 0;
  }else if((buttonDetected & 0x0102) || regs[74].val){  //rst
    int i = 0;
    if(colorChanged){
      gColor = colorBackup;
      colorChanged = 0;
    }
    //if(doubleButtonDetected & 1)
    //  goto clearmem;
    //else if(doubleButtonFlag &1)
    //  return ;
    gState = SNORMAL;
    gLight = 0;
    gTwink = 0;
    gButtonInputFlag =0;//&=(~buttonDetected);
    gButtonReleaseFlag =0;//&=(~buttonDetected);
    gDoubleButtonReleaseFlag = 0;
    gDoubleButtonFlag = 0;
    for(i=0;i<34;i++){
      regs[5+i].val = 0;
      regs[39+i].val = 0;
    }
    regs[73].val = 0;
    regs[74].val = 0;
    regs[75].val = 0;
    regs[3].val = 0;
    regs[4].val = 0;
    soundAlarmClose();
    soundPreAlarmClose();
  }else if((gState == SALARM)
      &&((buttonDetected & 0x0081)||(regs[73].val))){  //ack
    int i = 0;
    gState = SACK;
    gTwink = 0;
    gButtonInputFlag =0;//&=(~buttonDetected);
    gButtonReleaseFlag =0;//&=(~buttonDetected);
    for(i=0;i<34;i++){
      regs[5+i].val = 0;
      regs[39+i].val = 0;
    }
    regs[73].val = 0;
    regs[74].val = 0;
    regs[75].val = 0;
    regs[3].val = 0;
    regs[4].val = 0;
    soundAlarmClose();
    soundPreAlarmClose();
  }else if(gState == SNORMAL){
    if(doubleButtonDetected & 1){//RST MEM
      gLight = 1;
      gTwink = 1;
      eeprom_clear_history();
      gLight = 3;
      gTwink = 3;
      gDoubleButtonFlag &=0xfe;
      gDoubleButtonReleaseFlag &= 0xfe;
      gButtonReleaseFlag &=(~buttonDetected);
      //  gButtonInputFlag &=(~buttonDetected);
      gButtonInputFlag &=(~(1<<(RST-ALARMNUM)));
      gButtonInputFlag &=(~(1<<(MEM-ALARMNUM)));
      gButtonInputFlag =0;//&=(~buttonDetected);
      gButtonReleaseFlag =0;//&=(~buttonDetected);
      gDoubleButtonReleaseFlag = 0;
      gDoubleButtonFlag = 0;
    }else if(doubleButtonDetected & 2){  //ENT MOV
      gState = SSET;
      gLight = 1;
      gTwink = 1;
      gDoubleButtonReleaseFlag &=0xfd;
      gDoubleButtonFlag &= 0xfd;
      //gButtonInputFlag &= (~buttonDetected);
      gButtonReleaseFlag &= (~buttonDetected);
      gButtonInputFlag &= (~(1<<(ENT-ALARMNUM)));
      gButtonInputFlag &= (~(1<<(MOV-ALARMNUM)));
    }else if((buttonDetected & 0x0204)||(regs[75].val)){ //test
      gTestCnt = 0;
      gState = STEST;
      testColor = 0;

      switch(gInputNumber){
        case 12:
          gLight = 0x00000fff;
          break;
        case 16:
          gLight = 0x0000ffff;
          break;
        case 22:
          gLight = 0x003fffff;
          break;
        case 24:
          gLight = 0x00ffffff;
          break;
        default:
          gLight = 0xffffffff;
      }
      gTwink = gLight;
      gButtonReleaseFlag &= (~buttonDetected);
      gButtonInputFlag &= (~buttonDetected);
      regs[73].val = 0;
      regs[74].val = 0;
      regs[75].val = 0;
    }else if(buttonDetected & 0x0408){ //mem
      gState = SMEM;
      if(gHistoryNum!=0){
        mem_cnt = 1;//gHistoryNum;
        //查找数组中的第一个历史记录
        if(gHistoryPointer!=0)
          mem = gHistoryPointer-1;
        else
          mem = 255;
  //    }
  //    if(gHistoryNum!=0){
        //设置灯位置和颜色
        gLight = 1<<(gHistory[mem]&0x1f);
        gTwink = gLight;
        memColor = ((gHistory[mem]&0x20)?gLight:0);
        //检查是否回忆到最后一个历史记录
        if(mem_cnt==gHistoryNum){
          mem_cnt = 1;
          mem = gHistoryPointer-1;
        }else{
          mem_cnt++;
          mem--;
        }
      }
      gButtonInputFlag &= (~buttonDetected);
      gButtonReleaseFlag &= (~buttonDetected);
    }else if(buttonDetected){
      gButtonInputFlag &= (~buttonDetected);
      gButtonReleaseFlag &= (~buttonDetected);
    }
  }else if(gState ==SMEM){
    if(buttonDetected & 0x0408){ //mem
      if(gHistoryNum!=0){
        gLight = 1<<(gHistory[mem]&0x1f);
        gTwink = gLight;
        memColor = ((gHistory[mem]&0x20)?gLight:0);
        if(mem_cnt==gHistoryNum){
          mem_cnt = 1;
          mem = gHistoryPointer-1;
        }else{
          mem_cnt++;
          mem--;
        }
      }
      gButtonInputFlag &= (~buttonDetected);
      gButtonReleaseFlag &= (~buttonDetected);
    }
  }else if(gState==STEST){
    if((buttonDetected & 0x0204)||(regs[75].val)){ //test
      gTestCnt = (gTestCnt+1)%3;
      if(gTestCnt==1)
        testColor= 0xffffffff;
      else if(gTestCnt==0)
        testColor = 0;
      else if(gTestCnt==2)
        testColor = gColor;
      gButtonReleaseFlag &= (~buttonDetected);
      gButtonInputFlag &= (~buttonDetected);
      regs[73].val = 0;
      regs[74].val = 0;
      regs[75].val = 0;
    }
  }else if(gState==SSET){
    if(buttonDetected & 0x10)//MOV
    {
      if(gLight==(1<<(gInputNumber-1)))
        gLight = 1;
      else
        gLight <<=1;
      gTwink = gLight;
      gButtonReleaseFlag &= (~buttonDetected);
      gButtonInputFlag &= (~buttonDetected);
    }else if(buttonDetected & 0x20)//ADD
    {
      colorBackup = gColor;
      colorChanged = 1;
      if(gColor & gLight)
        gColor &= (~gLight);
      else
        gColor |= gLight;
      gButtonReleaseFlag &= (~buttonDetected);
      gButtonInputFlag &= (~buttonDetected);
    }
    else if(buttonDetected & 0x40)//ENT
    {
      gState = SNORMAL;
      gLight = 0;
      gTwink = 0;
      eeprom_store_color();
      colorChanged = 0;
      gButtonReleaseFlag &= (~buttonDetected);
      gButtonInputFlag &= (~buttonDetected);
    }else if(buttonDetected){
      gButtonReleaseFlag &= (~buttonDetected);
      gButtonInputFlag &= (~buttonDetected);
    }else if(doubleButtonDetected)
    {
      gDoubleButtonFlag &= (~doubleButtonDetected);
      gDoubleButtonReleaseFlag &= (~doubleButtonDetected);
    }
  }
  return ;
}
