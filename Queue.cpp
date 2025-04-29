#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#define MAX_Size 15
#define MAX_Line 10
using namespace std;
struct NODE {
    int key;
    NODE* p_next;
};
struct Queue {
    NODE* head;
    NODE* tail;
};
Queue* initializeQueue() {
    Queue* queue = new Queue();
    return queue;
}
void enqueue(Queue*& q, int key) {
    NODE* tmp = new NODE();
    tmp->key = key;
    tmp->p_next = NULL;
    if (q->head == NULL) {
        q->head = tmp;
        q->tail = tmp;
        return;
    }
    q->tail->p_next = tmp;
    q->tail = tmp;
}
int dequeue(Queue*& q) {
    if (q->head == NULL) {
        q->tail = NULL;
        return -1;
    }
    NODE* Delete = q->head;
    int key = q->head->key;
    q->head = q->head->p_next;
    delete Delete;
    return key;
}
int size(Queue* q) {
    NODE* curr = q->head;
    int count = 0;
    while (curr != NULL) {
        ++count;
        curr = curr->p_next;
    }
    return count;
}
bool isEmpty(Queue* q) {
    if (q->head == NULL) {
        return 1;
    }
    return 0;
}
int main() {
    Queue* queue = NULL;
    char* inputinfo[MAX_Line];
    for (int i = 0; i < MAX_Line; i++) {
        inputinfo[i] = new char[MAX_Size];
    }
    fstream fileinput;
    fileinput.open("input.txt");
    if (!fileinput.is_open()) {
        cout << "Xay ra loi" << endl;
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
        cout << "Xay ra loi" << endl;
        return 0;
    }
    for (int i = 0; i < MAX_Line; i++) {
        if (strcmp(inputinfo[i], "init") == 0) {
            queue = initializeQueue();
            fileoutput << "EMPTY" << endl;
        }
        else if (strcmp(inputinfo[i], "dequeue") == 0) {
            if (isEmpty(queue)) {
                fileoutput << "EMPTY" << endl;
            }
            else {
                int key = dequeue(queue);
                if (key != -1) {
                    if (queue->head == NULL) {
                        fileoutput << "EMPTY" << endl;
                    }
                    else {
                        NODE* curr = queue->head;
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
            int count = size(queue);
            fileoutput << count << endl;
        }
        else if (strcmp(inputinfo[i], " ") == 0) {
            fileoutput << endl;
        }
        else if (strncmp(inputinfo[i], "enqueue", 7) == 0) {
            string str;
            for (int j = 8; j < MAX_Size && inputinfo[i][j] != '\0'; j++) {
                if (inputinfo[i][j] >= '0' && inputinfo[i][j] <= '9') {
                    str = str + inputinfo[i][j];
                }
            }
            int key = stoi(str);
            enqueue(queue, key);
            NODE* curr = queue->head;
            while (curr != NULL) {
                fileoutput << curr->key << " ";
                curr = curr->p_next;
            }
            fileoutput << endl;
        }
    }
    fileoutput.close();
}