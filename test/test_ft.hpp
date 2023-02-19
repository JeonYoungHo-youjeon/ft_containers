#include <time.h>

#include <iostream>
#include "../vector.hpp"
#include "../stack.hpp"
#include "../map.hpp"
// #include "set.hpp"
#include <fstream>

/*
 **=========================================================================
 **		 vector Test
 **=========================================================================
 */

static void printvector(ft::vector<std::string>& v, std::ofstream& ftFile) {
	for (size_t i = 0; i < v.size(); i++) {
		ftFile << v[i] << " ";
	}
	ftFile << std::endl;
}

static void ft_vector_test(std::ofstream& ftFile) {
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

/*
 **=========================================================================
 **		 stack Test
 **=========================================================================
 */

static void ft_stack_test(std::ofstream& ftFile) {
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

/*
 **=========================================================================
 **		 map Test
 **=========================================================================
 */

static void printmap(ft::map<std::string, int>& m, std::ofstream& ftFile) {
	ftFile << '{';
	ft::map<std::string, int>::const_iterator b = m.begin();
	ft::map<std::string, int>::const_iterator e = m.end();
	while (b != e) {
		ftFile << b->first << ':' << b->second << ' ';
		b++;
	}
	ftFile << "}\n";
}

static void ft_map_test(std::ofstream& ftFile) {
	clock_t g_start = clock();

	ft::map<std::string, int> mp1;
	mp1["something"] = 21;
	mp1["anything"] = 42;
	mp1["that thing"] = 121;
	mp1["whatever"] = 555;
	ftFile << "mp1: ";
	printmap(mp1, ftFile);

	ft::map<std::string, int> mp2(mp1.find("anything"), mp1.end());
	ftFile << "mp2: ";
	printmap(mp2, ftFile);

	ft::map<std::string, int> mp3(mp1);
	ftFile << "mp3: ";
	printmap(mp3, ftFile);

	ftFile << "mp3[anything] with []: " << mp3["anything"] << std::endl;
	ftFile << "mp3[non_existing] with []: " << mp3["non_existing"]
						<< std::endl;
	printmap(mp3, ftFile);

	ft::map<std::string, int>::reverse_iterator rvrIt = mp3.rbegin();
	ftFile << '{';
	for (; rvrIt != mp3.rend(); rvrIt++) {
		ftFile << rvrIt->first << ':' << rvrIt->second << ' ';
	}
	ftFile << "}\n";

	ftFile << "mp3 empty: " << (mp3.empty() ? "true" : "false") << std::endl;
	ftFile << "mp3 size: " << mp3.size() << std::endl;

	ftFile << "mp3 clear\n";
	mp3.clear();
	ftFile << "mp3 size: " << mp3.size() << std::endl;
	ftFile << "mp3 insert (from mp2)\n";
	mp3.insert(mp2.begin(), mp2.end());
	ftFile << "mp3 size: " << mp3.size() << std::endl;
	ftFile << "mp3: ";
	printmap(mp3, ftFile);

	ftFile << "erase 'that_thing'\n";
	mp3.erase(mp3.find("that thing"));
	ftFile << "erase 'non_existing'\n";
	mp3.erase("non_existing");
	ftFile << "mp3: ";
	printmap(mp3, ftFile);

	mp3.swap(mp2);
	ftFile << "mp3: ";
	printmap(mp3, ftFile);

	ftFile << "mp3 == mp2: " << (mp3 == mp2 ? "true" : "false") << std::endl;
	ftFile << "mp3 < mp2: " << (mp3 < mp2 ? "true" : "false") << std::endl;
	ftFile << "mp3 >= mp2: " << (mp3 >= mp2 ? "true" : "false") << std::endl;

	ft::map<int, int> mp4;
	for (int i = 0, j = 100; i < 300000; i++, j++) {
		mp4.insert(ft::make_pair(i * 2, j));
	}
	ftFile << "count 41: " << mp4.count(41) << std::endl;
	ftFile << "count 50: " << mp4.count(50) << std::endl;
	ftFile << "count 300005: " << mp4.count(300005) << std::endl;
	ftFile << "find 26: " << mp4.find(26)->first << std::endl;
	ftFile << "lower bound 127: " << mp4.lower_bound(127)->first << std::endl;
	ftFile << "upper bound 244: " << mp4.upper_bound(244)->first << std::endl;

	clock_t g_end = clock();
	ftFile << "ft_map_Execution time (ms): " << (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
}

// /*
//  **=========================================================================
//  **		 set Test
//  **=========================================================================
//  */

// static void printSet(const ft::set<std::string>& s, std::ofstream& stlFile) {
// 	stlFile << '{';
// 	ft::set<std::string>::const_iterator b = s.begin();
// 	ft::set<std::string>::const_iterator e = s.end();
// 	while (b != e) {
// 		stlFile << *b << ' ';
// 		b++;
// 	}
// 	stlFile << "}\n";
// }

// static void ft_set_test(std::ofstream& stlFile) {
// 	clock_t g_start = clock();

// 	ft::set<std::string> st1;
// 	st1.insert("something");
// 	st1.insert("anything");
// 	st1.insert("that thing");
// 	st1.insert("whatever");
// 	stlFile << "st1: ";
// 	printSet(st1, stlFile);

// 	ft::set<std::string> st2(st1.find("anything"), st1.end());
// 	stlFile << "st2: ";
// 	printSet(st2, stlFile);

// 	ft::set<std::string> st3(st1);
// 	stlFile << "st3: ";
// 	printSet(st3, stlFile);

// 	ft::set<std::string>::reverse_iterator rvrIt = st3.rbegin();
// 	stlFile << '{';
// 	for (; rvrIt != st3.rend(); rvrIt++) {
// 		stlFile << *rvrIt << ' ';
// 	}
// 	stlFile << "}\n";

// 	stlFile << "st3 empty: " << (st3.empty() ? "true" : "false") << std::endl;
// 	stlFile << "st3 size: " << st3.size() << std::endl;

// 	stlFile << "st3 clear\n";
// 	st3.clear();
// 	stlFile << "st3 size: " << st3.size() << std::endl;
// 	stlFile << "st3 insert (from st2)\n";
// 	st3.insert(st2.begin(), st2.end());
// 	stlFile << "st3 size: " << st3.size() << std::endl;
// 	stlFile << "st3: ";
// 	printSet(st3, stlFile);

// 	stlFile << "erase 'that_thing'\n";
// 	st3.erase(st3.find("that thing"));
// 	stlFile << "erase 'non_existing'\n";
// 	st3.erase("non_existing");
// 	stlFile << "st3: ";
// 	printSet(st3, stlFile);

// 	st3.swap(st2);
// 	stlFile << "st3: ";
// 	printSet(st3, stlFile);

// 	stlFile << "st3 == st2: " << (st3 == st2 ? "true" : "false") << std::endl;
// 	stlFile << "st3 < st2: " << (st3 < st2 ? "true" : "false") << std::endl;
// 	stlFile << "st3 >= st2: " << (st3 >= st2 ? "true" : "false") << std::endl;

// 	ft::set<int> st4;
// 	for (int i = 0, j = 100; i < 300000; i++, j++) {
// 		st4.insert(i * 2);
// 	}
// 	stlFile << "count 41: " << st4.count(41) << std::endl;
// 	stlFile << "count 50: " << st4.count(50) << std::endl;
// 	stlFile << "count 300005: " << st4.count(300005) << std::endl;
// 	stlFile << "find 26: " << *st4.find(26) << std::endl;
// 	stlFile << "lower bound 127: " << *st4.lower_bound(127) << std::endl;
// 	stlFile << "upper bound 244: " << *st4.upper_bound(244) << std::endl;

// 	clock_t g_end = clock();
// 	stlFile << "stl_Execution time (ms): " << (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
// }


/*
 **=========================================================================
 **		 Launch Tests
 **=========================================================================
 */

int test_ft() {
	std::ofstream ftFile("./ftFile.txt");
	if (ftFile.fail())
	{
		std::cerr << "Error!" << std::endl;
	}

	ftFile << "----- TEST FT -----" << std::endl;
	ftFile << "\n***** VECTOR TEST *****\n" << std::endl;
	ft_vector_test(ftFile);
	ftFile << std::endl;

	ftFile << "\n***** STACK TEST *****\n" << std::endl;
	ft_stack_test(ftFile);
	ftFile << std::endl;

	ftFile << "\n***** MAP TEST *****\n" << std::endl;
	ft_map_test(ftFile);
	ftFile << std::endl;

	// ftFile << "\n***** SET TEST *****\n" << std::endl;
	// ft_set_test(ftFile);
	// ftFile << std::endl;

	ftFile.close();
	return 0;
}
