#include "rtu.h"
#include "rs485_config.h"
#include "eeprom.h"

uint8_t gModbusAddr = 0;
#define MODBUSADDR (gModbusAddr)

void regsInit(uint8_t busaddr,uint8_t baudrate,uint8_t verification)
{
    int i;
    //bus addr
    regs[0].addr = 0;
    regs[0].val = busaddr;//
    regs[0].mod = 2; //rw

    //baudrate
    regs[1].addr = 1;
    regs[1].val = baudrate;
    regs[1].mod = 2; //rw

    //verification
    regs[2].addr = 2;
    regs[2].val = verification;
    regs[2].mod = 2; //rw

    //global alarm
    regs[3].addr = 0x0010;
    regs[3].val = 0;
    regs[3].mod = 0; //ro

    //pre alarm
    regs[4].addr = 0x0011;
    regs[4].val = 0;
    regs[4].mod = 0;

    //input 1
    regs[5].addr = 0x0100;
    regs[5].val = 0;
    regs[5].mod = 0;
    //input 2
    regs[6].addr = 0x0101;
    regs[6].val = 0;
    regs[6].mod = 0;
    //input state
    for(i=0;i<32;i++)
    {
        regs[7+i].addr = 0x0102+i;
        regs[7+i].val = 0;
        regs[7+i].mod = 0;
    }

    //output 1
    regs[39].addr = 0x0200;
    regs[39].val = 0;
    regs[39].mod = 0;

    //output 2 
    regs[40].addr = 0x0201;
    regs[40].val = 0;
    regs[40].mod = 0;
    //output state
    for(i=0;i<32;i++)
    {
        regs[41+i].addr = 0x0202+i;
        regs[41+i].val = 0;
        regs[41+i].mod = 0;
    }

    //ack
    regs[73].addr = 0x1000;
    regs[73].val = 0;
    regs[73].mod = 2; //rw
    //rst
    regs[74].addr = 0x1001;
    regs[74].val = 0;
    regs[74].mod = 2; //rw
    ///test
    regs[75].addr = 0x1002;
    regs[75].val = 0;
    regs[75].mod = 2; //rw

}

void crc16(uint8_t data,uint16_t* crc)
{
    uint8_t i=0;
    *crc ^= ((uint16_t)data);
    for(i=0;i<8;i++){
      if(*crc&0x0001){
        *crc >>=1;
        *crc ^=0xa001;
      }else
        *crc >>=1;
    }
}

int address(uint16_t addr)
{
    if(addr>=0 && addr <=3)
        return 0;
    else if(addr==0x0010 || addr ==0x0011)
        return 4;
    else if(addr>=0x0100 && addr <= 0x0121)
        return 5;
    else if(addr>=0x0200 && addr <= 0x0221)
        return 39;
    else if(addr>=0x1000 && addr <=0x1002)
        return 73;
    else 
        return -1;
}
//exception code:0x02:非法数据地址  0x03:非法数据  0x10 无权限
//　0x11: 寄存器长度溢出 0x12 timeout
void exceptAns(uint8_t func,uint8_t exCode)
{
    uint16_t crc=0xffff;
    txBuf.tail = 0;
    PUTINTOBUF(txBuf,MODBUSADDR);
    crc16(MODBUSADDR,&crc);
    
    //txBuf[1] = 0x80+func;
    PUTINTOBUF(txBuf,0x80+func);
    crc16(0x80+func,&crc);
    PUTINTOBUF(txBuf,exCode);
    crc16(exCode,&crc);
    PUTINTOBUF(txBuf,(uint8_t)(crc & 0x00ff));
    PUTINTOBUF(txBuf,(uint8_t)((crc>>8) & 0x00ff));
}

int okToParse(void)
{
//    uint16_t regAddr;
//    uint16_t regNum;
//    int tmp = 0;
    if((rxBuf.tail>=2)){
        if((rxBuf.buf[1]==0x03)){
            if((rxBuf.tail==8))
                return 1; //OK
        }
    }
    if(rxBuf.tail>=2){
        if(rxBuf.buf[1]==0x10){
            if(rxBuf.tail>=6){
    //    regAddr = (rxBuf.buf[2]<<8) + rxBuf.buf[3];
    //    regNum = rxBuf.buf[5];
    //    tmp = regNum*2;
    /*    if(regAddr<=0x0100 && (regAddr+regNum)>=0x0100)
            tmp += 2;
        else if(regAddr <=0x0200 && (regAddr+regNum)>=0x0200)
            tmp += 2;
            else if(regAddr <=0x0100 && (regAddr+regNum)>=0x0200)
            tmp += 4;*/
                if(rxBuf.tail == (rxBuf.buf[5]<<1) + 8)
                    return 1;
            }
        }
    }
    return 0;
}


