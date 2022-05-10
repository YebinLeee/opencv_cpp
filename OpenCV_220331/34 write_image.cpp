#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
	Mat img8 = imread("image/read_color.jpg", IMREAD_COLOR);
	CV_Assert(img8.data);		// ���� ���� ���� ó��

	// params_jpg, params_pgn ���Ϳ� ���� 95(default)�� 50, 3(default)�� 9�� ���� ����
	vector<int> params_jpg, params_png;
	params_jpg.push_back(IMWRITE_JPEG_QUALITY);			// JPG ȭ�� ����
	params_jpg.push_back(50);
	params_png.push_back(IMWRITE_PNG_COMPRESSION);		// PNG ���෹�� ����
	params_png.push_back(9);


	imwrite("image/write_test1.jpg", img8);				// ��� �������Ϸ� ���� (default 95)
	imwrite("image/write_test1.jpg", img8);	// ���� ȭ���� ���� (50)
	imwrite("image/write_test1.png", img8, params_png);	// ���� ���� ������� ���� (9)
	imwrite("image/write_test1.bmp", img8);				// BMP ���� ���� (default 3)

	return 0;
}

