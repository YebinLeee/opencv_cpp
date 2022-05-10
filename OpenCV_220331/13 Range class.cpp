#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {

	Range r1(0, 3), r2(3, 7);	// ���� ��ü ����

	int data[] ={
		10,11,12,13,14,15,16,
		20,21,22,23,24,25,26,
		30,31,32,33,34,35,36,
		40,41,42,43,44,45,46
	};

	Mat m1, m2;
	m1 = Mat(4, 7, CV_32S, data); // 4�� 7�� ����� data �迭�� ���� �� �ʱ�ȭ
	m2 = m1(r1, r2);	// ���� ��ü�� ���� ����(0,3) ~ (3,7) ����

	cout << "[m1] = " << endl << m1 << endl << endl;
	cout << "[m2 (0~2�� 3~6��) ����] = " << endl << m2 << endl <<endl;

	m2.setTo(50); // ��ü ���� ����
	cout << "[m2] = " << endl << m2 << endl << endl;

	m1.release();
	cout << "------------- m1 release() -------------" << endl << endl;

	// m2�� ������ ���� m1�� �ش���� ���� ����
	cout << "[m1] = " << endl << m1 << endl << endl;
	cout << "[m2] = " << endl << m2 << endl << endl;


	return 0;
}