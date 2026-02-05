#pragma once

namespace Project1 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data::SqlClient;

    public ref class AddForm : public System::Windows::Forms::Form
    {
    public:
        AddForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~AddForm() { if (components) delete components; }

    private:
        System::Windows::Forms::TextBox^ txtType;
        System::Windows::Forms::TextBox^ txtBrand;
        System::Windows::Forms::TextBox^ txtManuf;
        System::Windows::Forms::TextBox^ txtSupp;
        System::Windows::Forms::TextBox^ txtPrice;
        System::Windows::Forms::DateTimePicker^ dtpExp;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnCancel;
        System::Windows::Forms::Label^ lblInfo;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->txtType = (gcnew System::Windows::Forms::TextBox());
            this->txtBrand = (gcnew System::Windows::Forms::TextBox());
            this->txtManuf = (gcnew System::Windows::Forms::TextBox());
            this->txtSupp = (gcnew System::Windows::Forms::TextBox());
            this->txtPrice = (gcnew System::Windows::Forms::TextBox());
            this->dtpExp = (gcnew System::Windows::Forms::DateTimePicker());
            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->lblInfo = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();

            // Розміщення
            this->lblInfo->Text = "Введіть: Тип, Марка, Виробник, Постачальник, Ціна";
            this->lblInfo->SetBounds(10, 10, 300, 20);

            this->txtType->SetBounds(10, 40, 100, 20); this->txtType->Text = "Вид";
            this->txtBrand->SetBounds(10, 70, 100, 20); this->txtBrand->Text = "Марка";
            this->txtManuf->SetBounds(10, 100, 100, 20); this->txtManuf->Text = "Виробник";
            this->txtSupp->SetBounds(10, 130, 100, 20); this->txtSupp->Text = "Постачальник";
            this->txtPrice->SetBounds(10, 160, 100, 20); this->txtPrice->Text = "0";
            this->dtpExp->SetBounds(10, 190, 200, 20);

            this->btnSave->Text = "Зберегти";
            this->btnSave->SetBounds(10, 230, 80, 30);
            this->btnSave->Click += gcnew System::EventHandler(this, &AddForm::btnSave_Click);

            this->btnCancel->Text = "Вихід";
            this->btnCancel->SetBounds(100, 230, 80, 30);
            this->btnCancel->Click += gcnew System::EventHandler(this, &AddForm::btnCancel_Click);

            this->Controls->Add(this->lblInfo);
            this->Controls->Add(this->txtType);
            this->Controls->Add(this->txtBrand);
            this->Controls->Add(this->txtManuf);
            this->Controls->Add(this->txtSupp);
            this->Controls->Add(this->txtPrice);
            this->Controls->Add(this->dtpExp);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->btnCancel);
            this->ClientSize = System::Drawing::Size(300, 300);
            this->Text = L"Додати товар";
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ connString = "Data Source=DESKTOP-T07RBAC;Initial Catalog=AlcoholShop;Integrated Security=True";
            SqlConnection^ sqlConn = gcnew SqlConnection(connString);
            try {
                sqlConn->Open();
                String^ query = "INSERT INTO Products (Type, Brand, Manufacturer, Supplier, Price, ExpirationDate) VALUES (@t, @b, @m, @s, @p, @d)";
                SqlCommand^ cmd = gcnew SqlCommand(query, sqlConn);

                cmd->Parameters->AddWithValue("@t", txtType->Text);
                cmd->Parameters->AddWithValue("@b", txtBrand->Text);
                cmd->Parameters->AddWithValue("@m", txtManuf->Text);
                cmd->Parameters->AddWithValue("@s", txtSupp->Text);
                cmd->Parameters->AddWithValue("@p", Convert::ToDecimal(txtPrice->Text));
                cmd->Parameters->AddWithValue("@d", dtpExp->Value);

                cmd->ExecuteNonQuery();
                MessageBox::Show("Збережено!");
                this->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Помилка: " + ex->Message);
            }
            finally { sqlConn->Close(); }
        }
    };
}