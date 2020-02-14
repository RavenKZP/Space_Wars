#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "Algorithms.h"

//#define MANUAL_TESTING

void Test_Alg_1 (Input_type Input, Output_type &Output)
{
	srand(time(NULL));

		
	Output_type Output_local;
#ifndef MANUAL_TESTING
	for (int i = 0; i < Input.No_Ships_IN; i++)
	{
		std::string OUT;

		OUT = "SHOOT " + std::to_string(Input.ID_IN[i]);
		Output_local.Commands_OUT.push_back(OUT);
		

		OUT = "WORKSHOP " + std::to_string(Input.X_IN[i]+1) + " " + std::to_string(Input.Y_IN[i]);
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "WORKSHOP " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]+1);
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "WORKSHOP " + std::to_string(Input.X_IN[i]-1) + " " + std::to_string(Input.Y_IN[i]);
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "WORKSHOP " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]-1);
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "WORKSHOP " + std::to_string(Input.X_IN[i]+1) + " " + std::to_string(Input.Y_IN[i]);
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "WORKSHOP " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]+1);
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "WORKSHOP " + std::to_string(Input.X_IN[i]-1) + " " + std::to_string(Input.Y_IN[i]);
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "WORKSHOP " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]-1);
		Output_local.Commands_OUT.push_back(OUT);

		OUT = "BUILD " + std::to_string(Input.X_IN[i]+1) + " " + std::to_string(Input.Y_IN[i]) + " 1" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]+1) + " 2" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]-1) + " " + std::to_string(Input.Y_IN[i]) + " 1" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]-1) + " 2" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]+1) + " " + std::to_string(Input.Y_IN[i]) + " 1" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]+1) + " 2" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]-1) + " " + std::to_string(Input.Y_IN[i]) + " 1" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]-1) + " 2" + " 1";
		Output_local.Commands_OUT.push_back(OUT);

		if (Input.Type_IN[i] != 0)
		{
			OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
			Output_local.Commands_OUT.push_back(OUT);
		}

		if (rand()%2)
		{
			OUT = "ROTATE " +  std::to_string(Input.ID_IN[i]) + " L";
			Output_local.Commands_OUT.push_back(OUT);
		}
		else
		{
			OUT = "ROTATE " +  std::to_string(Input.ID_IN[i]) + " R";
			Output_local.Commands_OUT.push_back(OUT);
		}
	}

	Output_local.Commands_OUT.push_back("END");

#else
	char command[100];
	std::cout << "Enter commands" << std::endl;
	std::string end;
	while (end != "END")
	{
		std::cin.getline(command, sizeof(command));
		Output_local.Commands_OUT.push_back(command);
		end = command;
	}
#endif

	Output = Output_local;
}


void Test_Alg_2 (Input_type Input, Output_type &Output)
{
	usleep(200);
}


