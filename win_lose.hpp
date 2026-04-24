#ifndef WIN_LOSE_H
#define WIN_LOSE_H

#include <iostream>
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
#include <queue>
#include <unordered_map>
#include <random>
using namespace std;

//output game over
void print_game_over(){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_hight - 6)/2;
	int padding2 = (term_width - 57)/2;
	std::vector<vector<char>> game_over;
	ifstream fin;
	fin.open("game_over.txt");
	if (fin.fail()){
		cout << "Error in file opening!" << endl;
		exit(1);
	}
	string line;
	while (getline(fin, line)){
		vector<char> row(line.begin(),line.end());
		game_over.push_back(row);
	}
	fin.close();
	cout << "\033[" << padding1 << ";" << 1 << "H";
	for (int i=0; i<game_over.size(); i++){

		// using random to print game_over using random color
		
		int color = rand() % 10;
		if (color < 5){
			cout << string(padding2,' ');
			for (int j=0; j < game_over[i].size(); j++){
				cout << "\033[1;36;40m" << game_over[i][j] << "\033[0m";
			}
			cout << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else {
			cout << string(padding2,' ');
			for (int j=0; j < game_over[i].size(); j++){
				cout << "\033[1;34;40m" << game_over[i][j] << "\033[0m";
			}
			cout << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}


//output game win
void print_win(){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_hight - 9)/2;
	int padding2 = (term_width - 68)/2;
	std::vector<vector<char>> win;
	ifstream fin;
	fin.open("win.txt");
	if (fin.fail()){
		cout << "Error in file opening!" << endl;
		exit(1);
	}
	string line;
	while (getline(fin, line)){
		vector<char> row(line.begin(),line.end());
		win.push_back(row);
	}
	fin.close();
	cout << "\033[" << padding1 << ";" << 1 << "H";
	for (int i=0; i<win.size(); i++){

		// using random to print the win with random color 

		int color = rand() % 10;
		if (color < 5){
			cout << string(padding2,' ');
			for (int j=0; j < win[i].size(); j++){
				cout << "\033[1;36;40m" << win[i][j] << "\033[0m";
			}
			cout << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else {
			cout << string(padding2,' ');
			for (int j=0; j < win[i].size(); j++){
				cout << "\033[1;32;40m" << win[i][j] << "\033[0m";
			}
			cout << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}

#endif