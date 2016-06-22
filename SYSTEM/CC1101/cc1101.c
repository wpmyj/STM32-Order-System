/*
** CC1101 433MHz无线模块相互通信
** 2014-11-16
*/
#include "cc1101.h"

//#include "RF_Send.h"
//#include "task.h"
//***************更多功率参数设置可详细参考DATACC1100英文文档中第48-49页的参数表******************
//INT8U PaTabel[8] = {0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04};  //-30dBm   功率最小
//INT8U PaTabel[8] = {0x17,0x17 ,0x17 ,0x17 ,0x17 ,0x17,0x17 ,0x17}; //-20dBm
//INT8U PaTabel[8] = {0x1D,0x1D ,0x1D ,0x1D ,0x1D ,0x1D,0x1D ,0x1D}; //-15dBm
//INT8U PaTabel[8] = {0x26,0x26 ,0x26 ,0x26 ,0x26 ,0x26,0x26 ,0x26}; //-10dBm
//INT8U PaTabel[8] = {0x37,0x37 ,0x37 ,0x37 ,0x37 ,0x37,0x37 ,0x37}; //-6dBm
//INT8U PaTabel[8] = {0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60};//0dBm
//INT8U PaTabel[8] = {0x86,0x86 ,0x86 ,0x86 ,0x86 ,0x86,0x86 ,0x86}; //5dBm

const u8 PaTabel[8] = {0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0};//10dBm

u8 RF_Read_Buff[66];//接收缓冲区

_RF_Sta  RF_Sta;//RF状态
/////////////////////////////////////////////////////////////////
const RF_SETTINGS rfSettings =
{
    0x00,
    0x08,   // FSCTRL1   Frequency synthesizer control.
    0x00,   // FSCTRL0   Frequency synthesizer control.
    0x10,   // FREQ2     Frequency control word, high byte.
    0xA7,   // FREQ1     Frequency control word, middle byte.
    0x62,   // FREQ0     Frequency control word, low byte.
    0x5B,   // MDMCFG4   Modem configuration.
    0xF8,   // MDMCFG3   Modem configuration.
    0x03,   // MDMCFG2   Modem configuration.
    0x22,   // MDMCFG1   Modem configuration.
    0xF8,   // MDMCFG0   Modem configuration.

    0x08,   // CHANNR    Channel number.//设置通道号,发送和接收必须一致
    0x47,   // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
    0xB6,   // FREND1    Front end RX configuration.
    0x10,   // FREND0    Front end RX configuration.
    0x18,   // MCSM0     Main Radio Control State Machine configuration.
// 0x0F,   // MCSM1     Main Radio Control State Machine configuration.
    0x1D,   // FOCCFG    Frequency Offset Compensation Configuration.
    0x1C,   // BSCFG     Bit synchronization Configuration.
    0xC7,   // AGCCTRL2  AGC control.
    0x00,   // AGCCTRL1  AGC control.
    0xB2,   // AGCCTRL0  AGC control.

    0xEA,   // FSCAL3    Frequency synthesizer calibration.
    0x2A,   // FSCAL2    Frequency synthesizer calibration.
    0x00,   // FSCAL1    Frequency synthesizer calibration.
    0x11,   // FSCAL0    Frequency synthesizer calibration.
    0x59,   // FSTEST    Frequency synthesizer calibration.
    0x81,   // TEST2     Various test settings.
    0x35,   // TEST1     Various test settings.
    0x09,   // TEST0     Various test settings.
    0x0B,   // IOCFG2    GDO2 output pin configuration.
    0x06,   // IOCFG0D   见64页
//开启在收到数据时为MCU提供中断信号
//GDO0 output pin configuration. Refer to SmartRF?Studio User Manual for detailed pseudo register explanation.

    0x05,   // PKTCTRL1  Packet automation control.  //地址校验以及0(0x00)为广播地址，不接受广播

    0x05,   // PKTCTRL0  Packet automation control.   //使用"可变数据包长度模式"
    0x08,   // ADDR      Device address.              //设备地址为0x08
    0xff    // PKTLEN    Packet length.               //在非固定长度时设置为255
};




