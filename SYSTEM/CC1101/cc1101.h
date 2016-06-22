#ifndef _cc1101_set_h_
#define _cc1101_set_h_
#include "stm32f10x.h"
#include "sys.h"
#include "led.h"
#include "RF_Dat.h"
#include "SPI.h"

#define MISO     PAin(6)
#define CSN      PCout(4)
#define GDO0     PAin(4)
#define GDO2     PCin(5)

#define GDO0_INTON   {EXTI->IMR|=1<<4;}			//使能PA4中断
#define GDO0_INTOFF  {EXTI->IMR&=~(1<<4);}	//除能PA4中断

#define SpiTxRxByte(dat)			SPI1_Write_Read_Byte(dat)		//替换SPI基本函数

#define 	WRITE_BURST     		0x40						//连续写入
#define 	READ_SINGLE     		0x80						//读
#define 	READ_BURST      		0xC0						//连续读
#define 	BYTES_IN_RXFIFO     0x7F  					//接收缓冲区的有效字节数
#define 	CRC_OK              0x80 						//CRC校验通过位标志



/***********************************************************
            定义CC11XX寄存器地址
***********************************************************/
#define CCxxx0_IOCFG2       0x00        // GDO2 output pin configuration
#define CCxxx0_IOCFG1       0x01        // GDO1 output pin configuration
#define CCxxx0_IOCFG0       0x02        // GDO0 output pin configuration
#define CCxxx0_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define CCxxx0_SYNC1        0x04        // Sync word, high INT8U
#define CCxxx0_SYNC0        0x05        // Sync word, low INT8U
#define CCxxx0_PKTLEN       0x06        // Packet length
#define CCxxx0_PKTCTRL1     0x07        // Packet automation control
#define CCxxx0_PKTCTRL0     0x08        // Packet automation control
#define CCxxx0_ADDR         0x09        // Device address
#define CCxxx0_CHANNR       0x0A        // Channel number
#define CCxxx0_FSCTRL1      0x0B        // Frequency synthesizer control
#define CCxxx0_FSCTRL0      0x0C        // Frequency synthesizer control
#define CCxxx0_FREQ2        0x0D        // Frequency control word, high INT8U
#define CCxxx0_FREQ1        0x0E        // Frequency control word, middle INT8U
#define CCxxx0_FREQ0        0x0F        // Frequency control word, low INT8U
#define CCxxx0_MDMCFG4      0x10        // Modem configuration
#define CCxxx0_MDMCFG3      0x11        // Modem configuration
#define CCxxx0_MDMCFG2      0x12        // Modem configuration
#define CCxxx0_MDMCFG1      0x13        // Modem configuration
#define CCxxx0_MDMCFG0      0x14        // Modem configuration
#define CCxxx0_DEVIATN      0x15        // Modem deviation setting
#define CCxxx0_MCSM2        0x16        // Main Radio Control State Machine configuration
#define CCxxx0_MCSM1        0x17        // Main Radio Control State Machine configuration
#define CCxxx0_MCSM0        0x18        // Main Radio Control State Machine configuration
#define CCxxx0_FOCCFG       0x19        // Frequency Offset Compensation configuration
#define CCxxx0_BSCFG        0x1A        // Bit Synchronization configuration
#define CCxxx0_AGCCTRL2     0x1B        // AGC control
#define CCxxx0_AGCCTRL1     0x1C        // AGC control
#define CCxxx0_AGCCTRL0     0x1D        // AGC control
#define CCxxx0_WOREVT1      0x1E        // High INT8U Event 0 timeout
#define CCxxx0_WOREVT0      0x1F        // Low INT8U Event 0 timeout
#define CCxxx0_WORCTRL      0x20        // Wake On Radio control
#define CCxxx0_FREND1       0x21        // Front end RX configuration
#define CCxxx0_FREND0       0x22        // Front end TX configuration
#define CCxxx0_FSCAL3       0x23        // Frequency synthesizer calibration
#define CCxxx0_FSCAL2       0x24        // Frequency synthesizer calibration
#define CCxxx0_FSCAL1       0x25        // Frequency synthesizer calibration
#define CCxxx0_FSCAL0       0x26        // Frequency synthesizer calibration
#define CCxxx0_RCCTRL1      0x27        // RC oscillator configuration
#define CCxxx0_RCCTRL0      0x28        // RC oscillator configuration
#define CCxxx0_FSTEST       0x29        // Frequency synthesizer calibration control
#define CCxxx0_PTEST        0x2A        // Production test
#define CCxxx0_AGCTEST      0x2B        // AGC test
#define CCxxx0_TEST2        0x2C        // Various test settings
#define CCxxx0_TEST1        0x2D        // Various test settings
#define CCxxx0_TEST0        0x2E        // Various test settings

