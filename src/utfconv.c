/*******************************************************************************************

Function set for UTF StrLwr, StrUpr and case insensitive StrCmp and  StrStr

by Jan Bergström, Alphabet AB, 2021 Open source code

2021-10-21

*******************************************************************************************/
// #define UTF32_TEST 1
#include <stdlib.h>
#include <string.h>

#include <stdint.h>
#include "utftypes.h"
#include "utfcase.c"

// Utf 32
size_t StrLenUtf32(const Utf32Char *str);
Utf32Char *StrCpyUtf32(Utf32Char *dest, const Utf32Char *src);
Utf32Char *StrCatUtf32(Utf32Char *dest, const Utf32Char *src);
int StrnCmpUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2, size_t ztCount);
int StrCmpUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2);
Utf32Char *StrToUprUtf32(Utf32Char *pUtf32);
Utf32Char *StrToLwrUtf32(Utf32Char *pUtf32);
int StrnCiCmpUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2, size_t ztCount);
int StrCiCmpUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2);
Utf32Char *StrCiStrUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2);

// Utf 16
size_t StrLenUtf16(const Utf16Char *str);
Utf16Char *StrCpyUtf16(Utf16Char *dest, const Utf16Char *src);
Utf16Char *StrCatUtf16(Utf16Char *dest, const Utf16Char *src);
int StrnCmpUtf16(const Utf16Char *Utf16s1, const Utf16Char *Utf16s2, size_t ztCount);
int StrCmpUtf16(const Utf16Char *Utf16s1, const Utf16Char *Utf16s2);
size_t CharLenUtf16(const Utf16Char *pUtf16);
Utf16Char *ForwardUtf16Chars(const Utf16Char *pUtf16, size_t ztForwardUtf16Chars);
size_t StrLenUtf32AsUtf16(const Utf32Char *pUtf32);
Utf16Char *Utf32ToUtf16(const Utf32Char *pUtf32);
Utf32Char *Utf16ToUtf32(const Utf16Char *pUtf16);
Utf8Char *Utf16ToUtf8(const Utf16Char *pUtf16);
Utf16Char *Utf16StrMakeUprUtf16Str(const Utf16Char *pUtf16);
Utf16Char *Utf16StrMakeLwrUtf16Str(const Utf16Char *pUtf16);
int StrnCiCmpUtf16(const Utf16Char *pUtf16s1, const Utf16Char *pUtf16s2, size_t ztCount);
int StrCiCmpUtf16(const Utf16Char *pUtf16s1, const Utf16Char *pUtf16s2);
Utf16Char *StrCiStrUtf16(const Utf16Char *pUtf16s1, const Utf16Char *pUtf16s2);

// Utf 8
size_t StrLenUtf8(const Utf8Char *str);
int StrnCmpUtf8(const Utf8Char *Utf8s1, const Utf8Char *Utf8s2, size_t ztCount);
int StrCmpUtf8(const Utf8Char *Utf8s1, const Utf8Char *Utf8s2);
size_t CharLenUtf8(const Utf8Char *pUtf8);
Utf8Char *ForwardUtf8Chars(const Utf8Char *pUtf8, size_t ztForwardUtf8Chars);
size_t StrLenUtf32AsUtf8(const Utf32Char *pUtf32);
Utf8Char *Utf32ToUtf8(const Utf32Char *pUtf32);
Utf32Char *Utf8ToUtf32(const Utf8Char *pUtf8);
Utf16Char *Utf8ToUtf16(const Utf8Char *pUtf8);
Utf8Char *Utf8StrMakeUprUtf8Str(const Utf8Char *pUtf8);
Utf8Char *Utf8StrMakeLwrUtf8Str(const Utf8Char *pUtf8);
int StrnCiCmpUtf8(const Utf8Char *pUtf8s1, const Utf8Char *pUtf8s2, size_t ztCount);
int StrCiCmpUtf8(const Utf8Char *pUtf8s1, const Utf8Char *pUtf8s2);
Utf8Char *StrCiStrUtf8(const Utf8Char *pUtf8s1, const Utf8Char *pUtf8s2);

