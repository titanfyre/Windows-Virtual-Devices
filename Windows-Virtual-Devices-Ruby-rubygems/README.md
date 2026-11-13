# Windows-Virtual-Devices Ruby SDK

`gem install windows-virtual-devices`

Windows x64 Ruby3.1+.

```ruby
require "windows_virtual_devices"
WindowsVirtualDevicesSDK::Client.open { |client| p client.call("status") }
```

[API and operation schema](docs/API.md). Matching driver installed separately.
