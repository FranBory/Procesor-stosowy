#include <iostream>

using namespace std;


class Stack
{
    public:
		struct List {
			char c;
			List* next;
		};
        struct Node {
			List* list;
            Node* next;
        };
        Node* top;
        
        bool isEmptyStack() {
            if (this->top == NULL) return true;
            else return false;
        }
		bool isEmptyList(List* list) {
			if (list == NULL) return true;
			else return false;
		}
        void push_empty_list() {       // apostrof włóż na stos pustą listę
            Node* node = new Node;
            List* list = NULL;
            node->list = list;
            if (!isEmptyStack()) node->next = this->top;
            else node->next = NULL;
            this->top = node;
        }
		void push_list(List* list) { 
			Node* node = new Node;
			node->list = list;
			if (!isEmptyStack()) node->next = this->top;
			else node->next = NULL;
			this->top = node;
		}
        void push_node(Node* node) {
			if (node == NULL) return;
			Node* new_node = new Node;
			new_node->list = node->list;
			new_node->next = top;
			top = new_node;
        }
		void push_char(char c) {
			List* list = new List;
			if (!isEmptyList(this->top->list))
				list->next = this->top->list;
			else list->next = NULL;
			this->top->list = list; 
			list->c = c;
		}
        List* pop_list() {               // przecinek zdejmij listę ze stosu
            if (!isEmptyStack()) {
                Node* temp = top;
                top = top->next;
                List* c = temp->list;
                delete temp;  
                return c;
            }
            printf("stack empty\n");
            return NULL;
        }
		Node* pop_node() {               
			if (!isEmptyStack()) {
				Node* temp = top;
				top = top->next;
				return temp;
			}
			printf("stack empty\n");
			return NULL;
		}
		List* copy_list(List* to_copy) {         
			if (to_copy == NULL) return NULL; 
            List* copied = new List;
            copied->c = to_copy->c;
			copied->next = copy_list(to_copy->next); // Rekurencyjnie kopiujemy resztę listy
        }

		void copy_top() {         // dwukropek skopiuj listę na szczycie stosu
			if (!isEmptyStack()) {
				Node* temp = top;
				List* copied_list = copy_list(temp->list);
				Node* new_node = new Node;
				new_node->list = copied_list;
				new_node->next = top;
				top = new_node;
			}
			else printf("stack empty\n");
		}
		void swap_top2() {   // średnik zamień 2 listy na szczycie stosu
            Node* old_top = top;
			Node* new_top = top->next;
			old_top->list = new_top->list;
			new_top->list = old_top->list;
        }
		int list_to_int(List* list,int level) { // @ zamień listę na liczbę
			int result = 0;
			result = list->c - '0';
			if (list->next==nullptr) {
				return result*level;
			}
			else {
				result += list_to_int(list->next, level * 10);
			}
		}
        void print(Node* node) {
			if (node == NULL) return;
			else {
				
			}
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
			stos.push_empty_list();
        }
        else if (c == ',') {
			stos.pop_list();
		}
        else if (c == ':') {
			stos.copy_top();
        }
        else if (c == ';') {
			stos.swap_top2();
		}
		else if (c == '@') {
			
        }
        else if (c == '&') {
			stos.print();
		}
        else {
			stos.push_char(c);
        }
    }



    return 0;
}
