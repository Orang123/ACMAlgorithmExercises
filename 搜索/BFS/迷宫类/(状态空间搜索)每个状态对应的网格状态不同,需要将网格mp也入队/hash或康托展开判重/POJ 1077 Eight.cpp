/*
����:�����������̲�������.
��3��3������,���а˸�����,ÿ�������ϱ���1��8��ĳһ����,
��ͬ�����ϱ�����ֲ���ͬ.�����ϻ���һ���ո�'x',��ո�����
�����ӿ��ԺͿո񽻻�λ��.���̵�״̬��ʾΪ��(0,0)��(2,2)��������,
���϶����γɵ����д�,Ҫ������������:����һ����ʼ״̬��һ��
Ŀ��״̬,���������ƶ���ʾΪ'u',�����ƶ���ʾΪ'd',�����ƶ���
ʾΪ'l',�����ƶ���ʾΪ'r',�ҳ�һ�ִӳ�ʼ״̬ת���Ŀ��״̬���ƶ�
�ո������ٵ��ƶ���������.����������.
ע��:�ո�'x'ʵ�ʱ�ʾ��'0'��'9' �����ϣ���ػ���չ������
����POJ 1077�����ݽ���,ò������û�в��ɴ������,HDU 1043���ݽ�ǿ,
�о���ͨ�ĵ���bfs��TLE,ֻ����˫����ѻ�A*�������ܹ�.
����:http://poj.org/problem?id=1077
˼·:��ش�ţ����:https://blog.csdn.net/u012283461/article/details/79078653
https://www.cnblogs.com/goodness/archive/2010/05/04/1727141.html

����������,�ؼ���9�����������ж�Ӧ��10������9λ��,�޷�ֱ�ӿ�
��СΪ10^8������,��MLE.�����ֽ����������ѹ��״̬�ռ�.

����1:hash����,��ϣ����Ϊ����ȡ�� �Թ�ϣ��ȡģ,��������Ϊ1000003(����),
�������ڲ�ͬ����ȡģ�����ĳ�ͻ,������ַ�������һ��������������.ʵ�ʹ�ϣ��
�ĳ��ȿ�����Ϊ362880,���������ӷ��������ͷ����Ϊ1000003.����״̬���صĿռ临�ӶȾ͵õ���ѹ��.
����hash���ط���ΪҪ��������������,������Ϊ��ͬ���е�hashȡģֵ��������ͬ��,
���ڳ�ͻ��ͬһ�������е�״̬,���ü�¼,��˲�����stl �е�queueȥ��¼��һ״̬.
���ֻ����дʵ�ֶ���,���д�СΪ362880(9�������п������и���).��Ȼʵ��9������
����״̬�ܹ���9!=362880��,��ʵ�ʳ�ʼ״̬������ֻ�ܵ����������������ͬ������,
Ҳ����������ֻ�ܵ���������,ż����Ҳֻ�ܵ���ż����,��ż����֮�䲻���໥ת��.
����ʵ�ʹ�ϣ��ĳ��� ��������9!=362880��ô��.

ע��:�������е�ʱ��������cantorչ�����������Ψһ��ŵ����ط���,���ӳ��õ���hash.


����2:����չ������,�ö�ĳһ����a�ÿ���չ������x=sum[0]*(n-1-0)!+sum[1]*(n-1-1)!+...+sum[n-2]*1!+sum[n-1]*0!
����sum[i]��ʾa[i+1]~a[n-1]�б�a[i]С�����ĸ���.
������x��ʾ��ǰ����a���������еĴ���Ϊx.
����:12345���д���Ϊ0,12354���д���Ϊ1.
����ԭ�ȵ�״̬�ռ���10^8�Ϳ�ѹ����9!=366280,�����Ϳ����ж�ĳ�����д���
(<366280,ʵ��ĳЩ����״̬���ɴ�,ԶС��9!)�Ƿ��Ѿ�������,������ֱ���ж�
��ǰ�������10������ֵ�Ƿ���ֹ�.
����չ���ο�����:https://blog.csdn.net/ltrbless/article/details/87696372

����3:ժ��Eric ppt
Ҳ����ʹ��STL�е�set��map������
�����ȼ���ƽ����
O(logn)�Ĳ��ң�����Ч��
һ��ģ�����Ч�ʱ�hashҪ��
�������ױ�д
����ʹ��set,map�����壬���TLE���ٻ���Hash�����������Ԥ��һ���Ƿ��TLE��
map+bfs��ʵ�ֿɲο�:https://blog.csdn.net/u012283461/article/details/79078653

һ���򵥵ĳ�����֦:
һ��״̬��ʾ��һά����ʽ,������ո�'0'֮���������ֵ�������֮��,Ҳ����ÿ������
�������С�����ֵĸ����ĺ�,��Ϊ���״̬��������.Ҳ������ÿ������ǰ�����������ָ����ĺ�.
��������ż������ͬ������һ���ǿɴ��,��������ż���ʲ�ͬ������һ���ǲ��ɴ��,
����������ʱ�ɲ���ո�λ'x'.
֤��:�������ƶ��ո�ʱ,���򲻱�.�������ƶ��ո�ʱ,�൱�ڽ�һ��������ǰ��������ƶ�����,
����������������Ҫô��������С��,������ܡ�2;Ҫôһ���ϴ�һ����С,���򲻱�.
���Կɵý���:ֻҪ���໥�ɴ������״̬,���ǵ�������ż����ͬ.
����֤��ժ�Բ���:https://blog.csdn.net/hnust_xiehonghao/article/details/7951173
��׼�ĸ����������ж��Ƿ��н�ı��:https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/

��������:����˫����ѡ�A*������ʵ��.
*/

