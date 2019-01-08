#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
//every character in S
typedef struct{
    char w;
    double n;
}chara;

typedef struct stack *Pointer;
typedef struct stack{
    chara data;
    Pointer link;
}stack;
Pointer top[2];
//top[0] -> char
//top[1] -> num

void push(int,chara);
void pop(int);
double eval(char);
void print(FILE);

int main(){
    FILE *fp1 = fopen("infix.txt","r");
    FILE *fp2 = fopen("postfix.txt","w");
    int i,j;
    char s[1000];
    chara t;
    top[0]=NULL;//char
    top[1]=NULL;//num
    while(fscanf(fp1,"%s",s)!=EOF){
        double a,b;
        int len=strlen(s),type=1,np=1,total_num=0,right=0;
        //type->char1 or num2
        //np-> + -
        //right-> ')'.exist
        for(i = 0;i < len;i++){
            if(s[i]=='('){
                t.w = '(';
                t.n = 0;
                push(0,t);
                type = 1;
            }
            else if(type==1 && s[i]=='-') np *= -1;
            else if(type==1 && s[i]=='+') continue;
            else if(s[i]<='9' && s[i]>='0'){
                total_num = 10*total_num + (s[i] - '0');
                type = 2;
            }
            else if(type==2 && (s[i] > '9' || s[i] < '0')){
                total_num *= np;
                if(!right){
                    fprintf(fp2,"%d ",total_num);
                    t.n = total_num;
                    t.w = '.';
                    push(1,t);
                }
                //initial
                np = 1;
                right = 0;
                total_num = 0;
                if(s[i]==')'){
                    while(1){
                        if(top[0]->data.w=='('){
                            pop(0);
                            break;
                        }
                        print(fp2);
                    }
                    right = 1;
                }
                else if(top[0]!=NULL){//priority of char
                    while((top[0]!=NULL) && (s[i]=='+' || s[i]=='-') && (top[0]->data.w=='*'
                            || top[0]->data.w=='/' || top[0]->data.w=='+' || top[0]->data.w=='-')){
                        print(fp2);
                    }
                    while((top[0]!=NULL) && (s[i]=='*' || s[i]=='/') && (top[0]->data.w=='*' ||
                                                                         top[0]->data.w=='/')){
                        print(fp2);
                    }
                    t.w = s[i];
                    push(0,t);
                    type = 1;
                }
                else{
                    t.w = s[i];
                    push(0,t);
                    type = 1;
                }
            }
        }
        total_num *= np;
        fprintf(fp2,"%d ",total_num);
        t.w = '.';
        t.n = total_num;
        push(1,t);
        while(top[0]!=NULL) print(fp2);
        fprintf(fp2,"%.2lf\n",top[1]->data.n);
        while(top[0]!=NULL) pop(0);
        while(top[1]!=NULL) pop(1);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
void push(int n,chara tmp){
    Pointer t = malloc(sizeof(*t));
    t->data = tmp;
    t->link = top[n];
    top[n] = t;
}
void pop(int n){
    Pointer t = top[n];
    if(t==NULL) return;
    top[n] = t->link;
    free(t);
    return;
}
double eval(char c){
    double b = top[1]->data.n;
    pop(1);
    double a=top[1]->data.n;
    pop(1);
    if(c=='+') return a+b;
    else if(c=='-') return a-b;
    else if(c=='*') return a*b;
    else return a/b;
}
void print(FILE *fp2){
    chara t;
    fprintf(fp2,"%c ",top[0]->data.w);
    t.n = eval(top[0]->data.w);
    t.w = '.';
    push(1,t);
    pop(0);
}
