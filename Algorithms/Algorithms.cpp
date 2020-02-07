#include <stdio.h>
#include <iostream>

#include "Algorithms.h"

Return_Type Test_Alg_1 (Input_type Input, Output_type* Output)
{

	//Test
	/*
	std::cout << "TEST_Alg_1" << std::endl;
	std::cout << Input.MAP_SIZE_IN << std::endl;
	for (int y = 0; y < Input.MAP_SIZE_IN; y++)
	{
		for (int x = 0; x < Input.MAP_SIZE_IN; x++)
		{
			std::cout << Input.MAP_IN[y][x] << " ";
		}
	std::cout << std::endl;
	}
	std::cout << Input.No_Ships_IN << std::endl;
	for (int i = 0; i < Input.No_Ships_IN; i++)
	{
		std::cout << Input.ID_IN[i] << std::endl;
		std::cout << Input.Type_IN[i] << std::endl;
		std::cout << Input.Rotation_IN[i] << std::endl;
		std::cout << Input.HP_IN[i] << std::endl;
		std::cout << Input.Storage_IN[i] << std::endl;
	}
	*/


	Output_type Output_local;

	Output_local.Commands_OUT.push_back("SHOOT 1");
	Output_local.Commands_OUT.push_back("SHOOT 2");
	Output_local.Commands_OUT.push_back("SHOOT 3");
	Output_local.Commands_OUT.push_back("BUILD 9 8 2 2");
	Output_local.Commands_OUT.push_back("BUILD 8 9 1 2");
	Output_local.Commands_OUT.push_back("MOVE 3");
//	Output_local.Commands_OUT.push_back("MOVE 2");
	Output_local.Commands_OUT.push_back("DIG 2");
	Output_local.Commands_OUT.push_back("ROTATE 2 L");
	Output_local.Commands_OUT.push_back("SHOOT 1");
	Output_local.Commands_OUT.push_back("END");

	*Output = Output_local;
	return E_OK;
}
