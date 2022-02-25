/*
����:ժ������
����n�����ʵ�Ȩֵ������ʹ�þż�ƴ���������û��İ�������Ȩֵ��󵥴ʣ�
������ж���������ֵ�����С�ģ��ʵ��û�����һ����ʱ��Ӧ�õ����ĸ����ʡ�
�涨ÿ�ΰ�����ֵһ����1-9�����֣����Ϊ1���ô�������һϵ�а���������ֵ�
��û����֮��Ӧ�ĵ��ʣ������MANUALLY�����������a�ǵ���b��ǰ׺����ôa��Ȩֵ
Ϊ���ߵ��ۼӺͣ��������hel 2��hello 4��hel��ȨֵΪ2+4=6�����һ��������
�ֵ��У���ô����ǰ׺Ҳ������Ϊ�����ֵ��У����Ҷ�Ӧ��ȨֵΪ����ĸ��Ȩֵ��
��������m�����ִ�,���������ÿ������ʱ����Ȩֵ���ĵ���.
n<=1000,���ʳ���<=100.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1298
˼·:�Ƚ�n��ģʽ�����ʹ������ֵ�����,����ÿ����������ִ�,
dfs�����ֵ���ö��ÿ�������Ͽ��ܳ��ֵ���ĸ,��¼�ڰ��¸�������ʱ
����Ȩֵ���ĵ���,�������������ִ�ȫ������.
*/
//ac 0ms �ֵ���+dfs
#include<cstdio>
#include<cstring>
#define N 100010

char phone[10][5]={"","","ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ"};
int n,m,tr[N][26],wordVal[N],cnt,p[110],plen;
char s[110],ans[110][110],tp[110];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordVal[cnt]=0;
    return cnt;
}

void insertWord(int val){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        wordVal[rt]+=val;
    }
}

void dfs(int rt,int k){
    if(wordVal[rt]>p[k]){//��¼����Ϊk�ĵ��ʵ����Ȩֵ��
        p[k]=wordVal[rt];
        tp[k]='\0';
        strcpy(ans[k],tp);
    }
    if(k == plen)
        return;
    int id=s[k]-'0';
    int num=strlen(phone[id]);
    int son;
    for(int i=0;i<num;i++){
        son=phone[id][i]-'A';//�ֻ��ϵĵ����Ǵ�д,������ʵ�����ִ�Сд
        if(tr[rt][son]){
            tp[k]='a'+son;//��¼��ǰ�����±�Ϊk�����ֳ��ֵ���ĸ
            dfs(tr[rt][son],k+1);
        }
    }
}

int main(){
    int T,cas=0,val;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();
        cas++;
        scanf("%d",&n);
        while(n--){
            scanf("%s %d",s,&val);
            insertWord(val);
        }
        scanf("%d",&m);
        printf("Scenario #%d:\n",cas);
        while(m--){
            scanf("%s",s);
            plen=strlen(s)-1;//���һ������Ϊ1 ���������ĸ
            memset(p,0,sizeof(p));
            dfs(0,0);
            for(int i=1;i<=plen;i++){
                if(p[i])
                    printf("%s\n",ans[i]);
                else
                    printf("MANUALLY\n");
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
