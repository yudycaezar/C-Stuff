#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Document{
	char documentname[100];
	int documentsize;
	Document* next;
	Document* prev;
}*head=NULL,*tail=NULL, *curr=NULL;

Document* create_node(char* filename, int filesize){
	Document* node = (Document*)malloc(sizeof(Document));
	strcpy(node->documentname, filename);
	node->documentsize = filesize;
	node->next = NULL;
	return node;
}

void push_head(Document* node){
	if (head == NULL){
		head = tail = node;
	}
	else{
		node->next = head;
		head->prev = node;
		head = node;
	}
}

void push_tail(Document* node){
	if (head == NULL){
		head = tail = node;
	}
	else{
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

void push(Document* node){
	if (head == NULL){
		head = tail = node;
	}
	else if (node->documentsize > head->documentsize){
		push_head(node);
	}
	else if (node->documentsize <= tail->documentsize){
		push_tail(node);
	}
	else{
		curr = head;
		while (curr)
		{
			if (curr->documentsize >= node->documentsize){
				curr = curr->next;
			}
			else{
				Document* left = curr->prev;
				Document* right = curr;
				left->next = node;
				node->prev = left;
				right->prev = node;
				node->next = right;
				break;
			}
		}
	}
}

void pop_head(){
	if (head == NULL){
		printf("Data is empty!\n");
	}
	else if (head == tail){
		head = tail = NULL;
	}
	else{
		head = head->next;
		free(head->prev);
		head->prev = NULL;
	}
}

void pop_tail(){
	if (head == NULL){
		printf("Data is empty!\n");
	}
	else if (head == tail){
		head = tail = NULL;
	}
	else{
		tail = tail->prev;
		free(tail->next);
		tail->next = NULL;
	}
}

void pop(char* keyword){
	if (head == NULL){
		printf("Data is empty!\n");
	}
	else if( strcmp(head->documentname, keyword) == 0 ){
		pop_head();
	}
	else if( strcmp(tail->documentname, keyword) == 0 ){
		pop_tail();
	}
	else{
		curr = head;
		while(curr){
			if( strcmp(curr->documentname, keyword) == 0 ){
				Document* left = curr->prev;
				Document* right = curr->next;
				left->next = right;
				right->prev = left;
				printf("Document: %s (%d kB) successfully removed!\n\n", curr->documentname, curr->documentsize);
				free(curr);
				return;
			}
			else{
				curr = curr->next;
			}
		}
		printf("There is no match document with name: %s\n", keyword);
	}
}

void pop_all(){
	while (head){
		pop_head();
	}
	printf("All data successfully removed!");
}

void view(){
	if( head==NULL ){
		printf("There is no data!!\n");
	}
	else{
		curr = head;
		int index = 1;
		while(curr){			
			printf("%2d. %-35s %4d kB\n",index, curr->documentname, curr->documentsize);
			curr = curr->next;
			index++;
		}
	}
}

void clrscr(){
	for(int i=0 ; i<25 ; i++){
		printf("\n");
	}
}

int is_document(char* input){
	if( strlen(input)<=4 ){
		return -1;
	}
	else if( input[strlen(input)-1] != 'c'
				|| input[strlen(input)-2] != 'o'
				|| input[strlen(input)-3] != 'd'
				|| input[strlen(input)-4] != '.' ){
		return -1;
	}
	return 0;
}

int main(){
	
	int menu = 0;
	char documentname[100];
	int documentsize;

	push(create_node("Array.doc", 230));
	push(create_node("Linked List.doc", 580));
	push(create_node("Queue.doc", 345));
	push(create_node("Stack.doc", 580));
	push(create_node("Tree.doc", 230));

	do{
		clrscr();
		printf("Zzerot File Manager\n");
		printf("=====================================================\n");
		printf("1. Register New Document\n");
		printf("2. Remove Document\n");
		printf("3. View Existing File\n");
		printf("4. Exit\n");
		do{
			printf("Choose: ");
			scanf("%d", &menu);
			fflush(stdin);

			switch(menu){
				
				case 1:
					clrscr();

					printf("Register New Document\n");
					printf("-----------------------------------------------------\n\n");
					
					do{
						printf("Input document name [*.doc]: ");
						scanf("%[^\n]", &documentname);
						fflush(stdin);
					}while( is_document(documentname) );

					do{
						printf("Input document size [1-9999 kB]: ");
						scanf("%d", &documentsize);
						fflush(stdin);
					}while( documentsize<1 || documentsize>9999 );

					//push_head(create_node(documentname, documentsize));
					push(create_node(documentname, documentsize));

					printf("Success registered new document!\n\n");
					printf("Press enter to continue...");
					getchar();
					break;

				/*
				case 2:
					clrscr();

					printf("Remove Last Registered Document\n");
					printf("-----------------------------------------------------\n\n");

					//printf("Document \"%s\" (%d kB) successfully removed!\n", head->documentname, head->documentsize);
					//pop_head();

					printf("Document \"%s\" (%d kB) successfully removed!\n\n", tail->documentname, tail->documentsize);
					pop_tail();

					printf("Press enter to continue...");
					getchar();
					break;
				*/

				case 2:
					clrscr();

					printf("Input document name: ");
					scanf("%[^\n]", &documentname);
					fflush(stdin);

					pop(documentname);

					printf("Press enter to continue...");
					getchar();
					break;

				case 3:
					clrscr();
					printf("View Existing File\n");
					printf("-----------------------------------------------------\n\n");

					view();

					printf("\nPress enter to continue...");
					getchar();
					break;

			}

		}while(menu<1 || menu>4);

	}while(menu != 4);

	clrscr();
	pop_all();
	getchar();
	return 0;
}