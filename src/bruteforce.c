/*
	PRT Bruteforce - Akshay Mohan.
	bruteforce.c
	
	Last Update - 10th of December, 2021.

	LICENSE:
	
	MIT License

Copyright (c) 2018-2021 Akshay Mohan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdlib.h>
#include <string.h>
#include "bruteforce.h"

int g_BRUTEFORCE_dataLen[16] = {

	0,
	33,
	10,
	43,
	26,
	59,
	36,
	69,
	26,
	59,
	36,
	69,
	52,
	85,
	62,
	95
};

char 
	g_BRUTEFORCE_bfSymbols[34] = " !\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"; 	//Used only if BF_FLAG_CUSTOM is used.

int bruteforce_init(BRUTEFORCE_HANDLE *bfHandle, size_t maxLen, BRUTEFORCE_FLAGS flags, const char *data, const char *startString) {

	size_t
			i,
			currLen = 0
	;
	if( (bfHandle->bfText = (char *)malloc((maxLen + 1)* sizeof(char))) == NULL) 
		return 0;

	if(flags & BF_FLAG_CUSTOM) {

		currLen = strlen(data);
		if( (bfHandle->bfData = (char *)malloc((currLen + 1) * sizeof(char))) == NULL) {

			free(bfHandle->bfText);
			return 0;
		}
		memcpy(bfHandle->bfData, data, currLen + 1);
	} else {

		if( (bfHandle->bfData = (char *)malloc((g_BRUTEFORCE_dataLen[flags] + 1) * sizeof(char))) == NULL) {

			free(bfHandle->bfText);
			return 0;
		}
		if(flags & BF_FLAG_UPPERCASE) {

			for(i = 0; i< 26; i++)
				bfHandle->bfData[i] 			= 	(char)(65 + i);
			currLen += 26;
		}
		if(flags & BF_FLAG_LOWERCASE) {

			for(i = 0; i< 26; i++)
				bfHandle->bfData[currLen + i] 	= 	(char)(97 + i);
			currLen += 26;
		}
		if(flags & BF_FLAG_DIGITS) {

			for(i = 0; i< 10; i++)
				bfHandle->bfData[currLen + i] 	= 	(char)(48 + i);
			currLen += 10;
		}
		if(flags & BF_FLAG_SYMBOLS) {

			memcpy(&bfHandle->bfData[currLen], g_BRUTEFORCE_bfSymbols, 33);
			currLen += 33;
		}
	}
	if( (bfHandle->bfCurrIdx = (size_t *)malloc(maxLen * sizeof(size_t))) == NULL) {

		free(bfHandle->bfText);
		free(bfHandle->bfData);

		return 0;
	}
	bfHandle->bfData[currLen]				=	'\0';
	bfHandle->bflastChar					=	bfHandle->bfData[currLen - 1];
	bfHandle->bfmaxLen						=	maxLen;
	if(startString != NULL && startString[0] != '\0') {

		bfHandle->bfUpdIdx = strlen(startString) - 1;
		memcpy(bfHandle->bfText, startString, bfHandle->bfUpdIdx + 1);
		for(currLen = 0; currLen <= bfHandle->bfUpdIdx; currLen++) {

			for(i = 0; bfHandle->bfText[currLen] != bfHandle->bfData[i]; i++);
			bfHandle->bfCurrIdx[currLen]			=	i;
		}
	} else {

		bfHandle->bfText[0] 						= 	bfHandle->bfData[0];
		bfHandle->bfUpdIdx							=	0;
		*(bfHandle->bfCurrIdx)						=	-1;
	}
	for(i = bfHandle->bfUpdIdx + 1; i<= maxLen; i++)
		bfHandle->bfText[i]							=	'\0';
	return 1;
}

int bruteforce_update(BRUTEFORCE_HANDLE *bfHandle) {

	size_t i = bfHandle->bfUpdIdx;
	while(i != (size_t)-1) {

		if(bfHandle->bfText[i] != bfHandle->bflastChar) {

			bfHandle->bfText[i] = bfHandle->bfData[++bfHandle->bfCurrIdx[i]];
			break;
		} else {

			bfHandle->bfText[i] = bfHandle->bfData[(bfHandle->bfCurrIdx[i] = 0)];
			i--;
		}
	}
	if(i == (size_t)-1) {

		if((bfHandle->bfUpdIdx + 1) < bfHandle->bfmaxLen)
#ifdef __cplusplus
			bfHandle->bfText[bfHandle->bfUpdIdx] = bfHandle->bfData[(bfHandle->bfCurrIdx[++bfHandle->bfUpdIdx] = 0)];
#else
			bfHandle->bfText[++bfHandle->bfUpdIdx] = bfHandle->bfData[(bfHandle->bfCurrIdx[bfHandle->bfUpdIdx] = 0)];
#endif
		else return 0;
	}
	return 1;
}

void bruteforce_finalize(BRUTEFORCE_HANDLE *bfHandle) {

	free(bfHandle->bfText);
	free(bfHandle->bfData);
	free(bfHandle->bfCurrIdx);
}
