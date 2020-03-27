#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NO_CHAR 52

char* read_line() {
	char str[MAX_NO_CHAR];
	char *input_line;

	//citire linie de la tastatura
	if(fgets(str, MAX_NO_CHAR, stdin) != NULL) {
		input_line = (char*)calloc(strlen(str), sizeof(char)); //alocare memorie pentru linie
		// stocare linie in vector de linii, fara ultimul caracter care e \n
		strncpy(input_line, str, strlen(str)-1);
		input_line[strlen(str)-1] = '\0'; //adaugarea terminatorului de sir
	} else {
		//iese cu eroare daca nu s-a citit cu succes de la tastatura
		return NULL;
	}
	return input_line;
}

void free_lines(char** input_lines, int line_number) {
	int i = 0;

	for (i = 0; i < line_number; i++) {
		free(input_lines[i]);
	}
}

/*functia aloca memorie pentru un vector de linii (sir de caractere) si
citeste, pe rand, de la tastatura, linii pana la intalnirea sirului "END"
si le stocheaza in vectorul de linii
returneaza vectorul de linii
primeste un parametru prin care se returneaza numarul de linii din vector*/
char** read_input_lines(int* line_number_result) {
	int line_number = 0;
	int input_lines_lenght = 1; /*lungimea vectorului de linii*/
	char** input_lines = (char**)calloc(1, sizeof(char*)); /*alocare vector de linii*/

	if(input_lines == NULL) {
		printf("Eroare la alocarea memoriei\n");
		return NULL;
	}
	/*stocheaza prima linie*/
	if((input_lines[0] = read_line()) == NULL) {
		printf("Eroare la citirea de la tastatura\n");
		free(input_lines); /*eliberez memoria alocata pentru vectorul de linii*/
		return NULL;
	}

	/*stocheaza liniile urmatoare*/
	while(strcmp(input_lines[line_number], "END") != 0) {
		line_number++;
		if (line_number == input_lines_lenght) {
			input_lines_lenght *= 2;
			input_lines = (char**)realloc(input_lines, input_lines_lenght * sizeof(char*));	//realocare vector de linii prin dublare
			if(input_lines == NULL) {
				printf("Eroare la realocarea memoriei\n");
				return NULL;
			}
		}
		if((input_lines[line_number] = read_line()) == NULL) {
			printf("Eroare la citirea de la tastatura\n");
			free_lines(input_lines, line_number); /*eliberez memoria alocata pentru liniile citite*/
			free(input_lines); /*eliberez memoria alocata pentru vectorul de linii*/
			return NULL;
		}
	}
	*line_number_result = line_number;
	return input_lines;
}

/*functie care elibereaza memoria folosita de catre liniile citite
elibereaza pe rand fiecare linie, apoi elibereaza memoria alocata vectorului de linii*/
void free_input(char** input, int input_line_number) {
	int i = 0;

	for(i = 0; i <= input_line_number; i++) {
		free(input[i]);
	}
	free(input);
}

/*functie care verifica daca linia citita este un numar
primeste ca parametru sirul citit
returneaza numarul format*/
long* check_numbers(char* line) {
	int i = 0;
	int negative = 0; /*consider ca numarul nu este negativ*/
	long* number = (long*)calloc(1, sizeof(long)); //aloc memorie pentru numar

	if(number == NULL) {
		printf("Eroare la alocarea memoriei - long\n");
		return NULL;
	}
	*number = 0;
	//verific daca linia are cel putin 2 caractere primul fiind '-'
	if(strlen(line) > 1 && line[0] == '-') { 
		negative = 1; /*numarul este negativ*/
	}
	for(i = negative; i < strlen(line); i++) {
		//verific daca linia contine doar cifre (fara 0)
		if(line[i] < 49 || line[i] > 57) {
			free(number); //eliberez memoria
			return NULL;
		}
		else *number = *number*10 + (line[i] - '0'); //formez numarul
	}
	//daca numarul e negativ, pe cel format il inmultesc cu -1
	if(negative == 1) 
		*number *= -1;
	return number;
}

