# Windows Virtual Devices — Virtual USB Driver and C++ SDK

Create and control virtual USB keyboard, mouse and gamepad devices on
Windows 10/11 x64. Define raw descriptors, endpoints and reports with a
two-file C++17 SDK: `VirtualDevice/VirtualDevice.h` and `VirtualDevice.cpp`.

**Demo 0.1.0.0 — Microsoft signing pending.** This repository currently provides
SDK, graphical-example and installer source code. Production installers and a
driver download will be added only after the new signed package is returned
and validated. Do not install an unsigned build on your normal PC.

[C++ API](docs/API.md) | [Graphical examples](ExamplesUI/README.md) |
[Installation](docs/INSTALLATION.md) | [Scope and validation](docs/VALIDATION.md)

## Seven operations for every protocol

| Operation | Purpose |
| --- | --- |
| `VirtualDevice::Check(config)` | Validate the raw description offline |
| `VirtualDevice::Status()` | Read capabilities, owned devices and demo state |
| `VirtualDevice::Connect(config)` | Create an owned virtual USB device |
| `VirtualDevice::Disconnect(device)` | Disconnect it explicitly |
| `VirtualDevice::Send(device, bytes)` | Send through the sole declared IN endpoint |
| `VirtualDevice::Receive(timeout)` | Receive host output, controls or device-state events |
| `VirtualDevice::Reply(output, bytes, stall)` | Complete a delegated control request |

For multi-IN devices, use `Send(device, endpoint, bytes)`. The implicit endpoint
is selected once during creation; a missing or ambiguous IN endpoint is rejected.
No device family, byte count or manual session management is required.

The move-only `Device` object owns its device. Keep it alive while sending and
receiving. Destruction or process termination disconnects owned virtual devices.
Creation is asynchronous: service output/control requests during enumeration
and wait for configuration before normal input. Send success means accepted
into the bounded queue, not consumed by an application.

## Build the SDK and examples

Install Visual Studio 2022 Desktop C++, a Windows SDK, CMake and .NET Framework
reference assemblies, then run:

```powershell
powershell -ExecutionPolicy Bypass -File .\Build.ps1
```

The default build compiles user-mode sources and runs offline checks. While
signing is pending it explicitly defers installer packaging. It never installs
a driver or creates a virtual device. `-Target Installers` requires the new
Microsoft-signed driver package and has no unsigned override.

The graphical examples cover a USB keyboard, mouse, Xbox 360/XInput, DualShock 4,
Xbox One/GIP and a raw Descriptor Workshop. `--preview` opens the five native
control panels offline. Normal device creation requires the matching signed
driver and administrator rights. Device-specific descriptions and report
encoders live in the examples; the SDK contains no built-in device profiles.

## Demo and supported scope

The demo allowance is **one hour per Windows kernel boot**, starting at the
first successful virtual-device creation and shared across applications.
Sleep counts; closing or reinstalling does not reset it. Expiry disconnects
devices and refuses creation/transfers until Windows Restart. For the
unrestricted version, contact **titancsa** on Discord. No paid edition is
included or prepared here.

The driver uses KMDF / UdeCx with USB low/full/high speed, one configuration,
alternate setting zero and interrupt/bulk endpoints. SuperSpeed, isochronous
audio, external hubs and additional configurations are outside the implemented
scope. A VID/PID change alone does not reproduce firmware or console
authentication. The GIP example uses the documented PC USB security opt-out
interface and requires Windows 10 21H2 or later.

## Source and notices

This demo is based on Vdevice. Original MIT and third-party notices are retained
in `LICENSE` and `licenses/NOTICE`. Selected example descriptors/protocol data
originate from [ViGEmBus](https://github.com/nefarius/ViGEmBus) under BSD-3-Clause
and Microsoft's MS-GIPUSB documentation. The examples are PC protocol examples,
not complete console firmware replicas. Kernel source is private and excluded
from this repository; driver binaries have separate distribution terms.

For physical input interception, see
[Windows Input Filter](https://github.com/titanfyre/Windows-Input-Filter).

## Responsible use

Use the software only on systems you are authorized to control and in compliance
with applicable laws, third-party rights and service rules. It is intended for
accessibility, customization, research, testing and software development. You
are responsible for your actions, including illegal or unauthorized use.
The software is provided "AS IS", without warranties to the extent permitted
by law. Existing licenses and liability terms remain applicable.
