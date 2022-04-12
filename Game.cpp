#include "Game.h"

Game* game;

Game::Game(int gameFrameWidth, int gameFrameHeight, int turnFrameWidth, int turnFrameHeight) {

	gameFrameWidth_ = gameFrameWidth;
	gameFrameHeight_ = gameFrameHeight;
	turnFrameWidth_ = turnFrameWidth;
	turnFrameHeight_ = turnFrameHeight;

};

void Game::startGame() {

	turn_ = 0;
	humanPoints_ = 0;
	aiPoints_ = 0;
	clearChosenCells();
	randomizeGameString();

};

void Game::displayCarcass(Graphics^ grp, int cellW) {

	Pen pen(Color::Black, 4);

	grp->DrawLine(% pen, 0, 0, gameFrameWidth_, 0); // right-up to left-up
	grp->DrawLine(% pen, 0, gameFrameHeight_ - 3, gameFrameWidth_ - 3, gameFrameHeight_ - 3); // right-bottom to left-bottom
	grp->DrawLine(% pen, 0, 0, 0, gameFrameHeight_); // right-up to right-bottom
	grp->DrawLine(% pen, gameFrameWidth_ - 3, 0, gameFrameWidth_ - 3, gameFrameHeight_); // left-up to left-bottom

	for (int i = 0; i < BOARD_SIZE - 1; i++) {
		grp->DrawLine(% pen, (cellW * i) + cellW, 0, (cellW * i) + cellW, gameFrameHeight_);
	}// draw 3 lines form up to bottom

};

void Game::displayCurrentState(Graphics^ grp, int cellW, int txtPosH) {

	SolidBrush brush(Color::Black);
	Font font(FontFamily::GenericSansSerif, gameFrameHeight_ / 3);

	StringFormat^ strFormat = gcnew StringFormat();
	strFormat->LineAlignment = StringAlignment::Center;
	strFormat->Alignment = StringAlignment::Center;

	for (int i = 0; i < BOARD_SIZE - turn_; i++) {
		grp->DrawString(board_[i].ToString(), % font, % brush, (cellW * i) + cellW / 2, txtPosH, strFormat);
	}// draw array content

};

void Game::displayGame(Graphics^ grp) {

	int cellW = gameFrameWidth_ / (BOARD_SIZE - turn_); //dividing frame by how many elements there are in array
	int txtPosH = gameFrameHeight_ / 2; // y-position, where elements will be drawn

	displayCarcass(grp, cellW);
	displayCurrentState(grp, cellW, txtPosH);

};

void Game::displayChosenNumberHuman(Graphics^ grp, PictureBox^ picBox, int mouseX) {

	SolidBrush^ brushHuman = gcnew SolidBrush(Color::FromArgb(90, 0, 255, 0));
	SolidBrush^ brushAI = gcnew SolidBrush(Color::FromArgb(90, 255, 0, 0));

	int cellW = gameFrameWidth_ / (BOARD_SIZE - turn_);
	int i = floor(mouseX / cellW);

	if (chosenCells_[i] == false) {
		if (isSelectedNumValid(i)) {
			chosenCells_[i] = true;
			if (human_) {
				grp->FillRectangle(brushHuman, cellW * i, 0, cellW, gameFrameHeight_);
			}
			if (ai_) {
				grp->FillRectangle(brushAI, cellW * i, 0, cellW, gameFrameHeight_);
			}
		}
	}
	else {
		chosenCells_[i] = false;

		for (int j = 0; j < 2; j++) {
			if (numsId_[j] == i) {
				numsId_[j] = -1;
			}
		}
		if (human_) {
			redrawDeselectGameFrame(grp, picBox, brushHuman, cellW);
		}
		if (ai_) {
			redrawDeselectGameFrame(grp, picBox, brushAI, cellW);
		}

	}

};

void Game::displayChosenNumberAI(Graphics^ grp) {
	SolidBrush^ brushAI = gcnew SolidBrush(Color::FromArgb(90, 255, 0, 0));

	int cellW = gameFrameWidth_ / (BOARD_SIZE - turn_);
	chosenCells_[numsId_[0]] = true;
	chosenCells_[numsId_[1]] = true;
	grp->FillRectangle(brushAI, cellW * numsId_[0], 0, cellW, gameFrameHeight_);
	grp->FillRectangle(brushAI, cellW * numsId_[1], 0, cellW, gameFrameHeight_);

};

void Game::redrawGameFrame(Graphics^ grp, PictureBox^ picBox) {

	grp->Clear(picBox->BackColor);
	displayGame(grp);

};

void Game::redrawDeselectGameFrame(Graphics^ grp, PictureBox^ picBox, Brush^ brush, int cellW) {

	grp->Clear(picBox->BackColor);

	displayGame(grp);

	for (int j = 0; j < BOARD_SIZE - turn_; j++) if (chosenCells_[j]) {
		grp->FillRectangle(brush, cellW * j, 0, cellW, gameFrameHeight_);
	}

};

