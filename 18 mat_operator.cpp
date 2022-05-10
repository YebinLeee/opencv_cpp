#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
	float data[] = {
		1,0,2,
		-3,4,6,
		-1,-2,3
	};

	Mat m1(3, 3, CV_32F, data);	// 3�� 3�� ��� ����
	Mat m2(Matx13f(6, 30, 8));	// Matx ��ü�� ��� ����
	Mat m2_t = m2.t();			// ��� ��ġ

	Mat m1_inv = m1.inv(DECOMP_LU);	// ����� ���
	Mat x = m1_inv * m2_t;			// ��� ��
	

}