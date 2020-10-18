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
	HWND hwnd; // ���������� ����
	HDC hWDC; // �������� ������
	HDC hScreen; // ����������� � ������� �������� � ������
	HBITMAP hBM; // ������� ������ ��� ������������ ��������� � ������
	BITMAPINFO BMI; // �������� �������� ������� ��� ������������ ��������� � ������

	int width; // ������ ������ � ��������
	int height; // ������ ������ � ��������

	char* data; // ������ ������ ���������
	cv::Mat* screen; // ��������

	HGDIOBJ hBM_Temp; // ������ ��� ������������ ��������� � ������ ��������� �� ���������	
};

bool Equal(const Mat& lhs, const Mat& rhs);