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
			auto mat = reinterpret_cast<const cv::Mat*>(ptr.ToPointer());
			return ToBitmapSource(mat);
		}

		static BitmapSource^ ToBitmapSource(System::IntPtr left, System::IntPtr right) {
			auto matL = reinterpret_cast<const cv::Mat*>(left.ToPointer());
			auto matR = reinterpret_cast<const cv::Mat*>(right.ToPointer());

			cv::Mat mat;
			cv::hconcat(*matL, *matR, mat);

			return ToBitmapSource(&mat);
		}

		static void drawRectangle(cv::Mat* mat, cv::Rect rect) {
			cv::rectangle(*mat,
				cv::Point(rect.x, rect.y),
				cv::Point(rect.x + rect.width, rect.y + rect.height),
				cv::Scalar(0, 200, 0), 3, CV_AA);
		}

	};
}
