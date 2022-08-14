/**
 * @file pin.h
 * @author Ahmed AKL
 * @date 12 Aug 2022
 * @brief Header file for the Pin class
**/
#include <iostream>
#include <string.h>

using namespace std;

enum class PinDirection {OUT=0, IN=1};		///< Pin direction; either IN or OUT
enum class PinDigitalValue {ZERO=0, ONE=1, ERROR=-1};	///< The result of reading a digital pin

class Pin
{
	int m_pin_num{0};								///< Pin number
	PinDirection m_direction{PinDirection::OUT};	///< Pin direction

	void ConfigPin(const int &pin_num);

public:
	Pin(const int &pin_num, const PinDirection direction);
	string DirectionToString(void);
	PinDirection GetDirection(void);
};
