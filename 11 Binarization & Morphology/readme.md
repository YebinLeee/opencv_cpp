# CH 11 영상의 이진화와 모폴로지

# **영상의 이진화 (Binarization)**

영상의 **이진화 (binarization)** 은 영상의 각 픽셀을 두 개의 부류로 나누는 작업이다. 이는 그레이스케일 영상의 픽셀 값을 0 또는 255로 변환하는 기법인데, 이는 영상에서 관심있는 객체 영역 (ROI, Region of Interest) 과 배경 영역을 구분하거나 관심 영역과 비관심 영역으로 구분하는 용도로 널리 사용된다. 이진화가 적용된 이진 영상은 보통 흰색과 검은색 픽셀로만 구성된다.

<br>

아래가 다양한 영상에 대해 이진화를 수행한 결과이다. 윗줄은 그레이스케일 영상이고, 아래 줄은 적절한 방법으로 이진화가 수행된 결과 영상이다.

(a)의 경우 왼쪽에 위치한 흑백 사각형 마커가 두드러지도록 이진화를 적용한 결과이며,

(b)는 문서를 스캔한 영상에서 배경과 글자 영역을 뚜렷하게 구분하기 위해 이진화가 사용되었으며,

(c)의 경우 지문 인식을 위한 전처리로 이진화가 사용된 예이다.

<img src="https://blog.kakaocdn.net/dn/bPUoat/btrUacTtGt7/st7YGajYpqczcFciLox7S1/img.png" width=500>

<br>

영상의 이진화는 기본적으로 영상의 각 픽셀 값을 이용하는데, 그레이스케일 영상에 대한 이진화를 수행하는 경우 영상의 픽셀 값이 어떠한 특정 값인 임계값(threshold)보다 크면 255로, 작으면 0으로 설정한다.

영상의 이진화를 수식으로 표현하면 다음과 같다.

<img src="https://blog.kakaocdn.net/dn/0PpBu/btrT97Y1OsU/0HFsRTmrLSSzs4oGzsdXB0/img.png" width=200>

src는 입력 영상, dst는 출력 영상을 의미하고, T는 임계값을 나타낸다. 임계값은 사용자의 경험에 의해 임의로 지정하거나, 또는 영상의 특성을 분석하여 자동으로 결정할 수도 있다.

임계값은 영상의 이진화를 수행하는 목적에 따라 적절하게 결정해야 한다.

<br>

아래 그림의 예는 혈액 속 세포를 촬영한 입력 영상에 대하여 서로 다른 임계값을 사용하여 영상을 이진화한 결과를 나타내고 있다. 촬영된 세포 중, 특정 약품에 의해 염색되어 검은색으로 관찰되는 세포가 있는데, (b)가 이 영상의 히스토그램을 나타낸 것이다. 입력 영상에서 흰색과 배경과 밝은 회색 세포 영역으로부터 두 개의 큰 분포가 형성되어 있고, 검은색으로 염색된 픽셀에 의한 분포가 미세하게 발견된다.

만약 임계값을 T1으로 설정하여 이진화를 수행하면 (c)의 그림과 같이 기존에 검은색으로 나타났던 영역만 검은색으로 나타나는 이진 영상을 얻을 수 있고, 밝은 회색 분포와 흰색 배경 픽셀 분포 사이의 T2를 임계값으로 설정하면, 모든 세포 영역을 검출한 (d)의 결과 영상을 얻을 수 있다.

따라서 임계값을 어떻게 설정하는지에 따라 서로 다른 의미를 갖는 이진화 영상을 얻을 수 있다.
<img src="https://blog.kakaocdn.net/dn/bhJH8z/btrT6XiQQPP/sMNRqzZCnnw1LMB4fhFc8K/img.png" width=500>

<br>

### **threshold() 함수**

OpenCV는 임계값을 이용해 이진화와 관련된 다양한 연산을 지원하는 threshold() 함수를 제공하고 있으며, 원형은 다음과 같다.

