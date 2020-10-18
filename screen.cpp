#include "screen.h"

void Screen::setHwnd(const HWND& newHwnd) {
	hwnd = newHwnd;
}

Screen::Screen() {}

Screen::Screen(const HWND& newHwnd) {
	// ��������� ������
	setHwnd(newHwnd);
	hWDC = GetWindowDC(hwnd);
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	// ����������� �������� � ������
	hScreen = CreateCompatibleDC(hWDC);
	hBM = CreateCompatibleBitmap(hWDC, width, height); 
	hBM_Temp = SelectObject(hScreen, hBM);

	// �������� �������� ������� ��� ������������ ��������� � ������
	BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BMI.bmiHeader.biWidth = width;
	BMI.bmiHeader.biHeight = -height;
	BMI.bmiHeader.biPlanes = 1;
	BMI.bmiHeader.biBitCount = 24;
	BMI.bmiHeader.biCompression = BI_RGB;

	// ������ ������ ���������
	const int colorSize = 3; // ������ �������
	const int alignment = 4; // ������������ ������		 
	int step = (int)ceil(width * colorSize / (double)alignment) * alignment; // ��� ������
	data = new char[step * height]; // - delete[] data;

	// ��������
	screen = new Mat(height, width, CV_8UC3, data, step);
}

Screen::~Screen() {
	SelectObject(hScreen, hBM_Temp);
	DeleteObject(hBM);
	DeleteDC(hScreen);
	delete screen; screen = NULL;
	delete[] data; data = NULL;
}

Mat& Screen::get() {
	BitBlt(hScreen, 0, 0, width, height, hWDC, 0, 0, SRCCOPY);
	GetDIBits(hScreen, hBM, 0, height, data, &BMI, DIB_RGB_COLORS);
	return *screen;
}

bool Equal(const Mat& lhs, const Mat& rhs) {
	if ((lhs.rows != rhs.rows) || (lhs.cols != rhs.cols)) {
		return false;
	}

	Scalar s = sum(lhs - rhs);

	return (s[0] == 0) && (s[1] == 0) && (s[2] == 0);
}