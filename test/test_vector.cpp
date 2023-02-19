#include <time.h>
#include <iostream>
#include "vector.hpp"
#include <vector>
#include <fstream>
#include <time.h>

static void printvector(ft::vector<std::string>& v, std::ofstream& ftFile) {
	for (size_t i = 0; i < v.size(); i++) {
		ftFile << v[i] << " ";
	}
	ftFile << std::endl;
}

static void ft_test(std::ofstream& ftFile) {
	clock_t g_start = clock();

	ft::vector<std::string> v1;
	v1.push_back("the");
	v1.push_back("frogurt");
	v1.push_back("is");
	v1.push_back("also");
	v1.push_back("cursed");

	ftFile << "v1: ";
	printvector(v1, ftFile);

	ft::vector<std::string> v2(v1.begin(), v1.end());
	ftFile << "v2: ";
	printvector(v2, ftFile);

	ft::vector<std::string> v3(v2);
	ftFile << "v3: ";
	printvector(v3, ftFile);


	ftFile << "v3[1]: " << v3.at(1) << std::endl;
	ftFile << "v3[2]: " << v3[2] << std::endl;
	ftFile << "v3 front: " << v3.front() << std::endl;
	ftFile << "v3 back: " << v3.back() << std::endl;

	ft::vector<std::string>::iterator it = v3.begin();
	for (; it < v3.end(); it++) {
		ftFile << "it: " << *it << " ";
	}
	ftFile << std::endl;

	ft::vector<std::string>::reverse_iterator rvrIt = v3.rbegin();

	for (; rvrIt < v3.rend(); rvrIt++) {
		ftFile << "rvrIt: " << *rvrIt << " ";
	}
	ftFile << std::endl;

	ftFile << "v3 empty: " << (v3.empty() ? "true" : "false") << std::endl;
	ftFile << "v3 size: " << v3.size() << std::endl;
	ftFile << "v3 max_size: " << v3.max_size() << std::endl;
	int i = -1;
	while (++i < 10)
	{
		v1.push_back("1");
		ftFile << "v3 capacity: " << v1.capacity() << std::endl;
		ftFile << "v3 size: " << v1.size() << std::endl;
	}


	ftFile << "v3 clear\n";
	v3.clear();
	ftFile << "v3 size: " << v3.size() << std::endl;
	ftFile << "v3 insert (from v2)\n";
	v3.insert(v3.begin(), v2.begin(), v2.end());
	ftFile << "v3 size: " << v3.size() << std::endl;
	ftFile << "v3: ";
	printvector(v3, ftFile);

	ftFile << "erase first\n";
	v3.erase(v3.begin() + 1);
	ftFile << "v3: ";
	printvector(v3, ftFile);

	v3.push_back("foo");
	v3.push_back("bar");
	v3.push_back("kek");
	ftFile << "v3: ";
	printvector(v3, ftFile);

	v3.pop_back();
	ftFile << "v3: ";
	printvector(v3, ftFile);

	v3.resize(4);
	ftFile << "v3: ";
	printvector(v3, ftFile);

	v3.assign(2, "newWord");
	ftFile << "v3: ";
	printvector(v3, ftFile);

	v3.swap(v2);
	ftFile << "v3: ";
	printvector(v3, ftFile);

	ftFile << "v3 == v2: " << (v3 == v2 ? "true" : "false") << std::endl;
	ftFile << "v3 < v2: " << (v3 < v2 ? "true" : "false") << std::endl;
	ftFile << "v3 >= v2: " << (v3 >= v2 ? "true" : "false") << std::endl;

	ft::vector<int> v4;
	for (int i = 0; i < 300000; i++) {
		v4.push_back(i);
	}

	clock_t g_end = clock();
	ftFile << "ft_vector_Execution time (ms): " << (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
}

static void printVector(const std::vector<std::string>& v, std::ofstream& stlFile) {
	for (size_t i = 0; i < v.size(); i++) {
		stlFile << v[i] << " ";
	}
	stlFile << std::endl;
}

static void stl_test(std::ofstream& stlFile) {
	clock_t g_start = clock();

	std::vector<std::string> v1;
	v1.push_back("the");
	v1.push_back("frogurt");
	v1.push_back("is");
	v1.push_back("also");
	v1.push_back("cursed");


	stlFile << "v1: ";
	printVector(v1, stlFile);

	std::vector<std::string> v2(v1.begin(), v1.end());
	stlFile << "v2: ";
	printVector(v2, stlFile);

	std::vector<std::string> v3(v2);
	stlFile << "v3: ";
	printVector(v3, stlFile);

	stlFile << "v3[1]: " << v3.at(1) << std::endl;
	stlFile << "v3[2]: " << v3[2] << std::endl;
	stlFile << "v3 front: " << v3.front() << std::endl;
	stlFile << "v3 back: " << v3.back() << std::endl;

	std::vector<std::string>::iterator it = v3.begin();
	for (; it < v3.end(); it++) {
		stlFile << "it: " << *it << " ";
	}
	stlFile << std::endl;

	std::vector<std::string>::reverse_iterator rvrIt = v3.rbegin();
	for (; rvrIt < v3.rend(); rvrIt++) {
		stlFile << "rvrIt: " << *rvrIt << " ";
	}
	stlFile << std::endl;

	stlFile << "v3 empty: " << (v3.empty() ? "true" : "false") << std::endl;
	stlFile << "v3 size: " << v3.size() << std::endl;
	stlFile << "v3 max_size: " << v3.max_size() << std::endl;
	int i = -1;
	while (++i < 10)
	{
		v1.push_back("1");
		stlFile << "v3 capacity: " << v1.capacity() << std::endl;
		stlFile << "v3 size: " << v1.size() << std::endl;
	}

	stlFile << "v3 clear\n";
	v3.clear();
	stlFile << "v3 size: " << v3.size() << std::endl;
	stlFile << "v3 insert (from v2)\n";
	v3.insert(v3.begin(), v2.begin(), v2.end());
	stlFile << "v3 size: " << v3.size() << std::endl;
	stlFile << "v3: ";
	printVector(v3, stlFile);

	stlFile << "erase first\n";
	v3.erase(v3.begin() + 1);
	stlFile << "v3: ";
	printVector(v3, stlFile);

	v3.push_back("foo");
	v3.push_back("bar");
	v3.push_back("kek");
	stlFile << "v3: ";
	printVector(v3, stlFile);

	v3.pop_back();
	stlFile << "v3: ";
	printVector(v3, stlFile);

	v3.resize(4);
	stlFile << "v3: ";
	printVector(v3, stlFile);

	v3.assign(2, "newWord");
	stlFile << "v3: ";
	printVector(v3, stlFile);

	v3.swap(v2);
	stlFile << "v3: ";
	printVector(v3, stlFile);

	stlFile << "v3 == v2: " << (v3 == v2 ? "true" : "false") << std::endl;
	stlFile << "v3 < v2: " << (v3 < v2 ? "true" : "false") << std::endl;
	stlFile << "v3 >= v2: " << (v3 >= v2 ? "true" : "false") << std::endl;

	std::vector<int> v4;
	for (int i = 0; i < 300000; i++) {
		v4.push_back(i);
	}

	clock_t g_end = clock();
	stlFile << "stl_vector_Execution time (ms): " << (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
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

    ftFile << "\n***** VECTOR TEST *****\n" << std::endl;
	ft_test(ftFile);
	ftFile.close();

    stlFile << "\n***** VECTOR TEST *****\n" << std::endl;
	stl_test(stlFile);
	stlFile.close();

	system("diff ftFile.txt stlFile.txt");
}