/*
����:��һ�����8����������ͼ���ѽ�����ź����ͼ��ÿ����(u,v)��
u��v�������е��������Ϊ�����еĴ����������С������.
����:https://www.luogu.com.cn/problem/UVA140
˼·:ö��ȫ����,�����������ڽӵ���������,�����Сֵ.
*/
//ac 0ms next_permutation��ȡȫ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#define N 100
#define INF 0x3f3f3f3f
using namespace std;

int id[N],letter[N],cnt,len,a[10],pos[N],ans,res[10];
char input[N];
vector<int> u,v;

int main(){
    while(scanf("%s",input) && input[0] != '#'){
        u.clear();
        v.clear();
        cnt=0;
        ans=INF;
        for(char ch='A';ch<='Z';ch++){
            if(strchr(input,ch)!=NULL){
                id[ch]=++cnt;//��¼��ĸ���
                letter[cnt]=ch;
            }
        }
        len=strlen(input);
        int p=0,q=0;
        while(1){
            while(p<len && input[p]!=':')
                p++;
            if(p == len)
                break;
            while(q<len && input[q]!=';')
                q++;
            for(int i=p+1;i<q;i++){
                u.push_back(id[input[p-1]]);
                v.push_back(id[input[i]]);
            }
            p++,q++;
        }
        for(int i=1;i<=cnt;i++)
            a[i]=i;
        do{
            for(int i=1;i<=cnt;i++)
                pos[a[i]]=i;
            int bandwidth=0;
            for(int i=0;i<u.size();i++)//��¼�����ڽӵ��������еľ��� ���������
                bandwidth=max(bandwidth,abs(pos[u[i]]-pos[v[i]]));
            if(bandwidth<ans){
                ans=bandwidth;
                memcpy(res,a,sizeof(a));
            }
        }while(next_permutation(a+1,a+1+cnt));
        for(int i=1;i<=cnt;i++)
            printf("%c ",letter[res[i]]);
        printf("-> %d\n",ans);
    }
    return 0;
}