void Game::clearChosenCells() {

	for (int i = 0; i < BOARD_SIZE; i++) {
		chosenCells_[i] = false;
	} // clearing chosen cells state 

};

void Game::randomizeGameString() {

	for (int i = 0; i < BOARD_SIZE; i++) {
		board_[i] = rand() % 10;
	}

};

bool Game::isSelectedNumValid(int index) {
	
	if (numsId_[0] > -1 && numsId_[1] > -1) { // check if there already is two selected nums
		return false;
	}

	if (numsId_[0] <= -1 && numsId_[1] <= -1) { // check if every numsId place is empty, then write selected to first numsId
		numsId_[0] = index;
		return true;
	}

	if (numsId_[0] <= -1 && numsId_[1] > -1) { // check for available spot in numsId_[0]
		if (numsId_[1] == (index - 1) || numsId_[1] == (index + 1)) {
			numsId_[0] = index;
			return true;
		}
	}

	if (numsId_[0] > -1 && numsId_[1] <= -1) { // check for available spot in numsId_[1]
		if (numsId_[0] == (index - 1) || numsId_[0] == (index + 1)) {
			numsId_[1] = index;
			return true;
		}
	}

	return false;

};

void Game::changeTurn(Graphics^ grp, PictureBox^ picBox) {

	if (turn_ < BOARD_SIZE) {
		turn_++;
	} // inrease turn
	numsId_[0] = -1;
	numsId_[1] = -1; // clear slected nums
	clearChosenCells(); // clear 
	redrawGameFrame(grp, picBox);

	if (human_) {

		ai_ = true;
		human_ = false;

	}else {

		human_ = true;
		ai_ = false;

	}

};

bool Game::checkSelectedNums() {

	return (numsId_[0] > -1 && numsId_[1] > -1);

};

void Game::calculate() {

	curSelNumSum_ = board_[numsId_[0]] + board_[numsId_[1]];

	increasePoints(curSelNumSum_);
		
};

void Game::changeField() {

	int changeStarted = 0; // index where to start to shift array

	for (int i = 0; i < BOARD_SIZE - turn_; i++) {

		if (numsId_[0] < numsId_[1]) {
			if (numsId_[0] == i) {
				board_[i] = curSelNumSum_;
				changeStarted = numsId_[1];
			} // num sum is written to lesser index
		}
		else {
			if (numsId_[1] == i) {
				board_[i] = curSelNumSum_;
				changeStarted = numsId_[0];
			}// num sum is written to lesser index
		}

	}

	for (int i = changeStarted; i < BOARD_SIZE - turn_ - 1; i++) {
		board_[i] = board_[i + 1];
	}

};

void Game::increasePoints(int receivedSum) {

	if (receivedSum % 2 == 0) { // if sum is even, then player who had done move +1 point, and to another +2
		if (human_) {
			humanPoints_ += 1;
			aiPoints_ += 2;
		}
		else {
			aiPoints_ += 1;
			humanPoints_ += 2;
		}
	}
	else {
		if (human_) {
			humanPoints_ += 2;
			aiPoints_ += 1;
		}
		else {
			aiPoints_ += 2;
			humanPoints_ += 1;
		}
	}

};

int Game::getTurn() {

	return turn_;

};

bool Game::gameEnd() {

	return game->getTurn() == (BOARD_SIZE - 1);

};

void Game::setHuman(bool human) {

	human_ = human;

};

void Game::setAI(bool AI) {

	ai_ = AI;

};

bool Game::getHuman() {

	return human_;

};

bool Game::getAI() {

	return ai_;

};

void Game::displayCurrentTurnState(Graphics^ grp) {

	SolidBrush brush(Color::Black);
	Font font(FontFamily::GenericSansSerif, 14);

	StringFormat^ strFormat = gcnew StringFormat();
	strFormat->LineAlignment = StringAlignment::Center;
	strFormat->Alignment = StringAlignment::Center;

	String^ currentState = gcnew String(String::Format(
		"Current state of the game: \nHuman points: {0} \nAI points: {1}",
		humanPoints_, aiPoints_
		));
	int curStLen = currentState->Length;

	if (human_) {
		String^ humanTurn = gcnew String(String::Format("Human selected numbers: {0}, {1}", board_[numsId_[0]], board_[numsId_[1]]));
		int len = humanTurn->Length;
		grp->DrawString(humanTurn, % font, % brush, turnFrameWidth_ / len + turnFrameWidth_ / 2 - 14, 30, strFormat);
		grp->DrawString(currentState, % font, % brush, turnFrameWidth_ / curStLen + turnFrameWidth_ / 2 - 5, 80, strFormat);
	}
	else {
		String^ aiTurn = gcnew String(String::Format("AI selected numbers: {0}, {1}", board_[numsId_[0]], board_[numsId_[1]]));
		int len = aiTurn->Length;
		grp->DrawString(aiTurn, % font, % brush, turnFrameWidth_ / len + turnFrameWidth_ / 2 - 14, 30, strFormat);
		grp->DrawString(currentState, % font, % brush, turnFrameWidth_ / curStLen + turnFrameWidth_ / 2 - 5, 80, strFormat);
	}

};

