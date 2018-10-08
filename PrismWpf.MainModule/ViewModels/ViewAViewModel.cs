using Prism.Mvvm;
using PrismWpf.MainModule.Common;
using PrismWpf.MainModule.Models;
using Reactive.Bindings;
using Reactive.Bindings.Extensions;
using System;
using System.Collections.Generic;
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

        // 顔検出フラグ
        public ReactiveProperty<bool> IsFaceDetect { get; }

        // ネガポジフラグ
        public ReactiveProperty<bool> IsNegaPosi { get; }

        #region Command

        // OpenCvSharpコマンド
        public ReactiveCommand StartCvSharpCommand { get; } = new ReactiveCommand();

        // C++Wrapperコマンド
        public ReactiveCommand StartCppCommand { get; } = new ReactiveCommand();

        #endregion

        // 以下、暫定
        private bool _IsFaceDetect2;
        public bool IsFaceDetect2
        {
            get => _IsFaceDetect2;
            set => SetProperty(ref _IsFaceDetect2, value);
        }
        private bool _IsNegaPosi2;
        public bool IsNegaPosi2
        {
            get => _IsNegaPosi2;
            set => SetProperty(ref _IsNegaPosi2, value);
        }


        public ViewAViewModel()
        {
            CompositeDisposable = new CompositeDisposable();

            videoStreamManager = new VideoStreamManager();
            CompositeDisposable.Add(videoStreamManager);

            // ReactiveProperty
            VideoFrameImage = videoStreamManager.FrameLatest.ToReadOnlyReactiveProperty().AddTo(CompositeDisposable);

            IsFaceDetect = this.ToReactivePropertyAsSynchronized(x => x.IsFaceDetect2).AddTo(CompositeDisposable);
            IsNegaPosi = this.ToReactivePropertyAsSynchronized(x => x.IsNegaPosi2).AddTo(CompositeDisposable);

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

                    Task.Run(() =>
                    {
                        // C++DLLのテストコード
                        while (true)
                        {
                            var matBuffer = new MatBuffer();
                            IntPtr srcMat = videoCaptureWrapper.GetVideoFrame();
                            IntPtr aftMat = matBuffer.CopyIntPtrMat(srcMat);

                            var moduleTypes = new List<ModuleFactory.ModuleType>();
                            if (IsFaceDetect2) moduleTypes.Add(ModuleFactory.ModuleType.Face);
                            if (IsNegaPosi2) moduleTypes.Add(ModuleFactory.ModuleType.Nega);

                            using (var moduleManager = new ModuleManager(moduleTypes.AsReadOnly()))
                            {
                                aftMat = moduleManager.Processing(aftMat);
                            }

                            //VideoFrameImage2 = StaticClassForCsharp.ToBitmapSource(aftMat);
                            VideoFrameImage2 = StaticClassForCsharp.ToBitmapSource(srcMat, aftMat);
                        }
                    });
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
