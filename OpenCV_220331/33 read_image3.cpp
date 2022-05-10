#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 행렬의 깊이(depth)와 채널, 자료형 출력
void print_matInfo(string name, Mat m) {
	string mat_type;

	if (m.depth() == CV_8U) mat_type = "CV_8U";
	else if (m.depth() == CV_8S) mat_type = "CV_8S";
	else if (m.depth() == CV_16U) mat_type = "CV_16U";
	else if (m.depth() == CV_16S) mat_type = "CV_16S";
	else if (m.depth() == CV_32S) mat_type = "CV_32S";
	else if (m.depth() == CV_32F) mat_type = "CV_32F";
	else if (m.depth() == CV_64F) mat_type = "CV_64F";

	cout << name;
	cout << format(": depth(%d) channels(%d) -> 자료형: ", m.depth(), m.channels());
	cout << name << "C" << m.channels() << endl;
}

int main() {
	string filename = "image/read_color.jpg";			// 영상 파일 위치
	Mat color2gray = imread(filename, IMREAD_GRAYSCALE);	// 영상 파일 로드
	Mat color2color = imread(filename, IMREAD_COLOR);
	CV_Assert(color2gray.data && color2color.data);		// 예외 처리

	Rect roi(100, 100, 1, 1);	// 행렬 내 한 화소 사각형
	cout << "행렬 좌표 (100,100) 화소값 " << endl;
	cout << "color2gray " << color2gray(roi) << endl;
	cout << "color2color" << color2color(roi) << endl;

	// 행렬 정보 출력
	print_matInfo("color2gray", color2gray);
	print_matInfo("color2color", color2color);

	// 행렬 정보 영상으로 표시
	imshow("color2gray", color2gray);
	imshow("color2color", color2color);
	return 0;
}

