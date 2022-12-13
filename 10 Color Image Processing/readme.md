# CH 10. 컬러 영상 처리

영상의 색상 정보를 이용해 영상을 처리하는 기법에 대해 알아보자.

영상의 명암비를 높이는 컬러 히스토그램 평활화 기법, 그리고 컬러 영상에서 원하는 색상 영역을 검출하는 방법에 대해 알아보자.

## **컬러 히스토그램 평활화**

그레이스케일 영상에서 활용한 equalizeHist() 함수를 통해 히스토그램 평활화를 수행했다. **3**채널 컬러 영상에 대해 히스토그램 평활화를 수행하기 위해서는, RGB 3개의 채널에 대해 각각 평활화를 수행하는 것이 아니라, YCrCb 색 공간으로 변환하고, Y 성분에 대해서만 히스토그램 평활화를 수행해야 한다.

만약 다음과 같이 RGB 각 채널에 히스토그램 평활화를 수행하면 어떻게 될까?

이 방식으로 각 채널마다 서로 다른 형태의 명암비 변환 함수를 사용하면, 원본 영상과 다른 색상의 결과 영상이 만들어진다. 아래 오른쪽 그림과 같이 녹색 성분이 많이 포함되어 있는 영상에 히스토그램 평활화 수행을 한 후 다시 채널을 합쳐 만들게 되면 원본 영상의 색감과 완전히 다른 결과 영상이 만들어진다.