/*******************************************************************************************

UTF32 Upr/Lwr conversions

*******************************************************************************************/
Utf32Char *StrToUprUtf32(Utf32Char *pUtf32)
{
	Utf32Char *p = pUtf32;
	if (pUtf32 && *pUtf32)
	{
		while (*p)
		{
			if ((*p >= 0x61) && (*p <= 0x7a)) /* US ASCII */
				(*p) -= 0x20;
			else
			{
				(*p) = ExtCharToUprUtf32(*p);
			}
			p++;
		}
	}
	return pUtf32;
}
Utf32Char *StrToLwrUtf32(Utf32Char *pUtf32)
{
	Utf32Char *p = pUtf32;
	if (pUtf32 && *pUtf32)
	{
		while (*p)
		{
			if ((*p >= 0x41) && (*p <= 0x5a)) /* US ASCII */
				(*p) += 0x20;
			else
			{
				(*p) = ExtCharToLwrUtf32(*p);
			}
			p++;
		}
	}
	return pUtf32;
}
/*******************************************************************************************

UTF32

*******************************************************************************************/
size_t StrLenUtf32(const Utf32Char *str)
{
	Utf32Char *s;
	for (s = (Utf32Char *)str; *s; ++s)
		;
	return (s - str);
}
Utf32Char *StrCpyUtf32(Utf32Char *dest, const Utf32Char *src)
{
	return (Utf32Char *)memcpy(dest, src, (StrLenUtf32(src) + 1) * sizeof(Utf32Char));
}
Utf32Char *StrCatUtf32(Utf32Char *dest, const Utf32Char *src)
{
	return StrCpyUtf32(dest + StrLenUtf32(dest), src);
}
int StrnCmpUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2, size_t ztCount)
{
	if (Utf32s1 && *Utf32s1 && Utf32s2 && *Utf32s2)
	{
		for (; ztCount--; Utf32s1++, Utf32s2++)
		{
			int iDiff = *Utf32s1 - *Utf32s2;
			if (iDiff != 0 || !*Utf32s1 || !*Utf32s2)
				return iDiff;
		}
		return 0;
	}
	return (-1);
}
int StrnCiCmpUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2, size_t ztCount)
{
	Utf32Char *pStr1Low = 0;
	Utf32Char *pStr2Low = 0;
	int iResult = (-1);

	if (Utf32s1 && *Utf32s1 && Utf32s2 && *Utf32s2)
	{
		pStr1Low = (Utf32Char *)calloc(StrLenUtf32(Utf32s1) + 1, sizeof(Utf32Char));
		if (pStr1Low)
		{
			pStr2Low = (Utf32Char *)calloc(StrLenUtf32(Utf32s2) + 1, sizeof(Utf32Char));
			if (pStr2Low)
			{
				memcpy((Utf32Char *)pStr1Low, Utf32s1, StrLenUtf32(Utf32s1) * sizeof(Utf32Char));
				memcpy((Utf32Char *)pStr2Low, Utf32s2, StrLenUtf32(Utf32s2) * sizeof(Utf32Char));
				StrToLwrUtf32(pStr1Low);
				StrToLwrUtf32(pStr2Low);
				iResult = StrnCmpUtf32(pStr1Low, pStr2Low, ztCount);
				free(pStr1Low);
				free(pStr2Low);
			}
			else
				free(pStr1Low);
		}
	}
	return iResult;
}
int StrCmpUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2)
{
	return StrnCmpUtf32(Utf32s1, Utf32s2, (size_t)(-1));
}
int StrCiCmpUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2)
{
	return StrnCiCmpUtf32(Utf32s1, Utf32s2, (size_t)(-1));
}
Utf32Char *StrCiStrUtf32(const Utf32Char *Utf32s1, const Utf32Char *Utf32s2)
{
	Utf32Char *p = (Utf32Char *)Utf32s1;
	size_t len = 0;

	if (Utf32s1 && *Utf32s1 && Utf32s2 && *Utf32s2)
	{
		len = StrLenUtf32(Utf32s2);
		while (*p)
		{
			if (StrnCiCmpUtf32(p, Utf32s2, len) == 0)
				return (Utf32Char *)p;
			p++;
		}
	}
	return (0);
}
/*******************************************************************************************

UTF16

*******************************************************************************************/
size_t StrLenUtf16(const Utf16Char *str)
{
	Utf16Char *s;
	for (s = (Utf16Char *)str; *s; ++s)
		;
	return (s - str);
}
Utf16Char *StrCpyUtf16(Utf16Char *dest, const Utf16Char *src)
{
	return (Utf16Char *)memcpy(dest, src, (StrLenUtf16(src) + 1) * sizeof(Utf16Char));
}
Utf16Char *StrCatUtf16(Utf16Char *dest, const Utf16Char *src)
{
	return StrCpyUtf16(dest + StrLenUtf16(dest), src);
}
int StrnCmpUtf16(const Utf16Char *Utf16s1, const Utf16Char *Utf16s2, size_t ztCount)
{
	if (Utf16s1 && *Utf16s1 && Utf16s2 && *Utf16s2)
	{
		for (; ztCount--; Utf16s1++, Utf16s2++)
		{
			int iDiff = (int)(*Utf16s1 - *Utf16s2);
			if (iDiff != 0 || !*Utf16s1 || !*Utf16s2)
				return iDiff;
		}
		return 0;
	}
	return (-1);
}
int StrCmpUtf16(const Utf16Char *Utf16s1, const Utf16Char *Utf16s2)
{
	return StrnCmpUtf16(Utf16s1, Utf16s2, (size_t)(-1));
}
size_t CharLenUtf16(const Utf16Char *pUtf16)
{
	size_t ztUtf16 = 0;
	size_t ztNumUtf16Chars = 0;

	while (pUtf16[ztUtf16] != 0)
	{
		ztNumUtf16Chars++;

		if (!(((uint16_t)pUtf16[ztUtf16] - 0xd800u) < 0x800u))
			// 1 byte code point
			ztUtf16 += 1;
		else if ((((uint16_t)pUtf16[ztUtf16] & 0xfffffc00u) == 0xd800u) && ((((uint16_t)pUtf16[ztUtf16 + 1] & 0xfffffc00u) == 0xdc00u)))
			// 2 byte code point
			ztUtf16 += 2;
	}
	return ztNumUtf16Chars;
}
Utf16Char *ForwardUtf16Chars(const Utf16Char *pUtf16, size_t ztForwardUtf16Chars)
{
	size_t ztUtf16 = 0;
	size_t ztNumUtf16Chars = 0;

	while ((ztNumUtf16Chars < ztForwardUtf16Chars) && ((uint16_t)pUtf16[ztUtf16] != 0))
	{
		ztNumUtf16Chars++;
		if (!(((uint16_t)pUtf16[ztUtf16] - 0xd800u) < 0x800u))
			// 1 byte code point
			ztUtf16 += 1;
		else if ((((uint16_t)pUtf16[ztUtf16] & 0xfffffc00u) == 0xd800u) && ((((uint16_t)pUtf16[ztUtf16 + 1] & 0xfffffc00u) == 0xdc00u)))
			// 2 byte code point
			ztUtf16 += 2;
	}
	return (Utf16Char *)&pUtf16[ztUtf16];
}
size_t StrLenUtf32AsUtf16(const Utf32Char *pUtf32)
{
	size_t ztUtf32 = 0;
	size_t ztNumUtf16Chars = 0;
	while (pUtf32[ztUtf32] != 0)
	{
		if ((pUtf32[ztUtf32] >= 0x10000u) && (pUtf32[ztUtf32] <= 0x10FFFFu))
			// 2 byte code point
			ztNumUtf16Chars++;
		ztNumUtf16Chars++;
		ztUtf32++;
	}
	return ztNumUtf16Chars;
}
Utf16Char *Utf32ToUtf16(const Utf32Char *pUtf32)
{
	size_t ztUtf32 = 0;
	Utf16Char *pUtf16 = calloc(StrLenUtf32AsUtf16(pUtf32) + 1, sizeof(Utf16Char));
	if (pUtf16)
	{
		// https://datatracker.ietf.org/doc/html/rfc3629#page-4
		// This function skips data when UTF bytes are out of bounds
		while (pUtf32[ztUtf32] != 0)
		{
			if (pUtf32[ztUtf32] < 0x10000u)
				pUtf16[StrLenUtf16((const Utf16Char *)pUtf16)] = (Utf16Char)pUtf32[ztUtf32];
			else if (pUtf32[ztUtf32] <= 0x10FFFFu)
			{
				pUtf16[StrLenUtf16((const Utf16Char *)pUtf16)] = (Utf16Char)(((((uint32_t)pUtf32[ztUtf32] - 0x10000u) << 12) >> 22) + 0xD800u);
				pUtf16[StrLenUtf16((const Utf16Char *)pUtf16)] = (Utf16Char)(((((uint32_t)pUtf32[ztUtf32] - 0x10000u) << 22) >> 22) + 0xDC00u);
			}
			// else out of RFC3629 Utf16 bounds doing nothing
			ztUtf32++;
		}
		return pUtf16;
	}
	return 0;
}
Utf32Char *Utf16ToUtf32(const Utf16Char *pUtf16)
{
	size_t ztUtf16 = 0;
	size_t ztUtf32 = 0;
	Utf32Char *pUtf32 = calloc(CharLenUtf16(pUtf16) + 1, sizeof(Utf32Char));
	if (pUtf32)
	{
		// https://datatracker.ietf.org/doc/html/rfc3629#page-4
		// This function skips data when UTF bytes are out of bounds
		while ((uint16_t)pUtf16[ztUtf16] != 0)
		{
			if (!(((uint16_t)pUtf16[ztUtf16] - 0xd800u) < 0x800u))
			{ // The same just copy
				pUtf32[ztUtf32] = (uint16_t)pUtf16[ztUtf16];
				ztUtf16++;
			}
			else if ((((uint16_t)pUtf16[ztUtf16] & 0xfffffc00u) == 0xd800u) && ((((uint16_t)pUtf16[ztUtf16 + 1] & 0xfffffc00u) == 0xdc00u)))
			{
				pUtf32[ztUtf32] = ((uint16_t)pUtf16[ztUtf16] << 10) + (uint16_t)pUtf16[ztUtf16 + 1] - 0x35fdc00u;
				ztUtf16 += 2;
			}
			// else ERROR
			ztUtf32++;
		}
		return pUtf32;
	}
	return 0;
}
Utf8Char *Utf16ToUtf8(const Utf16Char *pUtf16)
{
	Utf32Char *pUtf32 = Utf16ToUtf32((const Utf16Char *)pUtf16);
	if (pUtf32)
	{
		Utf8Char *pUtf8 = Utf32ToUtf8((const Utf32Char *)pUtf32);
		free(pUtf32);
		if (pUtf8)
			return pUtf8;
		return 0;
	}
	return 0;
}
Utf16Char *Utf16StrMakeUprUtf16Str(const Utf16Char *pUtf16)
{
	Utf32Char *pUtf32 = Utf16ToUtf32(pUtf16);
	if (pUtf32 && *pUtf32)
	{
		StrToUprUtf32(pUtf32);
		{
			Utf16Char *pUtf16Upr = Utf32ToUtf16(pUtf32);
			free(pUtf32);
			return pUtf16Upr;
		}
	}
	return 0; // calloc() failure
}
Utf16Char *Utf16StrMakeLwrUtf16Str(const Utf16Char *pUtf16)
{
	Utf32Char *pUtf32 = Utf16ToUtf32(pUtf16);
	if (pUtf32 && *pUtf32)
	{
		StrToLwrUtf32(pUtf32);
		{
			Utf16Char *pUtf16Lwr = Utf32ToUtf16(pUtf32);
			free(pUtf32);
			return pUtf16Lwr;
		}
	}
	return 0; // calloc() failure
}
int StrnCiCmpUtf16(const Utf16Char *pUtf16s1, const Utf16Char *pUtf16s2, size_t ztCount)
{
	Utf32Char *pUtf32s1 = Utf16ToUtf32(pUtf16s1);
	if (pUtf32s1)
	{
		Utf32Char *pUtf32s2 = Utf16ToUtf32(pUtf16s2);
		if (pUtf32s2)
		{
			int iDiff = StrnCiCmpUtf32(pUtf32s1, pUtf32s2, ztCount);
			free(pUtf32s1);
			free(pUtf32s2);
			return iDiff;
		}
		free(pUtf32s1);
		return (-1); // calloc() failure
	}
	return (-1); // calloc() failure
}
int StrCiCmpUtf16(const Utf16Char *pUtf16s1, const Utf16Char *pUtf16s2)
{
	return StrnCiCmpUtf16(pUtf16s1, pUtf16s2, (size_t)(-1));
}
Utf16Char *StrCiStrUtf16(const Utf16Char *pUtf16s1, const Utf16Char *pUtf16s2)
{
	Utf32Char *pUtf32s1 = Utf16ToUtf32(pUtf16s1);
	if (pUtf32s1)
	{
		Utf32Char *pUtf32s2 = Utf16ToUtf32(pUtf16s2);
		Utf32Char *pUtf32Found = StrCiStrUtf32(pUtf32s1, pUtf32s2);
		if (pUtf32s2)
		{
			Utf16Char *pUtf16Found = 0;
			size_t ztSteps = pUtf32Found - pUtf32s1;
			if (pUtf32Found)
				pUtf16Found = ForwardUtf16Chars(pUtf16s1, ztSteps);
			free(pUtf32s1);
			free(pUtf32s2);
			return pUtf16Found;
		}
		free(pUtf32s1);
		return 0; // calloc() failure
	}
	return 0; // calloc() failure
}
/*******************************************************************************************

UTF8

*******************************************************************************************/
size_t StrLenUtf8(const Utf8Char *str)
{
	Utf8Char *s;
	for (s = (Utf8Char *)str; *s; ++s)
		;
	return (s - str);
}
int StrnCmpUtf8(const Utf8Char *Utf8s1, const Utf8Char *Utf8s2, size_t ztCount)
{
	if (Utf8s1 && *Utf8s1 && Utf8s2 && *Utf8s2)
	{
		for (; ztCount--; Utf8s1++, Utf8s2++)
		{
			int iDiff = *Utf8s1 - *Utf8s2;
			if (iDiff != 0 || !*Utf8s1 || !*Utf8s2)
				return iDiff;
		}
		return 0;
	}
	return (-1);
}
int StrCmpUtf8(const Utf8Char *Utf8s1, const Utf8Char *Utf8s2)
{
	return StrnCmpUtf8(Utf8s1, Utf8s2, (size_t)(-1));
}
size_t CharLenUtf8(const Utf8Char *pUtf8)
{
	size_t ztUtf8 = 0;
	size_t ztNumUtf8Chars = 0;

	while (pUtf8[ztUtf8] != 0)
	{
		ztNumUtf8Chars++;

		if ((pUtf8[ztUtf8] & 0b10000000) == 0)
			// 1 byte code point
			ztUtf8 += 1;
		else if ((pUtf8[ztUtf8] & 0b11100000) == 0b11000000)
			// 2 byte code point
			ztUtf8 += 2;
		else if ((pUtf8[ztUtf8] & 0b11110000) == 0b11100000)
			// 3 byte code point
			ztUtf8 += 3;
		else
			// 4 byte code point
			ztUtf8 += 4;
	}
	return ztNumUtf8Chars;
}
Utf8Char *ForwardUtf8Chars(const Utf8Char *pUtf8, size_t ztForwardUtf8Chars)
{
	size_t ztUtf8 = 0;
	size_t ztNumUtf8Chars = 0;

	while ((ztNumUtf8Chars < ztForwardUtf8Chars) && (pUtf8[ztUtf8] != 0))
	{
		ztNumUtf8Chars++;

		if ((pUtf8[ztUtf8] & 0b10000000) == 0)
			// 1 byte code point
			ztUtf8 += 1;
		else if ((pUtf8[ztUtf8] & 0b11100000) == 0b11000000)
			// 2 byte code point
			ztUtf8 += 2;
		else if ((pUtf8[ztUtf8] & 0b11110000) == 0b11100000)
			// 3 byte code point
			ztUtf8 += 3;
		else
			// 4 byte code point
			ztUtf8 += 4;
	}
	return (Utf8Char *)&pUtf8[ztUtf8];
}
size_t StrLenUtf32AsUtf8(const Utf32Char *pUtf32)
{
	size_t ztUtf32 = 0;
	size_t ztNumUtf8Chars = 0;
	while (pUtf32[ztUtf32] != 0)
	{
		if (pUtf32[ztUtf32] >= 0x10000u)
			ztNumUtf8Chars += 3;
		else if (pUtf32[ztUtf32] >= 0x800u)
			ztNumUtf8Chars += 2;
		else if (pUtf32[ztUtf32] >= 0x80u)
			ztNumUtf8Chars += 1;
		ztNumUtf8Chars++;
		ztUtf32++;
	}
	return ztNumUtf8Chars;
}
Utf8Char *Utf32ToUtf8(const Utf32Char *pUtf32)
{
	size_t ztUtf32 = 0;
	Utf8Char *pUtf8 = calloc(StrLenUtf32AsUtf8(pUtf32) + 1, sizeof(Utf8Char));
	if (pUtf8)
	{
		// https://datatracker.ietf.org/doc/html/rfc3629#page-4
		// This function skips data when UTF bytes are out of bounds
		while (pUtf32[ztUtf32] != 0)
		{
			if (pUtf32[ztUtf32] <= 0x7Fu)
			{
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)pUtf32[ztUtf32];
			}
			else if (pUtf32[ztUtf32] <= 0x7FFu)
			{
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)(0xC0u | (pUtf32[ztUtf32] >> 6));		/* 110xxxxx */
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)(0x80u | (pUtf32[ztUtf32] & 0x3Fu)); /* 10xxxxxx */
			}
			else if (pUtf32[ztUtf32] <= 0xFFFFu)
			{
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)(0xE0u | (pUtf32[ztUtf32] >> 12));					 /* 1110xxxx */
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)(0x80u | ((pUtf32[ztUtf32] >> 6) & 0x3Fu)); /* 10xxxxxx */
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)(0x80u | (pUtf32[ztUtf32] & 0x3Fu));				 /* 10xxxxxx */
			}
			else if (pUtf32[ztUtf32] <= 0x10FFFFu)
			{
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)(0xF0u | (pUtf32[ztUtf32] >> 18));						/* 11110xxx */
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)(0x80u | ((pUtf32[ztUtf32] >> 12) & 0x3Fu)); /* 10xxxxxx */
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)(0x80u | ((pUtf32[ztUtf32] >> 6) & 0x3Fu));	/* 10xxxxxx */
				pUtf8[StrLenUtf8((const Utf8Char *)pUtf8)] = (Utf8Char)(0x80u | (pUtf32[ztUtf32] & 0x3Fu));					/* 10xxxxxx */
			}
			// else out of RFC3629 UTF8 bounds doing nothing
			ztUtf32++;
		}
		return pUtf8;
	}
	return 0;
}
Utf32Char *Utf8ToUtf32(const Utf8Char *pUtf8)
{
	size_t ztUtf8 = 0;
	size_t ztUtf32 = 0;
	Utf32Char *pUtf32 = calloc(CharLenUtf8(pUtf8) + 1, sizeof(Utf32Char));
	if (pUtf32)
	{
		// https://datatracker.ietf.org/doc/html/rfc3629#page-4
		// This function skips data when UTF bytes are out of bounds
		while (pUtf8[ztUtf8] != 0)
		{
			if ((pUtf8[ztUtf8] & 0b10000000) == 0)
			{
				// 1 byte code point, ASCII
				pUtf32[ztUtf32] = (pUtf8[ztUtf8] & 0b01111111);
				ztUtf8 += 1;
			}
			else if ((pUtf8[ztUtf8] & 0b11100000) == 0b11000000)
			{
				// 2 byte code point
				pUtf32[ztUtf32] = (pUtf8[ztUtf8] & 0b00011111) << 6 | (pUtf8[ztUtf8 + 1] & 0b00111111);
				if (pUtf32[ztUtf32] < 0x80u)			 // Not a valid result, Wrong encoding
					pUtf32[ztUtf32] = 0;						 // Out of UTF8 bound, skip data
				else if (pUtf32[ztUtf32] > 0x7ffu) // Not a valid result, Wrong encoding
					pUtf32[ztUtf32] = 0;						 // Out of UTF8 bound, skip data
				ztUtf8 += 2;
			}
			else if ((pUtf8[ztUtf8] & 0b11110000) == 0b11100000)
			{
				// 3 byte code point
				pUtf32[ztUtf32] = (pUtf8[ztUtf8] & 0b00001111) << 12 | (pUtf8[ztUtf8 + 1] & 0b00111111) << 6 | (pUtf8[ztUtf8 + 2] & 0b00111111);
				if (pUtf32[ztUtf32] < 0x800u)				// Not a valid result, Wrong encoding
					pUtf32[ztUtf32] = 0;							// Out of UTF8 bound, skip data
				else if (pUtf32[ztUtf32] > 0xffffu) // Not a valid result, Wrong encoding
					pUtf32[ztUtf32] = 0;							// Out of UTF8 bound, skip data
				ztUtf8 += 3;
			}
			else
			{
				// 4 byte code point
				if (pUtf8[ztUtf8] <= 0xf4u) // RFC3629 UTF8 do not allow larger values
					pUtf32[ztUtf32] = (pUtf8[ztUtf8] & 0b00000111) << 18 | (pUtf8[ztUtf8 + 1] & 0b00111111) << 12 | (pUtf8[ztUtf8 + 2] & 0b00111111) << 6 | (pUtf8[ztUtf8 + 3] & 0b00111111);
				else																	// Not a valid result, Wrong encoding
					pUtf32[ztUtf32] = 0;								// Out of UTF8 bound, skip data
				if (pUtf32[ztUtf32] < 0x10000u)				// Not a valid result, Wrong encoding
					pUtf32[ztUtf32] = 0;								// Out of UTF8 bound, skip data
				else if (pUtf32[ztUtf32] > 0x10FFFFu) // Not a valid result, Wrong encoding
					pUtf32[ztUtf32] = 0;								// Out of UTF8 bound, skip data
				ztUtf8 += 4;
			}
			if (pUtf32[ztUtf32]) // Only step when valid data
				ztUtf32++;
		}
		return pUtf32;
	}
	return 0;
}
Utf16Char *Utf8ToUtf16(const Utf8Char *pUtf8)
{
	Utf32Char *pUtf32 = Utf8ToUtf32((const Utf8Char *)pUtf8);
	if (pUtf32)
	{
		Utf16Char *pUtf16 = Utf32ToUtf16((const Utf32Char *)pUtf32);
		free(pUtf32);
		if (pUtf16)
			return pUtf16;
		return 0;
	}
	return 0;
}
Utf8Char *Utf8StrMakeUprUtf8Str(const Utf8Char *pUtf8)
{
	Utf32Char *pUtf32 = Utf8ToUtf32(pUtf8);
	if (pUtf32 && *pUtf32)
	{
		StrToUprUtf32(pUtf32);
		{
			Utf8Char *pUtf8Upr = Utf32ToUtf8(pUtf32);
			free(pUtf32);
			return pUtf8Upr;
		}
	}
	return 0; // calloc() failure
}
Utf8Char *Utf8StrMakeLwrUtf8Str(const Utf8Char *pUtf8)
{
	Utf32Char *pUtf32 = Utf8ToUtf32(pUtf8);
	if (pUtf32 && *pUtf32)
	{
		StrToLwrUtf32(pUtf32);
		{
			Utf8Char *pUtf8Lwr = Utf32ToUtf8(pUtf32);
			free(pUtf32);
			return pUtf8Lwr;
		}
	}
	return 0; // calloc() failure
}
int StrnCiCmpUtf8(const Utf8Char *pUtf8s1, const Utf8Char *pUtf8s2, size_t ztCount)
{
	Utf32Char *pUtf32s1 = Utf8ToUtf32(pUtf8s1);
	if (pUtf32s1)
	{
		Utf32Char *pUtf32s2 = Utf8ToUtf32(pUtf8s2);
		if (pUtf32s2)
		{
			int iDiff = StrnCiCmpUtf32(pUtf32s1, pUtf32s2, ztCount);
			free(pUtf32s1);
			free(pUtf32s2);
			return iDiff;
		}
		free(pUtf32s1);
		return (-1); // calloc() failure
	}
	return (-1); // calloc() failure
}
int StrCiCmpUtf8(const Utf8Char *pUtf8s1, const Utf8Char *pUtf8s2)
{
	return StrnCiCmpUtf8(pUtf8s1, pUtf8s2, (size_t)(-1));
}
Utf8Char *StrCiStrUtf8(const Utf8Char *pUtf8s1, const Utf8Char *pUtf8s2)
{
	Utf32Char *pUtf32s1 = Utf8ToUtf32(pUtf8s1);
	if (pUtf32s1)
	{
		Utf32Char *pUtf32s2 = Utf8ToUtf32(pUtf8s2);
		Utf32Char *pUtf32Found = StrCiStrUtf32(pUtf32s1, pUtf32s2);
		if (pUtf32s2)
		{
			Utf8Char *pUtf8Found = 0;
			size_t ztSteps = pUtf32Found - pUtf32s1;
			if (pUtf32Found)
				pUtf8Found = ForwardUtf8Chars(pUtf8s1, ztSteps);
			free(pUtf32s1);
			free(pUtf32s2);
			return pUtf8Found;
		}
		free(pUtf32s1);
		return 0; // calloc() failure
	}
	return 0; // calloc() failure
}
#ifdef UTF32_TEST
/******************/
/* Test functions */
/******************/
#include <stdio.h>
size_t FileWrite(char *pFileName, char *pBuffer)
{
	/* Open the file on disk */
	FILE *pFile = fopen((const char *)pFileName, (const char *)"wb");
	if (!pFile)
		return 0; /* File not found or opened */
	{
		size_t ztWritten = fwrite(pBuffer, sizeof(char), StrLenUtf8(pBuffer), pFile);
		fclose(pFile);
		return ztWritten;
	}
}

