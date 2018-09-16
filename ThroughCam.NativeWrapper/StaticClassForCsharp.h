#pragma once
#pragma unmanaged
#include <opencv2/opencv.hpp>
#pragma managed

// BitmapSource‘Î‰ž
// ŽQÆ‚É’Ç‰ÁF"PresentationCore", "WindowsBase"
using namespace System::Windows::Media::Imaging;

namespace ThroughCamVideoCaptureWrapper {

	public ref class StaticClassForCsharp abstract sealed
	{
	private:
		static const double dpi = 96.0;

	public:
		static BitmapSource^ ToBitmapSource(const cv::Mat* img) {
			int widht = img->cols;
			int height = img->rows;
			int stride = img->step;
			int size = stride * height;
			double dpiX = dpi;
			double dpiY = dpi;

			uchar *c = new uchar[size];
			System::IntPtr ip(c);
			memcpy(ip.ToPointer(), img->data, size);

			auto bitmapSource = BitmapSource::Create(
				widht, height, dpiX, dpiY,
				System::Windows::Media::PixelFormats::Bgr24, nullptr,
				ip, size, stride);
			bitmapSource->Freeze();

			delete c;
			return bitmapSource;
		}

		static BitmapSource^ ToBitmapSource(System::IntPtr ptr) {
			auto img = reinterpret_cast<const cv::Mat*>(ptr.ToPointer());
			return ToBitmapSource(img);
		}
	};
}
