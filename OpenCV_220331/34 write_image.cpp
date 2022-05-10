#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
	Mat img8 = imread("image/read_color.jpg", IMREAD_COLOR);
	CV_Assert(img8.data);		// 영상 파일 예외 처리

	// params_jpg, params_pgn 벡터에 각각 95(default)와 50, 3(default)와 9의 값을 저장
	vector<int> params_jpg, params_png;
	params_jpg.push_back(IMWRITE_JPEG_QUALITY);			// JPG 화질 설정
	params_jpg.push_back(50);
	params_png.push_back(IMWRITE_PNG_COMPRESSION);		// PNG 압축레벨 설정
	params_png.push_back(9);


	imwrite("image/write_test1.jpg", img8);				// 행렬 영상파일로 저장 (default 95)
	imwrite("image/write_test1.jpg", img8);	// 지정 화질로 저장 (50)
	imwrite("image/write_test1.png", img8, params_png);	// 지정 압축 양식으로 저장 (9)
	imwrite("image/write_test1.bmp", img8);				// BMP 파일 저장 (default 3)

	return 0;
}

