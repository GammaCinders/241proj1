#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define keyLen strlen(argv[2])

/* holds each number 0-25 once in order based on argv key input */
int key[26];
/* holds numbers 0-25 in order */
int alphabet[26];

char encryptDecrypt(char ch, int k);

void main(int argc, char *argv[]) {

	//obligitory error checking
	if(argc != 5) {
		printf("Usage: cipher inputFile key outputFile option(e or d)\n");
		printf("Option e for encryption and d for decryption");
		exit(1);
	}

	//init alphabet key array {0 - 25}
	for(int i=0; i<26; i++) {
		alphabet[i] = i;
	}
	//setup key[] to hold correct order of alphabet value (0-25) based on arg key
	for(int i=0; i<keyLen; i++) {
		if(isupper(*(argv[2]+i))) {
			key[i] = *(argv[2]+i)-'A';
			alphabet[key[i]] = -1;
		} else if(islower(*(argv[2]+i))) {
			key[i] = *(argv[2]+i)-'a';
			alphabet[key[i]] = -1;
		} else {
			key[i] = 0;
		}

		//invert/reverse rotation in alphabet when decrypting
		if(strcmp(argv[4], "d") == 0) {
			key[i] = -key[i];
		}
	}	
	//put rest of alphabet in key[] backwards
	int n = 25;
	for(int i=keyLen; i<26; i++) {
		//skip element already used and marked earlier
		while(alphabet[n] == -1) {
			n--;
		}	

		key[i] = alphabet[n];
		n--;
	}

	//load files needed to run program and check for errors
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[3], "w");
	if(in == NULL || out == NULL) {
		printf("File could not be opened!\n");
		exit(1);
	}

	//run through in file char by char and encrypt/decrypt to out file
	char c;
	n = 0;
	while(fscanf(in, "%c", &c) != EOF) {
		fprintf(out, "%c", encryptDecrypt(c, key[n%keyLen]));
		n++;
	}

	fclose(in);
	fclose(out);
}

char encryptDecrypt(char c, int k) {
	
	//rotates k to first positive alphabet letter value
	//so that k is always >= 0 and < 26
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
