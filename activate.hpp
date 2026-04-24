#ifndef ACTIVATE_H
#define ACTIVATE_H

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
#include "get_input.hpp"
using namespace std;

//Display the loading interface to make the entire program look more like a game
void loading(){
	// Preparation for centering output content
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_width - 27)/2;
	int padding2 = (term_hight - 7)/2;
	int padding3 = (term_width - 33)/2;
	int padding4 = (term_width - 28)/2;
	int padding5 = (term_width - 32)/2;
	// Move the cursor to the specified position
	cout << "\033[" << padding2 << ";" << 1 << "H";
	cout << "\033[1;33m" + string(padding3,'-') + "\033[0m" + "\033[1;31m<Welcome to the game of ENGG1340>\033[0m"+"\033[1;33m" + string(padding3,'-') + "\033[0m" << endl;
	cout << endl;
	for (int i=0; i <= 17; i++){
		string progress = "\033[1;33m" + string(padding1,'-') + "\033[0m" + "\033[1;32m" + "Loading [" + string(i,'.') + string(17-i,' ') + "]" + "\033[0m" + "\033[1;33m" + string(padding1,'-') + "\033[0m";
		cout << "\r" << progress << flush;
		//Implementing animation output
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
	// At the end of loading, print the loading completion and replace the original loading interface.
	cout << "\r" + string("\033[1;33m") + string(padding1+6,'-') + "\033[0m" + "\033[1;32mLoading Complete!\033[0m" + "\033[1;33m" + string(padding1+4,'-') + "\033[0m\n" << endl;
	cout << string(padding5-5,' ') + string(5,'-') + "[Please use full screen to play]" + string(5,'-') + string(padding5-5,' ') << endl;
	cout << endl;
	cout<< string(padding4,' ') + "<Press any key to continue.>" + string(padding4,' ') << endl;
	for (int i=0; i < padding2; i++){
		cout << endl;
	}
	// Get player input to continue
	while (true) {
		if (getch()) break;
	}
}

// Output a selection interface for players to choose, and return the player options
int selection(){
	//Preparation for centering output content
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_width - 27)/2;
	int padding2 = (term_width - 69)/2;
	int padding3 = (term_width - 12)/2;
	int padding4 = (term_width - 20)/2;
	int padding5 = (term_hight - 11)/2;
	int padding6 = (term_width - 8)/2;
	int padding7 = (term_width - 28)/2;
	int choice = 1;
	while (true){
		// Refresh the screen every time to implement the selection menu
		system("clear");
		// Move the cursor to the specified position
		cout << "\033[" << padding5 << ";" << 1 << "H";
		cout << string(padding1,' ') + "\033[1;34m[Welcome to the game menu.]\033[0m" + string(padding1,' ')<< endl;
		cout << "\n" + string(padding2,' ') + "Please use the up and down keys to select and press Enter to confirm." + string(padding2,' ') << endl;
		cout << endl;
		//Outputs the selection menu based on the player's current selection, so the player can know his current options
		if (choice == 1){
			cout << string(padding3-20,' ') + "------------------>>\033[1;36m[Start Game]\033[0m<<------------------" + string(padding3-21,' ') << endl;
			cout << endl;
			cout << string(padding7,' ') + "\033[1;31m[Continue the previous game]\033[0m" + string(padding7,' ') << endl;
			cout << endl;
			cout << string(padding3,' ') + "\033[1;32m[Game Guide]\033[0m" + string(padding3,' ') << endl;
			cout << endl;
			cout << string(padding4,' ') + "\033[1;33m[Author Information]\033[0m" + string(padding4,' ') << endl;
			cout << endl;
			cout << string(padding6,' ') + "\033[1;35m[ Quit ]\033[0m" + string(padding6,' ') << endl;
		}else if (choice == 3 ){
			cout << string(padding3,' ') + "\033[1;36m[Start Game]\033[0m" + string(padding3,' ') << endl;
			cout << endl;
			cout << string(padding7,' ') + "\033[1;31m[Continue the previous game]\033[0m" + string(padding7,' ') << endl;
			cout << endl;
			cout << string(padding3-20,' ') + "------------------>>\033[1;32m[Game Guide]\033[0m<<------------------" + string(padding3-21,' ') << endl;
			cout << endl;
			cout << string(padding4,' ') + "\033[1;33m[Author Information]\033[0m" + string(padding4,' ') << endl;
			cout << endl;
			cout << string(padding6,' ') + "\033[1;35m[ Quit ]\033[0m" + string(padding6,' ') << endl;
		}else if (choice == 4){
			cout << string(padding3,' ') + "\033[1;36m[Start Game]\033[0m" + string(padding3,' ') << endl;
			cout << endl;
			cout << string(padding7,' ') + "\033[1;31m[Continue the previous game]\033[0m" + string(padding7,' ') << endl;
			cout << endl;
			cout << string(padding3,' ') + "\033[1;32m[Game Guide]\033[0m" + string(padding3,' ') << endl;
			cout << endl;
			cout << string(padding4-20,' ') + "------------------>>\033[1;33m[Author Information]\033[0m<<------------------" + string(padding4-21,' ') << endl;
			cout << endl;
			cout << string(padding6,' ') + "\033[1;35m[ Quit ]\033[0m" + string(padding6,' ') << endl;
		}else if (choice == 5){
			cout << string(padding3,' ') + "\033[1;36m[Start Game]\033[0m" + string(padding3,' ') << endl;
			cout << endl;
			cout << string(padding7,' ') + "\033[1;31m[Continue the previous game]\033[0m" + string(padding7,' ') << endl;
			cout << endl;
			cout << string(padding3,' ') + "\033[1;32m[Game Guide]\033[0m" + string(padding3,' ') << endl;
			cout << endl;
			cout << string(padding4,' ') + "\033[1;33m[Author Information]\033[0m" + string(padding4,' ') << endl;
			cout << endl;
			cout << string(padding6-20,' ') + "------------------>>\033[1;35m[ Quit ]\033[0m<<------------------" + string(padding6-21,' ') << endl;
		}else if (choice == 2){
			cout << string(padding3,' ') + "\033[1;36m[Start Game]\033[0m" + string(padding3,' ') << endl;
			cout << endl;
			cout << string(padding7-20,' ') + "------------------>>\033[1;31m[Continue the previous game]\033[0m<<------------------" + string(padding7-21,' ') << endl;
			cout << endl;
			cout << string(padding3,' ') + "\033[1;32m[Game Guide]\033[0m" + string(padding3,' ') << endl;
			cout << endl;
			cout << string(padding4,' ') + "\033[1;33m[Author Information]\033[0m" + string(padding4,' ') << endl;
			cout << endl;
			cout << string(padding6,' ') + "\033[1;35m[ Quit ]\033[0m" + string(padding6,' ') << endl;
		}
		//Obtain player input, re-output the selection menu after adjusting player options, and confirm player input when the player presses the enter key.
		int key = getch();
		if (key == 10) break;
		if (key == 27){
			getch();
			key = getch();
			if (key == 65){
				choice = (choice == 1) ? 5 : choice - 1;
			}
			else if (key == 66) {
				choice = (choice == 5) ? 1 : choice + 1;
			}	
		}
	}
	return choice;
}

