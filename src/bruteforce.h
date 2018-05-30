/*
	PRT Bruteforce - Akshay Mohan.
	bruteforce.h

	Last Update - 31st of May, 2018.

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

#ifndef PRTBRUTEFORCE_H
#define PRTBRUTEFORCE_H

#define		BF_FLAG_ALL				(BRUTEFORCE_FLAGS)(BF_FLAG_UPPERCASE | BF_FLAG_LOWERCASE | BF_FLAG_DIGITS | BF_FLAG_SYMBOLS)
#define		BF_FLAG_ALPHANUMERIC	(BRUTEFORCE_FLAGS)(BF_FLAG_UPPERCASE | BF_FLAG_LOWERCASE | BF_FLAG_DIGITS)
#define 	BF_FLAG_LETTERS			(BRUTEFORCE_FLAGS)(BF_FLAG_UPPERCASE | BF_FLAG_LOWERCASE)
#define		BF_FLAG_ALPHANUM 		BF_FLAG_ALPHANUMERIC

enum BRUTEFORCE_FLAGS {

	BF_FLAG_SYMBOLS			=	1,
	BF_FLAG_DIGITS			=	2,
	BF_FLAG_LOWERCASE		=	4,
	BF_FLAG_UPPERCASE		=	8,
	BF_FLAG_CUSTOM			=	16
};

extern int g_BRUTEFORCE_dataLen[16];
extern char g_BRUTEFORCE_bfSymbols[34];

struct BRUTEFORCE_HANDLE {

	char
			*bfText,			//Current bruteforce text.
			bflastChar,			//Bruteforce terminating character.
			*bfData				//Array consisting of characters to be included on bruteforce attempts.
	;
	size_t
			bfmaxLen,			//Maximum length of 'bfText'.
			*bfCurrIdx,			//The current index in bfData.
			bfUpdIdx			//The index in 'bfText' from where update occurs.
	;
};

typedef 	enum BRUTEFORCE_FLAGS 		BRUTEFORCE_FLAGS;
typedef 	struct BRUTEFORCE_HANDLE	BRUTEFORCE_HANDLE;

/*
bruteforce_init - Initializes a bruteforce handler.

Parameters:
	BRUTEFORCE_HANDLE *bfHandle 	-		Bruteforce handler.
	size_t maxLen					-		Maximum length upto which bruteforce is performed.
	BRUTEFORCE_FLAGS flags 			-		Flags that determine what type of characters should be used. Use BF_FLAG_CUSTOM to use custom character set.
	const char *data 				-		Data or character set containing bruteforce characters. Set NULL to use the default character set.
	const char *startString 		-		String from where bruteforce should be started. Set NULL to start from beginning (first chararcter from bfData(character set)).

Returns:
	1								-		On success.
	0								-		On failure.
*/
extern int bruteforce_init(BRUTEFORCE_HANDLE *bfHandle, size_t maxLen, BRUTEFORCE_FLAGS flags, const char *data, const char *startString);

/*
bruteforce_update - Updates the bruteforce handler (updates bfText).

Parameters:
	BRUTEFORCE_HANDLE *bfHandle 	-		Bruteforce handler.

Returns:
	1								-		On success.
	0								-		On failure (indicates that bruteforce is over).
*/
extern int bruteforce_update(BRUTEFORCE_HANDLE *bfHandle);

/*
bruteforce_finalize - Finalizes/Deallocates given bruteforce handler.

Parameters:
	BRUTEFORCE_HANDLE *bfHandle 	-		Bruteforce handler.

Returns:
	No specific value.
*/
extern void bruteforce_finalize(BRUTEFORCE_HANDLE *bfHandle);

#endif
