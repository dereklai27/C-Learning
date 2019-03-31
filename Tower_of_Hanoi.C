#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

//Below is the implementation of stack by dynamic allocation since user will prompt number of levels of the tower. 
//We cannot simply use array because it will return error when the array is passing a non-static variable.

struct Stack {
	int top;
	unsigned thesize;
	int* array;
};

struct Stack* createStack(unsigned thesize) {
	struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
	stack->thesize = thesize;
	stack->top = -1;
	stack->array = (int*)malloc(stack->thesize * sizeof(int));
	return stack;
}

int isFull(struct Stack* stack) {
	return stack->top == stack->thesize - 1;
}

int isEmpty(struct Stack* stack) {
	return stack->top == -1;
}

void push(struct Stack* stack, int item) {
	if (isFull(stack)) {
		return;
	}
	stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
	if (isEmpty(stack)) {
		return INT_MIN;
	}
	return stack->array[stack->top--];
}

int peek(struct Stack* stack) {
	if (isEmpty(stack)) {
		return INT_MIN;
	}
	return stack->array[stack->top];
}

//checkwin will decide if one of the tower is having all elements from the tower 1;
int checkwin(struct Stack* stack2, struct Stack* stack3) {
	return (isFull(stack2) || isFull(stack3));
}

//checkmove will decide if user is moving a value from a tower that is small than the top value of another tower.
//It also allows user to put the ring on the empty tower.
int checkmove(struct Stack* stack1, struct Stack* stack2) {
	if (peek(stack1) < peek(stack2) || isEmpty(stack2) && !(isEmpty(stack1) && isEmpty(stack2)) ) {
		return 1;
	}
	else {
		return 0;
	}
}

//The action of moving the ring from one tower to another will be performed by makemove function.
void makemove(struct Stack* stack1, struct Stack* stack2) {
	int temp = pop(stack1);
	push(stack2, temp);
}

//assigntower reads the values when player choose 2 towers to take actions, then assign which towers need to be considered.
void assigntower(struct Stack* stack1, struct Stack* stack2, struct Stack* stack3, int from, int to, int *flag) {
	if (from == 1 && to == 2) {
		if (checkmove(stack1, stack2)) {
			makemove(stack1, stack2);
			*flag = 0;
		}

	}
	if (from == 1 && to == 3) {
		if (checkmove(stack1, stack3)) {
			makemove(stack1, stack3);
			*flag = 0;
		}
	}
	if (from == 2 && to == 1) {
		if (checkmove(stack2, stack1)) {
			makemove(stack2, stack1);
			*flag = 0;
		}
	}
	if (from == 2 && to == 3) {
		if (checkmove(stack2, stack3)) {
			makemove(stack2, stack3);
			*flag = 0;
		}
	}
	if (from == 3 && to == 1) {
		if (checkmove(stack3, stack1)) {
			makemove(stack3, stack1);
			*flag = 0;
		}
	}
	if (from == 3 && to == 2) {
		if (checkmove(stack3, stack2)) {
			makemove(stack3, stack2);
			*flag = 0;
		}
	}
}

//nullpush will push NULL values to the tower to make it available for printing.
void nullpush(struct Stack* stack1) {
	while (!isFull(stack1)) {
		push(stack1, NULL);
	}
}

//nullpop will pop all NULL values from the tower to recover the state of tower after printing.
void nullpop(struct Stack* stack1) {
	while (stack1->array[stack1->top] == NULL) {
		pop(stack1);
	}
}

//printtower prints the number of step, then prints the tower verticially.
void printtower(struct Stack* stack1 , struct Stack* stack2, struct Stack* stack3, int towerlevel, int step) {


	nullpush(stack1);
	nullpush(stack2);
	nullpush(stack3);
	for (int x = stack1->thesize - 1; x >= 0; x--) {
		if (stack1->array[x] == NULL) {
			printf("---x---");
		}
		if (stack1->array[x] < 10 && stack1->array[x] >0) {
			printf("<==%d==>", stack1->array[x]);
		}
		if (stack1->array[x] >= 10 && stack1->array[x] < 100) {
			printf("<=%d %d=>", stack1->array[x] / 10, stack1->array[x] % 10);
		}
		if (stack1->array[x] == 100) {
			printf("<=%d=>", stack1->array[x]);
		}
		printf("\t");
		if (stack2->array[x] == NULL) {
			printf("---x---");
		}
		if (stack2->array[x] < 10 && stack2->array[x] >0) {
			printf("<==%d==>", stack2->array[x]);
		}
		if (stack2->array[x] >= 10 && stack2->array[x] < 100) {
			printf("<=%d %d=>", stack2->array[x] / 10, stack2->array[x] % 10);
		}
		if (stack2->array[x] == 100) {
			printf("<=%d=>", stack2->array[x]);
		}
		printf("\t");
		if (stack3->array[x] == NULL) {
			printf("---x---");
		}
		if (stack3->array[x] < 10 && stack3->array[x] >0) {
			printf("<==%d==>", stack3->array[x]);
		}
		if (stack3->array[x] >= 10 && stack3->array[x] < 100) {
			printf("<=%d %d=>", stack3->array[x] / 10, stack3->array[x] % 10);
		}
		if (stack3->array[x] == 100) {
			printf("<=%d=>", stack3->array[x]);
		}


		printf("\n");
	}
	printf("\n\nStep %d... \n", step);
	nullpop(stack1);
	nullpop(stack2);
	nullpop(stack3);

}
int main()
{
	// initialization
	int towerlevel = 101;
	int fromtower = -1;
	int totower = -1;
	int step = 1;
	int flag = 1;
	int decision = 1;
	//To calculate the time elasped, this program implemented time.h to calculate end time subtracted by start time.
	time_t start_t, end_t;
	double diff_t;

	//start the tower game.
	while (decision == 1) {
		time(&start_t);
		while (towerlevel > 100 || towerlevel < 1) {
			printf("Choose the tower level, maximum is 100: ");
		}
		scanf_s("%d", &towerlevel);
		printf("\n");

		struct Stack* tower1 = createStack(towerlevel);
		struct Stack* tower2 = createStack(towerlevel);
		struct Stack* tower3 = createStack(towerlevel);

		for (int i = towerlevel; i > 0; i--) {
			push(tower1, i);
		}


		while (checkwin(tower2, tower3) != 1) {
			printtower(tower1, tower2, tower3, towerlevel, step);
			printf("\n");
			while (flag) {
				printf("choose tower you want to move: ");
				scanf_s("%d", &fromtower);
				printf("choose tower you are moving to: ");
				scanf_s("%d", &totower);
				printf("\n");
				assigntower(tower1, tower2, tower3, fromtower, totower, &flag);
			}

			flag = 1;
			step += 1;
		}

		time(&end_t);
		diff_t = difftime(end_t, start_t);
		printtower(tower1, tower2, tower3, towerlevel, step);

		//after winning the game.
		printf("You won, the number of steps that you have made is %d, time used is %.0f seconds. \n\n", step, diff_t); // here print the time elasped.
		printf("Retry, press 1; Exit, press any number else. ");
		scanf_s("%d", &decision);
		printf("\n");
	}
	
	//exit.
	printf("Thanks for playing the game.\n");
	
	system("Pause");
	return 0;
}