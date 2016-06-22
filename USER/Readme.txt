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

	1).Newtable_Func;		//开桌				已完成

	2).Order_Func;			//点菜				基本完成

	3).Reminder_Func;		//催菜				开动，基本完成

	4).AddFood_Func;		//加菜				
	
	5).RetreatFood_Func;	//退菜
		
	6).Query_Func;			//查询
	
	7).MMS_Func;			//接收服务器信息
	
	8).Settings_Func;		//设置				开动
	
		a.Settings_Time_Func;	//更新时间		完成
		
		b.Settings_User_Func;	//用户管理
		
		c.Settings_LAB_Func;	//背光及声音	完成
		
		d.Settings_About_Func;	//关于			完成
		
		
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


2016/3/15 9:00 开始做开桌界面

2016/3/15 10:30 开始做点菜界面


磁片 切换算法原理

00 01 02 
10 11 12
20 21 22

u8 tiepian[3][3];
u8 i=0l;j=0;

/*界面上下左右选择*/
if(key==KEY_DOWN)		i ++;
if(key==KEY_UP)			i --;
if(key==KEY_LEFT)		j --;
if(key==KEY_RIGHT)		j ++;
if(i>=3) i = 0;
if(j>=3) j = 0;

/*图标信息*/
#define ST_X			10			//起始横坐标
#define ST_Y			33			//起始纵坐标
#define Weight 			60			//图标宽度
#define Hight			25			//图标高度
#define JX			 	10			//间隙

LCD_DrawRecFill((ST_X+j*(Weight+JX)), (ST_Y+i*(Hight+JX)), (ST_X+j*(Weight+JX)+Weight), (ST_Y+i*(Hight+JX)+Hight),BROWN);
Display_String((ST_X+j*(Weight+JX)+4),(ST_Y+i*(Hight+JX)+3),60,16,(u8 *)Food[j+i*3],16);	

2016/3/15 16:07   已基本完成点菜界面了，但还没添加食物价格以及点的数量

2016/3/15 16:10	  开始制作催菜界面

2016/3/15 16:51	  基本完成催菜界面，后期在完善

2016/3/15 16:54	  开始制作设置界面

2016/3/15 21:16   完成设置界面关于

2016/3/17 9:03		开始数据整理



需要整理的数据：
1.用户名
2.用户密码
3.桌子号
4.菜单名
5.点啥菜
6.价格
7.数量
8.时间管理
9.窗体数据


/*用户管理*/
typedef struct{
	u8 *User;
	u8 *Passwd;
}user;

/*点菜部分*/
typedef struct{
	u8 *Table;
	u8 *Food;
	u8 *Price;
	u8 *Num;
}customer;

/*菜单部分*/
typedef struct{
	u8 **Food;
	u8 *Price;
	u8 *Num;
}list;

/*窗体信息*/
typedef struct{
	u8 
}windows;


2016/3/19  15:14
开始理清系统条理

开机--》输入密码--》开桌--》点菜--》确认

