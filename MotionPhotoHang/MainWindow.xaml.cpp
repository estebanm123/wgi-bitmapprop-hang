#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Graphics.Imaging.h>


using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::MotionPhotoHang::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    constexpr wchar_t* MicroVideoVersionQuery = L"/xmp/{wstr=http://ns.google.com/photos/1.0/camera/}:MicroVideoVersion";
    constexpr wchar_t* MicroVideoOffsetQuery = L"/xmp/{wstr=http://ns.google.com/photos/1.0/camera/}:MicroVideoOffset";
    constexpr wchar_t* MotionPhotoVersionQuery = L"/xmp/{wstr=http://ns.google.com/photos/1.0/camera/}:MotionPhotoVersion";

    winrt::fire_and_forget MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));

        WCHAR exePath[MAX_PATH];
        GetModuleFileNameW(NULL, exePath, MAX_PATH);
        PathRemoveFileSpecW(exePath);
        auto sampleHeicPath = std::wstring{ exePath } + L"\\Images\\test.HEIC";

        auto file = co_await Windows::Storage::StorageFile::GetFileFromPathAsync(sampleHeicPath);

        Windows::Storage::Streams::IRandomAccessStream fileStream = nullptr;

        try
        {
            fileStream = co_await file.OpenAsync(Windows::Storage::FileAccessMode::Read);
            auto decoder = co_await Windows::Graphics::Imaging::BitmapDecoder::CreateAsync(fileStream);
            auto bmpProperties = decoder.BitmapProperties();
            if (bmpProperties)
            {
                auto queries = winrt::single_threaded_vector<winrt::hstring>();
                queries.Append(MicroVideoVersionQuery);
                queries.Append(MicroVideoOffsetQuery);
                queries.Append(MotionPhotoVersionQuery);

                auto queryResults = co_await bmpProperties.GetPropertiesAsync(queries);
            }
        }
        catch (...) {}

        if (fileStream != nullptr) fileStream.Close();

        //DescriptionText().Text(L"Decode test is finished. \nClick the button again and you should see the memory permanently increase with each subsequent run.");
    }
}
