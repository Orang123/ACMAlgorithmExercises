/*
����:��һ���ٳ��ϰڷ���һ��N��ʯ�ӡ���Ҫ��ʯ���д���غϲ���һ�ѡ�
�涨ÿ��ֻ��ѡ���ڵ�2��ʯ�Ӻϲ����µ�һ�ѣ������µ�һ��ʯ������Ϊ�ôκϲ��ĵ÷֡�
�����һ���㷨���������N��ʯ�Ӻϲ���һ�ѵ���С�÷֡�
N<=40000.
����:https://www.luogu.com.cn/problem/P5569
˼·:
GarsiaWachs�㷨
n���ɴ� 40000,�ı��β���ʽ�Ż�Ҳ��TLE,����GarsiaWachs,
����㷨ר�Ž��ʯ�Ӻϲ�������.
*/
#include<bits/stdc++.h>
using namespace std;
long long ans,n;
vector<int> l;
inline int read()
{
    int i=0; char c=getchar();
    while(c>'9'||c<'0')c=getchar();
    while(c>='0'&&c<='9')i=i*10+c-'0',c=getchar();
    return i;
}
int merge()
{
    int k=l.size()-1-1;//���������A[0]��A[n-3]�Ҳ���A[k]<=A[k+2]����ôk��ֵӦ��Ϊn-2
    for(int i=0;i<l.size()-2;++i)
    {
        if(l[i]<=l[i+2])
        {
            k=i;
            break;
        }
    }
    int tmp=l[k]+l[k+1];
    l.erase(l.begin()+k);
    l.erase(l.begin()+k);//ɾ��
    int in=-1;
    for(int i=k-1;i>=0;--i) //���������ҵ�һ��
    {
        if(l[i]>tmp)
        {
            in=i;
            break;
        }
    }
    l.insert(l.begin()+in+1,tmp);//��Ϊ���ں�����룬����Ҫ+1
  return tmp;
}
int main()
{
    cin>>n;
    for(int i=1; i<=n;++i)
        l.push_back(read());
    for(int i=0;i<n-1;i++)
        ans+=merge();
    cout<<ans;
    return 0;
}
