/*
����:ժ������
��һ�����������ʽ��Ҫ���޸ľ����ٵ�����ʹ�޸ĺ��������ֻ��Ψһ�⡣
���ֿ����޸�Ϊͨ���,ͨ���Ҳ�����޸�Ϊ���֣�����Ҳ���Ըı�Ϊ��һ���֣�
��������ɾ�����ʽ�������漰����������û��ǰ���������������������һ��
����a*b=c������a��b��c�ֱ������2��2��4λ�����»��߱�ʾδ֪���֡�����
��֤���н⣬���о����任��϶�����һ�����ʽ��Ψһ�⡣����ж���⣬
����ֵ�����С�Ľ�.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3259
˼·:������dfsö���޸ĺ�ı��ʽ,������һ��dfsȥ�ͨ��� ��֤��ǰ���ʽ
�Ľ���Ƿ���Ψһ��.��Ϊ���ӶȺܴ�,���Ҫ�õ�����������ö���޸Ĵ�����������.
*/
//ac 110ms IDDFS
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5
#define INF 0x3f3f3f3f
using namespace std;

int len[3];
char str[3][N],op[12]="*0123456789";//�����ֵ���˳��'*'����С

//ǰ�������� ͨ������,cal()��֤ ����֮�������ֲ����Ƿ��str[3]һ��
int cal(){
    int a=0,b=0;
    for(int i=0;i<len[0];i++)
        a=a*10+str[0][i]-'0';
    for(int i=0;i<len[1];i++)
        b=b*10+str[1][i]-'0';
    int c=a*b;
    char s[4];
    int i=1;
    while(c){
        s[len[2]-i]=c%10+'0';
        c/=10;
        i++;
    }
    if(i!=len[2]+1)//���Ȳ�һ�� ���޽�
        return 0;
    for(int j=0;j<len[2];j++){
        //str[2]����ͨ����ĵط� ���ֱ��뱣��һ��
        if(str[2][j]!='*' && str[2][j]!=s[j])
            return 0;
    }
    return 1;//�н�
}

//���޸���dep�ε�ԭ������֤ ���Ƿ�Ψһ,�ǰ����������ͨ���
int check(int k,int pos){
    if(pos == len[k]){
        k++;
        pos=0;
    }
    if(k == 2)//ǰ�������� ͨ������,cal()��֤ ����֮�������ֲ����Ƿ��str[2]һ��
        return cal();
    char old=str[k][pos];
    int cnt=0;//��¼��ǰ������
    if(str[k][pos]!='*')//���������� �Ͳ������
        cnt+=check(k,pos+1);
    else{//ͨ��������
        for(int i=1;i<11;i++){//ֻ������� ������±���1,10
            if(i == 1 && !pos)//ȥ��ǰ����
                continue;
            str[k][pos]=op[i];
            cnt+=check(k,pos+1);
            if(cnt>1)//����1 ��˵���Ѿ���Ψһ��,�Ͳ�������֤ ���������֦ 230ms
                break;
        }
    }
    str[k][pos]=old;//��ΪҪ���ԭ���޸ĺ���ͨ�����ԭ��,����Ҫ��ԭ
    return cnt;
}

