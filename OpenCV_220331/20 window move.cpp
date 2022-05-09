#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
	Mat image1(300, 400, CV_8U, Scalar(255));	// ������� ���� ���� (300�� 400�� ũ���� ���ϵ� ���� ����)
	Mat image2(300, 400, CV_8U, Scalar(100));	// ȸ������ ���� ����
	String title1 = "whiteâ ����";	// ������ �̸�
	String title2 = "gray â ����";	//

	namedWindow(title1, WINDOW_AUTOSIZE);	// ������ �̸� ����
	namedWindow(title2, WINDOW_NORMAL);		// NORMAL - ũ�� ���� ����
	moveWindow(title1, 100, 200);		// ������ �̵�
	moveWindow(title2, 300, 200);

	imshow(title1, image1);	// ��� ���Ҹ� �������� ǥ��
	imshow(title2, image2);
	waitKey();		// Ű �̺�Ʈ ���
	destroyAllWindows();	// ���� ��� ������ ����

	return 0;
}