void Game::showWinner(Graphics^ grp) {

	SolidBrush brush(Color::FromArgb(0, 125, 0));
	Font font(FontFamily::GenericSansSerif, 14);

	StringFormat^ strFormat = gcnew StringFormat();
	strFormat->LineAlignment = StringAlignment::Center;
	strFormat->Alignment = StringAlignment::Center;

	if (humanPoints_ == aiPoints_) {
		grp->DrawString("Tie!!!", % font, % brush, turnFrameWidth_ / 6 + turnFrameWidth_ / 2 - 58, 130, strFormat);
	}
	else if (humanPoints_ < aiPoints_) {
		grp->DrawString("Human Win!!!", % font, % brush, turnFrameWidth_ / 12 + turnFrameWidth_ / 2 - 30, 130, strFormat);
	}
	else {
		grp->DrawString("Ai Win!!!", % font, % brush, turnFrameWidth_ / 9 + turnFrameWidth_ / 2 - 37, 130, strFormat);
	}

};

void Game::aiBestMove() {

	int bestScore = -10000;
	int aiBoard[BOARD_SIZE] = {};
	int bestMove[2] = {};

	for (int n = 0; n < BOARD_SIZE - turn_; n++) {
		aiBoard[n] = board_[n];	
	} 

	for (int i = 0; i < BOARD_SIZE - turn_ - 1; i++) {
		
		int score = minimax(aiBoard, i, i + 1, turn_, true, humanPoints_, aiPoints_, BOARD_SIZE);

		if (score > bestScore) {
			bestMove[0] = i;
			bestMove[1] = i + 1;
			bestScore = score;
		}

	} // pass only first possible moves to minimax(...)

	numsId_[0] = bestMove[0];
	numsId_[1] = bestMove[1];

};

int Game::minimax(int board[], int selNum1Id, int selNum2Id, int turn, bool isMaximizing, int pl1Score, int pl2Score, int maxDepth) {

	if (turn == (BOARD_SIZE - 2) || maxDepth == 0) {
		if (pl1Score < pl2Score) {
			return 1;
		}
		else if (pl1Score > pl2Score) {
			return -1;
		}
		else {
			return 0;
		}
	}// to exit from recursion, as well as to set score to move

	int aiBoard[BOARD_SIZE] = {};
	for (int i = 0; i < BOARD_SIZE; i++) {
		aiBoard[i] = board[i];
	}

	int move[2] = {};
	if (isMaximizing) { // player 1 
		int bestScore = -10000;

		move[0] = selNum1Id;
		move[1] = selNum2Id;
		int sum = aiBoard[move[0]] + aiBoard[move[1]]; // selected nums sum
		aiBoard[move[0]] = sum; // add selected nums sum to lesser index from selected nums 

		for (int i = move[1]; i < BOARD_SIZE - turn - 1; i++) {
			aiBoard[i] = aiBoard[i + 1];
		} // shift values in array starting from greater selected nums index

		for (int j = 0; j < BOARD_SIZE - turn - 2; j++) {

			int score = (sum % 2 == 0) ?
				minimax(aiBoard, j, j + 1, turn + 1, false, pl1Score + 1, pl2Score + 2, maxDepth - 1) :
				minimax(aiBoard, j, j + 1, turn + 1, false, pl1Score + 2, pl2Score + 1, maxDepth - 1)
				;

			bestScore = __max(score, bestScore);

		} // check every other possible combination of nums (passing nums indices)
		/*For example
			-- if we have array with 4 elements, then possible moves are 0-1 1-2 2-3 (indexes) -turn = 0
			 (P.S there are no reason to check for 1-0 2-1 3-2 because they are same)
			 
			-- so the next ones will be 0-1 1-2 -turn = 1 
			-- and then only 0-1 -turn = 2

			-- from that maximum index is BOARD_SIZE - 2 - turn 
			--  -2 because we already, before calling minimax(..), have done one turn

		*/

		return bestScore;

	}
	else { // player 2 
		int bestScore = 10000;

		move[0] = selNum1Id;
		move[1] = selNum2Id;
		int sum = aiBoard[move[0]] + aiBoard[move[1]];
		aiBoard[move[0]] = sum;

		for (int i = move[1]; i < BOARD_SIZE - turn - 1; i++) {
			aiBoard[i] = aiBoard[i + 1];
		}

		for (int j = 0; j < BOARD_SIZE - turn - 2; j++) {

			int score = (sum % 2 == 0) ?
				minimax(aiBoard, j, j + 1, turn + 1, true, pl1Score + 2, pl2Score + 1, maxDepth - 1) :
				minimax(aiBoard, j, j + 1, turn + 1, true, pl1Score + 1, pl2Score + 2, maxDepth - 1)
				;

			bestScore = __min(score, bestScore);

		}

		return bestScore;
	
	}

};

