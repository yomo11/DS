#include <bits/stdc++.h>
#include <tr1/functional>
#include <tuple>
using namespace std;
int **Map,*a,*b,r,c,p;
string str;
void init(){
    Map = (int**)malloc(r * sizeof(int*));
    for(int i=0;i<r;i++)
        Map[i] = (int*)malloc(sizeof(int) * c);
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            Map[i][j] = 0;
    a = (int*)malloc(sizeof(int) * r);
    b = (int*)malloc(sizeof(int) * r);

    bool tmp[p+1];
    for(int i=1;i<p;i++) tmp[i] = 1;

    srand(time(NULL));
    for(int i=0;i<r;i++){
        int t = (rand() % (p-1-1+1))+ 1;
        while(!tmp[t] || t==0)  t = (rand() % (p-1-1+1))+ 1;
        tmp[t] = 0;
        a[i] = t;
        b[r-1-i] = t;
    }
}//end init

int myhash(int cnt){
    tr1::hash<string> str_hash;
    long long key = str_hash(str);
    return (a[cnt] * key + b[cnt]) %p %c;
}

void Insert(){
    priority_queue<tuple<int,int,int> ,vector<tuple<int,int,int> >, greater<tuple<int,int,int> > > pq;
    while(!pq.empty()) pq.pop();

    int tmp,h,i;
    for(i=0;i<r;i++){
       h = myhash(i);
       tmp = Map[i][h];
       pq.push(std::make_tuple(tmp,i,h));
    }
    tmp = get<0>(pq.top());
    i = get<1>(pq.top());
    h = get<2>(pq.top());
    Map[i][h] ++;
    pq.pop();

    while(!pq.empty() && tmp==get<0>(pq.top()) ){
        i = get<1>(pq.top());
        h = get<2>(pq.top());
        Map[i][h] ++;
        pq.pop();
    }
}//end Insert

int query(){
    int m = 0x7f7f7f7f;
    for(int i=0;i<r;i++){
       int h = myhash(i);
       if(m>Map[i][h]) m = Map[i][h];
    }
    return m;
}


int main(){
    ifstream file("input.txt",ifstream::in);
    string tmp;
    //cin>>r>>c>>p;
    file>>tmp;
    r = stoi(tmp);
    file>>tmp;
    c = stoi(tmp);
    file>>tmp;
    p = stoi(tmp);

    init();
    while(file>>str){
        for(int i=0;i<str.size();i++){
            if(str[i]>=65 && str[i]<=90)
                str[i] = str[i]+ 'a' - 'A';
            else if(str[i]>=97 && str[i]<=122)
                continue;
            else
                str.erase(i);
        }
        Insert();
    }//end while
    while(cin>>str){
        for(int i=0;i<str.size();i++){
            if(str[i]>=65 && str[i]<=90)
                str[i] = str[i]+ 'a' - 'A';
            else if(str[i]>=97 && str[i]<=122)
                continue;
            else
                str.erase(i);
        }
        cout << query() << "\n";
    }//end while
    return 0;
}//end main
