#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string title = "밝기변경", bar_name = "밝기값";
Mat image;

// 트랙바 콜백 함수
void onChange(int value, void* userdata) {
	int add_value = value - 130;
	cout << "추가 화소값 " << add_value << endl;

	Mat tmp = image + add_value;
	imshow(title, tmp);
}

// 마우스 이벤트 처리할 콜백 함수
void onMouse(int event, int x, int y, int flags, void* param) {
	// 오른쪽 버튼 클릭 시 이벤트 처리
	if (event == EVENT_RBUTTONDOWN) {
		add(image, 10, image); // 이미지 전체 행렬의 화소값을 10 더함
		setTrackbarPos(bar_name, title, image.at <uchar>(0));	// 트랙바 위치 변경
		imshow(title, image);
	}
	// 왼쪽 버튼 클릭 시 이벤트 처리
	else if (event == EVENT_LBUTTONDOWN) {
		subtract(image, 10, image); // 이미지 전체 행렬의 화소값을 10 뺌
		setTrackbarPos(bar_name, title, image.at<uchar>(0));
		imshow(title, image);
	}
}

int main() {
	int value = 130;
	image = Mat(300, 500, CV_8UC1, Scalar(120));

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar(bar_name, title, &value, 255, onChange);	// 트랙바 등록
	setMouseCallback(title, onMouse, 0);					// 마우스 콜백함수 등록

	imshow(title, image);
	waitKey(0);
	return 0;
}