#include <opencv2/opencv.hpp >
using namespace cv;
using namespace std;

int main() {
	Mat image(200, 300, CV_8U, Scalar(255));
	namedWindow("Ű���� �̺�Ʈ", WINDOW_AUTOSIZE);
	imshow("Ű���� �̺�Ʈ", image);

	while (1) {
		int key = waitKey(100);		// 100ms���� Ű �̺�Ʈ ���
		if (key == 27) break;		// ESC Ű�� �ԷµǸ� ����

		switch (key) {
		case 'a':cout << "aŰ �Է�" << endl;break;
		case 'b':cout << "bŰ �Է�" << endl;break;
		case 0x41:cout << "AŰ �Է�" << endl;break;
		case 66:cout << "BŰ �Է�" << endl;break;

		case 0x250000: cout << "���� ȭ��ǥ Ű �Է�" << endl;break;
		case 0x260000:cout << "���� ȭ��ǥ Ű �Է�" << endl;break;
		case 0x270000:cout << "������ ȭ��ǥ Ű �Է�" << endl;break;
		case 0x280000: cout << "�Ʒ��� ȭ��ǥ Ű �Է�" << endl;break;
		}
	}

	return 0;
}