#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void print_locateROI(String str, Mat m) {
	Size size;
	Point pt;
	m.locateROI(size, pt); // 부분 행렬에서 부모 행렬의 크기와 위치를 알려줌

	cout << "부모크기" << size << ",";
	cout << "[" << str << "] = ";
	cout << m.size() << " from" << pt << endl;

}
int main() {

	Range r1(0, 3), r2(3, 7);	// 범위 객체 선언

	int data[] = {
		10,11,12,13,14,15,16,
		20,21,22,23,24,25,26,
		30,31,32,33,34,35,36,
		40,41,42,43,44,45,46
	};

	
	Mat m1(5, 7, CV_32S, data); // 4행 7열 행렬을 data 배열로 선언 및 초기화
	Mat m2 = m1(r1, r2);	// 범위 객체로 관심 영역(0,3) ~ (3,7) 참조
	Mat m3 = m1(r1, r1);

	// 행렬 정보 출력
	print_locateROI("m2", m2);
	print_locateROI("m3", m3);

	// 관심 영역 변경 (위쪽: 1행 감소 / 아래쪽: 1행 추가 / 왼쪽: 2열 추가 / 오른쪽: 1행 감소)
	m2.adjustROI(-1, 1, 2, -1);
	// 관심 영역 변경 (위쪽: 0 / 아래쪽: 1행 감소 / 왼쪽: 2열 감소 / 오른쪽: 2행 추가)
	m3.adjustROI(0, -1, -2, 2); 
	
	cout << endl << "<관심영역 변경 후>" << endl;
	print_locateROI("m2", m2);
	print_locateROI("m3", m3);

	cout << endl;
	cout << "[변경 m2] = " << endl << m2 << endl << endl;
	cout << "[변경 m3] = " << endl << m3 << endl;

	return 0;
}