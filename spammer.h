#pragma once

#include"screen.h"

#include <Windows.h>
#include <string>
#include <vector>

// Класс, описывающий точку для клика в окне
class _Point {
public:
	_Point();
	_Point(size_t newX, size_t newY, const HWND& newHwnd);

	// Геттеры
	void setX(size_t newX); // Установить координату x относительно окна
	void setY(size_t newY); // Установить координату y относительно окна
	void setHwnd(const HWND& newHwnd); // Установить хэндл окна

	size_t getX(); // Получить координату x относительно окна
	size_t getY(); // Получить координату y относительно окна
	HWND getHwnd(); // Получить хэндл окна

	void click(); // Клик по координатам в окне

private:
	size_t x;
	size_t y;
	HWND hwnd;
};

// Класс, описывающий механизм рассылки
class Spammer {
public:
	Spammer(const HWND& newHwnd);

	void SendText(const std::string& text_string); // Ввод текста в окне

	void FindUserByStr(const std::string& name); // Поиск пользователя по нику
	void ChooseUser(); // Выбор пользователя для взаимодействия
	void ConfirmUser(const std::string& userName); // Подтверждение выбора пользователя
	void SendMessageToUser(const std::string& message); // Отправить сообщение пользователю
	void CloseFind();

	void setHwnd(const HWND& newHwnd); // Установить хэндл окна

	bool IsUserFinded(const std::string& userName); // Найден пользователь

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


