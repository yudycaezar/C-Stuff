#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Project{
	char projectname[100];
	int projectdifficulty;
	Project* next;
	Project* prev;
}*head = NULL, *tail = NULL, *curr = NULL;

Project* create_node(char* filename, int filesize){
	Project* node = (Project*)malloc(sizeof(Project));
	strcpy(node->projectname, filename);
	node->projectdifficulty = filesize;
	node->next = NULL;
	return node;
}

void push_head(Project* node){
	if (head == NULL){
		head = tail = node;
	}
	else{
		node->next = head;
		head->prev = node;
		head = node;
	}
}

void push_tail(Project* node){
	if (head == NULL){
		head = tail = node;
	}
	else{
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

void push(Project* node){
	if (head == NULL){
		head = tail = node;
	}
	else if (node->projectdifficulty > head->projectdifficulty){
		push_head(node);
	}
	else if (node->projectdifficulty < tail->projectdifficulty){
		push_tail(node);
	}
	else{
		curr = head;
		while (curr)
		{
			if (curr->projectdifficulty >= node->projectdifficulty){
				curr = curr->next;
			}
			else{
				Project* left = curr->prev;
				Project* right = curr;
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

void pop_all(){
	while (head){
		pop_head();
	}
	printf("All data successfully removed!\n");
}

void view(){
	if (head == NULL){
		printf("There is no existing Project!\n");
	}
	else{
		curr = head;
		int index = 1;

		//PRINT HEADER
		printf("%c", 201);
		for (int i = 1; i <= 55; i++){
			if (i == 5)
				printf("%c", 203);
			else if (i==43)
				printf("%c", 203);
			else
				printf("%c", 205);
		}
		printf("%c\n", 187);
		printf("%c %2s %c %-35s %c %10s %c\n", 186, "No", 186, "Project Name", 186, "Difficulty", 186);
		printf("%c", 204);
		for (int i = 1; i <= 55; i++){
			if (i == 5)
				printf("%c", 206);
			else if (i == 43)
				printf("%c", 206);
			else
				printf("%c", 205);
		}
		printf("%c\n", 185);
		//END OF PRINT HEADER

		while (curr){
			printf("%c %2d %c %-35s %c %10d %c\n", 186, index, 186, curr->projectname, 186, curr->projectdifficulty, 186);
			curr = curr->next;
			index++;
		}

		printf("%c", 200);
		for (int i = 1; i <= 55; i++){
			if (i == 5)
				printf("%c", 202);
			else if (i == 43)
				printf("%c", 202);
			else
				printf("%c", 205);
		}
		printf("%c\n", 188);
	}
}

void clrscr(){
	for (int i = 0; i<25; i++){
		printf("\n");
	}
}

void print_application_footer(){
	printf(" _____ _              _                   \n");
	printf("|_   _| |_  __ _ _ _ | |__  _  _ ___ _  _ \n");
	printf("  | | | ' \\/ _` | ' \\| / / | || / _ \\ || |\n");
	printf("  |_| |_||_\\__,_|_||_|_\\_\\  \\_, \\___/\\_,_|\n");
	printf("                            |__/          ");
}

int main(){

	int menu = 0;
	char projectname[100];
	int projectdifficulty;

	push(create_node("Priority Queue Tutorial", 9));
	push(create_node("StarJus Mobile Application", 5));
	push(create_node("Alam Maya Backend", 8));
	push(create_node("Linked List Animation", 3));
	push(create_node("WebGL Tutorial", 4));

	do{
		clrscr();
		printf("Shurima Project Manager\n");
		printf("=========================================================\n");
		printf("1. Register New Project\n");
		printf("2. Assign Programmer to Project\n");
		printf("3. View Project List\n");
		printf("4. Exit\n");
		do{
			printf("Choose: ");
			scanf("%d", &menu);
			fflush(stdin);

			switch (menu){

			case 1:
				clrscr();

				printf("Register New Project\n");
				printf("---------------------------------------------------------\n\n");

				do{
					printf("Input project name [8-35 characters]: ");
					scanf("%[^\n]", &projectname);
					fflush(stdin);
				} while ( strlen(projectname)<8 || strlen(projectname)>35 );

				do{
					printf("Input project difficulty [1-10]: ");
					scanf("%d", &projectdifficulty);
					fflush(stdin);
				} while (projectdifficulty<1 || projectdifficulty>10);

				push(create_node(projectname, projectdifficulty));

				printf("Success registered new project!\n\n");
				printf("Press enter to continue...");
				getchar();
				break;

			case 2:
				clrscr();

				printf("Assign Programmer to Project\n");
				printf("---------------------------------------------------------\n\n");

				printf("Success assign programmer to this project:\n");
				printf("Project Name      : %s\n", head->projectname);
				printf("Project Difficulty: %d\n\n", head->projectdifficulty);
				pop_head();

				printf("Press enter to continue...");
				getchar();
				break;

			case 3:
				clrscr();
				printf("View Project List\n");
				printf("---------------------------------------------------------\n\n");

				view();

				printf("\nPress enter to continue...");
				getchar();
				break;

			}

		} while (menu<1 || menu>4);

	} while (menu != 4);

	clrscr();
	pop_all();
	print_application_footer();	
	getchar();
	return 0;
}