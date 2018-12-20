#include<iostream>
#include<vector>
#include<string>
using std::vector;
using std::string;
using std::cout;
using std::endl;

vector<int> prefix_function(const string& pattern)
{
	int n = pattern.length();
	vector<int> pi(n);// в i-м элементе (его индекс i-1) количество 
	//совпавших символов в начале и конце для построки длины i. 
	pi[0] = 0;
	for (size_t i = 1; i < n; ++i)
	{
		int j = pi[i - 1];
		while (j > 0 && pattern[i] != pattern[j])
			j = pi[j - 1];
		if (pattern[i] == pattern[j])  ++j;
		pi[i] = j;
	}
	return pi;
}

bool KMP(const string& text, const string& pattern)
{
	bool patternIsSubText = false;
	string S = pattern + '#' + text;

	vector<int> pr = prefix_function(S);
	for (size_t i = 2*pattern.size(); i < pr.size() && !patternIsSubText; i++)
	{
		if (pr[i] == pattern.length())
			patternIsSubText = true;
	}
	for (unsigned int i = 0; i < pr.size(); i++)
		cout << pr[i] << " ";

	cout << endl;
	return patternIsSubText;
}
bool isCyclicShift(const string& text, const string& pattern)
{
	string S = text + text;
	return KMP(S, pattern);
}
int main()
{
	string s1 = "aabaaab", s2 = "cba";
	vector<int> x = prefix_function(s1);
	for (int i = 0; i < x.size(); i++)
		cout << x[i] << " ";

	system("pause");
	return 0;
}