# Computer

AC's prototype is built for x64 machines running on Ubuntu 22.04 LTS. The system does not exploit GPU acceleration and can run on a laptop, a portable computing unit or a desktop.

## test
<!-- md:version v0.4.0 -->


=== ":fontawesome-solid-briefcase:&nbsp;&nbsp; Wearable"

    ## Deploying on a NUC


    In our current prototype we wanted to develop a computing unit that could be easily transported and used in construction sites and shops. For this reason we decided to use a x64 machine of type [NUC](https://en.wikipedia.org/wiki/Next_Unit_of_Computing). We decided such machine for our wearable layout for the following reasons:

    `x64 target machine`
    :   More importantly, it has the same architecture as a laptop or a desktop, which streamlines the development process (e.g. no `.apk` files to generate and deploy on the device). Additionally, being on UNIX x64 machines, we could leverage all the top notch libraries and dependecies available from robotics and computer vision communities.

    `Small factor`
    :   It is a small form factor computer that can be easily transported.

    ` Low power consumption`
    :   It is energy efficient and can be powered by a 18v (5.0Ah) battery for power tools.

    `Ordinary Sensor Interface`
    :   It has a USB interface which is common and can be used to connect the camera as well as any other device (e.g. touch screen).

    /// html | div[style='float: left; width: 40%;']
    
    ![pc hardware view](../assets/images/getting_started/only_pc.JPG){width="400" class="rounded-corners"}
    
    ///

    /// html | div[style='float: right;width: 60%;']
    
    <div style="padding: 10px; overflow: auto;">
    <pre>
    OS: Ubuntu 22.04.3 LTS x86_64 
    Host: NUC13ANHi7 M89903-203 
    Kernel: 6.8.0-40-generic 
    Uptime: 8 mins 
    Packages: 2299 (dpkg), 17 (snap) 
    Shell: bash 5.1.16 
    Resolution: 1024x600 
    DE: GNOME 42.9 
    WM: Mutter 
    WM Theme: Adwaita 
    Theme: Yaru [GTK2/3] 
    Icons: Yaru [GTK2/3] 
    Terminal: gnome-terminal 
    CPU: 13th Gen Intel i7-1360P (16) @ 5.000GHz 
    GPU: Intel Device a7a0 
    Memory: 1622MiB / 31645MiB 
    </pre>
    </div>
    
    ///

    /// html | div[style='clear: both;']
    ///
    
    ## Additional components

    The NUC is contained in a 3D printed protection[^1] case that we designed specifically for extra resistance and to include an attachment for the battery. The battery is a 18v (5.0Ah) battery that can be used for power tools. The battery is connected to the NUC via a 5v regulator (LM785) to ensure a stable power supply. The battery is also connected to a buzzer that will beep when the battery voltage is below a certain threshold (circa 15%). This will inform the user to change the battery.

    <!-- TODO:add block custom with files to donwload -->

    ???+ example "Simple battery monitor"

        As a bonus, here's the diagram and code snippet shows how to monitor the battery voltage connected to a NUC using a buzzer. The buzzer will inform when needs to be changed.

        To realize this schematic, you will need the following components:

        - [x] 1x Arduino Nano
        - [x] 1x DIY cable sleeve
        - [x] 1x 5v regulator (LM785)
        - [x] 1x battery attachment
        - [x] 1x piezo buzzer
        - [x] 6x resistors 200ohm

        ![diagram for battery](../assets/images/getting_started/voltageBuzzer.png){align=left width="500" class="rounded-corners"}

        ``` c++ title="assets/arduino_scripts/battmonitor.ino"
        --8<-- "assets/arduino_scripts/battmonitor.ino.ino"
        ```

        [^1]: for our prototype we printed on a Pruse MK3d+ on PLA.

=== ":fontawesome-solid-laptop-code:&nbsp;&nbsp; Laptop"

    pass


