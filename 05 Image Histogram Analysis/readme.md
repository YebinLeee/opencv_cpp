# CH 05. 영상 히스토그램 분석

# 히스토그램 분석

- 픽셀 값 변환을 통해 밝기와 명암비를 조절했다면, 주어진 영상의 픽셀 밝기 분포를 조사하여 밝기 및 명암비를 적절하게 조절하는 방법에 대해 알아보자.

<br>

## 히스토그램 구하기

- **히스토그램(histogram)** : 영상의 픽셀 값 분포를 그래프 형태로 표현한 것
그레이스케일 영상의 경우, 각 그레이스케일 값에 해당하는 픽셀의 개수를 구하고 이를 막대 그래프 형태로 표현함으로써 히스토그램을 구할 수 있다. 컬러 영상의 경우, 3개의 색상 성분 조합에 따른 픽셀 개수 각각 계산하여 히스토그램 구성한다.

컴퓨터 비전에서의 히스토그램(histogram)이란,  영상의 픽셀 값 분포를 그래프 형태로 표현한 것이라 할 수 있다.

<img src="https://blog.kakaocdn.net/dn/cFGAav/btrSpvHTzHl/P3Igf8lk1jFYruJwmkHCDK/img.png">


위의 4x4 입력 영상은 각 픽셀이 0부터 7 사이의 밝기를 가질 수 있는 단순한 형태의 영상으로, 각각의 픽셀 값(밝기)에 대하여 그 개수를 막대 그래프로 표현하였다.

<br>

히스토그램 그래프의 가로축을 **빈(bin)** 이라 하고, 위의 그래프는 픽셀 값 0부터 7까지 표현한 것으로 빈의 개수가 총 7개라 할 수 있다. 그레이스케일의 경우 **256개의 빈** 을 갖는 히스토그램을 구하는 것이 일반적이다.

<br>

히스토그램의 빈 개수가 항상 픽셀 값 범위와 같아야 하는 것은 아니다. 경우에 따라 히스토그램의 빈 개수를 픽셀 값 범위보다 작게 설정할 수도 있는데, 아래 그림의 경우 8개의 밝기 값을 가지는 영상에서 히스토그램 빈 개수를 4로 설정할 수도 있다.