<img src="https://blog.kakaocdn.net/dn/zsYXS/btrT81yqZLv/CJQLG2UkXv4r5KPvwpZ3nk/img.png" width=400>



함수는 마지막 type 인자에 지정하는 열거형 상수 ThresholdTypes 에 따라 수행하는 동작이 결정된다.

ThresholdTypes는 다음과 같다.

<img src="https://blog.kakaocdn.net/dn/cTJU3Q/btrUbrboJaB/Phb7HISSzKga15QjcigvJ0/img.png" width=300>

<br>


threshold() 함수를 이용해 영상을 이진화하려면 maxval 인자에 255를 지정하고, type 인자에는 THRESH_BINARY 또는 THRESH_BINARY_INV 를 지정해야 한다. 후자는 전자의 방법으로 이진화를 수행한 후 영상을 반전하는 것과 동일하다.

문서 영상을 임계값 128을 이용해 이진화를 수행하는 경우 다음과 같이 작성할 수 있다.

```cpp
Mat src = imread("document.bmp", IMREAD_GRAYSCALE);

Mat dst;
threshold(src, dst, 128, 255, THRESH_BINARY);
```

결과는 다음과 같다. (b)의 경우 임계값 128을 넘는 경우 255 검은색으로, 넘지 않거나 같은 경우 0 흰색으로 픽셀 값이 변경된다. 따라서 128보다 픽셀 값이 적은 옅은 회색의 경우 흰색 픽셀로 변경되었고, 글씨 부분은 255로 변경된 것을 확인할 수 있다.

<img src="https://blog.kakaocdn.net/dn/S0alU/btrT9HfoKzs/1reskSlQOfEIWGZaWSle10/img.png" width=500>

<br>

THRESH_OTSU와 THRESH_TRIANGLE은 임계값을 자동으로 결정할 때 사용한다. 두 방법 모두 영상의 픽셀 값 분포를 분석하여 임계값을 자동으로 결저하고, 결정된 임계값을 이용해 임계값 연산을 수행한다. **THRESH_OTSU** 상수는 오츠(Otsu)가 제안한 **자동 이진화 임계값 결정 알고리즘**을 이용하여 임계값을 결정하며, 이는 입력 영상의 픽셀 값 분포가 두 부류로 구분되는 경우 최적의 임계값을 결정하는 알고리즘이다. 자동 이진화를 수행하는 경우에는 threshold() 함수의 세번째 인자로 임계값은 사용되지 않는다. 더하여 CV_8UC1 타입의 영상에서만 자동 임계값 결정 방법을 적용할 수 있다.

<br>

아래 예제는 THRESH_BINARY와 THRESH_OTSU 상수를 함께 지정하여 오츠 알고리즘에 의해 결정된 임계값이 th 변수에 저장된다. (th 값은 88이 저장된다.)

```cpp
Mat src = imread("document.bmp", IMREAD_GRAYSCALE);

Mat dst;
int th = (int)threshold(src, dst, 0, 255, THRESH_OTSU | THRESH_BINARY);
```

이에 대한 결과 영상은 다음과 같이 나타난다.

<img src="https://blog.kakaocdn.net/dn/xCK21/btrUaq46Z7A/wZhvKFNfKUFir2xkfetkKk/img.png" width=400>

<br>


이번에는 다양한 임계값을 이용해 이진화를 수행하고 그 결과를 바로 확인하는 예제를 실행해보자.

아래 예제는 사용자가 지정한 트랙바의 위치에 해당하는 임계값에 따라 이진화를 수행하여 결과 영상이 달라지는 예제이다.

```cpp
// threshold 콜백 함수 (사용자가 지정한 트랙바 위치에 따라 이진화 수행)void on_threshold(int pos, void* userdata)
{

	Mat src = *(Mat*)userdata;

	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY);// 사용자의 위치 pos에 따라 이진화 수행imshow("dst", dst);
}

// 트랙바를 이용한 위치에 해당하는 임계값에 따라 이진화 수행void binarization_trackbar()
{
	Mat src;
	src = imread("sudoku.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src);// 트랙바 생성 (on_threshold 콜백함수 등록)setTrackbarPos("Threshold", "dst", 128);// 트랙바 처음 위치 128로 설정waitKey(0);
	return;
}
```

