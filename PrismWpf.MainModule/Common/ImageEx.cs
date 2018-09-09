using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Windows.Media.Imaging;

namespace PrismWpf.MainModule.Common
{
    static class ImageEx
    {
        /// <summary>
        /// BitmapをBitmapImageに型変換
        /// </summary>
        /// <param name="bitmap">Bitmap画像</param>
        /// <returns>BitmapImage画像</returns>
        public static BitmapImage ToBitmapImage(this Bitmap bitmap)
        {
            if (bitmap == null) throw new ArgumentNullException();

            var image = new BitmapImage();
            using (var ms = new MemoryStream())
            {
                bitmap.Save(ms, ImageFormat.Bmp);

                image.BeginInit();
                image.CacheOption = BitmapCacheOption.OnLoad;
                ms.Seek(0, SeekOrigin.Begin);
                image.StreamSource = ms;
                image.EndInit();
                image.Freeze();
            }
            return image;
        }

        /// <summary>
        /// 引数PATHをBitmapImageで読み出す
        /// </summary>
        /// <param name="imagePath">画像PATH</param>
        /// <returns></returns>
        public static BitmapImage ToBitmapImage(this string imagePath)
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

        /// <summary>
        /// BitmapSourceを保存する
        /// </summary>
        /// <param name="bitmapSource"></param>
        /// <param name="filePath"></param>
        public static void SaveFile(this BitmapSource bitmapSource, string filePath)
        {
            if (bitmapSource == null) throw new ArgumentNullException();

            using (var fileStream = new FileStream(filePath, FileMode.Create))
            {
                var encoder = new JpegBitmapEncoder
                {
                    QualityLevel = 50   // JPEG画質(Min=1, Max=100)
                };
                encoder.Frames.Add(BitmapFrame.Create(bitmapSource));
                encoder.Save(fileStream);
            }
        }


        /// <summary>
        /// BitmapからBitmapSourceに変換
        /// </summary>
        /// <param name="bitmap"></param>
        /// <returns></returns>
        private static BitmapSource ToBitmapSource(this Bitmap bitmap)
        {
            var bitmapData = bitmap.LockBits(
                new Rectangle(0, 0, bitmap.Width, bitmap.Height),
                ImageLockMode.ReadOnly, bitmap.PixelFormat);

            var bitmapSource = BitmapSource.Create(
                bitmapData.Width, bitmapData.Height,
                bitmap.HorizontalResolution, bitmap.VerticalResolution,
                System.Windows.Media.PixelFormats.Bgr24, null,
                bitmapData.Scan0, bitmapData.Stride * bitmapData.Height, bitmapData.Stride);

            bitmap.UnlockBits(bitmapData);
            return bitmapSource;
        }

    }
}
