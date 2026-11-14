#ifndef ERRNO_H
#define ERRNO_H

// The C library's errno, as the module imports it from NintendoSDK.
#ifdef __cplusplus
extern "C" {
#endif

int* __errno_location(void);

#ifdef __cplusplus
}
#endif

#define errno (*__errno_location())
#define ENOMEM 12

#endif
