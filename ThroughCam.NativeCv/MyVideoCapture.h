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

		//�f�o�C�X�̃I�[�v��
		cv::VideoCapture cap(0);	// cap.open(0); �������ł��ǂ��炵��

		// �f�o�C�X�̐ڑ��m�F
		if (!cap.isOpened()) return -1;

		while (1)
		{
			cv::Mat frame;
			cap >> frame;

			cv::imshow("window", frame);

#if true
			int key = cv::waitKey(1);
			if (key == 113)
				break;							// q�{�^�������Ń��[�v����
			else if (key == 115)
				cv::imwrite("img.png", frame);	// s�{�^�������Ńt���[���摜��ۑ�
#endif
		}

		cv::destroyAllWindows();
		return 0;
	}

	int GetVideoImage() {

		//�f�o�C�X�̃I�[�v��
		cv::VideoCapture cap(0);	// cap.open(0); �������ł��ǂ��炵��

		// �f�o�C�X�̐ڑ��m�F
		if (!cap.isOpened()) return -1;

		cv::Mat frame;
		cap >> frame;
		return 0;
	}

};
