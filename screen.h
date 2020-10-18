#pragma once

#include <Windows.h>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Screen {
public:
	Screen(const HWND& newHwnd);
	Screen();
	~Screen();

	void setHwnd(const HWND& newHwnd);

	cv::Mat& get();

private:
	HWND hwnd; // Дескриптор окна
	HDC hWDC; // Контекст экрана
	HDC hScreen; // Совместимый с экраном контекст в памяти
	HBITMAP hBM; // Рабочий массив бит совместимого контекста в памяти
	BITMAPINFO BMI; // Описание рабочего массива бит совместимого контекста в памяти

	int width; // Ширина экрана в пикселях
	int height; // Высота экрана в пикселях

	char* data; // Массив данных скриншота
	cv::Mat* screen; // Скриншот

	HGDIOBJ hBM_Temp; // Массив бит совместимого контекста в памяти созданный по умолчанию	
};

bool Equal(const Mat& lhs, const Mat& rhs);