# CH 07 필터링 - 엠보싱, 블러링, 샤프닝, 잡음 제거 필터링

# **영상의 필터링**

영상 처리에서 **필터링(filtering)** 이란**,** 영상에서 원하는 정보만 통과시키고 원치 않는 정보는 걸러 내는 작업이다. 영상의 필터링은 보통 **마스크(mask)** 라 부르는 작은 크기의 행렬을 이용한다. 마스크는 필터링의 성격을 정의하는 행렬로 커널(kernel), 윈도우(window)라고도 부르며, 경우에 따라서는 마스크 자체를 필터라고 부르기도 한다.

<br>

### **필터 마스크**

영상 처리에서 다양한 크기의 모양의 필터 마스크가 사용되는데, 행렬의 원소는 보통 실수로 구성되며, 1x3, 3x1 형태의 직사각형 행렬, 3x3, 5x5 등 정방형 행렬, 필요하다면 십자가 모양 등 여러 가지 모양이 있으며, 그중에서도 3x3 정방형 행렬이 가장 널리 사용되고 있다.

![https://blog.kakaocdn.net/dn/cmD2ed/btrSqGJkxpV/GxKkqLWaKIeZxFmo9IvzZ0/img.png](https://blog.kakaocdn.net/dn/cmD2ed/btrSqGJkxpV/GxKkqLWaKIeZxFmo9IvzZ0/img.png)

<br>

위의 그림은 다양한 필터 마스크 모양을 타나내느데, 진한 색으로 표시된 위치는 **고정점(anchor point)**를 나타낸다.

고정점은 현재 필터링 작업을 수행하고 있는 기준 픽셀 위치를 나타내고, 대부분의 경우 마스크 행렬 정중앙을 고정점으로 사용한다.

필터링 연산의 결과는 마스크 행렬의 모양과 원소 값에 의해 결정되는데, 마스크 행렬을 어떻게 정의하는가에 따라 영상을 드럽게 혹은 날카롭게 만들 수도, 잡음을 제거하거나 에지 성분만 나타나도록 만들 수도 있다.

<br>

가장 널리 사용하는 3x3 정방형 마스크를 이용해 필터링을 수행한다고 해보자.

m은 마스크 행렬을 나타내고, f와 g는 각각 입력 영상과 출력 영상을 의미한다. 마스크 행렬의 크기가 3x3이므로 고정점의 좌표는 중심 좌표인 (1,1)로 설정할 수 있다.

마스크를 이용한 필터링은 입력 영상의 모든 픽셀 위로 마스크 행렬을 이동시키면서 마스크 연산을 수행하는 방식으로 이루어진다. 마스크 연산은, 마스크 행렬의 모든 원소에 대해 마스크 행렬 원소 값과 같은 위치에 있는 입력 영상 픽셀 값을 서로 곱한 후, 그 결과를 모두 더하는 연산이다. 그리고 마스크 연산의 결과를 출력 영상에서 고정점 위치에 대응하는 픽셀 값으로 설정한다.

따라서 마스크 행렬 m의 중심이 입력 영상의 (x,y) 좌표 위에 위치했을 때 필터링 결과 영상의 픽셀 값 g(x,y)는 다음과 같이 계산된다.

![https://blog.kakaocdn.net/dn/bzrUZm/btrSr5uSJvZ/KgErRtbCzCtedxZ20CZcik/img.png](https://blog.kakaocdn.net/dn/bzrUZm/btrSr5uSJvZ/KgErRtbCzCtedxZ20CZcik/img.png)

![https://blog.kakaocdn.net/dn/bf1eff/btrStRJuCZA/ypriBUQK5CGOWr9uErjRm1/img.png](https://blog.kakaocdn.net/dn/bf1eff/btrStRJuCZA/ypriBUQK5CGOWr9uErjRm1/img.png)

(x,y) 좌표에서 마스크 연산을 통해 영상의 픽셀 값 g(x,y)를 구했으면, 다음에는 마스크를 한 픽셀 옆으로 이동하여 (x+1, y) 좌표에 다시 마스크 연산을 수행하고, 그 결과를 g(x+1, y)에 저장한다. 이 과정을 영상 전체 픽셀에 대해 수행하면 필터링이 완료된다.

<br>

### **가장자리 픽셀 확장 방법**

그런데 영상의 가장자리 픽셀에 대해서 수행할 때에는, 영상의 가장자리 픽셀을 확장하여 영상 바깥쪽에 가상의 픽셀을 만드는 방법을 수행한다. 가상의 픽셀 값을 어떻게 설정하는가에 따라 필터링 연산 결과가 달라지는데, OpenCV 필터링 연산에서 기본적으로 사용하는 방법은 아래와 같이 실제 입력 영상의 픽셀 값이 대칭 형태로 나타나도록 설정하는 방법이다.

아래는 5x5 크기의 필터 마스크를 사용하므로 좌측 상단의 가장자리 바깥쪽에 두 개씩의 가상 픽셀을 추가적으로 표현한 것이다.

![https://blog.kakaocdn.net/dn/v1MeX/btrSq7T5LOE/TgUt0o5A7eJZwdqOrqx9xK/img.png](https://blog.kakaocdn.net/dn/v1MeX/btrSq7T5LOE/TgUt0o5A7eJZwdqOrqx9xK/img.png)

OpenCV 필터링 연산에서 사용할 수 있는 가장자리 픽셀 확장 방법은 다음과 같이 BorderTypes라는 열거형 상수를 이용해 다른 방식으로 설정할 수도 있다.

![https://blog.kakaocdn.net/dn/ce6XXA/btrSsmccDOU/y4oZC6eZJTGEJB6Cwu3Hz1/img.png](https://blog.kakaocdn.net/dn/ce6XXA/btrSsmccDOU/y4oZC6eZJTGEJB6Cwu3Hz1/img.png)

<br>

### **filter2D() 함수**

OpenCV 에서 필터 마스크를 사용하는 일반적인 필터링은 filter2D() 함수를 이용한다.

src 영상에 kernel 필터를 이용하여 필터링을 수행하고, 그 결과를 dst에 저장한다.

src와 dst 인자에 같은 변수 지정 시 필터링 결과를 입력 영상에 덮어쓰게ㅇ 된다.

![https://blog.kakaocdn.net/dn/b6ToJh/btrSrohe9iB/k7Llntbp7WtRnncYNG7BoK/img.png](https://blog.kakaocdn.net/dn/b6ToJh/btrSrohe9iB/k7Llntbp7WtRnncYNG7BoK/img.png)

함수가 수행하는 연산을 수식으로 표현하면 다음과 같다.

![https://blog.kakaocdn.net/dn/cHGrRW/btrSvAgrZZ4/zrLdb8IV8PSNUiJsCbUYNk/img.png](https://blog.kakaocdn.net/dn/cHGrRW/btrSvAgrZZ4/zrLdb8IV8PSNUiJsCbUYNk/img.png)


<br>

ddepth 인자는 결과 영상의 깊이를 지정하는 용도로 사용하며, 입력 영상의 깊이에 따라 지정할 수 있는 값은 다음과 같다.

![https://blog.kakaocdn.net/dn/bQwlBv/btrStyXCSHJ/yGwrWvao7qq66zmaKANPlk/img.png](https://blog.kakaocdn.net/dn/bQwlBv/btrStyXCSHJ/yGwrWvao7qq66zmaKANPlk/img.png)

anchor, delta, borderType 인자는 기본 값을 가지고 있다.

anchor은 커널 행렬에서 고정점으로 사용할 좌표이며, 기본값으로 Point(-1, -1)을 지정하면 커널 행렬 중심 좌표를 고정점으로 사용한다.

delta는 필터링 연산 후 결과 영상에 추가적으로 더할 값을 지정하는 인자이며 (기본값 0), borderType은 위의 BorderTypes 열거형 상수 중 하나를 지정하면 된다.

---

<br>

## **엠보싱 필터링**

**엠보싱(embossing)** 이란, 직물이나 종이, 금속판 등에 올록볼록한 형태로 만든 객체의 윤곽 또는 무늬를 뜻하며, 엠보싱 필터는 입력 영상을 엠보싱 느낌이 나도록 변환환하는 필터이다.

보통 픽셀 값 변화가 적은 평탄한 영역은 회색으로, 객체의 경계 부분은 좀 더 밝거나 어둡게 설정하여 엠보싱 느낌을 낼 수 있다.

간단한 3x3 엠보싱 필터 마스크는 다음과 같이 대각선 방향으로 +1, -1 값이 지정되어 있는 행렬이다.

![https://blog.kakaocdn.net/dn/k0vd6/btrSpvuFRmn/kTM3jOPOtkcoIu8hqkbJI1/img.png](https://blog.kakaocdn.net/dn/k0vd6/btrSpvuFRmn/kTM3jOPOtkcoIu8hqkbJI1/img.png)

<br>

대각선 방향으로 픽셀 값이 급격하게 변하는 부분에서 결과 영상 픽셀 값이 0보다 훨씬 크거나 0보다 훨씬 작은 값을 가직 되어, 픽셀값이 크게 바뀌지 않는 평탄한 영역은 결과 영상의 픽셀 값이 0에가까운 값을 가지게 된다.

<br>

이렇게 구한 결과 영상을 그대로 화면에 나타내면 음수 값은 모두 포화 연산에 의해 0이 되어버리므로, 입체감이 크게 줄어들기 때문에 엠보싱 필터를 구현할 때에는 결과 영상에 128을 더하는 것이 보기에 좋다.

```cpp
// 엠보싱 필터링void filter_embossing()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

// 엠보싱 필터링 마스크float data[] = { -1,-1,0,-1,0,1,0,1,1 };
	Mat emboss(3, 3, CV_32FC1, data);

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1,-1), 128);// 결과 영상에 128을 더하기imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}
```

<br>

rose 이미지에 대해 엠보싱 필터 마스크 연산을 수행한 결과는 다음과 같다.

픽셀 값이 급격하게 변하는 장미꽃의 경계 부분이 입체감 있게 표현된 것을 확인할 수 있다.

픽셀 값이 완만하게 바뀌는 나머지 부분에 대해서는 필터링 결과 영상이 대체로 밝기값 128에 가까운 회색으로 표현되어 있는 것 또한 확인할 수 있다.

![https://blog.kakaocdn.net/dn/lgpx3/btrSrouIv81/TMiys2zyuI9PNz2wK77t30/img.png](https://blog.kakaocdn.net/dn/lgpx3/btrSrouIv81/TMiys2zyuI9PNz2wK77t30/img.png)

---

<br>


# **블러링: 영상 부드럽게 하기**

**블러링(Blurring**) 이란, 초점이 맞지 않은 사진처럼 영상을 부드럽게 만드는 필터링 기법으로, 스무딩(smoothing)이라고도 한다.

영상에서 인접한 픽셀 간의 픽셀 값 변화가 크지 않은 경우 부드러운 느낌을 받을 수 있는데, 블러링은 거친 느낌의 입력 영상을 부드럽게 만드는 용도로, 혹은 입력 영상에 존재하는 잡음의 영향을 제거하는 전처리 과정으로 사용된다.

비교적 간단한 평균값 필터를 사용하는 블러링 기법과, 수식이 조금 복잡하지만 좀 더 자연스러운 블러링을 수행하는 가우시안 필터에 대해 알아보자.

<br>

### **1. 평균값 필터**

**평균값 필터(mean filter)** 은 블러링 필터 중에서 단순하고 구현하기 쉬운 필터 방법이다. 이는 입력 영상에서 특정 픽셀과 주변 픽셀들의 산술 평균을 결과 영상 픽셀 값으로 설정하는 필터이다.

결과적으로 픽셀 값의 급격한 변화가 줄어들어 날카로운 에지가 무뎌지고 잡음의 영향이 크게 사라질 수 있다.

아래와 같이 3x3, 5x5 크기의 평균값 필터를 비롯해 다양한 크기의 필터 마스크가 나타날 수 있다. 각각의 행렬이 모두 원소 값이 1로 설정되어 있고, 행렬의 전체 원소 개수로 각 행렬 원소 값을 나누는 형태로 표현이 되어 있다.

평균값 필터는 마스크의 크기가 커지면 커질수록 더욱 부드러운 느낌의 결과 영상을 생성하며, 대신 연산량이 크게 증가할 수 있다.

![https://blog.kakaocdn.net/dn/zydg8/btrSvzB0laW/KB9IhDKdUbIFThJmosEPuk/img.png](https://blog.kakaocdn.net/dn/zydg8/btrSvzB0laW/KB9IhDKdUbIFThJmosEPuk/img.png)

> 일반적으로 필터 마스크 행렬은 모든 원소 합이 1 또는 0이 되도록 설계한다. 행렬의 전체 원소 합이 1이면 필터링 결과 영상의 평균 밝기가 입력 영상의 평균 밝기오 ㅏ같게 유지된다. 1보다 작은 경우 어두운 결과 영상이, 1보다 크면 좀 더 밝은 형태의 결과 영상이 생성 된다. 행렬 원소의 합이 0이라면, 전체적으로 검은색으로 구성된 필터링 결과 영상이 생성된다.
> 

<br>

### **blur() 함수**

OpenCV에서는 blur() 함수를 이용해 평균값 필터링을 수행할 수 있다. 원형은 다음과 같다.

![https://blog.kakaocdn.net/dn/boAPuG/btrSvAHELJw/7Br6EQHMWPSwKDaiS4Ikzk/img.png](https://blog.kakaocdn.net/dn/boAPuG/btrSvAHELJw/7Br6EQHMWPSwKDaiS4Ikzk/img.png)


ksize 크기의 평균값 필터 마스크를 사용하여 dst 출력 영상을 생성하게 된다.

anchor 인자와 borderType 인자는 기본값을 가지므로 호출 시 생략이 가능하다.

blur() 함수에서 사용하는 커널은 다음과 같은 형태를 가지며, 전체 원소 개수로 각 행렬 원소 값을 나누는 형태의 수식이다.

![https://blog.kakaocdn.net/dn/pE2Hx/btrStzoPK6v/jPQMkH7bT396tEpVHpR8BK/img.png](https://blog.kakaocdn.net/dn/pE2Hx/btrStzoPK6v/jPQMkH7bT396tEpVHpR8BK/img.png)

<br>

ksize의 값을 각각 3, 5, 7로 설정하여 ksize x kszie 크기의 블러링 커널 크기를 적용한 평균값 필터 마스크를 이용한 블러링을 수행해보자.

```cpp
// 평균값 필터를 이용한 블러링void blurring_mean()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);
	Mat dst;

// 3x3, 5x5, 7x7 크기의 평균값 필터를 이용해 블러링 수행for (int ksize = 3; ksize <= 7;ksize += 2) {
		blur(src, dst, Size(ksize, ksize));// 평균값 필터링을 이용한 블러링

		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey(0);
	}

	destroyAllWindows();
}
```

<br>

결과는 다음과 같이 나타난다.

평균값 필터의 크기가 커질 수록 결과 영상이 더욱 부드럽게 변경되는 것을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/YQxjr/btrSsnI5Mkh/aopwdzYfRdBSzKCZGMukX1/img.png](https://blog.kakaocdn.net/dn/YQxjr/btrSsnI5Mkh/aopwdzYfRdBSzKCZGMukX1/img.png)

![https://blog.kakaocdn.net/dn/cHCt5P/btrSsZBbqpG/mYRey0klWUwKpC7Fj36A5k/img.png](https://blog.kakaocdn.net/dn/cHCt5P/btrSsZBbqpG/mYRey0klWUwKpC7Fj36A5k/img.png)

![https://blog.kakaocdn.net/dn/l5TXn/btrSq9dxFtB/soPPNezkJzP3UHOIEkHpm0/img.png](https://blog.kakaocdn.net/dn/l5TXn/btrSq9dxFtB/soPPNezkJzP3UHOIEkHpm0/img.png)

5x5 크기부터 영상이 전체적으로 흐려지므로, 커널 크기 ksize를 적절히 조절하여 영상의 블러링 연산을 수행해야 할 것이다.

---

<br>

### **가우시안 필터**

**가우시안 필터(Gaussian filter)** 는 가우시안 분포(Gaussian Distribution) 함수를 근사하여 생성ㅅ한 필터 마스크를 사용하는 필터링 기법으로, 평균값 필터보다 자연스러운 블러링 결과를 생성한다.

<br>

**가우시안 분포란?**

가우시안 분분포는 평균을 중심으로 좌우 대칭의 종 모양을 갖는 확률 분포를 말하며, 정규 분포(noramal distribution)라고도 한다. 이는 평균 근방에서 분포가 가장 많이 발생하고, 평균에서 멀어질수록 발생 빈도가 종 모양으로 감소하는 형태를 따른다.

가우시안 분포는 평균과 표준 편차에 따라 분포 모양이 결정되는데, 영상의 가우시안 필터에서는 주로 평균이 0인 가우시안 분포를 사용한다.

<br>

평균이 0이고 표준 편차가 σ 인 1차원 가우시안 분포의 함수식은 다음과 같다.

![https://blog.kakaocdn.net/dn/udQpd/btrSs0z88oo/s1dKk1wCFKpLrEqwtT7DaK/img.png](https://blog.kakaocdn.net/dn/udQpd/btrSs0z88oo/s1dKk1wCFKpLrEqwtT7DaK/img.png)

평균이 0, 표준 편차가 &nbsp;&sigma;인 가우시안 분포 함수식

평균이 0이고 표준 편차가 각각 0.5, 1.0, 2.0인 가우시안 분포 그래프를 나타내면 다음과 같다.

![https://blog.kakaocdn.net/dn/yUJEr/btrSqGbJNpO/9IsFb3lKe0A6sKQMk0k1E0/img.png](https://blog.kakaocdn.net/dn/yUJEr/btrSqGbJNpO/9IsFb3lKe0A6sKQMk0k1E0/img.png)

<br>

### 2차**원 가우시안 분포 필터 마스크**

가우시안 분포를 따르는 2차원 필터 마스크 행렬을 생성하려면, 2차원 가우시안 분포 함수를 근사해야 하는데,

이는 x와 y 2개의 변수를 사용하고, 분포의 모양을 결정하는 평균과 표준 편차도 x축과 y축 방향에 따라 따로 설정한다.

평균이 (0,0)이고 x축과 y축 방향의 표준 편차가 각각  σ(x) ,  σ(y) 인 2차원 가우시안 분포 함수는 다음과 같이 정의된다.

![https://blog.kakaocdn.net/dn/xuKwf/btrSqMJFVkP/7YEGYYy4j6wNkvfI9Xnc8k/img.png](https://blog.kakaocdn.net/dn/xuKwf/btrSqMJFVkP/7YEGYYy4j6wNkvfI9Xnc8k/img.png)

<br>

아래는 평균이 (0,0)이고, σ(x)=σ(y)=1.0 인 2차원 가우시안 분포 함수 그래프를 나타낸 것이다.

평균이 (0,0)이므로 (0,0)에서 최댓값을 갖고, 평균에서 멀어질수록 함수가 감소한다. 2차원 가우시안 분포 함수의 경우 함수 그래프 아래의 부피를 구하면 1이 된다.

![https://blog.kakaocdn.net/dn/drdexc/btrSqW6z4Ip/iqFCG9NyJuN145dIkeqwZk/img.png](https://blog.kakaocdn.net/dn/drdexc/btrSqW6z4Ip/iqFCG9NyJuN145dIkeqwZk/img.png)

<br>

가우시안 필터는 위의 2차원 가우시안 분포 함수로부터 구한 마스크 행렬을 사용한다.

가우시안 분포 함수는 연속 함쉬지만 이산형의 마스크를 만들기 위해, x와 y값이 정수인 위치에서만 가우시안 분포 함수 값을 추출하여 생성한다.

평균이 0이고 표준 편차가 σ인 가우시안 분포는 x가 -4σ에서 4σ 사이인 구간에서 대부분의 값이 나타나므로, 가우시안 필터 마스크의 크기는 보통 (8σ+1)로 결정한다.

예를 들어 위와 같이 σ(x)=σ(y)=1.0 인 가우시안 함수를 사용하는 경우, x={-4,-3,...,3,4} , y={-4,-3,...,3,4} 인 경우에만 가우시안 분포 함수 값을 추출하여 필터 마스크를 생성한다. 이렇게 추출한 9x9 가우시안 필터 마스크는 아래와 같이 나타난다.

![https://blog.kakaocdn.net/dn/bLh6Dw/btrSyrcWoLg/YnYmzS7WRp35soy9DZFSuK/img.png](https://blog.kakaocdn.net/dn/bLh6Dw/btrSyrcWoLg/YnYmzS7WRp35soy9DZFSuK/img.png)

위에서 가우시안 필터 마스크 행렬은 중앙부에서 비교적 큰 값을 가지고, 주변부로 갈 수록 행렬 원소 값이 0에 가까운 작은 값을 가진다. 따라서 이 마스크를 이용해 마스크 연산을 수행한다는 것은, 필터링 대상 픽셀 근처에는 가중치를 크게 주고, 필터링 대상 픽셀과 멀리 떨어져 있는 주변부에는 가중치를 조금만 주어서 가중 평균(weighted average)르ㅓㄹ 구하는것과 같다.

<br>

### **GaussianBlur() 함수**

OpenCV에서 가우시안 필터링을 수행하려면 GaussianBlur() 함수를 사용한다.

![https://blog.kakaocdn.net/dn/b3WWNv/btrSwTBhcln/Tdkswt18bI2858vYk92G90/img.png](https://blog.kakaocdn.net/dn/b3WWNv/btrSwTBhcln/Tdkswt18bI2858vYk92G90/img.png)

가우시안 필터링을 수행하는 GaussianBlur() 함수

위 함수는 src 영상에 가우시안 블러링 필터링을 수행하고 결과를 dst 영상에 저장한다.

x, y축 방향으로의 표준 편차 sigmaX와 sigmaY는 보통 같은 값을 사용하고, 가우시안 필터의 크기를 지정하는 ksize 인자에도 보통 Size()를 전달하여 적절한 필터 크기를 자동으로 결정하도록 한다.

<br>

아래는 sigma 값을 1부터 5까지 지정하여 x, y축으로의 가우시안 커널 표준 편차를 바꿔 가며

가우시안 필터 마스크 연산을 수행한 결과의 차이를 확인하는 예제이다.

```cpp
// 가우시안 필터링 이용한 블러링 연산void blurring_gaussian()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src,", src);

	Mat dst;
// 1부터 5까지의 가우시안 커널 표준 편차를 지정하여 가우시안 필터링 수행for (int sigma = 1;sigma <= 5;sigma++)
{
		GaussianBlur(src, dst, Size(), (double)sigma);

		String text = format("sigma = %d", sigma);
		putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}
```

<br>

결과는 다음과 같이, 표준 편차 값이 커질 수록 결과 영상이 더욱 부드럽게 변경되는 것을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/csU9JQ/btrStQllHq0/nMG3ABy8BmxagdkMuOGkUK/img.png](https://blog.kakaocdn.net/dn/csU9JQ/btrStQllHq0/nMG3ABy8BmxagdkMuOGkUK/img.png)

![https://blog.kakaocdn.net/dn/cGLTlV/btrSxl5l6C1/eNstrsyo48e3mKbwUsRck1/img.png](https://blog.kakaocdn.net/dn/cGLTlV/btrSxl5l6C1/eNstrsyo48e3mKbwUsRck1/img.png)

![https://blog.kakaocdn.net/dn/cxAcaQ/btrSz76bJOV/uW6tfkwR3MqYzHVTubAKhK/img.png](https://blog.kakaocdn.net/dn/cxAcaQ/btrSz76bJOV/uW6tfkwR3MqYzHVTubAKhK/img.png)

![https://blog.kakaocdn.net/dn/xHjnk/btrSxQjJnGb/xqiXJH7qCOzOASrmjxmpa0/img.png](https://blog.kakaocdn.net/dn/xHjnk/btrSxQjJnGb/xqiXJH7qCOzOASrmjxmpa0/img.png)

![https://blog.kakaocdn.net/dn/p6WuP/btrSvzwQimD/ZBo1yqnaXBKAaAJ9Yf6ZYK/img.png](https://blog.kakaocdn.net/dn/p6WuP/btrSvzwQimD/ZBo1yqnaXBKAaAJ9Yf6ZYK/img.png)

---

<br>

# **샤프닝: 영상 날카롭게 하기**

블러링과 반대되는 개념인 **샤프닝 (Sharpening) 기법**은, 사물의 윤곽이 뚜렷하고 선명한 느낌이 나도록 영상을 변경하는 필터링 기법이다.

<br>

### **언샤프 마스크 필터**

샤프닝 기법을 구현하기 위해서는 블러링된 영상을 사용한다. 블러링이 적용된 영상, 언샤프(unsharp)한 영상을 이용하여 역으로 날카로운 영상을 생성하는 필터를 **언샤프 마스크 필터(unsharp mask filter)** 라고 한다.

언샤프 마스크 필터링의 동작 방식을 다음 그림을 통해 이해해보자.

가로 x축은 픽셀 좌표의 이동을, 세로 y축은 픽셀 값을 나타낸다.

![https://blog.kakaocdn.net/dn/bl9gOx/btrSyhO0ljm/udNpZ4TnG5qzExXobC5U0K/img.png](https://blog.kakaocdn.net/dn/bl9gOx/btrSyhO0ljm/udNpZ4TnG5qzExXobC5U0K/img.png)

(a)의 경우 영상의 에지 부근에서 픽셀 값이 증가하는 모양을 나타낸 것이고, (b)는 파란색 실선 그래프는 f(x,y)에 블러링을 적용한 결과를 나타낸다.

(c)는 f(x,y)에서 블러링된 영상을 뺸 결과로, 이는 g(x,y)로 표기하였다. 입력 함수 값이 증가하기 시작하는 부분에서는 음수 값을, 입력 함수 값 증가가 멈추는 부근에서는 양수 값을 가진다. 그러므로 f(x,y)에 g(x,y)를 더하면 에지가 강조된 함수가 생성되어, 마지막 (d)에서 h(x,y) = f(x,y) + g(x,y)로 샤프닝이 적용된 결과 영상 그래프를 나타낸다.


결론적으로, (c)의 g(x,y)는 날카로운 성분만을 가지고 있는 함수이므로, 입력 영상 f(x,y)에 g(x,y)를 더함으로써 날카로운 성분이 강조된 최종 영상 h(x,y)가 얻어지는 것으로 해석할 수 있다.

<br>

여기서, 실수 가중치를 곱하여 f(x,y)에 g(x,y)를 더하면 날카로운 정도를 사용자가 조절할 수 있게 된다.

샤프닝이 적용된 결과 영상의 수식을 다음과 같이 수정할 수 있다.

![https://blog.kakaocdn.net/dn/cb2fOh/btrSwrkZOXu/TO8bTbs7j7dQK72ks8lpJ1/img.png](https://blog.kakaocdn.net/dn/cb2fOh/btrSwrkZOXu/TO8bTbs7j7dQK72ks8lpJ1/img.png)

즉, α는 샤프닝 결과 영상의 날카로운 정도를 조절할 수 있는 파라미터이다. 이 값이 1.0이;ㄴ 경우는 날카로운 성분을 그대로 한 번 더하는 셈이고, 1보다 작은 값이라면 조금 덜 날카로운 영상을 만들 수 있다.

<br>

위의 수식에서 g(x,y) 을 치환하여 대입하고 식을 정리하면 다음과 같다.

![https://blog.kakaocdn.net/dn/pgff1/btrStP7Lgrt/Q0v2Tbo4pmZTyGFiRpbkg1/img.png](https://blog.kakaocdn.net/dn/pgff1/btrStP7Lgrt/Q0v2Tbo4pmZTyGFiRpbkg1/img.png)


<br>

OpenCV는 언샤프 마스크 필터 함수를 따로 제공하지 않는다. 다만 위의 수식을 그대로 소스 코드 형태로 작성하여 샤프닝 결과 영상을 얻을 수 있다.

alpha를 1.F로 지정하고 가우시안 필터링 GaussianBlur을 적용하여 샤프닝 연산을 수행하면 다음과 같이 나타낼 수 있다.

```cpp
    Mat blurred;
    GaussianBlur(src, blurred, Size(), sigma);

// unsharp mask (blur 제거)float alpha = 1.f;
    Mat dst = (1 + alpha)*src - alpha * blurred;
```

전체 코드는 다음과 같다.

```cpp
// 가우시안 블러링을 이용한 언샤프 마스크 연산void unsharp_mask()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);

	for (int sigma = 1;sigma <= 5;sigma++) {
		Mat blurred;
		GaussianBlur(src, blurred, Size(), sigma);

// unsharp mask (blur 제거)float alpha = 1.f;
		Mat dst = (1 + alpha)*src - alpha * blurred;

		String desc = format("sigma :%d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SCRIPT_SIMPLEX,
			1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}
```

<br>

가우시안 필터의 표준 편차 sigma 값을 1부터 5로 증가시키며 샤프닝 연산을 수행한 결과는 다음과 같다.

sigma 값이 커짐에 따라 샤프닝 연산의 결과 영상이 더욱 뚜렷해지는 것을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/8oteu/btrSySOY93N/sBcMVwak6E0kfIdXGv0By0/img.png](https://blog.kakaocdn.net/dn/8oteu/btrSySOY93N/sBcMVwak6E0kfIdXGv0By0/img.png)

![https://blog.kakaocdn.net/dn/kFNQ1/btrSy9iPMtP/PEebw6cuBa0AZw8ntPlgGK/img.png](https://blog.kakaocdn.net/dn/kFNQ1/btrSy9iPMtP/PEebw6cuBa0AZw8ntPlgGK/img.png)

![https://blog.kakaocdn.net/dn/eunNTN/btrSw5uLoxv/RiPbrLCwB6kkKzSzXC8ID1/img.png](https://blog.kakaocdn.net/dn/eunNTN/btrSw5uLoxv/RiPbrLCwB6kkKzSzXC8ID1/img.png)

---

<br>

### **잡음 제거 필터링**

영상을 획득하는 과정에서 원치 않는 잡음(noise)이 포함될 수 있다. 영상에서 잡음은 주로 영상을 획득하는 과정에서 발생하며, 디지털 카메라로 촬영하는 경우 광학적 신호를 전기적 신호로 변환하는 센서에서 주로 잡음이 추가된다.

컴퓨터 비전 시스템의 전처리 과정으로 잡음 제거 필터를 사용하는데, 다양한 종류의 잡음에 대해 사용할 수 있는 잡음 제거 필터링 기법에 대해 알아보자.

원본 신호를 s(x,y)라 하고, 여기에 추가되는 잡음을 n(x,y)라고 표현할 때 실제로 카메라에서 획득되는 영상 신호 f(x,y)는 다음과 같이 표현한다.

![https://blog.kakaocdn.net/dn/G29jj/btrStPUhaEX/nmZrqY45JKZDBBZ0xLy2oK/img.png](https://blog.kakaocdn.net/dn/G29jj/btrStPUhaEX/nmZrqY45JKZDBBZ0xLy2oK/img.png)

<br>

### **가우시안 잡음 모델**

잡음이 생성되는 방식을 **잡음 모델(noise model)** 이라 하며, 다양한 잡음 모델 중에서 가장 대표적인 잡음 모델은 **가우시안 잡음 모델(Gaussian noise model)** 이다. 이는 보통 평균이 0인 가우시안 분포를 따르는 잡음을 의미한다.

<br>

아래와 같이 평균이 0이고 표준 편차가 10인 1차원 가우시안 분포 그래프의 경우, 67%의 확률로 -10과 10 사이의 값이 잡음으로 추가된다. 표준 편차가 작은 가우시안 잡음 모델일수록 잡음에 의한 픽셀 값 변화가 적다고 할 수 있다.

![https://blog.kakaocdn.net/dn/bzsKNA/btrSwEj4qOo/YNh3UKCtbvdHHk8NKiGVMK/img.png](https://blog.kakaocdn.net/dn/bzsKNA/btrSwEj4qOo/YNh3UKCtbvdHHk8NKiGVMK/img.png)

OpenCV 함수를 이용해 영상에 가우시안 모델을 따르는 잡음을 인위적으로 추가하기 위해서는 가우시안 잡음으로 구성된 행렬을 생성하기 위해 randn() 함수를 이용한다.

![https://blog.kakaocdn.net/dn/UqVCr/btrSwpm7Whl/dJMYkxW3SajphqOICROKf0/img.png](https://blog.kakaocdn.net/dn/UqVCr/btrSwpm7Whl/dJMYkxW3SajphqOICROKf0/img.png)

<br>

이때 사용하는 가우시안 분포의 평균은 mean이고 표준 편차가 stddev이다. randn() 함수에 의해 생성된 난수는 dst 행렬의 자료형에 맞게끔 포화 연산이 수행된다.

다음과 같이, lenna 영상에 평균이 0이면서, 표준 편차가 10, 20, 30인 경우의 가우시안 잡음을 영상에 추가해보자.

```cpp
// 가우시안 잡음 필터링void noise_gaussian()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);

// 표준 편차가 10, 20, 30인 가우시안 잡음 추가for (int stddev = 10;stddev <= 30;stddev += 10)
    {
		Mat noise(src.size(), CV_32SC1);// 부호 있는 자료형 행렬 사용randn(noise, 0, stddev);// 가우시안 잡음으로 구성된 행렬을 생성하여 반환

		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);// 부호 있는 자료형 행렬 사용

		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SCRIPT_SIMPLEX,
			1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}
```

<br>

다음과 같이, 원본 영상에 비해 가우시안 잡음이 추가된 결과 영상은 거칠고 지저분해 보이며,

표준 편차 값이 증가함에 따라 잡음의 영향이 커지는 것을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/bMy6HE/btrSvdAMxAJ/h2kqbiG5ZnIJ53KTD7t2T1/img.png](https://blog.kakaocdn.net/dn/bMy6HE/btrSvdAMxAJ/h2kqbiG5ZnIJ53KTD7t2T1/img.png)

![https://blog.kakaocdn.net/dn/bJ3zhQ/btrStQezqTy/bbywnTgJUeDhbYoG9kfnYK/img.png](https://blog.kakaocdn.net/dn/bJ3zhQ/btrStQezqTy/bbywnTgJUeDhbYoG9kfnYK/img.png)

![https://blog.kakaocdn.net/dn/da70TK/btrSySVLa2J/YjYugJSNXEB0JexvaZ7jwK/img.png](https://blog.kakaocdn.net/dn/da70TK/btrSySVLa2J/YjYugJSNXEB0JexvaZ7jwK/img.png)

---

<br>

### **양방향 필터**

대부분의 영상에는 가우시안 잡음이 포함되어 있으며, 많은 컴퓨터 비전 시스템은 이를 제거하기 위해 가우시안 필터를 사용한다. 입력 영상에서 픽셀 값이 크게 변하지 않는 평탄한 영역에 가우시안 필터가 적용되는 경우, 주변 픽셀 값이 부드럽게 블러링 되며 잡음의 영향도 줄어든다. 그러나 픽셀 값이 급격히 변경되는 에지 근방에 동일한 가우시안 필터가 적용되면 잡음 뿐 아니라 에지 성분까지 감소한다. 따라서, 잡음이 줄어듬과 동시에 에지도 무뎌져 객체의 윤곽이 흐려진다.

이 단점을 보완하기 위해, 에지 정보는 그대로 유지하며 잡음만 제거하는 **에지 보전 잡음 제거 필터 (edge-preserving noise removal filter)** 에 대해 연구가 되었다.그 중 하나인 **양방향 필터(bilateral filter)** 은 에지 성분은 그대로 유지하며 가우시안 잡음을 효과적으로 제거하는 알고리즘이다.

<br>

이 필터는 다음 공식을 사용해 필터를 수행한다.

![https://blog.kakaocdn.net/dn/Izbxg/btrSwEj4yeW/rgKYdI0mj1nzxHAlAZBsO0/img.png](https://blog.kakaocdn.net/dn/Izbxg/btrSwEj4yeW/rgKYdI0mj1nzxHAlAZBsO0/img.png)

위 수식은, 두 점의 픽셀 밝기 값의 차이가 적은 평탄한 영역에서는 큰 가중치를 갖게 만든다. 반면 에지를 사이에 두고 있는 두 픽셀에 대해서는 상대적으로 두 점의 픽셀 밝기 값이 크게 나타나 두 점의 픽셀 값에 의한 가중치가 거의 0에 가까워, 에지 근방에서는 가우시안 블러링 효과가 거의 나타나지 않고 에지가 보존된다.

양방향 필터 수식이 픽셀 값의 차이에 의존적이므로 이는 모든 픽셀에서 서로 다른 형태를 갖게 된다. 즉 모든 픽셀 위치에서 주변 픽셀과의 밝기 차이에 의한 고유의 필터 마스크 행렬을 만들어 마스크 연산을 수행해야 한다. 따라서 가우시안 블러링보다 훨씬 많은 연산량을 필요로 한다.

<br>

### **bilateralFilter() 함수**

OpenCV 에서는 bilateralFilter() 함수를 이용해 양방향 필터를 수행한다.

![https://blog.kakaocdn.net/dn/Jrshn/btrSxE4KPw5/QciKD2X9vF0NSXRhffEjv1/img.png](https://blog.kakaocdn.net/dn/Jrshn/btrSxE4KPw5/QciKD2X9vF0NSXRhffEjv1/img.png)

양방향 필터링으로 블러링 연산을 수행하는 bilateralFilter() 함수

sigmaSpace 값은 일반적인 가우시안 필터링에서 사용하는 표준 편차와 같은 개념으로, 값이 클수록 더 많은 주변 픽셀을 고려하여 블러링을 수행하게 된다.

sigmaColor은 주변 픽셀과의 밝기 차이에 관한 표준 편차이다. 이를 작게 지정할 경우, 픽셀 값 차이가 큰 주변 픽셀과는 블러링 연산이 적용되지 않는다. 따라서 이 값을 이용해 어느 정도 밝기 차를 갖는 에지를 보존할 것인지를 조정할 수 있다.

```cpp
// 양방형 필터링을 이용한 잡음 제거void filter_bilateral()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);

	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);// 표준 편차 5인 가우시안 잡음 추가add(src, noise, src, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	Mat dst2;
// sigmaColor 표준 편차 10, sigmaSpace 표준 편차 5로 설정bilateralFilter(src, dst2, -1, 10, 5);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}
```

<br>

표준 편차가 5인 가우시안 잡음이 추가된 lenna 영상에 대하여,

가우시안 블러링을 이용한 잡음 제거 결과 영상인 dst1는 잡음은 줄었지만 전체 경계가 블러링되어 흐릿하게 변경된 반면,

양방향 필터링 연산의 결과 영상인 dst2는 머리카락, 모자, 배경 사물의 경계는 그대로 유지되며, 평탄안 영역의 잡음이 크게 줄어들어 눈으로 보기에 깔끔한 결과 영상을 만들었음을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/cD7v7x/btrSwTuwQ5x/RSdfVpYEFGjl4eXoEkQvEK/img.png](https://blog.kakaocdn.net/dn/cD7v7x/btrSwTuwQ5x/RSdfVpYEFGjl4eXoEkQvEK/img.png)

![https://blog.kakaocdn.net/dn/bPcQb2/btrSxEX0hnU/MlNPGoAYSrTe67FyOYz5T0/img.png](https://blog.kakaocdn.net/dn/bPcQb2/btrSxEX0hnU/MlNPGoAYSrTe67FyOYz5T0/img.png)

![https://blog.kakaocdn.net/dn/snTk0/btrSxO7kPrm/1yLSlUXvQbKAKeYgBLCK7K/img.png](https://blog.kakaocdn.net/dn/snTk0/btrSxO7kPrm/1yLSlUXvQbKAKeYgBLCK7K/img.png)

잡음이 추가된 입력 영상에 대해 Gaussian Blur, Bilateral Filter을 이용한 잡음 제거 결과 비교

