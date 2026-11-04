param([string]$DriverDirectory,[string]$NativeHelper,[string]$OutputDirectory,[string]$BuildDirectory)
$ErrorActionPreference='Stop'
$root=Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
if(!$DriverDirectory){$DriverDirectory=Join-Path $root 'Installer\UI\Package'}
if(!$NativeHelper){$NativeHelper=Join-Path $root 'bin\Native\Release\WindowsVirtualDevicesSetupNative.exe'}
if(!$OutputDirectory){$OutputDirectory=Join-Path $root 'bin\InstallerConsole'}
if(!$BuildDirectory){$BuildDirectory=Join-Path $root 'obj\InstallerConsole'}
. (Join-Path $root 'Installer\UI\Build.Common.ps1')
New-Item -ItemType Directory -Path $OutputDirectory -Force|Out-Null
$payload=New-WindowsVirtualDevicesPayload $BuildDirectory $DriverDirectory $NativeHelper
Build-WindowsVirtualDevicesManaged -Output (Join-Path $OutputDirectory 'WindowsVirtualDevicesSetupConsole.exe') -Sources @((Join-Path $PSScriptRoot 'Program.cs'),(Join-Path $root 'Installer\UI\Package.cs'),(Join-Path $root 'Installer\UI\AssemblyInfo.cs')) -Resources @(($payload.Zip+',Payload.zip'),($payload.Hashes+',PayloadHashes.json')) -Console
$payload.Files|ConvertTo-Json|Set-Content -LiteralPath (Join-Path $OutputDirectory 'payload-manifest.json') -Encoding UTF8
Write-Host 'Built the single-file console installer. No driver was installed.'
