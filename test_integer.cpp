#include <iomanip>
#include <random>
#include <ctime>
#include "Integer.h"
#include "iocolor.h"
using std::default_random_engine;				// ���������
using std::uniform_int_distribution;			// ������ֲ�����

#define TEST_STYLE 0
constexpr int TEST_NUM = 100;					// ��������������
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
		if (i&&!(i%5)) cout << endl;						\
		cout << std::setw(20) << std::right << temp;		\
	}														\
	cout << endl;											\
} while (false);


/**
 * ������Ӧ�Ķ�Ԫ���������
 * ���жϼ����Ƿ���ȷ
 * ������Ӧ�����ݼ�¼
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
			/*ע�⣡�������Ǹ�ֵ����������޸Ĳ������ݣ�*/	\
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
			tvec.at(i) = ti;								\
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
 * ��Ԫ���������
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
	Test_fun(/);
	Test_fun(%);
	Test_fun(+=);
	Test_fun(-=);
	Test_fun(*=);
	Test_fun(/=);
	Test_fun(%=);
	Test_fun(&&);
	Test_fun(||);

	// һԪ������������ˣ��϶�Ҳûɶ���⡣����

	Integer i0 = 123456;
	cout << 3 + i0 << endl;
	cout << 6 - i0 << endl;
	cout << 13 % Integer(5) << endl;
	cout << (i0 == 3) << endl;

	system("pause");

	return 0;
}