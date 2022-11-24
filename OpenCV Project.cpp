#include <iostream>
#include <vector>
#include <ball.h>
#include <Windows.h>
#include <opencv2/highgui.hpp>

cv::Scalar yellowL = cv::Scalar(25, 130, 180);
cv::Scalar yellowH = cv::Scalar(45, 255, 255);
cv::Scalar greenL = cv::Scalar(46, 40, 40);
cv::Scalar greenH = cv::Scalar(70, 255, 255);
cv::Scalar blueL = cv::Scalar(100, 150, 150);
cv::Scalar blueH = cv::Scalar(140, 255, 255);
cv::Scalar purpleL = cv::Scalar(148, 117, 89);
cv::Scalar purpleH = cv::Scalar(152, 255, 255);
cv::Scalar redL = cv::Scalar(170, 140, 160);
cv::Scalar redH = cv::Scalar(180, 255, 255);

cv::Mat getGameFrame(HWND hWND)
{
	HDC deviceContext = GetDC(hWND);
	HDC memoryDeviceContext = CreateCompatibleDC(deviceContext);

	RECT windowRect;
	GetClientRect(hWND, &windowRect);

	int height = windowRect.bottom;
	int width = windowRect.right;

	HBITMAP bitmap = CreateCompatibleBitmap(deviceContext, width, height);

	SelectObject(memoryDeviceContext, bitmap);
	BitBlt(memoryDeviceContext, 0, 0, width, height, deviceContext, 0, 0, SRCCOPY);

	BITMAPINFOHEADER bi;
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 1;
	bi.biYPelsPerMeter = 2;
	bi.biClrUsed = 3;
	bi.biClrImportant = 4;

	cv::Mat mat = cv::Mat(height, width, CV_8UC4);

	GetDIBits(memoryDeviceContext, bitmap, 0, height, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	DeleteObject(bitmap);
	DeleteDC(memoryDeviceContext);
	ReleaseDC(hWND, deviceContext);

	return mat;
}

int main()
{
	LPCWSTR windowTitle = L"Zuma Deluxe 1.0";
	HWND hWND = FindWindow(NULL, windowTitle);
	while (!hWND)
	{
		std::system("cls");
		std::cout << "Start the game..." << std::endl;
		hWND = FindWindow(NULL, windowTitle);
		Sleep(100);
	}
	cv::namedWindow("Result", cv::WINDOW_NORMAL);

	std::vector<Ball> balls;
	while (true)
	{
		cv::Mat gameFrame = getGameFrame(hWND);
		cv::Mat background;
		gameFrame.copyTo(background);

		cv::cvtColor(gameFrame, gameFrame, cv::COLOR_BGR2HSV);
		cv::rectangle(gameFrame, cv::Point(0, 0), cv::Point(640, 30), (0, 0, 0), cv::FILLED);
		balls.clear();

		getBalls(gameFrame, yellowL, yellowH, Color::YELLOW, balls);
		getBalls(gameFrame, blueL, blueH, Color::BLUE, balls);
		getBalls(gameFrame, redL, redH, Color::RED, balls);
		getBalls(gameFrame, greenL, greenH, Color::GREEN, balls);
		getBalls(gameFrame, purpleL, purpleH, Color::PURPLE, balls);
		drawBalls(background, balls);

		cv::imshow("Result", background);
		cv::waitKey(1);
	}

	return 0;
}
