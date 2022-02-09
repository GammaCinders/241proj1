#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define keyLen strlen(argv[2])

//Maybe change to a char pointer later
char encryptDecrypt(char ch, int k);

void main(int argc, char *argv[]) {

	//obligitory error checking
	if(argc != 5) {
		printf("Usage: cipher inputFile key outputFile option(e or d)\n");
		printf("Option e for encryption and d for decryption");
		exit(1);
	}


	//setup keylength and add each char value in alphabet to array
	int key[keyLen];
	for(int i=0; i<keyLen; i++) {
		if(isupper(*(argv[2]+i))) {
			key[i] = *(argv[2]+i)-'A';
		} else if(islower(*(argv[2]+i))) {
			key[i] = *(argv[2]+i)-'a';
		} else {
			key[i] = 0;
		}

		if(strcmp(argv[4], "d") == 0) {
			key[i] = -key[i];
		}
	}	

	//load files needed to run program and check for errors
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[3], "w");
	if(in == NULL || out == NULL) {
		printf("File could not be opened!\n");
		exit(1);
	}

	//run through the in file char by char and encrypt/decrypt to out file
	char c;
	int n = 0;
	while(fscanf(in, "%c", &c) != EOF) {
		fprintf(out, "%c", encryptDecrypt(c, key[n%keyLen]));
		n++;
	}

	fclose(in);
	fclose(out);
}

char encryptDecrypt(char c, int k) {
	
	//rotates k to first positive alph value
	while(k < 0) {
		k = k + 26;
	}

	if(isupper(c)) {
		return ((c - 'A' + k) % 26) + 'A';
	}

	if(islower(c)) {
		return ((c - 'a' + k) % 26) + 'a';
	}

	return c;
}
