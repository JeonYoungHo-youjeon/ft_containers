#include <iostream>
#include "test_stl.hpp"
#include "test_ft.hpp"

int main()
{
	test_stl();

	test_ft();

	system("diff ftFile.txt stlFile.txt");
	
	return (0);
}
