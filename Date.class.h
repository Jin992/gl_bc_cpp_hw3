#ifndef DATE_CLASS_H
#define DATE_CLASS_H
#include <string>
#include <vector>

class Date {
	public:
		Date();
		explicit Date(const std::string &);

		void setDate(const std::string &);
		std::string getDate(const std::string & format);
	
		long long operator-(const Date &);

	private:
		long long _date;
		void _encode_date(const std::vector<int> &);
		std::vector<int> 	_decode_date(void);
		void _extract_date(const std::vector<int> &, const std::string &);
		std::string assamble_date(std::string date_str, char delim);
};

std::istream & operator>>(std::istream &, Date &);
std::ostream & operator<<(std::ostream &, Date &);

#endif
