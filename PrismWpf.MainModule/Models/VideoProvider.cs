using OpenCvSharp;
using OpenCvSharp.Extensions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
        public BitmapSource GetVideoFrame()
        {
            BitmapSource bitmap = null;
            using (var frame = new Mat())
            {
                videoCapture.Read(frame);

                if (!frame.Empty())
                {
                    bitmap = frame.ToBitmapSource();
                    bitmap.Freeze();
                }
            }
            return bitmap;
        }

        public void Dispose()
        {
            videoCapture?.Dispose();
        }
    }
}
