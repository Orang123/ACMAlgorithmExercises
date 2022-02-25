/*
����:
�����ַ���str1,str2,���Խ�str1ѹ��ջ��,��������ջ�����ַ�ȥ
ƥ��str2,str1���Բ���ȫѹ��ջ����ȥƥ��,�Ǳ�ѹ��ƥ���,
ÿ��str1��str2ƥ���,��ջpop,��ѹջ��������'i',����ջ��������'o',
�����ֵ������str1��str2ƥ�������io��������.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1515
˼·:dfs����,��Ϊ�����ֵ���'i'<'o',����Ⱦ����ܵؽ�
str1ѹջ,����ʱ,�ж�ջ��Ԫ���Ƿ��str2��ǰλ��ƥ��.
��str1��str2��ȫƥ��ʱ ��:i == len1 j == len2.
*/
//ac 109ms dfs����
#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 110
using namespace std;

int len1,len2;
char str1[N],str2[N];
stack<char> s;
vector<char> ans;

void dfs(int i,int j){
    if(i == len1 && j == len2){
        for(char &x : ans)
            printf("%c ",x);
        printf("\n");
        return;
    }
    if(i<len1){//�������Ƚ�str1 ��ջ i���� �ֵ����С
        s.push(str1[i]);
        ans.push_back('i');
        dfs(i+1,j);
        s.pop();
        ans.pop_back();
    }
    if(j<len2 && !s.empty() && s.top() == str2[j]){//�жϵ�ǰջ��Ԫ���Ƿ��str2[j]ƥ��
        s.pop();
        ans.push_back('o');
        dfs(i,j+1);
        s.push(str2[j]);
        ans.pop_back();
    }
}

int main(){
    while(scanf("%s",str1)!=EOF){
        scanf("%s",str2);
        len1=strlen(str1);
        len2=strlen(str2);
        printf("[\n");
        if(len1 == len2)//���ַ���������ͬ ����ƥ��
            dfs(0,0);
        printf("]\n");
    }
    return 0;
}
