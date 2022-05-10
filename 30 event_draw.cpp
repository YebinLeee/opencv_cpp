#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string title = "이벤트 그리기";
Mat image;

void onMouse(int event, int x, int y, int flags, void* param) {
	static Point pt(-1, 1);
	if (event == EVENT_RBUTTONDOWN) {
		if (pt.x < 0) pt = Point(x, y);	// 사각 좌표 지정
		else {
			rectangle(image, pt, Point(x, y), Scalar(50), 2);	// 종료 좌표 및 그리기
			imshow(title, image);
			pt = Point(-1, -1);	// 시작 좌표 초기화
		}
	}
	else if (event == EVENT_LBUTTONDOWN) {
		if (pt.x < 0)pt = Point(x, y);
		else {
			Point2d pt2 = pt - Point(x, y);
			int radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y);	// 두 좌표 간 거리
			circle(image, pt, radius, Scalar(150), 2);

			imshow(title, image);
			pt = Point(-1, -1);	// 시작 좌표 초기화
				
		}
	}
}



int main() {
	image = Mat(300, 500, CV_8UC1, Scalar(255));
	imshow(title, image);
	setMouseCallback(title, onMouse, 0);		// 콜백 함수 등록

	waitKey(0);

	return 0;
}