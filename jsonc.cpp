#include <iostream>
#include <fstream>
#include <string>
#include "lexer.cpp"

using std::cout;
using std::endl;
using std::string;

string openfile(char *path) {
	cout << "filepath: " << path << endl;
	string lines;
	string line;
	std::ifstream file (path);
	if (file.is_open()) {
		while (getline(file, line)) {
			lines += line;
		}
		file.close();
	} else {
		cout << "failed to open: " << path << endl; 
	}

	return lines;
}

void help() {
	cout << "help"   		<< ": " << "show help" << endl;
	cout << "<JSON>" 		<< ": " << "analyze" << endl;
	cout << "-f <FILEPATH>" << ": " << "read file & analyze" << endl;
}

int main(int argc, char *argv[]) {
	string json_body;
	if (argc == 2) {
		// 0: bin
		// 1: json
		if (string(argv[1]) == "help") {
			help();
			return 0;
		}
		json_body = argv[1];
	} else if (argc == 3) {
		// 0: bin
		// 1: "-f"
		// 2: filepath
		if (string(argv[1]) != "-f") {
			cout << "unknown flag: " << argv[1] << endl;
			return 1;
		}
		json_body = openfile(argv[2]);
	} else {
		cout << "unknown arg. pls `help`" << endl;
		return 1;
	}

	vector<jsonc::Token> tokens = jsonc::lex(json_body);
	string out;
	int c = 0;
	for (jsonc::Token& t: tokens) {
		out += t.to_string();
		c++;
		if (c != tokens.size() - 1) {
			out += " ";
		}
	}
	cout << out << endl;

	return 0;
}
