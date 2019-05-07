#include "spi.h"

SPI_HandleTypeDef SPI1_Handler;
//SPI1�ڳ�ʼ��
void spi_init(void)
{
	uint16_t TxData;
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
	__HAL_RCC_GPIOB_CLK_ENABLE();			//ʹ��GPIOBʱ��
	__HAL_RCC_SPI1_CLK_ENABLE();			//ʹ��SPI1ʱ��
	GPIO_Initure.Mode = GPIO_MODE_AF_PP;											//�����������
	GPIO_Initure.Pull = GPIO_PULLUP;													//����
	GPIO_Initure.Speed = GPIO_SPEED_FAST;											//����
	GPIO_Initure.Alternate = GPIO_AF5_SPI1;										//����ΪSPI1
	
	GPIO_Initure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	GPIO_Initure.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOB, &GPIO_Initure);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pin = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
	SPI1_Handler.Instance = SPI1;																			//SPI1
	SPI1_Handler.Init.Mode = SPI_MODE_MASTER;													//����SPI����ģʽ��Ϊ��ģʽ
	SPI1_Handler.Init.Direction = SPI_DIRECTION_2LINES;								//SPI����Ϊ˫��ģʽ
	SPI1_Handler.Init.DataSize = SPI_DATASIZE_16BIT;									//SPI���ͽ���16λ֡�ṹ
	SPI1_Handler.Init.CLKPolarity = SPI_POLARITY_LOW;									//ͬ��ʱ�ӿ���״̬Ϊ�ߵ�ƽ
	SPI1_Handler.Init.CLKPhase = SPI_PHASE_1EDGE;											//ͬ��ʱ�ӵ�2�������ؿ�ʼ���ݲ���
	SPI1_Handler.Init.NSS = SPI_NSS_SOFT;											//NSS�ź����������
	SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;		//������Ԥ��ƵֵΪ2
	SPI1_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;										//ָ�����ݴ����MSBλ��ʼ
	SPI1_Handler.Init.TIMode = SPI_TIMODE_DISABLE;										//�ر�TIģʽ
	SPI1_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;		//�ر�CRC
	SPI1_Handler.Init.CRCPolynomial = 7;															//CRC�������ʽ
	if(HAL_OK != HAL_SPI_Init(&SPI1_Handler))		//��ʼ��
	{
		while(1);
	}
	
//	__HAL_SPI_DISABLE(&SPI1_Handler);																//�ر�SPI1
//	SPI1_Handler.Instance->CR1 &= 0XFFC7;														//λ3-5���㣬�������ò�����
//	SPI1_Handler.Instance->CR1 |= 0<<3;															//����SPI�ٶ�,����Ƶ
	
	__HAL_SPI_ENABLE(&SPI1_Handler);//ʹ��SPI1
//	TxData = 0xffff;
//	HAL_SPI_Transmit(&SPI1_Handler, (uint8_t*)&TxData, 2, 1000);				//��������
//	printf("\r\nHAL_SPI_Transmit: %x\r\n", HAL_SPI_Transmit(&SPI1_Handler, (uint8_t*)&TxData, 2, 1000));
}

uint16_t SPI1_ReadWriteByte(uint16_t TxData)
{
	uint16_t Rxdata;
	CS_L();
	HAL_SPI_TransmitReceive(&SPI1_Handler, (uint8_t*)&TxData, (uint8_t*)&Rxdata, 1, 1000);
	CS_H();
	printf("\r\nRxData = %x, TxData = %x\r\n", Rxdata, TxData);
	return Rxdata;
}
