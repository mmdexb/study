#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct node{
    int id;
    int score;
    char name[20];
    struct node* next;
};

typedef struct node STU;

STU* creat(){
    int id;
    int score;
    char name[20];

    STU *h;
    STU *s;
    STU *r;

    h=(STU*)malloc(sizeof(STU));
    r=h;

    printf("plz enter id\n");
    scanf("%d",&id);

    while (id!=0)
    {
        printf("name\n");
        scanf("%s",name);
        printf("score:\n");
        scanf("%d",&score);
        s=(STU*)malloc(sizeof(STU));
        s->id=id;
        s->score=score;
        strcpy(s->name,name);
        r->next=s;
        r=s;
        printf("plz entry id\n");
        scanf("%d",&id);
    }

    r->next=NULL;
    return h;
    

}

void display(STU *h){
    STU* temp;
    temp=h->next;

    if (temp==NULL)
    {
        printf("null");

    }else{
        while (temp!=NULL)
        {
        printf("inf\n");
        printf("%d" "%d" "%s\n",temp->id,temp->score,temp->name);
        temp= temp->next;
        }
        

    }
    

}

int main(){

    STU* head;
    head=creat();
    display(head);

    system("pause");
}