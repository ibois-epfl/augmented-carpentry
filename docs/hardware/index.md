# Hardware overview

![hardware overview><](../assets/images/getting_started/animation_overview_hardware.gif){width="1000"}

This section provides an overview of the hardware requirements for the AC system. AC can run with a simple laptop (:fontawesome-solid-laptop-code:) and connected sensor or as a wearable system (:fontawesome-solid-briefcase:). We include instructions for both layouts. The major XR hardware components for AC are:

- **A** : the [computing unit](./computing.md)
- **B** : the [woodworking electric powertool](./woodworking-tools.md)
- **C** : a [tool mount](./woodworking-tools.md#available-3d-mounts)
- **D** : a [digitized toolhead](./woodworking-tools.md#available-toolheads)
- **E** : an [interface](./interface.md)
- **F** : a [monocular camera](sensors.md)
- *: Additionally you will also require to print [stickers](./stickers.md) to tag the beams.

In the current state of our prototype, we have opted not to use off-the-shelf or commercial XR devices. Several factors influenced this decision. We wanted to maintain complete control over our XR prototype and make it fully open-srouce and free.

To reduce manufacturing tolerances and achieve higher precision, we limited the number of tracking devices to a single sensor—a simple monocular camera used by AC. Monocular cameras are rich in information, lightweight, and economically accessible, making them an attractive choice for open-source, distributed systems like AC.
Additionally, we aimed to avoid the proprietary barriers often found in low-level XR software components (e.g., the inability to replace a particular SLAM of a device) during development. As a result, we assembled a minimal yet highly customized demonstrator specifically adapted for woodworking, giving us greater freedom in refining and improving our XR setup.