//*****************************************************************************************
//函数名：delayus(unsigned int s)
//输入：时间
//输出：无
//功能描述：普通廷时,内部用
//*****************************************************************************************

void delayus(u16 timeout)
{
    u8 i;
    do
    {
        for(i=0; i<20; i++);
    }
    while (--timeout);

}

/*****************************************************************************************/
//函数名：CC1101_SpiInit()
//输入：无
//输出：无
//功能描述：SPI初始化程序
/*****************************************************************************************/
void CC1101_SpiInit(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启PA PC时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);
	/*配置相关GPIO口*/
	/*配置PC4：CSN 为推挽输出*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	/*配置PA4 GDO0上拉输入*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	/*配置PPC5：GDO2为上拉输入*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_5);
	/*SPI接口初始化*/
	SPI1_Init();								
}


void Open_GD0_Interrupt(void)
{
	/* 使能io复用时钟 */
	RCC->APB2ENR |=  1 << 0;
	/* 配置为输外部中断4在PA4上 */
	AFIO->EXTICR[1] &= ~(0xF << 0);
	AFIO->EXTICR[1] |=  (0x0 << 0);

	/* 开启外部中断4 */
	EXTI->IMR       |=  (1 << 4);

	/* 上升沿触发 */
	EXTI->RTSR      |=  (1 << 4);
	EXTI->FTSR      &= ~(1 << 4);
	
	/*设置PA4中断优先级*/
	Set_NVIC(EXTI4_IRQn ,2,2);			

}
//*****************************************************************************************
//函数名：SpisendByte(INT8U dat)
//输入：发送的数据
//输出：无
//功能描述：SPI发送一个字节
//*****************************************************************************************
//u8 SpiTxRxByte(u8 dat)
//{
//    u8 i,j,temp= 0;
//    SCK = 0;
//    for(i=0; i<8; i++)
//    {
//        if(dat & 0x80)MOSI = 1;
//        else MOSI = 0;
//        j++;
//        j++;//只是起到简单延时
//        dat <<= 1;
//        j++;
//        j++;
//        SCK = 1;
//        j++;
//        j++;
//        temp <<= 1;
//        if(MISO)temp++;
//        SCK = 0;
//        j++;
//        j++;
//    }
//    return temp;
//}

//*****************************************************************************************
//函数名：void RESET_CC1100(void)
//输入：无
//输出：无
//功能描述：复位CC1100
//*****************************************************************************************
u8 RESET_CC1100(void)
{
    u16 n=0;
    CSN = 0;
    while(MISO)
    {
        if(++n>300)return 0;
        delayus(5);
    }
    n=0;
    SpiTxRxByte(CCxxx0_SRES); 		//写入复位命令
    while(MISO)
    {
        if(++n>300)return 0;
        delayus(5);
    }
    CSN = 1;
    return 1;
}

//*****************************************************************************************
//函数名：void POWER_UP_RESET_CC1100(void)
//输入：无
//输出：无
//功能描述：上电复位CC1100
//*****************************************************************************************
u8 POWER_UP_RESET_CC1100(void)
{
    CSN = 1;
    delayus(10);
    CSN = 0;
    delayus(10);
    CSN = 1;
    delayus(100);
    if(RESET_CC1100())return 1;  		//复位CC1100
    return 0;
}

//*****************************************************************************************
//函数名：void halSpiWriteReg(INT8U addr, INT8U value)
//输入：地址和配置字
//输出：无
//功能描述：SPI写寄存器
//*****************************************************************************************
void halSpiWriteReg(u8 addr, u8 value)
{
    u16 n=0;
    CSN = 0;
    while(MISO)
    {
        if(++n>300)break;
        delayus(5);
    }
    SpiTxRxByte(addr);		//写地址
    SpiTxRxByte(value);		//写入配置
    CSN = 1;
}

