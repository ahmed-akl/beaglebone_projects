/**
 * @file	switch_thread.cpp
 * @author	Ahmed AKL
 * @date 12 Aug 2022
 * @version 1.0.0
 * @brief	This is an example of Reading a switch using a thread
 * @note	Before you run the code you need to export gpio13
 * 			echo 31  export
**/
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "button.h"

using namespace std;

pthread_mutex_t h_mutex;
const int pin31{31};

struct PinData {
	int pin_num;
	int status;
};

/**
 * @brief This function is the thread that handles the push button
 *
 * @note
 *
 * @param[in,out] pin_data
 *
 * @return	void* the type of passed parameter
**/
void *ThreadHandleSwitch(void *pin_data)
{
	bool error{false};
	Button B(pin31);
	PinDigitalValue temp;
	PinData *data = (PinData*)pin_data;

	data->pin_num = pin31;

	while (!error )
	{
		usleep(1000);
		temp = B.ReadButtonStatus(pin31);
		if(B.GetError() != 0)
		{
			error = true;
		}

		pthread_mutex_lock(&h_mutex);
		data->status= (int)temp;
		pthread_mutex_unlock(&h_mutex);

		switch(temp)
		{
		case PinDigitalValue::ZERO:
			cout << "Switch Unpressed" << endl;
			break;

		case PinDigitalValue::ONE:
			cout << "Switch Pressed" << endl;
			break;

		case PinDigitalValue::ERROR:
		default:
			cout << "\n\nCheck if gpio13 was exported\n  i.e. echo 31  export\n\n";
			error = true;
		}
	}
	return (pin_data);
}

/**
 * @brief This function is the main function (i.e. main thread)
 *
 * @note
 *
 * @param void
 *
 * @return	0 if success
**/
int main()
{
	// the main thread
	int x=0, y=0;
	bool pin_state{false};
	int pin_switch{31};
	PinData data{pin_switch, 0};

	pthread_t thread; ///< This is the thread handle

	// create thread, pass reference, address of the function and data
	if(pthread_create(&thread, nullptr, &ThreadHandleSwitch, &data))
	{
		cout << "Failed to create the thread" << endl;
		return 1;
	}

	void* result; // receive data back from pthread (if any)
	pthread_join(thread, &result); // allow the pthread to complete
	PinData *z = (PinData *) result; // cast from void* to PinData* to get z
	cout << "Final: " << z->status << endl;
	return 0;
}
