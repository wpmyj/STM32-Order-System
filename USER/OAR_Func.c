#include "Application.h"

#define Food_Num    30

/*菜单部分,后期修改从W25Q64里面获取*/
const u8 *Food[Food_Num] = {"炒饭     ￥10","炒面     ￥10","炒粉     ￥10",
														"面条     ￥10","饺子     ￥10","云吞     ￥10",
														"蒸饺     ￥10","鸡排饭   ￥12","叉烧饭   ￥13"};
						
const u8 *Null_Num[Food_Num] = {0};		
u8 Num[Food_Num][5] = {0};	
/*********************************************************************
	函数功能;点菜相关
**********************************************************************/
void Food_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag, u8 *name)
{
	#ifdef Debug_Get_Num
	u8 debug=0;
	#endif
	u8 key;
	u8 tmp;
	u8 *str;
	short i=0,j=0,tmp1=0,tmp2=0;
	u8 Food_flag[Food_Num] = {0};
	/*菜单*/
	LIST_TYPE Menu = {(u8 **)Food,(u8 **)Null_Num,(u8 **)Null_Num};
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Food_Info = {10,25,130,25,10,5,1,4};
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Num_Info  = {160,25,50,25,10,5,1,4};
	/*清屏颜色，背景颜色，名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE Win={GBLUE,LBBLUE,94,"    ","取消","选择"};
	Win.Name = name;
	/*界面初始化*/
	Windows_Init(Win);
	/*显示菜单*/
	Windows_Titles(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,LBBLUE);
	Windows_Titles(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,LBBLUE);
	/*选择第一项图标，添加高亮*/
	Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,CYAN);
	
	/*循环菜单*/
	do{
		/*获取功能键值*/
		key = Common_Key(&i,&j,5, Food_Info.tls_y,Old_flag, Self_flag, Self_flag);
		if(key==KEY_WKUP){
			Food_flag[i+j*Food_Info.tls_y] = 1;
			Clear_All = 1;
			/*输入数量高亮*/
			Windows_Title(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,i,0,CYAN);	
			#ifdef Debug_Get_Num
				printf("Food_flag[%d]:%d   i = %d j = %d \r\n",i+j*Food_Info.tls_y,Food_flag[i+j*Food_Info.tls_y],i,j);
			#endif
		}
		
		/*点菜数量*/
		if(Food_flag[i+j*Food_Info.tls_y]){
			str = Key_Input(key,3,&Clear_All);
			Display_String(164,(Num_Info.St_y+i*(Num_Info.Hight+Num_Info.Jx_y)+4),24,16,str,16);
		}

		/*被选择的图标添加高亮*/
		if(tmp1!=i){
			/*复制字符串*/
			if(Food_flag[tmp1+j*Food_Info.tls_y]){
				Food_flag[tmp1+j*Food_Info.tls_y] = 0;
				for(tmp=0;tmp<4;tmp++){
					Num[tmp1+j*Food_Info.tls_y][tmp] = str[tmp];
				}
				Num[tmp1+j*Food_Info.tls_y][tmp] = '\0';			//结束符，不加的话，下一次有会接上这次的字符
				Menu.Num[tmp1+j*Num_Info.tls_y] = Num[tmp1+j*Num_Info.tls_y];		//映射Num1的地址到Menu.Num 里面
			}
			/*恢复原来的图标颜色*/
			Windows_Title(Food_Info,(u8 **)Menu.Food+tmp2*Food_Info.tls_y,tmp1,0,LBBLUE);
			Windows_Title(Num_Info,(u8 **)Menu.Num+tmp2*Num_Info.tls_y,tmp1,0,LBBLUE);
			tmp1 = i;
			/*选择新的图标，添加高亮*/
			Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,CYAN);	
			#ifdef Debug_Get_Num
				for(debug=0;debug<30;debug++){
					printf("%s ",Menu.Num[debug]);
				}
				printf("\r\n");
			#endif
		}

		/*变化菜单*/
		if(tmp2!=j){
			/*显示菜单*/
			Windows_Titles(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,LBBLUE);
			Windows_Titles(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,LBBLUE);
			/*选择新的图标，添加高亮*/
			Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,CYAN);
			tmp2 = j;
			i = 0;	
			#ifdef Debug_Get_Num
				for(debug=0;debug<30;debug++)
					printf("%s ",Menu.Num[debug]);
				printf("\r\n");
			#endif
		}
		
	}while(*Self_flag);
	
}

/*********************************************************************
	函数功能：点菜界面
*********************************************************************/
void Order_Func(void)
{
	/*老的界面标志，自身界面标志，新界面标志，窗口名称*/
	Food_Func(&Menu_flag, &Order_flag,&Null,"点菜");
}

/*********************************************************************
	函数功能：加菜界面
*********************************************************************/
void AddFood_Func(void)
{		
	/*老的界面标志，自身界面标志，新界面标志，窗口名称*/
	Food_Func(&Menu_flag, &AddFood_flag,&Null,"加菜");
}

/*********************************************************************
	函数功能：退菜界面
*********************************************************************/
void RetreatFood_Func(void)
{	
	/*老的界面标志，自身界面标志，新界面标志，窗口名称*/
	Food_Func(&Menu_flag, &RetreatFood_flag,&Null,"退菜");
}

/*********************************************************************/

