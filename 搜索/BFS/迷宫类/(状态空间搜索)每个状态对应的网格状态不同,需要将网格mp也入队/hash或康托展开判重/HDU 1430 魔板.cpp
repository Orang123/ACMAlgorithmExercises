#include<cstdio>
#include<cstring>
#include<algorithm>
#define M 40330
#define HS 1000003
using namespace std;

int head[HS],cnt,ed;
struct State{
    int val,pre;
    char str[10],opt;
}Q[M];

struct HT{
    int val,next;
}edge[M];

int Hash(char *a){
    int s=0;
    for(int i=0;i<8;i++)
        s=s*10+a[i]-'0';
    return s;
}

int tryInsert(int val){
    int hval=val%HS;
    for(int i=head[hval];i!=-1;i=edge[i].next){
        if(edge[i].val == val)
            return 0;
    }
    edge[cnt]=(HT){val,head[hval]};
    head[hval]=cnt++;
    return 1;
}

int bfs(State st){
    int head=0,tail=0;
    Q[tail++]=st;
    State tp,next;
    int val;
    char x;
    while(head<tail){
        tp=Q[head++];
        if(tp.val == ed)
            break;
        //A操作
        memcpy(next.str,tp.str,sizeof(tp.str));
        for(int i=0;i<4;i++)
            swap(next.str[i],next.str[7-i]);
        val=Hash(next.str);
        if(tryInsert(val)){
            next.val=val;
            next.pre=head-1;
            next.opt='A';
            Q[tail++]=next;
        }
        //B操作
        memcpy(next.str,tp.str,sizeof(tp.str));
        x=next.str[3];
        for(int i=3;i>=1;i--)
            next.str[i]=next.str[i-1];
        next.str[0]=x;
        x=next.str[4];
        for(int i=4;i<=7;i++)
            next.str[i]=next.str[i+1];
        next.str[7]=x;
        val=Hash(next.str);
        if(tryInsert(val)){
            next.val=val;
            next.pre=head-1;
            next.opt='B';
            Q[tail++]=next;
        }
        //C操作
        memcpy(next.str,tp.str,sizeof(tp.str));
        next.str[1]=tp.str[6];
        next.str[2]=tp.str[1];
        next.str[5]=tp.str[2];
        next.str[6]=tp.str[5];
        val=Hash(next.str);
        if(tryInsert(val)){
            next.val=val;
            next.pre=head-1;
            next.opt='C';
            Q[tail++]=next;
        }
    }
    return head-1;
}

void print(int i){
    if(!i)
        return;
    print(Q[i].pre);
    printf("%c",Q[i].opt);
}

int main(){
    State st;
    while(scanf("%s",st.str)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&ed);
        st.val=Hash(st.str);
        st.pre=-1;
        print(bfs(st));
        printf("\n");
    }
    return 0;
}

/*
//TLE 康托展开判重
#include<cstdio>
#include<cstring>
#include<algorithm>
#define M 40330
using namespace std;

int ed,vis[M],factor[8]={1,1,2,6,24,120,720,5040};
struct State{
    int order,pre;
    char str[10],opt;
}Q[M];

int cantor(char *a){
    int sum,order=0;
    for(int i=0;i<8;i++){
        sum=0;
        for(int j=i+1;j<8;j++){
            if(a[j]<a[i])
                sum++;
        }
        order+=sum*factor[8-i-1];
    }
    return order;
}

int bfs(State st){
    int head=0,tail=0;
    vis[st.order]=1;
    Q[tail++]=st;
    State tp,next;
    int order;
    char x;
    while(head<tail){
        tp=Q[head++];
        if(tp.order == ed)
            break;
        memcpy(next.str,tp.str,sizeof(tp.str));
        for(int i=0;i<4;i++)
            swap(next.str[i],next.str[7-i]);
        order=cantor(next.str);
        if(!vis[order]){
            vis[order]=1;
            next.order=order;
            next.pre=head-1;
            next.opt='A';
            Q[tail++]=next;
        }

        memcpy(next.str,tp.str,sizeof(tp.str));
        x=next.str[3];
        for(int i=3;i>=1;i--)
            next.str[i]=next.str[i-1];
        next.str[0]=x;
        x=next.str[4];
        for(int i=4;i<=7;i++)
            next.str[i]=next.str[i+1];
        next.str[7]=x;
        order=cantor(next.str);
        if(!vis[order]){
            vis[order]=1;
            next.order=order;
            next.pre=head-1;
            next.opt='B';
            Q[tail++]=next;
        }

        memcpy(next.str,tp.str,sizeof(tp.str));
        next.str[1]=tp.str[6];
        next.str[2]=tp.str[1];
        next.str[5]=tp.str[2];
        next.str[6]=tp.str[5];
        order=cantor(next.str);
        if(!vis[order]){
            vis[order]=1;
            next.order=order;
            next.pre=head-1;
            next.opt='C';
            Q[tail++]=next;
        }
    }
    return head-1;
}

void print(int i){
    if(!i)
        return;
    print(Q[i].pre);
    printf("%c",Q[i].opt);
}

int main(){
    State st;
    char x[10];
    while(scanf("%s",st.str)!=EOF){
        scanf("%s",x);
        memset(vis,0,sizeof(vis));
        st.order=cantor(st.str);
        ed=cantor(x);
        print(bfs(st));
        printf("\n");
    }
    return 0;
}
*/