//��д����ʵ��
//ac 110ms dir[4][2]������������̬ģ��'x'('0')�������������ƶ�
//hash����ַ������
//ʱ�临�Ӷ���Ҫ����hash������ ʵ����ӵ�״̬�������9!=362880
#include<cstdio>
#include<cstring>
#define M 363000//362880 9������ȫ���������9!=362880��
#define HS 1000003//HSȡ��ԽС ��ʱԽ��
using namespace std;

//head�ڽӱ��ͷ �����±��ʾ���� hash����ȡ�������� head[x]��ʾhashȡģֵΪx�Ķ�Ӧ��edge����������±�
//��������С����Ϊhash��ĳ���,�����ȡ��Ӧ�����ܴ�,������ȡȡ���� �ܱ�֤�����ܽ��Ͳ���ʱ�ĳ�ͻ����
//������������еĲ�ѯ�Ϳ��ڳ���ʱ���ڲ��ҵ�
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},cnt,head[HS];
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir;//pso��ʾ'x'��str�е�λ���±�,pre��¼�ϸ�״̬�ڶ���Q�е��±�,dir��¼��ǰ״̬ת�Ƶķ���
    char str[10];
}Q[M];//�����д�ŵ�״̬������������ 0~8 ��9����ȫ���еĸ���

struct HashTable{
    int val,next;//val��ʵ�����д�����Ӧ��10������ֵ,next��ָ��ָ�� hash�� ����ȡ����ֵhval��ͬ�����������еı��״̬
}edge[M];//�������ӷ����ڽӱ����鳤�� Ҳ��0~8 ��9����ȫ���еĸ���

//�㷨ȫ�������� ��Ӧ��10������ֵ
int Hash(char *a){
    int s=0;
    for(int i=0;i<9;i++)
        s=s*10+a[i]-'0';
    return s;
}

