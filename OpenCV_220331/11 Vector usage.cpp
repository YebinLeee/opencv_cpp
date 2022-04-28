#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 벡터 정보 출력
void print_vectorInfo(string v_name, vector<int> v) {

	cout << "[ " << v_name << " ] =";

	if (v.empty()) cout << "벡터가 비었습니다." << endl;
	else cout << ((Mat)v).reshape(1, 1) << endl;

	cout << ".size() = " << v.size() << endl;
}

int main() {

	int arr[] = { 10,20,30,40,50 };							// 벡터 초기화할 배열
	vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));	// 배열로 벡터 초기화

	print_vectorInfo("v1", v1); // 벡터 정보 출력

	v1.insert(v1.begin() + 2, 100);	// 벡터에 2번 인덱스(3번째 위치)에 원소 삽입
	print_vectorInfo("v1, insert(2)", v1);
	cout << ".capacity() = " << v1.capacity() << endl << endl;

	v1.erase(v1.begin() + 3);	// 3번 인덱스(4번째) 원소 제거
	print_vectorInfo("v1, erase(3)", v1);
	cout << ".capacity() = " << v1.capacity() << endl << endl;
	
	v1.clear();	// 벡터 원소 전체 삭제
	print_vectorInfo("v1, clear()", v1);

	return 0;
}