#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

class MyVideoCapture {
private:
	int deviceId = 0;

	cv::VideoCapture* videoCapture = nullptr;
	cv::Mat frameLatest;
		
public:
	MyVideoCapture() {}
	~MyVideoCapture() {
		delete videoCapture;
		videoCapture = nullptr;
	}

#if 0	// 思い出保存
	int ShowVideo() {
		cv::VideoCapture cap(0);	// cap.open(0); こっちでも良いらしい
		if (!cap.isOpened()) return -1;
		while (1)
		{
			cv::Mat frame;
			cap >> frame;
			cv::imshow("window", frame);
			int key = cv::waitKey(1);
			if (key == 113)
				break;							// qボタン押下でループ抜け
			else if (key == 115)
				cv::imwrite("img.png", frame);	// sボタン押下でフレーム画像を保存
		}
		cv::destroyAllWindows();
		return 0;
	}
#endif

	// 初期化
	void Initialize() {
		videoCapture = new cv::VideoCapture(deviceId);

		// デバイスの接続確認
		if (!videoCapture->isOpened()) {
			videoCapture = nullptr;
		}
	}

	// 最新フレームを取得
	cv::Mat* GetVideoFrame() {
		if (videoCapture == nullptr || !videoCapture->isOpened())
			return nullptr;

		*videoCapture >> frameLatest;

		if (frameLatest.empty()) {
			return nullptr;
		}

		return &frameLatest;
	}

};
