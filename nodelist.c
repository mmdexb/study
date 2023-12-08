#include <stdio.h>
	  #include <stdlib.h>
	struct op {
	int x;
	struct op* next;
}
;
typedef struct op op;
int main() {
	int n;
	int d;
	int sum=0;
	scanf("%d",&n);
	op* head = NULL;
	op* tail = NULL;
	for (int i=0;i<n;i++) {
		op* newnode= (op*)malloc(sizeof(op));
		newnode->next=NULL;
		scanf("%d",&newnode->x);
		if(head==NULL) {
			head=newnode;
			tail=newnode;
		} else {
			tail->next=newnode;
			tail=newnode;
		}
	}
	int m;
	scanf("%d",&m);
	for (int i=0;i<m;i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		sum+=b;
		op* current=head;
		//这是第一项 
		op* prev=NULL;
		for (int j=1;j<a;j++) {
			prev=current;
			current=current->next;
		}
		//移动指针 
		for (int k=0;k<b;k++) {
			op* newnode=(op*)malloc(sizeof(op));
			scanf("%d",&newnode->x);
			newnode->next=NULL;
			//prev->next=newnode;
			//newnode->next=current;
			newnode->next=current->next;
			current->next=newnode;

			prev=current;
			current=current->next;


		
		}
	}
	tail=head;
	while (tail!= NULL) {
		printf("%d", tail->x);
		tail = tail->next;
		if (tail != NULL) {
			printf(" ");
		} else {
			break;
		}
	}
	printf("\n");
	system("pause");
	return 0;
}