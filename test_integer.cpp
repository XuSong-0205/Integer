#include <iomanip>
#include "Integer.h"
#include "iocolor.h"

int main()
{
	{
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
	}

	system("color 0A");
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
	cout << sx::io::reset::reset_all;
	return 0;
}