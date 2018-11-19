#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memset */
#include <ctype.h>//isdigit


#define	N	(10) // stack size

#define NUMB	(1)
#define OPER	(-1)
#define ERR	(1)
#define NOERR	(0)

int	stack[N];
int	element = 0;

void error_message(char* error) {
	printf("%s\n", error);
	exit(1);
}

void push(int nbr) {
	if (element >= N)
		error_message("Overflow");
	else
		stack[element++] = nbr;

}

int pop() {
	if (element < 0) {
		error_message("Empty Stack");
		return 0;

	}
	else {
		element--;
		int pop = stack[element];
		stack[element] = 0;
		//printf("%d\n", pop);
		return pop;

	}

}


void reset() {
	memset(stack, -1, sizeof(int) * N);
	element = 0;
}

void print_s() {
	printf("%s\n", "-----");
	for (int i = 0; i < N ; i++)
	printf("%d\n", stack[i]);
	printf("%s\n", "-----");
	printf("element %d\n", element);
}


void do_math(char op) {
	int	temp;
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

void read(){
	char	nbr_builder[10];
	size_t	index = 0;

	int	last = 0;
	int	print_line = 0;
	int	error = 0;
	int	strange = -1;
	int	c = 0;
	// (ch = getchar()) != EOF
	while (print_line < 4) {
		last = 0;
		print_line++;
		printf("%d\n", print_line);
		memset(nbr_builder, '\0', sizeof(char) * index);
		index = 0;
		while (c != '\n') {
		//printf("line = %d\n", print_line);
		// printf("c = %c\n", c);
		// printS();
			if (isdigit(c)) {
				nbr_builder[index++] = c;
				last = NUMB;


			} else if (c == ' ') {
				if (last == NUMB) {
					int nbr_done;
					sscanf(nbr_builder, "%d", &nbr_done);
					if (element >= N) {
						c = nbr_done + '0';
						error = ERR;

						break;
					}

					push(nbr_done);
					memset(nbr_builder, '\0', sizeof(char) * index);
					index = 0;

				}

			} else if (c == '+' || c == '-' || c == '/' || c == '*') {
				if (last == NUMB && nbr_builder[0] != '\0') {
					int nbr_done;
					sscanf(nbr_builder, "%d", &nbr_done);
					if (element >= N) {
						error = ERR;
						break;
					}
					push(nbr_done);
					memset(nbr_builder, '\0', sizeof(char) * index);
					index = 0;
				}
				last = OPER;

				if (c == '/' && stack[element-1] == 0) {
					error = ERR;
					break;
				}


				if (element <= 1) {
					error = ERR;
					break;
				}else {
					do_math(c);

				}


			} else {
				error = ERR;
				strange = 1;
				break;
			}

		}


		// PRINT LINE RESULT

		printf("line %d: ", print_line);
		if (strange != 1 && (c == '\n' && (element != 1 || last != OPER))){
			if(element != 0)
				printf("error at \\n\n");

		}else {
			if (error == ERR) {

				printf("error at %c\n", c);

				while (c != '\n') {
					c = getchar();

				}
			}
			else
				printf("%d\n", pop());


		}


		strange = -1;
		error = NOERR;
		c = 0;
		reset();



	}
}






int main(void)
{

	read();
	return 0;
}