//*****************************************************************************************
//函数名：void halSpiWriteBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//输入：地址，写入缓冲区，写入个数
//输出：无
//功能描述：SPI连续写配置寄存器
//*****************************************************************************************
void halSpiWriteBurstReg(u8 addr, u8 *buffer, u8 count)
{
    u8 i, temp;
    temp = addr | WRITE_BURST;
    CSN = 0;
    while(MISO)
    {
        if(++i>250)break;
        delayus(5);
    }
    SpiTxRxByte(temp);
    for (i = 0; i < count; i++)
    {
        SpiTxRxByte(buffer[i]);
    }
    CSN = 1;
}

//*****************************************************************************************
//函数名：void halSpiStrobe(INT8U strobe)
//输入：命令
//输出：无
//功能描述：SPI写命令
//*****************************************************************************************
void halSpiStrobe(u8 strobe)
{
    u8 n=0;
    CSN = 0;
    while(MISO)
    {
        if(++n>250)break;
        delayus(5);
    }
    SpiTxRxByte(strobe);		//写入命令
    CSN = 1;
}

//*****************************************************************************************
//函数名：INT8U halSpiReadReg(INT8U addr)
//输入：地址
//输出：该寄存器的配置字
//功能描述：SPI读寄存器
//*****************************************************************************************
u8 halSpiReadReg(u8 addr)
{
    u8 temp, value=0;
    temp = addr|READ_SINGLE;//读寄存器命令
    CSN = 0;
    while(MISO)
    {
        if(++value>250)break;
        delayus(5);
    }
    SpiTxRxByte(temp);
    value = SpiTxRxByte(0);
    CSN = 1;
    return value;
}


//*****************************************************************************************
//函数名：void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//输入：地址，读出数据后暂存的缓冲区，读出配置个数
//输出：无
//功能描述：SPI连续写配置寄存器
//*****************************************************************************************
void halSpiReadBurstReg(u8 addr, u8 *buffer, u8 count)
{
    u8 i=0,temp;
    temp = addr | READ_BURST;		//写入要读的配置寄存器地址和读命令
    CSN = 0;
    while(MISO)
    {
        if(++i>250)break;
        delayus(5);
    }
    SpiTxRxByte(temp);
    for (i = 0; i < count; i++)
    {
        buffer[i] = SpiTxRxByte(0);
    }
    CSN = 1;
}


//*****************************************************************************************
//函数名：INT8U halSpiReadReg(INT8U addr)
//输入：地址
//输出：该状态寄存器当前值
//功能描述：SPI读状态寄存器
//*****************************************************************************************
u8 halSpiReadStatus(u8 addr)
{
    u8 value=0,temp;
    temp = addr | READ_BURST;		//写入要读的状态寄存器的地址同时写入读命令
    CSN = 0;
    while(MISO)
    {
        if(++value>250)break;
        delayus(5);
    }
    SpiTxRxByte(temp);
    value = SpiTxRxByte(0);
    CSN = 1;
    return value;
}

//*****************************************************************************************
//函数名：void CC1101_Set_PKTLEN(u8 len)
//输入：无
//输出：无
//功能描述：配置CC1101数据长度
//*****************************************************************************************
void CC1101_Set_PKTLEN(u8 len)//配置CC1101数据长度
{
    halSpiWriteReg(CCxxx0_PKTLEN,len);
}

