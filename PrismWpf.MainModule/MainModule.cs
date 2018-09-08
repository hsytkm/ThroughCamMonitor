using Autofac;
using Prism.Modularity;
using Prism.Regions;
using PrismWpf.MainModule.Views;

namespace PrismWpf.MainModule
{
    public class MainModule : IModule
    {
        private IRegionManager _regionManager;
        private ContainerBuilder _builder;

        public MainModule(ContainerBuilder builder, IRegionManager regionManager)
        {
            _builder = builder;
            _regionManager = regionManager;
        }

        public void Initialize()
        {
            _regionManager.RegisterViewWithRegion("ContentRegion", typeof(ViewA));
        }
    }
}