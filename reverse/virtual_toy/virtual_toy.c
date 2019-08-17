#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NO_PARAM 0xdeadc0de

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(0[arr]))

enum opcode {
	OP_IN,
	OP_OUT,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_MOD,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_BIT_NOT,
	OP_LOG_NOT,
	OP_NEG,
	OP_SHR,
	OP_SHL,
	OP_JMP,
	OP_BR,
	OP_PUSH,
	OP_POP,
	OP_DUP,
	OP_RET,
};

struct opcode_param {
	enum opcode opcode;
	int param;
};

static int stack[4096];
static int stack_top = -1;
static int ip = 0;
static struct opcode_param check_prog[] = {
	{ OP_PUSH, 0 }, // check (0) // push ciphertext
	{ OP_PUSH, 12596 },
	{ OP_PUSH, 14668 },
	{ OP_PUSH, 14500 },
	{ OP_PUSH, 14668 },
	{ OP_PUSH, 14696 },
	{ OP_PUSH, 14724 },
	{ OP_PUSH, 14500 },
	{ OP_PUSH, 14724 },
	{ OP_PUSH, 14668 },
	{ OP_PUSH, 14528 },
	{ OP_PUSH, 14500 },
	{ OP_PUSH, 14752 },
	{ OP_PUSH, 13436 },
	{ OP_PUSH, 12904 },
	{ OP_PUSH, 13268 },
	{ OP_PUSH, 12848 },
	{ OP_PUSH, 12848 },
	{ OP_PUSH, 13268 },
	{ OP_PUSH, 13352 },
	{ OP_PUSH, 13436 },
	{ OP_PUSH, 12876 },
	{ OP_PUSH, 13156 },
	{ OP_PUSH, 13436 },
	{ OP_PUSH, 12820 },
	{ OP_PUSH, 13044 },
	{ OP_PUSH, 13268 },
	{ OP_PUSH, 12932 },
	{ OP_PUSH, 12652 },
	{ OP_PUSH, 13212 },
	{ OP_PUSH, 13380 },
	{ OP_PUSH, 13072 },
	{ OP_PUSH, 13240 },
	{ OP_DUP, NO_PARAM }, // loop (33)
	{ OP_LOG_NOT, NO_PARAM },
	{ OP_PUSH, 68 /* good */ },
	{ OP_BR, NO_PARAM },
	{ OP_IN, NO_PARAM },
	{ OP_PUSH, 10 },
	{ OP_ADD, NO_PARAM },
	{ OP_PUSH, 1337 },
	{ OP_MUL, NO_PARAM },
	{ OP_PUSH, 191 },
	{ OP_DIV, NO_PARAM },
	{ OP_PUSH, 0xfff },
	{ OP_XOR, NO_PARAM },
	{ OP_NEG, NO_PARAM },
	{ OP_BIT_NOT, NO_PARAM },
	{ OP_PUSH, 2 },
	{ OP_SHL, NO_PARAM },
	{ OP_XOR, NO_PARAM },
	{ OP_LOG_NOT, NO_PARAM },
	{ OP_PUSH, 33 /* loop */ },
	{ OP_BR, NO_PARAM },
	{ OP_PUSH, 'E' }, // bad (54)
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'r' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'r' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'o' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'r' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, '\n' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 1 },
	{ OP_RET, NO_PARAM },
	{ OP_PUSH, 'A' }, // good (68)
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'c' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'c' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'e' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 's' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 's' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, ' ' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'g' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'r' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'a' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'n' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 't' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'e' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 'd' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, '\n' },
	{ OP_OUT, NO_PARAM },
	{ OP_PUSH, 0 },
	{ OP_RET, NO_PARAM },
};

static void die(const char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

static int pop(void)
{
	if (stack_top < 0) {
		die("Stack underflow");
	}
	return stack[stack_top--];
}

static void push(int param)
{
	if (stack_top + 1 >= (int) ARRAY_LEN(stack)) {
		die("Stack overflow");
	}
	stack[++stack_top] = param;
}

static int check(void)
{
	int x, y, c, target, cond;

	for (;;) {
		if (ip < 0 || ip >= (int) ARRAY_LEN(check_prog)) {
			die("Instruction pointer out of bounds");
		}
		struct opcode_param *opcode = &check_prog[ip];
		switch (opcode->opcode) {
		case OP_IN:
			c = getchar();
			push(c);
			ip++;
			break;
		case OP_OUT:
			c = pop();
			if (c < 0 || c > 127) {
				die("Output is not ascii");
			}
			usleep(1000000 / 10);
			putchar(c);
			fflush(stdout);
			ip++;
			break;
		case OP_ADD:
			x = pop();
			y = pop();
			push(x + y);
			ip++;
			break;
		case OP_SUB:
			x = pop();
			y = pop();
			push(x - y);
			ip++;
			break;
		case OP_MUL:
			x = pop();
			y = pop();
			push(x * y);
			ip++;
			break;
		case OP_DIV:
			x = pop();
			y = pop();
			push(y / x);
			ip++;
			break;
		case OP_MOD:
			x = pop();
			y = pop();
			push(x % y);
			ip++;
			break;
		case OP_AND:
			x = pop();
			y = pop();
			push(x & y);
			ip++;
			break;
		case OP_OR:
			x = pop();
			y = pop();
			push(x | y);
			ip++;
			break;
		case OP_XOR:
			x = pop();
			y = pop();
			push(x ^ y);
			ip++;
			break;
		case OP_BIT_NOT:
			x = pop();
			push(~x);
			ip++;
			break;
		case OP_LOG_NOT:
			x = pop();
			push(!x);
			ip++;
			break;
		case OP_NEG:
			x = pop();
			push(-x);
			ip++;
			break;
		case OP_SHR:
			x = pop();
			y = pop();
			push(y >> x);
			ip++;
			break;
		case OP_SHL:
			x = pop();
			y = pop();
			push(y << x);
			ip++;
			break;
		case OP_JMP:
			ip = pop();
			break;
		case OP_BR:
			target = pop();
			cond = pop();
			if (cond) {
				ip = target;
			} else {
				ip++;
			}
			break;
		case OP_PUSH:
			push(opcode->param);
			ip++;
			break;
		case OP_POP:
			(void) pop();
			ip++;
			break;
		case OP_DUP:
			push(stack[stack_top]);
			ip++;
			break;
		case OP_RET:
			return pop();
		default:
			die("Unknown opcode");
		}
	}
}

int main(void)
{
	fputs("Virtual Toy (C) 1991 VMBox Technologies\n", stderr);
	fputs("Enter access code: ", stderr);
	return check();
}
