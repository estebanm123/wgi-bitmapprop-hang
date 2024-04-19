This sample app showcases a hang with the winrt::Windows::Graphics::Imaging::BitmapProperties::GetPropertiesAsync API when fetching motion photo metadata.

## Repro steps
1. Clone this repo and open MotionPhotoHang.sln. I have to restart Visual Studio after this step.
2. Launch the sample app in Debug/x64 -> Local Machine
3. Click the button in the center of the window. The UI should freeze indefinitely at this step. Pause the debugger -> inspect threads and observe the WGI::BitmapProperties::GetPropertiesAsync call is hung.

My OS version: 23H2 - 22631.3447

I've provided a .heic this repros 100% for me, but we have reports of users experiencing this exact hang on JPG.
