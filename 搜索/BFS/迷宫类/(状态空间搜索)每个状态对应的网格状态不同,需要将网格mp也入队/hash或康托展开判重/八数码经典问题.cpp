/*
��������������:
��3��3������,���а˸�����,ÿ�������ϱ���1��8��ĳһ����,
��ͬ�����ϱ�����ֲ���ͬ.�����ϻ���һ���ո�'x',��ո�����
�����ӿ��ԺͿո񽻻�λ��.���̵�״̬��ʾΪ��(0,0)��(2,2)��������,
���϶����γɵ����д�,Ҫ������������:����һ����ʼ״̬��һ��
Ŀ��״̬,�����ʼ״̬ת���Ŀ��״̬�������ƶ������ٲ���.

���� ������ һ��hash���� һ�ֿ���չ������ ��������ǿ���չ������
hash���زο�POJ 1077
*/
//stl queue����ʵ�� (State)pre�����¼��ǰ���е���һ״̬tp(State)
//dir[4][2]������������̬ģ��'x'('0')�������������ƶ�
//����չ�������д������� ��'0'����'x' +������ ��ż���ʼ�֦�ж� �޽�����
#include<cstdio>
#include<queue>
#include<cstring>
#define M 363000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//factorΪǰ8�����Ľ׳� 0~8 0�Ľ׳�0!=1
int factor[9]={1,1,2,6,24,120,720,5040,40320},vis[M],st,ed;
struct State{
    int pos,order,s;
    char str[10];
};

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
            break;
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
                next.s=tp.s+1;
                Q.push(next);
            }
        }
    }
    return tp.s;
}

int cal(char *a){
	int sum=0;
    //ֱ�Ӹ��ݳ�ʼ״̬��Ŀ��״̬��������ż���Ƿ���ͬ�ж��Ƿ�ɴ�
    //ע�������������������ո�λ'x',ʵ��ֻ��8����,����ʵ ��ʹ��'x'����'0'��'9'ԭ�������е� ��ż�����Ƿ���ͬҲ�ǲ�Ӱ���
    for(int i=0;i<9;i++){
        if(a[i] == '0')//�ո�λ' '����
            continue;
        for(int j=i+1;j<9;j++){
            if(a[j]!='0' && a[j]<a[i])//a[j]!='0' �ո�λ' '����
                sum++;
        }
    }
    return sum;
}

int main(){
    State s;
    char t[10];
    int ron1,ron2,flag1=0,flag2=0;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<9;i++){
        scanf(" %c",&s.str[i]);
        if(s.str[i] == 'x'){
            s.str[i]='0';
            s.pos=i;
        }
    }
    for(int i=0;i<9;i++){
        scanf(" %c",&t[i]);
        if(t[i] == 'x')
            t[i]='0';
    }
    //ronΪ������-"reverse order number"
    ron1=cal(s.str);
    ron2=cal(t);
    if(ron1%2)
    	flag1=1;
    if(ron2%2)
    	flag2=1;
    if(flag1 ^ flag2){
    	printf("unsolvable");//��ʼ̬��Ŀ��̬ ���ɴ� �������޽�
    	return 0;
	}
    st=s.order=cantor(s.str);
    s.s=0;
    ed=cantor(t);//edΪĿ��״̬�Ĵ���
    //��ʼ̬��Ŀ��̬��������ż������ͬһ���ǿɴ��,��������� unsolvable�޽�
    printf("%d",bfs(s));//������ �ӳ�ʼ״̬st��Ŀ��״̬ed������Ҫ�ƶ��Ĳ�������
    return 0;
}
/*
�������ݰ���
input
23415x768
12345678x
output
19

input
12345678x
12345678x
output
0

input
2831647x5
123784x65
output
5

input
2831x4765
1238x4765
output
4

input
87152634x ������ 18 ż��
87162534x ������ 19 ���� ��ż���ʲ�ͬ�޷�ת��
output
unsolvable

input
12345678x ������ 0 ż��
61234578x ������ 5 ���� ��ż���ʲ�ͬ�޷�ת��
output
unsolvable

*/
