#include "Font.h"

Font_Info Font_Addr;  //字库地址存放结构体

/*
	函数功能：中文字库初始化
*/
void Font_Init(void) 
{
	Font_Addr.F16Addr=0;  //16*16字库起始地址设置
//	Font_Addr.F24Addr=1;	//没有烧写24*24的字库所以屏蔽
}

/*
	函数功能：从Flash芯片里面读取汉字点阵码
	参数：u8 *code 汉字；
				u8 *buff 存储汉字点阵码空间首地址
				u8 size  汉字类型 16*16 还是 24*24
*/
void Get_Font_Data(u8 *HZ,u8 *buff,u8 size)
{
	u32 Addr_Offset;
	u8 Csize;
	
	Csize = (size/8+((size%8)?1:0))*(size);						//计算需要取多少字节点阵码
	Addr_Offset = ((HZ[0]-0xa1)*94+(HZ[1]-0xa1))*32;	//计算偏移地址
	
	switch(size){																			//读取点阵码
		case 16:FLASH_Serial_Read_Data(Addr_Offset+Font_Addr.F16Addr,Csize,buff);break;
		case 24:FLASH_Serial_Read_Data(Addr_Offset+Font_Addr.F24Addr,Csize,buff);break;
	}
}

/*
	函数功能：显示一个汉字字符
	参数：u16 x			显示的横坐标
				u16 y		 	显示的纵坐标
				u8 *font 	显示的汉字
				u8 size		显示的字体大小
*/
void Display_HZ(u16 x,u16 y,u8 *font,u8 size)
{
	u8 i,j,k=0;
	u16 y0 = y;
	u8 HZ[200];										//用来存放字符点阵码
	
	Get_Font_Data(font,HZ,size);	//从flash芯片里面获取字符点阵码
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){		//显示上下一列的字节
			if(HZ[k]&0x80)	
				LCD_DrawPoint(x,y);//如果是1的话显示
			else 						
				LCD_DrawPoint_color(x,y,BACK_COLOR);
			y ++;									//y坐标增加1
			HZ[k] <<= 1;					//把次高位变成最高位
			if((j+1)%8==0) k++;		//如果显示完一个字节，显示下一个字节
		}
		x ++;										//显示完一行，x地址增加1
		y = y0;									//y的坐标恢复到原始坐标
	}					
	
}


/*
	函数功能：显示汉字字符串
	参数：u16 x			显示的横坐标
				u16 y		 	显示的纵坐标
				u16 width 显示的宽度
				u16 height显示的高度
				u8 *str 	显示的汉字字符串
				u8 size		显示的字体大小
*/
void Display_String(u16 x,u16 y,u16 width,u16 height,u8 *str,u8 size)
{					
	u16 x0=x;
	u16 y0=y;							  	      				    				  	  
	while(*str!=0){  									//数据未结束
		if(*str>0x80){ 									//判断是否是汉字
			if(x>(x0+width-size)){				//换行 
				y += size;
				x = x0;		  
			}
			if(y>(y0+height-size))break; 	//越界返回  	
				
			Display_HZ(x,y,str,size); 	//显示这个汉字
			str += 2;   									//汉字是两个字节
			x += size;  									//下一个汉字偏移	
		}else{  												//显示英文字符
			if(x>(x0+width-size/2)){			//换行			   
				y += size;
				x = x0;	   
			}							    
			if(y>(y0+height-size))
				break;      								//越界返回   
			else 
				LCD_ShowChar(x,y,*str,size,0);//有效部分写入 
			str ++;     									//指针加1---英文字符
			x += size/2; 									//字符是汉字的一半 
		}				 
	}   
} 

