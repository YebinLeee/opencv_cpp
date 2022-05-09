#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
	Mat image(300, 400, CV_8U, Scalar(255));	// 흰색 바탕 영상 생성
	string title1 = "창 크기변경1 - AUTOSIZE";	// 윈도우 이름
	string title2 = "창 크기변경2 - NORMAL";

	namedWindow(title1, WINDOW_AUTOSIZE);
	namedWindow(title2, WINDOW_NORMAL);
	resizeWindow(title1, 500, 200);			// 창 크기 변경
	resizeWindow(title2, 500, 200);

	imshow(title1, image);
	imshow(title2, image);

	waitKey();
	return 0;
}