// Strobe commands
#define CCxxx0_SRES         0x30        // Reset chip.
#define CCxxx0_SFSTXON      0x31        // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
// If in RX/TX: Go to a wait state where only the synthesizer is
// running (for quick RX / TX turnaround).
#define CCxxx0_SXOFF        0x32        // Turn off crystal oscillator.
#define CCxxx0_SCAL         0x33        // Calibrate frequency synthesizer and turn it off
// (enables quick start).
#define CCxxx0_SRX          0x34        // Enable RX. Perform calibration first if coming from IDLE and
// MCSM0.FS_AUTOCAL=1.
#define CCxxx0_STX          0x35        // In IDLE state: Enable TX. Perform calibration first if
// MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
// Only go to TX if channel is clear.
#define CCxxx0_SIDLE        0x36        // Exit RX / TX, turn off frequency synthesizer and exit
// Wake-On-Radio mode if applicable.
#define CCxxx0_SAFC         0x37        // Perform AFC adjustment of the frequency synthesizer
#define CCxxx0_SWOR         0x38        // Start automatic RX polling sequence (Wake-on-Radio)
#define CCxxx0_SPWD         0x39        // Enter power down mode when CSn goes high.
#define CCxxx0_SFRX         0x3A        // Flush the RX FIFO buffer.
#define CCxxx0_SFTX         0x3B        // Flush the TX FIFO buffer.
#define CCxxx0_SWORRST      0x3C        // Reset real time clock.
#define CCxxx0_SNOP         0x3D        // No operation. May be used to pad strobe commands to two
// INT8Us for simpler software.

#define CCxxx0_PARTNUM      0x30
#define CCxxx0_VERSION      0x31
#define CCxxx0_FREQEST      0x32
#define CCxxx0_LQI          0x33
#define CCxxx0_RSSI         0x34
#define CCxxx0_MARCSTATE    0x35
#define CCxxx0_WORTIME1     0x36
#define CCxxx0_WORTIME0     0x37
#define CCxxx0_PKTSTATUS    0x38
#define CCxxx0_VCO_VC_DAC   0x39
#define CCxxx0_TXBYTES      0x3A
#define CCxxx0_RXBYTES      0x3B

#define CCxxx0_PATABLE      0x3E
#define CCxxx0_TXFIFO       0x3F
#define CCxxx0_RXFIFO       0x3F

// RF_SETTINGS is a data structure which contains all relevant CCxxx0 registers
typedef struct S_RF_SETTINGS
{
    u8 FSCTRL2;		//自已加的
    u8 FSCTRL1;   // Frequency synthesizer control.
    u8 FSCTRL0;   // Frequency synthesizer control.
    u8 FREQ2;     // Frequency control word, high INT8U.
    u8 FREQ1;     // Frequency control word, middle INT8U.
    u8 FREQ0;     // Frequency control word, low INT8U.
    u8 MDMCFG4;   // Modem configuration.
    u8 MDMCFG3;   // Modem configuration.
    u8 MDMCFG2;   // Modem configuration.
    u8 MDMCFG1;   // Modem configuration.
    u8 MDMCFG0;   // Modem configuration.
    u8 CHANNR;    // Channel number.      ***
    u8 DEVIATN;   // Modem deviation setting (when FSK modulation is enabled).
    u8 FREND1;    // Front end RX configuration.
    u8 FREND0;    // Front end RX configuration.
    u8 MCSM0;     // Main Radio Control State Machine configuration.
    u8 FOCCFG;    // Frequency Offset Compensation Configuration.
    u8 BSCFG;     // Bit synchronization Configuration.
    u8 AGCCTRL2;  // AGC control.
    u8 AGCCTRL1;  // AGC control.
    u8 AGCCTRL0;  // AGC control.
    u8 FSCAL3;    // Frequency synthesizer calibration.
    u8 FSCAL2;    // Frequency synthesizer calibration.
    u8 FSCAL1;    // Frequency synthesizer calibration.
    u8 FSCAL0;    // Frequency synthesizer calibration.
    u8 FSTEST;    // Frequency synthesizer calibration control
    u8 TEST2;     // Various test settings.
    u8 TEST1;     // Various test settings.
    u8 TEST0;     // Various test settings.
    u8 IOCFG2;    // GDO2 output pin configuration
    u8 IOCFG0;    // GDO0 output pin configuration   ***
    u8 PKTCTRL1;  // Packet automation control.      ***
    u8 PKTCTRL0;  // Packet automation control.      ***      
    u8 ADDR;      // Device address.                 ***
    u8 PKTLEN;    // Packet length.                  ***
} RF_SETTINGS;

#define RF_TXMODE 1 //发送模式
#define RF_RXMODE 2 //接收模式

#define OK        1  //成功
#define ERR       0  //失败/错误

#define IDLE   0X00 //空闲
#define BUSY   0X01 //忙
#define WAIT   0X02 //等待



typedef struct
{
    unsigned char DatFlag;   
    unsigned char Busy;  
    unsigned char mode;  
}_RF_Sta;

extern _RF_Sta  RF_Sta;
extern u8 RF_Read_Buff[];//接收缓冲区

extern void Set_TxMode(void);
extern void Set_RxMode(void);
extern void delayus(u16 timeout) ;
extern void halSpiStrobe(u8 strobe);
extern u8 CC1101_Init(void);
extern u8 SpiTxRxByte(u8 dat);
extern void Open_GD0_Interrupt(void);
extern u8 halRfSendPacket(u8 *txBuffer, u8 size) ;
extern u8 halRfReceivePacket(u8 *rxBuffer);
extern void CC1101_Set_PKTLEN(u8 len);//配置CC1101数据长度

#endif

