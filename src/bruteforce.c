/*
	PRT Bruteforce - Akshay Mohan.
	bruteforce.c
	
	LICENSE:
	
	MIT License

Copyright (c) 2018 Akshay Mohan

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

#if defined __cplusplus
extern "C" {
#endif

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

int bruteforce_init(BRUTEFORCE_HANDLE *bfHandle, unsigned int maxLen, BRUTEFORCE_FLAGS flags, char *data, char *startString) {

	unsigned int
					i,
					currLen = 0
	;
	if( (bfHandle->bfText = (char *)malloc(maxLen * sizeof(char))) == NULL) 
		return 0;

	if(flags & BF_FLAG_CUSTOM) {

		currLen = strlen(data);
		if( (bfHandle->bfData = (char *)malloc(currLen * sizeof(char))) == NULL) {

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
				bfHandle->bfData[i] 			= 	65 + i;
			currLen += 26;
		}
		if(flags & BF_FLAG_LOWERCASE) {

			for(i = 0; i< 26; i++)
				bfHandle->bfData[currLen + i] 	= 	97 + i;
			currLen += 26;
		}
		if(flags & BF_FLAG_DIGITS) {

			for(i = 0; i< 10; i++)
				bfHandle->bfData[currLen + i] 	= 	48 + i;
			currLen += 10;
		}
		if(flags & BF_FLAG_SYMBOLS) {

			memcpy(&bfHandle->bfData[currLen], g_BRUTEFORCE_bfSymbols, 33);
			currLen += 33;
		}
	}
	if( (bfHandle->bfCurrIdx = (unsigned int *)malloc(maxLen * sizeof(unsigned int))) == NULL) {

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
		for(currLen = 0; currLen < maxLen; currLen++) {

			for(i = 0; bfHandle->bfText[currLen] != bfHandle->bfData[i]; i++);
			bfHandle->bfCurrIdx[currLen]			=	i;
		}
	} else {

		bfHandle->bfText[0] 						= 	bfHandle->bfData[0];
		bfHandle->bfUpdIdx							=	0;
		*(bfHandle->bfCurrIdx)						=	-1;
	}
	for(i = bfHandle->bfUpdIdx + 1; i< maxLen; i++)
		bfHandle->bfText[i]							=	'\0';
	return 1;
}

int bruteforce_update(BRUTEFORCE_HANDLE *bfHandle) {

	int i = bfHandle->bfUpdIdx, j = -1;
	while(i >= 0) {

		if(bfHandle->bfText[i] != bfHandle->bflastChar) {

			bfHandle->bfText[i]			=	bfHandle->bfData[(j = bfHandle->bfCurrIdx[i]++ + 1)];
			break;
		} else
			bfHandle->bfText[i]			=	bfHandle->bfData[(bfHandle->bfCurrIdx[i--] = 0)];
	}
	if(j == -1) {

		if(strlen(bfHandle->bfText) < bfHandle->bfmaxLen)
			bfHandle->bfText[++bfHandle->bfUpdIdx]			=	bfHandle->bfData[(bfHandle->bfCurrIdx[bfHandle->bfUpdIdx] = 0)];
		else return 0;
	}
	return 1;
}

void bruteforce_finalize(BRUTEFORCE_HANDLE *bfHandle) {

	free(bfHandle->bfText);
	free(bfHandle->bfData);
	free(bfHandle->bfCurrIdx);
}

#if defined __cplusplus
}
#endif
