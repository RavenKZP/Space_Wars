#include <stdio.h>
#include <iostream>

#include "Algorithms.h"

#define MANUAL_TESTING

Return_Type Test_Alg_1 (Input_type Input, Output_type* Output)
{
		
	Output_type Output_local;

	for (int i = 0; i < Input.No_Ships_IN; i++)
	{
		std::string OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "ROTATE " +  std::to_string(Input.ID_IN[i]) + " R";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]+1) + " " + std::to_string(Input.Y_IN[i]) + " 1" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]+1) + " 1" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]-1) + " " + std::to_string(Input.Y_IN[i]) + " 1" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
		OUT = "BUILD " + std::to_string(Input.X_IN[i]) + " " + std::to_string(Input.Y_IN[i]-1) + " 1" + " 1";
		Output_local.Commands_OUT.push_back(OUT);
	}

	Output_local.Commands_OUT.push_back("END");

#ifndef MANUAL_TESTING
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

	*Output = Output_local;
	return E_OK;
}
