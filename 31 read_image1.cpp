#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// ����� ����(depth)�� ä��, �ڷ��� ���
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
	cout << format(": depth(%d) channels(%d) -> �ڷ���: ", m.depth(), m.channels());
	cout << mat_type << "C" << m.channels() << endl;
};

int main() {
	string filename = "image/read_gray.jpg";			// ���� ���� ��ġ
	// ���� ���� �ε�
	Mat gray2gray = imread(filename, IMREAD_GRAYSCALE);		// 1ä�� uchar(CV_8UC1) ��� ����
	Mat gray2color = imread(filename, IMREAD_COLOR);		// 3ä�� CV_8UC1 ��� ����(�÷�Ÿ�� ��ȯ)
	CV_Assert(gray2gray.data && gray2color.data);		// ���� ó��

	int x = 100, y = 100;

	while (x <= 105) {
		Rect roi(x, y, 1, 1);		// ��� �� �� ȭ�� �簢���� ���ɿ������� �����Ͽ� �� ȭ���� ���� Ȯ��
		
		cout << "��� ��ǥ (" << x << "," << y << ") ȭ�Ұ� " << endl;
		cout << "gray2gray " << gray2gray(roi) << endl;
		cout << "gray2color " << gray2color(roi) << endl <<endl;

		x += 1;y += 1;
	}

	// ��� ���� ���
	print_matInfo("gray2gray", gray2gray);
	print_matInfo("gray2color", gray2color);

	// ��� ���� �������� ǥ��
	imshow("gray2gray", gray2gray);
	imshow("gray2color", gray2color);

	return 0;
}

