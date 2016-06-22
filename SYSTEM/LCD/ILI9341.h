#ifndef ILI9341_H
#define ILI9341_H		
#include "sys.h"	 
#include "stdlib.h"
#include "math.h"
#include "Delay.h"

/*定义屏幕大小*/
#define LCDWIDTH         240
#define LCDHEIGHT        320

/*LCD重要参数集*/
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				  //LCD ID
	u8  dir;			  //横屏还是竖屏控制：0，竖屏；1，横屏。	
	u8	wramcmd;		//开始写gram指令
	u8  setxcmd;		//设置x坐标指令
	u8  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	  

/*扫描方向定义*/
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR  R2L_D2U  //默认的扫描方向

/*TFTLCD部分外要调用的函数*/
extern _lcd_dev LCDDEV;	//管理LCD重要参数
extern u16  POINT_COLOR;//默认黑色
extern u16  BACK_COLOR; //背景颜色.默认为白色
extern const unsigned char ASCII_12[95][12];   //ASCII字符集
extern const unsigned char ASCII_16[95][16];

/*定义画笔颜色*/
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

/*LCD相关端口定义*/
#define  LCD_BL 	  PAout(3)					 //LCD_BL背光				PA3
#define  LCD_CS     PCout(9)     		   //片选端口         PC9
#define  LCD_RS     PCout(8)           //数据/命令        PC8           
#define  LCD_WR     PCout(7)           //写数据           PC7
#define  LCD_RD     PCout(6)           //读数据           PC6
/*数据线*/
#define  DATA_OUT()		{GPIOB->CRL = 0x0;GPIOB->CRH = 0x0;GPIOB->CRL = 0x33333333;GPIOB->CRH = 0x33333333;GPIOB->ODR = 0xffff;}
#define  DATA_IN()		{GPIOB->CRL = 0x0;GPIOB->CRH = 0x0;GPIOB->CRL = 0x88888888;GPIOB->CRH = 0x88888888;GPIOB->ODR = 0;}
#define  DataOut(x) 	 GPIOB->ODR = x 	 //数据输出
#define  DataIn     	 GPIOB->IDR   		 //数据输入

/*
	写8位数据函数用宏定义,提高速度
*/
#define LCD_WR_DATA(data){\
	DATA_OUT();\
	LCD_RS=1;\
	LCD_CS=0;\
	DataOut(data);\
	LCD_WR=0;\
	LCD_WR=1;\
	LCD_CS=1;\
	DATA_IN();\
}							
/*
	写8位寄存器函数用宏定义,提高速度
*/
#define LCD_WR_REG(data){\
	DATA_OUT();\
	LCD_RS=0;\
	LCD_CS=0;\
	DataOut(data);\
	LCD_WR=0;\
	LCD_WR=1;\
	LCD_CS=1;\
	DATA_IN();\
}

/*
	相关函数声明
*/
void Show_Font(u16 x,u16 y,u8 *dzk,u8 size);    															  
void LCD_Init(void);													   	 //初始化
void LCD_DisplayOn(void);													 //开显示
void LCD_DisplayOff(void);													//关显示
void LCD_Clear(u16 Color);	 												//清屏
void LCD_SetCursor(u16 Xpos, u16 Ypos);							//设置光标
void LCD_DrawPoint(u16 x,u16 y);									  //画点
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);			//快速画点
u16  LCD_ReadPoint(u16 x,u16 y); 										//读点 
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);								//画圆
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							  //画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   			//画矩形
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//填充单色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);			//填充指定颜色
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//显示一个字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//显示一个数字
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);		//显示 数字
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//显示一个字符串,12/16字体
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);		  
void LCD_Scan_Dir(u8 dir);							//设置屏扫描方向
void LCD_Display_Dir(u8 dir);						//设置屏幕显示方向
void LCD_Pic(const unsigned char * p);
//画点
//x,y:坐标
//color:此点的颜色
void LCD_DrawPoint_color(u16 x,u16 y,u16 color);

//自定义的函数
void Draw_Circle_Line(int x,int y,int r,int du,int color);
void Draw_Circles(int x,int y,int r,int q,int color);
void Draw_Circle_Dot(int x,int y,int r,int q,int du,int color);
void LCD_DrawRecFill(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);

#endif
