

#define FOSC 8000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>

/* USART Buffer Defines */
#define USART_RX_BUFFER_SIZE 128     /* 2,4,8,16,32,64,128 or 256 bytes */
#define USART_TX_BUFFER_SIZE 128     /* 2,4,8,16,32,64,128 or 256 bytes */
#define USART_RX_BUFFER_MASK (USART_RX_BUFFER_SIZE - 1)
#define USART_TX_BUFFER_MASK (USART_TX_BUFFER_SIZE - 1)

#if (USART_RX_BUFFER_SIZE & USART_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif
#if (USART_TX_BUFFER_SIZE & USART_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif

/* Static Variables */
static unsigned char USART_RxBuf[USART_RX_BUFFER_SIZE];
static volatile unsigned char USART_RxHead;
static volatile unsigned char USART_RxTail;
static unsigned char USART_TxBuf[USART_TX_BUFFER_SIZE];
static volatile unsigned char USART_TxHead;
static volatile unsigned char USART_TxTail;

/* Prototypes */
void USART_Init(unsigned int ubrr_val);
unsigned char USART_Receive(void);
void USART_Transmit(unsigned char data);

/* Initialize USART */
void USART_Init(unsigned int ubrr_val)
{
	unsigned char x;

	/* Set the baud rate */
	UBRR0H = (unsigned char) (ubrr_val>>8);
	UBRR0L = (unsigned char) ubrr_val;
	
	/* Enable USART receiver and transmitter */
	UCSR0B = ((1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0));

	///* Set frame format: 8 data, 1 stop bit */
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00) ;
	
	/* Flush receive buffer */
	x = 0;

	USART_RxTail = x;
	USART_RxHead = x;
	USART_TxTail = x;
	USART_TxHead = x;
}

int main(void)
{
	
	USART_Init(MYUBRR); //Calculate baud rate
	sei();

	for( ; ; ) {
		/* Echo the received character */
		USART_Transmit(USART_Receive());
	}
	
	return 0;
}


//Receive Interrupt
ISR(USART_RX_vect)
{
	unsigned char data;
	unsigned char tmphead;

	/* Read the received data */
	data = UDR0;
	/* Calculate buffer index */
	tmphead = (USART_RxHead + 1) & USART_RX_BUFFER_MASK;
	/* Store new index */
	USART_RxHead = tmphead;

	if (tmphead == USART_RxTail)
	{
		/* ERROR! Receive buffer overflow */
	}
	/* Store received data in buffer */
	USART_RxBuf[tmphead] = data;
}



ISR(USART_UDRE_vect)
{
	unsigned char tmptail;

	/* Check if all data is transmitted */
	if (USART_TxHead != USART_TxTail)
	{
		/* Calculate buffer index */
		tmptail = (USART_TxTail + 1) & USART_TX_BUFFER_MASK;
		/* Store new index */
		USART_TxTail = tmptail;
		/* Start transmission */
		UDR0 = USART_TxBuf[tmptail];
	}
	else
	{
		/* Disable UDRE interrupt */
		UCSR0B &= ~(1<<UDRIE0);
	}
}
unsigned char USART_Receive(void)
{
	unsigned char tmptail;
	
	/* Wait for incoming data */
	while (USART_RxHead == USART_RxTail);
	/* Calculate buffer index */
	tmptail = (USART_RxTail + 1) & USART_RX_BUFFER_MASK;
	/* Store new index */
	USART_RxTail = tmptail;
	/* Return data */
	return USART_RxBuf[tmptail];
}

void USART_Transmit(unsigned char data)
{
	unsigned char tmphead;
	
	/* Calculate buffer index */
	tmphead = (USART_TxHead + 1) & USART_TX_BUFFER_MASK;
	/* Wait for free space in buffer */
	while (tmphead == USART_TxTail);
	/* Store data in buffer */
	USART_TxBuf[tmphead] = data;
	/* Store new index */
	USART_TxHead = tmphead;
	/* Enable UDRE interrupt */
	UCSR0B |= (1<<UDRIE0);
}



//void USART_Init( unsigned int ubrr)
//{
///*Set baud rate */
//UBRR0H = (unsigned char)(ubrr>>8);
//UBRR0L = (unsigned char)ubrr;
//
////Enable receiver and transmitter
//UCSR0B = (1<<RXEN0)|(1<<TXEN0);
//
///* Set frame format: 8data, 1 stop bit */
//UCSR0C = (3<<UCSZ00);
//}
//
//unsigned char USART_Receive( void )
//{
///* Wait for data to be received */
//while ( !(UCSR0A & (1<<RXC0)) );
///* Get and return received data from buffer */
//return UDR0;
//}
//
//void USART_Transmit( unsigned char data )
//{
///* Wait for empty transmit buffer */
//while ( !( UCSR0A & (1<<UDRE0)) );
///* Put data into buffer, sends the data */
//UDR0 = data;
//}
//
//int main(void)
//{
//USART_Init(MYUBRR);
//
///* Replace with your application code */
//while (1)
//{
//USART_Transmit(USART_Receive());
//}
//}