//���Բ����ϣ�� ��������
int tryInsert(char *a){
    int s=Hash(a);
    int hval=s%HS;//�������ȡ��ģ��ϣ���Ⱥ����ֵhval
    //�ж�����ַ���ڽӱ����Ƿ� �Ѿ�������s�������״̬
    for(int i=head[hval];i!=-1;i=edge[i].next){//ʱ�临�Ӷ�Ϊ ȡģ��Ĺ�ϣֵ��ȵ��������
        if(edge[i].val == s)//�Ѿ������val���״̬ �����ظ�����
            return 0;
    }
    //���ڳ���ȡ���hashֵ��ͻ����� �÷������ӷ� ����ͻ��ֵ�ŵ�һ��ͬ������
    //�����ǲ����� ͷ�巨(������ʽǰ�������ֲ�߷�ʽ),O(1)ʱ�����
    edge[cnt]=(HashTable){s,head[hval]};
    //head���±���hashȡģ���ֵhval ������ʵ�����е�10����ֵval,
    //val̫���޷�����10λ�����ȵ�����,��˲���hashȡģѹ���ռ�,ʹ�ó�ͻ��״̬������ַ�� ����һ��������
    head[hval]=cnt++;
    return 1;
}

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    //head��tail��ʾ��ͷ����βָ��
    int head=0,tail=0;
    Q[tail++]=st;
    State tp,next;
    int tx,ty,nx,ny,tpos;
    while(head<tail){
        tp=Q[head++];//��׼�ĳ��ӷ�ʽ��head=(head+1)%M
        //������strcmp�ж�str��wa,��֪��ԭ��,��memcmp����ac
        //memcmp������Ϊ ����"123456780" Ҫָ���ֽڳ���Ϊ9byte
        if(!memcmp(tp.str,"123456780",9))
            return head-1;
        tx=tp.pos/3;
        ty=tp.pos%3;
        for(int i=0;i<4;i++){
            nx=tx+dir[i][0];
            ny=ty+dir[i][1];
            if(nx<0 || nx>=3 || ny<0 || ny>=3)
                continue;
            tpos=nx*3+ny;//��״̬ 'x'��str�е�λ��
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='0';
            if(tryInsert(next.str)){
                next.pos=tpos;
                next.pre=head-1;
                next.dir=i;
                //��׼����ӷ�ʽ�Ƕ�βtail=(tail+1)%M,���������Ѿ������˶������鳤�����M,ʵ�ʾ��Դﲻ���������,��˲���ȡģ
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='0';
            st.pos=i;
        }
    }
    /*
    int sum=0;
    //ֱ�Ӹ��ݳ�ʼ״̬��Ŀ��״̬��������ż���Ƿ���ͬ�ж��Ƿ�ɴ�
    //ע�������������������ո�λ'x',ʵ��ֻ��8����,����ʵ ��ʹ��'x'����'0'��'9'ԭ�������е���ż�����Ƿ���ͬҲ�ǲ�Ӱ���
    for(int i=0;i<9;i++){
        if(st.str[i] == '0')//�ո�λ'x'����
            continue;
        for(int j=i+1;j<9;j++){
            //ÿ������str[i]����str[i+1,8]�б���С�����ָ��� Ҳ����str[i]ǰ��str[0,i-1]�б�str[i]������ָ����ĺ�
            if(st.str[j]!='0' && st.str[j]<st.str[i])//st.str[j]!='0' �ո�λ'x'����
                sum++;
        }
    }
    if(sum%2!=0){//Ŀ��̬"12345678x"������Ϊ0(ż��),����ʼ״̬��������Ϊż��Ϊ����,�򲻿ɴ�
        printf("unsolvable\n");
        return 0;
    }
    */
    st.pre=-1;
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else//������ż������ͬ�����о��ǿɴ��,�����������ż�����ж�,����Ĳ��ɴ������ʡ��
		printf("unsolvable");
    printf("\n");
    return 0;
}

