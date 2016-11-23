# src Makefile
include ../../../Makefile.common
OBJS+=USART_main.o
all:USART_main.o
	$(CC) $(CFLAGSLIB) USART_main.c
.PHONY: clean tshow
clean:
	rm -f USART_main.o
tshow:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"
