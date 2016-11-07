#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Connection.h"
using namespace std;

int tabSize, **input, vertexCount = 1;
vector<vector<int>> parentsOf, childrensOf;
vector<Connection*> result;

bool checkIfAdjont();
bool checkIfLinear();
void generateOutput();
bool checkPairs(vector<int>);
void loadFile(string);
void saveFile();

int main() {
	cout << "podaj nazwe pliku do otwarcia" << endl;
	string fileName;
	cin >> fileName;
	cout << endl;

	try	{
		loadFile(fileName);
	}
	catch (const std::exception& )	{
		//cout << e.what << endl;
	}
	
	if (checkIfAdjont()) {
		cout << "graf jest sprzezony" << endl;
		if (checkIfLinear()) {
			cout << "graf jest liniowy" << endl;
		}
		else {
			cout << "graf nie jest liniowy" << endl;
		}
		cout << "trwa generowanie grafu oryginalnego" << endl;
		generateOutput();

		saveFile();
		cout << "plik wyjsciowy to output.txt" << endl;
	}
	else {
		cout << "graf wejsiocwy nie jest sprzezony" << endl;
	}
	cout << "zakonczono prace programu, wcisnij dowolny klawisz by wyjsc...." << endl;
	getchar();
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
	result.reserve(tabSize);

	input = new int *[tabSize];
	for (int i = 0; i <= tabSize; i++) {
		result.push_back(new Connection(i));
		vector<int> tempParent;
		vector<int> tempChild;

		childrensOf.push_back(tempChild);
		parentsOf.push_back(tempParent);
		input[i] = new int[tabSize];
		for (int k = 0; k <= tabSize; k++) {
			input[i][k] = 0;
		}
		
	}
	int parent, child;
	while (!file.eof()) {
		getline(file, out, ' ');
		getline(file, in, '\n');

		parent = stoi(out, nullptr, 10);
		child = stoi(in, nullptr, 10);
		
		if (input[parent][child] != 0) {
			cout << "graf posiada krawedzie powtarzajace sie: " << parent << "-" << child << endl;
			return;
		}
		input[parent][child] = 1;
		parentsOf[child].push_back(parent);
		childrensOf[parent].push_back(child);
	}
	file.close();
}
void saveFile() {
	fstream file;
	file.open("output.txt", ios::out);
	file << vertexCount-1 << "\n";

	for (auto connection : result) {
		if (connection->vertex == 0)
			continue;
		file << connection->begin << " " << connection->end << "\n";
	}
	file.close();
}
bool checkPairs(vector<int> toCheck) {
	if (toCheck.size() > 1) {
		for (int v1 : toCheck) {
			for (int v2 : toCheck) {
				for (int i = 1; i <= tabSize; i++) {
					if (input[v1][i] != input[v2][i]) {
						return false;
					}
				}
			}
		}
	}
	return true;
}
bool checkIfAdjont() {
	vector<int> toCheck;
	for (int i = 1; i <= tabSize; i++) {
		for (int j = 1; j <= tabSize; j++) {
			if (input[j][i] == 1) {
				toCheck.push_back(j);
			}
		}
		if (!checkPairs(toCheck)) {
			return false;
		}
		toCheck.clear();
	}
	return true;
}
bool checkIfLinear() {
	for (auto children : childrensOf) {
		if (children.size() < 1)
			continue;
		for (int i = 0; i < tabSize; i++) {
			if (input[children[0]][i] == input[children[1]][i])
				return false;
		}
	}
	return true;
}
void generateOutput() {
	for (auto connection : result) {
		if (connection->vertex == 0)
			continue;
		if (connection->begin == 0) {
			connection->begin = vertexCount++;
		}

		for (auto children : childrensOf[connection->vertex]) {
			if (result[children]->begin != 0) {
				connection->end = result[children]->begin;
			}
		}
		if (connection->end == 0) {
			connection->end = vertexCount++;
		}
		for (auto children : childrensOf[connection->vertex]) {
			result[children]->begin = connection->end;
		}
	}
	
}