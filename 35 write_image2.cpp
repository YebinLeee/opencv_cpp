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
	Mat img8 = imread("image/read_color22.jpg", IMREAD_COLOR);
	CV_Assert(img8.data);		// 영상 파일 예외 처리
	Mat img16, img32;

	// 형변환 및 원소 스케일 조정 (화소값의 범위를 ushort, float형에 맞게 스케일 변경)
	img8.convertTo(img16, CV_16U, 65535 / 255.0);	// uchar형 img8행렬을 ushort(CV_16U)형으로 변환
	img8.convertTo(img32, CV_32F, 1 / 255.0f);		// float(CV_32F)형으로 변환
	
	Rect roi(10, 10, 3, 3);	// 화소값 확인을 위한 관심 영역 지정

	// 각 행렬의 일부 출력
	cout << "img8 행렬의 일부 " << endl << img8(roi) << endl << endl;
	cout << "img16 행렬의 일부 " << endl << img16(roi) << endl << endl;
	cout << "img32 행렬의 일부 " << endl << img32(roi) << endl << endl;

	// 16, 32비트 영상 포맷으로 저장
	imwrite("image/write_test_16.tif", img16);		// 행렬 영상 파일로 저장
	imwrite("image/write_test_32.tif", img32);

	// imshow 함수가 행렬의 자료형에 따라 각기 다른 스케일로 밝기 표시
	imshow("img8", img8);
	imshow("img16", img16);	// 최대 65535의 화소값
	imshow("img32", img32);	// 0~1 사이의 부동소수 화소값

	waitKey();
	return 0;
}

