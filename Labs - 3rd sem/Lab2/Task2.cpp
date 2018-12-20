#include"NutsAndBoltsMatch.h"

int main()
{
	char nuts[] = { '@', '#', '$', '%', '^', '&' };
	char bolts[] = { '$', '%', '&', '^', '@', '#' };
	int n = sizeof(nuts) / sizeof(nuts[0]);

	//NutsAndBoltsMatch::HashMatch(nuts, bolts, n);
	NutsAndBoltsMatch::PartitionMatch(nuts, bolts, n);
	system("pause");
	return 0;
}