#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void onMouse(int, int, int, int, void*);

int main() {
	Mat image(200, 300, CV_8U);
	image.setTo(255);			// ��� �ʱ�ȭ - ��� ����
	imshow("���콺 �̺�Ʈ1", image);
	imshow("���콺 �̺�Ʈ2", image);

	setMouseCallback("���콺 �̺�Ʈ1", onMouse, 0);	// "���콺 �̺�Ʈ1" â�� ���콺 ��� ���� �ݹ��Լ��� ��Ͻ�Ų��.
	setMouseCallback("���콺 �̺�Ʈ2", onMouse, 0);	// "���콺 �̺�Ʈ1" â�� ���콺 ��� ���� �ݹ��Լ��� ��Ͻ�Ų��.
	waitKey(0);

	return 0;
}

void onMouse(int event, int x, int y, int flags, void* param) {
	switch (event) {
	case EVENT_LBUTTONDOWN:
		cout << "���콺 ���ʹ�ư ������" << endl;
		break;
	case EVENT_RBUTTONDOWN:
		cout << "���콺 ������ ��ư ������" << endl;
		break;
	case EVENT_RBUTTONUP:
		cout << "���콺 ������ ��ư ����" << endl;
		break;
	case EVENT_LBUTTONDBLCLK:
		cout << "���콺 ���ʹ�ư ����Ŭ��" << endl;
		break;
	}
}