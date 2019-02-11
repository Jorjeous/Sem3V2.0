#include "pch.h"
#include <algorithm>
#include <iostream>
#include <map> 
#include <string>
#include <vector>
#include <fstream>
using namespace std;

string prepare(string (&str) )
{
	std::string data = str;
	std::transform(str.begin(), str.end(), data.begin(), ::tolower);
	//cout << "tolover\n" << data;
	int len = data.length();
	//cout << "len: " << len <<" last: " <<data[len-1];
	len--;
	if ( (data[len] == '.') || (data[len] == ',') || (data[len] == '!'))
	{
		//cout << "Here";
		data.pop_back();
	}
	return data;
}

struct Statistics {
	int count;
	string word;
}statist;

bool cmp(const Statistics &a1, const Statistics &a2)
{
	if ((a1.count) < (a2.count))
	{
		return true;
	}
	else
	{
		return false;
	}
}



int main()
{
	string word;
	map <string, int> CW; //count words
	ifstream file("Book.txt");

	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> word;
			word = prepare(word);
			CW[word]++;
		}
	}
	
	struct Statistics tmp;
	vector <Statistics> stat;
	for (auto it = CW.begin(); it != CW.end(); it++)
	{
		//cout << it->first << ":" << it->second << endl;
		tmp.word = it->first;
		tmp.count = it->second;
		stat.push_back(tmp);
	}
	sort(stat.begin(), stat.end(), cmp);

	for (auto it = stat.begin(); it != stat.end(); it++) {
		cout << it->word << ':' << it->count << '\n';
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
/*map <string, int> CW =		{	{ "Mother", 37 },
									{ "Father", 40 },///map явно инициализирована
									{ "Brother", 15 },
									{ "Sister", 20 } };; //Count Words
	cin >> str;
	for (auto it = CW.begin(); it != CW.end(); ++it) {
		cout << it->first << ":" << it->second << endl;
	};*/a
