# Windows-Virtual-Devices PowerShell SDK

PowerShell7.4+ Windows x64. `Install-Module WindowsVirtualDevices -Scope CurrentUser`.

```powershell
$client=Connect-WindowsVirtualDevicesSDK
try { Invoke-WindowsVirtualDevicesSDK -Client $client -Operation status } finally { Disconnect-WindowsVirtualDevicesSDK -Client $client }
```

Use -Arguments with a hashtable matching [schema](docs/API.md). Native errors retain their Windows code through the inner exception. Matching driver installed separately.
