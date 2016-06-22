#include "Application.h"

#define titles				3
#define SE_LABX					10				
#define SE_LABY					25
#define SE_LABWeight			200
#define SE_LABHight			25
#define SE_LABJX					5

const u8 Settings_LAB[titles][12] = {"背光开关","调节亮度","声音开关"};

/*
	函数功能：设置背光及声音
*/
void Settings_LAB_Func(void)
{
	u8 key;
	short i=0,tmp=1;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(70,3,80,16,"背光及声音",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"返回",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"选择",16);	
	
	for(i=0;i<titles;i++){
		LCD_DrawRecFill(SE_LABX, (SE_LABY+i*(SE_LABHight+SE_LABJX)), SE_LABX+SE_LABWeight, (SE_LABY+i*(SE_LABHight+SE_LABJX))+SE_LABHight,BROWN);
		Display_String(SE_LABX+4,(SE_LABY+i*(SE_LABHight+SE_LABJX)+4),70,16,(u8 *)Settings_LAB[i],16);	
	}
	
	i = 0;
	
	do{
		key = Key_Scan();
		
		/*退出*/
		if(key==KEY_ESC){
			Settings_LAB_flag = 0;
			Settings_flag = 1;
		}
		/*选择*/
		if(key==KEY_WKUP){
			if(i==0){
				KEY_LED = !KEY_LED;
				LCD_DrawRecFill(SE_LABX+120, (SE_LABY+i*(SE_LABHight+SE_LABJX)), SE_LABX+SE_LABWeight, (SE_LABY+i*(SE_LABHight+SE_LABJX))+SE_LABHight,CYAN);
				Display_String(SE_LABX+150,(SE_LABY+i*(SE_LABHight+SE_LABJX)+4),70,16,(u8 *)(KEY_LED?"开":"关"),16);	
			}
		}
		
		/*控制关标显示*/
		if(key==KEY_UP)		i--;
		if(key==KEY_DOWN)	i++;
		if(i>=titles)			i = 0;
		if(i<0)						i = titles - 1;
		
		/*更新显示*/
		if(tmp!=i){
			LCD_DrawRecFill(SE_LABX, (SE_LABY+tmp*(SE_LABHight+SE_LABJX)), SE_LABX+SE_LABWeight, (SE_LABY+tmp*(SE_LABHight+SE_LABJX))+SE_LABHight,BROWN);
			Display_String(SE_LABX+4,(SE_LABY+tmp*(SE_LABHight+SE_LABJX)+4),70,16,(u8 *)Settings_LAB[tmp],16);	
			tmp = i;
			LCD_DrawRecFill(SE_LABX, (SE_LABY+i*(SE_LABHight+SE_LABJX)), SE_LABX+SE_LABWeight, (SE_LABY+i*(SE_LABHight+SE_LABJX))+SE_LABHight,CYAN);
			Display_String(SE_LABX+4,(SE_LABY+i*(SE_LABHight+SE_LABJX)+4),70,16,(u8 *)Settings_LAB[i],16);	
		}
	
	}while(Settings_LAB_flag);
}
