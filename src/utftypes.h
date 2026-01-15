#ifndef UTFTYPES_H
#define UTFTYPES_H
#include <stdlib.h>

#define Utf32Char uint32_t     // min 4 bytes (int32_t), uint32_t suggested
#define Utf16Char wchar_t      // min 2 bytes (int16_t), wchar_t suggested
#define Utf8Char unsigned char // must be 1 byte, 8 bits, can be char, the UTF consortium specify unsigned

#endif