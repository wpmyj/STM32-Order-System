#include "Application.h"

/*菜单部分,后期修改从W25Q64里面获取*/
const u8 *Food[9] = {"炒饭","炒面","炒粉","面条","饺子","云吞","蒸饺","鸡排饭","叉烧饭"};

/*
	函数功能;点菜相关
*/
void Food_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag, u8 *name)
{
	u8 key;
	static short i=0,j=0,tmp1=1,tmp2=1;
	u8 Food_flag[3][3] = {0};
	/*菜单*/
	LIST_TYPE Menu = {(u8 **)Food,"10","10"};
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Food_Info = {10,33,60,25,10,10,3,3};
	/*清屏颜色，背景颜色，名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE Win={GBLUE,LBBLUE,94,"    ","返回","选择"};
	Win.Name = name;
	/*界面初始化*/
	Windows_Init(Win);
	/*显示菜单*/
	Windows_Titles(Food_Info,(u8 **)Menu.Food,LBBLUE);
	/*选择新的图标，添加高亮*/
	Windows_Title(Food_Info,(u8 **)Menu.Food,i,j,CYAN);
	
	/*循环点菜菜单*/
	do{
		/*获取功能键值*/
		key = Common_Key(&i,&j,Food_Info.tls_x, Food_Info.tls_y,Old_flag, Self_flag, Self_flag);
		if(key==KEY_WKUP)
			Food_flag[i][j] = !Food_flag[i][j];
		
		/*被选择的图标添加高亮*/
		if(tmp1!=i||tmp2!=j){	
			/*恢复原来的图标颜色*/
			if(!Food_flag[tmp1][tmp2])
				Windows_Title(Food_Info,(u8 **)Menu.Food,tmp1,tmp2,LBBLUE);
			tmp1 = i;
			tmp2 = j;
			/*选择新的图标，添加高亮*/
			Windows_Title(Food_Info,(u8 **)Menu.Food,i,j,CYAN);
		}

		/*后期再加入价格以及数量*/
		
	}while(*Self_flag);
	
}

/*
	函数功能：点菜界面
*/
void Order_Func(void)
{
	/*老的界面标志，自身界面标志，新界面标志，窗口名称*/
	Food_Func(&Menu_flag, &Order_flag,&Null,"点菜");
}

/*
	函数功能：加菜界面
*/
void AddFood_Func(void)
{		
	/*老的界面标志，自身界面标志，新界面标志，窗口名称*/
	Food_Func(&Menu_flag, &AddFood_flag,&Null,"加菜");
}

/*
	函数功能：退菜界面
*/
void RetreatFood_Func(void)
{	
	/*老的界面标志，自身界面标志，新界面标志，窗口名称*/
	Food_Func(&Menu_flag, &RetreatFood_flag,&Null,"加菜");
}

