using OpenCvSharp;
using OpenCvSharp.Extensions;
using Prism.Mvvm;
using System;
using System.Windows.Media.Imaging;

// OpenCvSharp を使ってカメラキャプチャをする http://www.moonmile.net/blog/archives/6258

namespace PrismWpf.MainModule.Models
{
    class VideoProvider : BindableBase, IDisposable
    {
        private VideoCapture videoCapture;

        // View表示用の最新フレーム画像
        private BitmapSource _FrameLatest;
        public BitmapSource FrameLatest
        {
            get => _FrameLatest;
            private set => SetProperty(ref _FrameLatest, value);
        }

        public VideoProvider() { }

        public void Initialize()
        {
            videoCapture = new VideoCapture();
            videoCapture.Open(0);

            if (!videoCapture.IsOpened())
                throw new Exception("Video Initialization Failed");
        }

        /// <summary>
        /// カメラからフレームを取得する
        /// </summary>
        /// <returns>カメラの生画像</returns>
        public void CaptureRawFrame()
        {
            using (var mat = GetRawMat())
            {
                if (mat != null)
                {
                    var bitmap = mat.ToBitmapSource();
                    bitmap.Freeze();
                    FrameLatest = bitmap;
                }
            }
        }

        /// <summary>
        /// カメラからフレームを取得して返す
        /// </summary>
        /// <returns>カメラの生画像</returns>
        //public BitmapSource GetRawBitmapSource()
        //{
        //    BitmapSource bitmap = null;
        //    using (var mat = GetRawMat())
        //    {
        //        if (mat != null)
        //        {
        //            bitmap = mat.ToBitmapSource();
        //            bitmap.Freeze();
        //        }
        //    }
        //    return bitmap;
        //}

        /// <summary>
        /// カメラからフレームを取得して返す
        /// </summary>
        /// <returns>生のMat</returns>
        private Mat GetRawMat()
        {
            if (videoCapture == null) return null;

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
