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

typedef struct ListNode {
	char c;
	struct ListNode* next;
} ListNode;

typedef struct {
	ListNode* head;  
	ListNode* tail;
} List;

typedef struct Node {
	List* list;
	struct Node* next;
} Node;

bool isEmptyStack(Node* top) {
	if (top == NULL) return true;
	else return false;
}
bool isEmptyList(List* list) {
	if (list->head == NULL) return true;
	else return false;
}
bool isEmptyInstr(Instructions* instr) {
	if (instr == NULL) return true;
	else return false;
}

void push_instruction(InstrList* instr, char c,int* id) { 
	Instructions* newInstr = new Instructions;
	newInstr->c = c;
	newInstr->id = *id;
	if (c != '?') (*id)++;
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

void push_numbs(List* numbs, char c, int id) {
	ListNode* newNumb = new ListNode;
	newNumb->c = c;
	newNumb->next = NULL;
	if (numbs->head != NULL) {
		numbs->tail->next = newNumb;
		numbs->tail = newNumb;
	}
	else {
		numbs->head = newNumb;
		numbs->tail = newNumb;
	}
}
void push_empty_list(Node** top) {       // apostrof włóż na stos pustą listę
	Node* node = new Node;
	List* list = new List;
	list->head = NULL;
	list->tail = NULL;
	node->list = list;
	if (!isEmptyStack(*top)) node->next = *top;
	else node->next = NULL;
	*top = node;
}
void push_list(List* list,Node** top) {          //TODO fix
	Node* node = new Node;
	node->list = list;
	if (!isEmptyStack(*top)) node->next = *top;
	else node->next = NULL;
	*top = node;
}
void push_node(Node* node, Node** top) {     //TODO check if it works
	if (node == NULL) return;
	node->next = *top;
	*top = node;
}
void push_char(char c, List** list) {
	ListNode* listNode = new ListNode;
	listNode->c = c;
	if (!isEmptyList(*list)) {
		listNode->next = (*list)->head;
		(*list)->head = listNode;
	}
	else {
		(*list)->head = listNode;
		(*list)->tail = listNode;
		listNode->next = NULL;
	}
}
List* pop_list(Node** top) {               // przecinek zdejmij listę ze stosu
	if (!isEmptyStack(*top)) {
		Node* temp = *top;
		*top = (*top)->next;
		List* c = temp->list;
		delete temp;
		return c;
	}
	else {
		printf("stack empty\n");
		return NULL;
	}
}
Node* pop_node(Node** top) {
	if (!isEmptyStack(*top)) {
		Node* temp = *top;
		*top = (*top)->next;
		return temp;
	}
	else {
		printf("stack empty\n");
		return NULL;
	}
}
void copy_list(List** copied, List* to_copy, ListNode* node ) {
	if (node == NULL) return;
	ListNode* new_node = new ListNode;
	new_node->c = node->c;
	new_node->next = NULL;
	if ((*copied)->head == NULL) {
		(*copied)->head = new_node;
		(*copied)->tail = new_node;
	}
	else {
		(*copied)->tail->next = new_node;
		(*copied)->tail = new_node;
	}
	copy_list(copied, to_copy, node->next);
}
void copy_top(Node** top) {         // dwukropek skopiuj listę na szczycie stosu
	if (!isEmptyStack(*top)) {
		Node* node = new Node;
		List* copied_list = new List;
		copied_list->head = NULL;
		copied_list->tail = NULL;
		copy_list(&copied_list, (*top)->list, (*top)->list->head);
		node->list = copied_list;
		push_node(node, top);
	}
	else printf("stack empty\n");
}
void swap_top2(Node** top) {   // średnik zamień 2 listy na szczycie stosu
	List* old_top = (*top)->list;
	(*top)->list = (*top)->next->list;
	(*top)->next->list = old_top;
}
long long list_to_int(List* list,ListNode* node, int level) {
	long long result = 0;
	result = (node->c - '0') * level;
	if (node != list->tail) {
		return list_to_int(list, node->next, level * 10) + result;
	}
	else return result;
}
Node* get_by_index(Node* node, long long index) {
	if (index == 0) return node;
	else return get_by_index(node->next, index - 1);
}
void copyByIndex(Node** top) {
	Node* popped = pop_node(top);
	long long indx = list_to_int(popped->list, popped->list->head, 1);
	delete popped;
	Node* toCopy = get_by_index((*top), indx);
	Node* node = new Node;
	List* copied_list = new List;
	copied_list->head = NULL;
	copied_list->tail = NULL;
	copy_list(&copied_list, toCopy->list, toCopy->list->head);
	node->list = copied_list;
	push_node(node, top);
}

void printList(ListNode* node,List* list) {
	if (isEmptyList(list)) return;
	else {
		printf("%c", node->c);
		if (node != list->tail) printList(node->next, list);
	}
}
void printStack(Node* node, int i) {
	if (node == NULL) return;
	else {
		printStack(node->next, i + 1);
		printf("%d: ", i);
		if (node->list != NULL) printList(node->list->head, node->list);
		printf("\n");
	}
}
void readChar(Node** stos, List** numbs) {
	push_char((*numbs)->head->c, &((*stos)->list));
	(*numbs)->head = (*numbs)->head->next;
}
void printFirstChar(Node** node) {
	Node* popped = pop_node(node);
	printf("%c", popped->list->head->c);
	delete popped;
}
void deleteTail(List** list, ListNode* node){
	if (node == NULL) return;
	if (node->next == (*list)->tail) {
		node->next = NULL;
		delete (*list)->tail;
		(*list)->tail = node;
	}
	else deleteTail(list, node->next);
}
void absolute(List** list) {
	if (isEmptyList(*list)) return;
	else if ((*list)->tail->c == '-') {
		if ((*list)->head == (*list)->tail) {
			(*list)->head = NULL;
			(*list)->tail = NULL;
		}
		else deleteTail(list, (*list)->head);
	}
	else return;
}
void pushMinus(List** list) {
	if (!isEmptyList(*list)) {
		if ((*list)->tail->c != '-') {
			(*list)->tail->next = new ListNode;
			(*list)->tail->next->c = '-';
			(*list)->tail->next->next = NULL;
			(*list)->tail = (*list)->tail->next;
		}
		else absolute(list);
	}
	else push_char('-', list);
}
void clearListNode(ListNode* node) {
	if (node == NULL) return;
	clearListNode(node->next);
	delete node;
}
void clearList(List** list) {
	if (isEmptyList(*list)) return;
	clearListNode((*list)->head);
	(*list)->head = NULL;
	(*list)->tail = NULL;

}
void pushAsASCII(Node** stos) {
	long long i = list_to_int((*stos)->list, (*stos)->list->head,1);
	clearList(&((*stos)->list));
	char c = (char)i;
	push_char(c, &((*stos)->list));
}

void pushInt(Node** stos,int i) {
	if (i < 10) {
		push_char(i + '0', &((*stos)->list));
	}
	else if (i < 100) {
		int j = i % 10;
		i = i / 10;
		push_char(i + '0', &((*stos)->list));
		push_char(j + '0', &((*stos)->list));
	}
	else {
		int j = i % 10;
		i = i / 10;
		int k = i % 10;
		i = i / 10;
		push_char(i + '0', &((*stos)->list));
		push_char(k + '0', &((*stos)->list));
		push_char(j + '0', &((*stos)->list));
	}
}

void pushHeadASCII(Node** stos) {
	char c = (*stos)->list->head->c;
	clearList(&((*stos)->list));
	int i = (int)c;
	pushInt(stos, i);
}
void pushHead(Node** stos) {
	if (!isEmptyStack(*stos)) {
		char c = (*stos)->list->head->c;
		if ((*stos)->list->head != (*stos)->list->tail) {
			(*stos)->list->head = (*stos)->list->head->next;
		}
		else {
			delete (*stos)->list->head;
			(*stos)->list->head = NULL;
			(*stos)->list->tail = NULL;
		}
		push_empty_list(stos);
		push_char(c, &((*stos)->list));
	}
	else printf("stack empty\n");
}
void connectTop2(Node** stos) {
	Node* popped = pop_node(stos);
	(*stos)->list->tail->next = popped->list->head;
	(*stos)->list->tail = popped->list->tail;
	delete popped;
}
void comperTop2(Node** stos) {
	Node* a = pop_node(stos);
	Node* b = pop_node(stos);
	long long iA = list_to_int(a->list, a->list->head, 1);
	long long iB = list_to_int(b->list, b->list->head, 1);
	delete a;
	delete b;
	push_empty_list(stos);
	if (iB < iA) push_char('1', &((*stos)->list));
	else push_char('0', &((*stos)->list));
}
void isEqualTop2(Node** stos) {
	Node* a = pop_node(stos);
	Node* b = pop_node(stos);
	delete a;
	delete b;
	long long iA = list_to_int(a->list, a->list->head, 1);
	long long iB = list_to_int(b->list, b->list->head, 1);
	push_empty_list(stos);
	if (iB == iA) push_char('1', &((*stos)->list));
	else push_char('0', &((*stos)->list));
}
void pushId(Node** stos,int id) {
	push_empty_list(stos);
	pushInt(stos, id);
}
void neagtion(Node** stos) {
	if (isEmptyList((*stos)->list)) push_char('1', &((*stos)->list));
	else if ((*stos)->list->head == (*stos)->list->tail && (*stos)->list->head->c == '0') (*stos)->list->head->c = '1';
	else {
		Node * poped = pop_node(stos);
		delete poped;
		push_empty_list(stos);
		push_char('0', &((*stos)->list));
	}
}
Instructions* iterToID(Instructions* instr,int id) {
	if (instr->id == id) return instr;
	else if (instr->next == NULL) return NULL;
	else return iterToID(instr->next, id);
}
void jumpToInstr(Instructions** instr,Node** stos) {
	Node* t = pop_node(stos);
	Node* w = pop_node(stos);
	if (!isEmptyList(w->list) && (w->list->head != w->list->tail && w->list->head->c =='0')) {
		int i = list_to_int(t->list, t->list->head, 1);	
		(*instr)->next = iterToID(*instr, i);
	}
	delete t;
	delete w;
}

void doAllInstructions(InstrList* list, Instructions* instr,Node** stos, List* numbs) {
	switch (instr->c) {
	case '\'': 
		push_empty_list(stos);
		break;
	case ',': 
		pop_list(stos);
		break;
	case '.':
		readChar(stos, &numbs);
		break;
	case ':': 
		copy_top(stos);
		break;
	case ';': 
		swap_top2(stos);
		break;
	case '@': 
		copyByIndex(stos);
		break;
	case '&': 
		printStack(*stos, 0);
		break;
	case '=': 
		comperTop2(stos);
		break;
	case '<':
		comperTop2(stos);
		break;
	case '>':
		printFirstChar(stos);
		break;
	case '[': 
		pushHeadASCII(stos);
		break;
	case ']':
		pushAsASCII(stos);
		break;
	case '$':
		pushHead(stos);
		break;
	case '#':
		connectTop2(stos);
		break;
	case '~':
		pushId(stos, instr->id);
		break;
	case '-':
		pushMinus(&((*stos)->list));
		break;
	case '^':
		absolute(&((*stos)->list));
		break;
	case '!':
		neagtion(stos);
		break;
	case '?':
		jumpToInstr(&instr,stos);
		break;
	default:
		push_char(instr->c, &((*stos)->list));
		break;
	}
	if (instr == list->tail) return;
	doAllInstructions(list,instr->next, stos, numbs);
}

int main()
{
	InstrList instrList;
	instrList.head = NULL;
	instrList.tail = NULL;
	List numbsList;
	numbsList.head = NULL;
	numbsList.tail = NULL;
	Node* stos = NULL;
	char c;
	int breakpoint = 0, id = 0;
	while (breakpoint != 2) {
		c = getchar();
		if (c == '\n') breakpoint++;
		else if (breakpoint == 0) {
			push_instruction(&instrList, c, &id);
		}
		else push_numbs(&numbsList, c, 0);
	}
	doAllInstructions(&instrList,instrList.head, &stos, &numbsList);
	return 0;
}
