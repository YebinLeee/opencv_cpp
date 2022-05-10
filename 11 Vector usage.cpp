#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// ���� ���� ���
void print_vectorInfo(string v_name, vector<int> v) {

	cout << "[ " << v_name << " ] =";

	if (v.empty()) cout << "���Ͱ� ������ϴ�." << endl;
	else cout << ((Mat)v).reshape(1, 1) << endl;

	cout << ".size() = " << v.size() << endl;
}

int main() {

	int arr[] = { 10,20,30,40,50 };							// ���� �ʱ�ȭ�� �迭
	vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));	// �迭�� ���� �ʱ�ȭ

	print_vectorInfo("v1", v1); // ���� ���� ���

	v1.insert(v1.begin() + 2, 100);	// ���Ϳ� 2�� �ε���(3��° ��ġ)�� ���� ����
	print_vectorInfo("v1, insert(2)", v1);
	cout << ".capacity() = " << v1.capacity() << endl << endl;

	v1.erase(v1.begin() + 3);	// 3�� �ε���(4��°) ���� ����
	print_vectorInfo("v1, erase(3)", v1);
	cout << ".capacity() = " << v1.capacity() << endl << endl;
	
	v1.clear();	// ���� ���� ��ü ����
	print_vectorInfo("v1, clear()", v1);

	return 0;
}