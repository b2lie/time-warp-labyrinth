// reccomended console window size: fullscreen
// reccomended OS: windows 8 onwards / other compatible OS
// fonts used: ASCII Mirror, Old Banner
// OST credits: Cats&Soup (game available on iOS and Android)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h> // running the program in fullscreen mode and other functions
#include <unistd.h> // for usleep

// colors
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define CORAL   "\033[38;5;203m"
#define GOLD    "\033[38;5;220m"

// customizing text
#define BLINKING     "\x1b[5m"
#define BOLD         "\x1b[1m"
#define UNDERLINE    "\x1b[4m"

// function declarations:
void delay(int number_of_seconds);
void gotoxy(int x, int y);
int is_goal_reached(int x, int y, int i, int j, char maze[i][j], char goal);
void winning_message(int player);
// void losing_message(int player);
void maze_traversal(int i, int j, char maze[i][j], char goal, int timelimit);
void add_obstacles(int i, int j, char maze[i][j], int timelimit);
void move_player(int *x, int *y, int rows, int cols, char (*maze)[cols]);
void move_player_simultaneous(int *x1, int *y1,int *x2, int *y2, int rows, int cols, char (*maze)[cols]);
void print_maze(int rows, int cols, char maze[rows][cols]);
void select_maze(char chosen_maze);
void menuDisplay(int selectedOption);
int menu();


int main() {

	// gets console window handle
	HWND hwnd = GetConsoleWindow();
	
	// maximizes console window
	ShowWindow(hwnd, SW_MAXIMIZE);

	// change for new desktop
	const char* gameOST = "C:\\Users\\Ali Nadir\\Desktop\\Time Warp Labyrinth\\twlcats.mp3";

	char myCommand[256]; // buffer that holds in the command to run

	/* int snprintf(char *str, size_t size, const char *format, ...);
	   better than just sprintf bc it allots a specific amount of memory for the buffer
	   start /B -> used to let the audio player execute in the background */
	snprintf(myCommand, sizeof(myCommand), "start /B \"%s\\Program Files (x86)\\Windows Media Player\\wmplayer.exe\" \"%s\"", getenv("SystemDrive"), gameOST);

	system(myCommand);

	menu();

	return 0;
}

COORD coord = {0, 0};

