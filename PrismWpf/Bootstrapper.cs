using PrismWpf.Views;
using System.Windows;
using Prism.Modularity;
using Autofac;
using Prism.Autofac;

namespace PrismWpf
{
    class Bootstrapper : AutofacBootstrapper
    {
        protected override DependencyObject CreateShell()
        {
            return Container.Resolve<MainWindow>();
        }

        protected override void InitializeShell()
        {
            Application.Current.MainWindow.Show();
        }

        protected override void ConfigureModuleCatalog()
        {
            var moduleCatalog = (ModuleCatalog)ModuleCatalog;
            moduleCatalog.AddModule(typeof(MainModule.MainModule));
        }
    }
}
