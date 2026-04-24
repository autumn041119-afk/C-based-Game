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
#include "win_lose.hpp"
#include "game_guide.hpp"
#include "game_progress.hpp"
#include "get_input.hpp"
#include "game.hpp"
#include "activate.hpp"
using namespace std;

//Output the world map and let the player choose the game route or exit the game and return to the player's choice
int print_map(int map_number){
	//Clear screen and prepare to center
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_hight - 35)/2;
	int padding2 = (term_width - 81)/2;
	int padding3 = (term_width - 49)/2;
	int padding4 = (term_width - 56)/2;
	std::vector<vector<char>> g_map;
	ifstream fin;
	// Read the corresponding map document to output different alternative routes
	fin.open("map_"+to_string(map_number)+".txt");
	if (fin.fail()){
		cout << "Error in file opening!" << endl;
		exit(1);
	}
	string line;
	// use vector to store the map
	while (getline(fin, line)){
		vector<char> row(line.begin(),line.end());
		g_map.push_back(row);
	}
	fin.close();
	cout << "\033[" << padding1 << ";" << 1 << "H";
	for (int i=0; i<g_map.size(); i++){
		cout << string(padding2,' ');
		for (int j=0; j < g_map[i].size(); j++){
			// use blue to highlight the routine and red to highlight your position
			if (g_map[i][j]=='*') cout << "\033[1;36;40m" << g_map[i][j] << "\033[0m";
			else if (isdigit(g_map[i][j])) cout << "\033[1;35;40m" << g_map[i][j] << "\033[0m";
			else if (isalpha(g_map[i][j])) cout << "\033[1;31;40m" << g_map[i][j] << "\033[0m";
			else cout << "\033[1;37;40m" << g_map[i][j] << "\033[0m";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << string(padding4,' ') + "\033[1;32m" + "------" + "[You escaped by chance and picked up a map.]" + "------" + "\033[0m" << endl;
	cout << endl;
	cout << "\033[1m" + string(padding3,' ') + "Please choose your escape route(or 'q' to quit): " + "\033[0m";
	string input;
	int mapnumber;
	//Read player input
    while (true) {
    	cin >> input;
    	if (input == "q" || input == "Q") {
        	return -1;
    	}
    	// determine whether the player input is reliable, and return different values based on reliable input
    	try {
        	mapnumber = stoi(input);
        	if (mapnumber >= 1 && mapnumber <= 6) {
            	break;  // if the input is valid, return the input
        	} else {
            	cout << "\033[1A\033[2K" << "\033[1m" + string(padding3, ' ') + "Invalid input, please try again(or 'q' to quit): " + "\033[0m";
        	}
    	} catch (const std::invalid_argument& e) {
        	cout << "\033[1A\033[2K" << "\033[1m" + string(padding3, ' ') + "Invalid input, please try again(or 'q' to quit): " + "\033[0m";
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
	}
	//return the players choice 
    return mapnumber;
}

// Used to determine whether the route entered by the player is a feasible route at the current location, and return player next place 
int choose(int address){
	int mapnumber;
	//mapnumber is the player's current position
	while(address!=6){
		if (address==0){
			mapnumber = print_map(0);
			if (mapnumber==1){
				return 1;
			}else if(mapnumber==2){
				return 2;
			}else if(mapnumber==-1){
				return -1;
			}else{
				mapnumber = print_map(0);
			}
		}else if(address==1){
			mapnumber = print_map(1);
			if(mapnumber==3){
				return 3;
			}else if(mapnumber==5){
				return 5;
			}else if(mapnumber==-1){
				return -1;
			}else{
				mapnumber = print_map(1);
			}
		}else if(address==2){
			mapnumber = print_map(2);
			if (mapnumber==3){
				return 3;
			}else if(mapnumber==4){
				return 4;
			}else if(mapnumber==-1){
				return -1;
			}else{
				mapnumber = print_map(2);
			}
		}else if(address==3){
			mapnumber = print_map(3);
			if(mapnumber==1){
				return 1;
			}else if(mapnumber==2){
				return 2;
			}else if(mapnumber==4){
				return 4;
			}else if(mapnumber==-1){
				return -1;
			}else{
				mapnumber = print_map(3);
			}
		}else if(address==4){
			mapnumber = print_map(4);
			if(mapnumber==2){
				return 2;
			}else if(mapnumber==3){
				return 3;
			}else if(mapnumber==6){
				return 6;
			}else if(mapnumber==-1){
				return -1;
			}else{
				mapnumber = print_map(4);
			}
		}else if(address==5){
			mapnumber = print_map(5);
			if(mapnumber==1){
				return 1;
			}else if(mapnumber==6){
				return 6;
			}else if(mapnumber==-1){
				return -1;
			}else{
				mapnumber = print_map(5);
			}
		}
	}
	return 0;
}

//Main program, used to connect the entire game
int main(){
	//clear screen
	system("clear");
	//print loading
	loading();
	int choice = 0;
	// if choice == 5 leave the game
	while (choice != 5){
		choice = selection();
		//Determined based on the choices made by the player in the selection menu
		if (choice == 1) {
			//Start a new game when selecting Start Game
			int address = 0, killer_d = 0;
			story();
			int check = 1;
			// Determine whether the player has reached the end point
			while (address <= 6){
				int in_game = 0, is_exist;
				is_exist = choose(address);
				//The player chooses to leave and terminate the game
				if (is_exist == -1){
					getch();
					save_game(address, killer_d, in_game);
					break;
				}
				address = is_exist;
				in_game = 1;
				// Enter specific game levels based on the player's chosen path
				int c3 = play(address, killer_d, check);
				//The player is captured and the game fails. Output failed
				if(c3 == 0){
					print_game_over();
					getch();
					getch();
					break;
				}
				//Player opts out, saves and terminates game
				else if (c3 == -1){
					getch();
					save_game(address, killer_d, in_game);
					break;
				}
				//The player successfully escapes and outputs victory.
				else if (address == 6){
					print_win();
					getch();
					getch();
					save_game(0,0,0);
					break;
				}
			}
		}
		//The player chooses to continue the previous game
		else if (choice == 2) {
			where place;
			place = continue_game();
			//read game process 
			int address = place.player_d, killer_d = place.killer_d, in_game=place.in_game;
			//Determine whether there is a game in progress. If so, the game will be output to continue and continue. 
			//If not, there will be no game in progress and return to the selection menu.
			if (address == 0 && killer_d == 0){
				print_no_game();
				getch();
			}
			else {
				print_continue_game();
				getch();
				//The logic is the same as in the new game, just starting from the save area
				int check = 1, is_exist = address;
				while (address <= 6){
					//Used to determine whether to leave in a game level or when selecting a path, and continue the game based on the difference.
					if (in_game == 0){
						is_exist = choose(address);
					}
					if (is_exist == -1){
						getch();
						save_game(address, killer_d, in_game);
						break;
					}
					address = is_exist;
					//in_game == 1 means player in the game level instead of choosing the routine
					in_game = 1;
					int c3 = play(address, killer_d, check);
					if(c3 == 0){
						// player was captured by the killer, game fail
						print_game_over();
						getch();
						getch();
						break;
					}
					else if (c3 == -1){
						//player choose to leave the game, and will save the game process
						getch();
						save_game(address, killer_d, in_game);
						break;
					}
					else if (address == 6){
						// player win the game 
						print_win();
						getch();
						getch();
						save_game(0,0,0);
						break;
					}
					in_game = 0;
				}
			}
		}
		// The player chooses to read the game guide and output the game guide.
		else if (choice == 3) {
			print_Gameplay_i();
			getch();
			print_s_i();
			getch();
		}
		// Select to read author information and output author information
		else if (choice == 4) a_i();
	}
	return 0;
}