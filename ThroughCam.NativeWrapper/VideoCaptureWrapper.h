#pragma once
#pragma unmanaged
#include "MyVideoCapture.h"
#pragma managed

using namespace System;

namespace ThroughCamVideoCaptureWrapper {
	public ref class VideoCaptureWrapper
	{
	private:
		bool isResponsible;
		MyVideoCapture *p;

	public:
		VideoCaptureWrapper() : isResponsible{ true }, p{ new MyVideoCapture() } {}
		//VideoCaptureWrapper(MyVideoCapture^ obj) : isResponsible{ true }, p{ new MyVideoCapture(obj->p) } {}
		//VideoCaptureWrapper(MyVideoCapture *p) : isResponsible { false }, p{ p } {}

		// マネージド及びアンマネージドリソースの解放
		~VideoCaptureWrapper() { this->!VideoCaptureWrapper(); }

		// アンマネージドリソースの解放
		!VideoCaptureWrapper()
		{
			if (isResponsible && p)
			{
				delete p;
				p = nullptr;
			}
		}

		void Initialize() {
			p->Initialize();
		}

		System::IntPtr GetVideoFrame() {
			cv::Mat* ptr = p->GetVideoFrame();
			return System::IntPtr(ptr);
		}

#if 0	// がんばったけど分からなかった版(別途実装できたので、これは思い出保存)
		int safeLongToInt(long l) {
			if (l < INT_MIN || l > INT_MAX) {
				throw gcnew System::ArgumentException("cannot be cast to int without changing its value.");
			}
			return (int)l;
		}

		BitmapImage^ ToBitmapImage(System::IntPtr ptr) {
			cv::Mat* img = reinterpret_cast<cv::Mat*>(ptr.ToPointer());

			//auto imageInBytes = new System::Byte[safeLongToInt(src->total()) * src->channels()];
			//auto imageInByte2 = gcnew array<Byte>(safeLongToInt(img->total()) * img->channels());

			uchar *c = new uchar[img->step*img->rows];
			System::IntPtr ip(c);
			memcpy(ip.ToPointer(), img->data, img->step*img->rows);

			//src->data;
			//src->data->put(0, 0, imageInByte2);

			//auto ms = gcnew System::IO::MemoryStream((unsigned char*)c);

			BitmapImage^ bitmap = gcnew BitmapImage();

			bitmap->BeginInit();
			//bitmap->StreamSource = ms;
			bitmap->EndInit();
			//bool b = bitmap->CanFreeze;
			//bitmap->Freeze();

			//delete[] imageInByte2;

			return nullptr;
		}
#endif

#if 0	// 動作するけど、System::Drawing::Bitmapは使わないので不要
		System::Drawing::Bitmap^ GetBitmap(System::IntPtr ptr) {
			cv::Mat* img = reinterpret_cast<cv::Mat*>(ptr.ToPointer());
			uchar *c = new uchar[img->step*img->rows];
			System::IntPtr ip(c);
			memcpy(ip.ToPointer(), img->data, img->step*img->rows);

			System::Drawing::Bitmap^ bmp = gcnew System::Drawing::Bitmap(
				img->cols, img->rows, img->step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb,
				ip);

			delete c;
			return bmp;
		}
#endif

#if 0	// マネージ→アンマネージ
		void test() {
			array<Byte>^ managedText = gcnew array<Byte>(6);
			managedText[0] = 'H';
			managedText[1] = 'e';
			managedText[2] = 'l';
			managedText[3] = 'l';
			managedText[4] = 'o';
			managedText[5] = '\0';
			pin_ptr<Byte> pinnedText = &managedText[0];
		}
#endif

	};
}
