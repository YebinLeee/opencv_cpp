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
	Mat img8 = imread("image/read_color22.jpg", IMREAD_COLOR);
	CV_Assert(img8.data);		// ���� ���� ���� ó��
	Mat img16, img32;

	// ����ȯ �� ���� ������ ���� (ȭ�Ұ��� ������ ushort, float���� �°� ������ ����)
	img8.convertTo(img16, CV_16U, 65535 / 255.0);	// uchar�� img8����� ushort(CV_16U)������ ��ȯ
	img8.convertTo(img32, CV_32F, 1 / 255.0f);		// float(CV_32F)������ ��ȯ
	
	Rect roi(10, 10, 3, 3);	// ȭ�Ұ� Ȯ���� ���� ���� ���� ����

	// �� ����� �Ϻ� ���
	cout << "img8 ����� �Ϻ� " << endl << img8(roi) << endl << endl;
	cout << "img16 ����� �Ϻ� " << endl << img16(roi) << endl << endl;
	cout << "img32 ����� �Ϻ� " << endl << img32(roi) << endl << endl;

	// 16, 32��Ʈ ���� �������� ����
	imwrite("image/write_test_16.tif", img16);		// ��� ���� ���Ϸ� ����
	imwrite("image/write_test_32.tif", img32);

	// imshow �Լ��� ����� �ڷ����� ���� ���� �ٸ� �����Ϸ� ��� ǥ��
	imshow("img8", img8);
	imshow("img16", img16);	// �ִ� 65535�� ȭ�Ұ�
	imshow("img32", img32);	// 0~1 ������ �ε��Ҽ� ȭ�Ұ�

	waitKey();
	return 0;
}