/*functie care verifica daca linia citita este un caracter
primeste ca parametru sirul citit
returneaza caracterul*/
char* check_character(char* line) {
	char* character = (char*)calloc(1, sizeof(char)); //aloc memorie pentru caracter

	if(character == NULL) {
		printf("Eroare la alocarea memoriei - character\n");
		return NULL;
	}
	//verific daca linia contine un singur caracter
	if(strlen(line) != 1) {
		free(character); //eliberez memoria
		return NULL;
	}
	else {
		//verific daca caracterul se afla in intervalul specificat si daca nu reprezinta o cifra
		if(line[0] < 32 || line[0] >=127 || (line[0] >=48 && line[0] <=57)) {
			free(character); //eliberez memoria
			return NULL;
		}
		else
			*character = line[0]; //stochez caracterul
	}
	return character;
}

/*functie care verifica daca linia citita este un cuvant
primeste ca parametru sirul citit
returneaza cuvantul respectiv*/
char* check_words(char* line) {
	int i = 0;
	//am alocat memorie pentru a copia in word cu strcpy, si +1 pentru terminatorul de sir
	char* word = (char*)calloc((strlen(line) + 1), sizeof(char)); //aloc memorie pentru cuvant
	if(word == NULL) {
		printf("Eroare la alocarea memoriei - word\n");
		return NULL;
	}
	for(i = 0; i < strlen(line); i++) {
		//verific daca fiecare caracter se afla in intervalul specificat
		if(line[i] < 32 || line[i] >= 127) {
			free(word); //eliberez memoria
			return NULL;
		}
	}
	//daca sunt indeplinite conditiile copiez linia 
	strcpy(word, line);
	return word;
}

/*functie care returneaza cel mai mare divizor din linie
primeste ca parametru sirul citit*/
int get_highest_divisor_from_string(char* line) {
	int l;
	int divisor = 0;

	l = strlen(line); //lungimea sirului
	for(divisor = l / 2; divisor >= 1; divisor--) {
		//verific daca exista un divizor
		if(l % divisor == 0)
			return divisor;
	}
}

/*functie care verifica daca exista cifre in linie
primeste ca parametru sirul citit*/
int string_contains_digit(char* line) {
	int i = 0;
	char digits[] = "0123456789";

	for(i = 0; i < strlen(line); i++) {
		//verific daca in linie exista o cifra
		if(strchr(digits, line[i]) != NULL)
			return 1;
	}
	return 0;
}

/*functie care formeaza si returneaza sirul inversat
primeste ca parametru sirul citit*/
char* get_reversed_string(char* line) {
	int i = 0;
	int j = 0;
	char* reversed_word = (char*)calloc(strlen(line), sizeof(char)); //alocare de memorie

	if(reversed_word == NULL) {
		printf("Eroare la alocarea memoriei - reversed_word\n");
		return NULL;
	}
	//formarea sirului inversat
	for(i = strlen(line) - 1; i >= 0; i--) {
		reversed_word[j] = line[i];
		j++;
	}
	return reversed_word;
}

//criptarea cuvantului
char* get_encrypted_word_from_string(char* line) {
	int highest_divisor = 0;
	int breakpoint = 0;
	char* encrypted_word = (char*)calloc((strlen(line) + 1), sizeof(char));

	if(encrypted_word == NULL) {
		printf("Eroare la alocarea memoriei - encrypted_word\n");
		return NULL;
	}
	highest_divisor = get_highest_divisor_from_string(line);
	breakpoint = strlen(line) - highest_divisor;
	//verific cerintele din enunt
	if(!string_contains_digit(line)) {
		strncpy(encrypted_word, line + highest_divisor, breakpoint);
		strncpy(encrypted_word + breakpoint, line, highest_divisor);
		encrypted_word[strlen(encrypted_word)] = '\0'; //adaugarea terminatorului de sir
	}
	else {
		char* reversed_string = get_reversed_string(line + highest_divisor);
		strncpy(encrypted_word, reversed_string, breakpoint);
		strncpy(encrypted_word + breakpoint, line, highest_divisor);
		encrypted_word[strlen(encrypted_word)] = '\0';
		free(reversed_string);
	}
	return encrypted_word;
}

//functie care returneaza dimensiunea numarului
long get_number_lenght(long number) {
	int count = 0;

	while(number) {
		number /= 10;
		count++;
	}
	return count;
}

