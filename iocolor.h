#pragma once

namespace sx
{
	namespace io
	{
		// 重置各种模式
		namespace reset
		{
			constexpr auto reset_all		=	"\033[0m";			// 重置所有模式
			constexpr auto reset_fg_color	=	"\033[39m";			// 重置前景色
			constexpr auto reset_bg_color	=	"\033[49m";			// 重置背景色
		}
		
		// 前景色 字体颜色
		namespace fg
		{
			constexpr auto black	=	"\033[30m";			// Black
			constexpr auto red		=	"\033[31m";			// RED
			constexpr auto green	=	"\033[32m";			// GREEN
			constexpr auto yellow	=	"\033[33m";			// YELLOW
			constexpr auto blue		=	"\033[34m";			// BLUE
			constexpr auto magenta	=	"\033[35m";			// MAGENTA
			constexpr auto cyan		=	"\033[36m";			// CYAN
			constexpr auto white	=	"\033[37m";			// WHITE
		}

		// 背景色 背景颜色
		namespace bg
		{
			constexpr auto black	=	"\033[40m";
			constexpr auto red		=	"\033[41m";
			constexpr auto green	=	"\033[42m";
			constexpr auto yellow	=	"\033[43m";
			constexpr auto blue		=	"\033[44m";
			constexpr auto magenta	=	"\033[45m";
			constexpr auto cyan		=	"\033[46m";
			constexpr auto white	=	"\033[47m";
		}

		// 字体
		namespace font
		{
			constexpr auto bold			=	"\033[1m";			// 高亮
			constexpr auto half_bold	=	"\033[2m";			// 亮度减半
			// constexpr auto italic		=	"\033[3m";			// 斜体				不生效
			constexpr auto underline	=	"\033[4m";			// 下划线
			// constexpr auto twinkle		=	"\033[5m";			// 闪烁				不生效
		    // constexpr auto flash		=   	"\033[6m";			// 快闪				不生效
			constexpr auto anti_display =	"\033[7m";			// 反显
			constexpr auto blanking		=	"\033[8m";			// 消隐
			// constexpr auto delete_line	=	"\033[9m";			// 删除线			不生效
		}

	}

}



//#define		RESET			"\033[0m"
//#define		BLACK			"\033[30m"			/* Black */
//#define		RED				"\033[31m"			/* Red */
//#define		GREEN			"\033[32m"			/* Green */
//#define		YELLOW			"\033[33m"			/* Yellow */
//#define		BLUE			"\033[34m"			/* Blue */
//#define		MAGENTA			"\033[35m"			/* Magenta */
//#define		CYAN			"\033[36m"			/* Cyan */
//#define		WHITE			"\033[37m"			/* White */
//#define		BOLDBLACK		"\033[1m\033[30m"	/* Bold Black */
//#define		BOLDRED			"\033[1m\033[31m"	/* Bold Red */
//#define		BOLDGREEN		"\033[1m\033[32m"	/* Bold Green */
//#define		BOLDYELLOW		"\033[1m\033[33m"	/* Bold Yellow */
//#define		BOLDBLUE		"\033[1m\033[34m"	/* Bold Blue */
//#define		BOLDMAGENTA		"\033[1m\033[35m"	/* Bold Magenta */
//#define		BOLDCYAN		"\033[1m\033[36m"	/* Bold Cyan */
//#define		BOLDWHITE		"\033[1m\033[37m"	/* Bold White */


//C / C++改变终端输出字体的颜色（Linux）(2014 - 03 - 07 12:50 : 30)转载▼
//标签： c / c linux 字体 颜色 ansi控制码
//简单的说就是ESC[*m，ESC的八进制为\033， * 可以是多个属性的组合，用分号隔开。
//
//例：
//#include
//int main()
//{
//	printf("\033[31mThis is RED.\n\033[0m");
//	return 0;
//}
//31m代表字体为红色，0m代表关闭所有属性。
//
//常用的ANSI控制码如下（有些不支持）：
//\033[0m 关闭所有属性
//\033[1m 高亮
//\033[2m 亮度减半
//\033[3m 斜体
//\033[4m 下划线
//\033[5m 闪烁
//\033[6m 快闪
//\033[7m 反显
//\033[8m 消隐
//\033[9m 中间一道横线
//10 - 19 关于字体的
//21 - 29 基本与1 - 9正好相反
//30 - 37 设置前景色
//40 - 47 设置背景色
//30 : 黑
//31 : 红
//32 : 绿
//33 : 黄
//34 : 蓝色
//35 : 紫色
//36 : 深绿
//37 : 白色
//38 打开下划线, 设置默认前景色
//39 关闭下划线, 设置默认前景色
//40 黑色背景
//41 红色背景
//42 绿色背景
//43 棕色背景
//44 蓝色背景
//45 品红背景
//46 孔雀蓝背景
//47 白色背景
//48 不知道什么东西
//49 设置默认背景色
//50 - 89 没用
//90 - 109 又是设置前景背景的，比之前的颜色浅
//\033[nA 光标上移n行
//\033[nB 光标下移n行
//\033[nC 光标右移n行
//\033[nD 光标左移n行
//\033[y; xH设置光标位置
//\033[2J 清屏
//\033[K 清除从光标到行尾的内容
//\033[s 保存光标位置
//\033[u 恢复光标位置
//\033[? 25l 隐藏光标
//\033[? 25h 显示光标
