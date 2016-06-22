现在已经移植好了大部分驱动

驱动部分：
1.LED： 已驱动
2.Beep:	已驱动
3.KEY： 已驱动
4.LCD:  已驱动
5.W25Q64:已驱动
6.RTC:	已驱动
7.USART:已驱动
8.ADC:	还没弄测量电量

字库部分：
1.字库：已做好

用户界面：
1.登陆界面 已做好
2.主界面：开始做
3.点菜系统：还没做
4.查询系统：还没做
5.设置界面：还没做


1.Login_Func;				//登陆				已完成

2.Home_Func;				//主界面			已完成

4.Menu_Func;				//菜单				已完成

	1).Newtable_Func;		//开桌				开动,完成

	2).Order_Func;			//点菜

	3).Reminder_Func;		//催菜

	4).AddFood_Func;		//加菜
	
	5).RetreatFood_Func;	//退菜
		
	6).Query_Func;			//查询
	
	7).MMS_Func;			//接收服务器信息
	
	8).Settings_Func;		//设置
	
		a.Updata_Func;		//更新
		
		b.User_Manage_Func;	//用户管理
		
		
extern 	u8 Newtable_flag;
extern  u8 Order_flag;
extern  u8 Reminder_flag;
extern  u8 AddFood_flag;
extern  u8 RetreatFood_flag;
extern  u8 Query_flag;
extern  u8 MMS_flag;
extern  u8 Settings_flag;

2016/3/14 22:40	基本需要用到的界面相应的c文件创立好，基本工作做好，
接下来就一步一步画界面了


2016/3/15 开始做开桌界面
