param([ValidateSet('All','Native','Installers','ExamplesUI','Tests')][string]$Target='All')
$ErrorActionPreference='Stop'
$root=$PSScriptRoot
$vswhere=Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
if(!(Test-Path -LiteralPath $vswhere)){throw 'Install Visual Studio 2022 Desktop development with C++ and a Windows SDK.'}
$vs=& $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if(!$vs){throw 'Visual Studio C++ x64 tools were not found.'}
$cmake=Join-Path $vs 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe'
if(!(Test-Path -LiteralPath $cmake)){$cmake=(Get-Command cmake.exe -ErrorAction Stop).Source}
$build=Join-Path $root 'obj\Native'
& $cmake -S $root -B $build -G 'Visual Studio 17 2022' -A x64
if($LASTEXITCODE){throw 'CMake configuration failed.'}
& $cmake --build $build --config Release --parallel
if($LASTEXITCODE){throw 'Native compilation failed.'}
& (Join-Path (Split-Path $cmake) 'ctest.exe') --test-dir $build -C Release --output-on-failure
if($LASTEXITCODE){throw 'Offline tests failed.'}
if($Target -in @('All','Installers')){
 $helper=Join-Path $root 'bin\Native\Release\WindowsVirtualDevicesSetupNative.exe'
 $driver=Join-Path $root 'InstallerUI\Package'
 $required=@('WindowsVirtualDevices.inf','WindowsVirtualDevices.sys','WindowsVirtualDevices.cat','DemoSessionClock.sys')
 $missing=@($required|Where-Object {!(Test-Path -LiteralPath (Join-Path $driver $_) -PathType Leaf)})
 if($missing.Count){
  if($Target -eq 'Installers'){throw ('Microsoft-signed package pending. Missing: '+($missing -join ', '))}
  Write-Host 'Installer build deferred: the new Microsoft-signed driver package has not returned yet.'
 }else{
  foreach($name in @('WindowsVirtualDevices.sys','DemoSessionClock.sys','WindowsVirtualDevices.cat')){
   $signature=Get-AuthenticodeSignature -LiteralPath (Join-Path $driver $name)
   if($signature.Status -ne 'Valid' -or !$signature.SignerCertificate -or $signature.SignerCertificate.Subject -notmatch 'CN=Microsoft Windows Hardware Compatibility Publisher(?:,|$)'){
    throw ('A valid Microsoft driver signature is required: '+$name)
   }
  }
  & (Join-Path $root 'InstallerConsole\Build.ps1') -DriverDirectory $driver -NativeHelper $helper
  & (Join-Path $root 'InstallerUI\Build.ps1') -DriverDirectory $driver -NativeHelper $helper
  & (Join-Path $root 'Tests\InstallerTests.ps1')
 }
}
if($Target -in @('All','ExamplesUI','Installers')){
 $bridge=Join-Path $root 'bin\ExamplesUI\Release\WindowsVirtualDevicesBridge.dll'
 & (Join-Path $root 'ExamplesUI\Build.ps1') -NativeBridge $bridge
 & (Join-Path $root 'Tests\WorkshopTests.ps1') -NativeBridge $bridge
}
Write-Host 'User-mode build and offline tests complete. No driver installed and no virtual device created.'
Write-Host 'The new driver package requires Microsoft signing before production installation.'