//*****************************************************************************************
//函数名：void halRfWriteRfSettings(RF_SETTINGS *pRfSettings)
//输入：无
//输出：无
//功能描述：配置CC1100的寄存器
//*****************************************************************************************
void halRfWriteRfSettings(void)
{

    halSpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL2);//自已加的
		// Write register settings
    halSpiWriteReg(CCxxx0_FSCTRL1,  rfSettings.FSCTRL1);
    halSpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL0);
    halSpiWriteReg(CCxxx0_FREQ2,    rfSettings.FREQ2);
    halSpiWriteReg(CCxxx0_FREQ1,    rfSettings.FREQ1);
    halSpiWriteReg(CCxxx0_FREQ0,    rfSettings.FREQ0);
    halSpiWriteReg(CCxxx0_MDMCFG4,  rfSettings.MDMCFG4);
    halSpiWriteReg(CCxxx0_MDMCFG3,  rfSettings.MDMCFG3);
    halSpiWriteReg(CCxxx0_MDMCFG2,  rfSettings.MDMCFG2);
    halSpiWriteReg(CCxxx0_MDMCFG1,  rfSettings.MDMCFG1);
    halSpiWriteReg(CCxxx0_MDMCFG0,  rfSettings.MDMCFG0);
    halSpiWriteReg(CCxxx0_CHANNR,   rfSettings.CHANNR);
    halSpiWriteReg(CCxxx0_DEVIATN,  rfSettings.DEVIATN);
    halSpiWriteReg(CCxxx0_FREND1,   rfSettings.FREND1);
    halSpiWriteReg(CCxxx0_FREND0,   rfSettings.FREND0);
    halSpiWriteReg(CCxxx0_MCSM0 ,   rfSettings.MCSM0 );
    halSpiWriteReg(CCxxx0_FOCCFG,   rfSettings.FOCCFG);
    halSpiWriteReg(CCxxx0_BSCFG,    rfSettings.BSCFG);
    halSpiWriteReg(CCxxx0_AGCCTRL2, rfSettings.AGCCTRL2);
    halSpiWriteReg(CCxxx0_AGCCTRL1, rfSettings.AGCCTRL1);
    halSpiWriteReg(CCxxx0_AGCCTRL0, rfSettings.AGCCTRL0);
    halSpiWriteReg(CCxxx0_FSCAL3,   rfSettings.FSCAL3);
    halSpiWriteReg(CCxxx0_FSCAL2,   rfSettings.FSCAL2);
    halSpiWriteReg(CCxxx0_FSCAL1,   rfSettings.FSCAL1);
    halSpiWriteReg(CCxxx0_FSCAL0,   rfSettings.FSCAL0);
    halSpiWriteReg(CCxxx0_FSTEST,   rfSettings.FSTEST);
    halSpiWriteReg(CCxxx0_TEST2,    rfSettings.TEST2);
    halSpiWriteReg(CCxxx0_TEST1,    rfSettings.TEST1);
    halSpiWriteReg(CCxxx0_TEST0,    rfSettings.TEST0);
    halSpiWriteReg(CCxxx0_IOCFG2,   rfSettings.IOCFG2);
    halSpiWriteReg(CCxxx0_IOCFG0,   rfSettings.IOCFG0);
    halSpiWriteReg(CCxxx0_PKTCTRL1, rfSettings.PKTCTRL1);
    halSpiWriteReg(CCxxx0_PKTCTRL0, rfSettings.PKTCTRL0);
    halSpiWriteReg(CCxxx0_ADDR,     rfSettings.ADDR);
    halSpiWriteReg(CCxxx0_PKTLEN,   rfSettings.PKTLEN);
		//halSpiWriteReg(CCxxx0_IOCFG0 ,   rfSettings.PKTLEN);
}


