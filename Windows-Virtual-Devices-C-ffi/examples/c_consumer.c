#include "WindowsVirtualDevicesJsonSDK.h"
#include <string.h>
int main(void){uint64_t session=0;if(windows_virtual_devices_json_open(&session))return 1;char *reply=windows_virtual_devices_json_call(session,"{",1);if(!reply){windows_virtual_devices_json_close(session);return 2;}int failed=strstr(reply,"\"ok\":false")==0;windows_virtual_devices_json_free(reply);if(windows_virtual_devices_json_close(session))return 3;return failed;}
