#include "Matrix_Search.h"

//function which computes hash for columns of given argument
//with keeping in mind presented bounds by pCols, pRows
void Matrix_Search::ComputateColumnsHash(char ** PATTERN, vector<int>& pattern, int pCols, 
	int pRows, int NO_OF_CHARS, int q)
{
	for (size_t j = 0; j < pCols; j++)
	{
		pattern[j] = 0;
		for (size_t i = 0; i < pRows; i++)
			pattern[j] = (pattern[j] * NO_OF_CHARS + PATTERN[i][j]) % q;
	}
}

//function which updates hash functions in text while pattern is shifting through rows
void Matrix_Search::ChangeRowHash(int row, char** TEXT, vector<int>& text, int pRows, int tCols,
	int NO_OF_CHARS, int dm, int q)
{
	for (size_t j = 0; j < tCols; j++)
	{
		text[j] = ((text[j] - TEXT[row - pRows + 1][j]*dm) * NO_OF_CHARS +
			TEXT[row+1][j]) % q;

		// We might get negative value of hash, converting it 
			// to positive 
		if (text[j] < 0)
			text[j] = (text[j] + q);
	}
}

//function for trivial check for equality: symbol by symbol
bool Matrix_Search::isSymbolEqual(int row, int column, char **PATTERN, int pRows, 
	int pCols, char **TEXT)
{
	bool isEqual = true;
	for(int i = 0; i < pRows && isEqual; i ++)
		for(int j = 0; j < pCols && isEqual; j ++)
			if (PATTERN[i][j] != TEXT[row - pRows + 1 + i][column + j])
				isEqual = false;
	return isEqual;
}

// return the prefix function for given patttern pat[0..M-1]
vector<int> Matrix_Search::BuildPrefixFunction(vector<int>& pat)
{
	int M = pat.size();
	vector<int> pi(M);
	//in i-th position(index i-1) is the quantity
	//of matched symbols with prefix and suffix in substring of pat
	//with length i
	pi[0] = 0;
	for (size_t i = 1; i < M; ++i)
	{
		int j = pi[i - 1];
		while (j > 0 && pat[i] != pat[j])
			j = pi[j - 1];

		if (pat[i] == pat[j])  ++j;
		pi[i] = j;
	}
	return pi;
}

//function which returns -1 if pattern isn't a subsequence of text by elements
//or index where pattern is presented in text
int Matrix_Search::KMP(vector<int>& pattern, vector<int>& text, bool & found)
{
	int M = pattern.size();
	int N = text.size();

	// create lps that will hold the longest prefix suffix 
	// values for pattern
	// Preprocess the pattern (calculate lps[] array) 
	vector<int> lps = BuildPrefixFunction(pattern);

	found = false;
	int i = 0; // index for txt[] 
	int j = 0; // index for pat[] 
	while (i < N) 
	{
		if (pattern[j] == text[i]) 
		{
			j++;
			i++;
		}

		if (j == M)
		{
			found = true;
			return i - j;
		}

		// mismatch after j matches 
		else if (i < N && pattern[j] != text[i]) {
			// Do not match lps[0..lps[j-1]] characters, 
			// they will match anyway 
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
	return -1;
}

//Function which prints information about whether PATTERN is submatrix of TEXT
void Matrix_Search::Search(char ** PATTERN, int pRows, int pCols, char ** TEXT, int tRows, 
	int tCols, int NO_OF_CHARS, int q)
{
	//creating hash function for text columns
	vector<int> text(tCols);
	ComputateColumnsHash(TEXT, text, tCols, pRows,NO_OF_CHARS,q);

	int row = pRows-1;
	int dm = 1;

	for (size_t j = 0; j < pRows - 1; j++)
		dm = (NO_OF_CHARS*dm) % q;

	//creating hash function for pattern columns
	vector<int> pattern(pCols);
	ComputateColumnsHash(PATTERN, pattern, pCols, pRows, NO_OF_CHARS, q);

	bool found = false;
	int column;
	do
	{//if hash functions of pattern and text submatrix columns are equal
		// we are checking these grids by symbol comparison
		column = KMP(pattern, text, found);
		if (column > -1 && !isSymbolEqual(row, column, PATTERN, pRows, pCols, TEXT))
			found = false;

		//changing the hash for shifted row
		if (found == false && row < tRows-1)
			ChangeRowHash(row, TEXT, text, pRows, tCols, NO_OF_CHARS,dm,q);
		row = row + 1;
	} while (found == false && row < tRows);

	if (found == true)
	{
		cout << "The beginning of the pattern is found at\n"
			<< row - pRows << "," << column << "\n";
	}
	else
	{
		cout << "Pattern wasn't found\n";
	}
}
