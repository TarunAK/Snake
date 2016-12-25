/*************************************************************************************************************************************/
/*                                                                                                                                   */
/*   Names: Tarun Kalikivaya                                                                                                         */
/*   Application: Snake                                                                                                    	         */
/*   Description: Snake.                                    					                                                     */
/*                                                                                                                                   */
/*************************************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>

int screen = 0;

char start = 'y';
char leave = 'a';

int yPos[3199] = {25};
int xPos[3199] = {25};

char drive = 'd';
int direction = 4;

int snakeLength = 5;
int snakeScan = 10;
int plotSnake = 1;
int score = 0;

int yFood;
int xFood;

int maxY = 0;
int maxX = 0;

int checkHead = 0;

void menuScreen() {

	screen = 0;

	start_color();

	init_pair(2, 4, 0);
	init_pair(3, 7, 0);
	init_pair(4, 7, 0);
	init_pair(5, 7, 0);

	time_t t;
	time(&t);

	/**
	* This code block is the title screen of the game. This prints out the title of the game, as well as giving menu
	* options to the user.
	**/

	sleep(1);
	//attron(A_STANDOUT|COLOR_PAIR(3));
	//mvprintw(0, 0, "Cardinal Operating System, MerlinSS Command-Line Interface");
	mvprintw(0, 140, "Last Log-In On : %s", ctime(&t));
	refresh();
	//usleep(75000);
	//mvprintw(1, 0, "(C) WEC Progress 2014-2017 All Rights Reserved");
	//refresh();
	//attroff(A_STANDOUT|COLOR_PAIR(3));
	attron(A_BOLD|COLOR_PAIR(3));
	//usleep(97000);
	//mvprintw(2, 0, "Version 2.15.33NB/CSR revision 9");
	//refresh();
	//usleep(85000);
	//mvprintw(3, 0, "Program Operations Mode [ON]");
	//refresh();
	//usleep(79740);
	//mvprintw(4, 0, "Current Program: [Program (v. 80.114.111.103.114.97.109)]");
	//refresh();
	usleep(72000);

	mvprintw(17, 60, " ______     __   __     ______     __  __     ______    ");
	mvprintw(18, 60, "/\\  ___\\   /\\ '-.\\ \\   /\\  __ \\   /\\ \\/ /    /\\  ___\\   ");
	mvprintw(19, 60, "\\ \\___  \\  \\ \\ \\-.  \\  \\ \\  __ \\  \\ \\  _'-.  \\ \\  __\\   ");
	mvprintw(20, 60, " \\/\\_____\\  \\ \\_\\' \\_\\  \\ \\_\\ \\_\\  \\ \\_\\ \\_\\  \\ \\_____\\ ");
	mvprintw(21, 60, "  \\/_____/   \\/_/ \\/_/   \\/_/\\/_/   \\/_/\\/_/   \\/_____/ ");
	mvprintw(30, 80, "Start Game?");
	mvprintw(31, 82, "-> Y / Yes");
	mvprintw(32, 82, "-> N / No");
	mvprintw(37, 80, "I / Information");
	mvprintw(53, 75, "(C) TURNURAT INCORPORATED");
	attroff(A_BOLD|COLOR_PAIR(3));

	refresh();

}

