#include "spammer.h"

void _Point::setX(size_t newX) {
	x = newX;
}

void _Point::setY(size_t newY) {
	y = newY;
}

void _Point::setHwnd(const HWND& newHwnd) {
	hwnd = newHwnd;
}

_Point::_Point(size_t newX, size_t newY, const HWND& newHwnd) {
	setX(newX);
	setY(newY);
	setHwnd(newHwnd);
}

_Point::_Point() {}

size_t _Point::getX() {
	return x;
}

size_t _Point::getY() {
	return y;
}

HWND _Point::getHwnd() {
	return hwnd;
}

void _Point::click() {
	SendMessage(hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(getX(), getY()));
	Sleep(10);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, MAKELPARAM(getX(), getY()));
	Sleep(10);
	SendMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(getX(), getY()));
	Sleep(10);
}

void Spammer::setHwnd(const HWND& newHwnd) {
	hwnd = newHwnd;
}

void Spammer::setNames(const std::vector<std::string>& newNames) {
	names.clear();
	names = newNames;
}

std::vector<std::string> Spammer::getNames() const {
	return names;
}

Spammer::Spammer(const HWND& newHwnd) {
	setHwnd(newHwnd);
	names = {};
	findUserClickP = _Point(200, 400, hwnd);
	chooseUserClickP = _Point(400, 280, hwnd);
	confirmUserClickP = _Point(600, 400, hwnd);
	newMessageUserClickP = _Point(700, 645, hwnd);
}

void Spammer::SendText(const std::string& text_string) {
	auto text_wstring = std::wstring(text_string.begin(), text_string.end());

	for (size_t i = 0; i < text_string.size(); ++i) {
		SendMessageW(hwnd, WM_CHAR, (WPARAM)text_wstring[i], 0);
		Sleep(10);
	}
}

Mat Spammer::getEmpty() {
	return empty;
}

void Spammer::FindUserByStr(const std::string& name) {
	findUserClickP.click();
	SendText(name);
	Sleep(1250);
}

void Spammer::ChooseUser() {
	chooseUserClickP.click();
	Sleep(1000);
}

void Spammer::ConfirmUser() {
	confirmUserClickP.click();
	Sleep(1000);
}

void Spammer::SendMessageToUser(const std::string& message) {
	newMessageUserClickP.click();
	Sleep(750);
	SendText(message);
	SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
}

bool Spammer::IsUserFinded() {
	SetForegroundWindow(hwnd);

	Screen screen(hwnd);

	int startX = 350, startY = 277, width = 160, height = 60;
	Mat ROI(screen.get(), Rect(350, 277, 160, height));
	Mat screen_cut;
	ROI.copyTo(screen_cut);

	if (!Equal(screen_cut, getEmpty())) {
		return false;
	}
	return true;
}
