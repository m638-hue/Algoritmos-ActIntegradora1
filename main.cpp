// =========================================================
// File: main.cpp
// Author:
//     Mauro Martinez - A01282152
//     Claudia Torres - A01284940		
// Date: 
// =========================================================

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void LongestPrefixSufix(vector<int>& arr, string pattern)
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
int KMP(string main, string pattern)
{
	vector<int> lps(pattern.length(), 0);
	LongestPrefixSufix(lps, pattern);
	int n = main.length(), m = pattern.length(); 
	int i = 0, j = 0;

	while (i < n)
	{
		if (main[i] == pattern[j])
			i++, j++;
		else
		{
			if (j == 0) i += 1;
			else j = lps[j - 1];
		}

		if (j == m) return i - m;
	}

	return -1;
}

vector<char> expand(string texto) {
	vector<char> nueva_cadena = { '#'};
	for (int i = 0; i < texto.length(); i++) {
		nueva_cadena.push_back(texto[i]);
		nueva_cadena.push_back('#');
	}
	return nueva_cadena;
}

//Claudia Palindromos
void palindromo(string texto) 
{
	auto cadena = expand(texto);
	vector<int> palin(cadena.size(), 0);

	// 0  1  2  3  4  5  6  7  8  9  10  11  12  13  14 
	// #  s  #  d  #  a  #  b  #  a  #   s   #   d   #
	// 0  1  0  1  0  1  0  3  0  1  0   1   0   1   0

	int center = 0; // center = 11
	int right = 0; // right = 12

	for (int i = 1; i < cadena.size(); i++) { // i = 13
		if (right > i) { // 10 > 10
			int iMirror = center - (i - center); // 7 - (9-7) = 5
			palin[i] = min(right - i, palin[iMirror]); // (2,0) = 0
		}
		while (i + 1 + palin[i] < cadena.size() && i - 1 - palin[i] >= 0 && cadena[i + 1 + palin[i]] == cadena[i - 1 - palin[i]]) { //  # == #
			palin[i] += 1;
		}
		if (i + palin[i] > right) { // 11 > 10 
			center = i; 
			right = i + palin[i]; 
		}
	}

	int maxPalindromo = 0;
	int centerIndex = 0;

	for (int j = 1; j < cadena.size(); j++) {
		if (maxPalindromo < palin[j]) {
			maxPalindromo = palin[j];
			centerIndex = j;
		}
	}

	int index = ((centerIndex - maxPalindromo) / 2);

	cout << "mirrored code found, start at " << index << ", ended at " << maxPalindromo + index << endl << endl;

}

void longestSubcadena(string transmision1, string transmision2) {

	int m = transmision1.length();
	int n = transmision2.length();

	int maximum = 0;

	vector<vector<int>> matrix(m+1, vector<int>(n+1));

	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0) {
				matrix[i][j] = 0; // Corregir índices
			}
			else if (transmision1[i - 1] == transmision2[j - 1]) { // Corregir índices
				matrix[i][j] = matrix[i - 1][j - 1] + 1; // Corregir índices
				maximum = max(maximum, matrix[i][j]);
			}
			else {
				matrix[i][j] = 0; // Corregir índices
			}
		}
	}

	cout << "the longest common substring between transmission1.txt and transmission2.txt is " << maximum << " characters long" << endl;
}

string getfile(string name)
{
	ifstream file(name);
	string res;
	string temp;

	while (getline(file, temp, '\n'))
		res += temp;

	return res;
}

//AMBOS la subcadena mas larga
int main()
{
	vector<string> transmissions(2);
	vector<string> codes(3);

	transmissions[0] = getfile("transmission1.txt");
	transmissions[1] = getfile("transmission2.txt");

	codes[0] = getfile("mcode1.txt");
	codes[1] = getfile("mcode2.txt");
	codes[2] = getfile("mcode3.txt");

	for (int i = 0; i < transmissions.size(); i++)
	{
		cout << "transmission" << i + 1 << ".txt:" << endl;

		for (int j = 0; j < codes.size(); j++)
		{
			int match = KMP(transmissions[i], codes[j]);

			cout << "mcode" << j + 1 << ".txt - ";
			if (match != -1) cout << "true, start at position " << match << endl;
			else cout << "false" << endl;
		}

		cout << endl;
	}

	cout << "transmission1.txt" << ":" << endl;
	palindromo(transmissions[0]);
	cout << "transmission2.txt" << ":" << endl;
	palindromo(transmissions[1]);
	
	longestSubcadena(transmissions[0], transmissions[1]);

	return 0;
}
