/*
����:
��һ��ֽ����Ϸ��������˼������N��ֽ�ƣ�һ���ſ���ֽ�����������棬
��ʼ��ֽ�ƿ�����һ���ҵ�״̬����Щ��������Щ����������������Ҫ����
��Щֽ�ơ������鷳���ǣ�ÿ���㷭һ��ֽ�ƣ������������������з���������ʱ��
����������ֽ�ƣ�����ߺ����ұߵ�ֽ�ƣ�ֻ��Ӱ�츽��һ�ţ�Ҳ������ŷ�����
���ڸ���һ���ҵ�״̬�������ܷ����������ã�ʹ��ÿ��ֽ�ƶ����泯�ϣ�
������ԣ�������Ҫ���ٴβ�����
һ�γ��Ȳ�����20���ַ���,1��ʾ���泯�ϣ�0��ʾ���泯�ϡ�
����:https://acm.hdu.edu.cn/showproblem.php?pid=2209
˼·:ֻ���������,��һ���ǵ�һ����,�ڶ����ǵ�һ������,
�жϵ�ʱ���ж�a[i-1]�����1�Ļ�,��תa[i-1]��a[i]��a[i+1].
a[i-1]=!a[i-1];
a[i]=!a[i];
a[i+1]=!a[i+1];i<len,
���һ���Ƶ���Ŷ���� �Ƿ񱻷�ת������0.
����Ƿ���1,��˵���÷�ʽ�޽�.
*/
//ac 0ms ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int a[N],len,ans;
char str[N];

int cal(int cnt){
    for(int i=1;i<len;i++){
        if(a[i-1]){
            a[i-1]=!a[i-1];
            a[i]=!a[i];
            a[i+1]=!a[i+1];
            cnt++;
        }
    }
    if(a[len-1])
        return INF;
    else
        return cnt;
}

int main(){
    while(scanf("%s",str)!=EOF){
        ans=INF;
        len=strlen(str);
        for(int i=0;i<len;i++)
            a[i]=str[i]-'0';
        a[0]=!a[0];
        a[1]=!a[1];
        ans=min(ans,cal(1));
        for(int i=0;i<len;i++)
            a[i]=str[i]-'0';
        ans=min(ans,cal(0));
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("NO\n");
    }
    return 0;
}
