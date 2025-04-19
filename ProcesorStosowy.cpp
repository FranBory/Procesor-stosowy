#include <stdio.h>
#include <stdlib.h>

using namespace std;


typedef struct ListNode {
	char c;
	struct ListNode* prev;
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


void push_empty_list(Node** top) {       
	Node* node = (Node*)malloc(sizeof(Node));
	List* list = (List*)malloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
	node->list = list;
	if (!isEmptyStack(*top)) node->next = *top;
	else node->next = NULL;
	*top = node;
}

void push_node(Node* node, Node** top) {     
	if (node == NULL) return;
	node->next = *top;
	*top = node;
}
//',','1'50?
void push_char(char c, List** list) {
	ListNode* listNode = (ListNode*)malloc(sizeof(ListNode));
	listNode->c = c;
	listNode->prev = NULL;
	if (!isEmptyList(*list)) {
		listNode->next = (*list)->head;
		(*list)->head->prev = listNode;
		(*list)->head = listNode;
	}
	else {
		(*list)->head = listNode;
		(*list)->tail = listNode;
		listNode->next = NULL;
	}
}
List* pop_list(Node** top) {
	if (!isEmptyStack(*top)) {
		Node* temp = *top;
		*top = (*top)->next;
		List* c = temp->list;
		free(temp);
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
void copy_list(List** copied, List* to_copy, ListNode* node) {
	if (node == NULL) return;
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->c = node->c;
	new_node->next = NULL;
	new_node->prev = NULL;
	if ((*copied)->head == NULL) {
		(*copied)->head = new_node;
		(*copied)->tail = new_node;
	}
	else {
		new_node->prev = (*copied)->tail;
		(*copied)->tail->next = new_node;
		(*copied)->tail = new_node;
	}
	copy_list(copied, to_copy, node->next);
}
void copy_top(Node** top) {
	if (!isEmptyStack(*top)) {
		Node* node = (Node*)malloc(sizeof(Node));
		List* copied_list = (List*)malloc(sizeof(List));
		copied_list->head = NULL;
		copied_list->tail = NULL;
		copy_list(&copied_list, (*top)->list, (*top)->list->head);
		node->list = copied_list;
		push_node(node, top);
	}
	else printf("stack empty\n");
}
void swap_top2(Node** top) {
	List* old_top = (*top)->list;
	(*top)->list = (*top)->next->list;
	(*top)->next->list = old_top;
}
long long list_to_int(List* list, ListNode* node, int level) {
	long long result = 0;
	if (node->c != '-') result = (node->c - '0') * level;
	if (list->tail->c == '-') result *= -1;
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
	free(popped);
	Node* toCopy = get_by_index((*top), indx);
	Node* node = (Node*)malloc(sizeof(Node));
	List* copied_list = (List*)malloc(sizeof(List));
	copied_list->head = NULL;
	copied_list->tail = NULL;
	copy_list(&copied_list, toCopy->list, toCopy->list->head);
	node->list = copied_list;
	push_node(node, top);
}

void printList(ListNode* node, List* list) {
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

void printFirstChar(Node** node) {
	Node* popped = pop_node(node);
	printf("%c", popped->list->head->c);
	free(popped);
}
void deleteTail(List* list) {
	ListNode* old = list->tail;
	list->tail = old->prev;
	if (list->tail) list->tail->next = NULL;
	else list->head = NULL;
	free(old);
}
void absolute(List** list) {
	if (isEmptyList(*list)) return;
	else if ((*list)->tail->c == '-') {
		if ((*list)->head == (*list)->tail) {
			(*list)->head = NULL;
			(*list)->tail = NULL;
		}
		else deleteTail(*list);
	}
	else return;
}
void pushCharToTail(char c, List** list) {
	ListNode* listNode = (ListNode*)malloc(sizeof(ListNode));
	listNode->c = c;
	listNode->next = NULL;
	if (!isEmptyList(*list)) {
		listNode->prev = (*list)->tail;
		(*list)->tail->next = listNode;
		(*list)->tail = listNode;
	}
	else {
		(*list)->head = listNode;
		(*list)->tail = listNode;
		listNode->prev = NULL;
	}
}
void pushMinus(List** list) {
	if (!isEmptyList(*list)) {
		if ((*list)->tail->c != '-') {
			pushCharToTail('-', list);
		}
		else absolute(list);
	}
	else push_char('-', list);
}
void clearListNode(ListNode* node) {
	if (node == NULL) return;
	clearListNode(node->next);
	free(node);
}
void clearList(List** list) {
	if (isEmptyList(*list)) return;
	clearListNode((*list)->head);
	(*list)->head = NULL;
	(*list)->tail = NULL;

}
void pushAsASCII(Node** stos) {
	long long i = list_to_int((*stos)->list, (*stos)->list->head, 1);
	clearList(&((*stos)->list));
	char c = (char)i;
	push_char(c, &((*stos)->list));
}
void pushInt(Node** stos, int n) {
	if (n >= 10) pushInt(stos, n / 10);
	char c = (char)('0' + (n % 10));
	push_char(c,&((*stos)->list));
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
	free(popped);
}

bool isPositive(List* node) {
	if (node->tail->c == '-') return false;
	else return true;
}

void listIsZeros(ListNode* node, bool* isZero) {
	if (node == NULL || node->c == '-') return;
	if (node->c != '0') {
		*isZero = false;
		return;
	}
	listIsZeros(node->next, isZero);
}

void trim_tail_zeros(List* list)
{
	if (list == NULL || list->tail == NULL) return;
	if (list->tail == list->head) return;
	if (list->tail->c != '0') return;

	ListNode* tmp = list->tail;
	list->tail = tmp->prev;
	list->tail->next = NULL;
	free(tmp);
	trim_tail_zeros(list);
}

ListNode* skip_leading_zeros(ListNode* p){
	if (p == NULL) return NULL;
	if (p->c == '0') return skip_leading_zeros(p->prev);
	else return p;
}
bool equal_values(ListNode* a_msb,ListNode* b_msb){
	if (a_msb == NULL && b_msb == NULL) return true;         
	if (a_msb == NULL || b_msb == NULL) return false;         
	if (a_msb->c != b_msb->c)          return false;           
	return equal_values(a_msb->prev, b_msb->prev);
}
bool isEqual(Node* a, Node* b) {
	bool isZeroA = true;
	bool isZeroB = true;
	listIsZeros(b->list->head, &isZeroB);
	listIsZeros(a->list->head, &isZeroA);
	if (isZeroA && isZeroB) return true;
	else if ((isZeroA && !isZeroB) || (!isZeroA && isZeroB)) return false;
	else if (isEmptyList(a->list) && isEmptyList(b->list)) return true;
	else if (isEmptyList(a->list) && !isEmptyList(b->list)) return false;
	else if (!isEmptyList(a->list) && isEmptyList(b->list)) return false;
	else {
		ListNode* a_msb = NULL;
		ListNode* b_msb = NULL;
		if (a->list->tail->c == '-') {
			a_msb = skip_leading_zeros(a->list->tail->prev);
			a_msb->next = (ListNode*)malloc(sizeof(ListNode));
			a_msb->next->c = '-';
			a_msb->next->prev = a_msb;
			a_msb->next->next = NULL;
			a_msb = a_msb->next;
		}
		else a_msb = skip_leading_zeros(a->list->tail);
		if(b->list->tail->c == '-') {
			b_msb = skip_leading_zeros(b->list->tail->prev);
			b_msb->next = (ListNode*)malloc(sizeof(ListNode));
			b_msb->next->c = '-';
			b_msb->next->prev = b_msb;
			b_msb->next->next = NULL;
			b_msb = b_msb->next;
		}
		else b_msb = skip_leading_zeros(b->list->tail);
		if (equal_values(a_msb, b_msb)) return true;
		else return false;
		free(a_msb);
		free(b_msb);
	}
}

bool compare2positive(ListNode* a, ListNode* b,bool flagR,bool flagIF) {
	if (flagIF && a->c > b->c) {
		flagR = true;
		flagIF = false;
	}
	else if (flagIF && a->c < b->c) {
		flagR = false;
		flagIF = false;
	}
	if (a->prev == NULL && b->prev == NULL) return flagR;
	else if (a->prev != NULL && b->prev == NULL) return true;
	else if (a->prev == NULL && b->prev != NULL) return false;
	else return compare2positive(a->prev, b->prev,flagR,flagIF);
	
}
bool isAgreater(Node* a, Node* b) {
	if (isEqual(a,b)) return false;
	if (isPositive(a->list) && !isPositive(b->list)) return true;
	else if (!isPositive(a->list) && isPositive(b->list)) return false;
	else if (isPositive(a->list) && isPositive(b->list)) {
		trim_tail_zeros(a->list);
		trim_tail_zeros(b->list);
		return compare2positive(a->list->tail, b->list->tail,false,true);
	}
	else if (!isPositive(a->list) && !isPositive(b->list))
	{
		absolute(&(a->list));
		absolute(&(b->list));
		trim_tail_zeros(a->list);
		trim_tail_zeros(b->list);
		return !compare2positive(a->list->tail, b->list->tail,false,true);
	}
	else return false;
}
void comperTop2(Node** stos) {
	Node* a = pop_node(stos);
	Node* b = pop_node(stos);
	push_empty_list(stos);
	if (isAgreater(a, b)) push_char('1', &((*stos)->list));
	else push_char('0', &((*stos)->list));
	free(a);
	free(b);
}
void isEqualTop2(Node** stos) {
	Node* a = pop_node(stos);
	Node* b = pop_node(stos);
	push_empty_list(stos);
	if (isEqual(a,b)) push_char('1', &((*stos)->list));
	else push_char('0', &((*stos)->list));
	free(a);
	free(b);
}
void pushId(Node** stos, int id) {
	push_empty_list(stos);
	pushInt(stos, id);
}
void neagtion(Node** stos) {
	if (isEmptyList((*stos)->list)) push_char('1', &((*stos)->list));
	else if ((*stos)->list->head == (*stos)->list->tail && (*stos)->list->head->c == '0') (*stos)->list->head->c = '1';
	else {
		Node* poped = pop_node(stos);
		free(poped);
		push_empty_list(stos);
		push_char('0', &((*stos)->list));
	}
}

void jumpToInstr(int* id, Node** stos) {
	Node* t = pop_node(stos);
	Node* w = pop_node(stos);
	bool s = true;
	listIsZeros(w->list->head, &s);
	if (!s && !isEmptyList(w->list)) {
		*id = list_to_int(t->list, t->list->head, 1);
		*id = *id - 1;
	}
	free(t);
	free(w);
}

void addPositive(ListNode* a, ListNode* b, List** result, int carry, bool aLast, bool bLast) {
	int a_value = a->c - '0';
	int b_value = b->c - '0';
	if (aLast) a_value = 0;
	if (bLast) b_value = 0;
	int sum = a_value + b_value + carry;
	if (sum >= 10) carry = 1;
	else carry = 0;
	char c = sum % 10 + '0';
	pushCharToTail(c, result);
	if (a->next != NULL && b->next != NULL) {
		addPositive(a->next, b->next, result, carry,false,false);
	}
	else if (a->next != NULL && b->next == NULL) {
		addPositive(a->next, b, result, carry, false, true);
	}
	else if (a->next == NULL && b->next != NULL) {
		addPositive(a, b->next, result, carry, true, false);
	}
	else if (carry == 1) pushCharToTail('1', result);
}
void subtract(ListNode* a, ListNode* b, List** result, int carry, bool bLast) {
	int a_value = a->c - '0';
	int b_value = b->c - '0';
	if (bLast) b_value = 0;
	int sub = a_value - b_value -carry;
	if (sub < 0) {
		sub += 10;
		carry = 1;
	}
	else carry = 0;
	char c = sub + '0';
	pushCharToTail(c, result);
	if (a->next != NULL && b->next != NULL) {
		subtract(a->next, b->next, result, carry, false);
	}
	else if (a->next != NULL && b->next == NULL) {
		subtract(a->next, b, result, carry, true);
	}
	else if (a->next == NULL && b->next != NULL) {
		subtract(a, b->next, result, carry, false);
	}
	else if (carry == 1) {
		pushCharToTail('1', result);
	}
}
void addTop2(Node** stos) {
	Node* a = pop_node(stos);
	Node* b = pop_node(stos);
	push_empty_list(stos);
	if (isPositive(a->list) && isPositive(b->list)) {
		addPositive(a->list->head, b->list->head, &((*stos)->list), 0, false, false);
	}
	else if (!isPositive(a->list) && !isPositive(b->list)) {
		absolute(&(a->list));
		absolute(&(b->list));
		if (isEqual(a, b)) push_char('0', &((*stos)->list));
		addPositive(b->list->head, a->list->head, &((*stos)->list), 0, false, false);
		pushMinus(&((*stos)->list));
	}
	else if (!isPositive(a->list) && isPositive(b->list)) {
		absolute(&(a->list));
		if (isEqual(a, b)) push_char('0', &((*stos)->list));
		else if (isAgreater(a,b)) {
			subtract(a->list->head, b->list->head, &((*stos)->list), 0, false);
			trim_tail_zeros((*stos)->list);
			bool s = true;	
			listIsZeros((*stos)->list->head, &s);
			if(!s) pushMinus(&((*stos)->list));
		}
		else {
			subtract(b->list->head, a->list->head, &((*stos)->list), 0, false);
			trim_tail_zeros((*stos)->list);
		}
	}
	else if (isPositive(a->list) && !isPositive(b->list)) {
		absolute(&(b->list));
		if (isEqual(a, b)) push_char('0', &((*stos)->list));
		else if (isAgreater(a, b)) { 
			subtract(a->list->head, b->list->head, &((*stos)->list), 0, false);
			trim_tail_zeros((*stos)->list);
		}
		else {
			subtract(b->list->head, a->list->head, &((*stos)->list), 0, false);
			trim_tail_zeros((*stos)->list);
			bool s = true;
			listIsZeros((*stos)->list->head, &s);
			if (!s) pushMinus(&((*stos)->list));
		}
	}
	else push_char('0', &((*stos)->list));
	free(a);
	free(b);
}

void freeStack(Node** top) {
	if (isEmptyStack(*top)) return;
	else {
		freeStack(&((*top)->next));
		clearList(&((*top)->list));
		free(*top);
	}
}

int main() {
	char instr[20001];
	Node* stos = NULL;
	int breakpoint = 0, id = 0;
	fgets(instr, 20001, stdin);

	while (breakpoint != 1) {
		char c = instr[id];
		switch (instr[id]) {
		case '\n':
			breakpoint++;
			break;
		case '\'':
			push_empty_list(&stos);
			break;
		case ',':
			pop_list(&stos);
			break;
		case '.':
			char temp;
			scanf_s("%c", &temp, 1);
			push_char(temp, &(stos->list));
			break;
		case ':':
			copy_top(&stos);
			break;
		case ';':
			swap_top2(&stos);
			break;
		case '@':
			copyByIndex(&stos);
			break;
		case '&':
			printStack(stos, 0);
			break;
		case '=':
			isEqualTop2(&stos);
			break;
		case '<':
			comperTop2(&stos);
			break;
		case '>':
			printFirstChar(&stos);
			break;
		case '[':
			pushHeadASCII(&stos);
			break;
		case ']':
			pushAsASCII(&stos);
			break;
		case '$':
			pushHead(&stos);
			break;
		case '#':
			connectTop2(&stos);
			break;
		case '~':
			pushId(&stos, id);
			break;
		case '-':
			pushMinus(&(stos->list));
			break;
		case '^':
			absolute(&(stos->list));
			break;
		case '!':
			neagtion(&stos);
			break;
		case '?':
			jumpToInstr(&id, &stos);
			break;
		case '+':
			addTop2(&stos);
			break;
		default:
			push_char(c, &(stos->list));
			break;
		}
		id++;
	}

	freeStack(&stos);

	return 0;
}