<br>

on_threshold() 콜백 함수는 사용자가 지정한 트랙바 위치 pos 해당하는 임계값에 따라 threshold() 함수를 실행하여 src 원본 영상에 대한 이진화를 수행하여 dst 결과 영상에 나타낸다.

binaraization_trackbar() 함수 내에서 sudoku 이미지를 원본 영상 src로읽어, creaetTrackbar() 함수에 on_threshold 함수를 콜백함수로 등록하여, src 영상에 대한 결과를 dst에 보이도록 하였다. setTrackbarPos() 함수로 트랙바의 초기 위치를 128로 지정하였다.

처음 src, dst 영상은 다음과 같이 나타난다. 트랙바 위치가 처음에 128에 놓여있는 것을 확인할 수 있다.

128을 임계값으로 하여 이진화를 수행하게 되는 경우, 전체적으로 어두운 원본 스캔 이미지에 대해

왼쪽 하단부 부터 중앙 부분까지의 픽셀 값이 128 이상인 경우 255 검은색으로 모두 변경되어 영상 자체가 훼손된 것을 확인할 수 있다.

<img src="https://blog.kakaocdn.net/dn/cFoOPE/btrUfsuFnrc/ULZTO0o0Nxk1O3Z6LRsJ0K/img.png" width=500>


트랙바를 적절한 위치로 조정한 결과 다음과 같이 모든 숫자가 명확하게 보이는 것을 확인할 수 있다.

임계값이 약 55가 되었을 때, 해당 영상에 적절한 이진화가 수행되는 것으로 판단할 수 있다.

<img src="https://blog.kakaocdn.net/dn/2j14n/btrUfQos6jp/zYK0YY35LLSpBYkBip5aL1/img.png" width=500>

<br>

모든 숫자가 명확해졌지만, 문제점은 원본 영상의 배경이 전체적으로 불균일하여 스도쿠 퍼즐의 사각형 직선이 심하게 끊어지는 현상이 발생했다는 점이다.

이를 어떻게 해결할 수 있을까?

<br>

---

## **적응형 이진화 (Adaptive Binarization)**


위에서 설명한 threshold() 함수는, 지정한 임계값을 영상 전체 픽셀에 동일하게 적용하여 이진화 영상을 생성한다. 이와 같이 영상의 모든 픽셀에 동일한 임계값을 적용해 이진화를 수행하는 방식을 전역 이진화 (global binarization) 라고 한다.

그러나, 균일하지 않은 조명 환경에서 촬영된 영상의 경우 객체와 배경이 이진화에 의해 적절히 분리되지 않는 경우가 발생하는 등 영상의 특성에 따라 전역 이진화를 적용하기 어려운 경우가 있다.

위의 sudoku 이미지도 마찬가지이다. 약 55의 임계값을 지정하여 이진화를 수행했을 때 좌측 하단의 스도쿠 숫자까지 제대로 이진화가 수행되었지만, 반대로 오른쪽 상단의 숫자가 매우 흐려지고 스도쿠 퍼즐의 사각형 직선도 심하게 끊어지는 현상이 발생했다.

<br>


불균일한 조명 성분을 갖고 있는 영상에 대해서는 하나의 임계값으로 객체와 배경을 제대로 구분하기 어려우므로, 각 픽셀마다 서로 다른 임계값을 사용하는 **적응형 이진화 (Adpative Binarization)** 기법을 사용하는 것이 효과적이다.

이는 영상의 모든 픽셀에 정해진 크기의 사각형 블록 영역을 설정하고, 블록 영역 내부의 픽셀 값 분포로부터 고유의 임계값을 결정하여 이진화하는 방식이다. *(x,y)* 좌표에서의 임계값 *T(x,y)*는 다음 수식을 이용해 결정한다.

