param([string]$Manifest,[string]$Fixture)
$ErrorActionPreference="Stop"
Import-Module $Manifest
Test-ModuleManifest $Manifest|Out-Null
$c=Connect-WindowsVirtualDevicesSDK
try{$rejected=$false;try{Invoke-WindowsVirtualDevicesSDK -Client $c -Operation check|Out-Null}catch{$rejected=$true};if(-not $rejected){throw "Invalid config accepted"};if($Fixture){$d=Invoke-WindowsVirtualDevicesSDK -Client $c -Operation connect -Arguments @{descriptors=@(@{data=@(1,2,3)})};if($d.device_id -cne "9223372036854775809"){throw "uint64 lost"}}}finally{Disconnect-WindowsVirtualDevicesSDK -Client $c}
