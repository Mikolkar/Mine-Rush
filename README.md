## Mine Rush Game

Mine Rush is a minesweeper-style game with some new and original gameplay features. The goal of the game is to disarm as many bombs as possible by uncovering new fields on the map, flagging or shifting the board down the map, thereby generating a new row with potential mines to disarm. The player can choose from three levels of difficulty: easy, medium, and hard, and the chosen difficulty affects the width of the playing board.

If the player moves the board down the map, the game removes the last row at the bottom of the map, checking whether the bombs have been flagged correctly. If a bomb is not flagged or if a flag is placed on a cell without a bomb, the player loses one life out of three. Additionally, if the player uncovers a cell with a bomb, they also lose one life. However, if the bombs are flagged correctly, the player earns one point for each bomb disarmed. The game ends when the player loses all three lives. After losing the game, all the bombs on the current field are shown on the board. The player can either exit the game or reset it by clicking the appropriate button.

Program Versions
The game comes in two versions, one terminal and the other graphical. Depending on which version you want to run, you need to follow these steps:

Terminal Version
The terminal version of the program accepts arguments for easy, medium, or hard 	difficulty levels. If no arguments are provided, the program will display a message telling the user what to enter to run the program correctly. To run the terminal version, navigate to the src/ directory and enter:
		./mine_terminal <argument>

Graphical Version
To run the graphical version of the game, navigate to the src/ directory and enter:
	.	/sdl2_game

It is important to note that the executable files should remain in the src/ directory, as there may be problems with loading the font and images.
Running the Program To run the program using the run_game.sh file, enter the following command for the specific version:

Terminal Version - Easy
		./run_game -t-e

Terminal Version - Medium
		./run_game -t-m

Terminal Version - Hard
		./run_game -t-h

To run it correctly on Linux, the following libraries must be installed: Ncurses, SDL2, SDL_TTF, and SDL_IMAGE. In case they are not installed, please enter the following commands in the terminal:

#Ncurses:
sudo apt-get install libncurses5-dev libncursesw5-dev

SDL2:
sudo apt-get install libsdl2-dev
SDL_TTF:
sudo apt-get install libsdl2-ttf-dev
SDL_IMAGE:
sudo apt-get install libsdl2-image-dev

Compilation of the project:
After downloading the libraries, go to the build/ directory and enter cmake .., then in the same directory enter the command make to compile the project.
To remove executable files in the build/ directory, enter make clean.

To easily remove the compiled file in the build directory, enter ./run_game remove-makefiles in the main project directory. If you want to quickly compile it, simply enter ./run_game build-makefiles. Before that, remember to change the permissions of the run_game.sh file to executable by entering chmod +x run_game.sh in the main project directory.








