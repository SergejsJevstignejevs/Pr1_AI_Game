#pragma once

#include "Game.h"
#include "ChoosePlayer.h"
#include "Rules.h"

namespace Pr1MaksIntel {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		Graphics^ grpGameFrame_ = nullptr;
		Graphics^ grpTurnFrame_ = nullptr;
	public: System::Windows::Forms::PictureBox^ turnFrame;
	private: System::Windows::Forms::Button^ rules;
	public:
		ChoosePlayer^ selPlayerForm = gcnew ChoosePlayer();
		Rules^ rulesForm = gcnew Rules();
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::PictureBox^ gameFrame;
	public: System::Windows::Forms::Button^ startGame;
	public: System::Windows::Forms::Button^ nextTurn;
	private: System::Windows::Forms::Timer^ stateTimer;
	public:
	private: System::ComponentModel::IContainer^ components;




	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->gameFrame = (gcnew System::Windows::Forms::PictureBox());
			this->startGame = (gcnew System::Windows::Forms::Button());
			this->nextTurn = (gcnew System::Windows::Forms::Button());
			this->stateTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->turnFrame = (gcnew System::Windows::Forms::PictureBox());
			this->rules = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gameFrame))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->turnFrame))->BeginInit();
			this->SuspendLayout();
			// 
			// gameFrame
			// 
			this->gameFrame->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->gameFrame->BackColor = System::Drawing::SystemColors::ControlLight;
			this->gameFrame->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->gameFrame->Location = System::Drawing::Point(12, 12);
			this->gameFrame->Name = L"gameFrame";
			this->gameFrame->Size = System::Drawing::Size(756, 150);
			this->gameFrame->TabIndex = 0;
			this->gameFrame->TabStop = false;
			this->gameFrame->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::gameFrame_MouseDown);
			// 
			// startGame
			// 
			this->startGame->Location = System::Drawing::Point(12, 168);
			this->startGame->Name = L"startGame";
			this->startGame->Size = System::Drawing::Size(100, 40);
			this->startGame->TabIndex = 1;
			this->startGame->Text = L"StartGame";
			this->startGame->UseVisualStyleBackColor = true;
			this->startGame->Click += gcnew System::EventHandler(this, &MainForm::StartGame_Click);
			// 
			// nextTurn
			// 
			this->nextTurn->Location = System::Drawing::Point(668, 168);
			this->nextTurn->Name = L"nextTurn";
			this->nextTurn->Size = System::Drawing::Size(100, 40);
			this->nextTurn->TabIndex = 2;
			this->nextTurn->Text = L"NextTurn";
			this->nextTurn->UseVisualStyleBackColor = true;
			this->nextTurn->Click += gcnew System::EventHandler(this, &MainForm::nextTurn_Click);
			// 
			// stateTimer
			// 
			this->stateTimer->Enabled = true;
			this->stateTimer->Tick += gcnew System::EventHandler(this, &MainForm::stateTimer_Tick);
			// 
			// turnFrame
			// 
			this->turnFrame->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->turnFrame->BackColor = System::Drawing::SystemColors::Info;
			this->turnFrame->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->turnFrame->Location = System::Drawing::Point(221, 168);
			this->turnFrame->Name = L"turnFrame";
			this->turnFrame->Size = System::Drawing::Size(348, 160);
			this->turnFrame->TabIndex = 3;
			this->turnFrame->TabStop = false;
			// 
			// rules
			// 
			this->rules->Location = System::Drawing::Point(693, 322);
			this->rules->Name = L"rules";
			this->rules->Size = System::Drawing::Size(75, 25);
			this->rules->TabIndex = 4;
			this->rules->Text = L"Rules";
			this->rules->UseVisualStyleBackColor = true;
			this->rules->Click += gcnew System::EventHandler(this, &MainForm::rules_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(780, 357);
			this->Controls->Add(this->rules);
			this->Controls->Add(this->turnFrame);
			this->Controls->Add(this->nextTurn);
			this->Controls->Add(this->startGame);
			this->Controls->Add(this->gameFrame);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"MainForm";
			this->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Game: Even/Uneven number";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gameFrame))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->turnFrame))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void StartGame_Click(System::Object^ sender, System::EventArgs^ e) {

		grpGameFrame_ = gameFrame->CreateGraphics();
		grpTurnFrame_ = turnFrame->CreateGraphics();
		grpGameFrame_->Clear(gameFrame->BackColor);
		grpTurnFrame_->Clear(turnFrame->BackColor);
		game->startGame();
		selPlayerForm->Show();
		game->displayGame(grpGameFrame_);
		startGame->Enabled = false;
		
	}
	private: System::Void gameFrame_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

		if (grpGameFrame_ != nullptr && !game->gameEnd() && game->getHuman()) {//&& game->getHuman()
			game->displayChosenNumberHuman(grpGameFrame_, gameFrame, e->X);
		}

	}

	private: System::Void nextTurn_Click(System::Object^ sender, System::EventArgs^ e) {

		grpTurnFrame_->Clear(turnFrame->BackColor);
		game->calculate();
		game->displayCurrentTurnState(grpTurnFrame_);
		game->changeField();
		game->changeTurn(grpGameFrame_, gameFrame);
		
	}

	private: System::Void stateTimer_Tick(System::Object^ sender, System::EventArgs^ e) {

		if (!game->checkSelectedNums()) {

			nextTurn->Enabled = false;

		}
		else {

			nextTurn->Enabled = true;

		}

		if (game->gameEnd()) {

			startGame->Enabled = true;
			game->setHuman(false);
			game->setAI(false);
			game->showWinner(grpTurnFrame_);
			/*delete grpGameFrame_;
			delete grpTurnFrame_;*/

		}

		if (game->getHuman() || game->getAI()) {

			selPlayerForm->Hide();

		}

		if (game->getAI()) {

			game->aiBestMove();
			game->displayChosenNumberAI(grpGameFrame_);
			System::Threading::Thread::Sleep(700);
			nextTurn_Click(sender, e);
		
		}

	}
	private: System::Void rules_Click(System::Object^ sender, System::EventArgs^ e) {

		rulesForm->Show();

	}
};
}

