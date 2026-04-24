#ifndef GAME_PROGRESS_H
#define GAME_PROGRESS_H

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
using namespace std;

//Game save format
struct where
{
	int player_d;
	int killer_d;
	int in_game;
};

//Save game progress related information into archive files
void save_game(int player_d, int killer_d, int in_game){
	ofstream fout;
	fout.open("game_progress.txt");
	if (fout.fail()){
		cout << "Error in file opening!" << endl;
		exit(1);
	}
	//save game process in a file 
	fout << player_d << " " << killer_d << " " << in_game << endl;
	fout.close();
}

//Read game process related information from archive files
where continue_game(){
	where place;
	ifstream fin;
	fin.open("game_progress.txt");
	if (fin.fail()){
		cout << "Error in file opening!" << endl;
		exit(1);
	}
	// read game process 
	fin >> place.player_d >> place.killer_d >> place.in_game;
	fin.close();
	// return game process
	return place;
}

//Output no games in progress
void print_no_game(){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_hight - 3)/2;
	int padding2 = (term_width - 32)/2;
	int padding5 = (term_width - 27)/2;
	cout << "\033[" << padding1 << ";" << 1 << "H";
	cout << string(padding2,' ') + "\033[1;32m---<< No games in progress >>---\033[0m" << endl;
	cout << endl;
	cout << string(padding5,' ') + "\033[1m<Press any key to continue>\033[0m" << endl;
}

//Output game continues
void print_continue_game(){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_hight - 3)/2;
	int padding2 = (term_width - 26)/2;
	int padding5 = (term_width - 27)/2;
	cout << "\033[" << padding1 << ";" << 1 << "H";
	cout << string(padding2,' ') + "\033[1;32m---<< Game continues >>---\033[0m" << endl;
	cout << endl;
	cout << string(padding5,' ') + "\033[1m<Press any key to continue>\033[0m" << endl;
}

#endif