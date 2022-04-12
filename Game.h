#pragma once

#include <stdlib.h>
#include <cmath>
#include <time.h>

#define BOARD_SIZE 9

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

class Game
{
private:
	int gameFrameHeight_ = 0; // h of gameFrame
	int gameFrameWidth_ = 0; // w of gameFrame
	int turnFrameHeight_ = 0; // h of turnFrame
	int turnFrameWidth_ = 0; // w of turnFrame
	int board_[BOARD_SIZE] = { 4, 7, 8, 9}; // game board
	bool chosenCells_[BOARD_SIZE]{ false, false, false, false}; // to check if selected cell in array is empty or not
	int numsId_[2] = {-1, -1}; // keep indicies of 2 selected numbers
	int curSelNumSum_ = 0; // selected num sum
	int turn_ = 0; // game turn
	bool human_ = false, ai_ = false; // players
	int humanPoints_ = 0, aiPoints_ = 0; // players points

public:
	Game(int gameFrameWidth, int gameFrameHeight, int turnFrameWidth, int turnFrameHeight);// constructor

	void startGame(); // randomly choose games string numbers and clear chosen cells

	void displayCarcass(Graphics^ grp, int cellW); // display form of the array [][][][][]...
	void displayCurrentState(Graphics^ grp, int cellW, int txtPosH); // display game string
	void displayGame(Graphics^ grp); // fully display visual representation of the game
	void displayChosenNumberHuman(Graphics^ grp, PictureBox^ picBox, int mouseX); // displays human chosen number
	void displayChosenNumberAI(Graphics^ grp); // displays ai chosen number
	void displayCurrentTurnState(Graphics^ grp); // diplay current state of the game

	void redrawDeselectGameFrame(Graphics^ grp, PictureBox^ picBox, Brush^ brush, int cellW); // redraw frame after number was deselected
	void redrawGameFrame(Graphics^ grp, PictureBox^ picBox); // redraw frame

	void clearChosenCells(); // clear chosen cells
	void randomizeGameString(); // randomize gameString

	bool isSelectedNumValid(int index); // check if the selected number is near previously selected one

	void changeTurn(Graphics^ grp, PictureBox^ picBox); // next turn
	void changeField(); // rearange array(shift values in the array) after turn ended 
	bool checkSelectedNums(); // check if 2 numbers were selected

	void calculate(); // calculate players choise sum and incease points
	void increasePoints(int numericVal); // increase players point after turn
	int getTurn(); // get current turn

	bool gameEnd(); // check turn == BOARD_SIZE - 1, and that says about the end of the game

	void setHuman(bool human); // set start player as human
	void setAI(bool AI);// set start player as AI
	bool getHuman(); // to check if it is human turn
	bool getAI(); // to check if it is AI turn

	void showWinner(Graphics^ grp); // show winner on screen when game ends

	void aiBestMove(); // ai make move, when it is his turn (using minimax(...))
	int minimax(int board[], int selNum1Id, int selNum2Id, int turn, bool isMaximizing, int pl1Score, int pl2Score, int maxDepth);
	// ai use minimax(...) algorithm to select best possible move

	void rusRules(Graphics^ grp, int Width, int Height);
	void engRules(Graphics^ grp, int Width, int Height);
	void lvRules(Graphics^ grp, int Width, int Height);
};

extern Game* game;