<img src="https://blog.kakaocdn.net/dn/bNI5KM/btrUfwqgXSc/3MYVgJ5tKKbyPtHrGAnQ41/img.png" width=150>

<br>


여기서 *μ(x,y)*는 *(x,y)* 주변 블록 영역의 픽셀 값 평균이고, 상수 *C*는 임계값의 크기를 조정하는 상수이다. 블록 내부 픽셀 값의 평균  *μ(x,y)*은 일반적인 산술 평균을 사용하거나 또는 가우시안 함수 형태의 가중치를 적용한 가중 평균을 사용한다. 상수 *C*는 영상의 특성에 따라 사용자가 결정한다.

<br>

### **adaptiveThreshold() 함수**

OpenCV에서 적응형 이진화는 adaptiveThreshold() 함수를 이용하여 수행할 수 있으며 원형은 다음과 같다.

<img src="https://blog.kakaocdn.net/dn/MxsDW/btrUbxKKFkd/0phWr7M6n5VlEIg7bWfYWK/img.png" width=400>


위 함수는 각 픽셀 주변의 blockSize x blockSize 영역에서 평균을 구하고, 평균에서 상수 C를 뺀 값을 해당 픽셀의 임계값으로 사용한다. 이 때 블록 영역의 평균을 구하는 방식은 adpativeMethod 인자를 통해 설정할 수 있으며, ADAPTIVE_THRESH_MEAN_C로 지정하면 주변 영역 픽셀로부터의 산술 평균을 구하고, ADAPTIVE_THRESH_GAUSSIAN_C를 지정하면 가우시안 마스크를 적용하여 가우시안 가중 평균을 계산한다.

<br>


sudoku 이미지에 대하여, 가우시안 평균을 이용하여 블록 사이즈 내 적응형 이진화를 수행하는 예제를 살펴보자.

```cpp
// 적응형 이진화 수행을 위한 트랙바 callback 함수void on_trackbar(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;

	int bsize = pos;// block 영역의 sizeif (bsize % 2 == 0)bsize--;// 짝수인 경우 1을 빼서 홀수로 변경if (bsize < 3) bsize = 3;// 3보다 작은 경우 3 최솟값으로 변경

	Mat dst;
// 가우시안 평균을 구하여 적응형 이진화 수행adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);

	imshow("dst", dst);
}

// 적응형 이진화 수행void adaptive_threshold()
{
	Mat src;
	src = imread("sudoku.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Block Size", "dst", 0, 200, on_trackbar, (void*)&src);// trackbar 콜백 함수 등록setTrackbarPos("Block Size", "dst", 11);// 트랙바 초기 위치를 11로 지정waitKey(0);
	return;
}
```

트랙바 초기 위치 11에 해당하는 적응형 이진화 수행 결과 영상은 다음과 같다.

<img src="https://blog.kakaocdn.net/dn/cClhLq/btrUeYgFjyq/vUKeVZ5GAX3canUVbib2z1/img.png" width=500>


<br>

이번에는 트랙바 위치를 조정하여 블록 사이즈를 58로 지정한 경우이다.

전체적으로 스도쿠 글씨와 사각형 외곽선이 검은색으로 이진화되어 구분이 잘 되어, 비교적으로 더 또렷한 결과 영상이 나타난 것을 확인할 수 있다.

<img src="https://blog.kakaocdn.net/dn/JE6LQ/btrUceYCq3c/U9wYkW81zRDbb9SkoHqVY0/img.png" width=500>

<br>


---

## **모폴로지 연산 (Morphology)**

모폴로지 연산은 영상 내부 객체의 형태와 구조를 분석하고 처리하는 기법이다. 이는 그레이스케일 영상과 이진 영상에 모두 적용 가능하지만, 주로 이진화된 영상에서 객체의 모양을 변형하는 용도로 사용된다.