![https://blog.kakaocdn.net/dn/binvJi/btrSpl6qVPk/CnIbsrQXCrXFnSYMVNrX01/img.png](https://blog.kakaocdn.net/dn/binvJi/btrSpl6qVPk/CnIbsrQXCrXFnSYMVNrX01/img.png)

0번 빈의 경우는 픽셀 값이 0과 1인 픽셀 개수, 1번 빈의 경우 픽셀 값이 2 또는 3인 픽셀의 개수를 나타냈다.

일반적으로 히스토그램의 빈 개수가 줄어들면, 히스토그램이 표현하는 영상의 픽셀 값 분포 모양이 좀 더 대략적인 형태로 바뀐다. 반대로 빈 개수가 많으면 세밀한 픽셀 값 분포 표현이 가능하다.

<br>

### calcHist()

OpenCV에서 영상의 히스토그램을 구하려면 `calcHist()` 함수를 사용한다. 이는 한 장의 영상 뿐 아니라 여러 장의 영상 그리고 여러 채널로부터 히스토그램을 구할 수 있다. 히스토그램 빈 개수도 조절이 가능하다. 


![https://blog.kakaocdn.net/dn/2bSFp/btrSrnhU6m1/odnX3qOPKffoXWMGBNZrhK/img.png](https://blog.kakaocdn.net/dn/2bSFp/btrSrnhU6m1/odnX3qOPKffoXWMGBNZrhK/img.png)

모두 10개의 인자를 가지고 있으며, 마지막의 uniform, accumulate 값은 각각 true, false로 기본 값을 가지고 있으므로 총 8개의 인자를 필수적으로 지정해줘야 한다.

<br>

우선 그레이스케일 영상으로부터 256개의 빈으로 구성된 히스토그램을 생성하는 함수는 다음과 같다.

```cpp
// 그레이스케일 영상으로부터 256개의 빈을 갖는 히스토그램 행렬 생성
Mat calcGrayHist(const Mat& img) {
	// img 영상이 그레이스케일 영상인지 검사 (아닌 경우 에러 발생 후 프로그램 종료)
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 }; // 그레이스케일 1채널
	int dims = 1;	// 1차원 행렬
	const int histSize[] = { 256 }; // 첫번째 채널 값의 범위를 256개 빈으로 나눔
	float graylevel[] = { 0,256 }; // 그레이스케일 값의 최솟값, 최댓값 지정
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}
```

위 함수를 통해 얻은 히스토그램 행렬은 CV_32FC1 타입을 갖는 256 x 1 크기의 행렬이다. 즉, hist 행렬의 행 개수는 256, 열 개수는 1이다.

<br>

이제 막대그래프의 형태로 나타내기 위해서는 hist 행렬을 참조하여 막대그래프 영상을 생성해야 한다.

256개의 빈을 갖는 hist 행렬로부터 가로가 256픽셀, 세로가 100픽셀인 크기의 히스토그램 영상을 생성해보자.

```cpp
// 히스토그램 행렬을 나타내는 막대 그래프 생성
Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256)); // 256개의 빈으로 구성된 히스토그램 행렬인지 검사

	double histMax;
	minMaxLoc(hist, 0, &histMax); // hist 행렬 원소의 최솟값 0, 최댓값을 histMax에 저장

	Mat imgHist(100, 256, CV_8UC1, Scalar(255)); // 흰색으로 초기화된 256x100 크기의 새 영상 생성
	// 각각의 빈에 대한 히스토그램 그래프 그리기
	for (int i = 0;i < 256;i++) {
		// 히스토그램 막대그래프의 최대 길이를 100픽셀로 설정
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0)*100 / histMax)), Scalar(0));
	}
	return imgHist;
}
```

<br>

앞서 작성한, 히스토그램 행렬을 생성하는 calcGrayHist()와 막대 그래프로 나타내는 getGrayHistImage() 함수를 사용하여 레나 영상의 히스토그램을 화면에 출력해보자.

```cpp
Mat src = imread("lenna256.bmp", IMREAD_GRAYSCALE);

imshow("src", src);
imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
waitKey(0);
```

![https://blog.kakaocdn.net/dn/TUQ9K/btrSs00HBUk/1osl7d6mKhhpgWqDtYK0w0/img.png](https://blog.kakaocdn.net/dn/TUQ9K/btrSs00HBUk/1osl7d6mKhhpgWqDtYK0w0/img.png)

결과는 위와 같다. 레나 영상 자체 만으로는 픽셀 값이 두드러지게 나타나는 부분을 찾기가 어려운데,

아래의 카메라맨 영상는 픽셀 값이 분포된 영역이 두 군데 나타내는 것을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/cAnilO/btrStRPZYYK/POXV6g8sDeozawZxXfquj0/img.png](https://blog.kakaocdn.net/dn/cAnilO/btrStRPZYYK/POXV6g8sDeozawZxXfquj0/img.png)

검정색에 가까운 어두운 옷과 머리에 해당하는 부분이 A영역,

그리고 조금 더 밝은 부분에 해당하는 하늘, 잔디밭 부분이 B 영역으로 나타난다고 볼 수 있다.

<br>

### **밝기와 명암비에 따른 영상과 히스토그램의 상관 관계**

밝기와 명암비가 다른 여러 레나 영상을 이용해 영상과 히스토그램의 상관관계를 살펴보자.

원본 레나 영상에 밝기를 30만큼 증가시킨 (b)의 경우, 히스토그램의 분포가 전체적으로 오른쪽으로 이동한 것을 확인할 수 있다.

밝기를 낮춘 (c)의 경우는 전체적으로 왼쪽으로 분포도가 이동하였다.

![https://blog.kakaocdn.net/dn/b6sNRn/btrSqL4wHLm/bcwnD6eoEhRsvdDeDTTdUk/img.png](https://blog.kakaocdn.net/dn/b6sNRn/btrSqL4wHLm/bcwnD6eoEhRsvdDeDTTdUk/img.png)

(d)의 경우 명암비를 증가시켜, 밝은 부분과 어두운 부분의 차이를 증가시켰더니, 히스토그램 그래프가 그레이스케일 값 범위 전체 구간에 골고루 넓게 분포되어 나타났다.

반대로 (e)와 같이 명암비를 감소시켰더니, 그래프 가운데 일부 구간에 몰려 나타났다.

![https://blog.kakaocdn.net/dn/Os4ii/btrSpk7GiwM/gAbHko0DOvH8O3ROku4oj0/img.png](https://blog.kakaocdn.net/dn/Os4ii/btrSpk7GiwM/gAbHko0DOvH8O3ROku4oj0/img.png)

이를 통해, 히스토그램의 픽셀 분포 그래프는 영상의 밝기와 명암비를 가늠할 수 있는 유용한 도구로 사용될 수 있다

<br>

---

## 히스토그램 스트레칭

**히스토그램 스트래칭(Histogram Stretching)** 이란, 영상의 히스토글매이 그레이스케일 전 구간에 걸쳐서 나타나도록 변경하는 선형 변환 기법이다.

보통 명암비가 낮은 영상은 히스토그램이 특정 구간에 집중되어 나타나는데, 이러한 히스토그램을 마치 고무줄을 잡아 늘이듯 펼쳐서 히스토그램 그래프가 그레이스케일 전 구간에서 나타나도록 변환하는 기법이다. 히스토그램 스트레칭을 수행한 영상은 명암비가 높아져서 대체로 선명하고 보기 좋은 사진으로 바뀐다.

<br>

히스토그램 스트레칭의 수식은 다음과 같이 표현할 수 있다.

![https://blog.kakaocdn.net/dn/vu1cn/btrSrnhVwhn/oxGWizADSmSEIr0KcQBCCk/img.png](https://blog.kakaocdn.net/dn/vu1cn/btrSrnhVwhn/oxGWizADSmSEIr0KcQBCCk/img.png)

Gmax가 입력 영상의 픽셀 값중 가장 큰 그레이스케일 값, Gmin이 가장 작은 그레이스케일 값이라 할 때,

그레이스케일 전체 분포를 양방향으로 늘려 Gmin은 0으로, GMax는 255가 되도록 변환하는 수식이다.

<br>

다음과 같이 히스토그램 스트레칭을 통해, (a)의 레나 영상이 (c) 영상으로 변환되어 명암비가 증가하여 더욱 뚜렷한 이미지가 나타남을 확인할 수 있다.

히스토그램 그래프의 분포도 또한 전체적으로 양 옆으로 늘어났고, 픽셀 값의 최솟값이었던 Gmin은 0으로, 최댓값이었던 Gmax는 255 값으로 변환된 것 또한 확인할 수 있다.

![https://blog.kakaocdn.net/dn/cIxRLL/btrSsQ4X4Bf/pyASdbG8UXOiQ9UVoctebk/img.png](https://blog.kakaocdn.net/dn/cIxRLL/btrSsQ4X4Bf/pyASdbG8UXOiQ9UVoctebk/img.png)

위의 (b)의 변환 함수 그래프를 통해 히스토그램 스트레칭을 수행하게 되는데,

이는 (Gmax, 0), (Gmin, 255)을 각각 지나가는 직선의 방정식을 구하여 얻을 수 있다.

<br>

아래와 같이 직선의 기울기와 y 절편을 구하면 되는데,

직선의 기울기는 255 / (Gmax - Gmin) 이고, y절편은 비례식을 이용해 구하면 -255*Gmin / (Gmax - Gmin) 으로,

결과적으로 직선의 방정식은 다음과 같이 결정된다.

![https://blog.kakaocdn.net/dn/bZWcaE/btrSqMbiVfP/adtfAynmxlcbDy1JJWkkX0/img.png](https://blog.kakaocdn.net/dn/bZWcaE/btrSqMbiVfP/adtfAynmxlcbDy1JJWkkX0/img.png)

<br>

히스토그램 스트레칭을 수행하기 위한 함수는 OpenCV에서 제공하지 않지만,

기본적인 산술 연산 재정의를 지원하므로, Gmin과 Gmax 값을 minMaxLoc() 함수를 사용하면 위의 수식을 소스 코드로 변경할 수 있다.

```cpp
// 히스토그램 스트레칭
void histogram_stretching() {
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax); // 그레이스케일 영상의 최솟값과 최댓값 구하기
	Mat dst = (src - gmin) * 255 / (gmax - gmin); // 히스토그램 스트레칭 수식 적용하여 dst에 적용

	// 입력 영상의 히스토그램 그래프
	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	// 결과 영상의 스트레칭 결과 히스토그램 그래프
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}
```

결과는 다음과 같다.

가운데에서 약간 오른쪽 위치에 분포해있던 히스토그램 그래프가 전체적으로 양 옆으로 넓게 퍼지며,

영상은 전체적으로 어두워졌고 명암비가 증가하여 뚜렷한 이미지가 나타탐을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/bxAX7U/btrStAt20lC/XmZcq08mCh6hlJYrr2h2i0/img.png](https://blog.kakaocdn.net/dn/bxAX7U/btrStAt20lC/XmZcq08mCh6hlJYrr2h2i0/img.png)

---

<br>

## 히스토그램 평활화

**히스토그램 평활화(Histogram Equalization)** 은 히스토그램 스트레칭과 더불어, 영상의 픽셀 값 분포가 그레이스케일 전체 영역에서 골고루 나타나도록 변경하는 알고리즘 중 하나이다.

이는 히스토그램 그래프에서 특정 그레시으케일 값 근방에서 픽셀 분포가 너무 많이 뭉쳐 있는 경우 이를 넓게 펼쳐 주는 방식으로 픽셀 값 분포를 조절한다.

히스토그램 평활화는 히스토그램 균등화, 히스토그램 평탄화라는 용어로도 번역되어 사용되고 있다.

<br>

히스토그램 그레이스케일 값 g에 대하여, 해당 g의 픽셀 개수를 함수 h(g) 로 표현해보자.

히스토그램 평활화를 계산하기 위해서는 누적함수 H(g)를 구해야 한다.

![https://blog.kakaocdn.net/dn/buTDH6/btrSro8YyWi/QYUPPUJcNTOZPNDeIK0710/img.png](https://blog.kakaocdn.net/dn/buTDH6/btrSro8YyWi/QYUPPUJcNTOZPNDeIK0710/img.png)

히스토그램 평활화는 H(g)를 픽셀 값 변환 함수로 사용하는데, 우선 H(g) 함수의 최댓값이 255가 되도록 정규화 과정을 거쳐야 한다.

입력 영상의 픽셀 개수를 NM이라 표기할 때, 히스토그램 평활화는 다음의 형태로 정의된다.

![https://blog.kakaocdn.net/dn/d1syPz/btrSnWZ6W1D/SUgKxuB5EKsJKB04QKFfS1/img.png](https://blog.kakaocdn.net/dn/d1syPz/btrSnWZ6W1D/SUgKxuB5EKsJKB04QKFfS1/img.png)

Lmax는 영상이 가질 수 있는 최대 밝기 값을 의미한하고, (일반적으로는 Lmax=255이다.) round()는 반올림 함수를 나타낸다.

4x4의 간단한 예시 영상을 통해 확인해보자.

h(g)는 0~7 사이의 픽셀값 g에 대한 픽셀 개수를 나타내는 함수이며, H(g)는 누적 함수이다.

영상의 최대 밝기 값이 7이고, 전체 픽셀 개수가 16이므로 정규화를 위한 상수는 7/16으로, 각각의 H(g)이 7/16을 곱한 값을 결과 영상의 픽셀 값으로 설정하게 된다.

<br>

결국 정규화 과정을 거친 결과는 (c)와 같이 나타난다.

![https://blog.kakaocdn.net/dn/ntoql/btrSq8yrRJ0/Zi0hsXoubbBWyVPk89OFg0/img.png](https://blog.kakaocdn.net/dn/ntoql/btrSq8yrRJ0/Zi0hsXoubbBWyVPk89OFg0/img.png)

OpenCV에서는 그레이스케일 영상의 히스토그램 평활화를 수행하는 equalizeHist() 함수를 제공하는데, 함수 원형은 다음과 같다.

![https://blog.kakaocdn.net/dn/mB4Go/btrSm1URcZF/jtQRk7tz6X2pjuV0uNFlDK/img.png](https://blog.kakaocdn.net/dn/mB4Go/btrSm1URcZF/jtQRk7tz6X2pjuV0uNFlDK/img.png)

입력 영상은 8비트 1채널인 그레이스케일 영상 (CV_8UC1) 만 허용한다.

```cpp
// 히스토그램 평활화void histogram_equalization()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst;
	equalizeHist(src, dst);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}
```

입력 영상과 히스토그램 평활화를 수행한 결과 영상은 다음과 같이 나타난다.

히스토그램 평활화를 수행한 결과 영상의 히스토그램 그래프가 전체적으로 넓게 퍼져 분포되어 뚜렷한 결과 이미지가 나타남을 확인할 수 있다.