#src Makefile

include ../Makefile.common

OBJS+=startup.o
#OBJS+=main.o ARC_LED.o ARC_GPIO.o ARC_RCC.o ARC_RTC.o \
#	  ARC_ADC.o ARC_Button_EXTI.o ARC_Debug.o \
#	  ARC_DMA.o ARC_EEPROM.o ARC_EXTI.o \
#	  ARC_IWDG.o ARC_LED.o ARC_NVIC_API.o \
#	  ARC_RCC.o ARC_SysTick.o \
#	  ARC_TIM_PWM.o ARC_USART.o
#OBJS+=main.o stm32f10x_it.o globalvar.o led.o \
#	  print.o gpio_i2c.o
OBJS+=main.o gpioi2c_config.o stm32f10x_it.o rs485_config.o \
	  alarm_input_config.o led_output_config.o other_hw_config.o \
	  hw_config.o run_led_config.o globalvar.o ringbuf.o led.o \
	  eeprom.o 
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
