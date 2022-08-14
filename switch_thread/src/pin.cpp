/**
 * @file pin.cpp
 * @author Ahmed AKL
 * @date 12 Aug 2022
 * @brief Implementation file for the Pin class
**/
#include "pin.h"

/**
 * @brief This is the constructor of the Pin class
 *
 * @note
 *
 * @param[in] pin_num		The pin number where the button is connected
 * @param[in] direction		The pin direction; either IN or OUT
 *
 * @return	None
**/
Pin::Pin(const int &pin_num, const PinDirection direction)
{
	m_direction = direction;
	ConfigPin(pin_num);
}

/**
 * @brief This function configure the Pin to be either In or Out pin
 *
 * @note
 *
 * @param[in] pin_num		The pin number where the button is connected
 *
 * @return	None
**/
void Pin::ConfigPin(const int &pin_num)
{
	FILE *IO_direction = nullptr;
	char str[50];

	sprintf(str, "/sys/class/gpio/gpio%d/direction", pin_num);
	IO_direction = fopen (str, "w");
	if(IO_direction == nullptr)
	{
		cout << "Error ===> Cannot open IO_direction (Line "  << __LINE__ << endl;
		perror("Failed: ");
	}
	else
	{
		cout<<DirectionToString().c_str()<< "   length: " << DirectionToString().length() << endl;
		fwrite (DirectionToString().c_str(), 1, DirectionToString().length(), IO_direction);
		fclose (IO_direction);
	}
}

/**
 * @brief This function conevrts the direction type into string
 *
 * @note
 *
 * @param void
 *
 * @return	The direction type as a string
**/
string Pin::DirectionToString(void)
{
	string str;

	switch(m_direction)
	{
	case PinDirection::IN :
		str = "in";
		break;

	case PinDirection::OUT :
	default:
		str = "out";
	}

	return(str);
}

/**
 * @brief This function returns the pin's direction (i.e. IN or OUT)
 *
 * @note
 *
 * @param void
 *
 * @return	The pin's direction
**/
PinDirection Pin::GetDirection(void)
{
	return(m_direction);
}

