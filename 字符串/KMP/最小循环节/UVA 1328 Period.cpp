/*
����:��һ����Ϊn���ַ��������ַ�����ǰ׺�ǲ������ڴ���
Ҳ�ͻ���˵�����Ƿ�Ϊĳһ�ַ����ظ����Ӷ��ɣ����������ظ�2�Σ�
����ѭ���ڣ�����������ڴ������ǰ׺�����һ����ĸ��λ�ú��������.
n<=10^6.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4074
˼·:
next�����±��0��ʼ i-next[i]��ʾ����Ϊi��ǰ׺��Сѭ���ڵĳ��� i%(i-next[i]) == 0 ��ʾ��������ѭ����
next�����±��1��ʼ i+1-next[i+1]��ʾ����Ϊi��ǰ׺��Сѭ���ڵĳ��� i%(i+1-next[i+1]) == 0 ��ʾ��������ѭ����
��ĿҪ������ظ�������С��2��ѭ����,
��˶����±��0��ʼ ����Ϊi��ǰ׺ next[i]=0�Ĳ�����,ֻ��һ��ѭ����.
�±��0��ʼ ����Ϊi��ǰ׺ next[i+1]=1�Ĳ�����,ֻ��һ��ѭ����.
*/
//ac 40ms �±��1��ʼ
#include<cstdio>
#include<cstring>
#define N 1000010

int n,next[N];
char str[N];

void getNext(){
    int i=0,j=1;
    next[1]=0;
    while(j<=n){
        if(!i || str[i] == str[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int main(){
    for(int cas=1;scanf("%d",&n) && n;cas++){
        scanf("%s",str+1);
        getNext();
        printf("Test case #%d\n",cas);
        for(int i=2;i<=n;i++){
            //����1 ��ʾ1~i���ͬǰ��׺����Ϊ0,����ѭ����ֻ��1��,
            //����1~i��Ϊһ������,������ĿҪ���ѭ��������Ϊ2,����1 ����Ϊ�±��1��ʼ����next����,���ҳ�ʼ���Ϸ�ֵΪ0
            if(next[i+1] == 1) continue;
            if(i%(i+1-next[i+1]) == 0)//i-next[i+1]�ᵼ�� ��ĸΪ0 �����쳣
                printf("%d %d\n",i,i/(i+1-next[i+1]));
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 40ms �±��0��ʼ
#include<cstdio>
#include<cstring>
#define N 1000010

int n,next[N];
char str[N];

void getNext(){
    int i=-1,j=0;
    next[0]=-1;
    while(j<n){
        if(i == -1 || str[i] == str[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int main(){
    for(int cas=1;scanf("%d",&n) && n;cas++){
        scanf("%s",str);
        getNext();
        printf("Test case #%d\n",cas);
        for(int i=2;i<=n;i++){
            if(!next[i]) continue;
            if(i%(i-next[i]) == 0)
                printf("%d %d\n",i,i/(i-next[i]));
        }
        printf("\n");
    }
    return 0;
}
*/

/*
//wa �������Ż���next����,�Ǹ�ֻ�ܵ��������ַ���ƥ��,
//���������ѭ���ڵ�����,��Ҫ�õ��������ǰ��׺,�Ż���next���� �������Ѿ������������ǰ��׺��
#include<cstdio>
#include<cstring>
#define N 1000010

int n,next[N];
char str[N];

void getNext(){
    int i=-1,j=0;
    next[0]=-1;
    while(j<n){
        if(i == -1 || str[i] == str[j]){
        	i++;
			j++;
			if(str[i] != str[j])
				next[j]=i;
			else
				next[j]=next[i];
		}
        else
            i=next[i];
    }
}

int main(){
    for(int cas=1;scanf("%d",&n) && n;cas++){
        scanf("%s",str);
        getNext();
        printf("Test case #%d\n",cas);
        for(int i=2;i<=n;i++){
            if(!next[i]) continue;
            if(i%(i-next[i]) == 0)
                printf("%d %d\n",i,i/(i-next[i]));
        }
        printf("\n");
    }
    return 0;
}
*/
