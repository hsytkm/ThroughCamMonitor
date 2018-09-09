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

#if 0	// �v���o�ۑ�
	int ShowVideo() {
		cv::VideoCapture cap(0);	// cap.open(0); �������ł��ǂ��炵��
		if (!cap.isOpened()) return -1;
		while (1)
		{
			cv::Mat frame;
			cap >> frame;
			cv::imshow("window", frame);
			int key = cv::waitKey(1);
			if (key == 113)
				break;							// q�{�^�������Ń��[�v����
			else if (key == 115)
				cv::imwrite("img.png", frame);	// s�{�^�������Ńt���[���摜��ۑ�
		}
		cv::destroyAllWindows();
		return 0;
	}
#endif

	// ������
	void Initialize() {
		videoCapture = new cv::VideoCapture(deviceId);

		// �f�o�C�X�̐ڑ��m�F
		if (!videoCapture->isOpened()) {
			videoCapture = nullptr;
		}
	}

	// �ŐV�t���[�����擾
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
