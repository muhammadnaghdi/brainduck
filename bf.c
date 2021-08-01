#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void interpret(char instruction);
void loop();
void init();

char tape[1024*32] = {0};
char* tptr = tape;

char instructions[1024*32];
char* iptr = instructions;

FILE* fptr;

int main(int argc, char* argv[]) {
	if (!(fptr = fopen(argv[1], "r")))
		return -1;
	
	init();
	
	while (*iptr != EOF) {
		interpret(*iptr++);
	}
 	
	fclose(fptr);
	return 0;
}

void init() {
	char c;
	char index = 0;
	while ((c = fgetc(fptr)) != EOF) {
		instructions[index++] = c;
	}
	instructions[index] = EOF;
}

void interpret(char instruction) {
	switch ((int)instruction) {
		case '>':
		++tptr;
		break;
		
		case '<':
		--tptr;
		break;
			
		case '+':
		++*tptr;
		break;

		case '-':
		--*tptr;
		break;

		case '.':
		putchar(*tptr);
		break;

		case ',':
		*tptr = getchar();
		break;

		case '[':
		loop();
		break;

		case ']':
		puts("ERROR: Unmatched ']'");
		break;
	}	
	
	return;
}

void loop() {
	char* start = iptr;
	
	if (!*tptr) {
		while (*iptr != ']') {
			++iptr;
		}
		++iptr;
		return;
	}
	
	while (*tptr) {
		iptr = start;
		while (*iptr != ']') {
			if (*iptr == EOF) {
				puts("ERROR: Unmatched '['");
			}
			
			interpret(*iptr++);
		}
		++iptr;
	}
		
	return;
}
