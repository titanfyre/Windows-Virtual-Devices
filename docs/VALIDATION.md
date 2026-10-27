# Validation and supported scope

WindowsVirtualDevices 0.1.0.0 has a matching Microsoft-signed return. Its catalog memberships, unchanged INF files and protected executable content have been verified against the submitted candidate. Installer builds and offline resource/state checks pass.

The live results below used guest-local test-signed copies of the same submitted image in disposable Hyper-V guests. This signed-return integration has not repeated the full installation/device lifecycle with the returned installers; physical-hardware and that final runtime validation remain pending.

## Live checks

- Windows 11, build 26200: installation, status, all five virtual-device examples
  and removal passed with standard Driver Verifier targeting
  WindowsVirtualDevices.sys and DemoSessionClock.sys.
- Windows 10, build 19045: the same five-example sequence passed in normal mode.
- The sequence checks keyboard/mouse report consumption by the USB stack, DS4
  HID state/features/output, Xbox 360 and GIP XInput states and rumble, 2,000-update
  bursts and neutral release. Desktop typing, every application and physical
  controller compatibility are not established by these software-only checks.

### Recorded Windows 10 Verifier limitation

With I/O verification enabled, Windows 10's xusb22.sys version 10.0.19041.6389
produced bugcheck C9/7 while completing a pending state request during virtual
Xbox 360 surprise removal. The Xbox state, rumble and burst assertions completed
before the failure. Dumps identify xusb22's cleanupWaitingRequests and its still-set
WaitAndUnfilteredRequestCancelRoutine; the same failure bucket appears in older
laboratory dumps predating this edition. This condition remains unresolved and
must not be represented as a clean Windows 10 Verifier result. Windows 10 normal
mode and the tested Windows 11 Verifier run passed; neither proves universal
lifecycle compatibility.

Offline checks cover descriptor construction, raw protocol state machines,
installer ownership helpers, payload validation and SDK endpoint selection.
Normal example execution is reserved for the signed package or an isolated test VM.
No unsigned package should be installed on a normal user's PC.

The driver uses KMDF and UdeCx with USB low/full/high speed. It supports one
configuration, alternate setting zero and interrupt/bulk endpoints. SuperSpeed,
isochronous audio, external hubs and extra configurations are not implemented.
VID/PID changes alone do not reproduce firmware or console authentication.

The public API is Check, Status, Connect, Disconnect, Send, Receive and Reply.
Send(device, bytes) resolves exactly one declared IN endpoint at creation. For
devices with multiple IN endpoints, use the explicit endpoint overload.
