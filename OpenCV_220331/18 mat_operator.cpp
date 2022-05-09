#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
	float data[] = {
		1,0,2,
		-3,4,6,
		-1,-2,3
	};

	Mat m1(3, 3, CV_32F, data);	// 3행 3열 행렬 선언
	Mat m2(Matx13f(6, 30, 8));	// Matx 객체로 행렬 선언
	Mat m2_t = m2.t();			// 행렬 전치

	Mat m1_inv = m1.inv(DECOMP_LU);	// 역행렬 계산
	Mat x = m1_inv * m2_t;			// 행렬 곱
	

}