int main(void)
{

	Utf8Char Base8[] = {"Text ÆÇÈ𐒷𐒶𐐝ＴꞫ123ÉêßꞵëìíîïðÑÒÓÔÕÖØÙÚÛÜÝÞĀĂĄ"};
	Utf8Char Target8[] = {"𐓞𐑅ＴꞫ123éêßꞵë"};
	Utf8Char Copy8[] = {"Hello 𐓞𐑅ＴꞫ123éêßꞵë123"};
	Utf8Char *pLwr8 = Utf8StrMakeLwrUtf8Str(Base8);
	Utf8Char *pUpr8 = Utf8StrMakeUprUtf8Str(pLwr8);
	Utf8Char *pLwr8B = Utf8StrMakeLwrUtf8Str(pUpr8);
	int iDiff8 = StrnCiCmpUtf8(pLwr8, pUpr8, 2);
	int iDiff8B = StrCiCmpUtf8(pLwr8, pUpr8);
	Utf8Char *pSearch8 = StrCiStrUtf8(Base8, Target8);

	Utf16Char *pBase16 = Utf8ToUtf16(Base8);
	Utf16Char *pTarget16 = Utf8ToUtf16(Target8);
	Utf16Char *pLwr16 = Utf16StrMakeLwrUtf16Str(pBase16);
	Utf16Char *pUpr16 = Utf16StrMakeUprUtf16Str(pLwr16);
	Utf16Char *pLwr16B = Utf16StrMakeLwrUtf16Str(pUpr16);
	int iDiff16 = StrnCiCmpUtf16(pLwr16, pUpr16, 2);
	int iDiff16B = StrCiCmpUtf16(pLwr16, pUpr16);
	Utf16Char *pSearch16 = StrCiStrUtf16(pBase16, pTarget16);

	Utf16Char *pCopy16 = Utf8ToUtf16(Copy8);
	Utf16Char *pCopyTest16 = calloc(200, sizeof(Utf16Char));
	StrCpyUtf16(pCopyTest16, pTarget16);
	StrCpyUtf16(pCopyTest16, pCopy16);
	StrCatUtf16(pCopyTest16, pTarget16);

	Utf32Char *pTarget32 = Utf8ToUtf32(Target8);
	Utf32Char *pCopy32 = Utf8ToUtf32(Copy8);
	Utf32Char *pCopyTest32 = calloc(200, sizeof(Utf32Char));
	StrCpyUtf32(pCopyTest32, pTarget32);
	StrCpyUtf32(pCopyTest32, pCopy32);
	StrCatUtf32(pCopyTest32, pTarget32);

	Utf8Char *pBase16_8 = Utf16ToUtf8(pBase16);
	Utf8Char *pLwr16_8 = Utf16ToUtf8(pLwr16);
	Utf8Char *pUpr16_8 = Utf16ToUtf8(pUpr16);
	Utf8Char *pLwr16B_8 = Utf16ToUtf8(pLwr16B);
	Utf8Char *pTarget16_8 = Utf16ToUtf8(pTarget16);
	Utf8Char *pSearch16_8 = Utf16ToUtf8(pSearch16);

	Utf8Char *pCopy16_8 = Utf16ToUtf8(pCopy16);
	Utf8Char *pCopyTest16_8 = Utf16ToUtf8(pCopyTest16);
	Utf8Char *pCopy32_8 = Utf32ToUtf8(pCopy32);
	Utf8Char *pCopyTest32_8 = Utf32ToUtf8(pCopyTest32);

	char Buffer[10000];
	sprintf(Buffer, "\xEF\xBB\xBF\nBase8  = %s\nBase16 = %s\npUpr8  = %s\npUpr16 = %s\npLwr8  = %s\npLwr8B = %s\npLwr16 = %s\npLwr16B= %s\npTarget8  = %s\npTarget16 = %s\npSearch8  = %s\npSearch16 = %s\nDiff8 = %i\nDiff8b = %i\nDiff16 = %i\nDiff16b = %i\npCopy16_8  = %s\npCopyTest16_8  = %s\npCopy32_8  = %s\npCopyTest32_8  = %s\n",
					Base8, pBase16_8, pUpr8, pUpr16_8, pLwr8, pLwr8B, pLwr16_8, pLwr16B_8, Target8, pTarget16_8, pSearch8, pSearch16_8, iDiff8, iDiff8B, iDiff16, iDiff16B, pCopy16_8, pCopyTest16_8, pCopy32_8, pCopyTest32_8);
	printf("% s", Buffer);
	FileWrite("UTF8_checked.txt", Buffer);
	free(pLwr8);
	free(pUpr8);
	free(pLwr8B);

	free(pBase16);
	free(pTarget16);
	free(pLwr16);
	free(pUpr16);
	free(pLwr16B);

	free(pBase16_8);
	free(pLwr16_8);
	free(pUpr16_8);
	free(pLwr16B_8);
	free(pTarget16_8);
	free(pSearch16_8);

	free(pCopy16);
	free(pCopyTest16);
	free(pCopy32);
	free(pCopyTest32);
	free(pCopy16_8);
	free(pCopyTest16_8);
	free(pCopy32_8);
	free(pCopyTest32_8);

	return 0;
}
#endif
