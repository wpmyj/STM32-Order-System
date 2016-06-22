#include "Application.h"

/*图标信息*/
#define ST_X			10			//起始横坐标
#define ST_Y			53			//起始纵坐标
#define Weight 		60			//图标宽度
#define Hight			25			//图标高度
#define JX			 	10			//间隙
#define titles_x	3
#define titles_y	2

/*时间项*/
const u8 Time[titles_x*titles_y][3] = {"年","月","日","时","分","秒"};
/*时间选择标记*/
u8 Time_flag[titles_y][titles_x] = {0};
u8 date_time[titles_x*titles_y][11] = {"2016","3","16","16","31","20"};


/*
	函数功能：按键输入处理
	参数：u8 key：外部输入的按键值
	返回值：处理完之后的数据首地址
*/
u8 *Key_Input1(u8 key, u8 range, u8 *Clear_All)
{
	static u8 i=0, Esc_flag=1;
	static u8 Input_Data[11]="          ";	
	
	/*正常获取数据*/
	if(i<range){								//输入范围
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
	
	if(*Clear_All){
		for(i=0;i<11;i++)
			Input_Data[i] = ' ';
		i=0;
		Esc_flag=1;
		*Clear_All = 0;
	}
	
	return Input_Data;
}


/*
	函数功能：设置时间
*/
void Settings_Time_Func(void)
{
	u8 key;
	u8 *str;
	u8 set_flag=0;
	short i=0,j=0,tmp1=1,tmp2=1;
	TIME_TYPE time;
	
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(78,3,80,16,"设置时钟",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,(u8 *)(Clear_flag?"清除":"返回"),16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"确认",16);	
	
	
	/*显示框框*/
	for(i=0;i<titles_y;i++){
		for(j=0;j<titles_x;j++){
			LCD_DrawRecFill((ST_X+j*(Weight+JX)), (ST_Y+i*(Hight+JX)), (ST_X+j*(Weight+JX)+Weight), (ST_Y+i*(Hight+JX)+Hight),(Time_flag[i][j]?CYAN:BROWN));
			Display_String((ST_X+j*(Weight+JX)+40),(ST_Y+i*(Hight+JX)+4),20,16,(u8 *)Time[j+i*3],16);	
		}
	}
	i = 0;
	j = 0;
	
	
	do{
		key = Key_Scan();
		
		/*退出*/
		if((key==KEY_ESC)&&Clear_flag == 0){
			Settings_Time_flag = 0;
			Settings_flag = 1;
		}
		/*选择*/
		if(key==KEY_WKUP){
			Settings_Time_flag = 0;
			Settings_flag = 1;
			set_flag = 1;
			strcpy((char *)date_time[j+i*3],(const char *)str);
		}
	
		/*界面上下左右选择*/
		if(key==KEY_DOWN)		i ++;
		if(key==KEY_UP)			i --;
		if(key==KEY_LEFT)		j --;
		if(key==KEY_RIGHT)	j ++;
		if(i>=titles_y) i = 0;
		if(j>=titles_x) j = 0;
		if(i<0)	 i = titles_y - 1;
		if(j<0)	 j = titles_x - 1;
		
		
		
		/*被选择的图标添加高亮*/
		if(tmp1!=i||tmp2!=j){	
			/*恢复原来的图标颜色*/

			LCD_DrawRecFill((ST_X+tmp2*(Weight+JX)), (ST_Y+tmp1*(Hight+JX)), (ST_X+tmp2*(Weight+JX)+Weight), (ST_Y+tmp1*(Hight+JX)+Hight),BROWN);
			Display_String((ST_X+tmp2*(Weight+JX)+40),(ST_Y+tmp1*(Hight+JX)+3),20,16,(u8 *)Time[tmp2+tmp1*3],16);	
			strcpy((char *)date_time[tmp2+tmp1*3],(const char *)str);
			Display_String((ST_X+tmp2*(Weight+JX)+4),(ST_Y+tmp1*(Hight+JX)+4),36,16,date_time[tmp2+tmp1*3],16);		//显示时间
			tmp1 = i;
			tmp2 = j;
			Time_flag[i][j] = 1; 
			
			/*选择新的图标，添加高亮*/
			LCD_DrawRecFill((ST_X+j*(Weight+JX)), (ST_Y+i*(Hight+JX)), (ST_X+j*(Weight+JX)+Weight), (ST_Y+i*(Hight+JX)+Hight),CYAN);
			Display_String((ST_X+j*(Weight+JX)+40),(ST_Y+i*(Hight+JX)+4),20,16,(u8 *)Time[j+i*3],16);
			Display_String((ST_X+j*(Weight+JX)+4),(ST_Y+i*(Hight+JX)+4),36,16,date_time[j+i*3],16);					//显示时间
		}
		
		str = Key_Input1(key,4,&Time_flag[i][j]);			//获取时间
		Display_String((ST_X+j*(Weight+JX)+4),(ST_Y+i*(Hight+JX)+4),36,16,str,16);					//显示时间
		
		
	}while(Settings_Time_flag);	

	if(set_flag){
		sscanf((char *)date_time[0],"%d",(int*)&time.year);
		sscanf((char *)date_time[1],"%d",(int*)&time.month);
		sscanf((char *)date_time[2],"%d",(int*)&time.day);
		sscanf((char *)date_time[3],"%d",(int*)&time.hour);
		sscanf((char *)date_time[4],"%d",(int*)&time.min);
		sscanf((char *)date_time[5],"%d",(int*)&time.second);
		Set_RTC_Time(time);
	}
}
