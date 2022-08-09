/*
 * This code is just a quick test for PWM capabilities of the beaglebone Black board
 * It assumes that:
 * - PWM feature is enabled and pwmchip2 is active
 * - pin8_13 is used for testing I
 */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

void SetDutyCycle(const int val)
{
	FILE *IO_val = NULL;
	char str[100];

	sprintf(str, "/sys/class/pwm/pwm-2:1/duty_cycle");
	IO_val = fopen (str, "w");
	if(IO_val == NULL)
	{
		printf ("Error ===> Cannot open IO_val (Line: %d\n", __LINE__);
	   	perror("Failed: ");
	}
	else
	{
		sprintf(str, "%d", val);
		fwrite (str, strlen(str), sizeof("1"), IO_val);
		fclose (IO_val);
	}
}

void SetPeriod(const int val)
{
	FILE *IO_val = NULL;
	char str[100];

	sprintf(str, "/sys/class/pwm/pwm-2:1/period");
	IO_val = fopen (str, "w");
	if(IO_val == NULL)
	{
		printf ("Error ===> Cannot open IO_val (Line %d\n", __LINE__);
		perror("Failed: ");
	}
	else
	{
		sprintf(str, "%d", val);
		fwrite (str, strlen(str), sizeof("0"), IO_val);
		fclose (IO_val);
	}
}

void SetRatio(const int ratio)
{
	const int period{100};
	int duty_cycle{0};

	duty_cycle=(ratio/100.0) * period;
	SetPeriod (period);
	cout << "ratio: " << ratio << "  Period: " << period << "  Duty Cycle: " << duty_cycle << endl;
	SetDutyCycle(duty_cycle);
}

int main()
{
   /* PWMChip2B - pin8_13
    * Note: Period must be greater than Duty Cycle
    */

   // increase brightness
   for(int ratio=0; ratio<100; ratio+=10)
   {
	   SetRatio(ratio);
	   usleep (500000);
   }

   // decrease brightness
   for(int ratio=100; ratio>0; ratio-=10)
      {
   	   SetRatio(ratio);
   	   usleep (500000);
      }
}
