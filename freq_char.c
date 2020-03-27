#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char get_frequent_character(char* line) {
	char* v = (char*)calloc(127, sizeof(char));
	int maxim = 0;
	int i;
	char frequent_character;

	for(i = 0; i < strlen(line); i++) {
		v[((int) line[i])]++;

		if(v[((int) line[i])] > maxim) {
			maxim = v[((int) line[i])];
			frequent_character = line[i];
		}
	}
	free(v);
	printf("maxim inainte de return este: %d\n", maxim);
	printf("frequent_character este: %c\n", frequent_character);
	return frequent_character;
}

int main() {
	char character;

	character = get_frequent_character("georgee");
	printf("%c\n", character);
	return 0;
}


//____________MY VERSION :__________________
/*char get_frequent_character(char* line) {
	char frequent_character;
	int i,j, nr_frequent_character, max;

	max = 1;
	for(i = 0; i < (strlen(line) -1); i++) {
		nr_frequent_character = 1;
	
		for(j = i + 1; j < strlen(line); j++) {
			if(line[i] == line[j]) {
				nr_frequent_character++;
			}
		}
		if(nr_frequent_character > max) {
			max = nr_frequent_character;
			frequent_character = line[i];
		}
	}
	return frequent_character;
}
*/