using OpenCvSharp;
using OpenCvSharp.Extensions;
using System;
using System.Windows.Media.Imaging;

// http://www.moonmile.net/blog/archives/6258

namespace PrismWpf.MainModule.Models
{
    class VideoProvider : IDisposable
    {
        private VideoCapture videoCapture;

        public VideoProvider() { }

        public void Initialize()
        {
            videoCapture = new VideoCapture();
            videoCapture.Open(0);

            if (!videoCapture.IsOpened())
                throw new Exception("Video Initialization Failed");
        }

        /// <summary>
        /// カメラからフレームを取得して返す
        /// </summary>
        /// <returns>カメラの生画像</returns>
        public BitmapSource GetRawBitmapSource()
        {
            BitmapSource bitmap = null;
            using (var mat = GetRawMat())
            {
                if (mat != null)
                {
                    bitmap = mat.ToBitmapSource();
                    bitmap.Freeze();
                }
            }
            return bitmap;
        }

        /// <summary>
        /// カメラからフレームを取得して返す
        /// </summary>
        /// <returns>生のMat</returns>
        public Mat GetRawMat()
        {
            var frame = new Mat();

            videoCapture.Read(frame);

            return frame.Empty() ? null : frame;
        }

        public void Dispose()
        {
            videoCapture?.Dispose();
        }
    }
}
