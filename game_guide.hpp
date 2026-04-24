#ifndef GAME_GUIDE_H
#define GAME_GUIDE_H


#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <chrono>
#include <thread>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <regex>
#include <cctype>
#include <iomanip>
#include <fcntl.h>
#include <cstdlib>
#include <limits>
using namespace std;

//Output game background introduction
void print_Gameplay_i(){
	//Clear screen and prepare to center
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_hight - 12)/2;
	int padding2 = (term_width - 71)/2;
	int padding3 = (term_width - 41)/2;
	string line;
	ifstream fin;
	vector<vector<char>> Gameplay_i;
	fin.open("Gameplay_Introduction.txt");
	//Read the document stored with the corresponding information
	while (getline(fin, line)){
		vector<char> row(line.begin(),line.end());
		Gameplay_i.push_back(row);
	}
	fin.close();
	cout << "\033[" << padding1 << ";" << 1 << "H";
	for (int i=0; i<Gameplay_i.size(); i++){
		cout << string(padding2,' ');
		for (int j=0; j<Gameplay_i[0].size(); j++){
			if (i < 2){
				if (Gameplay_i[i][j] == '<' || Gameplay_i[i][j]== '>') cout << "\033[1;34m" << Gameplay_i[i][j] << "\033[0m";
				else cout << "\033[1;36m" << Gameplay_i[i][j] << "\033[0m";
			}
			else cout << Gameplay_i[i][j];
			// Output line by line
			std::this_thread::sleep_for(std::chrono::milliseconds(3));
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << string(padding3,' ') + "\033[1;32m---< Press any key to next page >---\033[0m" << endl;
}

//Output the meaning of different characters in the game
void print_s_i(){
	//Clear screen and prepare to center
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_hight - 18)/2;
	int padding2 = (term_width - 62)/2;
	int padding3 = (term_width - 28)/2;
	string line;
	ifstream fin;
	vector<vector<char>> s_i;
	fin.open("s_i.txt");
	//Read the document stored with the corresponding information
	while (getline(fin, line)){
		vector<char> row(line.begin(),line.end());
		s_i.push_back(row);
	}
	fin.close();
	cout << "\033[" << padding1 << ";" << 1 << "H";
	for (int i=0; i<s_i.size(); i++){
		cout << string(padding2,' ');
		//Use different colors to output according to different characters
		for (int j=0; j<s_i[0].size(); j++){
			if (i < 1){
				if (s_i[i][j] == '<' || s_i[i][j]== '>') cout << "\033[1;34m" << s_i[i][j] << "\033[0m";
				else cout << "\033[1;36m" << s_i[i][j] << "\033[0m";
			}
			else if (i > 1 && i < 5 && j < 18){
				if (s_i[i][j] == '*') cout << "\033[1;36;40m" << s_i[i][j] << "\033[0m";
				else if (isalpha(s_i[i][j])) cout << "\033[1;31;40m" << s_i[i][j] << "\033[0m";
				else cout << "\033[1;36m" << s_i[i][j] << "\033[0m";
			}
			else if (i > 5 && i < 8 && j < 18){
				if (s_i[i][j] == '@') cout << "\033[1;36;40m" << s_i[i][j] << "\033[0m";
				else if (s_i[i][j] == '&') cout << "\033[1;31;40m" << s_i[i][j] << "\033[0m";
				else cout << "\033[1;36m" << s_i[i][j] << "\033[0m";
			}
			else if (i > 8 && i < 15 && j < 18){
				if (s_i[i][j] == 'E') cout << "\033[1;35;40m" << s_i[i][j] << "\033[0m";
				else if (s_i[i][j] == '.' || s_i[i][j] == 'a' || s_i[i][j] == 'w' || s_i[i][j] == 's' || s_i[i][j] == 'd') cout << "\033[1;37;40m" << s_i[i][j] << "\033[0m";
				else cout << "\033[1;36m" << s_i[i][j] << "\033[0m";
			}
			else if (i > 14 && j < 18){
				if (s_i[i][j] == 'K' || s_i[i][j] == 'i' || s_i[i][j] == 'l' || s_i[i][j] == 'e' || s_i[i][j] == 'r') cout << "\033[1;31;40m" << s_i[i][j] << "\033[0m";
				else if (s_i[i][j] == 'Y' || s_i[i][j] == 'o' || s_i[i][j] == 'u') cout << "\033[1;36;40m" << s_i[i][j] << "\033[0m";
				else cout << "\033[1;36m" << s_i[i][j] << "\033[0m";
			}
			else cout << s_i[i][j];
			//line by line output the symbols information
			std::this_thread::sleep_for(std::chrono::milliseconds(3));
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << string(padding3,' ') + "\033[1;32m---< Press any key to return >---\033[0m" << endl;
}


#endif
