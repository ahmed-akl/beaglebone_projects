/**
 * @file button.h
 * @author Ahmed AKL
 * @date 12 Aug 2022
 * @brief Header file for the Button class
**/
#include <iostream>
#include <string.h>
#include "pin.h"

using namespace std;

class Button:public Pin{

	int m_error;	///< The error returned (if any) while reading the button status
public:
	Button(const int &pin_num);
	PinDigitalValue ReadButtonStatus(const int pin_num);
	int GetError(void);
};
