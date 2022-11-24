#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

enum Color { BLUE, GREEN, RED, YELLOW, PURPLE };

struct Ball
{
	Ball(Color ucolor, cv::Rect rect, int x, int y);

	Color color;
	cv::Point position;
	cv::Rect rectangle;
};

void getBalls(cv::Mat img, cv::Scalar low, cv::Scalar high, Color color, std::vector<Ball>& balls);
void drawBalls(cv::Mat img, std::vector<Ball>& balls);