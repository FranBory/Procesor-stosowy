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
        void push_empty() {
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
            printf("stack empty\n");
            return 0;
        }
        void print() {
            Node* node = top;
			int i = 0;
            while (node != NULL)
            {
				printf("%d: %c\n",&i, node->c);
                node = node->next;
				i++;
            }
        }
		void copy_top() {
			char c = this->pop();
			this->push(c);
            this->push(c);
		}
		void swap() {
			char c1 = this->pop();
			char c2 = this->pop();
			this->push(c1);
			this->push(c2);
		}


};



int main()
{
    Stack stos;
    char c, temp;
	int breakpoint = 0;
    while (breakpoint!=2) {
        c = getchar();
		if (c == '\n') breakpoint++;
        else if (c=='\'') {
			stos.push_empty();
        }
        else if (c == ',') {
			temp = stos.pop();
		}
        else if (c == ':') {
			stos.copy_top();
        }
        else if (c == ';') {
			stos.swap();
		}
		else if (c == '@') {

        }
    }



    return 0;
}
