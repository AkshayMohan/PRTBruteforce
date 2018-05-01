/*
	PRT Bruteforce - Akshay Mohan.
	bruteforce.h
*/

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#define		BF_FLAG_ALL				BF_FLAG_UPPERCASE | BF_FLAG_LOWERCASE | BF_FLAG_DIGITS | BF_FLAG_SYMBOLS
#define		BF_FLAG_ALPHANUMERIC	BF_FLAG_UPPERCASE | BF_FLAG_LOWERCASE | BF_FLAG_DIGITS
#define 	BF_FLAG_LETTERS			BF_FLAG_UPPERCASE | BF_FLAG_LOWERCASE
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
	unsigned int
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
	unsigned int maxLen				-		Maximum length upto which bruteforce is performed.
	BRUTEFORCE_FLAGS flags 			-		Flags that determine what type of characters should be used. Use BF_FLAG_CUSTOM to use custom character set.
	char *data 						-		Data or character set containing bruteforce characters. Set NULL to use the default character set.
	char *startString 				-		String from where bruteforce should be started. Set NULL to start from beginning (first chararcter from bfData(character set)).

Returns:
	1								-		On success.
	0								-		On failure.
*/
int bruteforce_init(BRUTEFORCE_HANDLE *bfHandle, unsigned int maxLen, BRUTEFORCE_FLAGS flags, char *data, char *startString);

/*
bruteforce_update - Updates the bruteforce handler (updates bfText).

Parameters:
	BRUTEFORCE_HANDLE *bfHandle 	-		Bruteforce handler.

Returns:
	1								-		On success.
	0								-		On failure (indicates that bruteforce is over).
*/
int bruteforce_update(BRUTEFORCE_HANDLE *bfHandle);

/*
bruteforce_finalize - Finalizes/Deallocates given bruteforce handler.

Parameters:
	BRUTEFORCE_HANDLE *bfHandle 	-		Bruteforce handler.

Returns:
	No specific value.
*/
void bruteforce_finalize(BRUTEFORCE_HANDLE *bfHandle);

#endif