/*
����:ժ������
����һ��R*C���ַ�����,Ҫ������С���Ӿ���,������ͨ�������ظ����Ӿ���
�Ӷ��õ�һ��������ԭ�����������,������Ӿ�������?
ע��:
���������еĴ�"AB",ʵ����ƴ�ɵ�ͼ����Ҫ����ԭʼͼ����.
ABABAB ����1��B ֻҪ�������ھ���.
ABABAB        B
r<=10^4,c<=75.
����:http://poj.org/problem?id=2185
˼·:���԰�ÿһ�е���һ��Ԫ��,�Ƚ������ǱȽ������ж�Ӧ�����е�Ԫ���Ƿ����,
���next���,r-next[r]��Сѭ���ڱ�����С����Ŀ�.
���԰�ÿһ�е���һ��Ԫ��,�Ƚ������ǱȽ������ж�Ӧ�����е�Ԫ���Ƿ����,
���next���,c-next[c]��Сѭ���ڱ�����С����ĳ�.������������С���.
*/
//ac 782ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
#define M 80
using namespace std;

int r,c,nxt[N];
char p[N][M];

int checkCol(int i,int j){
    for(int k=0;k<c;k++){
        if(p[i][k]!=p[j][k])
            return 0;
    }
    return 1;
}

int checkRow(int i,int j){
    for(int k=0;k<r;k++){
        if(p[k][i]!=p[k][j])
            return 0;
    }
    return 1;
}

void getNextRow(){
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<r){
        if(i == -1 || checkCol(i,j))
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

void getNextCol(){
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<c){
        if(i == -1 || checkRow(i,j))
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    int row,col;
    scanf("%d%d",&r,&c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++)
            scanf(" %c",&p[i][j]);
    }
    getNextRow();
    row=r-nxt[r];//��
    getNextCol();
    col=c-nxt[c];//��
    printf("%d",row*col);
    return 0;
}
