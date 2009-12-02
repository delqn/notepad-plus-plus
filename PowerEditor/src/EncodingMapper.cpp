//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "precompiledHeaders.h"
#include "EncodingMapper.h"

// Don't change the order
EncodingUnit encodings[] = {
    {1250,  "windows-1250"},                                                                    //IDM_FORMAT_WIN1250
    {1251,  "windows-1251"},                                                                    //IDM_FORMAT_WIN1251
    {1252,  "windows-1252"},                                                                    //IDM_FORMAT_WIN1252
    {1253,  "windows-1253"},                                                                    //IDM_FORMAT_WIN1253
    {1254,  "windows-1254"},                                                                    //IDM_FORMAT_WIN1254
    {1255,  "windows-1255"},                                                                    //IDM_FORMAT_WIN1255
    {1256,  "windows-1256"},                                                                    //IDM_FORMAT_WIN1256
    {1257,  "windows-1257"},                                                                    //IDM_FORMAT_WIN1257
    {1258,  "windows-1258"},                                                                    //IDM_FORMAT_WIN1258
    {28591, "latin1 ISO_8859-1 ISO-8859-1 CP819 IBM819 csISOLatin1 iso-ir-100 l1"},             //IDM_FORMAT_ISO_8859_1 
    {28592, "latin2 ISO_8859-2 ISO-8859-2 csISOLatin2 iso-ir-101 l2"},                          //IDM_FORMAT_ISO_8859_2 
    {28593, "latin3 ISO_8859-3 ISO-8859-3 csISOLatin3 iso-ir-109 l3"},                          //IDM_FORMAT_ISO_8859_3 
    {28594, "latin4 ISO_8859-4 ISO-8859-4 csISOLatin4 iso-ir-110 l4"},                          //IDM_FORMAT_ISO_8859_4 
    {28595, "cyrillic ISO_8859-5 ISO-8859-5 csISOLatinCyrillic iso-ir-144"},                    //IDM_FORMAT_ISO_8859_5 
    {28596, "arabic ISO_8859-6 ISO-8859-6 csISOLatinArabic iso-ir-127 ASMO-708 ECMA-114"},      //IDM_FORMAT_ISO_8859_6 
    {28597, "greek ISO_8859-7 ISO-8859-7 csISOLatinGreek greek8 iso-ir-126 ELOT_928 ECMA-118"}, //IDM_FORMAT_ISO_8859_7 
    {28598, "hebrew ISO_8859-8 ISO-8859-8 csISOLatinHebrew iso-ir-138"},                        //IDM_FORMAT_ISO_8859_8 
    {28599, "latin5 ISO_8859-9 ISO-8859-9 csISOLatin5 iso-ir-148 l5"},                          //IDM_FORMAT_ISO_8859_9 
    {28600, "latin6 ISO_8859-10 ISO-8859-10 csISOLatin6 iso-ir-157 l6"},                        //IDM_FORMAT_ISO_8859_10
    {28601, "ISO_8859-11 ISO-8859-11"},                                                         //IDM_FORMAT_ISO_8859_11
    {28603, "ISO_8859-13 ISO-8859-13"},                                                         //IDM_FORMAT_ISO_8859_13
    {28604, "iso-celtic latin8 ISO_8859-14 ISO-8859-14 18 iso-ir-199"},                         //IDM_FORMAT_ISO_8859_14
    {28605, "Latin-9 ISO_8859-15 ISO-8859-15"},                                                 //IDM_FORMAT_ISO_8859_15
    {28606, "latin10 ISO_8859-16 ISO-8859-16 110 iso-ir-226"},                                  //IDM_FORMAT_ISO_8859_16
    {950,   "big5 csBig5"},                                                                     //IDM_FORMAT_BIG5
    {936,   "gb2312 gbk csGB2312"},                                                             //IDM_FORMAT_GB2312
    {932,   "Shift_JIS MS_Kanji csShiftJIS csWindows31J"},                                      //IDM_FORMAT_SHIFT_JIS
    {949,   "windows-949 korean"},                                                              //IDM_FORMAT_KOREAN_WIN
    {51949, "euc-kr csEUCKR"},                                                                  //IDM_FORMAT_EUC_KR
    {874,   "tis-620"},                                                                         //IDM_FORMAT_TIS_620
    {855,   "IBM855 cp855 855 csIBM855"},                                                       //IDM_FORMAT_CP855
    {10007, "x-mac-cyrillic xmaccyrillic"},                                                     //IDM_FORMAT_MAC_CYRILLIC
    {21866, "koi8_u"},                                                                          //IDM_FORMAT_KOI8U_CYRILLIC
    {20866, "koi8_r csKOI8R"},                                                                  //IDM_FORMAT_KOI8R_CYRILLIC
    {437,   "IBM437, cp437 437 csPC8CodePage437"},                                              //IDM_FORMAT_DOS437
	{367,   "ASCII US-ASCII us ISO646-US csASCII cp367 IBM367"}                                 //IDM_FORMAT_US_ASCII
};

EncodingMapper * EncodingMapper::_pSelf = new EncodingMapper;

bool isInListA(const char *token, const char *list) {
	if ((!token) || (!list))
		return false;
	char word[64];
	int i = 0;
	int j = 0;
	for (; i <= int(strlen(list)) ; i++)
	{
		if ((list[i] == ' ')||(list[i] == '\0'))
		{
			if (j != 0)
			{
				word[j] = '\0';
				j = 0;
				
				if (!stricmp(token, word))
					return true;
			}
		}
		else 
		{
			word[j] = list[i];
			j++;
		}
	}
	return false;
};

int EncodingMapper::getEncodingFromIndex(int index) const
{
	size_t nbItem = sizeof(encodings)/sizeof(EncodingUnit);
	if (index < 0 || (size_t)index >= nbItem)
		return -1;
	return encodings[index]._codePage;
}

int EncodingMapper::getIndexFromEncoding(int encoding) const
{
	bool found = false;
	size_t nbItem = sizeof(encodings)/sizeof(EncodingUnit);
	size_t i = 0;
	for ( ; i < nbItem ; i++)
	{
		if (encodings[i]._codePage == encoding)
		{
			found = true;
			break;
		}
	}
	return found?i:-1;
}

int EncodingMapper::getEncodingFromString(const char *encodingAlias) const
{
	size_t nbItem = sizeof(encodings)/sizeof(EncodingUnit);
	int enc = -1;
	for (size_t i = 0 ; i < nbItem ; i++)
	{
		if (isInListA(encodingAlias, encodings[i]._aliasList))
		{
			enc = encodings[i]._codePage;
			break;
		}
	}
	return enc;
}