#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 1000
typedef struct NODE{
    double x,y;
}NODE;
typedef struct EDGE{
    int a,b;
    double r;
}EDGE;
NODE node[MAX+5];
EDGE edge[MAX+5];
int exist[MAX+5]={0};
int cnt_edge,n;
double dist_n_n(NODE,NODE);//distance between two nodes
double dist_n_e(NODE,EDGE);//distance between node and edge
void solve();
void swap_e_e(int,int);

int main(){
    cnt_edge=0;
    FILE *fp=fopen("node.txt","r");
    fscanf(fp,"%d",&n);
    for(int i = 0; i < n; i++) fscanf(fp,"%d%lf%lf",&i,&node[i].x,&node[i].y);
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(dist_n_n(node[i],node[j])<=1){//make links
                edge[cnt_edge].a=i;
                edge[cnt_edge].b=j;
                edge[cnt_edge].r=dist_n_n(node[i],node[j]);
                exist[cnt_edge]=1;
                cnt_edge++;
            }
        }
    }
    fclose(fp);
    fp=fopen("link.txt","w");
    fprintf(fp,"%d\n",cnt_edge);
    printf("%d\n",cnt_edge);//print before remove the links
    for(int i=0;i<cnt_edge;i++){
        fprintf(fp,"%d %d %d\n",i,edge[i].a,edge[i].b);
        printf("%d %d %d\n",i,edge[i].a,edge[i].b);
    }
    solve(fp);//algorithm of remove links
    fclose(fp);

    return 0;
}
double dist_n_n(NODE a,NODE b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
double dist_n_e(NODE v,EDGE e){
    double midx=(node[e.a].x+node[e.b].x)/2;
    double midy=(node[e.a].y+node[e.b].y)/2;
    return sqrt((v.x - midx)*(v.x - midx) + (v.y - midy)*(v.y - midy));
}
void solve(FILE *fp){
    int ans_edge=cnt_edge;
    for(int i=0;i<cnt_edge;i++){
        for(int j=0;j<n;j++){
            if(j==edge[i].a || j==edge[i].b) continue;
            if(!exist[i]) continue;
            if(dist_n_e(node[j],edge[i])*2 < edge[i].r){
                exist[i]=0;
                ans_edge--;
            }
        }
    }
    fprintf(fp,"%d\n",ans_edge);
    printf("%d\n",ans_edge);//print after remove the links
    for(int i=0;i<cnt_edge;i++){
        if(exist[i]){
            fprintf(fp,"%d %d %d\n",i,edge[i].a,edge[i].b);
            printf("%d %d %d\n",i,edge[i].a,edge[i].b);
        }
    }
}
void swap_e_e(int i,int j){
    int t=edge[i].a;
    edge[i].a=edge[j].a;
    edge[j].a=t;
    t=edge[i].b;
    edge[i].b=edge[j].b;
    edge[j].b=t;
}
