
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
#include "utils.hpp"
#include "game.hpp"
using namespace std;

//Use breadth-first algorithm to find the shortest path between killer and player
int findShortestPath(int start, int end, unordered_map<int, vector<int>> graph) {
    vector<bool> visited(7, false);
    vector<int> parent(7, -1); 
    queue<int> q; 
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        //find path
        if (current == end) {
            vector<int> path;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            //Return to the killer's next move location
            return path[1];
        }
        // finding the path
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    return 0;
}

//Output the screen of the killer chasing the player
void killer_print(int address_k ,int address_p){
    system("clear");
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int term_width = size.ws_col;
    int term_hight = size.ws_row;
    int padding1 = (term_hight - 35)/2;
    int padding2 = (term_width - 81)/2;
    int padding3 = (term_width - 33)/2;
    int padding4 = (term_width - 56)/2;
    int padding5 = (term_width - 27)/2;
    std::vector<vector<char>> g_map;
    ifstream fin;
    fin.open("map.txt");
    if (fin.fail()){
        cout << "Error in file opening!" << endl;
        exit(1);
    }
    string line;
    while (getline(fin, line)){
        vector<char> row(line.begin(),line.end());
        g_map.push_back(row);
    }
    fin.close();

    //Display and highlight players and killers on the map
    if (address_k == 1){
        g_map[11][39]='K';
        g_map[11][40]='i';
        g_map[11][41]='l';
        g_map[11][42]='l';
        g_map[11][43]='e';
        g_map[11][44]='r';
    }
    else if (address_k == 2){
        g_map[15][25]='K';
        g_map[15][26]='i';
        g_map[15][27]='l';
        g_map[15][28]='l';
        g_map[15][29]='e';
        g_map[15][30]='r';
    }
    else if (address_k == 3){
        g_map[8][17]='K';
        g_map[8][18]='i';
        g_map[8][19]='l';
        g_map[8][20]='l';
        g_map[8][21]='e';
        g_map[8][22]='r';
    }
    else if (address_k == 4){
        g_map[6][46]='K';
        g_map[6][47]='i';
        g_map[6][48]='l';
        g_map[6][49]='l';
        g_map[6][50]='e';
        g_map[6][51]='r';
    }
    else if (address_k == 5){
        g_map[17][64]='K';
        g_map[17][65]='i';
        g_map[17][66]='l';
        g_map[17][67]='l';
        g_map[17][68]='e';
        g_map[17][69]='r';
    }
    else if (address_k == 6){
        g_map[8][57]='K';
        g_map[8][58]='i';
        g_map[8][59]='l';
        g_map[8][60]='l';
        g_map[8][61]='e';
        g_map[8][62]='r';
    }
    if (address_p == 1){
        g_map[12][39]='Y';
        g_map[12][40]='o';
        g_map[12][41]='u';
    }
    else if (address_p == 2){
        g_map[16][27]='Y';
        g_map[16][28]='o';
        g_map[16][29]='u';
    }
    else if (address_p == 3){
        g_map[9][17]='Y';
        g_map[9][18]='o';
        g_map[9][19]='u';
    }
    else if (address_p == 4){
        g_map[7][46]='Y';
        g_map[7][47]='o';
        g_map[7][48]='u';
    }
    else if (address_p == 5){
        g_map[18][64]='Y';
        g_map[18][65]='o';
        g_map[18][66]='u';
    }
    else if (address_p == 6){
        g_map[9][57]='Y';
        g_map[9][58]='o';
        g_map[9][59]='u';
    }
    cout << "\033[" << padding1 << ";" << 1 << "H";
    for (int i=0; i<g_map.size(); i++){
        cout << string(padding2,' ');
        for (int j=0; j < g_map[i].size(); j++){
            if (g_map[i][j]=='K' || g_map[i][j]=='i' || g_map[i][j]=='l' || g_map[i][j]=='e' || g_map[i][j]=='r') cout << "\033[1;31;40m" << g_map[i][j] << "\033[0m";
            else if (g_map[i][j]=='Y' || g_map[i][j]=='o' || g_map[i][j]=='u') cout << "\033[1;36;40m" << g_map[i][j] << "\033[0m";
            else cout << "\033[1;37;40m" << g_map[i][j] << "\033[0m";
        }
        cout << endl;
        // print line by line 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    cout << endl;
    cout << string(padding5,' ') + "\033[1m<Press any key to continue>\033[0m" << endl;
    //Stay on the display interface and wait for player input
    while (true) {
		if (Mygetchar()) break;
	}
}

//The killer moves and returns to the killer's new location for storage
int killer_move(int start,int end) {
	//Create a map to search for the path between the killer and the player
    unordered_map<int, vector<int>> graph = {
    {0, {1, 2}},
    {1, {3, 5}},
    {2, {3, 4}},
    {3, {1, 2, 4}},
    {4, {2, 3, 6}},
    {5, {1, 6}}
    };
    int killer_address = findShortestPath(start, end, graph);
    killer_print(killer_address,end);
    return killer_address;
}

//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
//Notice that the next few functions all do the same thing
//Output specific maps according to different game levels and change them to specific colors.
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！

void game_map2_print(int l, int i, vector<vector<char>>& game_map){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1= (term_width-l)/2;
	int padding2= (term_hight-i-3)/2;
	cout << "\033[" << padding2 << ";" << 1 << "H";
	for (size_t j=0; j < game_map.size(); j++){
		for (size_t k=0; k < game_map[j].size(); k++){
			if (k==0) cout << string(padding1,' ');
			if (game_map[j][k] == '@') {
                cout << "\033[1;36;40m" << game_map[j][k] << "\033[0m";
                continue;
            } else if (game_map[j][k] == '&') {
                cout << "\033[1;31;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == 'E') {
                cout << "\033[1;35;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == '/' || game_map[j][k] == '\\' || game_map[j][k] == '^'){
				cout << "\033[1;32;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == '_' || game_map[j][k] == '|' || game_map[j][k] == '+'){
				cout << "\033[1;33;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == 'o'){
				cout << "\033[1;93;40m" << game_map[j][k] << "\033[0m";
				continue;
			}
			else cout << "\033[1;37;40m" << game_map[j][k] << "\033[0m";
		}
		cout << endl;
	}
}

void game_map1_print(int l, int i, vector<vector<char>>& game_map){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1= (term_width-l)/2;
	int padding2= (term_hight-i-3)/2;
	cout << "\033[" << padding2 << ";" << 1 << "H";
	for (size_t j=0; j < game_map.size(); j++){
		for (size_t k=0; k < game_map[j].size(); k++){
			if (k==0) cout << string(padding1,' ');
			if (game_map[j][k] == '@') {
                cout << "\033[1;36;40m" << game_map[j][k] << "\033[0m";
                continue;
            } else if (game_map[j][k] == '&') {
                cout << "\033[1;31;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == 'E') {
                cout << "\033[1;35;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == '_' || game_map[j][k] == '\\' || game_map[j][k] == '/'){
				cout << "\033[1;33;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == 'X' || game_map[j][k] == '(' || game_map[j][k] == ')' || game_map[j][k] == '-' || game_map[j][k] == '|'){
				cout << "\033[1;31;40m" << game_map[j][k] << "\033[0m";
				continue;
			}
			else cout << "\033[1;37;40m" << game_map[j][k] << "\033[0m";
		}
		cout << endl;
	}
}

void game_map5_print(int l, int i, vector<vector<char>>& game_map){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1= (term_width-l)/2;
	int padding2= (term_hight-i-3)/2;
	cout << "\033[" << padding2 << ";" << 1 << "H";
	for (size_t j=0; j < game_map.size(); j++){
		for (size_t k=0; k < game_map[j].size(); k++){
			if (k==0) cout << string(padding1,' ');
			if (game_map[j][k] == '@') {
                cout << "\033[1;36;40m" << game_map[j][k] << "\033[0m";
                continue;
            } else if (game_map[j][k] == '&') {
                cout << "\033[1;31;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == 'E') {
                cout << "\033[1;35;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == '/' || game_map[j][k] == '\\' || game_map[j][k] == 'o'){
            	if (k>32){
            		cout << "\033[1;92;40m" << game_map[j][k] << "\033[0m";
					continue;
            	}else {
            		cout << "\033[1;91;40m" << game_map[j][k] << "\033[0m";
					continue;
            	}
			}else if (game_map[j][k] == '-' || game_map[j][k] == '_' || game_map[j][k] == '|' || game_map[j][k] == '\'' || game_map[j][k] == '\"'){
				if (j > 2){
					cout << "\033[1;34;40m" << game_map[j][k] << "\033[0m";
					continue;
				}else {
					cout << "\033[1;93;40m" << game_map[j][k] << "\033[0m";
					continue;
				}
			}else if (game_map[j][k] == '=') {
                cout << "\033[1;36;40m" << game_map[j][k] << "\033[0m";
                continue;
            }
			else cout << "\033[1;37;40m" << game_map[j][k] << "\033[0m";
		}
		cout << endl;
	}
}

void game_map3_print(int l, int i, vector<vector<char>>& game_map){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1= (term_width-l)/2;
	int padding2= (term_hight-i-3)/2;
	cout << "\033[" << padding2 << ";" << 1 << "H";
	for (size_t j=0; j < game_map.size(); j++){
		for (size_t k=0; k < game_map[j].size(); k++){
			if (k==0) cout << string(padding1,' ');
			if (game_map[j][k] == '@') {
                cout << "\033[1;36;40m" << game_map[j][k] << "\033[0m";
                continue;
            } else if (game_map[j][k] == '&') {
                cout << "\033[1;31;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == 'E') {
                cout << "\033[1;35;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == '*'){
				cout << "\033[1;93;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == '/' || game_map[j][k] == '\\' || game_map[j][k] == '^'){
				if (j <= 12){
					cout << "\033[1;32;40m" << game_map[j][k] << "\033[0m";
					continue;
				}else {
					cout << "\033[1;31;40m" << game_map[j][k] << "\033[0m";
					continue;
				}
			}else if (game_map[j][k] == '!' || game_map[j][k] == '|'){
				cout << "\033[1;91;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == ':' || game_map[j][k] == 'Q' || game_map[j][k] == 'O' || game_map[j][k] == ')'){
				cout << "\033[1;93;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == '-' || game_map[j][k] == '~'){
				if (j < 7){
					cout << "\033[1;94;40m" << game_map[j][k] << "\033[0m";
					continue;
				}else {
					cout << "\033[1;93;40m" << game_map[j][k] << "\033[0m";
					continue;
				}
			}else if (game_map[j][k] == '_'){
				if (j <= 11){
					cout << "\033[1;32;40m" << game_map[j][k] << "\033[0m";
					continue;
				}else {
					cout << "\033[1;31;40m" << game_map[j][k] << "\033[0m";
					continue;
				}
			}
			else cout << "\033[1;37;40m" << game_map[j][k] << "\033[0m";
		}
		cout << endl;
	}
}

void game_map6_print(int l, int i, vector<vector<char>>& game_map){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1= (term_width-l)/2;
	int padding2= (term_hight-i-3)/2;
	cout << "\033[" << padding2 << ";" << 1 << "H";
	for (size_t j=0; j < game_map.size(); j++){
		for (size_t k=0; k < game_map[j].size(); k++){
			if (k==0) cout << string(padding1,' ');
			if (game_map[j][k] == '@') {
                cout << "\033[1;36;40m" << game_map[j][k] << "\033[0m";
                continue;
            } else if (game_map[j][k] == '&') {
                cout << "\033[1;31;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == 'E') {
                cout << "\033[1;35;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == '*'){
				cout << "\033[1;93;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == '!' || game_map[j][k] == 'O'){
				cout << "\033[1;93;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == ',' || game_map[j][k] == '_' || game_map[j][k] == '`' || game_map[j][k] == ')' ||
				game_map[j][k] == '(' || game_map[j][k] == '-' || game_map[j][k] == '\'' || game_map[j][k] == '|' || game_map[j][k] == '~' || game_map[j][k] == 'l'){
				cout << "\033[1;91;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == 'H' || game_map[j][k] == '\\' || game_map[j][k] == '/' || game_map[j][k] == '+' || game_map[j][k] == '{' || game_map[j][k] == '}' || game_map[j][k] == 's'){
				cout << "\033[1;95;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == 'o' || game_map[j][k] == '='){
				cout << "\033[1;96;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == '[' || game_map[j][k] == ']'){
				cout << "\033[1;92;40m" << game_map[j][k] << "\033[0m";
				continue;
			}
			else cout << "\033[1;37;40m" << game_map[j][k] << "\033[0m";
		}
		cout << endl;
	}
}

void game_map4_print(int l, int i, vector<vector<char>>& game_map){
	system("clear");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1= (term_width-l)/2;
	int padding2= (term_hight-i-3)/2;
	cout << "\033[" << padding2 << ";" << 1 << "H";
	for (size_t j=0; j < game_map.size(); j++){
		for (size_t k=0; k < game_map[j].size(); k++){
			if (k==0) cout << string(padding1,' ');
			if (game_map[j][k] == '@') {
                cout << "\033[1;36;40m" << game_map[j][k] << "\033[0m";
                continue;
            } else if (game_map[j][k] == '&') {
                cout << "\033[1;31;40m" << game_map[j][k] << "\033[0m";
                continue;
            }else if (game_map[j][k] == 'E') {
                cout << "\033[1;35;40m" << game_map[j][k] << "\033[0m";
                continue;
			}else if (game_map[j][k] == '~' || game_map[j][k] == '_' || game_map[j][k] == '-'){
				cout << "\033[1;34;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == ':'){
				cout << "\033[1;93;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == '[' || game_map[j][k] == ']' || game_map[j][k] == '!'){
				cout << "\033[1;91;40m" << game_map[j][k] << "\033[0m";
				continue;
			}else if (game_map[j][k] == '^'){
				cout << "\033[1;36;40m" << game_map[j][k] << "\033[0m";
				continue;
			}
			else cout << "\033[1;37;40m" << game_map[j][k] << "\033[0m";
		}
		cout << endl;
	}
}

//read player's input, print the time remaining and player move->[wasd]
void show_key(char m, double time_over){
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int term_width = size.ws_col;
	int term_hight = size.ws_row;
	int padding1 = (term_width-1)/2;
	int padding2 = (term_width-11)/2;
	int padding3 = (term_width-3)/2;
	int padding4 = (term_width-53)/2;
	cout << endl;
	cout << endl;
	// highlight player move base on player input
	if (m == 'w'){
		cout << string(padding1,' ') + "_" + string(padding1,' ') << endl;
		cout << string(padding3,' ') + "[" + "\033[1;30;46m" + "w" + "\033[0m"+ "]" + string(padding1,' ') << endl;
		cout << string(padding2,' ') + "--" + "[" + "a" + " " + "s" + " " + "d" + "]" + "--" + string(padding2,' ') << endl;
	}
	else if (m == 'a'){
		cout << string(padding1,' ') + "_" + string(padding1,' ') << endl;
		cout << string(padding3,' ') + "[w]" + string(padding1,' ') << endl;
		cout << string(padding2,' ') + "--" + "[" + "\033[1;30;46m" + "a" + "\033[0m" + " " + "s" + " " + "d" + "]" + "--" + string(padding2,' ') << endl;
	}
	else if (m == 's'){
		cout << string(padding1,' ') + "_" + string(padding1,' ') << endl;
		cout << string(padding3,' ') + "[w]" + string(padding1,' ') << endl;
		cout << string(padding2,' ') + "--" + "[" + "a" + " " + "\033[1;30;46m" + "s" + "\033[0m" + " " + "d" + "]" + "--" + string(padding2,' ') << endl;
	}
	else if (m == 'd'){
		cout << string(padding1,' ') + "_" + string(padding1,' ') << endl;
		cout << string(padding3,' ') + "[w]" + string(padding1,' ') << endl;
		cout << string(padding2,' ') + "--" + "[" + "a" + " " + "s" + " " + "\033[1;30;46m" + "d" + "\033[0m" + "]" + "--" + string(padding2,' ') << endl;
	}
	else {
		cout << string(padding1,' ') + "_" + string(padding1,' ') << endl;
		cout << string(padding3,' ') + "[w]" + string(padding1,' ') << endl;
		cout << string(padding2,' ') + "--" + "[" + "a" + " " + "s" + " " + "d" + "]" + "--" + string(padding2,' ') << endl;
	}
	cout << endl;
	// print time remaining
	cout << string(padding4,' ') <<"\033[1;32m" << "------Time Remaining(Press 'q' to leave): " << std::setw(4) << std::fixed << std::setprecision(1) << time_over << " ------" << "\033[0m" << endl;
}



//Created by storing the coordinates within the game level
struct Position{
	int x, y;
};

//Determine whether the player was eaten by enemies in the level
bool end_game(const vector<vector<char>>& game_map) {
    for (int i = 0; i < game_map.size(); i++) {
        for (int j = 0; j < game_map[i].size(); j++) {
            if (game_map[i][j] == '@') {
                return true;
            }
        }
    }
    return false;
}

//Traverse the map to find the player's position and return
Position find_player(vector<vector<char>> &game_map){
	for (int i = 0; i < game_map.size(); i++) {
        for (int j = 0; j < game_map[i].size(); j++) {
            if (game_map[i][j] == '@') {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

//Traverse the map to find all enemy positions stored in vector and return
vector<Position> find_enemy(vector<vector<char>> &game_map){
	vector<Position> enemy;
	Position p;
	for (int i = 0; i < game_map.size(); i++) {
        for (int j = 0; j < game_map[i].size(); j++) {
            if (game_map[i][j] == '&') {
                enemy.push_back({i, j});
            }
        }
    }
    return enemy;
}

//The main body of the game level
int game(vector<vector<char>> &game_map, int game_num, int l, int i, double time_over, int &killer_d, int &check){
	vector<vector<char>> game_map_r = game_map;
	Position player = find_player(game_map);
	vector<Position> enemies = find_enemy(game_map);
	vector<int> enemy_directions(enemies.size(), 1);
	int win = 0;
	//Determine whether the player has been eaten, whether he has won, and whether there is still time left.
	while(end_game(game_map) && win == 0 && time_over > 0.0){
		time_over -= 0.2;
		char m = '\0';
		//If the player has input(kbhit()), read and change the player position
		if (kbhit()){
			char move = Mygetchar();
			m=move;
			//player choose to exit
			if (move == 'q'){
				return -1;
				break;
			}
			int new_x = player.x, new_y = player.y;
			switch (move){
				case 'w': case 'W': new_x--; break;
                case 's': case 'S': new_x++; break;
                case 'a': case 'A': new_y--; break;
                case 'd': case 'D': new_y++; break;
			}
			if (game_map[new_x][new_y] == '.') {
                game_map[player.x][player.y] = '.';
                player.x = new_x;
                player.y = new_y;
                game_map[player.x][player.y] = '@';
            }else if (game_map[new_x][new_y] == 'E'){
            	game_map[player.x][player.y] = '.';
                player.x = new_x;
                player.y = new_y;
                game_map[player.x][player.y] = '@';
            	win = 1;
            }
            else if (game_map[new_x][new_y] == '&'){
            	game_map[player.x][player.y] = '.';
            }
		}
		//Constantly changes the position of all enemies regardless of input
		for (int j = 0; j < enemies.size(); j++) {
            auto& enemy = enemies[j];
            int& direction = enemy_directions[j];
            int new_y = enemy.y + direction;
            if (game_map[enemy.x][new_y] == '.' || game_map[enemy.x][new_y] == '@') {
                game_map[enemy.x][enemy.y] = '.';
                enemy.y = new_y;
                game_map[enemy.x][enemy.y] = '&';
            } else {
                direction = -direction;
                enemy_directions[j] = direction;
            }
        }

		system("clear");
		if (game_num == 1) game_map1_print(l, i, game_map);
		else if (game_num == 2) game_map2_print(l, i, game_map);
		else if (game_num == 3) game_map3_print(l, i, game_map);
		else if (game_num == 4) game_map4_print(l, i, game_map);
		else if (game_num == 5) game_map5_print(l, i, game_map);
		else if (game_num == 6) game_map6_print(l, i, game_map);
		show_key(m, time_over);
		//Continuously refresh the screen, set to 5 frames per second
		usleep(200000);
	}
	//If there is no time left, the killer can make one move
	if (time_over <= 0.0) {
		killer_d = killer_move(killer_d, game_num);
		if (killer_d == game_num) return 0;
		check = game(game_map_r, game_num, l, i, 50.0, killer_d, check);
	}
	//If the player is eaten by an enemy, they will be returned to the starting point of the game level
	else if (win == 0) check = game(game_map_r, game_num, l, i, time_over, killer_d, check);
	//Players can continue to choose paths after passing the level.
	else if (win == 1) return 1;
	return check;
}

int play(int game_num, int &killer_d, int &check){
	vector<vector<char>> game_map;
	ifstream fin;
	string file_name;
	//Open different game levels based on player location
	if (game_num == 1) file_name = "game_1.txt";
	else if (game_num == 2) file_name = "game_2.txt";
	else if (game_num == 3) file_name = "game_3.txt";
	else if (game_num == 4) file_name = "game_4.txt";
	else if (game_num == 5) file_name = "game_5.txt";
	else if (game_num == 6) file_name = "game_6.txt";
	fin.open(file_name);
	if (!fin) {
        cout << "Error opening file." << endl;
        return 1;
    }
	string line;
	int i=0, file_num = game_num;
	while(getline(fin, line)){
		vector<char> row(line.begin(),line.end());
		game_map.push_back(row);
		i++;
	}
	fin.close();
	// initalising game data
	int c3 = game(game_map, game_num, line.length(), i, 50.0, killer_d, check);
	//Determine whether the player lost, quit, or passed the level, and return the corresponding value
	if (c3 == 1){
		return c3;
	}
	else if (c3 == 0){
		return c3;
	}
	else if (c3 == -1){
		return c3;
	}
	return 0;
}
