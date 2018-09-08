using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace PrismWpf.MainModule.Models
{
    class VideoStreamManager : IDisposable
    {
        private VideoProvider videoProvider;

        public VideoStreamManager()
        {
            videoProvider = new VideoProvider();
        }

        public void Dispose()
        {
            videoProvider?.Dispose();
        }

        public void Initialize()
        {
            videoProvider.Initialize();
        }

        public BitmapSource GetRawFrame()
        {
            return videoProvider.GetRawBitmapSource();
        }

        public BitmapSource GetEffectFrame()
        {
            return videoProvider.GetRawBitmapSource();
            // ◆実装予定
        }
    }
}
