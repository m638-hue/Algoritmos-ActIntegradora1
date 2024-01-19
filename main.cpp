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
	int n = main.length(), m = pattern.length(); 
	int i = 0, j = 0;

	while (i < n)
	{
		if (main[i] == pattern[j])
			i++, j++;
	}
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

	cout << "mirrored code found, start at " << index << ", ended at " << maxPalindromo + index << endl;

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



//AMBOS la subcadena mas larga
int main()
{
	string transmision1 = "3DB87592E2D933F1A1761D4D392D9CDD9851DE3B0044335D4C46983D16AA1AF6AC232FAFA20F6C21FAC9712D41C5CBB67D9AC397596B58D529E9A17E234BE30DE5ABB26E16FAA9324B8134766C14F11D6B81DB08074C51C45943EB33B7D596948000B08B7C8DD413D66B19FC0C2A2BEABEA6E216E93CD4F720915FE940270C32EFA325040A8306A2733C215728E241420F6346741F81623D66987FF97DCBE0DFF324A98B90CF3FC9551C416BE26D24C27E617EC0F8F27BBC1C95DF1C1793B5533B4AA1B99AB166D726C05DC655A0AF3533AA2DB358C21C9029253D65F22C3BB91DFF8262709190ED64FEEEEF46DE0919072628FFD19BB3C22F56D3529209C12C853BD2AA335720915FE940270C32EFA325040A8306A2733C215728E241420F6346741F81623D66987FF97DCBE0DFF324A98B90CF3FC9551C416BE26D24C27E617EC0F8F27BBC1C95DF1C1793B5533B4AA1B99AB166D726C05DC655A0AF3A56BE58E1A8457E05964B7AA1D6E159CAF784F659F9E68EB14FCC96D6CB8144B3B37BAD4963FA277CFCDCA07B1BF4E423069AEC7F21959118DE58EC3F82466696C20AF791926237A15F94CC34E7A4D4A96B352C7BFDD2583A7CE3827692A7650C042209EF6B2B356B24EA66108B7E07A0BC3C51BCCD703DB529F8F087CF5C70D2C0E21AED75DA38F52FD1F69B5E8CE5FB5DD67B3F0193998B86D7C6314";
	string transmision2 = "A277CFCDCA07B1BF4E423069AEC7F21959118DE58EC3F82466696C20AF791926237A15F94CC34E7A4D4A96B352C7BFDD2583A7CE3827692A7650C042209EF6B2B356B24EA66108B7E07A0BC3C51BCCD703DB529F8F087CF5C70D2C0E21AED75DA38F52FD1F69B5E8CE5FB5DD67B3F0193998B86D7C6314533AA2DB358C21C9029253D65F22C3BB91DFF8262709190ED64FEEEEF46DE0919072628FFD19BB3C22F56D3529209C12C853BD2AA3353DB87592E2D933F1A1761D4D392D9CDD9851DE3B0044335D4C46983D16AAA56BE58E1A8457E05964B7AA1D6E159CAF784F659F9E68EB14FCC96D6CB8144B3B37BAD4963F720915FE940270C32EFA325040A8306A2733C215728E241420F6346741F81623D66987FF97DCBE0DFF324A98B90CF3FC9551C416BE26D24C27E617EC0F8F27BBC1C95DF1C1793B5533B4AA1B99AB166D726C05DC655A0AF3B08074C51C45943EB33B7D596948000B08B7C8DD413D66B19FC0C2A2BEABEA6E216E93CD4F3DB87592E2D933F1A1761D4D392D9CDD9851DE3B0044335D4C46983D16AA1AF6AC232FAFA20F6C21FAC9712D41C5CBB67D9AC397596B58D529E9A17E233DB87592E2D933F1A1761D4D392D9CDD9851DE3B0044335D4C46983D16AA";
	
	palindromo(transmision1);
	palindromo(transmision2);
	
	longestSubcadena(transmision1, transmision2);

	return 0;
}
