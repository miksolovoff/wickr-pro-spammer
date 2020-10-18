#include "main.h"

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <ctime>

using namespace WickrSpammer;
using namespace System; 
using namespace System::Threading;

extern bool StopSpam = false;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew main);
    return 0;
}

void MarshalString(System::String^ s, std::string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

std::string WcharToString(wchar_t* wc_str) {
	std::wstring ws(wc_str);

	return std::string(ws.begin(), ws.end());
}


std::vector<std::string> StrsFromFile(const char* filename) {
	std::vector<std::string> result;

	std::fstream f(filename);
	if (f) {
		std::string str;
		while (!f.eof()) {
			std::getline(f, str);
			if (str.size() > 0) {
				result.push_back(str);
			}
		}
		f.close();
	}
	else {
		throw std::invalid_argument(filename);
	}

	return result;
}

void LogToFile(const char* filename, const std::string& name, const std::string& info) {
	std::ofstream f(filename, std::ios::app);

	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);

	f << name << ":		" << asctime(timeinfo) << "		" << info << "\n";
}


