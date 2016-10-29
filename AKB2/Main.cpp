#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int tabSize, **input;
vector<int> parentOf, childrenOf;

bool checkIfAdjont();
bool checkIfLinear();
void generateOutput();
void loadFile(string);

int main() {
	cout << "podaj nazwe pliku do otwarcia" << endl;
	string fileName;
	cin >> fileName;

	loadFile(fileName);

	if (checkIfAdjont) {
		if (checkIfLinear)
			cout << "graf jest liniowy" << endl;
		else
			cout << "graf nie jest liniowy" << endl;
		cout << "trwa generowanie grafu oryginalnego" << endl;



		cout << "plik wyjsciowy to output.txt" << endl;
	}
	else {
		cout << "graf wejsiocwy nie jest sprzezony" << endl;
	}
	cout << "zakonczono prace programu" << endl;
	getchar();
	return 0;
}

void loadFile(string fileName) {
	fstream file;
	string in, out;

	file.open(fileName, ios::in);
	string tabsize;
	getline(file, tabsize);
	tabSize = stoi(tabsize, nullptr, 10);

	for (int i = 0; i <= tabSize; i++) {
		input = new int *[tabSize];
		for (int j = 0; j <= tabSize; j++) {
			input[i] = new int[tabSize];
			for (int k = 0; k <= tabSize; k++) {
				input[i][k] = 0;
			}
		}
	}

	while (!file.eof()) {
		getline(file, out, ' ');
		getline(file, in, '\n');

		parentOf.push_back(stoi(in, nullptr, 10));
		childrenOf.push_back(stoi(out, nullptr, 10));

	}

}