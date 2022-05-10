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
	cout << name << "C" << m.channels() << endl;
}

int main() {
	string filename = "image/read_color.jpg";			// ���� ���� ��ġ
	Mat color2gray = imread(filename, IMREAD_GRAYSCALE);	// ���� ���� �ε�
	Mat color2color = imread(filename, IMREAD_COLOR);
	CV_Assert(color2gray.data && color2color.data);		// ���� ó��

	Rect roi(100, 100, 1, 1);	// ��� �� �� ȭ�� �簢��
	cout << "��� ��ǥ (100,100) ȭ�Ұ� " << endl;
	cout << "color2gray " << color2gray(roi) << endl;
	cout << "color2color" << color2color(roi) << endl;

	// ��� ���� ���
	print_matInfo("color2gray", color2gray);
	print_matInfo("color2color", color2color);

	// ��� ���� �������� ǥ��
	imshow("color2gray", color2gray);
	imshow("color2color", color2color);
	return 0;
}

