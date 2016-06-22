#include "Application.h"

u8 Clear_flag = 0;

/*
	函数功能：按键输入处理
	参数：u8 key：外部输入的按键值
	返回值：处理完之后的数据首地址
*/
u8 *Key_Input(u8 key){
	static u8 i=0,Esc_flag=1;
	static u8 Input_Data[11]="          ";
	
	/*正常获取数据*/
	if(i<10){								//输入范围0-10
		if((key>0&&key<10))		//输入数字1-9
			Input_Data[i++] = key + 0x30;
		if(key==KEY_0)				//输入数字0
			Input_Data[i++] = '0';
		if(key==KEY_X)				//输入字符*
			Input_Data[i++] = '*';
		if(key==KEY_J)				//输入字符#
			Input_Data[i++] = '#';
	}
	
	/*清除标志位*/
	if((i==1)&&Clear_flag==0){
		LCD_DrawRecFill(10, 145, 60, 170,BROWN);//清除效果
	}	
	if(i!=0){
		Clear_flag = 1;
		Display_String(20,150,80,16,"清除",16);
	}else{
		Clear_flag = 0;
		Display_String(20,150,80,16,"取消",16);
	}

	/*清除数据*/
	if(key==KEY_ESC){				//清除键
		Esc_flag = 0;
		LCD_DrawRecFill(10, 145, 60, 170,BROWN);//清除效果
		if(i!=0)							//范围最低0
			Input_Data[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
	return Input_Data;
}

/*
	函数功能：开新桌
*/
void Newtable_Func(void)
{
	u8 key;
	u8 *Table;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"开桌",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,(u8 *)(Clear_flag?"清除":"取消"),16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"确认",16);	
	
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"请输入新开桌号：",16);
	
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
		key = Key_Scan();
		
		/*退出*/
		if((key==KEY_ESC)&&Clear_flag==0){
			Newtable_flag = 0;
			Menu_flag = 1;
		}
		/*选择*/
		if((key==KEY_WKUP)&&Clear_flag){
			Newtable_flag = 0;
			Menu_flag = 1;
			/*后期加上发送桌子号*/
		}
		
		/*获取新开桌子号*/
		Table = Key_Input(key);
		Display_String(70,90,120,16,Table,16);
		
	}while(Newtable_flag);
	
}


