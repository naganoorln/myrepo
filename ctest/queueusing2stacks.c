#include <stdio.h>
#define MAX 100

int s1[MAX], s2[MAX];
int top1 = -1, top2 = -1;

void push1(int x) { s1[++top1] = x; }
void push2(int x) { s2[++top2] = x; }

int pop1() { return s1[top1--]; }
int pop2() { return s2[top2--]; }

int isEmpty1() { return top1 == -1; }
int isEmpty2() { return top2 == -1; }

void enqueue(int x) {
    push1(x);
}

int dequeue() {
    if (isEmpty2()) {
        while (!isEmpty1()) {
            push2(pop1());
        }
    }
    if (isEmpty2()) {
        printf("Queue empty\n");
        return -1;
    }
    return pop2();
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);

    printf("%d\n", dequeue()); // 10
    printf("%d\n", dequeue()); // 20
    printf("%d\n", dequeue()); // 30

    return 0;
}

