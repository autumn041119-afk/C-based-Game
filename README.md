# **HKUer's Global Escape —— by Group 23**
## Game Description & Rules

> You were kidnapped by a mysterious man !!!
> 
1. Mysterious organizations are scouring the world for smart college students in an attempt to obtain their genes. As a smart HKU student, you are unfortunately targeted by them and kidnapped to Antarctica.
2. You managed to escape from the house where you were held, but Antarctica is not safe and you need to find a way to get back to Hong Kong (”destination”).
3. As there is no direct route, you need to find and select your transit continent on the world map (by typing in a number), each continent has a different level waiting for you!
4. After arriving at the staging continent, you meet some local members of the mysterious organization who are looking for you (indicated by an "&"), and after being spotted by them (the "@" and "&" run into each other), you'll be returned to your initial position on the continent
5. You need to follow the available paths (indicated by "·"), move up(w), down(s), left(a), and right(d) to avoid their capture, and find the exit ("E") to complete the level.
6. Once you reach the exit, you can choose a new staging continent on the world map.
7. When you reach Hong Kong (destination) your game is complete!
8. Note that because staying on a continent for a long time leaves too many clues, you need to try to complete the level on that continent before the time limit.
9. If you stay on a continent for longer than the time limit, the Mystery Organization will immediately find your tracks and send assassins（“Killer”） from Antarctica to hunt you down.
10. When the assassins of the mysterious organization reach your continent, it means that they have captured you and your game is a complete failure!

## **Introduction to Symbols**

**"*"**                           Escape routes you can choose.

**"Destination"**       The destination you need to go to.

**"now"**                       where you are now.

**"@"**                           player position.

**"&"**                           Enemies who encounter you will be reset to original position.

**"E"**                           Exits in the game.

**"."**                           Walkable area.

**"w"**                           Player moves up.

**"a"**                           Player goes left.

**"s"**                           Player goes down.

**"d"**                           Player goes right.

**"Killer"**                 Killer location.

**"You"**                       Your location.

## Team Members（alphabetical order）

1. Chen Airui
    - uid: 3036227719
    - email: ivy204@connect.hku.hk
    - github account: ChenIvy204
2. Huang Junran
    - uid: 3036226909
    - email: huangjr@connect.hku.hk
    - github account: florenccce
3. Yau Tin
    - uid: 3036226686
    - email: autumn04@connect.hku.hk
    - github account: qt1119

## Introduction Video

Link: https://youtu.be/IORjig8XWzU

## Game Features & Coding Requirement

1. Use random to pick random colors to output the game settlement screen when the game is won or lost.
    - Generation of random game sets or events [Code Requirement 1]
2. Use vectors to store constantly changing information about enemies and players in the game, thus realizing the effect of constantly moving players and enemies.
    - Data structures for storing game status (e.g., arrays, STL containers)[Code Requirement 2]
3. Use vectors to store the world map and offer it to the player for path selection.
    - Data structures for storing game status (e.g., arrays, STL containers)[Code Requirement 2]
4. Use structure with vectors to store multiple enemy positions for a Super Mario-like effect where enemies are constantly moving.
    - Data structures for storing game status (e.g., arrays, STL containers)[Code Requirement 2]
5. Use vectors to store the game's backstory screen, as well as the game's victory and defeat screens. Release the memory when you end the use.
    - Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)[Code Requirement 3]
6. Use vectors to store constantly changing information about enemies and players in the game, thus realizing the effect of constantly moving players and enemies. Memory is freed at the end of use and is used to store game content for the next node.
    - Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)[Code Requirement 3]
7. Use vectors to store the world map and offer it to the player for path selection. Memory is freed at the end of use and is used to store game content for the next node.
    - Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)[Code Requirement 3]
8. Use structure with vectors to store multiple enemy positions for a Super Mario-like effect where enemies are constantly moving. Memory is freed at the end of use and is used to store game content for the next node.
    - Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)[Code Requirement 3]
9. Use the file input to read story background images, victory/defeat images, world map images, and terrain maps for each game level.
    - When the player chooses to quit the game in the middle of the game use file output to save the progress of the game.
    - When the player chooses to continue the previous game, the file input is used to read the progress of the player's last game.
    - File input/output (e.g., for loading/saving game status)[Code Requirement 4]
10. Write the main program for route selection, etc. and specific game levels in each location separately, and finally merge the programs.
    - Program codes in multiple files (recall separate compilation)[Code Requirement 5]
11. Write functions that will be used by multiple programs as separate header files (hpp) and reference them in different files. Examples include functions for non-blocking input, functions for storing and reading game processes, etc.
    - Program codes in multiple files (recall separate compilation)[Code Requirement 5]

## List of non-standard C/C++ libraries
1. <sys/ioctl.h>
- Used to get the size of the terminal window to achieve the centering effect.
2. <unistd.h> <termios.h> <fcntl.h>
- Used to implement non-blocking input by changing the terminal settings, e.g. kbhit(), getch(), Mygetchar()

## Compilation and execution instructions
1. Open a linux terminal
2. Compile the game using makefile: `make play`
3. Run the game: `./play`
4. Clears the executable program: `make clean`