//******************************************************************************************
//函数名：void Set_TxMode(void)
//输入：无
//输出：无
//功能描述：设置CC1100为发射模式
//*****************************************************************************************
void Set_TxMode(void)
{
    RF_Sta.mode=RF_TXMODE;
    RF_Sta.Busy=BUSY;//置忙
    GDO0_INTON;//开中断
    halSpiStrobe(CCxxx0_SIDLE);//强制进入空闲模式
    halSpiStrobe(CCxxx0_STX);		//进入发送模式发送数据
}
//*****************************************************************************************
//函数名：void Set_RxMode(void)
//输入：无
//输出：无
//功能描述：设置CC1100为发射接收模式
//*****************************************************************************************
void Set_RxMode(void)
{
    RF_Sta.mode=RF_RXMODE;
    halSpiStrobe(CCxxx0_SFRX);//清洗接收缓冲区
    halSpiStrobe(CCxxx0_SIDLE);//强制进入空闲模式
    halSpiStrobe(CCxxx0_SRX);//进入接收模式
    GDO0_INTON;//开中断
}
//*****************************************************************************************
//函数名：void halRfSendPacket(INT8U *txBuffer, INT8U size)
//输入：发送的缓冲区，发送数据个数
//输出：OK 已发送,其它,错误标志
//功能描述：CC1100发送一组数据
//*****************************************************************************************

u8 halRfSendPacket(u8 *txBuffer, u8 size)
{
    halSpiWriteBurstReg(CCxxx0_TXFIFO, txBuffer, size);	//写入要发送的数据
    Set_TxMode();//进入发送模式发送数据
    while(RF_Sta.Busy==BUSY);//等待发送完成
    return OK;
}

//*****************************************************************************************
//函数名：u8 halRfReceivePacket(u8 *rxBuffer)
//输入：u8 *rxBuffer 接收的缓冲区，
//输出：CRC_OK 接收成功,其它,接收失败
//功能描述：CC1100接收一组数据
//*****************************************************************************************
u8 halRfReceivePacket(u8 *rxBuffer)
{
    u8 status[2];
    u8 packetLength;
    if((halSpiReadStatus(CCxxx0_RXBYTES) & BYTES_IN_RXFIFO)) //如果接的字节数不为0
    {
        packetLength = halSpiReadReg(CCxxx0_RXFIFO);//读出第一个字节，此字节为该帧数据长度
        halSpiReadBurstReg(CCxxx0_RXFIFO,(rxBuffer+1), packetLength); //读出所有接收到的数据
			  
        rxBuffer[0] = packetLength;				//把接收数据长度的修改为当前数据的长度
        halSpiReadBurstReg(CCxxx0_RXFIFO, status, 2); 	//读出CRC校验位
        halSpiStrobe(CCxxx0_SFRX);		//清洗接收缓冲区
        return (status[1] & CRC_OK);	//如果校验成功返回接收成功
    }
    return 0;
}
//*****************************************************************************************
//函数名：u8 CC1101_Init(void)
//输入：无
//输出：1,初始化成功   0,初始化失败
//功能描述：CC1100初始化
//*****************************************************************************************
u8 CC1101_Init(void)
{
		CC1101_SpiInit();
    if(POWER_UP_RESET_CC1100())//复位CC1100
    {
        halRfWriteRfSettings();//配置CC1100
        halSpiWriteBurstReg(CCxxx0_PATABLE, (u8 *)PaTabel, 8);//设置功率
        RF_Sta.Busy=IDLE;//空闲
        RF_Sta.DatFlag=ERR;
        Set_RxMode();//进入接收状态
        return 1;
    }
		return 0;
}



//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
    EXTI->PR=1<<4;  //清除LINE4上的中断标志位
    GDO0_INTOFF;//关中断
		KEY_LED=!KEY_LED;
    if(GDO0)
    {
        delayus(20);
        if(GDO0)
        {
            while(GDO0);
            switch(RF_Sta.mode)
            {
            case RF_TXMODE:
                halSpiStrobe(CCxxx0_SFTX);//清洗发送缓冲区
                RF_Sta.Busy=IDLE;//空闲
                RF_Sta.DatFlag=ERR;
                break;
            case RF_RXMODE:
                if(halRfReceivePacket(RF_Read_Buff))//读RXFIFO
                {
                    KEY_LED=!KEY_LED;
                    RF_Sta.DatFlag=OK;
                }
                break;
            default:
                break;
            }
        }
    }
    Set_RxMode();//进入接收状态
}
