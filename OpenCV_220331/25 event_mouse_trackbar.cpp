#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string title = "��⺯��", bar_name = "��Ⱚ";
Mat image;

// Ʈ���� �ݹ� �Լ�
void onChange(int value, void* userdata) {
	int add_value = value - 130;
	cout << "�߰� ȭ�Ұ� " << add_value << endl;

	Mat tmp = image + add_value;
	imshow(title, tmp);
}

// ���콺 �̺�Ʈ ó���� �ݹ� �Լ�
void onMouse(int event, int x, int y, int flags, void* param) {
	// ������ ��ư Ŭ�� �� �̺�Ʈ ó��
	if (event == EVENT_RBUTTONDOWN) {
		add(image, 10, image); // �̹��� ��ü ����� ȭ�Ұ��� 10 ����
		setTrackbarPos(bar_name, title, image.at <uchar>(0));	// Ʈ���� ��ġ ����
		imshow(title, image);
	}
	// ���� ��ư Ŭ�� �� �̺�Ʈ ó��
	else if (event == EVENT_LBUTTONDOWN) {
		subtract(image, 10, image); // �̹��� ��ü ����� ȭ�Ұ��� 10 ��
		setTrackbarPos(bar_name, title, image.at<uchar>(0));
		imshow(title, image);
	}
}

int main() {
	int value = 130;
	image = Mat(300, 500, CV_8UC1, Scalar(120));

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar(bar_name, title, &value, 255, onChange);	// Ʈ���� ���
	setMouseCallback(title, onMouse, 0);					// ���콺 �ݹ��Լ� ���

	imshow(title, image);
	waitKey(0);
	return 0;
}