/*
//��д����ʵ��
//ac 110ms hash����ַ������ Eric �μ��е����� ��dir[9][4]�����ʾ0������ �ĸ������λ���ڶ�Ӧ��������str�е�λ���±�
//��'0'����'x'
#include<cstdio>
#include<cstring>
#define M 363000//362880 9������ȫ���������9!=362880��
#define HS 1000003
using namespace std;

//dir[pos][0/1/2/3] ��ʾ�������е�'x'('0')�������Ӧ���д�str�����posλ��ʱ,
//������Ӧ3*3����������(0)��(1)��(2)��(3)λ����str�����е�λ�������±�
//dir[pos][i]=-1ʱ,˵��'x'('0')i�����λ���ǲ��Ϸ��� ������0~2������±귶Χ
int dir[9][4]={-1,3,-1,1,
                -1,4,0,2,
                -1,5,1,-1,
                0,6,-1,4,
                1,7,3,5,
                2,8,4,-1,
                3,-1,-1,7,
                4,-1,6,8,
                5,-1,7,-1};
int cnt,head[HS];//�ڽӱ��ͷ ΪHash���С,����Ϊ����,�����ܴ�
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir,val;
    char str[10];
}Q[M];//�����д�ŵ�״̬������������ 0~8 ��9����ȫ���еĸ���

struct HashTable{
    int val,next;
}edge[M];//�������ӷ����ڽӱ����鳤�� Ҳ��0~8 ��9����ȫ���еĸ���

int Hash(char *a){
    int s=0;
    for(int i=0;i<9;i++)
        s=s*10+a[i]-'0';
    return s;
}

int tryInsert(int s){
    int hval=s%HS;
    for(int i=head[hval];i!=-1;i=edge[i].next){
        if(edge[i].val == s)
            return 0;
    }
    edge[cnt]=(HashTable){s,head[hval]};
    head[hval]=cnt++;
    return 1;
}

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    int head=0,tail=0;
    Q[tail++]=st;
    State tp,next;
    int tpos,s;
    while(head<tail){
        tp=Q[head++];
        //������strcmp�ж�str��wa,��֪��ԭ��,��memcmp����ac
        //�����ǲ����� ��¼10������ֵval�� ֱ���ж��Ƿ񵽴�Ŀ��״̬
        if(tp.val == 123456780)
            return head-1;
        for(int i=0;i<4;i++){
            tpos=dir[tp.pos][i];
            if(tpos == -1)//˵����ǰλ�ó����� 3x3����߽�
                continue;
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='0';
            s=Hash(next.str);//hash�����str���ж�Ӧ��10������ֵ
            if(tryInsert(s)){
                next.pos=tpos;
                next.val=s;
                next.pre=head-1;
                next.dir=i;
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='0';
            st.pos=i;
        }
    }
    st.pre=-1;
    st.val=Hash(st.str);
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//��д����ʵ��
//ac 125ms dir[4][2]������������̬ģ��'x'('9')�������������ƶ�
//����չ�������д������� ��'9'����'x' 132456789�Ĵ���Ϊ0
//����չ����ϸ����ο�:https://blog.csdn.net/ltrbless/article/details/87696372
//������չ����δ��
#include<cstdio>
#include<cstring>
#define M 363000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//factorΪǰ8�����Ľ׳� 0~8 0�Ľ׳�0!=1
int factor[9]={1,1,2,6,24,120,720,5040,40320},vis[M];
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir,order;
    char str[10];
}Q[M];

int cantor(char *a){
    int order=0,sum;
    for(int i=0;i<9;i++){
    	sum=0;
    	//����[i+1,8]�б�a[i]С��Ԫ�صĸ���
    	for(int j=i+1;j<9;j++){
    		if(a[i]>a[j])
    			sum++;
		}
		//��ôʵ�ʱ�a[i]С��Ԫ�صĸ������Է���a[i]��λ��,��[i+1,8]�е�����������,����Ϊ(9-i-1)!,�����������Ǳȵ�ǰ�����ַ���aҪС��
		//sumΪ��a[i]С��������a[i]��λ��, factor[9-i-1]Ϊ[i+1,8]�е�����ȫ���и��� (9-i-1)! �׳�
		order+=sum*factor[9-i-1];
	}
	//���н���ۼ����,��ô�ȵ�ǰ�����ַ���aС�����и���Ϊorder,��Ϊ�����Ǵ�0��ʼ��,��ô��ǰ���еõ��������order.
    return order;
}

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    int head=0,tail=0;
    vis[st.order]=1;
    Q[tail++]=st;
    int tx,ty,nx,ny,tpos,order;
    State tp,next;
    while(head<tail){
        tp=Q[head++];
        //'x'��'9'���� 123456789�Ŀ���չ���Ĵ�����0
        //���'x'��'0'������ 123456780�Ŀ���չ�������� 46233
        if(tp.order == 0)
            return head-1;
        tx=tp.pos/3;
        ty=tp.pos%3;
        for(int i=0;i<4;i++){
            nx=tx+dir[i][0];
            ny=ty+dir[i][1];
            if(nx<0 || nx>=3 || ny<0 || ny>=3)
                continue;
            tpos=nx*3+ny;
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='9';
            order=cantor(next.str);
            if(!vis[order]){
            	vis[order]=1;
                next.pos=tpos;
                next.pre=head-1;
                next.dir=i;
                next.order=order;
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='9';
            st.pos=i;
        }
    }
    st.pre=-1;
    st.order=cantor(st.str);
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//stl queue����ʵ�� (State)pre�����¼��ǰ���е���һ״̬tp(State)
//ac 204ms dir[4][2]������������̬ģ��'x'('0')�������������ƶ�
//����չ�������д������� ��'0'����'x' 123456780�Ĵ���Ϊ46233
#include<cstdio>
#include<queue>
#include<cstring>
#define M 363000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//factorΪǰ8�����Ľ׳� 0~8 0�Ľ׳�0!=1
int factor[9]={1,1,2,6,24,120,720,5040,40320},vis[M],st,ed;
char opt[4]={'u','d','l','r'};
struct State{
    int pos,dir,order;
    char str[10];
}pre[M];

int cantor(char *a){
    int order=0,sum;
    for(int i=0;i<9;i++){
    	sum=0;
    	//����[i+1,8]�б�a[i]С��Ԫ�صĸ���
    	for(int j=i+1;j<9;j++){
    		if(a[i]>a[j])
    			sum++;
		}
		//��ôʵ�ʱ�a[i]С��Ԫ�صĸ������Է���a[i]��λ��,��[i+1,8]�е�����������,����Ϊ(9-i-1)!,�����������Ǳȵ�ǰ�����ַ���aҪС��
		//sumΪ��a[i]С��������a[i]��λ��, factor[9-i-1]Ϊ[i+1,8]�е�����ȫ���и��� (9-i-1)! �׳�
		order+=sum*factor[9-i-1];
	}
	//���н���ۼ����,��ô�ȵ�ǰ�����ַ���aС�����и���Ϊorder,��Ϊ�����Ǵ�0��ʼ��,��ô��ǰ���еõ��������order.
    return order;
}

void print(int i){
    if(pre[i].order == st){
    	printf("%c",opt[pre[i].dir]);
        return;
	}
    print(pre[i].order);
    printf("%c",opt[pre[i].dir]);
}

int bfs(State s){
	queue<State> Q;
    vis[s.order]=1;
    Q.push(s);
    int tx,ty,nx,ny,tpos,order;
    State tp,next;
    while(!Q.empty()){
        tp=Q.front();
        //'x'��'9'���� 123456789�Ŀ���չ���Ĵ�����0
        //���'x'��'0'������ 123456780�Ŀ���չ�������� 46233
        if(tp.order == ed)
            return 1;
        Q.pop();
        tx=tp.pos/3;
        ty=tp.pos%3;
        for(int i=0;i<4;i++){
            nx=tx+dir[i][0];
            ny=ty+dir[i][1];
            if(nx<0 || nx>=3 || ny<0 || ny>=3)
                continue;
            tpos=nx*3+ny;
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='0';
            order=cantor(next.str);
            if(!vis[order]){
            	vis[order]=1;
                next.pos=tpos;
                next.order=order;
                pre[order]=tp;
                //ע�������ΪҪ���������ʽ,��Ϊʵ�ʲ�û�м�¼ Ŀ��״̬��State,���ÿһ���Ĳ�����¼���� ǰһ״̬tp���� ��� pre[order].dir=i���ܽ����в����������
                //���򵽴�Ŀ��״̬�Ĳ����޷����
                pre[order].dir=i;
                Q.push(next);
            }
        }
    }
    return 0;
}

int main(){
    State s;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<9;i++){
        scanf(" %c",&s.str[i]);
        if(s.str[i] == 'x'){
            s.str[i]='0';
            s.pos=i;
        }
    }
    st=s.order=cantor(s.str);
    ed=cantor("123456780");//123456780�Ĵ���Ϊ46233
    if(bfs(s))
    	print(ed);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//��д����ʵ��
//ac 125ms dir[4][2]������������̬ģ��'x'('0')�������������ƶ�
//����չ�������д������� ��'0'����'x' 123456780�Ĵ���Ϊ46233
#include<cstdio>
#include<cstring>
#define M 363000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//factorΪǰ8�����Ľ׳� 0~8 0�Ľ׳�0!=1
int factor[9]={1,1,2,6,24,120,720,5040,40320},vis[M],ed;
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir,order;
    char str[10];
}Q[M];

int cantor(char *a){
    int order=0,sum;
    for(int i=0;i<9;i++){
    	sum=0;
    	//����[i+1,8]�б�a[i]С��Ԫ�صĸ���
    	for(int j=i+1;j<9;j++){
    		if(a[i]>a[j])
    			sum++;
		}
		//��ôʵ�ʱ�a[i]С��Ԫ�صĸ������Է���a[i]��λ��,��[i+1,8]�е�����������,����Ϊ(9-i-1)!,�����������Ǳȵ�ǰ�����ַ���aҪС��
		//sumΪ��a[i]С��������a[i]��λ��, factor[9-i-1]Ϊ[i+1,8]�е�����ȫ���и��� (9-i-1)! �׳�
		order+=sum*factor[9-i-1];
	}
	//���н���ۼ����,��ô�ȵ�ǰ�����ַ���aС�����и���Ϊorder,��Ϊ�����Ǵ�0��ʼ��,��ô��ǰ���еõ��������order.
    return order;
}

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    int head=0,tail=0;
    vis[st.order]=1;
    Q[tail++]=st;
    int tx,ty,nx,ny,tpos,order;
    State tp,next;
    while(head<tail){
        tp=Q[head++];
        //'x'��'9'���� 123456789�Ŀ���չ���Ĵ�����0
        //���'x'��'0'������ 123456780�Ŀ���չ�������� 46233
        if(tp.order == ed)
            return head-1;
        tx=tp.pos/3;
        ty=tp.pos%3;
        for(int i=0;i<4;i++){
            nx=tx+dir[i][0];
            ny=ty+dir[i][1];
            if(nx<0 || nx>=3 || ny<0 || ny>=3)
                continue;
            tpos=nx*3+ny;
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='0';
            order=cantor(next.str);
            if(!vis[order]){
            	vis[order]=1;
                next.pos=tpos;
                next.pre=head-1;
                next.dir=i;
                next.order=order;
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='0';
            st.pos=i;
        }
    }
    st.pre=-1;
    st.order=cantor(st.str);
    ed=cantor("123456780");//123456780�Ĵ���Ϊ46233
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//ac 94ms hash����ַ������ Eric �μ��е����� ��dir[9][4]�����ʾ0������ �ĸ������λ���ڶ�Ӧ��������str�е�λ���±�
//��'9'����'x'
#include<cstdio>
#include<cstring>
#define M 363000//362880 9������ȫ���������9!=362880��
#define HS 1000003
using namespace std;

//dir[pos][0/1/2/3] ��ʾ�������е�'x'('0')�������Ӧ���д�str�����posλ��ʱ,
//������Ӧ3*3����������(0)��(1)��(2)��(3)λ����str�����е�λ�������±�
//dir[pos][i]=-1ʱ,˵��'x'('0')i�����λ���ǲ��Ϸ��� ������0~2������±귶Χ
int dir[9][4]={-1,3,-1,1,
                -1,4,0,2,
                -1,5,1,-1,
                0,6,-1,4,
                1,7,3,5,
                2,8,4,-1,
                3,-1,-1,7,
                4,-1,6,8,
                5,-1,7,-1};
int cnt,head[HS];//�ڽӱ��ͷ ΪHash���С,����Ϊ����,�����ܴ�
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir,val;
    char str[10];
}Q[M];//�����д�ŵ�״̬������������ 0~8 ��9����ȫ���еĸ���

struct HashTable{
    int val,next;
}edge[M];//�������ӷ����ڽӱ����鳤�� Ҳ��0~8 ��9����ȫ���еĸ���

int Hash(char *a){
    int s=0;
    for(int i=0;i<9;i++)
        s=s*10+a[i]-'0';
    return s;
}

int tryInsert(int s){
    int hval=s%HS;
    for(int i=head[hval];i!=-1;i=edge[i].next){
        if(edge[i].val == s)
            return 0;
    }
    edge[cnt]=(HashTable){s,head[hval]};
    head[hval]=cnt++;
    return 1;
}

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    int head=0,tail=0;
    Q[tail++]=st;
    State tp,next;
    int tpos,s;
    while(head<tail){
        tp=Q[head++];
        if(tp.val == 123456789)
            return head-1;
        for(int i=0;i<4;i++){
            tpos=dir[tp.pos][i];
            if(tpos == -1)//˵����ǰλ�ó����� 3x3����߽�
                continue;
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='9';
            s=Hash(next.str);//hash�����str���ж�Ӧ��10������ֵ
            if(tryInsert(s)){
                next.pos=tpos;
                next.val=s;
                next.pre=head-1;
                next.dir=i;
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='9';
            st.pos=i;
        }
    }
    st.pre=-1;
    st.val=Hash(st.str);
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//ac 0ms A*���� ����ʽ���� stl���ȶ���ʵ��
//ժ������
#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>
#include<math.h>
using namespace std;
int c[4][2]= {0,1,1,0,-1,0,0,-1};
char D[4]= {'r','d','u','l'};
int book[3700000];
int C[9]= {1,1,2,6,24,120,720,5040,40320};

struct node
{
    int pos;
    int step;
    int state[10];
    int HMD;
    int cantor;
    bool operator < (const node h)const
    {
        return step+HMD>h.step+h.HMD;
    }
};

struct yun
{
    int Node;
    int dis;
} path[3700000];

int is_solve(int a[])
{
    int i,j,ans=0;
    for(i=0; i<8; i++)
        for(j=i+1; j<9; j++)
        {
            if(a[i]==9||a[j]==9)continue;
            if(a[j]<a[i])
                ans++;
        }

    if(ans&1)
        return 1;
    else
        return 0;
}

int hmd(int ma[])
{
    int ans=0,i;
    for(i=0; i<9; i++)
    {
        if(ma[i]==9)
            continue;
        ans+=fabs((ma[i]-1)/3-i/3)+fabs((ma[i]-1)%3-i%3);
    }
    return ans;
}

int Cantor(int a[])
{
    int i,j,l,ans=0;
    for(i=0; i<8; i++)
    {
        l=0;
        for(j=i+1; j<9; j++)
            if(a[j]<a[i])
                l++;
        ans+=C[8-i]*l;
    }
    return ans;
}

void A_star(int pos,int a[])
{
    int i;
    priority_queue<node> Q;
    node st,en;
    for(i=0; i<9; i++)
        st.state[i]=a[i];
    st.pos=pos;
    st.HMD=hmd(st.state);
    st.cantor=Cantor(st.state);
    st.step=0;
    Q.push(st);
    while(Q.size())
    {
        st=Q.top();
        Q.pop();//printf("Cantor: %d  Step: %d  Pos: %d\n",st.cantor,st.step,st.pos);
        if(st.cantor==0)
        {
            int k=0;
            int p[10000];
            for(i=1; i<=st.step; i++)
            {
                p[i]=path[k].dis;
                k=path[k].Node;
            }
            for(i=st.step;i>=1;i--)
                printf("%c",D[p[i]]);
            printf("\n");
            return ;
        }
        int x=st.pos/3;
        int y=st.pos%3;
        for(i=0; i<4; i++)
        {
            int dx=x+c[i][0];
            int dy=y+c[i][1];
            int dz=dx*3+dy;
            if(dx<0||dy<0||dx>2||dy>2)
                continue;

            for(int j=0; j<9; j++)
                en.state[j]=st.state[j];
            swap(en.state[dz],en.state[st.pos]);
         //   printf("%d \n",dz);
            int kk=Cantor(en.state);
         //   printf("KK %d KK\n",kk);
            if(book[kk])
                continue;
         //   printf("%d****\n",i);
            book[kk]=1;
            en.cantor=kk;
            en.pos=dz;

            en.step=st.step+1;
         //   printf("%d**>>\n");
            en.HMD=hmd(en.state);
            path[kk].dis=i;
            path[kk].Node=st.cantor;

            Q.push(en);
        }
    }
}

int main()
{
    char str[100];
    gets(str);
    int puzzle[10],pos;
    int k=0,i;
    for(i=0; i<strlen(str); i++)
    {
        if(str[i]!=' ')
        {
            if(str[i]=='x')
            {
                puzzle[k++]=9;
                pos=k-1;
            }
            else
                puzzle[k++]=str[i]-'0';
        }
    }
    int is=is_solve(puzzle);
    if(is)
        printf("unsolvable\n");
    else
        A_star(pos,puzzle);
}
*/