void snakeControl() {

	/**
	 * This entire code block is dedicated to the move function of the Snake object. By using 'if' statements, the 
	 * user can control what direction the snake travels in. 
	 * Also within this code block is the function for detecting the Food object.
	 */

 	snakeScan = snakeLength;

	if ((drive == 'w' || drive == 'W') && direction != 3) {

		screen = 1;

		mvprintw(1,0, "               ");
		mvprintw(2,0, "               ");
		mvprintw(3,0, "               ");
		refresh();

		for (snakeScan = snakeLength; snakeScan >= 0; snakeScan--) {
			
			yPos[snakeScan + 1] = yPos[snakeScan]; // Move current segment to subsequent segement
			xPos[snakeScan + 1] = xPos[snakeScan];
		
		}
		
		usleep(9000); // Slow down up/down
		--yPos[0]; // Updates head y co-ordinate up

	}
	
	if ((drive == 's' || drive == 'S') && direction != 1) {
		
		screen = 1;
		
		mvprintw(1,0, "               ");
		mvprintw(2,0, "               ");
		mvprintw(3,0, "               ");
		refresh();
		
		for (snakeScan = snakeLength; snakeScan >= 0; snakeScan--) {
			
			yPos[snakeScan + 1] = yPos[snakeScan]; // Move current segment to subsequent segement
			xPos[snakeScan + 1] = xPos[snakeScan];
			
		}
		
		usleep(9000); // Slow down up/down
		++yPos[0]; // Updates head y co-ordinate up
		
	}


	if ((drive == 'd' || drive == 'D') && direction != 2) {

		screen = 1;

		mvprintw(1,0, "               ");
		mvprintw(2,0, "               ");
		mvprintw(3,0, "               ");
		refresh();

		for (snakeScan = snakeLength; snakeScan >= 0; snakeScan--) {
			
			yPos[snakeScan + 1] = yPos[snakeScan]; // Move current segment to subsequent segement
			xPos[snakeScan + 1] = xPos[snakeScan];
		
		}
		
		++xPos[0]; // Updates head y co-ordinate up

	}

	if ((drive == 'a' || drive == 'A') && direction != 4) {

		screen = 1;

		mvprintw(1,0, "               ");
		mvprintw(2,0, "               ");
		mvprintw(3,0, "               ");
		refresh();

		for (snakeScan = snakeLength; snakeScan >= 0; snakeScan--) {

			yPos[snakeScan + 1] = yPos[snakeScan]; // Move current segment to subsequent segement
			xPos[snakeScan + 1] = xPos[snakeScan];

		}
		
		--xPos[0]; // Updates head y co-ordinate up

	}


	if (drive == 'p' || drive == 'P') { // Pause routine

		beep();
		drive = -1;
		attron(A_STANDOUT|COLOR_PAIR(3));
		mvprintw(1, 0, "GAME PAUSED");
		attroff(A_STANDOUT|COLOR_PAIR(3));
		mvprintw(2, 0, "X / EXIT");
		mvprintw(3, 0, "WASD / RESUME");

		screen = 3;

	}
	

	refresh(); // Refresh snake print out after motion

	/**
	 * This code block below is the movement function for the Snake object.
	 */

	for (plotSnake = 0; plotSnake < snakeLength; plotSnake++) {

		attron(A_BOLD|COLOR_PAIR(4));
		mvaddstr(yPos[plotSnake], xPos[plotSnake], ".");
		attroff(A_BOLD|COLOR_PAIR(4));

	}

	refresh();
	usleep(50000);

	for (plotSnake = 0; plotSnake < snakeLength; plotSnake++) {
		
		mvaddstr(yPos[plotSnake], xPos[plotSnake], " ");
	
	}	
	
	refresh();

	/**
	 * The code block below is the detection function for the Food object. If the x and y position of the Snake  
	 * matches the x and y position of the Food, then the code block runs. The code increments the amount of 
	 * snakeLength by one, and prints out the score at location x=0 and y=0 on the screen. After doing so, 
	 * it also randomizes the location of the food, and prints it out.
	 */

 	attron(COLOR_PAIR(5));
	mvaddstr(yFood, xFood, ".");
	attroff(COLOR_PAIR(5));
	attron(COLOR_PAIR(3));
	mvprintw(0, 0, "SCORE : [%i]", score);
	refresh();
	attroff(COLOR_PAIR(3));
	
	if (score >= 0 && score <= 10) {

		if (yPos[0] == yFood && xPos[0] == xFood) {
			
			snakeLength += 5;
			score++;
			mvaddstr(yFood, xFood, " ");
			yFood = (rand() % maxY);
			xFood = (rand() % maxX);
			refresh();
			
		}
		
	}
	
	else if (score >= 11 && score <= 30) {
		
		if (yPos[0] == yFood && xPos[0] == xFood) {
			
			snakeLength += 10;
			score++;
			mvaddstr(yFood, xFood, " ");
			yFood = (rand() % maxY);
			xFood = (rand() % maxX);
			refresh();
			
		}
		
	}
	
	else if (score >= 31 && score <= 50) {
		
		if (yPos[0] == yFood && xPos[0] == xFood) {
			
			snakeLength += 20;
			score++;
			mvaddstr(yFood, xFood, " ");
			yFood = (rand() % maxY);
			xFood = (rand() % maxX);
			refresh();
			
		}
		
	}
	
	else if (score >= 51 && score <= 70) {
		
		if (yPos[0] == yFood && xPos[0] == xFood) {
			
			snakeLength += 40;
			score++;
			mvaddstr(yFood, xFood, " ");
			yFood = (rand() % maxY);
			xFood = (rand() % maxX);
			refresh();
			
		}
		
	}
	
	else if (score > 70) {
		
		if (yPos[0] == yFood && xPos[0] == xFood) {
			
			snakeLength += 80;
			score++;
			mvaddstr(yFood, xFood, " ");
			yFood = (rand() % maxY);
			xFood = (rand() % maxX);
			refresh();
			
		}
		
	}
	
	mvprintw(0, 15, "%d", snakeLength);

	attroff(COLOR_PAIR(5));

	/**
	 * The code block below is the 'lose' function for the game. If the x and y position of the head matches the
	 * x and y position of any of the snakeLength array values, the game clears the screen, prints out a 'lose'
	 * screen and exits the game.
	 */
	
	for (checkHead = 1; checkHead < snakeLength; checkHead++) {
		
		if (xPos[0] == xPos[checkHead] && yPos[0] == yPos[checkHead]) {
			
			erase();
			sleep(1);
			init_pair(1, 1, 0);
			attron(A_BOLD|A_STANDOUT|COLOR_PAIR(1));
			beep();
			mvprintw(2, 2, "CRITICAL DAMAGE!");
			refresh();
			attroff(A_STANDOUT);
			usleep(750000);
			mvprintw(3, 2, "SNAKE IS DEAD");
			refresh();
			usleep(750000);
			mvprintw(4, 2, "SCORE : [%d]", score);
			refresh();
			usleep(750000);
			mvprintw(maxY/2, maxX/2.5, "CRITICAL MISSION FAILURE");
			refresh();
			beep();
			attroff(A_BOLD|COLOR_PAIR(1));
			sleep(2.5);
			erase();
			endwin();
			exit(0);
				
		}
			
	}
	
	/**
	 * This code block allows the snake to exit the edge of the screen and come back on the opposite side.
	 */

	if (xPos[0] == maxX + 1) {

		xPos[0] = 0;

	}

	if (xPos[0] == -1) {

		xPos[0] = maxX;

	}

	if (yPos[0] == maxY + 1) {
	
		yPos[0] = 0;

	}

	if (yPos[0] == -1) {

		yPos[0] = maxY;

	}

}

