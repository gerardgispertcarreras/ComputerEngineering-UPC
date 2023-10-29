#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int hexa_a_decimal(const string& hexa){
	int dec = 0;
	int mult = 1;
	for (int i = hexa.length()-1; i >= 0; --i){
		int dig;
		if (hexa[i] > '9') dig = 10 + hexa[i] - 'a';
		else dig = hexa[i] - '0';
		dec += dig*mult;
		mult *= 16;
	}
	return (dec);
}

int bin_a_decimal(const vector<int>& bin){
	int dec = 0;
	int mult = 1;
	for (int i = bin.size()-1; i >= 0; --i){
		dec += bin[i]*mult;
		mult *= 2;
	}
	return (dec);
}



vector<int> hexa_a_binari(const string& hexa){
	int dec = hexa_a_decimal(hexa);
	vector<int> bin;
	while(dec != 0){
		if (dec % 2 == 1) bin.insert(bin.begin(), 1);
		else bin.insert(bin.begin(), 0);
		dec /= 2;
	}
	for (int i = bin.size(); i < 32; ++i) bin.insert(bin.begin(), 0);
	return bin;
}

void print_vec(const vector<int>& vec){
	for(int i = 0; i < vec.size(); ++i) cout << vec[i];
	cout << endl;
}

void print_hexa(const vector<int>& bin){
	int dec = bin_a_decimal(bin);
	vector<char> hexa;
	while(dec != 0){
		if (dec % 16 > 9) hexa.insert(hexa.begin(), char(dec%16 - 10 + 'A'));
		else hexa.insert(hexa.begin(), char(dec%16+'0'));
		dec /= 16;
	}
	int c = bin.size()/4;
	if (bin.size()%4 != 0) ++c;
	for(int i = hexa.size(); i < c; ++i) hexa.insert(hexa.begin(), '0');
	for(int i = 0; i < hexa.size(); ++i) cout << hexa[i];
}

void print_ref(const vector<int>& vec){
	cout << "byte: ";
	print_hexa(vector<int>(&vec[27], &vec[32]));
	cout << endl << "Bloque M: ";
	print_hexa(vector<int>(&vec[0], &vec[27]));
	cout << endl << "Linea MC: ";
	print_hexa(vector<int>(&vec[20], &vec[27]));
	cout << endl << "TAG: ";
	print_hexa(vector<int>(&vec[0], &vec[20]));
	cout << endl;
}

int main(){
	string ref;
	while(cin >> ref){
	vector<int> ref_bin = hexa_a_binari(ref);
	print_vec(ref_bin);
	print_ref(ref_bin);
	}
}