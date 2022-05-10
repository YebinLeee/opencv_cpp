#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


string title = "트랙바 이벤트";
Mat image;

void onChange(int value, void* userdata) {
	int add_value = value - 130;		// 행렬에 추가할 값 선언 (-120 ~ 129 범위)
	cout << "추가 화소값 " << add_value << endl;

	Mat tmp = image + add_value;	// 
	imshow(title, tmp);
}

int main() {
	int value = 128;	// 행렬에 추가할 값
	image = Mat(300, 400, CV_8UC1, Scalar(120));

	namedWindow(title, WINDOW_AUTOSIZE);		// 윈도우 생성
	// 트랙바 생성 - 트랙바 이벤트가 발생할 때마다 트랙바의 위치값을 value로 반환받으며, 콜백함수 onChange()를 호출
	createTrackbar("밝기값", title, &value, 255, onChange);

	imshow(title, image);
	waitKey(0);

	return 0;
}