//functia returneaza cel mai mare numar format prin rotatia ciclica a cifrelor sale
long max_digit(long number) {
	int i = 0;
	int number_lenght = 0;
	long max = 0;

	max = number; //maximul este numarul initial
	number_lenght = get_number_lenght(number); //dimensiunea numarului
	for(i = 0; i < number_lenght - 1; i++) {
		//formarea numarului prin rotatii ciclice
		number = (number % 10) * pow(10, (number_lenght - 1)) + number / 10;
		if(number > max)
			max = number;
	}
	return max;
}

//functia returneaza cel mai mic numar format prin rotatia ciclica a cifrelor sale
long min_digit(long number) {
	int i = 0;
	int number_lenght = 0;
	long min = 0;

	if(number < 0) {
		number = abs(number); //iau numarul in modul
	}
	number_lenght = get_number_lenght(number); //dimensiunea
	min = number; //minimul este numarul initial

	for(i = 0; i < number_lenght - 1; i++) {
		//formarea numarului prin rotatii
		number = (number % 10) * pow(10, (number_lenght - 1)) + number / 10;
		if(number < min)
			min = number;
	}
	return min;
}

//functie care returneaza cel mai des intalnit caracter
char get_frequent_character(char* line) {
	int i = 0;
	int maximum = 0;
	int* v = (int*)calloc(127, sizeof(int)); //alocare de memorie pentru un vector de tip int
	char frequent_character;

	for(i = 0; i < strlen(line); i++) {
		//cresc cu 1 in vectorul de int-uri pe fiecare pozitie al codului ascii al caracterului
		v[((int) line[i])]++;
	}
	for(i = 0; i < strlen(line); i++) {
		//determinarea celui mai frecvent caracter
		if(v[((int) line[i])] > maximum) {
			maximum = v[((int) line[i])];
			frequent_character = line[i];
		}
	}
	free(v); //eliberez memoria vectorului
	return frequent_character;
}

