#include "Application.h"


/*菜单部分,后期修改从W25Q64里面获取*/
const u8 *Food1[9] = {"炒饭","炒面","炒粉","面条","饺子","云吞","蒸饺","鸡排饭","叉烧饭"};

void AddFood_Func(void)
{	
	u8 key;
	static short i=0,j=0,tmp1=1,tmp2=1;
	u8 Food_flag[3][3] = {0};
	/*菜单*/
	LIST_TYPE Menu = {(u8 **)Food1,"10","10"};
	
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE AddFood_Info = {10,33,60,25,10,10,3,3};
	/*清屏颜色，背景颜色，名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE AddFood_Win={YELLOW,BROWN,94,"加菜","返回","选择"};
	/*界面初始化*/
	Windows_Init(AddFood_Win);
	/*显示菜单*/
	Windows_Titles(AddFood_Info,(u8 **)Menu.Food,BROWN);
	/*选择新的图标，添加高亮*/
	Windows_Title(AddFood_Info,(u8 **)Menu.Food,i,j,CYAN);	

	do{
		/*获取功能键值*/
		key = Common_Key(&i,&j,AddFood_Info.tls_x, AddFood_Info.tls_y,&Menu_flag,&AddFood_flag,&AddFood_flag);
		if(key==KEY_WKUP)
			Food_flag[i][j] = !Food_flag[i][j];
		
		/*被选择的图标添加高亮*/
		if(tmp1!=i||tmp2!=j){	
			/*恢复原来的图标颜色*/
			if(!Food_flag[tmp1][tmp2])
				Windows_Title(AddFood_Info,(u8 **)Menu.Food,tmp1,tmp2,BROWN);
			tmp1 = i;
			tmp2 = j;
			/*选择新的图标，添加高亮*/
			Windows_Title(AddFood_Info,(u8 **)Menu.Food,i,j,CYAN);
		}

		/*后期再加入价格以及数量*/
		
	}while(AddFood_flag);
	
}