void gotoxy(int x, int y) { // function to set the cursor position
	coord.X = (SHORT)x;
	coord.Y = (SHORT)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void delay(int number_of_seconds) {
	int milli_seconds = 1000 * number_of_seconds;
	clock_t start_time = clock(); // records current time
	while (clock() < start_time + milli_seconds); // increments time until current time is less than alloted time
}

int is_goal_reached(int x, int y, int i, int j, char maze[i][j], char goal) {
	return (maze[x][y] == goal);
}

void winning_message(int player) {
	system("cls");

	// change for new desktop
	const char* effect = "C:\\Users\\Ali Nadir\\Desktop\\Time Warp Labyrinth\\won_game.wav";

	char playSound[256]; // buffer that holds in the command to run

	/* int snprintf(char *str, size_t size, const char *format, ...);
	   better than just sprintf bc it allots a specific amount of memory for the buffer
	   start /B -> used to let the audio player execute in the background */
	snprintf(playSound, sizeof(playSound), "start /B \"%s\\Program Files (x86)\\Windows Media Player\\wmplayer.exe\" \"%s\"", getenv("SystemDrive"), effect);

	system(playSound);

	if(player == 1) {
		printf(GREEN BOLD"\n\n\t\t\t\t\t######  #          #    #     # ####### ######        #      #     # ####### #     # \n");
		printf("\t\t\t\t\t#     # #        #   #    # #   #       #     #     # #      #  #  # #     # # #   # \n");
		printf("\t\t\t\t\t######  #       #     #    #    #####   ######        #      #  #  # #     # #  #  # \n");
		printf("\t\t\t\t\t#       #       #######    #    #       #   #         #      #  #  # #     # #   # # \n");
		printf("\t\t\t\t\t#       #       #     #    #    #       #    #        #      #  #  # #     # #    ## \n");
		printf("\t\t\t\t\t#       ####### #     #    #    ####### #     #     #####     ## ##  ####### #     # \n" RESET);
		printf("\n\n");
	} else {
		printf(GREEN BOLD "\n\n\t\t\t\t\t######  #          #    #     # ####### ######      #####     #     # ####### #     # \n");
		printf("\t\t\t\t\t#     # #         # #    #   #  #       #     #    #     #    #  #  # #     # ##    # \n");
		printf("\t\t\t\t\t#     # #        #   #    # #   #       #     #          #    #  #  # #     # # #   # \n");
		printf("\t\t\t\t\t######  #       #     #    #    #####   ######      #####     #  #  # #     # #  #  # \n");
		printf("\t\t\t\t\t#       #       #######    #    #       #   #      #          #  #  # #     # #   # # \n");
		printf("\t\t\t\t\t#       #       #     #    #    #       #    #     #          #  #  # #     # #    ## \n");
		printf("\t\t\t\t\t#       ####### #     #    #    ####### #     #    #######     ## ##  ####### #     # \n" RESET);
		printf("\n\n");
	}

	delay(2);

	system("cls");

	printf(RED BOLD "\n\t\t\t\t _______  _____ _____ ___ _   _ ____    _____ _   _ _____   ____    _    __  __ _____ _ \n");
	printf("\t\t\t\t|____ \\ \\/ |_ _|_   _|_ _| | / |___ \\  |_   _| | | |____ | |___ \\  / \\  |  \\/  |____ | |\n");
	printf("\t\t\t\t  |_  |\\  / | |  | |  | || |/  |_  | |   | | | |_| | |_  |  _  | |/ _ \\ | |\\/| | |_  | |\n");
	printf("\t\t\t\t ___| |/  \\ | |  | |  | ||  /| | |_| |   | | |  _  |___| | | |_| / ___ \\| |  | |___| |_|\n");
	printf("\t\t\t\t|_____/_/\\_|___| |_| |___|_/ |_|____/    |_| |_| |_|_____| |____/_/   \\_|_|  |_|_____(_)\n");
	printf("\t\t\t\t                                                                                        \n" RESET);

	delay(2);
	HWND myConsole = GetConsoleWindow(); // gets window identifier
	ShowWindow(myConsole, 0); // closes console entirely
	exit(0);
}

// for E, M, H and C maze traversal:
void maze_traversal(int i, int j, char maze[i][j], char goal, int timelimit) {
	int x1 = 0, y1 = 1;  // player 1 starting pos
	int x2 = i - 1, y2 = j - 2;  // player 2 starting pos
	int time_remaining = timelimit;

	while (1) {
		print_maze(i, j, maze);
		move_player_simultaneous(&x1,&y1,&x2,&y2,i,j,maze);

		// simulating time passing
		delay(1);
		time_remaining--;

		// add obstacle if time is up
		add_obstacles(i, j, maze, time_remaining);
	}
}

void add_obstacles(int i, int j, char maze[i][j], int timelimit) {
	if(timelimit <= 0) {
		srand(time(NULL));
		char obstacle = '*';
		int random_i = rand() % i;
		int random_j = rand() % j;

		if(maze[random_i][random_j] == ' ') {
			if((random_i == i + 5) || (random_j == j + 5) || (random_i == i - 5) || (random_j == j - 5)) {
				// ^ ensures ostacles wont be placed within 5 blocks of the players to make the game more fair, allows for movement
				maze[random_i][random_j] = obstacle;
				print_maze(i, j, maze);

				printf("\n\tOBSTACLE ADDED!\n\t");
				delay(1);
			}
		}
	}
}

void move_player(int *x, int *y, int rows, int cols, char (*maze)[cols]) {
	if (kbhit()) { // checking for key presses
		char move = getch();
		switch (move) {
			// player 1's movement
			case 'w':
				if(maze[*x - 1][*y] == 'X') {
					winning_message(1);
//					losing_message(2);
				}
				if (maze[*x - 1][*y] != '#') {
					maze[*x][*y] = ' ';
					*x -= 1;
					maze[*x][*y] = '1';
				}
				if(maze[*x - 1][*y] == '*') {
					winning_message(2);
//					losing_message(1);
				}
				break;
			case 'a':
				if(maze[*x][*y - 1] == 'X') {
					winning_message(1);
//					losing_message(2);
				}
				if (maze[*x][*y - 1] != '#') {
					maze[*x][*y] = ' ';
					*y -= 1;
					maze[*x][*y] = '1';
				}
				if(maze[*x][*y - 1] == '*') {
					winning_message(2);
//					losing_message(1);
				}
				break;
			case 's':
				if(maze[*x + 1][*y] == 'X') {
					winning_message(1);
//					losing_message(2);
				}
				if (maze[*x + 1][*y] != '#') {
					maze[*x][*y] = ' ';
					*x += 1;
					maze[*x][*y] = '1';
				}
				if(maze[*x + 1][*y] == '*') {
					winning_message(2);
//					losing_message(1);
				}
				break;
			case 'd':
				if(maze[*x][*y + 1] == 'X') {
					winning_message(1);
//					losing_message(2);
				}
				if (maze[*x][*y + 1] != '#') {
					maze[*x][*y] = ' ';
					*y += 1;
					maze[*x][*y] = '1';
				}
				if(maze[*x][*y + 1] == '*') {
					winning_message(2);
//					losing_message(1);
				}
				break;
			// player 2's movement
			case 72:  // up key
				if(maze[*x - 1][*y] == 'X') {
					winning_message(2);
//					losing_message(1);
				}
				if (maze[*x - 1][*y] != '#') {
					maze[*x][*y] = ' ';
					*x -= 1;
					maze[*x][*y] = '2';
				}
				if(maze[*x - 1][*y] == '*') {
					winning_message(1);
//					losing_message(2);
				}
				break;
			case 75:  // left key
				if(maze[*x][*y - 1] == 'X') {
					winning_message(2);
//					losing_message(1);
				}
				if (maze[*x][*y - 1] != '#') {
					maze[*x][*y] = ' ';
					*y -= 1;
					maze[*x][*y] = '2';
				}
				if(maze[*x][*y - 1] == '*') {
					winning_message(1);
//					losing_message(2);
				}
				break;
			case 80:  // down key
				if (maze[*x + 1][*y] == 'X') {
					winning_message(2);
//					losing_message(1);
				}
				if (maze[*x + 1][*y] != '#') {
					maze[*x][*y] = ' ';
					*x += 1;
					maze[*x][*y] = '2';
				}
				if (maze[*x + 1][*y] == '*') {
					winning_message(1);
//					losing_message(2);
				}
				break;
			case 77:  // right key
				if (maze[*x][*y + 1] == 'X') {
					winning_message(2);
//					losing_message(1);
				}
				if (maze[*x][*y + 1] != '#') {
					maze[*x][*y] = ' ';
					*y += 1;
					maze[*x][*y] = '2';
				}
				if (maze[*x][*y + 1] == '*') {
					winning_message(1);
//					losing_message(2);
				}
				break;
			default:
				break;
		}
	}
//    usleep(200);
}

void move_player_simultaneous(int *x1, int *y1,int *x2, int *y2, int rows, int cols, char (*maze)[cols]) {
	// checking for key presses
	char move = getch();
	switch (move) {
		// player 1's movement
		case 'w':
			if(maze[*x1 - 1][*y1] == 'X') {
//				losing_message(2);
				winning_message(1);
			} else if(maze[*x1 - 1][*y1] == '*') {
//				losing_message(1);
				winning_message(2);
			} else if (maze[*x1 - 1][*y1] != '#') {
				maze[*x1][*y1] = ' ';
				*x1 -= 1;
				maze[*x1][*y1] = '1';
			}
			break;
		case 'a':
			if(maze[*x1][*y1 - 1] == 'X') {
//				losing_message(2);
				winning_message(1);
			} else if(maze[*x1][*y1 - 1] == '*') {
//				losing_message(1);
				winning_message(2);
			} else if (maze[*x1][*y1 - 1] != '#') {
				maze[*x1][*y1] = ' ';
				*y1 -= 1;
				maze[*x1][*y1] = '1';
			}
			break;
		case 's':
			if(maze[*x1 + 1][*y1] == 'X') {
//				losing_message(2);
				winning_message(1);
			} else if(maze[*x1 + 1][*y1] == '*') {
//				losing_message(1);
				winning_message(2);
			} else if (maze[*x1 + 1][*y1] != '#') {
				maze[*x1][*y1] = ' ';
				*x1 += 1;
				maze[*x1][*y1] = '1';
			}
			break;
		case 'd':
			if(maze[*x1][*y1 + 1] == 'X') {
//				losing_message(2);
				winning_message(1);
			} else if(maze[*x1][*y1 + 1] == '*') {
//				losing_message(1);
				winning_message(2);
			} else if (maze[*x1][*y1 + 1] != '#') {
				maze[*x1][*y1] = ' ';
				*y1 += 1;
				maze[*x1][*y1] = '1';
			}
			break;
		// player 2's movement
		case 72:  // up key
			if(maze[*x2 - 1][*y2] == 'X') {
//				losing_message(1);
				winning_message(2);
			} else if(maze[*x2 - 1][*y2] == '*') {
//				losing_message(2);
				winning_message(1);
			} else if (maze[*x2 - 1][*y2] != '#') {
				maze[*x2][*y2] = ' ';
				*x2 -= 1;
				maze[*x2][*y2] = '2';
			}
			break;
		case 75:  // left key
			if(maze[*x2][*y2 - 1] == 'X') {
//				losing_message(1);
				winning_message(2);
			} else if(maze[*x2][*y2 - 1] == '*') {
//				losing_message(2);
				winning_message(1);
			} else if (maze[*x2][*y2 - 1] != '#') {
				maze[*x2][*y2] = ' ';
				*y2 -= 1;
				maze[*x2][*y2] = '2';
			}
			break;
		case 80:  // down key
			if (maze[*x2 + 1][*y2] == 'X') {
//				losing_message(1);
				winning_message(2);
			} else if (maze[*x2 + 1][*y2] == '*') {
//				losing_message(2);
				winning_message(1);
			} else if (maze[*x2 + 1][*y2] != '#') {
				maze[*x2][*y2] = ' ';
				*x2 += 1;
				maze[*x2][*y2] = '2';
			}
			break;
		case 77:  // right key
			if (maze[*x2][*y2 + 1] == 'X') {
//				losing_message(1);
				winning_message(2);
			} else if (maze[*x2][*y2 + 1] == '*') {
//				losing_message(2);
				winning_message(1);
			} else if (maze[*x2][*y2 + 1] != '#') {
				maze[*x2][*y2] = ' ';
				*y2 += 1;
				maze[*x2][*y2] = '2';
			}
			break;
		default:
			break;
	}
//    usleep(200);
}

void print_maze(int rows, int cols, char maze[rows][cols]) {
	system("cls");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
}

void select_maze(char chosen_maze) {
	// initializing maze arrays and player initials (i.e. names)
	// determining 'goal' position
	char goal_pos;
	char p1, p2;

	switch (chosen_maze) {
		case 'e': {
			char maze_E[12][14] = {
				{'#', '1', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
				{'#', ' ', 'X', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
				{'#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
				{'#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
				{'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#'},
				{'#', ' ', ' ', ' ', '#', '#', 'X', '#', '#', ' ', ' ', ' ', '#', '#'},
				{'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#'},
				{'#', ' ', '#', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', '#'},
				{'#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
				{'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#'},
				{'#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', '#'},
				{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '2', '#'}
			};
			goal_pos = 'X';
			system("cls");
			printf("\nYou have " CYAN BOLD "30 seconds" RESET " to clear this maze. Good luck!\n");
			delay(3);
			system("cls");
			maze_traversal(12, 14, maze_E, goal_pos, 30);
			break;
		}
		case 'm': {
			char maze_M[14][16] = {
				{'#', '1', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
				{'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', '#', '#'},
				{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', '#'},
				{'#', '#', '#', '#', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
				{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
				{'#', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#'},
				{'#', ' ', ' ', '#', '#', '#', '#', 'X', '#', ' ', ' ', '#', '#', ' ', ' ', '#'},
				{'#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
				{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#'},
				{'#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
				{'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
				{'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#'},
				{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
				{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '2', '#'}
			};
			goal_pos = 'X';
			system("cls");
			printf("\nYou have " CYAN BOLD "25 seconds" RESET" to clear this maze. Good luck!\n");
			delay(3);
			system("cls");
			maze_traversal(14, 16, maze_M, goal_pos, 25);
			break;
		}
		case 'h': {
			char maze_H[16][18] = {
				{'#', '1', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
				{'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#'},
				{'#', '#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#'},
				{'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#'},
				{'#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
				{'#', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#'},
				{'#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#'},
				{'#', ' ', ' ', ' ', '#', '#', '#', '#', 'X', '#', '#', '#', ' ', ' ', ' ', ' ', '#', '#'},
				{'#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#'},
				{'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
				{'#', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#'},
				{'#', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
				{'#', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#'},
				{'#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#'},
				{'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
				{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '2', '#'}
			};
			goal_pos = 'X';
			system("cls");
			printf("\nYou have " CYAN BOLD "20 seconds" RESET " to clear this maze. Good luck!\n");
			delay(3);
			system("cls");
			maze_traversal(16, 18, maze_H, goal_pos, 20);
			break;
		}
		case 'c': {
			system("cls");
			printf(CYAN BOLD "\n\t\t\t\t\t\t ____  _   _  ____ _____ ___  __  __   __  __    _   _____ _____ \n");
			printf("\t\t\t\t\t\t|___ \\| | | ||___ |_   _/ _ \\|  \\/  | |  \\/  |  / \\  \\  __|____ |\n");
			printf("\t\t\t\t\t\t    | | | | |/ ___/ | || | | | |\\/| | | |\\/| | / _ \\  \\ \\   |_  |\n");
			printf("\t\t\t\t\t\t ___| | |_| | (___  | || |_| | |  | | | |  | |/ ___ \\ _\\ \\ ___| |\n");
			printf("\t\t\t\t\t\t|____/ \\___/ \\____| |_| \\___/|_|  |_| |_|  |_/_/   \\_|____|_____|\n" RESET);

			int rows, cols, goal_x, goal_y;
			int x1, y1;
			int x2, y2;
			int timelim;
			printf("\n\tEnter the number of rows (x): ");
			scanf("%d", &rows);
			printf("\n\tEnter the number of columns (y): ");
			scanf("%d", &cols);
			printf("\n\tEnter your goal position (x, y): ");
			scanf("%d %d", &goal_x, &goal_y);

			printf("\n\tEnter a time limit (in seconds) for your maze: ");
			scanf("%d", &timelim);

			char maze_C[rows][cols];

			printf("\n");
			printf(CYAN BOLD "\n\tPlease make sure that Player 1 (situated at [1, 2]) and Player 2 (situated at [%d, %d]) have Free Spaces (' ')" RESET ".\n", rows, cols - 1);

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					printf("\t\tEnter a " CYAN BOLD "WALL ('#') " RESET "or " MAGENTA BOLD "FREE SPACE (' ') " RESET "for (%d, %d): ", i + 1, j + 1);
					char part = getch();
					if ((part != '#') || (part != ' ')) {
						printf("\n\n\t\t" RED BOLD "WALL ('#') or FREE SPACE (' ') not detected" RESET ".\n\t\tRetry please.\n");
						printf(YELLOW BOLD "\n\t\t\t\t\t\t  ____ _____ _____ ______   _____ _   _ ____              \n");
						printf("\t\t\t\t\t\t / _  |____ |_   _/ _  \\ \\ / |_ _| | / |___ \\             \n");
						printf("\t\t\t\t\t\t| (_| | |_  | | || (_| |\\ V / | || |/  |_  | |            \n");
						printf("\t\t\t\t\t\t > _  |___| | | | > _  | | |  | ||  /| | |_| |  _   _   _ \n");
						printf("\t\t\t\t\t\t/_/ |_|_____| |_|/_/ |_| |_| |___|_/ |_|____/  (_) (_) (_)\n" RESET);

						delay(3);
						main();
					}
				}
			}
			if (maze_C[0][1] == ' ' && maze_C[rows][cols - 1] == ' ') {
				maze_C[0][1] = '1';
				maze_C[rows][cols - 1] = '2';
			}
			char goal_pos = maze_C[goal_x - 1][goal_y - 1];
			if (goal_pos != 'X') {
				printf("Uh Oh! " RED BOLD "No goal 'X' found at suggested goal position." RESET "\nPlease re-enter your custom maze!\n");
				printf(YELLOW BOLD "\n\t\t\t\t\t\t _______  _____ _____ ___ _   _ ____    _____ _   _ _____   ____    _    __  __ _____ _ \n");
				printf("\t\t\t\t\t\t|____ \\ \\/ |_ _|_   _|_ _| | / |___ \\  |_   _| | | |____ | |___ \\  / \\  |  \\/  |____ | |\n");
				printf("\t\t\t\t\t\t  |_  |\\  / | |  | |  | || |/  |_  | |   | | | |_| | |_  |  _  | |/ _ \\ | |\\/| | |_  | |\n");
				printf("\t\t\t\t\t\t ___| |/  \\ | |  | |  | ||  /| | |_| |   | | |  _  |___| | | |_| / ___ \\| |  | |___| |_|\n");
				printf("\t\t\t\t\t\t|_____/_/\\_|___| |_| |___|_/ |_|____/    |_| |_| |_|_____| |____/_/   \\_|_|  |_|_____(_)\n" RESET);
				delay(3);
				main();
			}
			if ((maze_C[0][1] != ' ') || (maze_C[rows - 1][cols - 2] != ' ')) {
				printf("Oops. " RED BOLD "No Free Spaces (' ') detected for the players to move" RESET ".\nPlease re-enter your custom maze!\n");
				printf(YELLOW BOLD "\n\t _______  _____ _____ ___ _   _ ____    _____ _   _ _____   ____    _    __  __ _____ _ \n");
				printf("\t|____ \\ \\/ |_ _|_   _|_ _| | / |___ \\  |_   _| | | |____ | |___ \\  / \\  |  \\/  |____ | |\n");
				printf("\t  |_  |\\  / | |  | |  | || |/  |_  | |   | | | |_| | |_  |  _  | |/ _ \\ | |\\/| | |_  | |\n");
				printf("\t ___| |/  \\ | |  | |  | ||  /| | |_| |   | | |  _  |___| | | |_| / ___ \\| |  | |___| |_|\n");
				printf("\t|_____/_/\\_|___| |_| |___|_/ |_|____/    |_| |_| |_|_____| |____/_/   \\_|_|  |_|_____(_)\n");
				printf("\t                                                                                        \n" RESET);
				delay(3);
				main();
			} else {
				system("cls");
				maze_traversal(rows, cols, maze_C, goal_pos, timelim);
			}
			break;
		}
		default:
			printf("\n\t\t\t\t\t\t\tInvalid maze difficulty chosen. " RED "Please retry.\n" RESET);
			printf(YELLOW BOLD "\n\t\t\t\t\t\t  ____ _____ _____ ______   _____ _   _ ____              \n");
			printf("\t\t\t\t\t\t / _  |____ |_   _/ _  \\ \\ / |_ _| | / |___ \\             \n");
			printf("\t\t\t\t\t\t| (_| | |_  | | || (_| |\\ V / | || |/  |_  | |            \n");
			printf("\t\t\t\t\t\t > _  |___| | | | > _  | | |  | ||  /| | |_| |  _   _   _ \n");
			printf("\t\t\t\t\t\t/_/ |_|_____| |_|/_/ |_| |_| |___|_/ |_|____/  (_) (_) (_)\n" RESET);

			delay(3);
			main();
			break;
	}
}

int menu() {
	// title screen
	// system("clear");
	system("cls");

	int selectedOption = 1;
	char key;

	do {
		menuDisplay(selectedOption);

		key = getch();
		switch (key) {
			case 72:
				if (selectedOption > 1) {
					selectedOption--;
				}
				break;
			case 80:
				if (selectedOption < 3) {
					selectedOption++;
				}
				break;
		}
	} while (key != 13);

	system("cls");

	switch(selectedOption) {
		case 1: // start game
			system("cls");

			printf(CYAN BOLD "\n\t\t\t\t  ____ _____     _ _____ ____ _____    ____ ___ _____ _____ ___ ____  _   _    _ _______   __\n");
			printf("\t\t\t\t |___ |____ |   | |____ |___ |_   _|  / _  |_ _|___  |___  |_ _|___ \\| | | |  | |_   _\\ \\ / /\n");
			printf("\t\t\t\t / ___/ |_  |   | | |_  |   | || |   | | | || |   _| |  _| || |    | | | | |  | | | |  \\ V / \n");
			printf("\t\t\t\t| (___ ___| |___| |___| |___| || |   | |_| || |  |_  | |_  || | ___| | |_| ___| | | |   | |  \n");
			printf("\t\t\t\t \\____|_____|_____|_____|____/ |_|    \\____|___|   |_|   |_|___|____/ \\___|_____| |_|   |_|  \n");
			printf("\t\t\t\t                                                                                             \n" RESET);
			printf("\n");
			printf("\n");

			char choice;
			while(1) {
				printf("\tEnter choice...\n\n");
				printf("\tE - easy\n");
				printf("\tM - medium\n");
				printf("\tH - hard\n");
				printf("\tC - custom\n\n\t");
				choice = getch();
				if (choice =='e' || choice =='m' || choice =='h' || choice =='c') {
					break;
				} else {
					system("cls");
					break;
				}
			}
			select_maze(choice);
			break;
		case 2: // tutorial
			system("cls");

			printf(GREEN BOLD "\n\t\t\t\t _   _  _____        __  _____ ___     ____     _    _ __   __\n");
			printf("\t\t\t\t| | | |/ _ \\ \\      / / |_   _/ _ \\   / _  |   | |  / \\\\ \\ / /\n");
			printf("\t\t\t\t| |_| | | | \\ \\ /\\ / /    | || | | | | (_| |   | | / _ \\\\ V / \n");
			printf("\t\t\t\t|  _  | |_| |\\ V  V /     | || |_| |  \\__  |___| |/ ___ \\| |  \n");
			printf("\t\t\t\t|_| |_|\\___/  \\_/\\_/      |_| \\___/      |_|_____/_/   \\_|_|  \n");
			printf("\t\t\t\t                                                              \n" RESET);
			printf("\n\n");

			printf(" Welcome to the turn-based, time constrained maze: the " BOLD CYAN "Time " RESET BOLD MAGENTA "Warp " BOLD YELLOW "Labyrinth!" RESET);
			printf("\n First, select a difficulty from either Easy, Medium, Hard or Custom.");
			printf("\n Custom difficulty allows you to make your own maze and assign custom goal posts for the two players.");
			printf("\n For all modes there is a " YELLOW BOLD "time limit" RESET ". Again, for custom mode you can assign a time limit by yourself.");
			printf("\n If the maze is not compeleted within the given limit, obstacles are added randomly to the course as " RED BOLD "penalty" RESET ".");
			printf("\n");
			printf("\n");

			printf(BLUE BOLD "\n Player '1' Controls (W-A-S-D):" RESET);
			printf("\n W - move up");
			printf("\n A - move left");
			printf("\n S - move down");
			printf("\n D - move right");
			printf("\n");

			printf(MAGENTA BOLD "\n Player '2' Controls (Arrow Keys):" RESET);
			printf("\n Up arrow key - move up");
			printf("\n Left arrow key - move left");
			printf("\n Down arrow key - move down");
			printf("\n Right arrow key - move right");
			printf("\n");

			printf(CYAN BOLD "\n\t__        _____ _   _ _   _ ___ _   _ ____    ____   ___  _   _  ____ ___ _____ ___ ___  _   _  ____ \n");
			printf("\t\\ \\      / |_ _| | / | | / |_ _| | / |___ \\  |___ \\ / _ \\| | / |/ _  |_ _|_   _|_ _/ _ \\| | / ||___ \\\n");
			printf("\t \\ \\ /\\ / / | || |/  | |/  || || |/  |_  | |     | | | | | |/  | | | || |  | |  | | | | | |/  |/ ___/\n");
			printf("\t  \\ V  V /  | ||  /| |  /| || ||  /| | |_| |  ___| | |_| |  /| | |_| || |  | |  | | |_| |  /| | (___ \n");
			printf("\t   \\_/\\_/  |___|_/ |_|_/ |_|___|_/ |_|____/  |____/ \\___/|_/ |_|\\____|___| |_| |___\\___/|_/ |_|\\____|\n");
			printf("\t                                                                                                     \n" RESET);
			printf("\n");

			printf("\n A player must reach the goal [" GREEN " X " RESET "] before their time is up.");
			printf("\n If the time limit exceeds, the players need to survive the obstacles that start to come up \n (i.e. they shouldn't come in contact with them).");
			printf("\n Failure to get to the goal results in that specific player losing the game!");
			printf(CORAL"\n Good luck!~"RESET);

			printf(YELLOW BOLD "\n\n Press '0' to RETURN to MAIN MENU\n" RESET);
			char input = getch();
			if(input == '0') {
				main();
			}
			break;
		case 3: // exit sequence
			system("cls");

			printf(RED BOLD "\n\t\t\t\t _______  _____ _____ ___ _   _ ____    _____ _   _ _____   ____    _    __  __ _____ _ \n");
			printf("\t\t\t\t|____ \\ \\/ |_ _|_   _|_ _| | / |___ \\  |_   _| | | |____ | |___ \\  / \\  |  \\/  |____ | |\n");
			printf("\t\t\t\t  |_  |\\  / | |  | |  | || |/  |_  | |   | | | |_| | |_  |  _  | |/ _ \\ | |\\/| | |_  | |\n");
			printf("\t\t\t\t ___| |/  \\ | |  | |  | ||  /| | |_| |   | | |  _  |___| | | |_| / ___ \\| |  | |___| |_|\n");
			printf("\t\t\t\t|_____/_/\\_|___| |_| |___|_/ |_|____/    |_| |_| |_|_____| |____/_/   \\_|_|  |_|_____(_)\n");
			printf("\t\t\t\t                                                                                        \n" RESET);

			delay(2);
			HWND myConsole = GetConsoleWindow(); // gets window identifier
			ShowWindow(myConsole, 0); // closes console entirely
			break;
		default:
			system("cls");

			printf("\t\t\tError! Please make sure you've chosen an option among 1, 2 or 3. Try again.\n\n");
			printf(YELLOW BOLD "\n\t\t\t\t  ____ _____ _____ ______   _____ _   _ ____              \n");
			printf("\t\t\t\t / _  |____ |_   _/ _  \\ \\ / |_ _| | / |___ \\             \n");
			printf("\t\t\t\t| (_| | |_  | | || (_| |\\ V / | || |/  |_  | |            \n");
			printf("\t\t\t\t > _  |___| | | | > _  | | |  | ||  /| | |_| |  _   _   _ \n");
			printf("\t\t\t\t/_/ |_|_____| |_|/_/ |_| |_| |___|_/ |_|____/  (_) (_) (_)\n");
			printf("\t\t\t\t                                                          \n" RESET);

			delay(1);
			main();
			break;
	}
	return 0;
}

void menuDisplay(int selectedOption) {
	system("cls");

	printf(MAGENTA BOLD "\n\n\t\t\t _____ ___ __  __ _____  __        ___     ____  ____       _    _    ______   ______ ___ _   _ _____ _   _ \n");
	printf("\t\t\t|_   _|_ _|  \\/  |____ | \\ \\      / / \\   / _  |/ _  |     | |  / \\  ( __ \\ \\ / / _  |_ _| | / |_   _| | | |\n");
	printf("\t\t\t  | |  | || |\\/| | |_  |  \\ \\ /\\ / / _ \\ | (_| | (_| |     | | / _ \\ / _  |\\ V | (_| || || |/  | | | | |_| |\n");
	printf("\t\t\t  | |  | || |  | |___| |   \\ V  V / ___ \\ > _  |\\__  |  ___| |/ ___ | (_| | | | > _  || ||  /| | | | |  _  |\n");
	printf("\t\t\t  |_| |___|_|  |_|_____|    \\_/\\_/_/   \\_/_/ |_|   |_| |_____/_/   \\_\\____| |_|/_/ |_|___|_/ |_| |_| |_| |_|\n" RESET);

	printf("\n");
	printf("\n");
	printf("\t\t\t\t\t\t|           |  |  |  |                 |  |  |     |  |         |\n");
	printf("\t\t\t\t\t\t+--+--+--+  +--+  +  +--+--+--+--+--+  +  +  +--+--+--+--+--+   +\n");
	printf(GREEN BOLD "\t\t\t\t\t\tSTART ->" RESET "          |                 |     |              | " BOLD RED "-> END\n" RESET);
	printf("\t\t\t\t\t\t+-----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+\n");

	gotoxy(19+54, 16);
	printf(CORAL"M A I N  M E N U\n"RESET);
	int i;

	for (i = 1; i <= 3; ++i) {

		if (i == selectedOption) {

			printf(GOLD);
		} else {
			printf("   ");
		}

		switch (i) {
			case 1:
				gotoxy(19+50, 18);
				printf("1. S T A R T  G A M E  !");
				break;
			case 2:
				gotoxy(19+50, 19);
				printf("2. H O W  T O  P L A Y ?");
				break;
			case 3:
				gotoxy(19+56, 20);
				printf("3. E X I T !");
				break;
		}

		printf(RESET);
	}
}