//functie care returneaza cel mai rar intalnit caracter
char get_infrequent_character(char* line) {
	int i = 0;
	int minimum = 0;
	int* v = (int*)calloc(127, sizeof(int)); //alocare memorie
	char infrequent_character = line[0];

	//procesul de determinare al celui mai rar intalnit caracter
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

//functia returneaza media codurilor ascii ale caracterelor dintr-un sir
double get_line_complexity(char* line) {
	int n = 0;
	int i = 0;
	double sum = 0; //initializarea sumei cu 0

	n = strlen(line); //lungimea sirului
	for(i = 0; i < n; i++) {
		sum += line[i]; //se adauga la suma codul ascii al caracterului curent
	}
	return sum / n; //returneaza media aritmetica
}

//structura ce continte un char pointer si un double
typedef struct {
	char* line;
	double complexity;
} string;


/*functie care imparte in n bucati mesajul criptat
functia primeste ca paremetru mesajul criptat si un n ce reprezinta in cate parti sa fie impartit mesajul*/
string* get_split_encrypted_message(char* encrypted_message, int n) {
	string* split_message = (string*)calloc(n, sizeof(string)); //alocare

	if(split_message == NULL) {
		printf("Eroare la alocarea memoriei\n");
		return NULL;
	}

	int chunk = strlen(encrypted_message) / n; //dimensiunea sirurilor egal despicate
	int i = 0;
	int size = 0;

	for(i = 0; i < n - 1; i++) {
		split_message[i].line = (char*)calloc((chunk + 1), sizeof(char));
		if(split_message[i].line == NULL) {
            printf("Eroare la alocarea memoriei\n");
            return NULL;
        }
        //copiez in split_message[i].line fiecare bucata din mesaj
		strncpy(split_message[i].line, encrypted_message + chunk * i, chunk);
		split_message[i].line[chunk] = '\0'; //terminator de sir
		split_message[i].complexity = get_line_complexity(split_message[i].line); //ii atribui complexitatea
	}
	size = strlen(encrypted_message) - chunk * i; //dimensiunea ultimei bucati despicate

	split_message[i].line = (char*)calloc((size + 1), sizeof(char)); //alocare pentru ultima bucata
	if(split_message[i].line == NULL) {
		printf("Eroare la alocarea memoriei\n");
		return NULL;
	}
	//se copiaza si ultima bucata si i se atribuie complexitatea
	strncpy(split_message[i].line, encrypted_message + chunk * i, size);
	split_message[i].line[size] = '\0';
	split_message[i].complexity = get_line_complexity(split_message[i].line);
	return split_message;
}

/*functie care ordoneaza vectorul de structuri descrescator in functie de complexitatea componentelor*/
string* get_sorted_encrypted_message(string* array, int n) {
	int i = 0, j = 0;
	char* aux_line; //auxiliar folosit la interschimbarea sirurilor
	double aux_complexity; //auxiliar folosit la interschimbarea valorilor complexitatilor

	//ordonarea vectorului de structuri
	for(i = 0 ; i < n - 1; i++) {
		for(j = i + 1; j < n; j++) {
			if(array[i].complexity < array[j].complexity) {

				//interschimbarea sirurilor intre ele
				aux_line = (char*)calloc(strlen(array[i].line), sizeof(char));
				if(aux_line == NULL) {
                    printf("Eroare la alocarea memoriei\n");
                    return NULL;
                }
				strcpy(aux_line, array[i].line);
				//se realoca array[i].line cu dimensiunea sirului array[j].line pentru a putea efectua interschimbul
				array[i].line = (char*)realloc(array[i].line, strlen(array[j].line) * sizeof(char));
				if(array[i].line == NULL) {
                    printf("Eroare la alocarea memoriei\n");
                    return NULL;
                }
				strcpy(array[i].line, array[j].line);
				array[j].line = (char*)realloc(array[j].line, strlen(aux_line) * sizeof(char));
				if(array[j].line == NULL) {
                    printf("Eroare la alocarea memoriei\n");
                    return NULL;
                }
				strcpy(array[j].line, aux_line);
				free(aux_line); //eliberez memoria
				//interschimbarea complexitatilor
				aux_complexity = array[i].complexity;
				array[i].complexity = array[j].complexity;
				array[j].complexity = aux_complexity;
			}
			//daca sirurile au aceeasi complexitate, se sorteaza lexicografic dupa acelasi algoritm ca mai sus
			if(array[i].complexity == array[j].complexity) {
				if(strcmp(array[i].line, array[j].line) > 0) {
					aux_line = (char*)calloc(strlen(array[i].line), sizeof(char));
					if(aux_line == NULL) {
                        printf("Eroare la alocarea memoriei\n");
                        return NULL;
                    }
					strcpy(aux_line, array[i].line);
					array[i].line = (char*)realloc(array[i].line, strlen(array[j].line) * sizeof(char));
					if(array[i].line == NULL) {
                        printf("Eroare la alocarea memoriei\n");
                        return NULL;
                    }
					strcpy(array[i].line, array[j].line);
					array[j].line = (char*)realloc(array[j].line, strlen(aux_line) * sizeof(char));
					if(array[j].line == NULL) {
                        printf("Eroare la alocarea memoriei\n");
                        return NULL;
                    }
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

/*Functie pentru eliberarea memoriei a vectorului de structuri*/
void free_string(string* array, int n) {
	int i = 0;
	for(i = 0; i < n; i++) {
        if(array[i].line != NULL) {
            free(array[i].line);
        }
	}
	if(array != NULL) {
        free(array);
	}
}

/*functie care returneaza mesajul codificat
primeste ca si parametri dimensiunea vectorului de linii si vectorul de linii*/
char* get_encrypted_message(int input_line_number, char** input) {
	int i = 0;
	long* number;
	char* character;
	char* word;
	char* encrypted_word;
	char* encrypted_message = (char*)calloc(5001, sizeof(char)); //se aloca memorie pentru mesajul codificat
	if(encrypted_message == NULL) {
        printf("Eroare la alocarea memoriei\n");
        return NULL;
    }
	//prelucrarea mesajului criptat
	for(i = 0 ; i < (input_line_number) - 1; i++) {
		number = check_numbers(input[i]);
		//verifica daca sirul este un numar
		if(number != NULL) {
			long cycled_number = 0;
			char* buffer = (char*)calloc(strlen(input[i]), sizeof(char)); //vector pentru conversie
			if(buffer == NULL) {
                printf("Eroare la alocarea memoriei\n");
                return NULL;
            }
			if(*number > 0){
				cycled_number = max_digit(*number); //cel mai mare numar format prin rotatia cifrelor
			}
			else{
				cycled_number = min_digit(*number); //cel mai mic numar format prin rotatie
			}
			//in buffer se salveaza conversia lui cycled_number de la tipul long la tipul char
			sprintf(buffer, "%ld", cycled_number); 
			strcat(encrypted_message, buffer); //concatenez numarul la mesajul codificat
			free(buffer); //eliberare memorie
			free(number);
		}
		else {
			character = check_character(input[i]);
			//verific daca sirul reprezinta un caracter
			if(character != NULL) {
				//daca nu se afla pe prima pozitie, aplic functiile pentru frecventa caracterului din sirul format
				if(i != 0) {
					char frequent_character = get_frequent_character(encrypted_message); //cel mai frecvent
					char infrequent_character = get_infrequent_character(encrypted_message); //cel mai rar
					char encrypted_characters[4];
					//salvez intr-un vector caracterele si adaug terminator de sir
					encrypted_characters[0] = frequent_character;
					encrypted_characters[1] = *character;
					encrypted_characters[2] = infrequent_character;
					encrypted_characters[3] = '\0';
					strcat(encrypted_message, encrypted_characters); //concatenez vectorul la mesajul codificat
				}
				else {
					strcat(encrypted_message, input[i]); //concatenez caracterul la mesajul codificat
				}
				free(character); //eliberez memoria
			}
			else {
				word = check_words(input[i]);
				//verific daca sirul face parte din categoria 'cuvant'
				if(word != NULL) {
					encrypted_word = get_encrypted_word_from_string(input[i]); //cuvantul codificat
					//concatenez cuvantul criptat la mesajul codificat
					strcat(encrypted_message, encrypted_word); 
					//eliberari de memorie
					free(encrypted_word);
					free(word);
				}
			}
		}
	}
	return encrypted_message;
}

/*Functia returneaza mesajul codificat dupa rearanjare
Primeste ca parametru vectorul de structuri sortat si numarul de componente*/
char* get_final_encrypted_message(string* sorted_array, int n) {
	char* final_encrypted_message = (char*)calloc(5001, sizeof(char));
	int i = 0;

	for(i = 0; i < n / 2; i++) {
		//rearanjarea mesajului
		strcat(final_encrypted_message, sorted_array[i].line);
		strcat(final_encrypted_message, sorted_array[n-i-1].line);
	}
	if(n % 2 != 0) {
		//concatenez la mesajul final componenta din mijlocul vectorului de structuri
		strcat(final_encrypted_message, sorted_array[n / 2].line);
	}
	return final_encrypted_message;
}

/*functie care formeaza numarul daca stringul e format din cifre*/
int get_number_from_line(char* line) {
	int i;
	int number = 0;

	for(i = 0; i < strlen(line); i++) {
		//verific daca fiecare caracter reprezinta o cifra
		if(line[i] < 48 || line[i] > 57) {
			return -1;
		}
		else number = number*10 + (line[i] - '0'); //formez numarul
	}
	return number;
}

int main() {

	int i = 0;
	int input_line_number, nr_words = 0, nr_characters = 0, nr_numbers = 0, n = 0;
	long* number;
	char* character;
	char* word;
	char* encrypted_word;
	char* encrypted_message;
	char* final_encrypted_message;
	char** input = read_input_lines(&input_line_number);

	//afisam prima linie (numarul de cuvinte, caractere, numere)
	for(i = 0; i < (input_line_number) - 1; i++) {
		number = check_numbers(input[i]);
		if(number != NULL) {
			nr_numbers += 1;
			free(number);
		}
		else {
			character = check_character(input[i]);
			if(character != NULL) {
				nr_characters += 1;
				free(character);
			}
			else {
				word = check_words(input[i]);
				if(word != NULL) {
					nr_words += 1;
					free(word);
				}
			}
		}
	}
	printf("%d %d %d\n", nr_words, nr_characters, nr_numbers);

	encrypted_message = get_encrypted_message(input_line_number, input);
	printf("%s\n", encrypted_message);

	n = get_number_from_line(input[input_line_number -1]);
	string* split_encrypted_message = get_split_encrypted_message(encrypted_message, n);
	string* sorted_encrypted_message = get_sorted_encrypted_message(split_encrypted_message, n);
	final_encrypted_message = get_final_encrypted_message(sorted_encrypted_message, n);
	printf("%s\n", final_encrypted_message);

	free(encrypted_message);
	free(final_encrypted_message);
	free_input(input, input_line_number);
	free_string(split_encrypted_message, n);
	return 0;
}