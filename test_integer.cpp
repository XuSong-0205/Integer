#include <iomanip>
#include "Integer.h"
#include "iocolor.h"

int main()
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


	cout << sx::io::bg::black << sx::io::fg::green;
	cout << "¼Ó·¨²âÊÔ : ";


	cout << sx::io::reset::reset_all;
	return 0;
}