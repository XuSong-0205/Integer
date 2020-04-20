#include <iomanip>
#include <random>
#include <ctime>
#include "Integer.h"
#include "iocolor.h"
using std::default_random_engine;				// 随机数引擎
using std::uniform_int_distribution;			// 随机数分布类型

constexpr int TEST_NUM = 10;					// 测试用例的数量
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
		if (i == 5) cout << endl;							\
		cout << std::setw(20) << std::right << temp;		\
	}														\
	cout << endl;											\
} while (false);


/**
 * 进行相应的函数测试
 * 并判断计算是否正确
 * 进行相应的数据记录
 */
#define Test_oper(fun)										\
do															\
{															\
	for (int i = 0; i < TEST_NUM; ++i)						\
	{														\
		for (int j = 0; j < TEST_NUM; ++j)					\
		{													\
			const auto ti=tvec.at(i);						\
			const auto tj=tvec.at(j);						\
			const auto ans1 =								\
			(Integer(tvec.at(i)) fun Integer(tvec.at(j)));	\
			/*注意！下面若是二元运算符，将修改测试数据！*/	\
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
			tvec.at(i)=ti;									\
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
	Test_oper(fun);											\
	Test_mes();												\
	Test_err();												\
	Test_end();												\
															\
} while (false);

int main()
{
	/*{
		Integer i(222222222);
		cout << sx::io::fg::red;
		cout << std::setw(15) << std::left
			<< "i = " << std::setw(30) << std::right
			<< i << endl;

		cout << sx::io::fg::green;
		cout << std::setw(15) << std::left
			<< "i + 3 = " << std::setw(30) << std::right
			<< i + 3 << endl;

		cout << sx::io::fg::black;
		cout << std::setw(15) << std::left
			<< "i + 999 = " << std::setw(30) << std::right
			<< i + 999 << endl;

		cout << sx::io::fg::cyan;
		cout << std::setw(15) << std::left
			<< "i + 99999999 = " << std::setw(30) << std::right
			<< i + 99999999 << endl;

		Integer j("1999999999999999999999999");
		cout << sx::io::fg::magenta;
		cout << std::setw(15) << std::left
			<< "j = " << std::setw(30) << std::right
			<< j << endl;

		cout << sx::io::fg::yellow;
		cout << std::setw(15) << std::left
			<< "j + 666 = " << std::setw(30) << std::right
			<< j + 666 << endl;

		cout << sx::io::fg::blue;
		cout << std::setw(15) << std::left
			<< "i + j = " << std::setw(30) << std::right
			<< i + j << endl;


		Integer k("123456789");
		cout << sx::io::fg::magenta;
		cout << std::setw(15) << std::left
			<< "k = " << std::setw(30) << std::right
			<< k << endl;

		cout << sx::io::fg::yellow;
		cout << std::setw(15) << std::left
			<< "k - 999999 = " << std::setw(30) << std::right
			<< k - 999999 << endl;



		Integer h("333");
		cout << sx::io::fg::magenta;
		cout << std::setw(15) << std::left
			<< "h = " << std::setw(30) << std::right
			<< h << endl;

		cout << sx::io::fg::yellow;
		cout << std::setw(15) << std::left
			<< "h * 222 = " << std::setw(30) << std::right
			<< h * 222 << endl;
	}*/

	system("color 0A");

	/*{
		cout << sx::io::bg::black << sx::io::fg::green;
		cout << "四则运算测试 : 开始" << endl;
		vector<Integer> vec;
		vec.push_back(111111111);
		vec.push_back(999999999);
		vec.push_back(-666666666);
		vec.push_back(Integer("123456789"));
		vec.push_back(Integer("987654321"));
		vec.push_back(Integer("-333333333"));
		vec.push_back(Integer("-15198621265126513156"));
		vec.push_back(Integer("874156894651986519845619861598651"));
		vec.push_back(Integer("-233333333"));
		vec.push_back(Integer("-6561894986584166841165815611948914"));

		cout << "输出所有值 : " << endl;
		for (size_t i = 0; i < vec.size(); ++i)
			cout << "vec.at(" << i << ") : " << vec.at(i) << endl;

		for (size_t i = 0; i < vec.size(); ++i)
		{
			for (size_t j = 0; j < vec.size(); ++j)
			{
				cout << "i = " << vec.at(i) << "	,j = " << vec.at(j) << endl;
				cout << "i + j = " << vec.at(i) + vec.at(j) << endl;
				cout << "i - j = " << vec.at(i) - vec.at(j) << endl;
				cout << "i * j = " << vec.at(i) * vec.at(j) << endl;
				cout << endl;
			}
		}

		cout << "四则测试 : 结束" << endl;
	}*/

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
	//Test_fun(/);		// 未实现
	//Test_fun(%);		// 未实现
	Test_fun(+=);
	Test_fun(-=);
	Test_fun(*=);
	//Test_fun(/=);		// 未实现
	//Test_fun(%=);		// 未实现
	Test_fun(&&);
	Test_fun(||);

	// 一元运算符测试




	return 0;
}