int main(void) {

	initscr();
	cbreak();
	timeout(1);
	noecho();
	curs_set(0);
	start_color();
	init_pair(3, 7, 0);
	bkgd(COLOR_PAIR(3));
	
	getmaxyx(stdscr, maxY, maxX);

	srand(time(0));

	yFood = (rand() % maxY);
	xFood = (rand() % maxX);

	yPos[0] = 25;
	xPos[0] = 25;

	char currentChar;

	/**
	* This particular code block is the movement function of the snake. This code block reads the input from the user
	* and sends it to the snakeControl function for evaluation.
	**/
	
	menuScreen();

	while (1) {

		start = getch();

		if ((start == 'y' || start == 'Y') && screen != 2) {
				
			screen = 1;
			beep();
			erase();

			while (1) {
					
				snakeControl();
					
				currentChar = getch();
					
				if (currentChar != drive) {
                        
					if (currentChar != -1) {
							
						if ((currentChar == 'w' || currentChar == 'W') && (direction != 3) && (drive != 's' || drive != 'S')) {
								
							drive = 'w';
							direction = 1;
								
						}
							
						if ((currentChar == 's' || currentChar == 'S') && (direction != 1) && (drive != 'w' || drive != 'W')) {
								
							drive = 's';
							direction = 3;
							
						}

							
						if ((currentChar == 'a' || currentChar == 'A') && (direction != 4) && (drive != 'd' || drive != 'D')) {
								
							drive = 'a';
							direction = 2;
								
						}
							
							
						if ((currentChar == 'd' || currentChar == 'D') && (direction != 2) && (drive != 'a' || drive != 'A')) {
								
							drive = 'd';
							direction = 4;
							
						}
							
						if ((currentChar == 'p' || currentChar == 'P') && (direction == 1 || direction == 2 || direction == 3 || direction == 4)) {
								
							drive = 'p';
								
						}
							
						if ((currentChar == 'x' || currentChar == 'X') && drive == -1) {
								
							beep();
							erase();
							menuScreen();
							refresh();
							score = 0;
							snakeLength = 5;
							break;
								
						}
							
					}
			
				}

			}

		}

		else if ((start == 'n' || start == 'N') && screen != 2) {

			beep();
			endwin();
			exit(0);

		}

		else if (start == 'i' || start == 'I') {
				
			screen = 2;
			beep();
			erase();
			refresh();
			attron(COLOR_PAIR(3));
			mvprintw(25, 67, "Use WASD to move the snake");
			mvprintw(26, 67, "Try to eat as much food [.] as you can");
			mvprintw(27, 67, "If you need to pause the game, press P.");
			mvprintw(28, 67, "Press any movement key to resume motion.");
			mvprintw(29, 67, "Remember, don't eat yourself!");
			attron(A_STANDOUT);
			mvprintw(32, 67,"RETURN TO MENU");
			attroff(A_STANDOUT);
			mvprintw(33, 69, "-> X / Exit");
			attroff(COLOR_PAIR(2));
			
		}

		else if (start == 'x' || start == 'X') {
				
			screen = 0;
			beep();
			erase();
			menuScreen();

		}

	}

}
