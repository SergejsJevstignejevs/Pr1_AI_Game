#pragma once

#include "Game.h"

namespace Pr1MaksIntel {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ choosePlayer
	/// </summary>
	public ref class ChoosePlayer : public System::Windows::Forms::Form
	{
	
	public:
		ChoosePlayer(void)
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
		~ChoosePlayer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ selHuman;
	private: System::Windows::Forms::Button^ selAI;
	protected:

	protected:

	private: System::Windows::Forms::MaskedTextBox^ text;


	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->selHuman = (gcnew System::Windows::Forms::Button());
			this->selAI = (gcnew System::Windows::Forms::Button());
			this->text = (gcnew System::Windows::Forms::MaskedTextBox());
			this->SuspendLayout();
			// 
			// selHuman
			// 
			this->selHuman->Location = System::Drawing::Point(100, 75);
			this->selHuman->Name = L"selHuman";
			this->selHuman->Size = System::Drawing::Size(100, 50);
			this->selHuman->TabIndex = 0;
			this->selHuman->Text = L"Select Human";
			this->selHuman->UseVisualStyleBackColor = true;
			this->selHuman->Click += gcnew System::EventHandler(this, &ChoosePlayer::selHuman_Click);
			// 
			// selAI
			// 
			this->selAI->Location = System::Drawing::Point(100, 125);
			this->selAI->Name = L"selAI";
			this->selAI->Size = System::Drawing::Size(100, 50);
			this->selAI->TabIndex = 1;
			this->selAI->Text = L"Select AI";
			this->selAI->UseVisualStyleBackColor = true;
			this->selAI->Click += gcnew System::EventHandler(this, &ChoosePlayer::selAI_Click);
			// 
			// text
			// 
			this->text->Location = System::Drawing::Point(50, 50);
			this->text->Name = L"text";
			this->text->ReadOnly = true;
			this->text->Size = System::Drawing::Size(200, 20);
			this->text->TabIndex = 3;
			this->text->Text = L"Choose Player who will start game.";
			this->text->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// choosePlayer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(280, 257);
			this->ControlBox = false;
			this->Controls->Add(this->text);
			this->Controls->Add(this->selAI);
			this->Controls->Add(this->selHuman);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"choosePlayer";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Select Player";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void selHuman_Click(System::Object^ sender, System::EventArgs^ e) {

		game->setHuman(true);

	}

	private: System::Void selAI_Click(System::Object^ sender, System::EventArgs^ e) {

		game->setAI(true);

	}

	};
}

