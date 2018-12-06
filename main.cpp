#include "Date.class.h"
#include <iostream>

int main() {
	Date date;
	Date date1("10-12-2012");
	Date date2;
	Date date3;
	Date date4;
	
	std::cout << "Enter the date to check >> operator ";
	std::cin >> date;
	std::cout << "date :"<<  date << std::endl;
	std::cout << "date << operator :"<<  date << std::endl;
	std::cout << "date.getDate() :"<<  date.getDate("DD-MM-YYYY") << std::endl;

	std::cout << "date1 construtor check :"<<  date1 << std::endl;
	date1.setDate("06/12/2018");
	std::cout << "date1 setDate() check :"<<  date1 << std::endl;

	date2.setDate("12/12/2012");
	date3.setDate("10-12-2012");
	std::cout << "date2 = " << date2 << "  date3 = " << date3 << std::endl;
	std::cout << "'-' operation check date2 - date3 = " << date2 - date3 << std::endl;
	std::cout << "'-' operation check date3 - date2 = " << date3 - date2 << std::endl;
	date3.setDate("12/12/2012");
	std::cout << "date2 = " << date2 << "  date3 = " << date3 << std::endl;
	std::cout << "'-' operation check date3 - date2 = " << date2 - date3 << std::endl;

	std::cout << "different input formate test :" << std::endl;
	date.setDate("2012/12/12");
	date3.setDate("10.12.2012");
	std::cout << "date format 2012/12/12 : " << date << std::endl;
	date.setDate("2012.12.12");
	std::cout << "date  format 2012.12.12 : " << date << std::endl;
	date.setDate("2012-12-12");
	std::cout << "date  format 2012-12-12 : " << date << std::endl;
}
