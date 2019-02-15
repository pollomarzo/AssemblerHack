typedef struct Node {
    int num;
    struct Node *prev;
} node;

typedef node *Stack;

int empty(Stack S);

void init(Stack *S);

void push(Stack *S, int d);

int pop(Stack *S);
