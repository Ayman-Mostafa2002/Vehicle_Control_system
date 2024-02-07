/*
 ============================================================================
 Name        : Vehicle_Control_system.c
 Author      : Ayman Mostafa
 Version     : 1.0.1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//System with engine temp controller or not
#define WITH_ENGINE_TEMP_CONTROLLER 1
enum state
{TURN_OFF,TURN_ON};
//Do the requirements when the engine is on
void vehicle_engine_is_on(char*);
//Display Sensors set menu
void display_Sensors_set_menu();
//Set the speed based on traffic light data
void traffic_light_set();
//Set the room temperature Based on room temperature data
void room_temperature_set();
//Set the engine temperature Based on engine temperature data
void engine_temperature_set();
//Do the requirements when the speed is 30 Km/Hr
void check_speed_30();
//Print all the data
void print_current_state();

struct data
{
	char vehicle_engine_state;
	float vehicle_speed;
	float room_temperature;
	char AC_state;
	float engine_temperature;
	char engine_temperature_controller_state;
};
//initial values for data
struct data data1={TURN_OFF,0,20,TURN_OFF,110,TURN_OFF};

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char user_selection=0;
	//main menu
	while(1)
	{
		printf("Enter the operation number\n");
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n\n");
		scanf(" %c",&user_selection);
		// do some process based on user selection
		switch(user_selection)
		{
		case'a':
			data1.vehicle_engine_state=TURN_ON;
			printf("Turn on the vehicle engine.\n\n");
			vehicle_engine_is_on(&user_selection);
			break;
		case'b':
			data1.vehicle_engine_state=TURN_OFF;
			printf("Turn off the vehicle engine\n\n");
			break;
		case'c':
			printf("Quit the system\n\n");
			exit(0);
		default:
			printf("You entered an incorrect number, please try again\n");
			break;
		}
	}
	return 0;
}

//Do the requirements when the engine is on
void vehicle_engine_is_on(char*selection)
{
	while(1)
	{
		display_Sensors_set_menu();
		scanf(" %c",selection);
		switch(*selection)
		{
		case 'a':
			return;
		case 'b':
			traffic_light_set();
			check_speed_30();
			print_current_state();
			break;
		case 'c':
			room_temperature_set();
			print_current_state();
			break;
        #if (WITH_ENGINE_TEMP_CONTROLLER)
		case 'd':
			engine_temperature_set();
			print_current_state();
			break;
        #endif
		default:
			printf("You entered an incorrect number, please try again\n");
			break;
		}
	}
	return;
}

//Display Sensors set menu
void display_Sensors_set_menu()
{
	printf("a. Turn off the engine.\n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature (Temperature Sensor).\n");
#if (WITH_ENGINE_TEMP_CONTROLLER)
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n\n");
#endif

	return;
}

//Set the speed based on traffic light data
void traffic_light_set()
{
	char Required_Colour=0;
	printf("Enter the required colour\n");
	scanf(" %c",&Required_Colour);
	switch(Required_Colour)
	{
	case'G':
		data1.vehicle_speed=100;
		break;
	case'O':
		data1.vehicle_speed=30;
		break;
	case'R':
		data1.vehicle_speed=0;
		break;
	}
	return;
}

//Set the room temperature Based on room temperature data
void room_temperature_set()
{
	printf("Enter the room temperature \n");
	scanf(" %f",&data1.room_temperature);
	if(data1.room_temperature<10 || data1.room_temperature>30)
	{
		data1.room_temperature=20;
		data1.AC_state=TURN_ON;
	}
	else
	{
		data1.AC_state=TURN_OFF;
	}
	return;
}

//Set the engine temperature Based on engine temperature data
void engine_temperature_set()
{
	printf("Enter the engine temperature \n");
	scanf(" %f",&data1.engine_temperature);
	if(data1.engine_temperature<100 || data1.engine_temperature>150)
	{
		data1.engine_temperature=125;
		data1.engine_temperature_controller_state=TURN_ON;
	}
	else
	{
		data1.engine_temperature_controller_state=TURN_OFF;
	}
	return;
}

//Do the requirements when the speed is 30 Km/Hr
void check_speed_30()
{
	if(data1.vehicle_speed==30)
	{
		if(!data1.AC_state)
		{
			data1.AC_state=TURN_ON;
		}
		data1.room_temperature*=(float)5/4 ;
		data1.room_temperature++;
        #if (WITH_ENGINE_TEMP_CONTROLLER)
		if(!data1.engine_temperature_controller_state)
		{
			data1.engine_temperature_controller_state=TURN_ON;
		}
		data1.engine_temperature*=(float)5/4;
		data1.engine_temperature++;
        #endif
	}
	return;
}

//Print all the data
void print_current_state()
{
	if(data1.vehicle_engine_state)
		printf("Engine is ON\n");
	else
		printf("Engine is OFF\n");

	if(data1.AC_state)
		printf("AC is ON\n");
	else
		printf("AC is OFF\n");

	printf("Vehicle Speed: %f Km/Hr\n",data1.vehicle_speed);

	printf("Room Temperature: %f\n",data1.room_temperature);

    #if (WITH_ENGINE_TEMP_CONTROLLER)
	if(data1.engine_temperature_controller_state)
		printf("Engine Temp Controller is ON\n");
	else
		printf("Engine Temp Controller is OFF\n");

	printf("Engine Temperature: %f\n\n",data1.engine_temperature);
    #endif
	return;
}


