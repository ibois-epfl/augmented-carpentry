# Interface

AC is designed as a console app with a [GUI](https://en.wikipedia.org/wiki/Graphical_user_interface). This means that it can work with a touch screen (via HDMI) or a laptop. The interface is designed to be simple and intuitive. The main goal is to provide a quick and familiar way to interact with the system where every touch operations is in reality a click operation. This way we can develop our AR software without bodering for dedicated development on more complex [HMDs](https://en.wikipedia.org/wiki/Head-mounted_display) or advanced AR interfaces that would offer more ergonomic value to the cost of an increase complexity during the deployement. 


=== ":fontawesome-solid-briefcase:&nbsp;&nbsp; Wearable"
    <!-- TODO: add here sub chapters and the hardware necessary -->
    If you use a touch screen be sure to set this option when configuring the build:

    ``` c++
    cmake -S . -B build -DDEPLOY_ON_TOUCH=ON
    ```

    You can use the [WaveShare WS170120](https://www.waveshare.com/wiki/7inch_HDMI_LCD_(B)) as in the current prototype and follow the instructions below:

    To config the touch screen on the pc follow [these steps first](https://www.waveshare.com/wiki/7inch_HDMI_LCD). Be sure to switch the display on, plug the mini-USB and finally plug the HDMI cable.

    Set the display properties in the `config.ini` properties (to find them run the commands `xinput`  for the name and `xrandr` for the connection type).

    The following specs works on the X11 display server also, but you can use any other touch screen, just make sure to set the correct specs in the `config.ini` file:

    ```c++ title="config.ini"
    [MonitorSpecs]
    monitor_name = WaveShare WS170120
    monitor_link_t = HDMI
    monitor_resolution = 1280 x 720
    ```

    !!! warning

        Wayland display and touchscreen are not compatible yet as the touchscreen register for the main display and not the small display.

        ```c++ title="config.ini"
        [MonitorSpecs]
        LinkMode = XWAYLAND1
        Name = Virtual core pointer
        Resolution = 1280 x 720
        ```

=== ":fontawesome-solid-laptop-code:&nbsp;&nbsp; Laptop"

    For a quick test or development you can use a laptop and the webcam. Just adjust later the CMake config option.

    ``` c++
    cmake -S . -B build -DDEPLOY_ON_TOUCH=OFF
    ```