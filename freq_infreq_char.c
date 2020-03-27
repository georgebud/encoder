#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char get_frequent_character(char* line) {
	int* v = (int*)calloc(127, sizeof(int));
	char frequent_character;
	int maximum = 0;
	int i;

	for(i = 0; i < strlen(line); i++) {
		v[((int) line[i])]++;
	}
	for(i = 0; i < strlen(line); i++) {
		if(v[((int) line[i])] > maximum) {
			maximum = v[((int) line[i])];
			frequent_character = line[i];
		}
	}
	free(v);
	return frequent_character;
}

char get_infrequent_character(char* line) {
	int* v = (int*)calloc(127, sizeof(int));
	char infrequent_character = line[0];
	int minimum, i;

	minimum = strlen(line);
	for(i = 0; i < strlen(line); i++) {
		v[((int) line[i])]++;
	}
	for(i = 0; i < strlen(line); i++) {
		if(v[((int) line[i])] < minimum) {
			minimum = v[((int) line[i])];
			infrequent_character = line[i];
		}
	}
	free(v);
	return infrequent_character;
}

int main() {
	char infrequent_character, frequent_character;

    frequent_character = get_frequent_character("georgee");
	infrequent_character = get_infrequent_character("georgee");
	printf("%c %c\n", frequent_character, infrequent_character);
	return 0;
}