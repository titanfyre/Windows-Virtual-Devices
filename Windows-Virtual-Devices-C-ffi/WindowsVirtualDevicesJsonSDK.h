/* SPDX-License-Identifier: MIT */
#ifndef WINDOWS_VIRTUAL_DEVICES_CSDK_H
#define WINDOWS_VIRTUAL_DEVICES_CSDK_H
#include <stdint.h>
#if !defined(_WIN32) || !defined(_WIN64)
#error This SDK requires Windows x64.
#endif
#ifdef __cplusplus
#define WINDOWS_VIRTUAL_DEVICES_CSDK_NOEXCEPT noexcept
extern "C" {
#else
#define WINDOWS_VIRTUAL_DEVICES_CSDK_NOEXCEPT
#endif
#if defined(WINDOWS_VIRTUAL_DEVICES_CSDK_BUILD)
#define WINDOWS_VIRTUAL_DEVICES_CSDK_API __declspec(dllexport)
#else
#define WINDOWS_VIRTUAL_DEVICES_CSDK_API __declspec(dllimport)
#endif
/* open is inert. One active session per loaded product DLL.
   call accepts length-delimited UTF-8 JSON and returns an allocated UTF-8
   response, or NULL on allocation failure. Always free with this same DLL.
   Session/operation handles are scoped to the client that returned them. */
WINDOWS_VIRTUAL_DEVICES_CSDK_API uint32_t windows_virtual_devices_json_open(uint64_t *session) WINDOWS_VIRTUAL_DEVICES_CSDK_NOEXCEPT;
WINDOWS_VIRTUAL_DEVICES_CSDK_API uint32_t windows_virtual_devices_json_close(uint64_t session) WINDOWS_VIRTUAL_DEVICES_CSDK_NOEXCEPT;
WINDOWS_VIRTUAL_DEVICES_CSDK_API char *windows_virtual_devices_json_call(uint64_t session,const char *request,uint32_t length) WINDOWS_VIRTUAL_DEVICES_CSDK_NOEXCEPT;
WINDOWS_VIRTUAL_DEVICES_CSDK_API void windows_virtual_devices_json_free(char *response) WINDOWS_VIRTUAL_DEVICES_CSDK_NOEXCEPT;
#ifdef __cplusplus
}
#endif
#undef WINDOWS_VIRTUAL_DEVICES_CSDK_NOEXCEPT
#endif
