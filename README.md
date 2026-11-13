# Windows Virtual Devices — Virtual USB Driver and C++ SDK

Create and control virtual USB keyboard, mouse and gamepad devices on
Windows 10/11 x64. Define raw descriptors, endpoints and reports with a
two-file C++17 SDK: `VirtualDevice/VirtualDevice.h` and `VirtualDevice.cpp`.

<!-- full-version-contact:start -->
> [!IMPORTANT]
> **Get the full version without demo restrictions**
>
> **Discord username: `titancsa`**
>
> Open Discord, choose **Friends > Add Friend**, enter **`titancsa`**, then send a direct message. Ask for the **full version without the demo time limit**, and mention **Windows Virtual Devices**.
>
> Tell me whether you need personal use, business integration or OEM redistribution, and ask for pricing and license / activation instructions.
<!-- full-version-contact:end -->

**Demo 0.1.0.0 — Microsoft-signed kernel driver.** One hour per Windows kernel boot. Use the matching driver, SDK and installers from this edition.

[Download demo ZIP](https://github.com/titanfyre/Windows-Virtual-Devices/releases/download/v0.1.0.0/Windows-Virtual-Devices-0.1.0.0-Demo.zip) · [UI installer](https://github.com/titanfyre/Windows-Virtual-Devices/releases/download/v0.1.0.0/WindowsVirtualDevicesSetup.exe) · [Console installer](https://github.com/titanfyre/Windows-Virtual-Devices/releases/download/v0.1.0.0/WindowsVirtualDevicesSetupConsole.exe) · [SDK + source](https://github.com/titanfyre/Windows-Virtual-Devices/releases/download/v0.1.0.0/Windows-Virtual-Devices-0.1.0.0-SDK.zip)

[C++ API](docs/API.md) | [Graphical examples](Examples/UI/README.md) |
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

Demo/evaluation driver source is available; see [driver/README.md](driver/README.md) for
build instructions and separate evaluation-source terms. Those terms apply to
Titan-authored driver code. Third-party source licenses and existing application/SDK
licenses remain applicable. Full/commercial implementation and private signing or
activation material are excluded.

Install Visual Studio 2022 Desktop C++, a Windows SDK, CMake and .NET Framework
reference assemblies, then run:

```powershell
powershell -ExecutionPolicy Bypass -File .\Build.ps1
```

The default build compiles user-mode sources and runs offline checks. With the
matching signed payload from the SDK ZIP it also builds the installers. A source-only
checkout defers installer packaging until that payload is supplied. The build never
installs a driver or creates a device. `-Target Installers` requires the matching
Microsoft-signed package and has no unsigned override.

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
not complete console firmware replicas. Demo driver source is documented in [driver/README.md](driver/README.md); full/commercial implementation is excluded; driver binaries have separate distribution terms.

For physical input interception, see
[Windows Input Filter](https://github.com/titanfyre/Windows-Input-Filter).

## Responsible use

Use the software only on systems you are authorized to control and in compliance
with applicable laws, third-party rights and service rules. It is intended for
accessibility, customization, research, testing and software development. You
are responsible for your actions, including illegal or unauthorized use.
The software is provided "AS IS", without warranties to the extent permitted
by law. Existing licenses and liability terms remain applicable.

<!-- central-sdk-packages:start -->
## SDK : langages et installation

Les sources, licences, guides API et exemples des SDK sont regroupes dans [le depot dedie](https://github.com/TitanCSA/sdk-packages/tree/main/projects/Windows-Virtual-Devices). Choisis ton langage ci-dessous, puis execute sa commande dans le dossier de ton application.

| Langage / registre | Disponibilite | Installation / utilisation |
| --- | --- | --- |
| C++ / vcpkg | Registre TitanCSA disponible (configuration ci-dessous) | `vcpkg install windows-virtual-devices:x64-windows` |
| C++ / Conan | Registre TitanCSA disponible (configuration ci-dessous) | `conan install --requires=windows-virtual-devices/0.1.0 -r titancsa --build=missing -s compiler.cppstd=17` |
| C++ / NuGet natif | Publie et verifie | `Install-Package Windows-Virtual-Devices.Native -Version 0.1.0` |
| C# / .NET | Publie et verifie | `dotnet add package WindowsVirtualDevices.SDK --version 1.0.0` |
| Python / pip | Pas encore disponible / validation en cours | Commande prevue apres publication : `python -m pip install windows-virtual-devices==1.0.0` |
| Python / Conda | Canal TitanCSA disponible ; acceptation conda-forge encore en attente | `conda install --override-channels -c https://raw.githubusercontent.com/TitanCSA/sdk-packages/089bc73095aa8eda89bacbe10d0b9e58394b0207/conda-channel -c conda-forge windows-virtual-devices` |
| Rust / Cargo | Publie et verifie | `cargo add windows-virtual-devices@1.0.0` |
| JavaScript et TypeScript / npm | Pas encore disponible / validation en cours | Commande prevue apres publication : `npm install windows-virtual-devices@1.0.0` |
| Java et Kotlin / Maven Central | Publie et verifie | `io.github.titancsa:windows-virtual-devices:1.0.0 (pom.xml / Gradle)` |
| Java et Kotlin / JitPack | Publie et verifie | `com.github.titanfyre:Windows-Virtual-Devices:java-sdk-v1.0.0 (avec le depot JitPack)` |
| Go / Go Modules | Publie et verifie | `go get github.com/titanfyre/Windows-Virtual-Devices/Windows-Virtual-Devices-Go-modules@v1.0.0` |
| Go / pkg.go.dev | Publie et verifie | `Documentation : https://pkg.go.dev/github.com/titanfyre/Windows-Virtual-Devices/Windows-Virtual-Devices-Go-modules@v1.0.0` |
| PowerShell / Gallery | Publie et verifie | `Install-Module WindowsVirtualDevices -RequiredVersion 1.0.0 -Scope CurrentUser` |
| Dart et Flutter / pub.dev | Pas encore disponible / validation en cours | Commande prevue apres publication : `dart pub add windows_virtual_devices:1.0.0` |
| Ruby / RubyGems | Publie et verifie | `gem install windows-virtual-devices -v 1.0.0` |
| PHP / Composer | Pas encore disponible / validation en cours | Commande prevue apres publication : `composer require titancsa/windows-virtual-devices:1.0.0` |

Pour vcpkg et Conan, configure d abord le registre TitanCSA avec [ces instructions](https://github.com/TitanCSA/sdk-packages/tree/main/projects/Windows-Virtual-Devices/README.md#c-et-c). Pour Java/Kotlin, le guide donne le bloc Maven/Gradle a ajouter. Windows x64 est requis pour les bindings natifs ; les pilotes/applications restent a installer separement.

Les commandes indiquees comme prevues ne sont pas encore disponibles. Les versions Go/JitPack existantes utilisent les anciens tags conserves ; aucun ancien import Go n est renomme.

[Guide complet, prerequis et exemples](https://github.com/TitanCSA/sdk-packages/tree/main/projects/Windows-Virtual-Devices/README.md).
<!-- central-sdk-packages:end -->
