/*
����:Ignatius�������һ������,��ʦ�������ܶ൥��(ֻ��Сд��ĸ���,
�������ظ��ĵ��ʳ���),������ʦҪ��ͳ�Ƴ���ĳ���ַ���Ϊǰ׺�ĵ�������
(���ʱ���Ҳ���Լ���ǰ׺).����ÿ������,�����Ը��ַ���Ϊǰ׺�ĵ��ʵ�����.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1251
˼·:�ֵ���ģ��.
*/
/*
�ֵ����Ŀռ临�Ӷ��ΪΪ����(ģʽ���ĳ��Ⱥ�)*26,
����ڵ�Ͳ��ҽڵ�ĸ��Ӷ�ΪO(n),nΪ���ģʽ���ĳ���.
*/
//ac 218ms ��̬����ʵ��trie��
#include<cstdio>
#include<cstring>
#define maxn 1000010 //�����1000010ȡ���Ǹ��������Χ,ʵ������ڵ�϶�ܿ�������ռ俪��Ҳ��ԶԶ������,Tire���Կռ任ʱ���һ�ֲ���

char s[20];
int trie[maxn][26];//ÿ�����׽ڵ㶼�����26��Ҷ�ӽڵ����26��Ӣ����ĸ
int cnt[maxn],pos=1;//pos����ÿ����ĸ��Ӧ�Ľڵ���

void insertNode(){//O(n)
    int root=0,child;
    for(int i=0;s[i];i++){
        child=s[i]-'a';
        //ͬһ���׽ڵ�Ķ��ӽڵ����ڵ� trie ��ά�������±�����ͬһ�е�,
        //ÿ�����ӽڵ���Ժ͸��׽ڵ㲻��ͬһ���±�,posֵҲ�п������ܴ�
        if(!trie[root][child])
            trie[root][child]=pos++;//���������޶��ӽڵ�Ͳ���
        root=trie[root][child];
        cnt[root]++;//��¼����ַ���ǰ���ɵ��Ӵ���Ӧ��ǰ׺�����˶��ٴ�
    }
}

int findNode(){//O(n)
    int root=0,child;
    for(int i=0;s[i];i++){
        child=s[i]-'a';
        if(!trie[root][child])//û���Ը��ַ���Ϊǰ׺���Ӵ�
            return 0;
        root=trie[root][child];//�������±�����Ӧ�Ķ��ӽڵ�
    }
    return cnt[root];
}

int main(){
    while(gets(s)){//O(n*len)
        if(s[0]==NULL) break;
        insertNode();
    }
    while(gets(s))
        printf("%d\n",findNode());
    return 0;
}

/*
//ac 171ms ��ʽ�ṹָ��ʵ��trie��
#include<cstdio>
//������ʽ�ṹֻ����C++�༭��������,����HDU�� G++��Memory Limit Exceeded 171ms ���鷽ʽ218ms ���
struct trie{
    trie *next[26];
    int cnt;
    trie(){
        for(int i=0;i<26;i++)
            next[i]=NULL;
        cnt=0;
    }
}node;
char s[20];
int pos=1;

void insertNode(){
    trie *root=&node;
    int c;
    for(int i=0;s[i];i++){
        c=s[i]-'a';
        if(!root->next[c])
            root->next[c]=new trie;//��malloc����ִ��trie()���캯�� ��new��
        root=root->next[c];
        root->cnt++;
    }
}

int findNode(){
    trie *root=&node;
    int c;
    for(int i=0;s[i];i++){
        c=s[i]-'a';
         if(!root->next[c])
            return 0;
         root=root->next[c];
    }
    return root->cnt;
}

int main(){
    while(gets(s)){//O(n^2)
        if(s[0]==NULL) break;
        insertNode();
    }
    while(gets(s))
        printf("%d\n",findNode());
    return 0;
}
*/

/*
//ac 818ms map<string,int>ʵ��
#include<cstdio>
#include<iostream>
#include<string>
#include<map>
using namespace std;
map<string,int> mp;
int main(){//811ms ӳ��Ͳ�ѯ�����ʱ ����
    string ss,s;

    while(getline(cin, s) && s != ""){//cin�����س���
        int len=s.size();
        ss="";
        for(int i=0;i<len;i++){
            ss+=s[i];
            mp[ss]++;
        }
    }
    while(cin >> s)
        cout << mp[s] <<endl;
    return 0;
}
*/
