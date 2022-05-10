#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
	Mat image1(300, 400, CV_8U, Scalar(255));	// 흰색바탕 영상 생성 (300행 400열 크기의 명암도 영상 생성)
	Mat image2(300, 400, CV_8U, Scalar(100));	// 회색바탕 영상 생성
	String title1 = "white창 제어";	// 윈도우 이름
	String title2 = "gray 창 제어";	//

	namedWindow(title1, WINDOW_AUTOSIZE);	// 윈도우 이름 지정
	namedWindow(title2, WINDOW_NORMAL);		// NORMAL - 크기 변경 가능
	moveWindow(title1, 100, 200);		// 윈도우 이동
	moveWindow(title2, 300, 200);

	imshow(title1, image1);	// 행렬 원소를 영상으로 표시
	imshow(title2, image2);
	waitKey();		// 키 이벤트 대기
	destroyAllWindows();	// 열린 모든 윈도우 제거

	return 0;
}