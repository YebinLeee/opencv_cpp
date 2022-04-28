#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {

	vector<Point> v1;				// Point 자료형을 원소로 사용하는 빈 벡터 선언
	v1.push_back(Point(10, 20));	// 벡터에 원소 추가
	v1.push_back(Point(20, 30));
	v1.push_back(Point(50, 60));

	vector<float> v2(3, 9.25);	// float형 벡터 선언, 3개 공간 원소를 모두 9.25로 초기화
	Size arr_size[] = { Size(2,2), Size(3,3), Size(4,4) }; // 사각형 공간의 배열 선언
	int arr_int[] = { 10,20,30,40,50 }; // 정수 배열 선언

	// 배열 원소로 벡터 초기화
	vector<Size> v3(arr_size, arr_size + sizeof(arr_size) / sizeof(Size));// 첫번째 주소, 마지막 주소
	vector<int> v4(arr_int + 2, arr_int + sizeof(arr_int) / sizeof(int)); // 2번째 위치부터 시작

	// reshape(a,b) - a채널 b=0행으로 변경
	cout << "[v1] " << (Mat)v1 << endl << endl;
	cout << "[v2] " << (Mat)v2 << endl << endl;
	cout << "[((Mat)v2).reshape(1,1)] " << ((Mat)v2).reshape(1,1) << endl << endl;
	cout << "[v3] " << (Mat)v3 << endl << endl;
	cout << "[((Mat)v3.reshape(1,1)] " << ((Mat)v3).reshape(1, 1) << endl << endl;
	cout << "[v4] " << ((Mat)v4).reshape(1,1) << endl << endl;

	return 0;
}