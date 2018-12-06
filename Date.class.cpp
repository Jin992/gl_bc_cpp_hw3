#include "Date.class.h"
#include <iostream>
#include <numeric>
#include <algorithm>

/*-----Static functions for class internal use-----*/

/* searching of delimiter in format string */
static char getDelim(const std::string & date) {
	char c;

	for (auto it : date) {
		if (!isdigit(it)) {
			return c = it;	
		}				
	}
	return 0;
}

/* validation of delimiter between date partsv*/
static int delimiter_validator(const std::string & date) {
	char		delim;
	unsigned short	delim_cnt;

	delim_cnt = 0;
	if ((delim = getDelim(date)) == '\0') {
		return 1;
	}
	if (isalpha(delim)) {
		return 1;
	}
	for (auto it : date)
	{	if (!isdigit(it)) {
			if (delim != it) {
				return 1;
			}
			delim_cnt++;
		}
	}
	if (delim_cnt != 2) {
		return 1;
	}
	return 0;
}

/* validation of format string */
static int format_validator( std::vector<int> &format, const std::string &date) {
	constexpr unsigned short dayLen = 2;
	constexpr unsigned short monthLen = 2;
	constexpr unsigned short yearLen = 4;
	int i = 0;
	
	format = std::vector<int>(3, 0);
	for (auto it : date) {
		
		if (isdigit(it)) {
			format[i]++;
		}
		else {	
			i++;
		}	
	}
	if (std::accumulate(format.begin(), format.end(), 0) != 8) {
	       return 1;
	}
	if ((format[0] != dayLen && format[0] != yearLen) || format[1] != monthLen ||
		(format[2] != dayLen && format[2] != yearLen)) {
		return 1;
	}
	return 0;
}

/* convert the date into days */
static long long day_from_civil(int y, int m, int d) noexcept {
	y -= m <= 2;
	const int era = (y >= 0? y : y - 399) / 400;
	const unsigned yoe = static_cast<unsigned>(y - era * 400);
	const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d -1;
	const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
	return era * 146097 + static_cast<long long>(doe) - 719468;
}

/* convert days into date */
static std::vector<int> civil_from_date(long long z) {
	z += 719468;
	const int era = (z >= 0 ? z : z - 146096) / 146097;
	const unsigned doe = static_cast<unsigned>(z -era * 146097);
	const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
	const int y = static_cast<int>(yoe) + era * 400;
	const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
	const unsigned mp = ( 5 * doy + 2) / 153;
	const unsigned d = doy - (153 * mp + 2) / 5 + 1;
	const unsigned m = mp + ( mp < 10 ? 3 : -9);
	return std::vector<int> {static_cast<int>(d), static_cast<int>(m), y + (m <= 2)};
}
/*-----Static functions for class internal use-----*/


Date::Date():_date(0)
{}

Date::Date(const std::string & date):_date(0) {
	setDate(date);
}

/* return difference in days between two dates */
long long Date::operator-(const Date & other) {
	return _date - other._date;
}

/* encode date from vector to long long value */
void Date::_encode_date(const std::vector<int> & date) {
	_date = day_from_civil(date[2], date[1], date[0]);
}

/* decode from long long value to vector */
std::vector<int> Date::_decode_date(void){
	return civil_from_date(_date);
}

/* extract date value from string */
void Date::_extract_date(const std::vector<int> & format, const std::string & date) {
	int				i = 0;
	std::string::const_iterator	checkpoint = date.begin();
	std::vector<int>		date_vector(3,0);

	for (auto &elem : date_vector) {
		elem = std::stoi(std::string(checkpoint, checkpoint + format[i]));
		checkpoint = std::next(checkpoint + format[i]);
		i++;			
	}
	if (format[0] == 4) {
		std::reverse(date_vector.begin(), date_vector.end());
	}
	if (date_vector[0] < 1 || date_vector[0] > 31){
		throw std::invalid_argument("Error: bad date.");
	}
	if (date_vector[1] < 1 || date_vector[1] > 12) {
		throw std::invalid_argument("Error: date month.");
	}
	_encode_date(date_vector);
}

void Date::setDate(const std::string &date){	
	std::vector<int> format;
	
	if (date.length() != 10) {
		throw std::invalid_argument("Error: date string is too long.");
	}
	/* check delimiter (quantity, type) */
	if (delimiter_validator(date)) {
		throw std::invalid_argument("Error: bad delimiter.");
	}
	if (format_validator(format, date)) {
		throw std::invalid_argument("Error: bad format.");
	}
	/* extract day, month, year from string, and store it to attributes of class */
	_extract_date(format, date);
}

/* compose date from vector to string */
std::string Date::assamble_date(std::string date_str, char delim) {
	int year_position =  date_str.find("YYYY");
	std::vector<int> date_vector = _decode_date();
	
	if (year_position == 0) {
		std::reverse(date_vector.begin(), date_vector.end());	
	}
	std::string res;
	for (auto elem = date_vector.begin(); elem != date_vector.end(); ++elem) {
		res += std::to_string(*elem);
		if (std::next(elem) != date_vector.end()) {
			res += delim;
		}
	}
	return res;
}

std::string Date::getDate(const std::string & format) {
	if (format.length() != 10) {
		throw std::invalid_argument("Error: format string is too long.");	}
	if (format.find("DD") == std::string::npos ||
	    format.find("MM") == std::string::npos ||
	    format.find("YYYY") == std::string::npos) {
		throw std::invalid_argument("Error: bad format.");
	}
	
	char delim = *(std::next(format.begin() + format.find("MM") + 1, 1)); 
	if ((delim != *(std::prev(format.begin() + format.find("MM"), 1))) || 
		isalpha(delim) || isdigit(delim))  {
		throw std::invalid_argument("Error: bad delimiter.");
	}
	return assamble_date(format, delim);
}

std::istream & operator>>(std::istream & is, Date & date) {
	std::string tmp;

	is >> tmp;
	date.setDate(tmp);
	return is;
}

std::ostream & operator<<(std::ostream & os, Date & date) {
	os << date.getDate("DD-MM-YYYY");
	return os;
}