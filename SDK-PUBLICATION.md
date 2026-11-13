# SDK publication status

Current source layout and registry coverage. A GitHub download is distinct from publication on a central registry.

| Target | Status | Package / documentation |
| --- | --- | --- |
| CPP/vcpkg | published_custom_registry | windows-virtual-devices |
| CPP/conan | published_custom_source_index | [windows-virtual-devices](https://github.com/TitanCSA/sdk-packages/tree/089bc73095aa8eda89bacbe10d0b9e58394b0207/conan-index) [Source](packaging/native/) |
| CPP/nuget | published_payload_verified | [Windows-Virtual-Devices.Native](https://www.nuget.org/packages/Windows-Virtual-Devices.Native/0.1.0) |
| NET/nuget | published_payload_verified | [WindowsVirtualDevices.SDK](https://www.nuget.org/packages/WindowsVirtualDevices.SDK/1.0.0) |
| Python/pypi | built_fixture_and_production_verified | windows-virtual-devices [Source](Windows-Virtual-Devices-Python-pypi/) |
| Python/conda-forge | custom_channel_install_verified_requires_conda_forge_review | [windows-virtual-devices](https://raw.githubusercontent.com/TitanCSA/sdk-packages/089bc73095aa8eda89bacbe10d0b9e58394b0207/conda-channel) [Source](packaging/conda/) |
| Rust/cargo | published_install_verified | [windows-virtual-devices](https://crates.io/crates/windows-virtual-devices) [Source](Windows-Virtual-Devices-Rust-cargo/) |
| JavaScript/npm | registry_rate_limit_wait | [windows-virtual-devices](https://www.npmjs.com/package/windows-virtual-devices) [Source](Windows-Virtual-Devices-JavaScript-npm/) |
| Java/maven | published_install_verified | [windows-virtual-devices](https://central.sonatype.com/artifact/io.github.titancsa/windows-virtual-devices/1.0.0) [Source](Windows-Virtual-Devices-Java-maven/) |
| Java/jitpack | published_install_verified | [windows-virtual-devices](https://jitpack.io/#titanfyre/Windows-Virtual-Devices/java-sdk-v1.0.0) [Source](Windows-Virtual-Devices-Java-maven/) |
| Go/modules | published_install_verified | [windows-virtual-devices](https://pkg.go.dev/github.com/titanfyre/Windows-Virtual-Devices/Windows-Virtual-Devices-Go-modules@v1.0.0) [Source](Windows-Virtual-Devices-Go-modules/) |
| Go/pkg-go-dev | indexed_verified | [Documentation](https://pkg.go.dev/github.com/titanfyre/Windows-Virtual-Devices/Windows-Virtual-Devices-Go-modules@v1.0.0) |
| PowerShell/gallery | published_install_verified | [WindowsVirtualDevices](https://www.powershellgallery.com/packages/WindowsVirtualDevices/1.0.0) [Source](Windows-Virtual-Devices-PowerShell-gallery/) |
| Dart/pub-dev | built_fixture_and_production_verified | windows_virtual_devices [Source](Windows-Virtual-Devices-Dart-pub-dev/) |
| Ruby/rubygems | published_install_verified | [windows-virtual-devices](https://rubygems.org/gems/windows-virtual-devices) [Source](Windows-Virtual-Devices-Ruby-rubygems/) |
| PHP/packagist | composer_source_and_tag_published | [titancsa/windows-virtual-devices](https://packagist.org/packages/titancsa/windows-virtual-devices) |

Native SDK source and CMake/Conan/vcpkg/NuGet recipes share [`packaging/native`](packaging/native/LAYOUT.md). Previous release archives and tags remain unchanged.

Application and driver prerequisites and original licensing remain those documented by each SDK. No driver installer is bundled with these source packages.
