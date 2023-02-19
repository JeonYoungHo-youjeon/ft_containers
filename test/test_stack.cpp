#include <time.h>
#include <iostream>
#include "stack.hpp"
#include <stack>
#include <fstream>
#include <time.h>

static void stl_test(std::ofstream& stlFile) {
	clock_t g_start = clock();

	std::stack<int> st;
	for (int i = 0; i < 100000; i++) {
		st.push(i * 3);
	}
	stlFile << "Top element (st): " << st.top() << std::endl;
	stlFile << "stack size (st): " << (st.empty() ? "true" : "false")
						<< std::endl;

	std::stack<int> st2(st);
	stlFile << "Top element (st2): " << st2.top() << std::endl;
	stlFile << "stack size (st2): " << (st2.empty() ? "true" : "false")
						<< std::endl;
	stlFile << "stack empty (st2): " << (st2.empty() ? "true" : "false")
						<< std::endl;

	st2.push(99);
	st2.push(42);
	stlFile << "Top element (st2): " << st2.top() << std::endl;
	stlFile << "stack size (st2): " << (st2.empty() ? "true" : "false")
						<< std::endl;

	std::stack<int> st3 = st2;
	stlFile << "st2 == st3: " << (st2 == st3 ? "true" : "false") << std::endl;

	st3.pop();
	st3.pop();
	st3.pop();
	st3.pop();
	st3.pop();
	stlFile << "Top element (st3): " << st2.top() << std::endl;
	stlFile << "st2 == st3: " << (st2 == st3 ? "true" : "false") << std::endl;
	stlFile << "st2 != st3: " << (st2 != st3 ? "true" : "false") << std::endl;
	stlFile << "st2 < st3: " << (st2 < st3 ? "true" : "false") << std::endl;
	stlFile << "st2 >= st3: " << (st2 >= st3 ? "true" : "false") << std::endl;

	int count = 0;
	while (!st3.empty()) {
		count++;
		st3.pop();
	}
	stlFile << "Count of pop operations (st3): " << count << std::endl;
	stlFile << "stack empty (st3): " << (st3.empty() ? "true" : "false")
						<< std::endl;

	clock_t g_end = clock();
	stlFile << "stl_stack_Execution time (ms): " << (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
}

static void ft_test(std::ofstream& ftFile) {
	clock_t g_start = clock();
	ft::stack<int> st;
	for (int i = 0; i < 100000; i++) {
		st.push(i * 3);
	}
	ftFile << "Top element (st): " << st.top() << std::endl;
	ftFile << "stack size (st): " << (st.empty() ? "true" : "false")
						<< std::endl;

	ft::stack<int> st2(st);
	ftFile << "Top element (st2): " << st2.top() << std::endl;
	ftFile << "stack size (st2): " << (st2.empty() ? "true" : "false")
						<< std::endl;
	ftFile << "stack empty (st2): " << (st2.empty() ? "true" : "false")
						<< std::endl;

	st2.push(99);
	st2.push(42);
	ftFile << "Top element (st2): " << st2.top() << std::endl;
	ftFile << "stack size (st2): " << (st2.empty() ? "true" : "false")
						<< std::endl;

	ft::stack<int> st3 = st2;
	ftFile << "st2 == st3: " << (st2 == st3 ? "true" : "false") << std::endl;

	st3.pop();
	st3.pop();
	st3.pop();
	st3.pop();
	st3.pop();
	ftFile << "Top element (st3): " << st2.top() << std::endl;
	ftFile << "st2 == st3: " << (st2 == st3 ? "true" : "false") << std::endl;
	ftFile << "st2 != st3: " << (st2 != st3 ? "true" : "false") << std::endl;
	ftFile << "st2 < st3: " << (st2 < st3 ? "true" : "false") << std::endl;
	ftFile << "st2 >= st3: " << (st2 >= st3 ? "true" : "false") << std::endl;

	int count = 0;
	while (!st3.empty()) {
		count++;
		st3.pop();
	}
	ftFile << "Count of pop operations (st3): " << count << std::endl;
	ftFile << "stack empty (st3): " << (st3.empty() ? "true" : "false")
						<< std::endl;
	clock_t g_end = clock();
	ftFile << "ft_stack_Execution time (ms): " << (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
}


int main()
{
    std::ofstream stlFile("./stlFile.txt");
	if (stlFile.fail())
	{
		std::cerr << "Error!" << std::endl;
	}
    std::ofstream ftFile("./ftFile.txt");
	if (ftFile.fail())
	{
		std::cerr << "Error!" << std::endl;
	}

    ftFile << "\n***** STACK TEST *****\n" << std::endl;
	ft_test(ftFile);
	ftFile.close();

    stlFile << "\n***** STACK TEST *****\n" << std::endl;
	stl_test(stlFile);
	stlFile.close();

	system("diff ftFile.txt stlFile.txt");
}