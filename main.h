#pragma once

#include "spammer.h"

#include <iostream>
#include <algorithm>

bool StopSpam;
size_t NewProgressMax = 0;
void MarshalString(System::String^ s, std::string& os);
std::vector<std::string> StrsFromFile(const char* filename);
void LogToFile(const char* filename, const std::string& name, const std::string& info);
std::string WcharToString(wchar_t* wc_str);

std::string namesFile;
std::string messageFile;
std::string logsFile;

namespace WickrSpammer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Сводка для main
	/// </summary>
	public ref class main : public System::Windows::Forms::Form
	{
	public:
		main(void)
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
		~main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ spamRunClick;
	private: System::Windows::Forms::Button^ spamStopClick;
	protected:

	private: Spammer* spammer;
	private: Thread^ myThread;
	private: System::Windows::Forms::ProgressBar^ spamProgress;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ chooseFileNames;
	private: System::Windows::Forms::Button^ chooseFileMessage;
	private: System::Windows::Forms::Button^ chooseFileLogs;


	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(main::typeid));
			this->spamRunClick = (gcnew System::Windows::Forms::Button());
			this->spamStopClick = (gcnew System::Windows::Forms::Button());
			this->spamProgress = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->chooseFileNames = (gcnew System::Windows::Forms::Button());
			this->chooseFileMessage = (gcnew System::Windows::Forms::Button());
			this->chooseFileLogs = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// spamRunClick
			// 
			this->spamRunClick->Location = System::Drawing::Point(12, 97);
			this->spamRunClick->Name = L"spamRunClick";
			this->spamRunClick->Size = System::Drawing::Size(150, 57);
			this->spamRunClick->TabIndex = 0;
			this->spamRunClick->Text = L"Запуск рассылки";
			this->spamRunClick->UseVisualStyleBackColor = true;
			this->spamRunClick->Click += gcnew System::EventHandler(this, &main::SpamRunClick);
			// 
			// spamStopClick
			// 
			this->spamStopClick->Location = System::Drawing::Point(193, 97);
			this->spamStopClick->Name = L"spamStopClick";
			this->spamStopClick->Size = System::Drawing::Size(150, 57);
			this->spamStopClick->TabIndex = 1;
			this->spamStopClick->Text = L"Остановить рассылку";
			this->spamStopClick->UseVisualStyleBackColor = true;
			this->spamStopClick->Click += gcnew System::EventHandler(this, &main::SpamStopClick);
			// 
			// spamProgress
			// 
			this->spamProgress->Location = System::Drawing::Point(156, 193);
			this->spamProgress->Name = L"spamProgress";
			this->spamProgress->Size = System::Drawing::Size(187, 16);
			this->spamProgress->TabIndex = 2;
			this->spamProgress->Click += gcnew System::EventHandler(this, &main::SpamProgress);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 193);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(138, 16);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Прогресс рассылки:";
			this->label1->Click += gcnew System::EventHandler(this, &main::label1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &main::openFileDialog1_FileOk);
			// 
			// chooseFileNames
			// 
			this->chooseFileNames->Location = System::Drawing::Point(15, 12);
			this->chooseFileNames->Name = L"chooseFileNames";
			this->chooseFileNames->Size = System::Drawing::Size(95, 57);
			this->chooseFileNames->TabIndex = 4;
			this->chooseFileNames->Text = L"Выбрать файл с никами";
			this->chooseFileNames->UseVisualStyleBackColor = true;
			this->chooseFileNames->Click += gcnew System::EventHandler(this, &main::chooseFileNames_Click);
			// 
			// chooseFileMessage
			// 
			this->chooseFileMessage->Location = System::Drawing::Point(131, 12);
			this->chooseFileMessage->Name = L"chooseFileMessage";
			this->chooseFileMessage->Size = System::Drawing::Size(95, 57);
			this->chooseFileMessage->TabIndex = 5;
			this->chooseFileMessage->Text = L"Выбрать файл с сообщением";
			this->chooseFileMessage->UseVisualStyleBackColor = true;
			this->chooseFileMessage->Click += gcnew System::EventHandler(this, &main::chooseFileMessage_Click);
			// 
			// chooseFileLogs
			// 
			this->chooseFileLogs->Location = System::Drawing::Point(248, 12);
			this->chooseFileLogs->Name = L"chooseFileLogs";
			this->chooseFileLogs->Size = System::Drawing::Size(95, 57);
			this->chooseFileLogs->TabIndex = 6;
			this->chooseFileLogs->Text = L"Выбрать файл для записи логов";
			this->chooseFileLogs->UseVisualStyleBackColor = true;
			this->chooseFileLogs->Click += gcnew System::EventHandler(this, &main::chooseFileLogs_Click);
			// 
			// main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(351, 245);
			this->Controls->Add(this->chooseFileLogs);
			this->Controls->Add(this->chooseFileMessage);
			this->Controls->Add(this->chooseFileNames);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->spamProgress);
			this->Controls->Add(this->spamStopClick);
			this->Controls->Add(this->spamRunClick);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"main";
			this->Text = L"Wickr Spammer";
			this->Load += gcnew System::EventHandler(this, &main::main_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	public:	void Spam() {
			try {
				StopSpam = false; // Рассылка активна

				Spammer sp(FindWindow(L"Qt5QWindowOwnDCIcon", L"Wickr Pro")); // Объект класса Spammer, необходим для рассылки

				std::vector<std::string> names = {};
				std::vector<std::string> messages = {};

				try {
					names = StrsFromFile(namesFile.c_str()); // Вектор с никами
				        messages = StrsFromFile(messageFile.c_str()); // Вектор с сообщениями
				}
				catch (std::exception e) {
					System::String^ exceptionMsg; // Сообщение с исключением
					exceptionMsg = gcnew System::String((std::string("Any problems in file: ") + e.what()).c_str()); // Преобразование сообщения
					MessageBox::Show(exceptionMsg, "Error!", MessageBoxButtons::OK, MessageBoxIcon::Asterisk); // Вывод окошка с сообщением об ошибке
					StopSpam = true;
				}

				NewProgressMax = names.size(); // Верхнаяя граница ProgressBar

				this->Invoke(gcnew Action(this, &main::UpdateProgressMax)); // Для запуска в другом потоке

				for (const auto& name : names) { // Итерирование по каждому нику
					if (StopSpam) {
						break;
					}

					sp.FindUserByStr(name); // Поиск пользователя
					if (StopSpam) {
						break;
					}

					if (sp.IsUserFinded(name)) { // Пользователь найден
						if (StopSpam) {
							break;
						}

						sp.ChooseUser(); // Выбрать пользователя
						if (StopSpam) {
							break;
						}

						sp.ConfirmUser(name); // Подтвердить выбор пользователя
						if (StopSpam) {
							break;
						}

						for (const auto& msg : messages) { // Итерирование по каждому сообщению
							if (StopSpam) {
								break;
							}
							sp.SendMessageToUser(msg); // Отправка сообщения
							Sleep(10);
						}

						LogToFile(logsFile.c_str(), name, "message has been sent"); // Запись лога в файл
					}
					else { // Пользователь не найден
						sp.CloseFind(); // Закрыть область поиска
						LogToFile(logsFile.c_str(), name, "invalid nick"); // Запись лога
					}

					this->Invoke(gcnew Action(this, &main::UpdateProgressIncrement)); // Для запуска в другом потоке
				}
			}
			catch (std::exception e) { // Обработка исключений
				System::String^ exceptionMsg; // Сообщение с исключением
				exceptionMsg = gcnew System::String(e.what()); // Преобразование 
				MessageBox::Show(exceptionMsg, "Error!", MessageBoxButtons::OK, MessageBoxIcon::Asterisk); // Вывод окошка с сообщением об ошибке

				StopSpam = true;
			}
		}

		  void UpdateProgressMax() {
			  this->spamProgress->Maximum = NewProgressMax;
		  }

		  void UpdateProgressIncrement() {
			  this->spamProgress->Increment(1);
		  }

		  void OPF_Names() {
			  this->openFileDialog1->ShowDialog();
			  System::String^ path_f = this->openFileDialog1->FileName;
			  path_f->Replace("\\", "//");

			  MarshalString(path_f, namesFile);
		  }

		  void OPF_Message() {
			  this->openFileDialog1->ShowDialog();
			  System::String^ path_f = this->openFileDialog1->FileName;
			  path_f->Replace("\\", "//");

			  MarshalString(path_f, messageFile);
		  }

		  void OPF_Logs() {
			  this->openFileDialog1->ShowDialog();
			  System::String^ path_f = this->openFileDialog1->FileName;
			  path_f->Replace("\\", "//");

			  MarshalString(path_f, logsFile);
		  }

	private: System::Void main_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void SpamRunClick(System::Object^ sender, System::EventArgs^ e) {
		myThread = gcnew Thread(gcnew ThreadStart(this, &main::Spam));
		myThread->Start();
	}
	private: System::Void SpamStopClick(System::Object^ sender, System::EventArgs^ e) {
		StopSpam = true;
		this->spamProgress->Value = 0;
	}
	private: System::Void SpamProgress(System::Object^ sender, System::EventArgs^ e) {

	}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
}

private: System::Void chooseFileNames_Click(System::Object^ sender, System::EventArgs^ e) {
	ThreadStart^ threadDelegate = gcnew ThreadStart(this, &main::OPF_Names);
	Thread^ newThread = gcnew Thread(threadDelegate, 0);
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();
}

private: System::Void chooseFileMessage_Click(System::Object^ sender, System::EventArgs^ e) {
	ThreadStart^ threadDelegate = gcnew ThreadStart(this, &main::OPF_Message);
	Thread^ newThread = gcnew Thread(threadDelegate, 0);
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();
}

private: System::Void chooseFileLogs_Click(System::Object^ sender, System::EventArgs^ e) {
	ThreadStart^ threadDelegate = gcnew ThreadStart(this, &main::OPF_Logs);
	Thread^ newThread = gcnew Thread(threadDelegate, 0);
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();
}
};
}
