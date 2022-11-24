#include <ball.h>

Ball::Ball(Color ucolor, cv::Rect rect, int x, int y)
	: color(ucolor)
	, rectangle(rect)
	, position(cv::Point(x, y))
{
}

void getBalls(cv::Mat img, cv::Scalar low, cv::Scalar high, Color color, std::vector<Ball>& balls)
{
	cv::Mat mask;
	cv::inRange(img, low, high, mask);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++)
	{
		cv::Rect boundRect = cv::boundingRect(contours[i]);
		if (boundRect.area() > 350 && (boundRect.width < 70 || boundRect.height < 70))
			balls.emplace_back(color, boundRect, boundRect.x + boundRect.width / 2, boundRect.y + boundRect.height / 2);
	}
}

void drawBalls(cv::Mat img, std::vector<Ball>& balls)
{
	for (int i = 0; i < balls.size(); i++)
	{
		switch (balls[i].color)
		{
		case RED:
			cv::rectangle(img, balls[i].rectangle.tl(), balls[i].rectangle.br(), CV_RGB(255, 0, 0), 2);
			break;
		case BLUE:
			cv::rectangle(img, balls[i].rectangle.tl(), balls[i].rectangle.br(), CV_RGB(0, 0, 255), 2);
			break;
		case GREEN:
			cv::rectangle(img, balls[i].rectangle.tl(), balls[i].rectangle.br(), CV_RGB(0, 255, 0), 2);
			break;
		case YELLOW:
			cv::rectangle(img, balls[i].rectangle.tl(), balls[i].rectangle.br(), CV_RGB(255, 255, 0), 2);
			break;
		case PURPLE:
			cv::rectangle(img, balls[i].rectangle.tl(), balls[i].rectangle.br(), CV_RGB(128, 0, 128), 2);
			break;
		}
	}
}