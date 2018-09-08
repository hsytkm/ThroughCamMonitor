#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

class MyVideoCapture {
private:
	int x;

public:
	MyVideoCapture() {}
	~MyVideoCapture() {}

	int ShowVideo() {

		//デバイスのオープン
		cv::VideoCapture cap(0);	// cap.open(0); こっちでも良いらしい

		// デバイスの接続確認
		if (!cap.isOpened()) return -1;

		while (1)
		{
			cv::Mat frame;
			cap >> frame;

			cv::imshow("window", frame);

#if true
			int key = cv::waitKey(1);
			if (key == 113)
				break;							// qボタン押下でループ抜け
			else if (key == 115)
				cv::imwrite("img.png", frame);	// sボタン押下でフレーム画像を保存
#endif
		}

		cv::destroyAllWindows();
		return 0;
	}

	int GetVideoImage() {

		//デバイスのオープン
		cv::VideoCapture cap(0);	// cap.open(0); こっちでも良いらしい

		// デバイスの接続確認
		if (!cap.isOpened()) return -1;

		cv::Mat frame;
		cap >> frame;
		return 0;
	}

};
