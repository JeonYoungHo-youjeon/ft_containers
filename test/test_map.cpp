#include <time.h>
#include <iostream>
#include "map.hpp"
#include <map>
#include <fstream>
#include <time.h>

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

static void ft_test(std::ofstream& ftFile) {
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
	for (int i = 0, j = 100; i < 3000000; i++, j++) {
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

static void stl_test(std::ofstream& stlFile) {
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
	for (int i = 0, j = 100; i < 3000000; i++, j++) {
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