![https://blog.kakaocdn.net/dn/bKZWPh/btrS1RosGW5/khbFeobTHrzg00EpFtwcyk/img.png](https://blog.kakaocdn.net/dn/bKZWPh/btrS1RosGW5/khbFeobTHrzg00EpFtwcyk/img.png)

![https://blog.kakaocdn.net/dn/ceG1DE/btrSXq0EzND/4kIIhm5ClOlqQCyCgSBEnK/img.png](https://blog.kakaocdn.net/dn/ceG1DE/btrSXq0EzND/4kIIhm5ClOlqQCyCgSBEnK/img.png)

따라서 컬러 영상의 색감은 변경하지 않고, 명암비를 높이고자 하는 경우 영상의 밝기 정보만을 사용해야 한다.

따라서 보통 히스토그램 평활화 수행 시, 입력 영상을 밝기 정보와 색상 정보로 분리한 후, 밝기 정보에 대해서만 히스토그램 평활화를 수행한다. 예를 들어 YCrCb 색공간을 사용하는 경우, Y 성분에 대해서만 히스토그램 평활화를 수행하고, 변경된 Y 채널과 나머지 채널을 다시 합쳐 결과를 도출한다.

<br>

결국 색상 정보는 전혀 변경하지 않아 입력 영상의 색감이 그대로 유지되고, 오직 밝기 성분에 대해서만 명암비가 증가하게 된다.

![https://blog.kakaocdn.net/dn/bkTR3G/btrS1Kv8l87/qp5TKnVhgKWmKIzdHE3Pl0/img.png](https://blog.kakaocdn.net/dn/bkTR3G/btrS1Kv8l87/qp5TKnVhgKWmKIzdHE3Pl0/img.png)

<br>

다음 예제를 살펴 보자.

```cpp
// 컬러 영상의 히스토그램 평활화void color_histogram()
{
	Mat src = imread("pepper.bmp", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);// YCrCb 색 공간으로 변경

	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);// 채널 분리// Y 성분(명암비)에 해당하는 영상만 히스토그램 평활화 수행equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);

// 세 채널에 대한 영상 다시 합치기
	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);

	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);// BGR 색 공간으로 다시 변환imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return;
}
```

우선 BGR 색 공간의 평면 pepper src 영상에 대하여, YCrCB 색 공간으로 변환을 수행한다.

이후 채널을 분리한 영상의 0번 값인, Y 성분(brightness, 밝기 성분)에 해당하는 영상에 대해서만 equalizeHist() 함수를 통해 히스토그램 평활화를 수행하고, 세 채널 영상을 다시 합쳐 BGR 색 공간으로 변환하고 결과를 출력하게 된다.

<br>

결과는 다음과 같다. 색감은 그대로 유지한채, 밝기에 대한 히스토그램 평활화가 이루어져 명암비가 높아지며 조금 더 뚜렷한 영상이 나타난 것을 확인할 수 있다. 히스토그램 평활화를 통해 어두운 부분은 더욱 어두워졌으며, 밝은 부분은 더욱 밝아진 것이 확실하게 나타난다.

![https://blog.kakaocdn.net/dn/dExnKA/btrSXqsQcIA/TiDZAFKSwVmZS49eNAAJwk/img.png](https://blog.kakaocdn.net/dn/dExnKA/btrSXqsQcIA/TiDZAFKSwVmZS49eNAAJwk/img.png)

YCrCB 영상 변환 후 Y 성분에 대한 히스토그램 평활화 수행

---

<br>

### **색상 범위 지정에 의한 영역 분할**

컬러 영상을 다룰 때 특정 색상 영역을 추출하는 작업이 많이 요구되기도 한다. 예를 들어 입력 영상에서 빨간색 픽셀을 모두 찾아내면 빨간색 객체의 위치와 크기를 알아낼 수 있다. 컬러 영상에서 대표적인 색상 영역을 구분하고자 할 때는 색상 정보가 따로 설정되어 있는 HSV 공간을 사용하는 것이 유리하다.

<br>

### **inRange() 함수**

OpenCV 에서 행렬의 원소값이 특정 범위 안에 있는지 확인하기 위해 inRange() 함수를 사용한다.

![https://blog.kakaocdn.net/dn/bgLy3w/btrS1P5gsb6/0mND25os6KvWr41aU7POOk/img.png](https://blog.kakaocdn.net/dn/bgLy3w/btrS1P5gsb6/0mND25os6KvWr41aU7POOk/img.png)

inRange() 는 입력 영상 src의 픽셀 값이 지정한 밝기 또는 색상 범위에 포함되어 있으면 흰색, 그렇지 않으면 검은색으로 채워진 마스크 영상 dst를 반환한다.

만약 그레이스케일 영상을 입력으로 사용하는 경우, 특정 밝기 값 범위에 있는 픽셀 영역을 추출할 수도 있다. 1채널 영상에 대해 inRange() 함수의 동작을 수식으로 표현하면 다음과 같다.

<img src="https://blog.kakaocdn.net/dn/qSfkP/btrS1Qpym5L/2mt8P7RV9n0OcPvxVc6zI0/img.png" width=400>

<br>

입력 영상의 채널이 2개 이상이라면, 각 채널 값이 모두 지정된 범위를 만족할 때 dst 영상의 픽셀 값이 255로 설정된다.

여기서 lowerp와 upperb 인자에는 Mat 객체 또는 Scalar 객체를 지정할 수도 있다. 만약 Mat 객체를 지정하는 경우, src 의 모든 픽셀에 각기 다른 하한 값과 상한 값을 지정할 수 있다. Scalar 또는 int, double 과 같은 기본 자료형을 지정하는 경우, src 모든 픽셀에 동일한 하한, 상한 값이 적용된다.

<br>

다음 예제를 살펴보자.

예제는 영상 출력 창에 두 개의 트랙바를 붙여서 사용자가 HSV 색 공간에서 색상의 하한값과 상한 값을 조절하여, 사용자가 설정한 색상 값 범위에 해당하는 영역을 흰색, 그 외의 영역은 검은색으로 표현된 마스크 영상을 화면에 출력하게 된다.

inRange() 함수의 lowerb, upperb 인자에는 Scalar 값을 지정하였는데, 이를 이용하여 색상의 하한과 상한 값, 채도와 명도의 범위르 지정하였다.

```cpp
// 특정 색상 영역 분할int lower_hue = 40, upper_hue = 80;// upperb, lowerb의 default 값 설정
Mat src, src_hsv, mask;

void on_hue_changed(int, void*) {
// 채도의 범위를 100부터 255로 설정, 명도는 0부터 255까지 설정Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);

// 색 성분 범위가 lowerb와 upperb 사이인 위치의 픽셀만 흰색으로 설정한 mask 영상 생성inRange(src_hsv, lowerb, upperb, mask);

	imshow("mask", mask);
}

void in_range() {
	src = imread("candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

// HSV 색 공간으로 변환cvtColor(src, src_hsv, COLOR_BGR2HSV);
	imshow("src", src);

// 상한, 하한 값을 조정하는 두 트랙바 생성, 색상의 최댓값을 179로 지정namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	on_hue_changed(0, 0);// 트랙바 콜백 함수 강제 호출waitKey();
	return;
}
```

<br>

결과는 다음과 같이 나타난다.

![https://blog.kakaocdn.net/dn/czwNlG/btrS1LaLlEM/ymoX8iQCHrYyeFCszvyZek/img.png](https://blog.kakaocdn.net/dn/czwNlG/btrS1LaLlEM/ymoX8iQCHrYyeFCszvyZek/img.png)


<br>

다음은 색상H의 범위가 42~82 (Green), 채도 S 의 범위가 100~255, 명도 V의 범위가 9~255 사이인 픽셀 위치를 찾은 결과이다.

H 값이 60 근방이면 녹색을 나타낸다. 채도 값이 100보다 큰 픽셀만 찾은 것은 충분히 선명한 녹색만 찾기 위함이다. 명도 범위를 0~255 사이로 지정한 것은 명도의 값은 상관하지 않겠다는 의미이다.

두번째와 같이 100~140 사이의 H 색상을 지정한 경우 120 근방의 값을 갖는 파란색 성분만 흰색으로 표현이 된다.

![https://blog.kakaocdn.net/dn/lZzAn/btrS0fp6YHk/kU1yYhyiRx25hDoGyykkJk/img.png](https://blog.kakaocdn.net/dn/lZzAn/btrS0fp6YHk/kU1yYhyiRx25hDoGyykkJk/img.png)

![https://blog.kakaocdn.net/dn/cS8ea7/btrSW598Jwd/07ey1Dn5f4oAgPDNnK57yK/img.png](https://blog.kakaocdn.net/dn/cS8ea7/btrSW598Jwd/07ey1Dn5f4oAgPDNnK57yK/img.png)

---

<br>

## **히스토그램 역투영**

위에서 설명한 inRange() 함수를 사용하여 특정 색상 영역을 검출하는 경우, 빨강, 노랑, 파랑 등 원색에 가까운 색상을 찾기에는 효과적이다. 그러나 사람의 피부색(살구색)과 같은 경우 미세한 변화가 있거나 색상 값을 수치적으로 지정하기 어려운 경우에는 적합하지 않은 방법이다.

**히스토그램 역투영 (Historgram Backprojection)** 이란, 입력 영상에서 찾고자 하는 객체의 기준 영상을 미리 가지고 있는 경우 컬러 히스토그램 정보를 이용하여 주어진 입력 영상에서 해당 히스토그램 모델과 일치하는 픽셀을 찾아내는 기법이다.

<br>

### **calcBackProject() 함수**

히스토그램 역투영은 calcBackProject() 함수를 이용하여 수행할 수 있다.

<img src="https://blog.kakaocdn.net/dn/b3BA8l/btrSZ2LgJiN/ggLKXVwyeaWpciV1CAwpnK/img.png" width=400>


위 함수는 입력 영상 images에서 히스토그램 hist 를 따르는 픽셀을 찾고, 그 정보를 backProject 영상으로 반환한다.

이 때 사용하는 히스토그램 행렬은 calcHist() 함수로 구하게 된다.

<br>

이를 이용해 입력 영상에서 피부색 영역을 추출하는 예제를 살펴보자.

```cpp
// 히스토그램 역투영을 이용한 피부색 영역 검출 예제void histogram_project()
{
	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR);// 기존의 사람 영상
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);// 피부에 해당하는 곳만 흰색으로 표시한 마스크

// ycrcb 공간으로 변환cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	Mat hist;
	int channels[] = { 1,2 };
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins, cr_bins };
	float cr_range[] = { 0,256 };
	float cb_range[] = { 0,256 };
	const float* ranges[] = { cr_range, cb_range };

// 피부색 영역의 CrCb 2차원 히스토그램 계산하여 출력 영상을 hist에 저장calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

/* 히스토그램 역투영을 입력 영상에 적용 */

	Mat src, src_ycrcb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);// Ycrcb 공간으로 변환// 히스토그램 역투영
	Mat backproj;
// 입력 영상 hist 히스토그램을 이용하여 입력 영상에 대한 역투영 수행하여 backProject 출력 영상에 저장calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

	imshow("reference", ref);// 원본 아이 영상 (히스토그램 도출을 위한 기준 영상)imshow("mask", mask);// 피부색에 해당하는 곳만 흰색 영역으로 나타낸 마스크 영상imshow("src", src);// 두 아이 영상imshow("backproj", backproj);// 히스토그램 역투영 결과 영상waitKey();
	return;
}
```

<br>

위 예제는 피부색이 포함된 아이의 영상을, 피부색이 나타난 영역만 흰색으로 표시한 마스크 영상을 이용해 기준 영상에서 피부색 영역의 CrCb 히스토그램을 구하고, 그 결과를 콘솔에 출력하였다. 이는 CrCb 평면에서 피부색을 표현하는 영역이 가운데에서 좌측 하단 부분에 나타난 것 을 확인할 수 있다.

<br>

이후 두 아이가 담긴 src 영상에 대하여, hist 히스토그램을 역투영을 수행하였다. backproj 영상에서 밝은 회색, 흰색으로 표시된 영역은 입력 영상의 픽셀 값이 지정한 히스토그램 hist에서 높은 빈도수로 표현된 것이다. 검은색으로 나타난 부분은 해당 픽셀 값이 히스토그램에서 빈도수가 낮거나 0임을 의미한다.

![https://blog.kakaocdn.net/dn/dxgmck/btrSZZ2cbQo/ToaskzWZLPnKQEKlobNsZ1/img.png](https://blog.kakaocdn.net/dn/dxgmck/btrSZZ2cbQo/ToaskzWZLPnKQEKlobNsZ1/img.png)

![https://blog.kakaocdn.net/dn/boZTNF/btrS1dSRpFV/2eYeRMESKokWlZpZU9HsIk/img.png](https://blog.kakaocdn.net/dn/boZTNF/btrS1dSRpFV/2eYeRMESKokWlZpZU9HsIk/img.png)

- 정리
    
    # 컬러 영상 다루기
    
    ### 컬러 영상 픽셀 값 반전
    
    ```cpp
    // 컬러 영상의 픽셀 값 반전
    void color_inverse() {
    	Mat src = imread("butterfly.jpg", IMREAD_COLOR);
    
    	if (src.empty()) {
    		cerr << "Image load failed!" << endl;
    		return;
    	}
    
    	Mat dst(src.rows, src.cols, src.type());
    
    	for (int j = 0;j < src.rows; j++) {
    		for (int i = 0;i < src.cols; i++) {
    			Vec3b& p1 = src.at<Vec3b>(j, i);
    			Vec3b& p2 = dst.at<Vec3b>(j, i);
    
    			// BGR 값 각각 반전 수행
    			p2[0] = 255 - p1[0]; // B
    			p2[1] = 255 - p1[1]; // G
    			p2[2] = 255 - p1[2]; // R
    		}
    	}
    	imshow("src", src);
    	imshow("dst", dst);
    
    	waitKey();
    	destroyAllWindows();
    }
    ```
    
    ### 색 공간 변환
    
    - OpenCV에서는 BGR 순서로 색상이 저자된 컬러 영상의 색 공간을 HSV, YCrCB 등 다른 색 공간으로 변환하는 인터페이스를 제공
    - `cvtColor()` 함수를 사용해 영상의 색 공간을 다른 색 공간으로 변환
        
        ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/66115f03-247f-4468-b8ce-d4788f38866e/Untitled.png)
        
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/4fbd2cb4-bedf-4bfe-a397-de72d8b9ecc6/Untitled.png)
    
    ### 컬러 영상 그레이스케일로 변환
    
    - `BGR2GRAY` , `GRAY2BGR` : 컬러 영상은 3개의 채널에 대해 연산 수행해야 하므로 더 많은 연산 시간을 필요로 함
        - 입력 영상을 그레이스케일 영상으로 변환하여 처리하는 것이 효율적
    
    ```cpp
    // 컬러 영상을 그레이스케일 영상으로 변환
    void color_graysacle() {
    	Mat src = imread("butterfly.jpg");
    
    	if (src.empty()) {
    		cerr << "Image load failed!" << endl;
    		return;
    	}
    
    	Mat dst;
    	cvtColor(src, dst, COLOR_BGR2GRAY); // 컬러에서 그레이스케일로 변환
    
    	imshow("src", src);
    	imshow("dst", dst);
    
    	waitKey();
    	destroyAllWindows();
    }
    ```
    
    ### 색상 채널 나누기
    
    - `BGR2HSV` , `HSV2BGR` : 색상, 채도, 명도로 색을 표현하는 HSV
        - 채도: 색의 순도 (높으면 맑고, 낮으면 탁한)
        - 명도: 빛의 세기 (높으면 밝고, 낮으면 어두움)
            
            ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/d616e3d3-0dd4-483f-ba4c-0298235fad6c/Untitled.png)
            
    
    ```cpp
    // BGR 컬러 영상의 채널 나누기
    void color_split() {
    	Mat src = imread("candies.png");
    
    	if (src.empty()) {
    		cerr << "Image load failed!" << endl;
    		return;
    	}
    
    	vector<Mat> bgr_planes;
    	split(src, bgr_planes);
    
    	imshow("src", src);
    	imshow("B_plane", bgr_planes[0]);
    	imshow("G_plane", bgr_planes[1]);
    	imshow("R_plane", bgr_planes[2]);
    
    	waitKey();
    	destroyAllWindows();
    }
    ```
    
    ### 컬러 히스토그램 평활화
    
    - `BGR2YCrCb` , `YCrCb2BGR` : YCrCb 색 공간에서는 Cr과 Cb를 함께 조합하여 색을 구분
        - Y 성분 : 밝기 또는 휘도 정보
        - Cr, Cb: 색상 또는 색차 정보
            
            ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/45771f0d-2809-4124-9df6-e2ad70b248e8/Untitled.png)
            
    - 명암비 높이기 (Y 성분)
    
    ```cpp
    // 컬러 영상의 히스토그램 평활화
    void color_histogram() {
    	Mat src = imread("pepper.bmp", IMREAD_COLOR);
    	if (src.empty()) {
    		cerr << "Image load failed!" << endl;
    		return;
    	}
    
    	// YCrCb 색 공간으로 변경
    	Mat src_ycrcb;
    	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
    
    	// 채널을 분리
    	vector<Mat> ycrcb_planes;
    	split(src_ycrcb, ycrcb_planes);
    	// Y 성분(명암비)에 해당하는 영상만 히스토그램 평활화 수행
    	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);
    
    	// 세 채널에 대한 영상 합치기
    	Mat dst_ycrcb;
    	merge(ycrcb_planes, dst_ycrcb);
    
    	Mat dst;
    	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);
    
    	imshow("src", src);
    	imshow("dst", dst);
    
    	waitKey(0);
    	return;
    }
    ```
    
    ### 색상 범위 지정에 의한 영역 분할
    
    - 특정 색상을 추출
    - `inRange()` : 행렬의 원소 값이 특정 범위 안에 있는지 확인하는 함수
        - 입력 영상 src의 픽셀 값이 지정한 밝기 또는 색상 범위에 포함되어 있으면 흰색
        - 그렇지 않으면 검은색으로 채워진 마스크 영상 반환
            
            ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/9422b706-1bd1-485c-8043-6843adbc7ae0/Untitled.png)
            
        
        ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/33d130d8-9aa0-4cac-9c4c-7cda29f42739/Untitled.png)
        
    
    ```cpp
    // 특정 색상 영역 분할
    
    int lower_hue = 40, upper_hue = 80;
    Mat src, src_hsv, mask;
    
    void on_hue_changed(int, void*) {
    	// 채도의 범위를 100부터 255로 설정
    	Scalar lowerb(lower_hue, 100, 0);
    	Scalar upperb(upper_hue, 255, 255);
    
    	// 색 성붐 범위가 lowerb와 upperb 사이인 위치의 픽셀만 흰색으로 설정한 mask 영상 생성
    	inRange(src_hsv, lowerb, upperb, mask);
    
    	imshow("mask", mask);
    }
    
    void in_range() {
    	src = imread("candies.png", IMREAD_COLOR);
    
    	if (src.empty()) {
    		cerr << "Image load failed!" << endl;
    		return;
    	}
    
    	// HSV 색 공간으로 변환
    	cvtColor(src, src_hsv, COLOR_BGR2HSV);
    	imshow("src", src);
    
    	// 두 트랙바 생성, 색상의 최댓값을 179로 지정
    	namedWindow("mask");
    	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
    	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
    	on_hue_changed(0, 0);
    
    	waitKey();
    	return;
    }
    ```
    
    ### 히스토그램 역투영
    
    ```cpp
    // 히스토그램 역투영을 이용한 피부색 영역 검출 예제
    void histogram_project() {
    	Mat ref, ref_ycrcb, mask;
    	ref = imread("ref.png", IMREAD_COLOR); // 기존의 사람 영상
    	// 피부에 해당하는 곳만 흰색으로 표시한 마스크
    	mask = imread("mask.bmp", IMREAD_GRAYSCALE);
    	
    	// ycrcb 공간으로 변환
    	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);
    
    	Mat hist;
    	int channels[] = { 1,2 };
    	int cr_bins = 128; int cb_bins = 128;
    	int histSize[] = { cr_bins, cr_bins };
    	float cr_range[] = { 0,256 };
    	float cb_range[] = { 0,256 };
    	const float* ranges[] = { cr_range, cb_range };
    
    	// 피부색 영역의 CrCb 2차원 히스토그램 계산
    	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);
    
    	Mat src, src_ycrcb;
    	src = imread("kids.png", IMREAD_COLOR);
    	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb; // Ycrcb 공간으로 변환
    
    	// 히스토그램 역투영
    	Mat backproj;
    	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);
    
    	imshow("src", src);
    	imshow("backproj", backproj);
    
    	waitKey();
    	return;
    }
    ```
    

# **컬러 영상의 픽셀 값 참조**

OpenCV에서 영상 파일을 불러와 Mat 객체를 생성할 때 imread() 함수를 사용하는데, 이때 두번째 인자를 IMREAD_COLOR로 설정하면 영상을 3채널 컬러 영상 형식으로 불러올 수 있다.

일반적으로 컬러 영상은 흔히 RGB라 불르는 빨간색(R), 초록색(G), 파란색(B) 색상 성분의 조합으로 픽셀 값을 표현한다. 그러나 OpenCV는 RGB가 아닌, **BGR 색상 순서로 픽셀 값을 표현**한다. 즉, imread() 함수로 영상을 3채널 컬러 영상 형식으로 불러오면 각 픽셀의 색상 값이 B, G, R 순서로 저장된 Mat 객체가 생성된다.

컬러 영상에서 각각의 R, G, B 색상 성분은 0부터 255 사이의 값을 가지며, 0이면 색상 성분이 전혀 없는 상태(검정)이고, 255면 해당 색상 성분이 가득 차 있음(흰색)을 의미한다. **각 생상 성분 값은 uchar 자료형**을 사용해 표현하며, 컬러 영상에서 하나의 픽셀은 3개의 색상 성분을 가지고 있으므로, **Vec3b 자료형**을 통해 표현한다. Vec3b 클래스는 크기가 3인 uchar 자료형 배열을 멤버 변수로 갖는 클래스로, 바이트 크기는 정확하게 3바이트며, 이는 실제 3채널 컬러 영상의 한 픽셀이 차지하는 바이트 수와 같다.

컬러 영상에서 픽셀 값을 참조할 때에도 Mat::at() 함수를 사용한다. 이는 템플릿으로 정의된 함수이므로, 3채널 컬러 영상에 대해서는 Vec3b자료형을 명시해야 한다.

아래 예제는 Vec3b 참조형으로 선언된 변수 pixel을 통해 img 영상의 (0,0) 좌표에서 BGR 색상 정보를 가져오고,

포인터 ptr에 컬러 영상의 특정 행 시작 주소를 얻어와 픽셀 값에 접근하여 BGR 색상 성분을 얻어오는 예제이다.

```cpp
Mat src = imread("butterfly.jpg", IMREAD_COLOR);

// 한 픽셀 참조
Vec3b& pixel = img.at<Vec3b>(0,0);// (0,0) 좌표에서 BGR 색상 정보 참조

uchar b1 = pixel[0];// 파란색 성분 값
uchar g1 = pixel[1];// 초록색 성분 값
uchar r1 = pixel[2];// 빨간색 성분 값// 포인터를 이용하기
Vec3b* ptr = img.ptr<Vec3b>(0);

uchar b2 = ptr[0][0];
uchar g2 = ptr[0][1];
uchar g2 = ptr[0][2];
```

컬러 영상의 픽셀 값 참조 방법을 이용해 컬러 영상을 반전하는 예제는 다음과 같다.

```cpp
// 컬러 영상의 픽셀 값 반전void color_inverse() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0;j < src.rows; j++) {
		for (int i = 0;i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

// BGR 값 각각 반전 수행
			p2[0] = 255 - p1[0];// B
			p2[1] = 255 - p1[1];// G
			p2[2] = 255 - p1[2];// R
		}
	}
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
```

3채널 컬러 영상의 각 모든 픽셀의 성분 값을 255에서 빼는 연산을 수행하여 나타나는 결과 영상은 다음과 같다.

src와 dst 영상의 (j, i) 위치 픽셀 값을 각각 Vec3b 자료형 변수 p1와 p2로 참조하여 반전한 방법인데,

다음과 같이 B, G, R 색상 성분의 반전을 Vec3b 클래스에서 지원하는 - 연산자 재정의를 이용해 3채널의 반전 연산을 한꺼번에 수행 가능하다.

```cpp
	for (int j = 0;j < src.rows;j++) {
		for (int i = 0;i < src.cols;i++) {
			dst.at<Vec3b>(j, i) = Vec3b(255, 255, 255) - src.at<Vec3b>(j, i);
		}
	}
```

결과는 다음과 같다.

![https://blog.kakaocdn.net/dn/d20XDN/btrSZzQlNsj/0frT8WbpMkzwzAkiBVgTFK/img.png](https://blog.kakaocdn.net/dn/d20XDN/btrSZzQlNsj/0frT8WbpMkzwzAkiBVgTFK/img.png)

위에서는 컬러 영상의 픽셀 값 참조 방법을 설명하기 위해 각 픽셀 위치에 접근하여 반전 연산을 수행하도록 구현했지만, 실전에서는 다음과 같이 Mat 클래스에 정의된 - 연산자 재정의 함수를 이용하면 매우 쉽게 구현이 가능하다.

```cpp
Mat dst = Scalar(255, 255, 255) - src;
```

---

# **색 공간 변환**

컴퓨터에서는 빛의 삼원색인 빨강(R), 초록(G), 파랑(B) 성분의 조합으로 색을 표현하는데, OpenCV 에서 컬러 영상을 Mat 객체에 저장할 때에는 파란, 녹색, 빨강의 순서로 색 정보를 저장하여 BGR 을 표현하게 된다.

이렇게 3가지 색 성분의 조합으로 색을 표현하는 방식을 RGB 색 모델, RGB 색 공간 (color sapce) 표현이라고 한다.

그러나 컬러 영상 처리 관점에서는, RGB 색 공간보다, 색상 구분이 용이한 HSV, HSL 색 공간을 사용하거나, 휘도 성분이 구분되어 있는 YCrCb, YUV 등의 색 공간을 사용하는 것이 유리하다. 따라서 OpenCV는 BGR 순서로 색상이 저장된 컬러 영상의 색 공간을 HSV, YCrCb 등 다른 색 공간으로 변환하는 인터페이스를 제공한다.

### **cvtColor() 함수**

우선 OpenCV는 색 공간을 다른 색 공간으로 변환하는 cvtColor() 함수를 제공한다.

![https://blog.kakaocdn.net/dn/bkicXL/btrSZyYfLOD/WbjCkWGJIw5EjtbdocsPj1/img.png](https://blog.kakaocdn.net/dn/bkicXL/btrSZyYfLOD/WbjCkWGJIw5EjtbdocsPj1/img.png)

위 함수는 입력 영상 src의 색 공간을 변환하여 결과 영상 dst를 생성하여 반환한다. code 인자에 CololrConversionCodes 열거형 상수를 지정하여 어떻게 색 공간을 변환할지 결정하게 된다.

![https://blog.kakaocdn.net/dn/p31mu/btrSZZ8Tw0S/d26IQFmeqz2SdQMUNezWlk/img.png](https://blog.kakaocdn.net/dn/p31mu/btrSZZ8Tw0S/d26IQFmeqz2SdQMUNezWlk/img.png)

그 중 사용성이 높은 몇 가지 색 공간 변환에 대해 알아보자.

**BGR2GRAY, GRAY2BGR**

BGR2GRAY 색 공간 변환 코드는 **BGR** 컬러 영상을 그레이스케일 영상으로 변환할 때 사용한다. 그레이스케일 영상으로 변환하는 주된 이유는 연삭 속도와 메모리 사용량을 줄이기 위함이다. 기본적으로 컬러 영상은 3채널 영상으로, 3배 많은 메모리를 필요로 하고 더 많은 연산 시간을 필요로 한다. 따라서 색상 정보의 활용도가 그리 높지 않은 경우 입력 영상을 그레이 스케일 영상으로 변환하여 처리하는 것이 효율적이다.

BGR 3채널 컬러 영상을 그레이스케일 영상으로 변환할 때는 다음 공식이 사용된다.

![https://blog.kakaocdn.net/dn/cMsgLS/btrSZKD6356/ql4t8maAyC06ExsvWg93p0/img.png](https://blog.kakaocdn.net/dn/cMsgLS/btrSZKD6356/ql4t8maAyC06ExsvWg93p0/img.png)

반대로 GRAY2BGR 색 공간 변환 코드는 그레이 스케일 영상을 BGR 컬러 영상으로 변환할 때 사용한다. 이 때 결과 영상은 CV_8UC3 타입으로 결정되고, BGR 색상 성분 값은 다음과 같이 결정된다.

![https://blog.kakaocdn.net/dn/YSXxO/btrS1LBMypu/jSWy5Zgr8PQdqKI3b3xDz0/img.png](https://blog.kakaocdn.net/dn/YSXxO/btrS1LBMypu/jSWy5Zgr8PQdqKI3b3xDz0/img.png)

주로 그레이스케일 영상 위에 색깔이 있는 선, 글씨를 나타내는 경우 미리 그레이스케일 영상을 BGR 컬러 영상으로 변환이 필요하다.

**BGR2HSV, HSV2BGR**

HSV 모델은 색상(hue), 채도(saturation), 명도(value)로 색을 표현하는 방식이다.

**색상**은 빨강, 노랑, 녹색과 같은 색의 종류를, **채도**는 색의 순도를 나타낸다. 즉 채도가 높은 경우 맑은 색을, 낮은 경우 탁한 색을 띄게 된다.

**명도**는 빛의 세기로, 명도가 높으면 밝고, 낮으면 어둡게 느껴진다.

HSV 색 공간은 다음과 같이 원뿔 모양으로 표현이 가능하다.

HSV 색 공간 모형에서 색상은 원뿔을 가로로 잘랐을 대 나타나는 원형에서 각도로 정의된다. 각도가 낮을 수록 빨간색을, 각도가 증가할 수록 노란, 녹색, 하늘, 파랑, 보라색을 거쳐 각도가 360도에 가까워지면 다시 빨간색으로 표현된다.

채도는 원뿔을 가로로 잘랐을 때 나타나는 원 모양의 중심에서 최솟값을, 원의 중심에서 방사형으로 멀어지는 방향으로 값이 증가한다.

명도는 원뿔 아래쪽 꼭짓점에서 최솟값을, 원뿔의 축을 따라 올라가서 증가한다.

![https://blog.kakaocdn.net/dn/DrRZA/btrSZm4AxO4/xvILs1J2c59B05nOlNQ760/img.png](https://blog.kakaocdn.net/dn/DrRZA/btrSZm4AxO4/xvILs1J2c59B05nOlNQ760/img.png)

BGR2HSV 색 공간 변환 코드 사용 시, 8비트 BGR 영상을 HSV 영상으로 변환하게 되는데, H 값은 0~179 사이의 정수, S와 V는 0~255 사이의 정수로 표현된다. OpenCV 에서 각도는 2로 나눈 값을 H 성분으로 저장한다. (360도 각도로 표현하지만 uchar 자료형으로는 256 이상의 정수를 표현할 수 없기 때문)

**BGR2YCrCb, YCrCb2BGR**

YCrCb 색 공간에서 Y 성분을 밝기 또는 **휘도(lumincance)** 정보를, Cr과 Cb 성분은 색상 또는 색차 (chrominacne) 정보를 나타낸다. RGB 색상 성분으로부터 Y 성분을 계산하는 공식은 그레이스케일 계산 공식과 똑같고, Cr과 Cb 성분은 밝기가 아닌 오직 색상에 대한 정보만을 갖는다. 따라서 YCrCb 색 공간은 영상을 그레이스케일 정보와 색상 정보로 분리하여 처리할 때 매우 유용하다.

Y, Cr, Cb 각 성분은 0~255 사이의 값으로 표현되고, cvtColor() 함수 입력 영상이 0에서 1 사이 값으로 정규화된 CV_32FC3 타입의 행렬이라면, 각각 0과 1 사이의 실수 값으로 표현된다.

Y 성분을 128로 고정한 상태에서 Cr과 Cb 값에 따른 색상 표현을 그림오르 나타내면 다음과 같다.

HSV 색 공간에서는 H 값만을 이용해 색 종류를 구분할 수 있었지만, YCrCb 색 공간에서는 Cr과 Cb를 함께 조합하여 색을 구분할 수 있다.

![https://blog.kakaocdn.net/dn/bYE0S9/btrSZYB8Ie7/UkOM8sYwb9aTWG5cNaZb8K/img.png](https://blog.kakaocdn.net/dn/bYE0S9/btrSZYB8Ie7/UkOM8sYwb9aTWG5cNaZb8K/img.png)

다음 코드로 간단히 그레이스케일 영상으로 변환해보자.

컬러 영상을 불러올 때 두번째 인자를 지정하지 않으면 기본적으로 3채널 BGR 컬러 영상 형식으로 불러오게 된다.

이후 cvtColor() 함수를 이용해 컬러 영상을 그레이스케일 영상으로 변환하여 dst 영상을 저장하게 된다.

```cpp
Mat src = imread("butterfly.jpg");

/*

*/

Mat dst;
cvtColor(src, dst, COLOR_BGR2GRAY);
```

---

## **색상 채널 나누기**

imread() 함수로 생성된 컬러 영상은 하나의 픽셀이 B,G,R 3개의 색상 정보를 가지고 있으며, 보통 uchar 자료형을 사용하여 3개의 채널을 갖는 Mat 객체로 표현한다. 컬러 영상을 다루다 보면, 빨간색 성분만을 이용하거나 HSV 색 공간으로 변환 후 H 성분만을 이용하게 되는 경우가 종종 발생하는데, 이러한 경우 3채널 Mat 객체를 1채널 Mat 객체 3개로 분리해 다루는 것이 효율적이다.

### **split(), merge() 함수**

다채널 행렬을 1채널 행렬 여러 개로 변환할 때는 split() 함수를, 다시 1채널 행렬을 여러 개로 합쳐 다채널 행렬 하나를 생성할 때는 merge() 함수를 사용한다.

![https://blog.kakaocdn.net/dn/b00sie/btrSZ2YMp8j/ndVHgYaJzftMQ44oBjCufK/img.png](https://blog.kakaocdn.net/dn/b00sie/btrSZ2YMp8j/ndVHgYaJzftMQ44oBjCufK/img.png)

분할된 결과는 Mat 자료형의 배열(포인터), 또는 vector<Mat> 형식의 변수로 받을 수 있다. 배열을 사용할 경우 배열의 크기가 입력 영상의 채널 수보다 같거나 커야 한다.

![https://blog.kakaocdn.net/dn/w7IGr/btrSZTnvoZF/ldTelVzGWAVtgpo9ZO2ok0/img.png](https://blog.kakaocdn.net/dn/w7IGr/btrSZTnvoZF/ldTelVzGWAVtgpo9ZO2ok0/img.png)

다음 예제를 통해 컬러 영상을 각 B,G,R 채널로 분리해보자

```cpp
// BGR 컬러 영상의 채널을 각각 나누기void color_split() {
	Mat src = imread("candies.png");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<Mat> bgr_planes;
	split(src, bgr_planes);// src 입력 영상을 bgr_planes 벡터에 각 채널을 분리imshow("src", src);
// 각 성분에 대한 값이 큰 경우 밝은 흰색으로 표현imshow("B_plane", bgr_planes[0]);// B 색상imshow("G_plane", bgr_planes[1]);// G 색상imshow("R_plane", bgr_planes[2]);// R 색상waitKey();
	destroyAllWindows();
}
```

candies src 영상을 vector 자료형인 bgr_planes에 저장하였고, 각 채널 영상을 결과로 나타내면 다음과 같다.

각 색상 성분이 많이 포함되어 있는 경우 255에 가까운 밝은 흰색 성분으로 나타나는 것을 확인할 수 있다.

![https://blog.kakaocdn.net/dn/pQd0a/btrS0ekrbKM/7xyQ6UBVjAjDp1n0E9HNdK/img.png](https://blog.kakaocdn.net/dn/pQd0a/btrS0ekrbKM/7xyQ6UBVjAjDp1n0E9HNdK/img.png)

간단히 RGB 색 공간에서 색상 채널을 나누는 예제를 살펴보았다.

하지만 컬러 영상을 다루는 경우 RGB 색 공간보다는 HSV, YCrCb 등 색 공간에서 채널을 나누어 색 정보를 다루는 경우가 많다. 다음 글을 통해 HSV, YCrCb 색 공간에서 색상 평면을 나누거나 합치는 방법을 알아보도록 하자.

영상의 색상 정보를 이용해 영상을 처리하는 기법에 대해 알아보자.

영상의 명암비를 높이는 컬러 히스토그램 평활화 기법, 그리고 컬러 영상에서 원하는 색상 영역을 검출하는 방법에 대해 알아보자.

# **컬러 히스토그램 평활화**

그레이스케일 영상에서 활용한 equalizeHist() 함수를 통해 히스토그램 평활화를 수행했다. **3**채널 컬러 영상에 대해 히스토그램 평활화를 수행하기 위해서는, RGB 3개의 채널에 대해 각각 평활화를 수행하는 것이 아니라, YCrCb 색 공간으로 변환하고, Y 성분에 대해서만 히스토그램 평활화를 수행해야 한다.

만약 다음과 같이 RGB 각 채널에 히스토그램 평활화를 수행하면 어떻게 될까?

이 방식으로 각 채널마다 서로 다른 형태의 명암비 변환 함수를 사용하면, 원본 영상과 다른 색상의 결과 영상이 만들어진다. 아래 오른쪽 그림과 같이 녹색 성분이 많이 포함되어 있는 영상에 히스토그램 평활화 수행을 한 후 다시 채널을 합쳐 만들게 되면 원본 영상의 색감과 완전히 다른 결과 영상이 만들어진다.

<img src="https://blog.kakaocdn.net/dn/bKZWPh/btrS1RosGW5/khbFeobTHrzg00EpFtwcyk/img.png" width=500>

<img src="https://blog.kakaocdn.net/dn/ceG1DE/btrSXq0EzND/4kIIhm5ClOlqQCyCgSBEnK/img.png" width=500>


따라서 컬러 영상의 색감은 변경하지 않고, 명암비를 높이고자 하는 경우 영상의 밝기 정보만을 사용해야 한다.

따라서 보통 히스토그램 평활화 수행 시, 입력 영상을 밝기 정보와 색상 정보로 분리한 후, 밝기 정보에 대해서만 히스토그램 평활화를 수행한다. 예를 들어 YCrCb 색공간을 사용하는 경우, Y 성분에 대해서만 히스토그램 평활화를 수행하고, 변경된 Y 채널과 나머지 채널을 다시 합쳐 결과를 도출한다.

결국 색상 정보는 전혀 변경하지 않아 입력 영상의 색감이 그대로 유지되고, 오직 밝기 성분에 대해서만 명암비가 증가학 ㅔ된다.

<img src="https://blog.kakaocdn.net/dn/bkTR3G/btrS1Kv8l87/qp5TKnVhgKWmKIzdHE3Pl0/img.png" width=500>


다음 예제를 살펴 보자.

```cpp
// 컬러 영상의 히스토그램 평활화void color_histogram() {
	Mat src = imread("pepper.bmp", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);// YCrCb 색 공간으로 변경

	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);// 채널 분리// Y 성분(명암비)에 해당하는 영상만 히스토그램 평활화 수행equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);

// 세 채널에 대한 영상 다시 합치기
	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);

	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);// BGR 색 공간으로 다시 변환imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return;
}
```

우선 BGR 색 공간의 평면 pepper src 영상에 대하여, YCrCB 색 공간으로 변환을 수행한다.

이후 채널을 분리한 영상의 0번 값인, Y 성분(brightness, 밝기 성분)에 해당하는 영상에 대해서만 equalizeHist() 함수를 통해 히스토그램 평활화를 수행하고, 세 채널 영상을 다시 합쳐 BGR 색 공간으로 변환하고 결과를 출력하게 된다.

결과는 다음과 같다. 색감은 그대로 유지한채, 밝기에 대한 히스토그램 평활화가 이루어져 명암비가 높아지며 조금 더 뚜렷한 영상이 나타난 것을 확인할 수 있다. 히스토그램 평활화를 통해 어두운 부분은 더욱 어두워졌으며, 밝은 부분은 더욱 밝아진 것이 확실하게 나타난다.

![https://blog.kakaocdn.net/dn/dExnKA/btrSXqsQcIA/TiDZAFKSwVmZS49eNAAJwk/img.png](https://blog.kakaocdn.net/dn/dExnKA/btrSXqsQcIA/TiDZAFKSwVmZS49eNAAJwk/img.png)

---

## **색상 범위 지정에 의한 영역 분할**

컬러 영상을 다룰 때 특정 색상 영역을 추출하는 작업이 많이 요구되기도 한다. 예를 들어 입력 영상에서 빨간색 픽셀을 모두 찾아내면 빨간색 객체의 위치와 크기를 알아낼 수 있다. 컬러 영상에서 대표적인 색상 영역을 구분하고자 할 때는 색상 정보가 따로 설정되어 있는 HSV 공간을 사용하는 것이 유리하다.

### **inRange() 함수**

OpenCV 에서 행렬의 원소값이 특정 범위 안에 있는지 확인하기 위해 inRange() 함수를 사용한다.

<img src="https://blog.kakaocdn.net/dn/bgLy3w/btrS1P5gsb6/0mND25os6KvWr41aU7POOk/img.png" width=500>

inRange() 는 입력 영상 src의 픽셀 값이 지정한 밝기 또는 색상 범위에 포함되어 있으면 흰색, 그렇지 않으면 검은색으로 채워진 마스크 영상 dst를 반환한다.

만약 그레이스케일 영상을 입력으로 사용하는 경우, 특정 밝기 값 범위에 있는 픽셀 영역을 추출할 수도 있다. 1채널 영상에 대해 inRange() 함수의 동작을 수식으로 표현하면 다음과 같다.

![https://blog.kakaocdn.net/dn/qSfkP/btrS1Qpym5L/2mt8P7RV9n0OcPvxVc6zI0/img.png](https://blog.kakaocdn.net/dn/qSfkP/btrS1Qpym5L/2mt8P7RV9n0OcPvxVc6zI0/img.png)

입력 영상의 채널이 2개 이상이라면, 각 채널 값이 모두 지정된 범위를 만족할 때 dst 영상의 픽셀 값이 255로 설정된다.

여기서 lowerp와 upperb 인자에는 Mat 객체 또는 Scalar 객체를 지정할 수도 있다. 만약 Mat 객체를 지정하는 경우, src 의 모든 픽셀에 각기 다른 하한 값과 상한 값을 지정할 수 있다. Scalar 또는 int, double 과 같은 기본 자료형을 지정하는 경우, src 모든 픽셀에 동일한 하한, 상한 값이 적용된다.

다음 예제를 살펴보자.

예제는 영상 출력 창에 두 개의 트랙바를 붙여서 사용자가 HSV 색 공간에서 색상의 하한값과 상한 값을 조절하여, 사용자가 설정한 색상 값 범위에 해당하는 영역을 흰색, 그 외의 영역은 검은색으로 표현된 마스크 영상을 화면에 출력하게 된다.

inRange() 함수의 lowerb, upperb 인자에는 Scalar 값을 지정하였는데, 이를 이용하여 색상의 하한과 상한 값, 채도와 명도의 범위르 지정하였다.

```cpp
// 특정 색상 영역 분할int lower_hue = 40, upper_hue = 80;// upperb, lowerb의 default 값 설정
Mat src, src_hsv, mask;

void on_hue_changed(int, void*) {
// 채도의 범위를 100부터 255로 설정, 명도는 0부터 255까지 설정Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);

// 색 성분 범위가 lowerb와 upperb 사이인 위치의 픽셀만 흰색으로 설정한 mask 영상 생성inRange(src_hsv, lowerb, upperb, mask);

	imshow("mask", mask);
}

void in_range() {
	src = imread("candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

// HSV 색 공간으로 변환cvtColor(src, src_hsv, COLOR_BGR2HSV);
	imshow("src", src);

// 상한, 하한 값을 조정하는 두 트랙바 생성, 색상의 최댓값을 179로 지정namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	on_hue_changed(0, 0);// 트랙바 콜백 함수 강제 호출waitKey();
	return;
}
```

결과는 다음과 같이 나타난다.

![https://blog.kakaocdn.net/dn/czwNlG/btrS1LaLlEM/ymoX8iQCHrYyeFCszvyZek/img.png](https://blog.kakaocdn.net/dn/czwNlG/btrS1LaLlEM/ymoX8iQCHrYyeFCszvyZek/img.png)

다음은 색상H의 범위가 42~82 (Green), 채도 S 의 범위가 100~255, 명도 V의 범위가 9~255 사이인 픽셀 위치를 찾은 결과이다.

H 값이 60 근방이면 녹색을 나타낸다. 채도 값이 100보다 큰 픽셀만 찾은 것은 충분히 선명한 녹색만 찾기 위함이다. 명도 범위를 0~255 사이로 지정한 것은 명도의 값은 상관하지 않겠다는 의미이다.

두번째와 같이 100~140 사이의 H 색상을 지정한 경우 120 근방의 값을 갖는 파란색 성분만 흰색으로 표현이 된다.

<img src="https://blog.kakaocdn.net/dn/lZzAn/btrS0fp6YHk/kU1yYhyiRx25hDoGyykkJk/img.png" width=500>


<img src="https://blog.kakaocdn.net/dn/cS8ea7/btrSW598Jwd/07ey1Dn5f4oAgPDNnK57yK/img.png" width=500>


---

<br>

# **히스토그램 역투영**

위에서 설명한 inRange() 함수를 사용하여 특정 색상 영역을 검출하는 경우, 빨강, 노랑, 파랑 등 원색에 가까운 색상을 찾기에는 효과적이다. 그러나 사람의 피부색(살구색)과 같은 경우 미세한 변화가 있거나 색상 값을 수치적으로 지정하기 어려운 경우에는 적합하지 않은 방법이다.

**히스토그램 역투영 (Historgram Backprojection)** 이란, 입력 영상에서 찾고자 하는 객체의 기준 영상을 미리 가지고 있는 경우 컬러 히스토그램 정보를 이용하여 주어진 입력 영상에서 해당 히스토그램 모델과 일치하는 픽셀을 찾아내는 기법이다.

### **calcBackProject() 함수**

히스토그램 역투영은 calcBackProject() 함수를 이용하여 수행할 수 있다.

<img src="https://blog.kakaocdn.net/dn/b3BA8l/btrSZ2LgJiN/ggLKXVwyeaWpciV1CAwpnK/img.png" width=500>


<br>

위 함수는 입력 영상 images에서 히스토그램 hist 를 따르는 픽셀을 찾고, 그 정보를 backProject 영상으로 반환한다.

이 때 사용하는 히스토그램 행렬은 calcHist() 함수로 구하게 된다.

이를 이용해 입력 영상에서 피부색 영역을 추출하는 예제를 살펴보자.

```cpp
// 히스토그램 역투영을 이용한 피부색 영역 검출 예제void histogram_project() {
	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR);// 기존의 사람 영상
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);// 피부에 해당하는 곳만 흰색으로 표시한 마스크

// ycrcb 공간으로 변환cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	Mat hist;
	int channels[] = { 1,2 };
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins, cr_bins };
	float cr_range[] = { 0,256 };
	float cb_range[] = { 0,256 };
	const float* ranges[] = { cr_range, cb_range };

// 피부색 영역의 CrCb 2차원 히스토그램 계산하여 출력 영상을 hist에 저장calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

/* 히스토그램 역투영을 입력 영상에 적용 */

	Mat src, src_ycrcb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);// Ycrcb 공간으로 변환// 히스토그램 역투영
	Mat backproj;
// 입력 영상 hist 히스토그램을 이용하여 입력 영상에 대한 역투영 수행하여 backProject 출력 영상에 저장calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

	imshow("reference", ref);// 원본 아이 영상 (히스토그램 도출을 위한 기준 영상)imshow("mask", mask);// 피부색에 해당하는 곳만 흰색 영역으로 나타낸 마스크 영상imshow("src", src);// 두 아이 영상imshow("backproj", backproj);// 히스토그램 역투영 결과 영상waitKey();
	return;
}
```

위 예제는 피부색이 포함된 아이의 영상을, 피부색이 나타난 영역만 흰색으로 표시한 마스크 영상을 이용해 기준 영상에서 피부색 영역의 CrCb 히스토그램을 구하고, 그 결과를 콘솔에 출력하였다. 이는 CrCb 평면에서 피부색을 표현하는 영역이 가운데에서 좌측 하단 부분에 나타난 것 을 확인할 수 있다.

이후 두 아이가 담긴 src 영상에 대하여, hist 히스토그램을 역투영을 수행하였다. backproj 영상에서 밝은 회색, 흰색으로 표시된 영역은 입력 영상의 픽셀 값이 지정한 히스토그램 hist에서 높은 빈도수로 표현된 것이다. 검은색으로 나타난 부분은 해당 픽셀 값이 히스토그램에서 빈도수가 낮거나 0임을 의미한다.