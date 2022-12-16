# CH 06. 영상의 산술, 논리 연산

# **영상의 산술 연산**

영상은 일종의 2차원 행렬이므로, 행렬의 산술 연산(arithmetic operation)을 그대로 적용할 수 있다.

즉 두 개의 영상을 서로 더하거나 빼는 연산을 수행함으로써 새로운 결과 영상을 생성할 수 있다.

영상의 덧셈 연산을 수식으로 표현하면 다음과 같다.

두 입력 영상(src1, src2) 에서 같은 위치 픽셀 값을 서로 더하여 결과 영상 픽셀값(dst(x,y)) 으로 설정하는 연산이라 할 수 있다.

<img src="https://blog.kakaocdn.net/dn/OciSh/btrSqNH4YVO/P6XwFE44hJmx7MblwgueV0/img.png" width=300>

<br>

덧셈 연산 수행 시, 그레이스케일 최댓값인 255보다 결과값이 커지는 경우가 발생하는데

이러한 경우 결과 영상 픽셀값을 255로 설정하는 포화 연산도 함께 수행해야 한다.

이를 수식으로 좀 더 정확하게 표현하자면 다음과 같다.

![https://blog.kakaocdn.net/dn/sDTtf/btrSqWZcRnr/cQhaRBJj9eP9YSKylasQi0/img.png](https://blog.kakaocdn.net/dn/sDTtf/btrSqWZcRnr/cQhaRBJj9eP9YSKylasQi0/img.png)

<br>

OpenCV에서는 add() 함수를 사용해 영상의 덧셈을 수행할 수 있다.

![https://blog.kakaocdn.net/dn/mTNJw/btrSrn93LRk/tLSdIEIkrRMMVtMqpjw1Ak/img.png](https://blog.kakaocdn.net/dn/mTNJw/btrSrn93LRk/tLSdIEIkrRMMVtMqpjw1Ak/img.png)

덧셈 결과가 dst 객체가 표현할 수 있는 자료형의 범위를 벗어나는 경우 자동으로 포화 연산을 수행한다.

add() 함수에서 mask와 dtype 인자는 기본 값으로 가지고 있는데, src1와 src2 행렬 깊이가 서로 다른 경우에는 dtype 인자를 반드시 지정해줘야 한다.

두 영상의 타입이 서로 같으면, add() 함수 대신 + 연산자 재정의를 사용할 수 있다.

<br>

### **가중치 부여하여 덧셈 연산 수행**

두 영상을 더할 때 각 영상에 가중치를 부여하여 덧셈 연산을 할 수도 있는데, 이를 수식으로 표현하면 다음과 같다.

![https://blog.kakaocdn.net/dn/b5jNE2/btrSqHuqvXd/0zPRmhkJTWYPvSlogQ7RvK/img.png](https://blog.kakaocdn.net/dn/b5jNE2/btrSqHuqvXd/0zPRmhkJTWYPvSlogQ7RvK/img.png)

보통 a알파와 b베타의 합이 1이 되도록 설정하는 경우가 많으면, 두 합이 1이면 결과 영상에서 포화되는 픽셀이 발생하지 않는다.

a=0.1, b=0.9와 같이 설정하는 경우, src1 영상의 윤곽은 조금만 나타나고, src2 영상의 윤곽은 많이 나타나는 결과가 생성된다.

두 합이 1이 넘으면, 두 입력 영상보다 밝아지고, 덧셈 결과가 255보다 커지는 포화 현상이 발생할 수 있다. 합이 1보다 작다면, 두 입력 영상의 평균 밝기보다 어두운 결과가 생성된다.

두 영상의 가중치 합을 구하려면 addWeighted() 함수를 사용한다. 함수의 원형은 다음과 같다.

![https://blog.kakaocdn.net/dn/bFd8k6/btrSsQYdfzD/azbHAGjIKiJKAhMQqdj6Ak/img.png](https://blog.kakaocdn.net/dn/bFd8k6/btrSsQYdfzD/azbHAGjIKiJKAhMQqdj6Ak/img.png)

<br>

addWeighted()는 gamma 인자를 통해 가중치의 합에 추가적인 덧셈을 한꺼번에 수행할 수 있다. 수식은 다음과 같이 표현된다.

![https://blog.kakaocdn.net/dn/qd9MR/btrSqFDnLEl/K4nOZ3OZfpCQAKXKT1gEV1/img.png](https://blog.kakaocdn.net/dn/qd9MR/btrSqFDnLEl/K4nOZ3OZfpCQAKXKT1gEV1/img.png)

두 입력 영상의 평균 영상을 생성하려면 alpha와 beta에 각각 0.5의 가중치를 부여하면 된다.

<br>

다음 예제를 실행해보자.

```cpp
// 두 영상의 덧셈 연산void add_image()
{
	Mat src1 = imread("airplane.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("mask_plane.bmp", IMREAD_GRAYSCALE);

	Mat dst = src1 + src2;
	imshow("dst", dst);

// addWeighted(src1, 0.5, src2, 0.5, 0, dst); // 가중치 부여

	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}
```

가중치를 부여하지 않은 경우는 다음과 같이, 그레이스케일 값의 최댓값인 255를 넘어가면서 포화 연산이 수행되고

전체적으로 밝은 영상이 나타난다.

![https://blog.kakaocdn.net/dn/NawZJ/btrSruacYKu/33skEhhvwkVEAwNTaAmz81/img.png](https://blog.kakaocdn.net/dn/NawZJ/btrSruacYKu/33skEhhvwkVEAwNTaAmz81/img.png)

가중치를 각각 0.5씩 부여하여 덧셈 수행을 한 결과는 다음과 같이 src1과 src2를 적절히 동일하게 더해진 결과 영상이 나타남을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/PNl18/btrStzaQNHC/7pykQtUsRCHvTrb39twdhK/img.png](https://blog.kakaocdn.net/dn/PNl18/btrStzaQNHC/7pykQtUsRCHvTrb39twdhK/img.png)

<br>

뺄셈 연산도 마찬가지로 subtract() 함수 또는 - 연산자 재정의를 사용하여 수행할 수 있다.

마찬가지로 뺄셈 결과 픽셀 값이 0보다 작아지면, 결과 영상의 픽셀 값을 0으로 설정하는 포화 연산을 수행해야 한다.

![https://blog.kakaocdn.net/dn/lB6ZB/btrSsSItXqR/yDvgEVCezISviaXvqQkK41/img.png](https://blog.kakaocdn.net/dn/lB6ZB/btrSsSItXqR/yDvgEVCezISviaXvqQkK41/img.png)

뺄셈 연산의 경우 뺄셈 순서에 따라 결과 값이 달라지는데,

만약 두 영상의 뺄셈 순서에 상관없이 픽셀 값 차이가 큰 영역을 두드러지게 나타내고 싶다면 차이 연산을 수행할 수 있다.

이는 뺄셈 연산 결과에 절댓값을 취하는 연산으로, 차이 연산으로 구한 결과 영상은 차영상(difference image)라고 한다.

![https://blog.kakaocdn.net/dn/dNOvTW/btrSm1gfSvG/VmxIksn2ikGH77vkuu9Q90/img.png](https://blog.kakaocdn.net/dn/dNOvTW/btrSm1gfSvG/VmxIksn2ikGH77vkuu9Q90/img.png)

이를 수식으로 표현하면 위와 같고, absdiff() 함수의 원형은 다음과 같다.

![https://blog.kakaocdn.net/dn/cAuwWr/btrSnEZvO57/IbugxzNNadwwBGYHPJnIe1/img.png](https://blog.kakaocdn.net/dn/cAuwWr/btrSnEZvO57/IbugxzNNadwwBGYHPJnIe1/img.png)

<br>

다음 코드를 통해 영상의 덧셈, 뺄셈, 차 연산의 수행 결과를 살펴보자.

lenna 영상과 검정색 배경에 흰색 정사각형 영상에 대한 연산 수행을 해보도록 하자.

dst1에는 add() 연산, dst2에는 subtract() 연산, dst3에는 addWeighted() 연산, dst4에는 absdiff() 연산 결과 영상이 담기게 된다.

```cpp
// 영상의 덧샘, 뺄셈, 차 연산 수행void calculate_image()
{
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	add(src1, src2, dst1);
	subtract(src1, src2, dst2);
	addWeighted(src1, 0.5, src2, 0.5, 0, dst3);
	absdiff(src1, src2, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4",dst4);
	waitKey();

	destroyAllWindows();
}
```

<br>

결과는 다음과 같다.

add() 연산의 경우, 흰색 정사각형 부분의 덧셈 연산 수행 결과값은 255가 넘어가므로 그대로 포화 연산이 수행되어 255를 유지하여 흰색으로 나타나고, subtract() 연산의 경우도 마찬가지로 255값을 뺀 결과 값이 0 이하로 넘어가므로 포화 연산에 의해 0을 유지하여 검정색으로 나타나게 된다.

dst3의 경우 addWeighted() 함수로 가중치를 각각 0.5를 부여하여 덧셈 연산을 수행하여 두 영상의 평균값 결과가 나타났고,

dst4의 경우 두 영상의 차에 해당하는 결과가 나타난 것을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/uYPXj/btrSqsxn6zd/NiXnNfQ2fhOm308rmAKCQk/img.png](https://blog.kakaocdn.net/dn/uYPXj/btrSqsxn6zd/NiXnNfQ2fhOm308rmAKCQk/img.png)

---

<br>

# **영상의 논리 연산**

영상의 **논리 연산(Logical Operation)**은 픽셀 값을 이진수로 표현하여 각 비트 단위 논리 연산을 수행하는 것을 말한다.

OpenCV에서는 다양한 논리 연산 중 논리곱(AND), 논리합(OR), 배타적 논리합(XOR), 부정(NOT) 연산을 지원한다.

> **논리곱(AND) :** 두 개의 입력 비트가 모두 1인 경우에 결과가 1이 되는 연산
> 
> 
> **논리합(OR) :** 두 개의 입력 비트 중 하나라도 1이 있으면 결과가 1이 되는 연산
> 
> **배타적 논리합(XOR) :** 두 개의 입력 비트 중 오직 하나만 1인 경우 결과가 1이 되는 연산
> 
> **부정(NOT)** : 입력 비트가 0이면 1, 입력 비트가 1이면 결과가 0이 되는 연산
> 
> ![https://blog.kakaocdn.net/dn/bZkIZa/btrSqN2Amhy/BhEu0Moc5o7fa1c5wTU08k/img.png](https://blog.kakaocdn.net/dn/bZkIZa/btrSqN2Amhy/BhEu0Moc5o7fa1c5wTU08k/img.png)
> 

<br>

영상의 논리 연산은 각 픽셀 값에 대하여 비트 단위로 이루어지며 그레이스케일 영상의 경우 한 픽셀을 구성하는 8개의 비트에 모두 논리 연산이 이루어진다.

두 입력 픽셀 110, 200에 대하여 논리 연산을 수행하면 다음과 같다.

110을 이진수로 표현하면 01101110(2), 200을 이진수로 표현하면 11001000(2)이고

이 두 수에 대해 비트 단위 논리곱, 논리합, 배타적 논리합, 부정 연산을 다음과 같은 결과가 나타난다.

![https://blog.kakaocdn.net/dn/PiYpG/btrSru9g7kt/Of8qgbOZlCmV7IkbJKkjv0/img.png](https://blog.kakaocdn.net/dn/PiYpG/btrSru9g7kt/Of8qgbOZlCmV7IkbJKkjv0/img.png)

OpenCV 에서는 영상의 비트 단위 논리 연산을 수행하는 bitwise_and(), bitwise_or(), bitwise_xor(), bitwise_not() 함수를 제공한다.

![https://blog.kakaocdn.net/dn/btJB1I/btrSqtca9Uv/pljXcefNRExR8JYk7YElJ0/img.png](https://blog.kakaocdn.net/dn/btJB1I/btrSqtca9Uv/pljXcefNRExR8JYk7YElJ0/img.png)

bitwise_and(), bitwise_or(), bitwise_xor(), bitwise_not() 함수

<br>

위의 논리 연산 함수를 이용해 lenna 이미지와 square 이미지에 대한 연산을 수행해보자.

```cpp
int calc() {
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	bitwise_and(src1, src2, dst1);// and연산bitwise_or(src1, src2, dst2);// or 연산bitwise_xor(src1, src2, dst3);// xor 연산bitwise_not(src1, dst4);// not 연산imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();

	return 0;
}
```

lenna와 검정색 배경에 흰색 정사각형을 띄는 square 이미지에 대한 비트 연산을 수행한 결과는 다음과 같다.

square 이미지의 가운데 사각형 영역의 픽셀 값은 모두 흰색 255로, 이진수로 표현하면 모든 비트가 1로 설정된 11111111(2) 로 표현되고, 바깥 배경 영역의 픽셀값은 모두 검정색 0으로, 이진수로 표현하면 00000000(2)라 할 수 있다.

<br>

따라서 AND 연산의 결과 영상(dst1)의 경우 square 이미지에 의해 사각형 영역의 바깥 배경 영역에 대해 비트가 0을 하나라도 포함하므로 연산 결과가 0으로 나타나 검정색 배경에 대해서는 그대로 검정색 배경이 나타나는 것을 확인할 수 있다.

OR 연산의 결과 영상(dst2)의 경우 square 이미지의 내부 하얀색 사각형 영역이 1의 비트를 지니므로, 하나라도 1인 경우 결과값이 1이 되므로 해당 사각형 영역은 그대로 흰색으로 나타나는 것을 확인할 수 있다.

XOR 연산의 경우 흰색 사각형 영역에 대해 반전이 일어난 것을 확인할 수 있다. 기존 레나 이미지에서 밝았던 부분은 XOR 연산 수행으로 1과 1이 만난 경우이므로 결과가 0이 되어 어두워지고, 어두웠던 부분은 1과 0이 만난 경우이므로 결과가 1이 되어 밝아진다.