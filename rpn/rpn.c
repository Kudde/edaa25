#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N (10)
#define TRUE (1)
#define FALSE (-1)

int stack[N];
int element = 0;

void push(int nbr) {
	stack[element++] = nbr;
}

int pop(){
	element--;
	int pop = stack[element];
	stack[element] = 0;
	return pop;
}

void reset() {
	memset(stack, -1, sizeof(int) * N);
	element = 0;
}

void do_math(char op) {
	int temp;
	switch (op) {
		case '+':
			push(pop() + pop());
			break;
		case '-':
			temp = pop();
			push(pop() - temp);
			break;
		case '/':
			temp = pop();
			push(pop() / temp);
			break;
		case '*':
			push(pop() * pop());
			break;
	}

}


int main() {
	char nr_b[10];
	size_t b_i = 0;
	size_t line = 1;
	int c = 0;
	int last_nbr = 0;
	int error = 0;

	while ((c = getchar()) != EOF && line) {
		error = FALSE;
		if (isdigit(c)) {
                        nr_b[b_i++] = c;
                        last_nbr = TRUE;


                } else if (c == ' ') {
			if (last_nbr == TRUE) {
				int nbr_done = 0;
				sscanf(nr_b, "%d", &nbr_done);
				memset(nr_b, '\0', sizeof(char) * b_i);
				b_i = 0;
				if (element >= N) {
					c = nbr_done + '0';
                                	error = TRUE;
				} else {
					push(nbr_done);
				}
                        }
		} else if (c == '+' || c == '-' || c == '/' || c == '*') {
			if (last_nbr && nr_b[0] != '\0') {
				int nbr_done = 0;
				sscanf(nr_b, "%d", &nbr_done);
				memset(nr_b, '\0', sizeof(char) * b_i);
				b_i = 0;
				if (element >= N){
					c = nbr_done + '0';
					error = TRUE;
				} else {
					push(nbr_done);
				}
                        }
			if (c == '/' && stack[element-1] == 0) {
				error = TRUE;
			} else if (element <= 1) {
				error = TRUE;
			} else {
				do_math(c);
			}
			last_nbr = FALSE;

		} else if (c == '\n' && error == FALSE && last_nbr == FALSE) {
			printf("line %zu: %d\n", line, pop());
			reset();
			line++;
		} else {
			error = TRUE;
		}

		if (error == TRUE) {
			if (c == '\n') {
				memset(nr_b, '\0', sizeof(char) * b_i);
				b_i = 0;
				printf("line %zu: error at \\n\n", line);

			} else {
				printf("line %zu: error at %c\n", line, c);
				while (c != '\n')
					c = getchar();
			}


			reset();
			line++;
		}

	}
	return 0;

}
