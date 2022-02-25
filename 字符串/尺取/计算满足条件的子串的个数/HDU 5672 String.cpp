/*
����:ժ������
��T��������ÿ��������һ����һ���ַ���s���ڶ�����һ������k��
�������ַ��������ٺ���k����ͬ��ĸ�����ַ����ĸ���.
10<=|s|<=10^6.1<=k<=26.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5672
˼·:��ȡ.��ָ���ƶ������ǵ���ǰ[l,r]�Ӵ��к��в�ͬ��ĸ
�ĸ���δ�ﵽk��ʱ,��ָ�������ƶ�.
*/
//ac 530ms
//�±��0��ʼ,++r,++l,��ʼ��r=l=-1
#include<cstdio>
#include<cstring>
#define N 1000010
typedef long long ll;

int k,num[26];
ll ans;
char s[N];

int check(){
    int cnt=0;
    for(int i=0;i<26;i++){
        if(num[i])
            cnt++;
    }
    return cnt == k;
}

int main(){
    int T,l,r,len;
    scanf("%d",&T);
    while(T--){
        memset(num,0,sizeof(num));
        ans=0;
        scanf("%s",s);
        scanf("%d",&k);
        len=strlen(s);
        l=r=-1;
        while(1){//��������������r<len-1,��Ϊ��ָ�뵽��ĩβʱ,����l��������,��ǰ�Ӵ� ���в�ͬ��ĸ��������k��,��ʱ����Ҫ�ۼ��Ӵ�����.
            while(r<len-1 && !check())
                num[s[++r]-'a']++;
            if(!check())//���������� ����ָ���ƶ���β��,��ǰ�Ӵ�[l,r]�Ӵ����еĲ�ͬ��ĸ����Ҳδ�ﵽk��
                break;
            //�������r �ǲ����,lһֱ����ǰ�ƶ�,���������ַ��������ĸ��ͬ,��ǰ�Ӵ��в�ͬ��ĸ����һֱ����k��
            //����ʵ�������������Ӵ���[l,r] [l,r+1] [l,r+2] ...[l,len-1] ������ۼӵĸ�����len-r
            ans+=len-r;
            num[s[++l]-'a']--;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 140ms cntֱ�Ӽ�¼�Ƿ�ﵽ��k����ͬ���ַ�,����ѭ���ж�
#include<cstdio>
#include<cstring>
#define N 1000010
typedef long long ll;

int k,num[26],cnt;
ll ans;
char s[N];

int main(){
    int T,l,r,len;
    scanf("%d",&T);
    while(T--){
        memset(num,0,sizeof(num));
        ans=0;
        scanf("%s",s);
        scanf("%d",&k);
        len=strlen(s);
        l=r=-1;
        cnt=0;
        while(1){
            while(r<len-1 && cnt!=k){
            	if(!num[s[++r]-'a'])
            		cnt++;
            	num[s[r]-'a']++;
			}
            if(cnt!=k)
                break;
            ans+=len-r;
            num[s[++l]-'a']--;
            if(!num[s[l]-'a'])
            	cnt--;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/

/*
//ac 546ms
//�±��0��ʼ,r++,l++,��ʼ��r=l=0
#include<cstdio>
#include<cstring>
#define N 1000010
typedef long long ll;

int k,num[26];
ll ans;
char s[N];

int check(){
    int cnt=0;
    for(int i=0;i<26;i++){
        if(num[i])
            cnt++;
    }
    return cnt == k;
}

int main(){
    int T,l,r,len;
    scanf("%d",&T);
    while(T--){
        memset(num,0,sizeof(num));
        ans=0;
        scanf("%s",s);
        scanf("%d",&k);
        len=strlen(s);
        l=r=0;
        while(1){
            while(r<len && !check())
                num[s[r++]-'a']++;
            if(!check())
                break;
            ans+=len-r+1;
            num[s[l++]-'a']--;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/

/*
//ac 608ms
//�±��1��ʼ,++r,++l,��ʼ��r=l=0
#include<cstdio>
#include<cstring>
#define N 1000010
typedef long long ll;

int k,num[26];
ll ans;
char s[N];

int check(){
    int cnt=0;
    for(int i=0;i<26;i++){
        if(num[i])
            cnt++;
    }
    return cnt == k;
}

int main(){
    int T,l,r,len;
    scanf("%d",&T);
    while(T--){
        memset(num,0,sizeof(num));
        ans=0;
        scanf("%s",s+1);
        scanf("%d",&k);
        len=strlen(s+1);
        l=r=0;
        while(1){
            while(r<len && !check())
                num[s[++r]-'a']++;
            if(!check())
                break;
            ans+=len-r+1;
            num[s[++l]-'a']--;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/