// Output game author information
void a_i(){
	system("clear");
	//Clear the screen to prepare for centering
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_hight - 9)/2;
	int padding2 = (term_width - 40)/2;
	int padding3 = (term_width - 20)/2;
	int padding4 = (term_width - 25)/2;
	cout << "\033[" << padding1 << ";" << 1 << "H";
	cout << string(padding3,' ') + "\033[1;36m<Author Information>\033[0m" + string(padding3,' ') << endl;
	cout << endl;
	cout << string(padding2,' ') + "Yau Tin , email: autumn04@connect.hku.hk" + string(padding2,' ')<< endl;
	cout << endl;
	cout << string(padding2-1,' ') + "Chen Airui , email: ivy204@connect.hku.hk" + string(padding2,' ')<< endl;
	cout << endl;
	cout << string(padding2-2,' ') + "Huang Junran , email: huangjr@connect.hku.hk" + string(padding2,' ') << endl;
	cout << endl;
	cout << string(padding4,' ') + "\033[1;34m<Press any key to return>\033[0m" + string(padding4,' ') << endl;
	//Stay after displaying the author information and wait for player input before continuing.
	while (true){
		if (getch()) break;
	}
}

//Convert the txt document containing the ascii code that changes the output color into an implementable form
string ascii_to_char(const string& str) {
    static const regex ascii_regex(R"(\\033\[(\d+(?:;\d+)*)m)");
    string result;
    auto start = str.begin();
    auto end = str.end();
    smatch match;
    //Find a specific form code and convert it
    while (regex_search(start, end, match, ascii_regex)) {
        result += string(start, match[0].first);
        result += "\033[" + match[1].str() + "m";
        start = match[0].second;
    }
    result += string(start, end);
    return result;
}



//Output the story background of the game
void story(){
	system("clear");
	std::vector<string> abduction;
	ifstream fin;
	//Read the corresponding pattern from the story txt
	fin.open("abduction.txt");
	if (fin.fail()){
		cout << "Error in file opening!" << endl;
		exit(1);
	}
	string line;
	while (getline(fin, line)){
		// use the previous function to change ascii code in the txt file, and make the color can be shown
		abduction.push_back(ascii_to_char(line));
	}
	fin.close();
	int a = abduction.size();
	//prepare for centering
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_hight - a - 4)/2;
	int padding2 = (term_width - 60)/2;
	int padding3 = (term_width - 40)/2;
	int padding4 = (term_width - 27)/2;
	//move cursor to center
	cout << "\033[" << padding1 << ";" << 1 << "H";
	for (int i=0; i < a; i++){
		cout << string(padding2,' ') + "\033[1;37;40m" + abduction[i] + "\033[0m" << endl;
		//animation for line by line output
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	cout << endl;
	cout << string(padding3,' ') + "\033[1;31m<You were kidnapped by a mysterious man>\033[0m" << endl;
	cout << endl;
	cout << string(padding4,' ') + "\033[1m<Press any key to continue>\033[0m" << endl;
	//Stay after displaying the background story and wait for player input before continuing.
	while (true){
		if (getch()) break;
	}
}

#endif
