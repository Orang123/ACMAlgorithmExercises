/*
����:KMP����,ֻ���������ִ�.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1711
˼·:kmp�㷨.
*/
//ac 826ms δ�Ż���next���� �±��0��ʼ
#include<cstdio>
int n,m,b[10010],a[1000010],next[10010];
void getNext(){
    int i=0,j=-1;
    next[0]=-1;
    while(i<m-1){
        if(j==-1||b[i]==b[j]){
            i++;
            j++;
            next[i]=j;
        }
        else{
            j=next[j];
        }
    }
}

int kmp(){
    int i=0,j=0;
    while(i<n&&j<m){
        if(j==-1||a[i]==b[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    if(j==m)
        return i-m+1;
    else
        return -1;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)
            scanf("%d",a+i);
        for(int i=0;i<m;i++)
            scanf("%d",b+i);
        getNext();
        printf("%d\n",kmp());
    }
    return 0;
}

/*
//ac 826ms kmp�±��1��ʼ
#include<cstdio>
int n,m,b[10010],a[1000010],next[10010];
void getNext(){
    int i=1,j=0;
    next[1]=0;
    while(i<m){
        if(!j || b[i]==b[j]){
            i++;
            j++;
            next[i]=j;
        }
        else{
            j=next[j];
        }
    }
}

int kmp(){
    int i=1,j=1;
    while(i<=n&&j<=m){
        if(!j ||a[i]==b[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    if(j==m+1)
        return i-j+1;
    else
        return -1;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",a+i);
        for(int i=1;i<=m;i++)
            scanf("%d",b+i);
        getNext();
        printf("%d\n",kmp());
    }
    return 0;
}
*/

/*
//ac 858ms �Ż���next����
#include<cstdio>
int n,m,b[10010],a[1000010],next[10010];
void getNext(){
    int i=0,j=-1;
    next[0]=-1;
    while(i<m){
        if(j==-1||b[i]==b[j]){
            i++;
            j++;
            if(b[i] != b[j])
                next[i]=j;
            else
                next[i]=next[j];
        }
        else{
            j=next[j];
        }
    }
}

int kmp(){
    int i=0,j=0;
    while(i<n&&j<m){
        if(j==-1||a[i]==b[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    if(j==m)
        return i-m+1;
    else
        return -1;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)
            scanf("%d",a+i);
        for(int i=0;i<m;i++)
            scanf("%d",b+i);
        getNext();
        printf("%d\n",kmp());
    }
    return 0;
}
*/

/*
//TLE ��ͨ�ı���ƥ���㷨
//ʱ�临�Ӷ�O(n*m)=10^6*10^4=10^10
#include<cstdio>
int n,m,b[10010],a[1000010];

int match(){
    int i=0,j=0;
    while(i<n && j<m){
        if(a[i] == b[j]){
            i++;
            j++;
        }
        else{
            i=i-j+1;
            j=0;
        }
    }
    if(j == m)
        return i-j+1;
    else
        return -1;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)
            scanf("%d",a+i);
        for(int i=0;i<m;i++)
            scanf("%d",b+i);
        printf("%d\n",match());
    }
    return 0;
}
*/
