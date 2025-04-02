#include <iostream>

using namespace std;


class Stack
{
    private:
        struct Node {
            char c;
            Node* next;
        };
        
        Node* top;
        
        bool isEmpty() {
            if (this->top == NULL) return true;
            else return false;
        }

    public:
        Stack() {
            this->top = NULL;
        }
        void push(char c) {
            Node* node = new Node;
            node->c = c;
            if (!isEmpty()) node->next = this->top;
            else node->next = NULL;
            top = node;
        }
        char pop() {
            if (!isEmpty()){
                Node* temp = top;
                delete top;
                return temp->c;
            }
            cout << "stack empty" << endl;
            return 0;
        }
        void print() {
            Node* node = top;
            while (node != NULL)
            {
                cout << node->c << endl;
                node = node->next;
            }
        }

};



int main()
{
    Stack stos;
    stos.push('a');
    stos.push('b');
    stos.push('c');
    //stos.print();

    return 0;
}
