#include <stdio.h>
#include "bruteforce.h"

int main(int argc, char **argv) {

	BRUTEFORCE_HANDLE bf_handle; //Declare a bruteforce handler.
	//Initialize it.
	bruteforce_init(
		&bf_handle, 			//The handler to be initialized.
		3, 						//Maximum length upto which bruteforce is performed.
		BF_FLAG_ALPHANUM,		//Include alphabets and numbers.
		NULL,					//I'm not using custom bruteforce character set, so I set this argument to NULL.
		NULL					//I'll start from the very beginning, I'm not having any particular entry point.
	);
	while(bruteforce_update(&bf_handle)) {

		//This code works until bruteforce_udpate returns 0.
		printf("%s\n", bf_handle.bfText); //bf_handle.`bfText` is the text that gets updated.

		//Instead of printing bf_handle.bfText - I can use this loop against a database, SSH or POST requests.
	}
	bruteforce_finalize(&bf_handle);
	return 0;
}