void parse(void)
{
    int i,j;
    uint8_t mod_addr;
    uint8_t func;
    uint8_t highByte;
    uint8_t lowByte;
    uint16_t addr;
    uint16_t length;
    uint16_t crc=0xffff;
    uint16_t crctmp;
    uint16_t crctmp2;
    uint16_t crcin;
    uint16_t regstmp[3];
    uint16_t regVal = 0;
    
    //uint8_t str[100] = {0};
//    if(!okToParse())
//        goto the_end;
    
    rxBuf.head = 0;
    mod_addr = GETFROMBUF(rxBuf);
    if((mod_addr!=MODBUSADDR)&&(mod_addr!=0)){
        CLEARBUF(rxBuf);
     //   str[0] = 'a';
     //   print(str,1);
     //   print(&gModbusAddr,1);
     //   print(&func,1);
        goto the_end;
    }
    crc16(mod_addr,&crc);//modbus address
    func = GETFROMBUF(rxBuf);
    if(func!=0x03 && func!=0x10)  //func code wrong!!
    {
        CLEARBUF(rxBuf);
        exceptAns(func,0x03); //illegal data
        goto tx_int_en;
    }
    crc16(func,&crc);  //function code
    crctmp = crc;  //crctmp is used for function 0x03

    //reg addr
    highByte = GETFROMBUF(rxBuf);
    crc16(highByte,&crc);
    lowByte = GETFROMBUF(rxBuf);
    crc16(lowByte,&crc);
    addr = highByte;
    addr = (addr<<8) + lowByte;
    //reg length
    highByte = GETFROMBUF(rxBuf);
    crc16(highByte,&crc);
    lowByte = GETFROMBUF(rxBuf);
    crc16(lowByte,&crc);
    length = highByte;
    length = (length << 8) + lowByte;
    crctmp2 = crc; //crctmp2 is used for function 0x10;crc is used for verify
    // if this frame is correct.
   
    if(func == 0x03)
    {
     //   str[0] = 0x03;
     //   print(str,1);
        if((address(addr)==-1)||(address(addr+length-1)!=address(addr)))
        {
     //   str[0] = 0x04;
     //   print(str,1);
            CLEARBUF(rxBuf);
            exceptAns(func,0x11); //reg length overflow
            goto tx_int_en;
        }
        lowByte = GETFROMBUF(rxBuf);
        highByte = GETFROMBUF(rxBuf);
        crcin = highByte;
        crcin = (crcin<<8) + lowByte;
        if(crc !=crcin)  //this frame is not correct
        {
     //   str[0] = 0x05;
     //   print(str,1);
            CLEARBUF(rxBuf);
           // cout << "here" << endl;
            exceptAns(func,0x03); //illegel data
            goto tx_int_en;
        }
        //answer 0x03
        txBuf.tail = 0;
        PUTINTOBUF(txBuf,mod_addr);   //modbus addr
        PUTINTOBUF(txBuf,0x03);         //code 
        PUTINTOBUF(txBuf,rxBuf.buf[4]);
        //(uint8_t)((length>>8)&0xff));  //length
        crc16(rxBuf.buf[4]/*(uint8_t)((length>>8) & 0xff)*/,&crctmp);
        PUTINTOBUF(txBuf,rxBuf.buf[5]);//(uint8_t)(length & 0xff));
        crc16(rxBuf.buf[5]/*(uint8_t)(length&0xff)*/,&crctmp);
        
        j = address(addr);   //reg index
        j = addr - regs[j].addr + j;//
        for(i=0;i<length;i++)   //data
        {
     //   str[0] = j;
     //   str[1] = length;
     //   print(str,2);
            
          //  if(j+i == 5 || j+i==38) // 4 Bytes
          //  {
          //      highByte = (uint8_t)((regs[j+i].val>>24) & 0x00ff);
          //      PUTINTOBUF(txBuf,highByte);
          //      crc16(highByte,&crctmp);

          //      highByte = (uint8_t)((regs[j+i].val>>16) & 0x00ff);
          //      PUTINTOBUF(txBuf,highByte);
          //      crc16(highByte,&crctmp);

          //      highByte = (uint8_t)((regs[j+i].val>>8) & 0x00ff);
          //      PUTINTOBUF(txBuf,highByte);
          //      crc16(highByte,&crctmp);
          //      
          //      highByte = (uint8_t)(regs[j+i].val & 0x00ff);
          //      PUTINTOBUF(txBuf,highByte);
          //      crc16(highByte,&crctmp);
          //  }
          //  else // 2 Bytes
         //   {
                highByte = (uint8_t)((regs[j+i].val>>8) & 0x00ff);
                PUTINTOBUF(txBuf,highByte);
                crc16(highByte,&crctmp);
                
                highByte = (uint8_t)(regs[j+i].val & 0x00ff);
                PUTINTOBUF(txBuf,highByte);
                crc16(highByte,&crctmp);
          //  }
        }
        PUTINTOBUF(txBuf,(uint8_t)(crctmp & 0x00ff));    //crc
        PUTINTOBUF(txBuf,(uint8_t)(crctmp>>8)&(0x00ff));
        CLEARBUF(rxBuf);
        goto tx_int_en;
    }
    //func == 0x10
    if(func==0x10)
    {
      //  str[0] = 0x10;
      //  print(str,1);
      //  注意不能写只读寄存器
        if((length>3) ||(addr>2 && addr<0x1000) || (addr >0x1002))
        {
            CLEARBUF(rxBuf);
            exceptAns(func,0x10); 
            goto tx_int_en;
        }

        for(i = 0;i<length;i++)   //registers' value
        {
           // if(regs[j+i].mod==0) //read only
            //{
             //   CLEARBUF(rxBuf);
               // exceptAns(func,0x10); 
               // goto tx_int_en;
           // }
            highByte = GETFROMBUF(rxBuf);
            crc16(highByte,&crc);
            lowByte = GETFROMBUF(rxBuf);
            crc16(lowByte,&crc);
            regVal = highByte;
            regVal = (regVal<<8)+lowByte;
            /*if(regs[j+i].len==4)
            {
                highByte = GETFROMBUF(rxBuf);
                crc16(highByte,&crc);
                lowByte = GETFROMBUF(rxBuf);
                crc16(lowByte,&crc);
                regVal = (regVal<<8)+highByte;
                regVal = (regVal<<8)+lowByte;
            }*/
            regstmp[i] = regVal;
        }
        lowByte = GETFROMBUF(rxBuf);
        highByte = GETFROMBUF(rxBuf);  //crc
        crcin = highByte;
        crcin = (crcin << 8) + lowByte; 
        //crcin是接收到的CRC码，
        //crc是计算得到的CRC码
        if(crcin!=crc)
        {
            CLEARBUF(rxBuf);
            exceptAns(func,0x03); //illegel data
            goto tx_int_en;
        }
        //assign value to regs
        j = address(addr);
        j = addr - regs[j].addr + j;
        for(i=0;i<length;i++)
        {
            regs[j+i].val = regstmp[i];
        }
        //answer
        for(i=0;i<6;i++){
            PUTINTOBUF(txBuf,rxBuf.buf[i]);//MODBUSADDR);
        }
//        PUTINTOBUF(txBuf,rxBuf.buf[0]);//MODBUSADDR);
//        PUTINTOBUF(txBuf,rxBuf.buf[1]);
//    //    highByte = (uint8_t)((addr>>8)&0x00ff);
//    //    lowByte = (uint8_t)(addr & 0x00ff);
//        PUTINTOBUF(txBuf,rxBuf.buf[2]);//highByte);
//        PUTINTOBUF(txBuf,rxBuf.buf[3]);//lowByte);
//     //   highByte = (uint8_t)((length>>8)&0x00ff);
//     //   lowByte = (uint8_t)(length & 0x00ff);
//        PUTINTOBUF(txBuf,rxBuf.buf[4]);//highByte);
//        PUTINTOBUF(txBuf,rxBuf.buf[5]);//lowByte);
        PUTINTOBUF(txBuf,(uint8_t)(crctmp2 &0x00ff));
        PUTINTOBUF(txBuf,(uint8_t)((crctmp2>>8)&0x00ff));
        CLEARBUF(rxBuf);
        // TODO reconfig usart and bus address
        //
        //
    }   
tx_int_en:
    //TODO turn on tx interrupt
the_end:
    return;
    //nothing here
}

void new_config_from_rtu(void){
    if(gModbusAddr != regs[0].val)
        eeprom_store_modbusaddr(regs[0].val);
    if((regs[1].val<<4) + regs[2].val!=gRS485Config)
        eeprom_store_rs485config((regs[1].val<<4)+regs[2].val);
}
