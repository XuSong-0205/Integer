#include <iomanip>
#include <random>
#include <ctime>
#include "Integer.h"
#include "iocolor.h"
using std::default_random_engine;				// ���������
using std::uniform_int_distribution;			// ������ֲ�����

constexpr int TEST_NUM = 10;					// ��������������
constexpr int TEST_RANGE = 400000000;			// ������������ֵ��Χ
using test_type=__int64;						// ������ⰸ���Ƿ���ȷ�ĸ�������


/**
 * �������еĺ꺯����ͬ����˲��Ժ���
 * ע�⣡���º꺯������һ��ʹ�ã�
 * �����޷������������У�
 * Ӧ���պ꺯���Ķ���˳��ʹ�ã�
 * �����Ҫ��
 */

/**
 * ���԰��еĿ�ʼ����
 */
#define Test_start()										\
do															\
{															\
	cout << "�������� : " << std::setw(3)					\
	<<fun_name << "��ʼ"<<endl;								\
	cout << "������ɲ������� : " << endl;					\
} while (false);


/**
 * ������ɲ��԰������õ�����
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
 * ������Ӧ�ĺ�������
 * ���жϼ����Ƿ���ȷ
 * ������Ӧ�����ݼ�¼
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
			/*ע�⣡�������Ƕ�Ԫ����������޸Ĳ������ݣ�*/	\
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
			/*�޸Ļ�ԭ��������*/							\
			tvec.at(i)=ti;									\
		}													\
	}														\
} while (false);


/**
 * ��ʾ���԰��е�ͨ�����
 */
#define Test_mes()											\
do															\
{															\
	if (pass != pass + noPass)								\
	cout << sx::io::fg::red;								\
	cout <<std::left<<std::setw(11)<<"ͨ��������   : "		\
	<< std::left << std::setw(9) << pass;					\
	cout << std::left << std::setw(10) << "δͨ�������� : "	\
	<< std::left << std::setw(8) << noPass;					\
	cout << std::left << std::setw(8) << "ͨ���� : "		\
	<< std::left << pass /(pass + noPass) * 100				\
	<< "%" << endl;											\
} while (false);


/**
 * ��ʾ���еĴ�����
 * �ͺ������ʽ
 * ����𰸺���ȷ��
 */
#define Test_err()											\
do															\
{															\
	if (pass != pass + noPass)								\
	{														\
		cout << "������԰��� : " << endl;					\
		for (size_t i = 0; i < err.size(); ++i)				\
		{													\
			cout											\
			<< std::setw(8) << std::left << "error "		\
			<< std::setw(4) << i << " : "					\
			<< std::setw(12) << std::right<<err.at(i).at(0)	\
			<< " " << fun_name << " "						\
			<< std::setw(12) << std::left << err.at(i).at(1)\
			<< "  " << std::setw(10) << "����� : "		\
			<< std::setw(20) << falseData.at(i)				\
			<< std::setw(10) << "��ȷ�� : "				\
			<< std::setw(20) << trueData.at(i) << endl;		\
		}													\
	}														\
} while (false);


/**
 * ���԰��н�������
 */
#define Test_end()											\
do															\
{															\
	cout << sx::io::fg::green;								\
	cout <<  "�������� : " <<std::setw(3)					\
	<< fun_name << "����\n" << endl;						\
} while (false);


/**
 * ���԰��е��ⲿ�ӿ�
 * ���и����������ݵ�����
 * ����ǰ��ĺ꺯�����в��Թ���
 */
#define Test_fun(fun)										\
do															\
{															\
	string fun_name=#fun;			/*��������*/			\
	double pass = 0;				/*ͨ���Ĳ�������*/		\
	double noPass = 0;				/*δͨ���Ĳ�������*/	\
	vector<vector<test_type>> err;	/*δͨ���Ĳ�������*/	\
	vector<Integer>	falseData;		/*�����*/			\
	vector<Integer>	trueData;		/*��ȷ��*/			\
	vector<test_type> tvec;			/*��������*/			\
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
		cout << "����������� : ��ʼ" << endl;
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

		cout << "�������ֵ : " << endl;
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

		cout << "������� : ����" << endl;
	}*/

	default_random_engine random(time(nullptr) & 0xffffffff);

	// ��Ԫ���������
	Test_fun(==);
	Test_fun(!=);
	Test_fun(<);
	Test_fun(<=);
	Test_fun(>);
	Test_fun(>=);
	Test_fun(+);
	Test_fun(-);
	Test_fun(*);
	//Test_fun(/);		// δʵ��
	//Test_fun(%);		// δʵ��
	Test_fun(+=);
	Test_fun(-=);
	Test_fun(*=);
	//Test_fun(/=);		// δʵ��
	//Test_fun(%=);		// δʵ��
	Test_fun(&&);
	Test_fun(||);

	// һԪ���������




	return 0;
}