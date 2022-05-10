#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;
using namespace std;

int main() {

	vector<double> v1, v2;
	v1.reserve(10000000); // reserve - 벡터의 원소를 저장할 공간 예약


	// reserve() 사용

	double start_time = clock();
	for (int i = 0;i < v1.capacity();i++)
		v1.push_back(i);
	printf("v1.capacity() = %d\n",(int)v1.capacity());
	printf("reserve() 사용 %5.2f m2\n", (clock() - start_time));


	// reserve() 미사용
	
	start_time = clock();
	for (int i = 0;i < v1.capacity();i++)
		v2.push_back(i);
	printf("v1.capacity() = %d\n", (int)v1.capacity());
	printf("reserve() 미사용 %5.2f m2\n", (clock() - start_time));

	return 0;
}