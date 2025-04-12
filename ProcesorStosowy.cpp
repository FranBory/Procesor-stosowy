#include <iostream>

using namespace std;

typedef struct Instructions {
	int id;
	char c;
	struct Instructions* next;
} Instructions;

typedef struct {
	Instructions* head;  
	Instructions* tail;  
} InstrList;

typedef struct List {
	char c;
	struct List* next;
} List;

typedef struct Node {
	List* list;
	struct Node* next;
} Node;



bool isEmptyStack(Node* top) {
	if (top == NULL) {
		//cout << "tru";
		return true;
	}
	else {
		//cout << "fals";
		return false;
	}
}
bool isEmptyList(List* list) {
	if (list == NULL) return true;
	else return false;
}
bool isEmptyInstr(Instructions* instr) {
	if (instr == NULL) return true;
	else return false;
}

void push_instruction(InstrList* instr, char c,int id) { 
	Instructions* newInstr = new Instructions;
	newInstr->c = c;
	newInstr->id = id;
	newInstr->next = NULL;
	if (instr->head != NULL) {
		instr->tail->next = newInstr;
		instr->tail = newInstr;
	}
	else {
		instr->head = newInstr;
		instr->tail = newInstr;
	}
}
void push_empty_list(Node** top) {       // apostrof włóż na stos pustą listę
	Node* node = new Node;
	List* list = NULL;
	node->list = list;
	if (!isEmptyStack(*top)) node->next = *top;
	else node->next = NULL;
	*top = node;
}
void push_list(List* list,Node** top) {
	Node* node = new Node;
	node->list = list;
	if (!isEmptyStack(*top)) node->next = *top;
	else node->next = NULL;
	*top = node;
}
void push_node(Node* node, Node** top) {
	if (node == NULL) return;
	Node* new_node = new Node;
	new_node->list = node->list;
	new_node->next = *top;
	*top = new_node;
}
void push_char(char c, Node** top) {
	List* list = new List;
	if (!isEmptyList((*top)->list)) list->next = (*top)->list;
	else list->next = NULL;
	(*top)->list = list;
	list->c = c;
}
List* pop_list(Node** top) {               // przecinek zdejmij listę ze stosu
	if (!isEmptyStack(*top)) {
		Node* temp = *top;
		*top = (*top)->next;
		List* c = temp->list;
		delete temp;
		return c;
	}
	printf("stack empty\n");
	return NULL;
}
Node* pop_node(Node** top) {
	if (!isEmptyStack(*top)) {
		Node* temp = *top;
		*top = (*top)->next;
		return temp;
	}
	printf("stack empty\n");
	return NULL;
}
List* copy_list(List* to_copy) {
	if (to_copy == NULL) return NULL;
	List* new_list = new List;
	new_list->c = to_copy->c;
	new_list->next = copy_list(to_copy->next);
	return new_list;
}

void copy_top(Node** top) {         // dwukropek skopiuj listę na szczycie stosu
	if (!isEmptyStack(*top)) {
		Node* temp = *top;
		List* copied_list = copy_list(temp->list);
		Node* new_node = new Node;
		new_node->list = copied_list;
		new_node->next = *top;
		*top = new_node;
	}
	else printf("stack empty\n");
}
void swap_top2(Node** top) {   // średnik zamień 2 listy na szczycie stosu
	List* old_top = (*top)->list;
	(*top)->list = (*top)->next->list;
	(*top)->next->list = old_top;
}
int list_to_int(List* list, int level) {
	int result = 0;
	if (list != NULL) {
		result = (list->c - '0') * level;
		return list_to_int(list->next, level * 10) + result;
	}
	else return 0;
}
Node* get_by_index(Node* node, int index) {
	if (index == 0) return node;
	else return get_by_index(node->next, index - 1);
}
void copyByIndex(Node** top) {
	Node* popped = pop_node(top);
	int indx = list_to_int(popped->list, 1);
	delete popped;
	Node* toCopy = get_by_index((*top), indx);
	push_list(copy_list(toCopy->list),top);
}

void printList(List* list) {
	if (list == NULL) return;
	else {
		printf("%c", list->c);
		printList(list->next);
	}
}
void printStack(Node* node, int i) {
	if (node == NULL) return;
	else {
		printStack(node->next, i + 1);
		printf("%d: ", i);
		if (node->list != NULL) {
			printList(node->list);
			printf("\n");
		}
		else {
			printf("\n");
		}
	}
}
void readChar(Node** stos,InstrList* numbs) {
	push_char(numbs->head->c, stos);
	numbs->head = numbs->head->next;
}

void doAllInstructions(Instructions* instr,Node** stos, InstrList* numbs, int size) {
	if (instr->c == '\'') push_empty_list(stos);
	else if (instr->c == ',') pop_list(stos);
	else if (instr->c == ':') copy_top(stos);
	else if (instr->c == ';') swap_top2(stos);
	else if (instr->c == '@') copyByIndex(stos);
	else if (instr->c == '&') printStack(*stos, 0);
	else if (instr->c == '.') readChar(stos, numbs);
	else push_char(instr->c, stos);
	if (instr->id == size) return;
	else doAllInstructions(instr->next, stos, numbs, size);
}


int main()
{
	Instructions* instr = NULL;
	InstrList instrList;
	instrList.head = NULL;
	instrList.tail = NULL;
	Instructions* numbs = NULL;
	InstrList numbsList;
	numbsList.head = NULL;
	numbsList.tail = NULL;
	Node* stos = NULL;
	char c;
	int breakpoint = 0, id = 0;
	while (breakpoint != 2) {
		c = getchar();
		if (c == '\n') breakpoint++;
		else if (breakpoint == 0) {
			push_instruction(&instrList, c, id);
			id++;
		}
		else push_instruction(&numbsList, c, 0);
	}
	doAllInstructions(instrList.head, &stos, &numbsList, id-1);

	return 0;
}
