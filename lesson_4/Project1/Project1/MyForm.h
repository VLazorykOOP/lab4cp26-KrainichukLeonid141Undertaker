#pragma once
#include "AddForm.h"

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			LoadData();
		}

	protected:
		~MyForm()
		{
			if (components) delete components;
		}

	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ button1; // Оновити
	private: System::Windows::Forms::Button^ button2; // Додати
	private: System::Windows::Forms::Button^ button3; // Видалити
	private: System::Windows::Forms::Button^ button4; // Пошук/Інше

	private: System::ComponentModel::Container^ components;

		   // --- НАШІ ЗМІННІ ---
		   String^ connString = "Data Source=DESKTOP-T07RBAC;Initial Catalog=AlcoholShop;Integrated Security=True";

		   void LoadData() {
			   SqlConnection^ sqlConn = gcnew SqlConnection(connString);
			   try {
				   sqlConn->Open();
				   SqlDataAdapter^ da = gcnew SqlDataAdapter("SELECT * FROM Products", sqlConn);
				   DataTable^ dt = gcnew DataTable();
				   da->Fill(dt);
				   dataGridView1->DataSource = dt;
			   }
			   catch (Exception^ ex) {
				   MessageBox::Show("Помилка підключення: " + ex->Message);
			   }
			   finally { sqlConn->Close(); }
		   }
		   // -------------------

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->button4 = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			   this->SuspendLayout();

			   // Grid
			   this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->dataGridView1->Location = System::Drawing::Point(12, 12);
			   this->dataGridView1->Name = L"dataGridView1";
			   this->dataGridView1->Size = System::Drawing::Size(500, 200);
			   this->dataGridView1->TabIndex = 0;

			   // Button 1 (Оновити)
			   this->button1->Location = System::Drawing::Point(530, 12);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(100, 30);
			   this->button1->Text = L"Оновити";
			   this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);

			   // Button 2 (Додати)
			   this->button2->Location = System::Drawing::Point(530, 50);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(100, 30);
			   this->button2->Text = L"Додати";
			   this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);

			   // Button 3 (Видалити)
			   this->button3->Location = System::Drawing::Point(530, 90);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(100, 30);
			   this->button3->Text = L"Видалити";
			   this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);

			   // Button 4 (Вихід)
			   this->button4->Location = System::Drawing::Point(530, 130);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(100, 30);
			   this->button4->Text = L"Вихід";
			   this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);

			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(650, 300);
			   this->Controls->Add(this->button4);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->dataGridView1);
			   this->Name = L"MyForm";
			   this->Text = L"Облік Алкоголю";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			   this->ResumeLayout(false);
		   }
#pragma endregion

		   // Кнопка Оновити
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadData();
	}

		   // Кнопка Додати (Відкриває AddForm)
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		AddForm^ form = gcnew AddForm();
		form->ShowDialog(); // Відкриваємо як діалогове вікно
		LoadData(); // Коли закрили - оновлюємо таблицю
	}

		   // Кнопка Видалити
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dataGridView1->SelectedRows->Count > 0) {
			int id = Convert::ToInt32(dataGridView1->SelectedRows[0]->Cells[0]->Value);

			SqlConnection^ sqlConn = gcnew SqlConnection(connString);
			try {
				sqlConn->Open();
				SqlCommand^ cmd = gcnew SqlCommand("DELETE FROM Products WHERE Id = @id", sqlConn);
				cmd->Parameters->AddWithValue("@id", id);
				cmd->ExecuteNonQuery();
				MessageBox::Show("Видалено!");
			}
			catch (Exception^ ex) { MessageBox::Show("Помилка: " + ex->Message); }
			finally { sqlConn->Close(); LoadData(); }
		}
		else {
			MessageBox::Show("Виберіть рядок повністю (клікніть зліва від рядка)");
		}
	}

		   // Кнопка Вихід
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	};
}