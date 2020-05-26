#include <iomanip>
#include <random>
#include <ctime>
#include "Integer.h"
#include "iocolor.h"
using std::default_random_engine;				// 随机数引擎
using std::uniform_int_distribution;			// 随机数分布类型

#define TEST_STYLE 0
constexpr int TEST_NUM = 100;					// 测试用例的数量
constexpr int TEST_RANGE = 400000000;			// 测试用例的数值范围
using test_type=__int64;						// 用来检测案例是否正确的辅助类型


/**
 * 以下所有的宏函数共同组成了测试函数
 * 注意！以下宏函数必须一起使用！
 * 否则无法正常编译运行！
 * 应按照宏函数的定义顺序使用！
 * 这很重要！
 */

/**
 * 测试案列的开始部分
 */
#define Test_start()										\
do															\
{															\
	cout << "函数测试 : " << std::setw(3)					\
	<<fun_name << "开始"<<endl;								\
	cout << "随机生成测试数据 : " << endl;					\
} while (false);


/**
 * 随机生成测试案列所用的数据
 */
#define Test_data()											\
do															\
{															\
	const uniform_int_distribution<test_type>				\
	range(0, TEST_RANGE);									\
	for (int i = 0; i < TEST_NUM; ++i)						\
	{														\
		const test_type temp =								\
		range(random) * (range(random) & 1 ? 1 : -1);		\
		tvec.push_back(temp);								\
		if (i&&!(i%5)) cout << endl;						\
		cout << std::setw(20) << std::right << temp;		\
	}														\
	cout << endl;											\
} while (false);


/**
 * 进行相应的二元运算符测试
 * 并判断计算是否正确
 * 进行相应的数据记录
 */
#define Test_binary(fun)									\
do															\
{															\
	for (int i = 0; i < TEST_NUM; ++i)						\
	{														\
		for (int j = 0; j < TEST_NUM; ++j)					\
		{													\
			const auto ti=tvec.at(i);						\
			const auto tj=tvec.at(j);						\
			auto ans1 = Integer();							\
			if(TEST_STYLE == 0)								\
			ans1 =											\
			(Integer(tvec.at(i)) fun Integer(tvec.at(j)));	\
			else if(TEST_STYLE == 1)						\
			ans1 =											\
			(Integer(tvec.at(i)) fun tvec.at(j));			\
			/*注意！下面若是赋值运算符，将修改测试数据！*/	\
			const auto ans2 =								\
			(tvec.at(i) fun tvec.at(j));					\
			if (ans1 == ans2) pass += 1;					\
			else											\
			{												\
				noPass += 1;								\
				err.push_back({ ti,tj });					\
				falseData.push_back(ans1);					\
				trueData.push_back(ans2);					\
			}												\
			/*修改回原来的数据*/							\
			tvec.at(i) = ti;								\
		}													\
	}														\
} while (false);


/**
 * 显示测试案列的通过情况
 */
#define Test_mes()											\
do															\
{															\
	if (pass != pass + noPass)								\
	cout << sx::io::fg::red;								\
	cout <<std::left<<std::setw(11)<<"通过测试数   : "		\
	<< std::left << std::setw(9) << pass;					\
	cout << std::left << std::setw(10) << "未通过测试数 : "	\
	<< std::left << std::setw(8) << noPass;					\
	cout << std::left << std::setw(8) << "通过率 : "		\
	<< std::left << pass /(pass + noPass) * 100				\
	<< "%" << endl;											\
} while (false);


/**
 * 显示所有的错误案列
 * 和函数表达式
 * 错误答案和正确答案
 */
#define Test_err()											\
do															\
{															\
	if (pass != pass + noPass)								\
	{														\
		cout << "错误测试案例 : " << endl;					\
		for (size_t i = 0; i < err.size(); ++i)				\
		{													\
			cout											\
			<< std::setw(8) << std::left << "error "		\
			<< std::setw(4) << i << " : "					\
			<< std::setw(12) << std::right<<err.at(i).at(0)	\
			<< " " << fun_name << " "						\
			<< std::setw(12) << std::left << err.at(i).at(1)\
			<< "  " << std::setw(10) << "错误答案 : "		\
			<< std::setw(20) << falseData.at(i)				\
			<< std::setw(10) << "正确答案 : "				\
			<< std::setw(20) << trueData.at(i) << endl;		\
		}													\
	}														\
} while (false);


/**
 * 测试案列结束部分
 */
#define Test_end()											\
do															\
{															\
	cout << sx::io::fg::green;								\
	cout <<  "函数测试 : " <<std::setw(3)					\
	<< fun_name << "结束\n" << endl;						\
} while (false);


/**
 * 二元运算符测试
 * 测试案列的外部接口
 * 进行各种所需数据的声明
 * 调用前面的宏函数进行测试工作
 */
#define Test_fun(fun)										\
do															\
{															\
	string fun_name=#fun;			/*函数名称*/			\
	double pass = 0;				/*通过的测试数量*/		\
	double noPass = 0;				/*未通过的测试数量*/	\
	vector<vector<test_type>> err;	/*未通过的测试数据*/	\
	vector<Integer>	falseData;		/*错误答案*/			\
	vector<Integer>	trueData;		/*正确答案*/			\
	vector<test_type> tvec;			/*测试数据*/			\
															\
	Test_start();											\
	Test_data();											\
	Test_binary(fun);										\
	Test_mes();												\
	Test_err();												\
	Test_end();												\
															\
} while (false);



int main()
{
	system("color 0A");
	default_random_engine random(time(nullptr) & 0xffffffff);

	// 二元运算符测试
	Test_fun(==);
	Test_fun(!=);
	Test_fun(<);
	Test_fun(<=);
	Test_fun(>);
	Test_fun(>=);
	Test_fun(+);
	Test_fun(-);
	Test_fun(*);
	Test_fun(/);
	Test_fun(%);
	Test_fun(+=);
	Test_fun(-=);
	Test_fun(*=);
	Test_fun(/=);
	Test_fun(%=);
	Test_fun(&&);
	Test_fun(||);

	// 一元运算符不测试了，肯定也没啥问题。。。

	Integer i0 = 123456;
	cout << 3 + i0 << endl;
	cout << 6 - i0 << endl;
	cout << 13 % Integer(5) << endl;
	cout << (i0 == 3) << endl;

	system("pause");

	return 0;
}