// =========================================================
// File: main.cpp
// Author:
//     Mauro Martinez - A01282152
//	   Claudia Torres - A01284940		
// Date: 
// =========================================================

#include <iostream>
#include <vector>
using namespace std;

void PrefixArray(vector<int>& arr, string pattern)
{
	int length = 0;
	arr[0] = 0;

	for (int i = 1; i < pattern.length(); i++)
	{
		if (pattern[i] == pattern[length])
		{
			length++;
			arr[i] = length;
		}
		else
		{
			if (length != 0)
			{
				length = arr[length - 1];
				i--;
			}
			else
				arr[i] = 0;
		}
	}
}

//Mauro KMP
void KMP(string main, string pattern)
{
	vector<int> prefix(0, pattern.length());
	PrefixArray(prefix, pattern);


}

//Claudia Palindromos


//AMBOS la subcadena mas larga
int main()
{

	return 0;
}