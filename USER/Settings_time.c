#include "Application.h"

/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
WINDOWS_TYPE Settings_Time_Info = {10,53,60,25,10,10,3,2};

/*清屏颜色，背景颜色，名称起始横坐标，按键1，按键2*/
WINDOWS_INIT_TYPE Settings_Time_Win={YELLOW,BROWN,78,"设置时间","取消","确认"};


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
	函数功能：设置时间
*/
void Settings_Time_Func(void)
{
	u8 key;
	u8 *str;
	u8 set_flag=0;
	short i=0,j=0,tmp1=0,tmp2=0;
	TIME_TYPE time;
	
	/*窗口初始化*/
	Windows_Init(Settings_Time_Win);	

//	/*显示菜单*/
//	Windows_Titles(Settings_Time_Info,(u8 **)Time,BROWN);
	
	/*显示框框*/
	for(i=0;i<titles_y;i++){
		for(j=0;j<titles_x;j++){
			LCD_DrawRecFill((ST_X+j*(Weight+JX)), (ST_Y+i*(Hight+JX)), (ST_X+j*(Weight+JX)+Weight), (ST_Y+i*(Hight+JX)+Hight),BROWN);
			Display_String((ST_X+j*(Weight+JX)+40),(ST_Y+i*(Hight+JX)+4),20,16,(u8 *)Time[j+i*3],16);	
		}
	}
	i = 0;
	j = 0;
	
	do{
		
		/*获取功能键值*/
		key = Common_Key(&i,&j,3,2, &Settings_flag,&Settings_Time_flag,&Settings_flag);		
		if(key==KEY_WKUP){
			set_flag = 1;
			strcpy((char *)date_time[j+i*3],(const char *)str);
		}
		
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
		
		str = Key_Input(key,4,&Time_flag[i][j]);			//获取时间
		Display_String((ST_X+j*(Weight+JX)+4),(ST_Y+i*(Hight+JX)+4),36,16,str,16);					//显示时间
		
	}while(Settings_Time_flag);	
	Clear_flag = 0;
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
