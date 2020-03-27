#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double get_line_complexity(char* line) {
	double sum = 0;
	int n = strlen(line);

	for(int i = 0; i < n; i++) {
		sum += line[i];
	}
	return sum / n;
}

typedef struct {
	char* line;
	double complexity;
} string;

string* get_split_encrypted_message(char* encrypted_message, int n) {
	string* split_message = (string*)malloc(n * sizeof(string));
	int chunk = strlen(encrypted_message) / n;
	int i;

	for(i = 0; i < n - 1; i++) {
		split_message[i].line = (char*)malloc((chunk + 1) * sizeof(char));
		strncpy(split_message[i].line, encrypted_message + chunk * i, chunk);
		split_message[i].line[chunk] = '\0';
		split_message[i].complexity = get_line_complexity(split_message[i].line);
	}
	int size = strlen(encrypted_message) - chunk * i;

	split_message[i].line = (char*)malloc((size + 1) * sizeof(char));
	strncpy(split_message[i].line, encrypted_message + chunk * i, size);
	split_message[i].line[size] = '\0';
	split_message[i].complexity = get_line_complexity(split_message[i].line);

	return split_message;
}

string* get_sorted_encrypted_message(string* array, int n) {
	int i, j;
	char* aux_line;
	double aux_complexity;

	for(i = 0 ; i < n - 1; i++) {
		for(j = i + 1; j < n; j++) {
			if(array[i].complexity < array[j].complexity) {

				//interschimbarea sirurilor intre ele
				aux_line = (char*)malloc(strlen(array[i].line) * sizeof(char));
				strcpy(aux_line, array[i].line);
				array[i].line = (char*)realloc(array[i].line, strlen(array[j].line) * sizeof(char));
				strcpy(array[i].line, array[j].line);
				array[j].line = (char*)realloc(array[j].line, strlen(aux_line) * sizeof(char));
				strcpy(array[j].line, aux_line);
				free(aux_line);

				//interschimbarea complexitatilor
				aux_complexity = array[i].complexity;
				array[i].complexity = array[j].complexity;
				array[j].complexity = aux_complexity;
			}
			if(array[i].complexity == array[j].complexity) {
				if(strcmp(array[i].line, array[j].line) > 0) {
					aux_line = (char*)malloc(strlen(array[i].line) * sizeof(char));
					strcpy(aux_line, array[i].line);
					array[i].line = (char*)realloc(array[i].line, strlen(array[j].line) * sizeof(char));
					strcpy(array[i].line, array[j].line);
					array[j].line = (char*)realloc(array[j].line, strlen(aux_line) * sizeof(char));
					strcpy(array[j].line, aux_line);
					free(aux_line);

					aux_complexity = array[i].complexity;
					array[i].complexity = array[j].complexity;
					array[j].complexity = aux_complexity;
				}
			}
		}
	}
	return array;
}


/*string* get_sorted_encrypted_message(string* array, int n) {
	int i, finish = 0;
	char aux[1000];

	while(!finish) {
		finish = 1;
		for(i = 0; i < n - 1; i++) {
			if(array[i].complexity < array[i+1].complexity) {
				finish = 0;
				strcpy(aux, array[i].line);
				array[i].line = array[i+1].line;
				array[i+1].line = aux;
			}
			if(array[i].complexity == array[i+1].complexity) {
				finish = 0;
				if(strcmp(array[i].line, array[i+1].line) > 0) {
					strcpy(aux, array[i].line);
					array[i].line = array[i+1].line;
					array[i+1].line = aux;
				}
		    }
		}
	}
	return array;
}*/

int main()
{
    char s[12] = "ab`cefghijk";
    string* p = get_split_encrypted_message(s, 5);
    for(int i = 0; i<5; i++) {
        printf("%s ___ %lf  |   ", p[i].line, p[i].complexity);
    }
    printf("\n");
    
    string* q = get_sorted_encrypted_message(p, 5);
    for(int i = 0; i<5 ; i++) {
        printf("%s   +++  %lf     ", q[i].line, q[i].complexity);
    }

    printf("\n");

    return 0;
}