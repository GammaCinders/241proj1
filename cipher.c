#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>

char *encrypt(char *message);
char *decrypt(char *message, char *key);
char *createCipher(char *message);

int main(int argc, char *argv[]) {

	//TODO argc should always be 5 (check criteria)
	char option = *argv[4];
	
	//obv need to check for file open validity after
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[3], "w");
	
	//cipher and char stuff idk
	char *cipher = createCipher(argv[2]);

	char c;

	if(option == 'd') {
		while(!feof(in)) {
			fscanf(in, "%c", &c);

			if(isupper(c)) {
				fprintf(out, "%c", toupper('a'+(index(cipher, tolower(c))-cipher)));
			} else if(islower(c)) {
				fprintf(out, "%c", 'a'+(index(cipher, tolower(c))-cipher));
			} else {
				fprintf(out, "%c", c);
			}
		}
	}

	if(option == 'e') {
		while(!feof(in)) {
			fscanf(in, "%c", &c);

			if(isupper(c)) {
				fprintf(out, "%c", toupper(cipher[c-'A']));
			} else if(islower(c)) {
				fprintf(out, "%c", cipher[c-'a']); 
			} else {
				fprintf(out, "%c", c);
			}
		}
	}

	fclose(in);
	fclose(out);
	free(cipher);

	return 1;
}

char *encrypt(char *message) {
	
}

//TODO not going to work for other symbols
char *createCipher(char *key) {

	//just add int symbols that counts the number of 
	//symbols (non letter chars) in key and then do
	//char cipher[26+numOfNonletters]
	char *cipher = (char*)malloc(sizeof(char)*26);
	//char cipher[26];

	//inc cp to first emtpy index of cipher (or end of key in cipher) 
	for(int i=0; i<strlen(key); i++) {
		cipher[i] = tolower(key[i]);
	}	

	char *cp = cipher+strlen(key);

	//copies all other letters not used into cipher

	for(int i='z'; i>='a'; i--) {
		//make sure to have only 26 chars total
		if(cp >= &(cipher[26])) {
			break;
		}

		//skip any letters in key 
		int isUsed = 0;
		for(int j=0; j<strlen(key); j++) {
			if(key[j]==i) {
				isUsed = 1;
				break;
			}
		}
		//set cipher to correct value and inc cp
		if(isUsed==0) {
			*cp = i;
			cp++;
		}
	}

	//debug printing
/*	for(int i=0; i<26; i++) {
		printf("%c", cipher[i]);
	}
	printf("\n%d\n", strlen(cipher));
*/
	return cipher;
}
