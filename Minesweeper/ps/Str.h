#ifndef INCLUDED_STR
#define INCLUDED_STR

#include <string>
#include "types.h"

class Str: public std::string
{
public:
    //Constructors.
    Str() {}
	Str(const char* String) : std::string(String) {}
    Str(const std::string& String) : std::string(String) {}
    static Str FromInt(int n);
	static Str FromUInt(unsigned int n);
	static Str FromInt64(i64 n);
	static Str FromDouble(double n);

    /**
	 * Return CStr as Integer.
	 * Conversion is from the beginning of CStr.
	 *
	 * @return int CStr represented as an integer.
	 **/
	int ToInt() const;

	/**
	 * Return CStr as Unsigned Integer.
	 * Conversion is from the beginning of CStr.
	 *
	 * @return unsigned int CStr represented as an unsigned integer.
	 **/
	unsigned int ToUInt() const;

	/**
	 * Return CStr as Long.
	 * Conversion is from the beginning of CStr.
	 *
	 * @return long CStr represented as a long.
	 **/
	long ToLong() const;

	/**
	 * Return CStr as Unsigned Long.
	 * Conversion is from the beginning of CStr.
	 *
	 * @return unsigned long CStr represented as an unsigned long.
	 **/
	unsigned long ToULong() const;

	/**
	 * Return CStr as Float.
	 * Conversion is from the beginning of CStr.
	 *
	 * @return float CStr represented as a float.
	 **/
	float ToFloat() const;

	/**
	 * Return CStr as Double.
	 * Conversion is from the beginning of CStr.
	 *
	 * @return double CStr represented as a double.
	 **/
	double ToDouble() const;

};
#endif // INCLUDED_STR
