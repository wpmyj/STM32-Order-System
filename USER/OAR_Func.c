#include "Application.h"

#define Food_Num    30

/*菜谱部分,后期修改从W25Q64里面获取*/
const u8 *Food[Food_Num] = {"蛋炒饭     ￥10","扬州炒饭   ￥10","炒面       ￥10",
														"干炒牛河   ￥10","湿炒牛河   ￥10","桂林米粉   ￥10",
														"担担面     ￥10","饺子       ￥10","云吞       ￥10",
														"蒸饺       ￥10","鸡排饭     ￥12","叉烧饭     ￥13",
														"红烧肉饭   ￥15","青椒瘦肉   ￥10","红烧牛肉面 ￥15",
														"红烧狮子头 ￥15","隆江猪脚饭 ￥10","黄焖鸡米饭 ￥15",
														"酒水另算   ￥00","水果自选   ￥00"};
						
const u8 *Null_Num[Food_Num] = {0};		

/*********************************************************************
	函数功能;点菜相关
**********************************************************************/
void Food_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag, u8 *name)
{
	#ifdef Debug_Get_Num
	u8 debug=0;
	#endif
	u8 key;
	u8 Num[Food_Num][5] = {0};
	short i=0,j=0,tmp1=0,tmp2=0;	
	/*菜单*/
	LIST_TYPE Menu = {(u8 **)Food,(u8 **)Null_Num};
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Food_Info = {10,25,130,25,10,5,1,4};
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Num_Info  = {160,25,50,25,10,5,1,4};
	/*名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE Win={94,"    ","取消","确认"};
	Win.Name = name;
	/*界面初始化*/
	Windows_Init(Win);
	/*显示菜单*/
	Windows_Titles(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,Theme_BACK);
	Windows_Titles(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,Theme_BACK);
	/*选择第一项图标，添加高亮*/
	Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,Theme_SLE);
	Windows_Title(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,i,0,Theme_SLE);
	BACK_COLOR = Theme_BACK;
	
	/*循环菜单*/
	do{
		/*获取功能键值*/
		key = Common_Key(&i,&j,5, Food_Info.tls_y,Old_flag, Self_flag, Self_flag);
		if(key==KEY_WKUP){
			*Self_flag = 0;
			Message_Warming_flag = 1;
			/*复制字符串*/
			Menu.Num[i+j*Num_Info.tls_y] = Num[i+j*Num_Info.tls_y];		//映射Num的地址到Menu.Num 里面
		}
		
		/*点菜数量*/
		Key_Input_Str(Num_Info,i,0,key,3,Num[i+j*Food_Info.tls_y]);
		Display_String(164,(Num_Info.St_y+i*(Num_Info.Hight+Num_Info.Jx_y)+4),24,16,Num[i+j*Food_Info.tls_y],16);
		
		/*被选择的图标添加高亮*/
		if(tmp1!=i){
			/*复制字符串*/
			Menu.Num[tmp1+tmp2*Num_Info.tls_y] = Num[tmp1+tmp2*Num_Info.tls_y];		//映射Num的地址到Menu.Num 里面
			/*恢复原来的图标颜色*/
			Windows_Title(Food_Info,(u8 **)Menu.Food+tmp2*Food_Info.tls_y,tmp1,0,Theme_BACK);
			Windows_Title(Num_Info,(u8 **)Menu.Num+tmp2*Num_Info.tls_y,tmp1,0,Theme_BACK);
			tmp1 = i;
			/*选择新的图标，添加高亮*/
			Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,Theme_SLE);	
			Windows_Title(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,i,0,Theme_SLE);	
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
			Windows_Titles(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,Theme_BACK);
			Windows_Titles(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,Theme_BACK);
			/*选择新的图标，添加高亮*/
			Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,Theme_SLE);
			Windows_Title(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,i,0,Theme_SLE);	
			tmp2 = j;
			i = 0;	
			#ifdef Debug_Get_Num
				for(debug=0;debug<30;debug++)
					printf("%s ",Menu.Num[debug]);
				printf("\r\n");
			#endif
		}
		
	}while(*Self_flag);
	if(*Old_flag==0)
		Message_Warming_Func(Self_flag,New_flag,"是否确认！");
	if(*New_flag==1){
		/*发送点菜单数据，整理数据*/
		u8 **food_tmp;
		u8 **num_tmp;
		u8 tmp=0;
		u8 *str;
		
		food_tmp = (u8 **)malloc(Food_Num);										//开辟空间
		num_tmp = (u8 **)malloc(Food_Num);
		str = (u8 *)malloc(Food_Num);
		
		for(i=0;i<Food_Num;i++){
			if(Menu.Num[i][0]>='0'&&Menu.Num[i][0]<='9'){				//查找有点到的食物
				num_tmp[tmp] = Menu.Num[i];												//复制食物数量地址
				food_tmp[tmp] = Menu.Food[i]; 										//复制食物名称地址
				tmp ++;																						//重新指向下一个指针数组元素
			}
		}
		COUSTOMER.Food = food_tmp;														//重新映射地址
		COUSTOMER.Num = num_tmp;															//重新映射地址
	
		/*发送点菜单*/
		sprintf((char *)str,"桌子号：%d",COUSTOMER.Table);
		Send_msg(0x08,str);
		for(i=0;i<tmp;i++){
			sprintf((char *)str,"%s***数量：%s",COUSTOMER.Food[i],COUSTOMER.Num[i]);
			Send_msg(0x08,str);
		}
		free(food_tmp);																				//释放空间
		free(num_tmp);
		free(str);
		#ifdef Debug_data
			printf("桌子号：%d\r\n",COUSTOMER.Table);
			for(i=0;i<tmp;i++)
				printf("食物：%s****数量：%s\r\n",COUSTOMER.Food[i],COUSTOMER.Num[i]);
		#endif

	}
	
}


/*********************************************************************
	函数功能：点菜界面
*********************************************************************/
void Order_Func(void)
{
	/*老的界面标志，自身界面标志，新界面标志，窗口名称*/
	Food_Func(&Menu_flag, &Order_flag,&Menu_flag,"点菜");
}

/*********************************************************************
	函数功能：加菜界面
*********************************************************************/
void AddFood_Func(void)
{	
	/*老的界面标志，自身界面标志，新界面标志，窗口名称*/
	Food_Func(&Menu_flag, &AddFood_flag,&Menu_flag,"加菜");
}

/*********************************************************************
	函数功能：退菜界面
*********************************************************************/
void RetreatFood_Func(void)
{	
	/*老的界面标志，自身界面标志，新界面标志，窗口名称*/
	Food_Func(&Menu_flag, &RetreatFood_flag,&Menu_flag,"退菜");
}

/*********************************************************************/

