/*
 * IncFile1.h
 *
 * Created: 02/08/2020 21:44:08
 *  Author: John
 */ 


#ifndef USART_irq_H_
#define USART_irq_H_

/* USART Buffer Defines */
#define USART_RX_BUFFER_SIZE 128     /* 2,4,8,16,32,64,128 or 256 bytes */
#define USART_TX_BUFFER_SIZE 128     /* 2,4,8,16,32,64,128 or 256 bytes */
#define USART_RX_BUFFER_MASK (USART_RX_BUFFER_SIZE - 1)
#define USART_TX_BUFFER_MASK (USART_TX_BUFFER_SIZE - 1)


/* Prototypes */
void USART_Init(unsigned int ubrr_val);
unsigned char USART_Receive(void);
void USART_Transmit(unsigned char data);
void USART_TransmitString(char* stringPtr);

#endif /* INCFILE1_H_ */