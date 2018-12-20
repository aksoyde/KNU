#include "StringSearch.h"

// The preprocessing function for Boyer Moore's 
// bad character heuristic 
void StringSearch::badCharHeuristic(char * str, int size, int badchar[NO_OF_CHARS])
{
	int i;

	// Initialize all occurrences as -1 
	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	// Fill the actual value of last occurrence  
	// of a character 
	for (i = 0; i < size; i++)
		badchar[(int)str[i]] = i;
}

// preprocessing for strong good suffix rule 
void StringSearch::preprocess_strong_suffix(int *shift, int *bpos, char *pat, int m)
{
	// m is the length of pattern  
	int i = m, j = m + 1;
	bpos[i] = j;

	while (i > 0)
	{
		/*if character at position i-1 is not equivalent to
		  character at j-1, then continue searching to right
		  of the pattern for border */
		while (j <= m && pat[i - 1] != pat[j - 1])
		{
			/* the character preceding the occurence of t in
			   pattern P is different than mismatching character in P,
			   we stop skipping the occurences and shift the pattern
			   from i to j */
			if (shift[j] == 0)
				shift[j] = j - i;

			//Update the position of next border  
			j = bpos[j];
		}
		/* p[i-1] matched with p[j-1], border is found.
		   store the  beginning position of border */
		i--; j--;
		bpos[i] = j;
	}
}

////Preprocessing for case 2 
void preprocess_case2(int *shift, int *bpos, char *pat, int m)
{
	int i, j;
	j = bpos[0];
	for (i = 0; i <= m; i++)
	{
		/* set the border postion of first character of pattern
		   to all indices in array shift having shift[i] = 0 */
		if (shift[i] == 0)
			shift[i] = j;

		/* suffix become shorter than bpos[0], use the position of
		   next widest border as value of j */
		if (i == j)
			j = bpos[j];
	}
}

vector<int> prefix_function(const string&pat)
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

void StringSearch::NaiveSearch(char* pat, char* txt)
{
	int M = strlen(pat);
	int N = strlen(txt);

	/* A loop to slide pat[] one by one */
	for (int i = 0; i <= N - M; i++) {
		int j;

		/* For current index i, check for pattern match */
		for (j = 0; j < M; j++)
			if (txt[i + j] != pat[j])
				break;

		if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
			printf("Pattern found at index %d \n", i);			
	}
}

void StringSearch::RabinKarpSearch(char pat[], char txt[], int q)
{
	int d = NO_OF_CHARS;
	/* pat -> pattern
	txt -> text
	q -> A prime number*/
	int M = strlen(pat);
	int N = strlen(txt);
	int i, j;
	int p = 0; // hash value for pattern 
	int t = 0; // hash value for txt 
	int h = 1;

	// The value of h would be "pow(d, M-1)%q" 
	for (i = 0; i < M - 1; i++)
		h = (h*d) % q;

	// Calculate the hash value of pattern and first window of text 
	for (i = 0; i < M; i++)
	{
		p = (d*p + pat[i]) % q;
		t = (d*t + txt[i]) % q;
	}

	// Slide the pattern over text one by one 
	for (i = 0; i <= N - M; i++)
	{

		// Check the hash values of current window of text 
		// and pattern. If the hash values match then only 
		// check for characters on by one 
		if (p == t)
		{
			/* Check for characters one by one */
			for (j = 0; j < M; j++)
			{
				if (txt[i + j] != pat[j])
					break;
			}

			// if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1] 
			if (j == M)
				printf("Pattern found at index %d \n", i);
		}

		// Calculate hash value for next window of text: Remove 
		// leading digit, add trailing digit 
		if (i < N - M)
		{
			t = (d*(t - txt[i] * h) + txt[i + M]) % q;

			// We might get negative value of t, converting it 
			// to positive 
			if (t < 0)
				t = (t + q);
		}
	}
}

void StringSearch::BoerMurHorspulSearch(char * pat, char * txt)
{
	int m = strlen(pat);
	int n = strlen(txt);

	int badchar[NO_OF_CHARS];

	/* Fill the bad character array by calling
	   the preprocessing function badCharHeuristic()
	   for given pattern */
	badCharHeuristic(pat, m, badchar);

	int s = 0;  // s is shift of the pattern with  
				// respect to text 
	while (s <= (n - m))
	{
		int j = m - 1;

		/* Keep reducing index j of pattern while
		   characters of pattern and text are
		   matching at this shift s */
		while (j >= 0 && pat[j] == txt[s + j])
			j--;

		/* If the pattern is present at current
		   shift, then index j will become -1 after
		   the above loop */
		if (j < 0)
		{
			printf("pattern occurs at shift = %d \n", s);

			/* Shift the pattern so that the next
			   character in text aligns with the last
			   occurrence of it in pattern.
			   The condition s+m < n is necessary for
			   the case when pattern occurs at the end
			   of text */
			s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

		}

		else
			/* Shift the pattern so that the bad character
			   in text aligns with the last occurrence of
			   it in pattern. The max function is used to
			   make sure that we get a positive shift.
			   We may get a negative shift if the last
			   occurrence  of bad character in pattern
			   is on the right side of the current
			   character. */
			s += fmax(1, j - badchar[txt[s + j]]);
	}
}

void StringSearch::BoerMurSearch(char * pat, char * txt)
{
	int m = strlen(pat);
	int n = strlen(txt);

	int *bpos = new int[m + 1], *shift = new int[m + 1], badchar[NO_OF_CHARS];

	//initialize all occurence of shift to 0 
	for (int i = 0; i < m + 1; i++) shift[i] = 0;

	//do preprocessing
	badCharHeuristic(pat, m, badchar);
	preprocess_strong_suffix(shift, bpos, pat, m);
	preprocess_case2(shift, bpos, pat, m);

	int i = 0, j;
	while (i <= n - m)
	{
		j = m - 1;
		while (j >= 0 && pat[j] == txt[i + j]) j--;
		if (j < 0)
		{
			printf("pattern occurs at shift = %d \n", i);
			i += shift[0];
		}
		else
			i += fmax(shift[j + 1], j - badchar[txt[i + j]]);
	}
	delete[] bpos;
	delete[] shift;
}

void StringSearch::KMPSearch(char * pat, char * txt)
{
	int M = strlen(pat);
	int N = strlen(txt);
	string S = string(pat) + '#' + string(txt);

	//create a prefix function for pat#txt string
	vector<int> pr = prefix_function(S);

	for (size_t i = 2 * M; i < pr.size(); i++)
	{
		if (pr[i] == M)
			printf("Found pattern at index %d \n", i - 2 * M);
	}
}
