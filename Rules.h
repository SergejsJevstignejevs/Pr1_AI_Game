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
	/// Сводка для Rules
	/// </summary>
	public ref class Rules : public System::Windows::Forms::Form
	{
	public:
		

	public:
		Rules(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Rules()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^ rusBtn;
	protected:
	private: System::Windows::Forms::RadioButton^ engBtn;
	private: System::Windows::Forms::RadioButton^ lvBtn;
	private: System::Windows::Forms::PictureBox^ rulesFrame;
	private: System::Windows::Forms::Button^ closeButton;
	private: System::Windows::Forms::Timer^ checkTimer;
	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->rusBtn = (gcnew System::Windows::Forms::RadioButton());
			this->engBtn = (gcnew System::Windows::Forms::RadioButton());
			this->lvBtn = (gcnew System::Windows::Forms::RadioButton());
			this->rulesFrame = (gcnew System::Windows::Forms::PictureBox());
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->checkTimer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rulesFrame))->BeginInit();
			this->SuspendLayout();
			// 
			// rusBtn
			// 
			this->rusBtn->AutoSize = true;
			this->rusBtn->Location = System::Drawing::Point(12, 12);
			this->rusBtn->Name = L"rusBtn";
			this->rusBtn->Size = System::Drawing::Size(67, 17);
			this->rusBtn->TabIndex = 0;
			this->rusBtn->TabStop = true;
			this->rusBtn->Text = L"Русский";
			this->rusBtn->UseVisualStyleBackColor = true;
			// 
			// engBtn
			// 
			this->engBtn->AutoSize = true;
			this->engBtn->Location = System::Drawing::Point(146, 12);
			this->engBtn->Name = L"engBtn";
			this->engBtn->Size = System::Drawing::Size(59, 17);
			this->engBtn->TabIndex = 1;
			this->engBtn->TabStop = true;
			this->engBtn->Text = L"English";
			this->engBtn->UseVisualStyleBackColor = true;
			// 
			// lvBtn
			// 
			this->lvBtn->AutoSize = true;
			this->lvBtn->Location = System::Drawing::Point(287, 12);
			this->lvBtn->Name = L"lvBtn";
			this->lvBtn->Size = System::Drawing::Size(65, 17);
			this->lvBtn->TabIndex = 2;
			this->lvBtn->TabStop = true;
			this->lvBtn->Text = L"Latviešu";
			this->lvBtn->UseVisualStyleBackColor = true;
			// 
			// rulesFrame
			// 
			this->rulesFrame->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->rulesFrame->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rulesFrame->Location = System::Drawing::Point(12, 35);
			this->rulesFrame->Name = L"rulesFrame";
			this->rulesFrame->Size = System::Drawing::Size(560, 200);
			this->rulesFrame->TabIndex = 3;
			this->rulesFrame->TabStop = false;
			// 
			// closeButton
			// 
			this->closeButton->Location = System::Drawing::Point(497, 241);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(75, 25);
			this->closeButton->TabIndex = 4;
			this->closeButton->Text = L"Close";
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &Rules::closeButton_Click);
			// 
			// checkTimer
			// 
			this->checkTimer->Enabled = true;
			this->checkTimer->Tick += gcnew System::EventHandler(this, &Rules::checkTimer_Tick);
			// 
			// Rules
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 276);
			this->ControlBox = false;
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->rulesFrame);
			this->Controls->Add(this->lvBtn);
			this->Controls->Add(this->engBtn);
			this->Controls->Add(this->rusBtn);
			this->Name = L"Rules";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Rules";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rulesFrame))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void closeButton_Click(System::Object^ sender, System::EventArgs^ e) {

		this->Hide();

	}
	private: System::Void checkTimer_Tick(System::Object^ sender, System::EventArgs^ e) {

		if (rusBtn->Enabled) {
			if (rusBtn->Checked) {
				rusBtn->Enabled = false;
				engBtn->Enabled = true;
				lvBtn->Enabled = true;
				Graphics^ grpRulesFrame = rulesFrame->CreateGraphics();
				grpRulesFrame->Clear(rulesFrame->BackColor);
				game->rusRules(grpRulesFrame, rulesFrame->Width, rulesFrame->Height);
				delete grpRulesFrame;
			}
		}

		if (engBtn->Enabled) {
			if (engBtn->Checked) {
				engBtn->Enabled = false;
				rusBtn->Enabled = true;
				lvBtn->Enabled = true;
				Graphics^ grpRulesFrame = rulesFrame->CreateGraphics();
				grpRulesFrame->Clear(rulesFrame->BackColor);
				game->engRules(grpRulesFrame, rulesFrame->Width, rulesFrame->Height);
				delete grpRulesFrame;
			}
		}

		if (lvBtn->Enabled) {
			if (lvBtn->Checked) {
				lvBtn->Enabled = false;
				engBtn->Enabled = true;
				rusBtn->Enabled = true;
				Graphics^ grpRulesFrame = rulesFrame->CreateGraphics();
				grpRulesFrame->Clear(rulesFrame->BackColor);
				game->lvRules(grpRulesFrame, rulesFrame->Width, rulesFrame->Height);
				delete grpRulesFrame;
			}
		}

	}
};
}