이진 영상에서 사용되는 기본적인 모폴로지 연산 동작에 대해 이해해보고, 모폴로지 함수 사용 방법에 대해 알아보자.

<br>

## **이진 영상의 침식과 팽창**

**모폴로지(Morphology)** 는 형태 또는 모양에 관한 학문을 의미한다. 영상 처리 분야에서 모폴로지는 영상에서 객체의 형태 및 구조에 대해 분석하고 처리하는 기법을 의미하며, 수학적 모폴로지(mathematical morphology)라고도 한다. 모폴로지 그레이스케일 영상과 이진 영상에 대해 모두 적용할 수 있지만, 주로 이진 영상에서 객체의 모양을 단순화시키거나 잡음을 제거하는 등의 용도로 사용된다.

모폴로지 연산을 정의하려면 먼저 **구조 요소(structuring element)** 를 정의해야 한다. 구조 요소란 마치 필터링에서 사용되는 마스크처럼 모폴로지 연산의 동작을 결정하는 작은 크기의 행렬을 말한다. 다양한 크기와 모양의 구조 요소의 예는 다음과 같다.

<img src="https://blog.kakaocdn.net/dn/DMg8Y/btrUfrCK7Hs/lqQP7KiKcXZSllyVPuKCH0/img.png" width=350>

<br>

필요에 따라 원하는 구조 요소를 선택하여 사용할 수 있지만, 대부분의 모폴로지 연산에서는 4번째에 나타난 3x3 정방형 구조 요소를 사용한다. 각각의 구조 요소 행렬에서 진한 색으로 표시한 원소는, 연산 결과가 저장될 위치를 나타내는 **고정점(anchor point**)이며, 대부분의 경우 구조 요소의 중심을 고정점으로 사용한다.

<br>

영상의 모폴로지 기법 중 가장 기본이 되는 연산은 **침식(erosion)**과 **팽창(dilation)**이다.

침식 연산은 객체 영역의 외곽을 골고루 깎아 내는 연산으로 전체적으로 객체 영역이 축소되고 배경이 확대된다. 침식 연산은 구조 요소를 영상 전체에 대해 스캔하면서, 구조 요소가 객체 영역 내부에 완전히 포함될 경우, 고정점 위치 픽셀을 255로 설정한다.

팽창 연산은 객체 외곽을 확대하는 연산이다. 이로 인해 객체 영역이 확대되며 배경 영역이 줄어든다. 팽창 연산은 구조 요소를 영상 전체에 대해 이동시키면서, 구조 요소와 객체 영역이 한 픽셀이라도 만날 경우 고정점 위치 픽셀을 255로 설정한다.

작은 크기의 영상에서 3x3 정방형 구조 요소를 사용해 침식, 팽창 연산을 수행한 결과는 다음과 같다.

<img src="https://blog.kakaocdn.net/dn/vK6db/btrUdhnomr9/mBfKa71AasK0VH3W5tNHW1/img.png" width=350>

<br>

12x12 크기의 입력 이진 영상 (a)에 대하여 3x3 크기의 정방형 구조 요소 (b)를 침식 연산한 결과가 (c)이고 팽창 연산한 결과가 (d)로 나타난다. 침식 연산에 의해 윗 부분이 매끄럽게 깎인 것을 확인할 수 있다. 그리고 팽창 연산에 의해서는 객체 아래 쪽에 작게 패인 부분이 깔끔하게 메워진 것을 확인할 수 있다.

<br>

### **getStructuringElement() 함수**

OpenCV 에서 구조 요소는 원소 값이 0 또는 1로 구성된 CV_8UC1 타입의 Mat 행렬로 표현하며, 널리 사용되는 모양의 구조 요소 행렬을 간단하게 생성하는 getStructuringElement() 함수를 제공한다.

<img src="https://blog.kakaocdn.net/dn/cGMZ5N/btrUfhtCzIk/OqZG8mK9cWGwxxkQXAyBR1/img.png" width=400>