void Game::rusRules(Graphics^ grp, int Width, int Height) {

	SolidBrush brush(Color::Black);
	Font font(FontFamily::GenericSansSerif, 12);

	StringFormat^ strFormat = gcnew StringFormat();
	strFormat->LineAlignment = StringAlignment::Center;
	strFormat->Alignment = StringAlignment::Center;

	String^ rusR1 = gcnew String(String::Format(
		"1. {0}{1}\n",
		"При выборе 2-ух рядом стоящих чисел чья сумма образует чётное число\n",
		"игроку сделавшему ход +1 пункт, противнику +2."));
	String^ rusR2 = gcnew String(String::Format(
		"2. {0}{1}\n",
		"Игра заканчивается, когда на доске\n",
		"остаётся лишь одно число."));
	String^ rusR3 = gcnew String(String::Format(
		"3. {0}\n",
		"Побеждает тот, у кого меньшее количество очков.\n"
		));

	int len1 = rusR1->Length;
	int len2 = rusR2->Length;
	int len3 = rusR3->Length;
	grp->DrawString(rusR1, % font, % brush, Width / len1 + Width / 2, 20, strFormat);
	grp->DrawString(rusR2, % font, % brush, Width / len2 + Width / 2, 80, strFormat);
	grp->DrawString(rusR3, % font, % brush, Width / len3 + Width / 2, 140, strFormat);

};

void Game::engRules(Graphics^ grp, int Width, int Height) {

	SolidBrush brush(Color::Black);
	Font font(FontFamily::GenericSansSerif, 12);

	StringFormat^ strFormat = gcnew StringFormat();
	strFormat->LineAlignment = StringAlignment::Center;
	strFormat->Alignment = StringAlignment::Center;

	String^ engR1 = gcnew String(String::Format(
		"1. {0}{1}\n",
		"If 2 adjacent chosen numbers sum is even, then\n",
		"player who did move score +1, to opponent +2."));
	String^ engR2 = gcnew String(String::Format(
		"2. {0}{1}\n",
		"Game ends, when on board remains\n",
		"only one number."));
	String^ engR3 = gcnew String(String::Format(
		"3. {0}\n",
		"Wins player with lowest score.\n"
	));

	int len1 = engR1->Length;
	int len2 = engR2->Length;
	int len3 = engR3->Length;
	grp->DrawString(engR1, % font, % brush, Width / len1 + Width / 2, 20, strFormat);
	grp->DrawString(engR2, % font, % brush, Width / len2 + Width / 2, 80, strFormat);
	grp->DrawString(engR3, % font, % brush, Width / len3 + Width / 2, 140, strFormat);

};

void Game::lvRules(Graphics^ grp, int Width, int Height) {

	SolidBrush brush(Color::Black);
	Font font(FontFamily::GenericSansSerif, 12);

	StringFormat^ strFormat = gcnew StringFormat();
	strFormat->LineAlignment = StringAlignment::Center;
	strFormat->Alignment = StringAlignment::Center;

	String^ lvR1 = gcnew String(String::Format(
		L"1. {0}{1}\n",
		L"Ja izvēlēto 2 blakusstāvošo skaitļu summa ir pāra skaitļis, tad\n",
		L"spēlētājām, kurš izdarīja gājienu + 1 punkts, bet pretiniekam +2."));
	String^ lvR2 = gcnew String(String::Format(
		L"2. {0}{1}\n",
		L"Spēle beidzas, kad uz spēles laukā\n",
		L"palika tikai viens skaitlis."));
	String^ lvR3 = gcnew String(String::Format(
		L"3. {0}\n",
		L"Uzvar spēletājs, kuram ir mazāk punktu.\n"
	));

	int len1 = lvR1->Length;
	int len2 = lvR2->Length;
	int len3 = lvR3->Length;
	grp->DrawString(lvR1, % font, % brush, Width / len1 + Width / 2, 20, strFormat);
	grp->DrawString(lvR2, % font, % brush, Width / len2 + Width / 2, 80, strFormat);
	grp->DrawString(lvR3, % font, % brush, Width / len3 + Width / 2, 140, strFormat);

};