//�޸�dep��ԭ��
int dfs(int d,int dep,int k,int pos){
    if(d == dep)
        return check(0,0) == 1;//�жϵ�ǰ�޸Ĵ���Ϊdep�ı��ʽ ���Ƿ�Ψһ 0�����޽�,>1����ⲻΨһ
    if(pos == len[k]){
        k++;
        pos=0;
    }
    if(k == 3)//�޸Ĵ���δ�ﵽdep��,�����޸Ĵ���Ϊ0,dep-1�Ľ����ǰ���Ѿ�ȫ����֤ �ⲻΨһ���޽���.
        return 0;
    char old=str[k][pos];
    //�����Ȱ��ձ����old���޸�ȥ����,�����������Ĳ�һ�����ֵ�����С��.
    for(int i=0;i<11;i++){//ö��str[k][pos]λ�� �����޸ĵ�����
        if(i == 1 && !pos)//0 ���ܷ��ڵ�һ��
            continue;
        str[k][pos]=op[i];
        if(op[i] == old){//�������old����,�޸Ĵ�������,�����ǰ����ֵ���ö��,��dep���޸��� �Ƿ�Ψһ��
            if(dfs(d,dep,k,pos+1))
                return 1;
        }
        else{//��ԭ�ȵ�old�޸�Ϊop[i]
            if(dfs(d+1,dep,k,pos+1))
                return 1;
        }
    }
    str[k][pos]=old;//����ʱ�ָ� ԭ�ȵ�old
    return 0;
}

int main(){
    int cas=0;
    while(scanf("%s",str[0]) && str[0][0]!='0'){
        scanf("%s",str[1]);
        scanf("%s",str[2]);
        len[0]=strlen(str[0]);
        len[1]=strlen(str[1]);
        len[2]=strlen(str[2]);
        cas++;
        for(int i=0;;i++){
            if(dfs(0,i,0,0)){
                printf("Case %d: %s %s %s\n",cas,str[0],str[1],str[2]);
                break;
            }
        }
    }
    return 0;
}

/*
//ac 2.98s dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5
#define INF 0x3f3f3f3f
using namespace std;

int len[3],ans;
char str[3][N],op[12]="*0123456789",res[3][N];

int cal(){
    int a=0,b=0;
    for(int i=0;i<len[0];i++)
        a=a*10+str[0][i]-'0';
    for(int i=0;i<len[1];i++)
        b=b*10+str[1][i]-'0';
    int c=a*b;
    char s[4];
    int i=1;
    while(c){
        s[len[2]-i]=c%10+'0';
        c/=10;
        i++;
    }
    if(i!=len[2]+1)
        return 0;
    for(int j=0;j<len[2];j++){
        if(str[2][j]!='*' && str[2][j]!=s[j])
            return 0;
    }
    return 1;
}

int check(int k,int pos){
    if(pos == len[k]){
        k++;
        pos=0;
    }
    if(k == 2)
        return cal();
    char old=str[k][pos];
    int cnt=0;
    if(str[k][pos]!='*')
        cnt+=check(k,pos+1);
    else{
        for(int i=1;i<11;i++){
            if(i == 1 && !pos)
                continue;
            str[k][pos]=op[i];
            cnt+=check(k,pos+1);
            if(cnt>1)
                break;
        }
    }
    str[k][pos]=old;
    return cnt;
}

void dfs(int d,int k,int pos){
    if(check(0,0) == 1){
        if(d<ans){
        	ans=d;
        	for(int i=0;i<3;i++)
        		strcpy(res[i],str[i]);
		}
        return;
	}
	if(d>=ans)
		return;
    if(pos == len[k]){
        k++;
        pos=0;
    }
    if(k == 3)
        return;
    char old=str[k][pos];
    for(int i=0;i<11;i++){
        if(i == 1 && !pos)
            continue;
        str[k][pos]=op[i];
        if(op[i] == old)
            dfs(d,k,pos+1);
        else
            dfs(d+1,k,pos+1);
    }
    str[k][pos]=old;
}

int main(){
    int cas=0;
    while(scanf("%s",str[0]) && str[0][0]!='0'){
        scanf("%s",str[1]);
        scanf("%s",str[2]);
        len[0]=strlen(str[0]);
        len[1]=strlen(str[1]);
        len[2]=strlen(str[2]);
        cas++;
        ans=INF;
        dfs(0,0,0);
        printf("Case %d: %s %s %s\n",cas,res[0],res[1],res[2]);
    }
    return 0;
}
*/

/*
bfs ����ģ��,״̬���ñ�ʾ,�޷�����,�ض���MLE.
*/
