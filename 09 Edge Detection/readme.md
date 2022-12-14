# CH 09. 에지 검출

# **영상의 에지 검출**

영상에서 **에지(edge)** 란 한쪽 방향으로 픽셀 값이 급격하게 바뀌는 부분으로, 픽셀 값의 변화율을 이용해 이를 찾을 수 있다. 2차원 디지털 영상에서 픽셀 값의 변화율을 근사화하여 구하는 방법과 다양한 응용에서 영상의 미분을 구하는 용도로 사용되고 있는 소벨 필터에 대해 알아보자.

<br>

## **1. 미분과 그래디언트**

에지란, 픽셀 값이 급격하게 바뀌는 부분으로 어두운 영역에서 갑자기 밝아지거나 반대로 밝은 영역에서 급격히 어두워지는 부분을 말한다. 일반적으로 객체와 배경의 경계, 또는 객체와 다른 객체의 경계에서 에지가 발생한다.

따라서 에지 검출은 컴퓨터 비전 시스템에서 객체의 윤곽을 알아내고, 객체를 판별하기 위한 전처리로 많이 사용되고 있다.

1차원 연속 함수 *f(x)*의 미분은 다음과 같이 정의한다.

![https://blog.kakaocdn.net/dn/btzsYX/btrSJmQOC0W/6cxGwpxfmeT0fhpNjbEooK/img.png](https://blog.kakaocdn.net/dn/btzsYX/btrSJmQOC0W/6cxGwpxfmeT0fhpNjbEooK/img.png)

Δx 는 x의 변화량을 의미하여, x의 변화량이 무한히 0에 가까워질 때의 함수값 변화량을 미분이라 한다. 함수 값이 증가하는 위치에서는 함수의 미분 값이 0보다 큰 양수로, 함수 값이 감소하는 위치에서는 미분 값이 0보다 작은 음수를 갖게 되어, 함수 값이 일정한 구간에서는 함수의 미분이 0에 가까운 값을 갖는다.

<br>

1차원 연속함수 *f(x)* 의 값 변화에 따른 미분 *f'(x)* 를 다음과 같이 나타낼 수 있다.

![https://blog.kakaocdn.net/dn/b0nXPM/btrSHNPtN0G/UjOK5XuKXeyXPo1K1dXsU0/img.png](https://blog.kakaocdn.net/dn/b0nXPM/btrSHNPtN0G/UjOK5XuKXeyXPo1K1dXsU0/img.png)

함수의 값이 급격히 증가하는 ⓐ 구간에서 *f'(x)*의 값은 큰 양수값으로 나타나고, 급격히 감소하는 ⓑ에서는 *f'(x)*의 값이 큰 음수값으로, 그리고 서서히 증가하다 평탄해지는 ⓒ 구간에서는 작은 양수 값으로 나타난다.

따라서 *f(x)*의 값이 급격하게 바뀌는 부분을 찾기 위해서는 미분 *f'(x)*의 값이 0보다 훨씬 크거나 또는 훨씬 작은 위치를 찾으면 된다.

<br>

잘 알려진 다항함수나 삼각함수 등의 미분을 계산하는 것은 많이 연구되어 도출된 공식을 통해 쉽게 구할 수 있지만, 영상은 2차원 평면 위에 픽셀 값이 정형화되지 않은 상태로 나열되어 있는 이산 형태이므로, 미분 공식을 적용할 수 없다. 따라서 두 가지 특징을 고려하여 미분을 계산해야 하는데, 하나는 영상이 2차원 평면에서 정의된 함수라는 점, 둘째는 영상이 정수 단위 좌표에 픽셀이 나열되어 있는 이산함수라는 점이다.

영상은 2차원 평면에 정의된 함수이므로, 영상에서 에지를 찾기 위해서는 영상을 가로 방향, 세로 방향으로 각각 미분을 해야 한다. 2차원 영상 *I(x,y)* 를 가로 방향으로 미분한다는 것은 y좌표는 고정한 상태에서 x축 방향으로만 미분 근사를 계산하는 것을 의미하며, 이러한 연산을 x축 방향으로의 편미분(partial derivative)라고 한다.

<br>

**미분 근사화 방법** 에는 전진 차분, 후진 차분, 중앙 차분이 있는데 이는 자기 자신을 제외하고 바로 앞과 뒤에 있는 픽셀 값을 이용하는 방법으로, 세 가지 미분 근사 방법 중 중간값 차이를 이용하는 **중앙 차분** 방법이 이론적으로 근사화 오류가 가장 적고, 실제 영상에서 미분을 계산할 때 널리 사용되고 있다.

x축 방향의 편미분은 아래의 *Ix,* 그리고 y축 방향의 편미분은 *Iy*로 표기한다.

2차원 영상 *I(x,y)*에 대하여 x축과 y축 방향에 대한 각각의 편미분을 중앙 차분 방법으로 근사화하면 다음과 같다.

![https://blog.kakaocdn.net/dn/YI9qk/btrSL1LF982/QCzxOATAZsKaNZaiO1Fhbk/img.png](https://blog.kakaocdn.net/dn/YI9qk/btrSL1LF982/QCzxOATAZsKaNZaiO1Fhbk/img.png)

중앙 차분을 이용한 영상의 미분 근사는 마스크 연산을 이용해 쉽게 구현할 수 있다.

<br>

다음은 영상을 x축 방향으로 편미분을 수행하는 1x3 필터, y축 방향으로 편미분을 수행하는 3x1 필터 마스크이다. 이를 이용해 영상을 각각 필터링 하면 영상을 가로 방향, 세로 방향으로 편미분한 정보를 담고 있는 행렬을 얻을 수 있다.

<img src="https://blog.kakaocdn.net/dn/0MtmC/btrSIRcymyO/iw1BKdcUwmjlQwd1EejQmK/img.png" width=300>

<br>

원래 영상은 미분의 부호가 있는 실수로 계산되지만, 미분 결과를 시각적으로 분석하기 위해 미분 값에 128을 더한 후, 0~255 사이의 정수로 형변환하여 그레이스케일 영상 형태로 다음과 같이 lenna 영상에 대한 미분 결과를 각각 x축, y축으로 각각 편미분한 결과를 나타냈다.


![https://blog.kakaocdn.net/dn/byMy1W/btrSIrLRyUA/NSdfnZUkgib6gErzI3ShKK/img.png](https://blog.kakaocdn.net/dn/byMy1W/btrSIrLRyUA/NSdfnZUkgib6gErzI3ShKK/img.png)

흰색, 검은색으로 표현된 픽셀이 입력 영상에서 각각 x좌표, y좌표 방향으로 픽셀 값이 급격하게 감소하는 위치이다.

2차원 공간에서 정의된 영상에서 에지를 찾으려면, x축과 y축 방향의 편미분을 모두 사용해야 하는데, x축과 y축 방향 미분을 한꺼번에 벡터로 표현한 것을 **그래디언트(gradient)**라고 하며 다음과 같이 표기한다.

![https://blog.kakaocdn.net/dn/bQq3ro/btrSHYpCD6m/oE67n2ZujwT0kstLDdUNJK/img.png](https://blog.kakaocdn.net/dn/bQq3ro/btrSHYpCD6m/oE67n2ZujwT0kstLDdUNJK/img.png)

그래디언트는 벡터이므로 크기와 방향 성분으로 표현할 수 있다. 따라서 벡터의 방향은 변화 정도가 가장 큰 방향을 나타내고, 그래디언트 벡터의 크기는 변화율 세기로 나타내는 척도로 생각할 수도 있다.

<br>

따라서 그래디언트의 크기는 ||∇*f|| = square root(fx^2 + fy^2)*로 구하고,

그래디언트 방향 각도는 다음 수식으로 구할 수 있다.

![https://blog.kakaocdn.net/dn/bKMWvC/btrSJmDhOIg/C5lxZiynpvlI9UJIQGCTh0/img.png](https://blog.kakaocdn.net/dn/bKMWvC/btrSJmDhOIg/C5lxZiynpvlI9UJIQGCTh0/img.png)

<br>

그래디언트를 구한 예를 다음 그림을 통해 확인할 수 있다.

어두운 배경에 밝기가 다른 두 객체가 나타난 영상으로, 그래디언트 벡터는빨간색 화살표로 나타났으며, 이 길이는 그래디언트의 크기를, 방향은 그래디언트 벡터의 방향을 나타낸다. 따라서 a, b 점의 그래디언트 방향의 길이보다 밝기 차이가 심한 c점에서의 그래디언트 벡터의 길이가 훨씬 긴 것을 확인할 수 있다. 그리고, 그래디언트 벡터의 방향은 해당 위치에서 밝기가 가장 밝아지는 방향을 가리킨다.

노란색 화살표는 그래디언트 벡터와 수직인 방향을 표시한 것으로, 이는 에지의 방향을 나타낸다.

![https://blog.kakaocdn.net/dn/E9FUq/btrSHJ0xBdm/xdPHpHUVdCuKrtnU0s6Uk0/img.png](https://blog.kakaocdn.net/dn/E9FUq/btrSHJ0xBdm/xdPHpHUVdCuKrtnU0s6Uk0/img.png)

2차원 영상에서 에지를 찾는 기본적인 방법은 그래디언트의 크기가 특정 값보다 큰 위치를 찾는 것이다.

여기서 에지 여부를 판단하기 위해 기준이 되는 **임계값(threshhold)** 또는 문턱치를 영상의 특성에 따라 다르게 설정해야 한다. 임계값을 높게 설정하면 밝기 차이가 급격하게 변하는 에지 픽셀만 검출되고, 낮게 설정하면 약한 에지 성분까지도 쉽게 모두 검출되므로, 이를 유의하여 적절한 임계값을 지정해야 한다.

---

<br>

## 2. **마스크 기반 에지 검출**

영상을 x, y축 방향으로 편미분 하는 1x3, 3x1 크기의 마스크를 통해 에지를 검출할 수 있는 것 같지만, 사실 대부분의 영상에는 잡음이 포함되어 있어 단순히 1x3, 3x1 마스크를 이용해서 미분을 구할 경우 다소 부정확한 결과가 생성될 수 있다. 따라서 실제 영상에서 미분을 구할 때는 좀 더 큰 크기의 마스크를 사용한다

가장 널리 사용되고 있는 미분 근사 마스크는 **소벨 필터(Sobel Filter)** 마스크 이다.

아래 그림 (a)는 x축으로 방향으로의 편미분을 구하는 소벨 마스크를, (b)는 y축 방향으로 편미분을 구하는 소벨 마스크이다.

![https://blog.kakaocdn.net/dn/chmUpX/btrSHNon8cX/kJXHpKLWxqKFefj21zSJsK/img.png](https://blog.kakaocdn.net/dn/chmUpX/btrSHNon8cX/kJXHpKLWxqKFefj21zSJsK/img.png)

(a)에 나타난 미분 마스크는 현재 행에 대해 중앙 차분 연산을 2회 수행하고, 이전 행과 다음 행에 대해서도 중앙 차분 연산을 1회씩 수행한다. 이는 현재 행과 이웃 행에서 픽셀 값 변화가 유사하다는 점을 이용해 잡음의 영향을 줄이기 위함이며, 특히 현재 행에서 2번의 중앙 차분 연산을 수행한 것은 현재 행의 중앙 차분 근사에 더 큰 가중치를 주기 위함이다.

(b) 마스크도 위와 같은 방식으로 설계되었다.

<br>

### **Sobel() 함수**

OpenCV는 소벨 마스크를 이용해 영상을 미분하는 Sobel() 함수를 제공한다. 이는 3x3 소벨 마스크 또는 확장된 형태의 큰 마스크를 이용해 영상을 미분한다.

![https://blog.kakaocdn.net/dn/cIV4jh/btrSIPMBfsD/QoNMy6Ks70HNKxrYYqCbVK/img.png](https://blog.kakaocdn.net/dn/cIV4jh/btrSIPMBfsD/QoNMy6Ks70HNKxrYYqCbVK/img.png)

3x3 또는 그 이상의 크기의 마스크로 영상을 미분하는 Sobel() 함수

결과 영상의 자료형 ddepth에 -1를 지정하면 src와 같은 타입을 사용하는 dst 영상을 생성한다. dx와 dy인자는 각각 x와 y방향으로의 편미분 차수를 의미하며, dst 결과 행렬은 다음 수식과 같은 의미를 갖는다.

![https://blog.kakaocdn.net/dn/cAkkgv/btrSJUNcqLJ/4JjKvCimn97EmiGov9LG60/img.png](https://blog.kakaocdn.net/dn/cAkkgv/btrSJUNcqLJ/4JjKvCimn97EmiGov9LG60/img.png)

ksize는 소벨 커널의 크기로, 1을 지정하는 경우 3x1 또는 1x3 커널을 사용하고, 기본 값인 3을 지정하면 3x3 소벨 마스크를 사용한다.

<br>

Sobel() 함수는 x방향과 y방향으로의 고차 미분을 계산할 수 있지만, 대부분의 경우 x방향 또는 y방향으로의 1차 미분을 구하는 용도로 사용된다. 예를 들면 그레이스케일 레나 영상을 x방향으로 편미분한 결과를 dx 행렬에, y방향으로 편미분한 결과를 dy 행렬에 저장하려면 다음과 같이 작성하면 된다.

<br>

```cpp
Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

Mat dx,dy;
Sobel(src, dx, CV_32FC1, 1, 0);// x 방향으로 편미분Sobel(src, dy, CV_32FC1, 0, 1);// y 방향으로 편미분
```

<br>

OpenCV는 소벨 마스크 이외에도 **샤르 필터(Scharr filter) 마스크** 를 이용한 미분 연산도 지원한다.

이는 3x3 소벨 마스크보다 정확한 미분 계산을 수행하는 것으로 알려져 있다.

아래는 각각 가로, 세로 방향으로 미분을 수행하는 샤르 필터 마스크를 나타낸 것이다.

![https://blog.kakaocdn.net/dn/KBacM/btrSHXj6Vyq/Tqno4ud0pyhrlafzVjaQJ1/img.png](https://blog.kakaocdn.net/dn/KBacM/btrSHXj6Vyq/Tqno4ud0pyhrlafzVjaQJ1/img.png)

<br>

### **Scharr() 함수**

![https://blog.kakaocdn.net/dn/btbjyf/btrSHVsVwRL/H8SwUZakXp1VNVMnKZZS2k/img.png](https://blog.kakaocdn.net/dn/btbjyf/btrSHVsVwRL/H8SwUZakXp1VNVMnKZZS2k/img.png)

Scharr() 함수의 원형은 위와 같은데,

샤르 필터를 이용한 영상의 미분은 앞서 설명한 Sobel() 함수를 이용하여 구할 수도 있다. Sobel() 함수의 ksize 인자에 FILTER_SCHARR 또는 -1을 지정하면 3x3 샤르 마스크를 사용하여 영상을 미분한다.

Sobel() 또는 Scharr() 함수를 이용하여 x, y방향으로 각각 미분을 계산하여 행렬에 저장한 후, 두 미분 행렬을 이용해 그래디언트 크기를 계산할 수 있다. OpenCV는 2차원 벡터의 x, y  방향 좌표를 이용해 벡터의 크기를 계산하는 magnitude() 함수를 제공한다.

<br>

### **magnitude() 함수**

![https://blog.kakaocdn.net/dn/bVprqz/btrSLKcfrZl/r6BxVGkXtM6JzsOKAsGcm0/img.png](https://blog.kakaocdn.net/dn/bVprqz/btrSLKcfrZl/r6BxVGkXtM6JzsOKAsGcm0/img.png)

방향 좌표를 이용해 벡터의 크기를 계산하는 magnitude() 함수

함수의 입력으로 사용되는 x,y는 CV_32F 또는 CV_64F 깊이를 사용하는 행렬 또는 벡터여야 한다. 출력 magnitude를 구성하는 원소 값은 다음 수식에 의해 계산된다.

![https://blog.kakaocdn.net/dn/JFenA/btrSJmDl6nc/4cMYwAOceMuO5mqLMmBMx0/img.png](https://blog.kakaocdn.net/dn/JFenA/btrSJmDl6nc/4cMYwAOceMuO5mqLMmBMx0/img.png)

<br>

### **phase() 함수**

만약 x방향으로 미분, y방향으로 미분이 저장된 두 행렬이 있을 때 그래디언트의 방향을 계산하고 싶다면 phase() 함수를 사용할 수 있다.

![https://blog.kakaocdn.net/dn/bDOYJV/btrSI9xk9Qn/WSg89JauJTyIqfR1kgDqT1/img.png](https://blog.kakaocdn.net/dn/bDOYJV/btrSI9xk9Qn/WSg89JauJTyIqfR1kgDqT1/img.png)

x,y는 입력이고 angle은 출력이다. angle의 각 원소는 다음 수식에 의해 계산된다.

![https://blog.kakaocdn.net/dn/dAJKb3/btrSJxY05MP/JoLfpuTg5QVQnMMpzkilv1/img.png](https://blog.kakaocdn.net/dn/dAJKb3/btrSJxY05MP/JoLfpuTg5QVQnMMpzkilv1/img.png)

---

<br>

이제 Sobel() 함수를 사용하여 실제 영상으로부터 그래디언트를 계산하고, 그래디언트 크기를 이용하여 에지를 검출하는 예제 코드를 살펴보자.

```cpp
// 소벨 마스크 기반 에지 검출void sobel_edge()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

// 가로, 세로 방향으로 각각 소벨 마스크 연산
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

// dx와 dy 행렬으로부터 그래디언트 크기 계산하여 fmag에 저장
	Mat fmag, mag;
	magnitude(dx, dy, fmag);
	fmag.convertTo(mag, CV_8UC1);

// 에지 판별을 위한 그래디언트 크기 임계값을 150으로 설정 (150보다 크면 255로, 작으면 0으로 설정됨)
	Mat edge = mag > 150;

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}
```

<br>


src는 원본 lenna 영상이고, mag는 그래디언트 크기를 그레이스케일 영상 형식으로 나타낸 것이다. 이때 각 픽셀에서 계산된 그래디언트 크기가 255보다 큰 경우에는 포화 연산에 의해 흰색으로 표현된다.

edge 영상은 그래디언트 크기 mag 가 150보다 큰 픽셀을 흰색으로, 아니면 검은색으로 표현한 이진 영상이다.

![https://blog.kakaocdn.net/dn/vy12O/btrSISP1wsG/1t6sMjSRdRGlRceQY5Ow10/img.png](https://blog.kakaocdn.net/dn/vy12O/btrSISP1wsG/1t6sMjSRdRGlRceQY5Ow10/img.png)

---

<br>

## **캐니 에지 검출기**

소벨 마스크를 이용한 에지 검출 방법은구현이 간단하고 빠르게 동작하여 현재 컴퓨터 비전 시스템에서 사용되고 있지만, 그래디언트 크기만을 기준으로 에지 픽셀을 검출하기 때문에 임계값에 민감하고 에지 픽셀이 두껍게 표현되는 문제점이 있다.

1986년 캐니(J. Canny)는 에지 검출을 최적화 문제 관점으로 접근함으로써 소벨 에지 검출 방법의 단점을 해결할 수 있는 방법을 제시하였다. 캐니는 다음 세가지 항목을 좋은 에지 검출기의 조건으로 제시하였다.

> **정확한 검출 (Good Detection) -** 에지를 검출하지 못하거나, 또는 에지가 아닌데 에지로 검출하는 확률 최소화 필요
> 
> 
> **정확한 위치 (Good Localization) -** 실제 에지의 중심을 찾아야 함
> 
> **단일 에지 (Single Edge) -** 하나의 에지는 하나의 점으로 표현되어야 함
> 

<br>

캐니는 위의 조건을 만족하는 새로운 형태의 에지 검출 방법, **캐니 에지 검출기(Canny Edge Detector)** 을 제시하였다.

캐니 에지 검출기는 그래디언트의 크기에 더해 방향까지 모두 고려하여 좀 더 정확한 에지를 찾는 방법이다. 에지는 서로 연결되어 있는 가능서이 높다는 점을 고려하여 그래디언트 크기가 다소 약하게 나타나는 에지도 놓치지 않고 찾을 수 있다.

---

캐니 에지 검출기는 아래의 4개 연산 과정을 포함한다. 각 연산의 의미와 수행 방법을 살펴보도록 하자.

![https://blog.kakaocdn.net/dn/bE8u0o/btrSLZUKO4F/RCGqc6BF1KbTAD6eatJkZ1/img.png](https://blog.kakaocdn.net/dn/bE8u0o/btrSLZUKO4F/RCGqc6BF1KbTAD6eatJkZ1/img.png)

<br>

### **1. 가우시안 필터링**

가우시안 필터링은 앞선 포스팅에서 설명한 바가 있다.([https://dream-and-develop.tistory.com/308](https://dream-and-develop.tistory.com/308))

가우시안 필터링은 가우시안 분포 함수를 근사하여 생성한 필터 마스크를 사용하는 블러링 기법으로,우선 영상에 포함된 잡음을 제거하는 단계가 필요하다. 다만 가우시안 필터링에 의해 영상이 부드러워지면서, 에지의 세기도 함께 감소할 수 있기 때문에 적절한 표준 편차를 선택하여 수행하는 것이 필요하며, 잡음이 심하지 않은 영상이라면 이 단계는 생략 가능하다.

<br>

### **2. 그래디언트 계산**

다음으로는 영상의 그래디언트를 구하는 단계이다. 캐니 에지 검출기에서 보통 3x3 소벨 마스크를 사용하여 그래디언트 계산을 한다. 정확한 에지를 찾기 위해 가로, 세로 방향으로 각각 소벨 마스크 필터링을 수행한 후, 그래디언트 크기와 방향을 모두 계산하여야 한다.

<br>

### **3. 비최대 억제**

에지가 두껍게 표현되는 현상을 방지하기 위해 캐니 에지 검출기에서는 **비최대 억제(non-maxmimum suppression)** 과정을 사용한다. 단순히 그래디언트 크기가 특정 임계값보다 큰 픽셀을 선택하는 경우, 에지 근방의 여러 픽셀이 한꺼번에 에지로 선택될 수 있기 때문이다. 비최대 억제는 그래디언트 크기가 국지적 최대(local maximum)인 픽셀만을 에지 픽셀로 설정하는 기법이다.

일반적으로 2차원 영상에서 local maximum을 찾기 위해선 특정 픽셀을 둘러싼 모든 픽셀 값을 검사하여 판별해야 하지만, 캐니 에지 검출기의 경우 그래디언트 벡터의 방향과 같은 방향에 있는 인접 픽셀에 대해서만 검사를 수행한다.

결과적으로, 비최대 억제를 수행하여 가장 변화율이 큰 위치의 픽셀만 에지로 탐색된다.

<br>

### **4. 이중 임계값을 이용한 히스테라시스 에지 트래킹**

소벨 에지 검출 방법은 특정 임계값 수치를 이용해 에지 픽셀을 판단하였다. 이 경우 조명이 조금 바뀌거나 임계값을 조금만 다르게 조절해도 에지 픽셀 판단 결과가 크게 달라질 수 있다. 이는 하나의 임계값을 사용하여 이분법으로 에지 판별 결과가 판단되기 때문에 환경 변화에 민감해질 수 있다는 문제를 지닌다.

이러한 문제를 보완하기 위해 캐니 에지 검출기에서는 2개의 임계값을 사용한다.

두 임계값 중 높은 임계값을 *T(High),* 낮은 임계값을 *T(Low)* 라 할 때, 그래디언트 크기가 *T(High)* 보다 크면 해당 픽셀은 최종적인 에지로 판단하고, *T(Low)* 보다 작으면 에지 픽셀이 아니라고 판단한다.

*T(Low)*와 *T(High)* 사이의 픽셀은 에지일 수도, 에지가 아닐 수도 있다고 판단하여 이런 픽셀에 대해서는 추가적인 검사를 수행하게 된다.

아래와 같이 총 세 영역에 분포할 수 있는 에지에 대해 차례대로 연속적인 픽셀 값들에 대하여 강한에지, 약한에지, 에지 아님으로 구분해보자.

![https://blog.kakaocdn.net/dn/tIGVe/btrSJnbdggR/7VT3vVWKyRuzHU0rBWWDLK/img.png](https://blog.kakaocdn.net/dn/tIGVe/btrSJnbdggR/7VT3vVWKyRuzHU0rBWWDLK/img.png)

<br>

에지 검출기의 마지막 단계에서는 **히스테리시스 에지 트래킹(Hystersis Edge Tracking)** 을 사용하여 약한 에지 중, 최종 적으로 에지로 판별할 픽셀을 선택한다. 이 방법을 이용해 약한 에지 중, 강한 에지 픽셀과 상호적으로 연결되어 있는 약한 에지만을 최종적인 에지로 판단한다.

따라서 위 그림에서 약한 (a)와 (c)의 약한 에지는, 강한 에지와 연결되어 있으므로 최종적인 이제로 판단이 되지만, 

(b)의 약한 에지는 강한 에지와 연결되어 있는 에지가 아니므로 에지가 아닌 픽셀들로 판단된다.

<br>

### **Canny() 함수**

OpenCV에서 캐니 검출 알고리즘은 Canny() 함수에 구현되어 있다. 두 가지 형태로 정의되어 있고, 원형은 다음과 같다.

![https://blog.kakaocdn.net/dn/b8y8h8/btrSJUmaN2S/agbSjpR55h37v7NWEzRxHk/img.png](https://blog.kakaocdn.net/dn/b8y8h8/btrSJUmaN2S/agbSjpR55h37v7NWEzRxHk/img.png)

첫번째 Canny() 함수는 일반 영상을 입력으로 전달하여 에지를 검출할 때 사용하고, 두번째 함수는 이미 x,y방향의 미분 영상을 가지고 있을 때 사용한다.

캐니 에지 검출기의 히스테리시스 에지 트래킹 단계에서 사용되는 두 임계값 threshold1, threshold2을 적절하게 지정하는 것이 중요한데, 차례대로 낮은 임계값, 큰 임계값을 지정하면 된다. 두 임계값은 보통 1:2, 1:3의 비율로 지정한다.

<br>

마지막으로 예제를 살펴보자.

```cpp
// 캐니 에지 검출기void canny_edge()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2,dst3;
	Canny(src, dst1, 50, 100);// 낮은 임계값 50, 높은 임계값 100으로 설정Canny(src, dst2, 50, 150);// 낮은 임계값 50, 높은 임계값 150으로 설정Canny(src, dst3, 50, 200);// 낮은 임계값 50, 높은 임계값 200으로 설정imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);

	waitKey();
	destroyAllWindows();
}
```

<br>

낮은 임계값과 높은 임계값의 비율을 1:2, dst2는 비율을 1:3로 설정하여 캐니 에지 검출기를 이용한 두 결과 영상을 생성하였다. 임계값을 높일 수록 검출되는 에지 픽셀이 적어지는 것을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/bHQPXp/btrSJXwlO5l/ILDb29AWoOBlyCn51XoPIK/img.png](https://blog.kakaocdn.net/dn/bHQPXp/btrSJXwlO5l/ILDb29AWoOBlyCn51XoPIK/img.png)

50과 100으로 두 임계값을 설정한 dst1의 경우 모자와 얼굴에서, 사소한 음영 변화가 일어나는 부분에서도 에지가 과도히 많이 검출되는 것을 확인할 수 있다.

반면 50과 200으로 설정한 마지막 결과 영상의 경우, 얼굴과 모자, 머리 부분에서 에지가 어느정도 정리되었다.