# Installation status and workflow

Windows Virtual Devices 0.1.0.0 has a verified matching Microsoft-signed package. Download the [demo ZIP](https://github.com/titanfyre/Windows-Virtual-Devices/releases/download/v0.1.0.0/Windows-Virtual-Devices-0.1.0.0-Demo.zip) for the installers and graphical examples, or the [SDK ZIP](https://github.com/titanfyre/Windows-Virtual-Devices/releases/download/v0.1.0.0/Windows-Virtual-Devices-0.1.0.0-SDK.zip) for source and matching signed binary build inputs.

Installation workflow:

1. Run `WindowsVirtualDevicesSetup.exe`, accept elevation and choose Install.
2. Restart Windows only if setup requests it, then reopen setup to check state.
3. Open a graphical device example and choose Create device. Wait for READY.
4. Edit controls and send a state. Release held inputs before disconnecting.

The console installer uses `/install`, `/uninstall`, `/status` and `/diagnose`.
It stages only the new product's package and root controller. Installation
must pass Microsoft-signature and catalog-membership validation; security settings
are never disabled. Existing Vdevice or other product services are not its targets.

The driver root/service identity is `WindowsVirtualDevices`. Its package also
contains `DemoSessionClock.sys`, with the product-owned
`WindowsVirtualDevicesDemoClock` service. This implements the one-hour per-boot
demo allowance, shared across applications. Closing an application or reinstalling
does not reset it.

Install/repair reports the PnP, service, package, API and restart
states separately. A service entry alone does not establish readiness. The UI
shows a Restart button only when required; diagnostics are read-only and do not
create devices or start the demo allowance.