위 함수는 지정한 모양과 크기에 해당하는 구조 요소 행렬을 반환하고, 첫번째 인자 shape는 구조 요소 모양을 결정하는 역할을 하며, MorphShapes 열거형 상수와 의미는 다음의 표에서 자세하게 확인할 수 있다.

구조 요소의 크기는 ksize 인자를 통해 지정하며 보통 가로와 세로 크기는 모두 홀수로 지정한다.

<br>

<img src="https://blog.kakaocdn.net/dn/bdkMlV/btrUbqyArdB/PcVkDClJW0yftiGXzCgUWk/img.png" width=400>

<br>

### **erode() 함수**

OpenCV 에서 영상의 침식 연산은 erode() 함수를 이용해 수행하며, 원형은 다음과 같다.

src, dst, kernel 인자를 제외한 나머지는 기본값이 설정되어 있으므로 생략이 가능하다.

kernel에는 getStructuringElement() 함수로 생성한 구조 요소 행렬을 지정할 수 있다. 다만 해당 인자에 Mat() 또는 noArray() 를 지정하면 3x3 정방형 구조 요소를 사용해 자동 침식 연산을 수행한다.

<img src="https://blog.kakaocdn.net/dn/bgmrdB/btrUhm1KWRN/f8F8orPQOoO7q4UzrV1P0k/img.png" width=400>

<br>


### **dilate() 함수**

팽창 연산은 dialte() 함수를 사용하며 원형은 다음과 같으며, erode() 함수와 인자 구성이 완전히 동일하다.

<img src="https://blog.kakaocdn.net/dn/c8hSLk/btrUfrwfCWN/Cr7K5sV2WkPc8bgBKD4hK0/img.png" width=400>

<br>

erode()와 dilate() 을 이용하여 모폴로지 침식과 팽창 연산을 수행하는 예제를 살펴보도록 하자.

```cpp
// 모폴로지 침식, 팽창 연산 수행void erode_dilate()
{
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);// otsu 알고리즘으로 자동 이진화 수행

	Mat dst1, dst2;
	erode(bin, dst1, Mat());// 3x3 정방형 구조 요소를 이용한 침식 연산dilate(bin, dst2, Mat());//  3x3 정방형 구조 요소를 이용한 팽창 연산imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}
```

mildrop.bmp 영상을 이진화한 후, 침식과 팽창 연산을 각각 수행하여 결과를 화면에 출력하면 다음과 같다.

src 원본 이미지에 대해 오츠 알고리즘을 이용해 이진화 한 결과가 bin 에 나타나고 있다.

침식 결과인 좌측 하단의 erode 결과 영상을 보면, bin 영상에 비해 객체 외관이 다소 작아졌고, 영상의 우측 하단에 있는 작은 한두 픽셀 짜리의 작은 흰색 객체가 사라진 것을 확인할 수 있다.

팽창 결과인 우측 하단의 dilate 결과 영상을 보면 객체 외관이 확대되었으며, 객체 내부의 검은색 구멍은 사라지거나 좁아진 것을 확인할 수 있다.

<br>

<img src="https://blog.kakaocdn.net/dn/Qo2F2/btrUdgbxPxz/sGanweHmZahJKcw6hzmV60/img.png" width=500>

<br>

---

## **이진 영상의 열기와 닫기**

모폴로지 기법 중에서 **열기(opening)**와 **닫기(closing)** 연산에 대해 알아보자. 열기와 닫기 연산은 위의 침식과 팽창 연산을 이용해 쉽게 구현할 수 있는 연산이다.

열기 연산은 입력 영상에 대해 침식 연산을 수행한 후, 다시 팽창 연산을 수행하는 연산이고 닫기 연산은 팽창 연산을 먼저 수행한 후, 침식 연산을 수행하는 연산이다.  열기와 닫기는 각각 침식과 팽창 연산이 한 번씩 적용되므로 객체 영역의 크기가 크게 바뀌지 않지만, 침식과 팽창 연산을 적용하는 순서에 따라 서로 다른 효과가 발생한다.

