#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#define MAX_Line 10
#define MAX_Size 10
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Stack {
    NODE* top;
};

Stack* initializeStack() {
    Stack* stack = new Stack();
    stack->top = NULL;
    return stack;
}

void push(Stack*& s, int key) {
    NODE* tmp = new NODE();
    tmp->key = key;
    tmp->p_next = NULL;
    tmp->p_next = s->top;
    s->top = tmp;
}

bool isEmpty(Stack* s) {
    if (s->top == NULL) {
        return 1;
    }
    return 0;
}

int pop(Stack*& s) {
    if (s->top == NULL) {
        return -1;
    }
    NODE* tmp = s->top;
    s->top = s->top->p_next;
    int key = tmp->key;
    delete tmp;
    return key;
}

int size(Stack* s) {
    NODE* top = s->top;
    int count = 0;
    while (top != NULL) {
        ++count;
        top = top->p_next;
    }
    return count;
}

int main() {
    char* inputinfo[MAX_Line];
    Stack* stack;
    for (int i = 0; i < MAX_Line; i++) {
        inputinfo[i] = new char[MAX_Size];
    }
    fstream fileinput;
    fileinput.open("input.txt");
    if (!fileinput.is_open()) {
        cout << "Xay ra loi";
        return 0;
    }
    int count = 0;
    while (count < MAX_Line && fileinput.getline(inputinfo[count], MAX_Size)) {
        ++count;
    }
    fileinput.close();

    fstream fileoutput;
    fileoutput.open("output.txt");
    if (!fileoutput.is_open()) {
        cout << "Xay ra loi";
    }

    for (int i = 0; i < MAX_Line; i++) {
        if (strcmp(inputinfo[i], " ") == 0) {
            return 0;
        }
        if (strcmp(inputinfo[i], "init") == 0) {
            stack = initializeStack();
            fileoutput << "EMPTY" << endl;
        }
        else if (strcmp(inputinfo[i], "pop") == 0) {
            if (isEmpty(stack)) {
                fileoutput << "EMPTY" << endl;
            }
            else {
                int key = pop(stack);
                if (key != -1) {
                    if (stack->top == NULL) {
                        fileoutput << "EMPTY" << endl;
                    }
                    else {
                        NODE* curr = stack->top;
                        while (curr != NULL) {
                            fileoutput << curr->key << " ";
                            curr = curr->p_next;
                        }
                        fileoutput << endl;
                    }
                }
            }
        }
        else if (strcmp(inputinfo[i], "size") == 0) {
            int key = size(stack);
            fileoutput << key << endl;
        }
        else if (strncmp(inputinfo[i], "push", 4) == 0) {
            string str;
            for (int j = 5; j < MAX_Size && inputinfo[i][j] != '\0'; j++) {
                if (inputinfo[i][j] >= '0' && inputinfo[i][j] <= '9') {
                    str = str + inputinfo[i][j];
                }
            }
            if (!str.empty()) {
                int key = stoi(str);
                push(stack, key);
            }
            NODE* curr = stack->top;
            while (curr != NULL) {
                fileoutput << curr->key << " ";
                curr = curr->p_next;
            }
            fileoutput << endl;
        }
    }
    fileoutput.close();
    return 0;
}