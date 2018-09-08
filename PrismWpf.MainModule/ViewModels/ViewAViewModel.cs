using Prism.Commands;
using Prism.Mvvm;
using PrismWpf.MainModule.Models;
using Reactive.Bindings;
using Reactive.Bindings.Extensions;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
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

        //public ReactiveProperty<BitmapSource> VideoImage { get; } = new ReactiveProperty<BitmapSource>();
        //{
        //    get => _VideoImage;
        //    set => SetProperty(ref _VideoImage, value);
        //}

        // View表示画像
        public ReadOnlyReactiveProperty<BitmapSource> VideoFrameImage { get; }

        #region Command

        // 自動実行コマンド
        public ReactiveCommand StartCommand { get; } = new ReactiveCommand();
        
        #endregion


        public ViewAViewModel()
        {
            CompositeDisposable = new CompositeDisposable();

            videoStreamManager = new VideoStreamManager();
            CompositeDisposable.Add(videoStreamManager);

            // C++DLLのテストコード
            using (var vc = new VideoCaptureWrapper())
            {
                //vc.ShowVideo();
                //vc.GetVideoImage();
            }

            // ReactiveProperty
            VideoFrameImage = videoStreamManager.FrameLatest.ToReadOnlyReactiveProperty().AddTo(CompositeDisposable);

            this.StartCommand
                .Subscribe(_ =>
                {
                    Task.Run(() =>
                    {
#if false
                        var basePath = @"C:\Users\t_hos\source\repos\_data\CrazyShooters\_Bonus";

                        string[] imagePaths = Directory.GetFiles(basePath, "*.jpg", SearchOption.TopDirectoryOnly);

                        Debug.WriteLine("Start");
                        var sw = new Stopwatch();
                        sw.Start();

                        foreach (var path in imagePaths)
                        {
                            VideoImage = ToBitmapImage(path);
                        }

                        sw.Stop();
                        Debug.WriteLine($"End {sw.ElapsedMilliseconds}msec");
#endif
                        // 初期化
                        videoStreamManager.Initialize();

                        while (true)
                        {
                            //videoStreamManager.CaptureRawFrame();
                            videoStreamManager.CaptureEffectFrame();

                            //var image = VideoStreamManager.GetRawFrame();
                            //var image = videoStreamManager.GetEffectFrame();
                            //if (image != null) VideoFrameImage.Value = image;
                        }

                    });
                });

        }


        /// <summary>
        /// 引数PATHをBitmapImageで読み出す
        /// </summary>
        /// <param name="imagePath">画像PATH</param>
        /// <returns></returns>
        public static BitmapImage ToBitmapImage(string imagePath)
        {
            if (imagePath == null) throw new ArgumentNullException();
            if (!File.Exists(imagePath)) throw new FileNotFoundException();

            var bi = new BitmapImage();

            // アプリが画像ファイルを占有しない
            using (var fs = File.Open(imagePath, FileMode.Open, FileAccess.Read, FileShare.Read))
            {
                bi.BeginInit();
                bi.CacheOption = BitmapCacheOption.OnLoad;
                bi.StreamSource = fs;
                bi.EndInit();
                bi.Freeze();
            }
            return bi;
        }
    }
}
