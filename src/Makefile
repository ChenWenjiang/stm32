#src Makefile

include ../Makefile.common

OBJS+=startup.o
#OBJS+=main.o ARC_LED.o ARC_GPIO.o ARC_RCC.o ARC_RTC.o \
#	  ARC_ADC.o ARC_Button_EXTI.o ARC_Debug.o \
#	  ARC_DMA.o ARC_EEPROM.o ARC_EXTI.o \
#	  ARC_IWDG.o ARC_LED.o ARC_NVIC_API.o \
#	  ARC_RCC.o ARC_SysTick.o \
#	  ARC_TIM_PWM.o ARC_USART.o
OBJS+=main.o stm32f10x_it.o \
#	  ARC_LED.o ARC_I2C.o ARC_EEPROM.o ARC_RCC.o \
#	  ARC_USART.o \
#	  ARC_SysTick.o ARC_NVIC_API.o ARC_RTC.o ARC_GPIO.o \
#	  ARC_Retarget.o SysCalls.o
all:src

src:app.a

app.a:$(OBJS)
	$(AR) cr app.a $(OBJS)

.PHONY:src clean tshow

clean:
	rm -f app.a $(OBJS)

ishow:
	@echo "############################################################"
	@echo "######### optimize settings: $(InfoTextLib),$(InfoTextSrc)"
	@echo "############################################################"
