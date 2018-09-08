using Prism.Mvvm;
using Reactive.Bindings;
using Reactive.Bindings.Extensions;
using System;
using System.Reactive.Disposables;
using System.Windows.Media.Imaging;

namespace PrismWpf.MainModule.Models
{
    class VideoStreamManager : BindableBase, IDisposable
    {
        private CompositeDisposable CompositeDisposable;

        private VideoProvider videoProvider;

        // View表示用の最新フレーム画像
        public ReadOnlyReactivePropertySlim<BitmapSource> FrameLatest { get; }

        public VideoStreamManager()
        {
            CompositeDisposable = new CompositeDisposable();

            videoProvider = new VideoProvider();
            CompositeDisposable.Add(videoProvider);

            #region ReactiveProperty

            // View表示用の最新フレーム画像
            FrameLatest = videoProvider
                .ObserveProperty(x => x.FrameLatest)
                .ToReadOnlyReactivePropertySlim()
                .AddTo(CompositeDisposable);

            #endregion
        }

        public void Dispose()
        {
            if (!CompositeDisposable.IsDisposed)
                CompositeDisposable.Dispose();
        }

        public void Initialize()
        {
            videoProvider.Initialize();
        }
        
        public void CaptureRawFrame()
        {
            videoProvider.CaptureRawFrame();
        }

        //public BitmapSource CaptureEffectFrame()
        //{
        //    return videoProvider.GetRawBitmapSource();
        //}
    }
}
