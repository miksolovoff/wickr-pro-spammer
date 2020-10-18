#pragma once

#include"screen.h"

#include <Windows.h>
#include <string>
#include <vector>

// �����, ����������� ����� ��� ����� � ����
class _Point {
public:
	_Point();
	_Point(size_t newX, size_t newY, const HWND& newHwnd);

	// �������
	void setX(size_t newX); // ���������� ���������� x ������������ ����
	void setY(size_t newY); // ���������� ���������� y ������������ ����
	void setHwnd(const HWND& newHwnd); // ���������� ����� ����

	size_t getX(); // �������� ���������� x ������������ ����
	size_t getY(); // �������� ���������� y ������������ ����
	HWND getHwnd(); // �������� ����� ����

	void click(); // ���� �� ����������� � ����

private:
	size_t x;
	size_t y;
	HWND hwnd;
};

// �����, ����������� �������� ��������
class Spammer {
public:
	Spammer(const HWND& newHwnd);

	void SendText(const std::string& text_string); // ���� ������ � ����

	void FindUserByStr(const std::string& name); // ����� ������������ �� ����
	void ChooseUser(); // ����� ������������ ��� ��������������
	void ConfirmUser(const std::string& userName); // ������������� ������ ������������
	void SendMessageToUser(const std::string& message); // ��������� ��������� ������������
	void CloseFind();

	void setHwnd(const HWND& newHwnd); // ���������� ����� ����

	bool IsUserFinded(const std::string& userName); // ������ ������������

private:
	HWND hwnd;
	_Point findUserClickP;
	_Point chooseUserClickP;
	_Point confirmUserClickP;
	_Point newMessageUserClickP;
	_Point closeFindP;

	void FindUserSleep(Mat& initalConditions, size_t dt_ms);
	void ChooseUserSleep(Mat& initalConditions, size_t dt_ms);
	void ConfirmUserSleep(const std::string& userName);
};

std::string StrFromPhoto(const char* filename);