<br>

**열기 연산**의 경우, 침식을 먼저 수행하므로 한두 픽셀짜리 작은 영역이 먼저 제거된 후, 팽창 연산이 수행된다. 그 결과 입력 이진 영상에 존재하는 작은 크기의 객체가 효과적으로 제거된다.

**닫기 연산**은 팽창 연산을 먼저 수행하므로 객체 내부의 작은 구멍이 메워진 후에 침식 연산이 수행된다.

<br>

아래 그림을 통해 열기와 닫기 연산을 시각적으로 이해해보자.

<img src="https://blog.kakaocdn.net/dn/2MQTo/btrUeXbIryT/ixPo3YVXIukdxEFV9Kqtkk/img.png" width=500>


(a)의 원본 영상에 대해 3x3 정방형 구조 요소를 사용해 열기와 닫기 연산을 수행한 결과 (b)와 (c)를 살펴보자.

열기 연산의 결과 영상인 (b)를 통해 큰 객체 외곽에 돌출된 한두 픽셀이 제거되었고, 중앙의 위, 아래에 위치한 1x1 픽셀과 2x2 픽셀이 사라진 것을 확인할 수 있다.

닫기 연산 결과 영상인 (c)의 경우 객체 내부의 작은 구멍이 사라졌고, 오른쪽 객체 외곽에 오목하게 들어간 부분이 메꿔진 것을 확인할 수 있다.

<br>

### **morphologyEx() 함수**

morpholotyEx() 함수는 OpenCV에서 열기와 닫기 연산을 수행하며, 침식, 팽창과 같은 일반적인 모폴로지 연산도 수행할 수 있는 범용적인 모폴로지 연산 함수이다.

<img src="https://blog.kakaocdn.net/dn/dXI047/btrUdhuJlXX/jNraZWB2AUKtnTFJ2eBx8K/img.png" width=400>


위 함수는 세번째 인자 op를 지정하여 모폴로지 연산 방법을 지정한다. MorphTypes 열거형 상수를 통해 지정할 수 있으며, **MORPH_GRADIENT** 상수는 팽창 결과 영상에서 침식 결과 영상을 빼는 연산을 수행하며, 객체의 외곽선이 추출되는 효과가 있다.

<br>

<img src="https://blog.kakaocdn.net/dn/UwmsR/btrUgOR6fXf/UQybL6m5bba3h4AbHWgXi0/img.png" width=400>

<br>

morphologyEx() 함수를 이용해 이진 영상에 모폴로지 열기와 닫기 연산을 수행하는 예제를 살펴 보자.

```cpp
// 모폴로지 열기와 닫기 연산 수행void open_close()
{
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	morphologyEx(bin, dst1, MORPH_OPEN, Mat());// 3x3 정방형 구조 요소를 이용한 열기 연산morphologyEx(bin, dst2, MORPH_CLOSE, Mat());// 3x3 정방형 구조 요소를 이용한 열기 연산imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}
```

<br>

열기와 닫기 연산을 수행한 결과는 다음과 같다.

<img src="https://blog.kakaocdn.net/dn/nOYn7/btrUgPpVLen/r4yEFFIwwOkpbUlz9PWLLK/img.png" width=400>

opening 열기 연산 결과 영상의 경우, 영상의 우측 하단에 있던 미세한 한두픽셀짜리 영역이 효과적으로 제거되었고,

closing 닫기 연산 결과 영상의 경우, 흰색 객체 내부의 미세한 구멍들이 메꾸어져 사라진 것을 확인할 수 있다.

<br>

즉 요약해보자면,

**열기 연산은 침식 연산 후 팽창 연산을 수행한다. 따라서 객체 외부에 있는 미세한 영역을 효과적으로 제거하는데 쓰일 수 있는 기법이며,**

**닫기 연산은 팽창 연산 후 침식 연산을 수행한다. 따라서 객체 내부에 있는 미세한 영역을 효과적으로 제거하는데 쓰일 수 있는 기법이다.**