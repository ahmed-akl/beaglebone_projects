/**
 * @file button.cpp
 * @author Ahmed AKL
 * @date 12 Aug 2022
 * @brief implementation of the button class
**/
#include "button.h"

/**
 * @brief This is the constructor of the Button class
 *
 * @note
 *
 * @param[in] pin_num	the pin number where the button is connected
 *
 * @return	None
**/
Button::Button(const int &pin_num):
				Pin::Pin(pin_num, PinDirection::IN)
{
}

/**
 * @brief This function reads the button status
 *
 * @note
 *
 * @param[in] pin_num	the pin number where the button is connected
 *
 * @return	The button status
**/
PinDigitalValue Button::ReadButtonStatus(const int pin_num)
{
	FILE *IO_val = nullptr;
	char str[50];
	char ch[3];
	size_t size;
	PinDigitalValue val{PinDigitalValue::ZERO};

	sprintf(str, "/sys/class/gpio/gpio%d/value", pin_num);
	IO_val = fopen (str, "r");
	if(IO_val == nullptr)
	{
		cout << "Error ===> Cannot open IO_val (Line " << __LINE__ << ")" << endl;
		m_error = errno;
		val = PinDigitalValue::ERROR;
		perror("Failed: ");
	}
		else
		{
			size = fread (ch, 1, sizeof(ch), IO_val);
			cout << "data: " <<  ch << endl;
			if ( ferror(IO_val) )
			{
				m_error = errno;
				val = PinDigitalValue::ERROR;
				perror( "Error reading myfile" );
			}
			else
			{
				if (ch[0]=='1')
				{
					val= PinDigitalValue::ONE;
				}
			}
			fclose (IO_val);
		}
		return (val);
}

/**
 * @brief This function gets the last error (if any) while reading the button status
 *
 * @note
 *
 * @param void
 *
 * @return	error number
**/
int Button::GetError(void)
{
	return(m_error);
}



