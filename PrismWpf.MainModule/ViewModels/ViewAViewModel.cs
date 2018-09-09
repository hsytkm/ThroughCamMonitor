using Prism.Mvvm;
using PrismWpf.MainModule.Common;
using PrismWpf.MainModule.Models;
using Reactive.Bindings;
using Reactive.Bindings.Extensions;
using System;
using System.Diagnostics;
using System.IO;
using System.Reactive.Disposables;
using System.Reactive.Linq;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;
using ThroughCamVideoCaptureWrapper;

namespace PrismWpf.MainModule.ViewModels
{
    public class ViewAViewModel : BindableBase
    {
        private CompositeDisposable CompositeDisposable;

        private VideoStreamManager videoStreamManager;

        // C++Wrapper
        private VideoCaptureWrapper videoCaptureWrapper = new VideoCaptureWrapper();


        // View表示画像
        public ReadOnlyReactiveProperty<BitmapSource> VideoFrameImage { get; }

        private BitmapSource _VideoFrameImage2;
        public BitmapSource VideoFrameImage2
        {
            get => _VideoFrameImage2;
            set => SetProperty(ref _VideoFrameImage2, value);
        }

        #region Command

        // OpenCvSharpコマンド
        public ReactiveCommand StartCvSharpCommand { get; } = new ReactiveCommand();

        // C++Wrapperコマンド
        public ReactiveCommand StartCppCommand { get; } = new ReactiveCommand();

        #endregion


        public ViewAViewModel()
        {
            CompositeDisposable = new CompositeDisposable();

            videoStreamManager = new VideoStreamManager();
            CompositeDisposable.Add(videoStreamManager);

            // ReactiveProperty
            VideoFrameImage = videoStreamManager.FrameLatest.ToReadOnlyReactiveProperty().AddTo(CompositeDisposable);

            videoCaptureWrapper.Initialize();

            this.StartCvSharpCommand
                .Subscribe(_ =>
                {
                    // Task.Run(() => ReadDiskJpegs()); // View表示テスト

                    Task.Run(() =>
                    {
                        videoStreamManager.Initialize();

                        while (true)
                        {
                            videoStreamManager.CaptureRawFrame();
                            //videoStreamManager.CaptureEffectFrame();
                        }
                    });
                });


            this.StartCppCommand
                .Subscribe(_ =>
                {
                    //Task.Run(() => ReadDiskJpegs()); // View表示テスト

                    // C++DLLのテストコード
                    //while (true)
                    {
                        IntPtr matPtr = videoCaptureWrapper.GetVideoFrame();

                        using (var nega = new NegaFilterWrapper())
                        {
                            nega.Processing(matPtr);
                        }

                        VideoFrameImage2 = videoCaptureWrapper.ToBitmapSource(matPtr);

                        //System.Threading.Thread.Sleep(100);
                    }
                });

        }

        private void ReadDiskJpegs()
        {
            var basePath = @"C:\";
            string[] imagePaths = Directory.GetFiles(basePath, "*.jpg", SearchOption.TopDirectoryOnly);

            Debug.WriteLine("Start");
            var sw = new Stopwatch();
            sw.Start();

            foreach (var path in imagePaths)
            {
                VideoFrameImage2 = path.ToBitmapImage();
            }

            sw.Stop();
            Debug.WriteLine($"End {sw.ElapsedMilliseconds}msec");
        }
    }
}
