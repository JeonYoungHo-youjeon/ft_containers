#include <time.h>

#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <fstream>

/*
 **=========================================================================
 **		 vector Test
 **=========================================================================
 */

static void printVector(const std::vector<std::string>& v, std::ofstream& stlFile) {
	for (size_t i = 0; i < v.size(); i++) {
		stlFile << v[i] << " ";
	}
	stlFile << std::endl;
}

static void vector_test(std::ofstream& stlFile) {
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

/*
 **=========================================================================
 **		 stack Test
 **=========================================================================
 */

static void stack_test(std::ofstream& stlFile) {
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

/*
 **=========================================================================
 **		 map Test
 **=========================================================================
 */

static void printMap(const std::map<std::string, int>& m, std::ofstream& stlFile) {
	stlFile << '{';
	std::map<std::string, int>::const_iterator b = m.begin();
	std::map<std::string, int>::const_iterator e = m.end();
	while (b != e) {
		stlFile << b->first << ':' << b->second << ' ';
		b++;
	}
	stlFile << "}\n";
}

static void map_test(std::ofstream& stlFile) {
	clock_t g_start = clock();

	std::map<std::string, int> mp1;
	mp1["something"] = 21;
	mp1["anything"] = 42;
	mp1["that thing"] = 121;
	mp1["whatever"] = 555;
	stlFile << "mp1: ";
	printMap(mp1, stlFile);

	std::map<std::string, int> mp2(mp1.find("anything"), mp1.end());
	stlFile << "mp2: ";
	printMap(mp2, stlFile);

	std::map<std::string, int> mp3(mp1);
	stlFile << "mp3: ";
	printMap(mp3, stlFile);

	stlFile << "mp3[anything] with []: " << mp3["anything"] << std::endl;
	stlFile << "mp3[non_existing] with []: " << mp3["non_existing"]
	<< std::endl;
	printMap(mp3, stlFile);

	std::map<std::string, int>::reverse_iterator rvrIt = mp3.rbegin();
	stlFile << '{';
	for (; rvrIt != mp3.rend(); rvrIt++) {
		stlFile << rvrIt->first << ':' << rvrIt->second << ' ';
	}
	stlFile << "}\n";

	stlFile << "mp3 empty: " << (mp3.empty() ? "true" : "false") << std::endl;
	stlFile << "mp3 size: " << mp3.size() << std::endl;

	stlFile << "mp3 clear\n";
	mp3.clear();
	stlFile << "mp3 size: " << mp3.size() << std::endl;
	stlFile << "mp3 insert (from mp2)\n";
	mp3.insert(mp2.begin(), mp2.end());
	stlFile << "mp3 size: " << mp3.size() << std::endl;
	stlFile << "mp3: ";
	printMap(mp3, stlFile);

	stlFile << "erase 'that_thing'\n";
	mp3.erase(mp3.find("that thing"));
	stlFile << "erase 'non_existing'\n";
	mp3.erase("non_existing");
	stlFile << "mp3: ";
	printMap(mp3, stlFile);

	mp3.swap(mp2);
	stlFile << "mp3: ";
	printMap(mp3, stlFile);

	stlFile << "mp3 == mp2: " << (mp3 == mp2 ? "true" : "false") << std::endl;
	stlFile << "mp3 < mp2: " << (mp3 < mp2 ? "true" : "false") << std::endl;
	stlFile << "mp3 >= mp2: " << (mp3 >= mp2 ? "true" : "false") << std::endl;

	std::map<int, int> mp4;
	for (int i = 0, j = 100; i < 300000; i++, j++) {
		mp4.insert(std::make_pair(i * 2, j));
	}
	stlFile << "count 41: " << mp4.count(41) << std::endl;
	stlFile << "count 50: " << mp4.count(50) << std::endl;
	stlFile << "count 300005: " << mp4.count(300005) << std::endl;
	stlFile << "find 26: " << mp4.find(26)->first << std::endl;
	stlFile << "lower bound 127: " << mp4.lower_bound(127)->first << std::endl;
	stlFile << "upper bound 244: " << mp4.upper_bound(244)->first << std::endl;

	clock_t g_end = clock();
	stlFile << "stl_map_Execution time (ms): " << (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
}

/*
 **=========================================================================
 **		 set Test
 **=========================================================================
 */

// static void printSet(const std::set<std::string>& s, std::ofstream& stlFile) {
// 	stlFile << '{';
// 	std::set<std::string>::const_iterator b = s.begin();
// 	std::set<std::string>::const_iterator e = s.end();
// 	while (b != e) {
// 		stlFile << *b << ' ';
// 		b++;
// 	}
// 	stlFile << "}\n";
// }

// static void set_test(std::ofstream& stlFile) {
// 	clock_t g_start = clock();

// 	std::set<std::string> st1;
// 	st1.insert("something");
// 	st1.insert("anything");
// 	st1.insert("that thing");
// 	st1.insert("whatever");
// 	stlFile << "st1: ";
// 	printSet(st1, stlFile);

// 	std::set<std::string> st2(st1.find("anything"), st1.end());
// 	stlFile << "st2: ";
// 	printSet(st2, stlFile);

// 	std::set<std::string> st3(st1);
// 	stlFile << "st3: ";
// 	printSet(st3, stlFile);

// 	std::set<std::string>::reverse_iterator rvrIt = st3.rbegin();
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

// 	std::set<int> st4;
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

int test_stl() {
	std::ofstream stlFile("./stlFile.txt");
	if (stlFile.fail())
	{
		std::cerr << "Error!" << std::endl;
	}

	stlFile << "----- TEST STL -----" << std::endl;
	stlFile << "\n***** VECTOR TEST *****\n" << std::endl;
	vector_test(stlFile);
	stlFile << std::endl;

	stlFile << "\n***** STACK TEST *****\n" << std::endl;
	stack_test(stlFile);
	stlFile << std::endl;

	stlFile << "\n***** MAP TEST *****\n" << std::endl;
	map_test(stlFile);
	stlFile << std::endl;

	// stlFile << "\n***** SET TEST *****\n" << std::endl;
	// set_test(stlFile);
	// stlFile << std::endl;

	stlFile.close();
	return 0;
}
