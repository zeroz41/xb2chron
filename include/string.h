#ifndef STRING_H
#define STRING_H

// The C library's string functions, as the module imports them from NintendoSDK.
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* dest, const void* src, size_t count);
void* memmove(void* dest, const void* src, size_t count);
void* memset(void* dest, int value, size_t count);
int memcmp(const void* a, const void* b, size_t count);

size_t strlen(const char* text);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t count);
char* strcat(char* dest, const char* src);
int strcmp(const char* a, const char* b);
int strncmp(const char* a, const char* b, size_t count);
int strcasecmp(const char* a, const char* b);
int strncasecmp(const char* a, const char* b, size_t count);
char* strchr(const char* text, int c);
char* strrchr(const char* text, int c);
char* strstr(const char* text, const char* part);
char* strcasestr(const char* text, const char* part);
char* strtok(char* text, const char* separators);
char* strtok_r(char* text, const char* separators, char** rest);

#ifdef __cplusplus
}
#endif

#endif
