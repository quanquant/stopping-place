#include<iostream>
using namespace std;
const int N=2;             //ͣ����ջ�ĳ���
const int M=1;             //��λʱ����ͣ�����շ�ֵ
#define OK 1
#define ERROR 0   
typedef struct
{
	int num;            //�������
	int arrtime;        //������뿪ʱ��
}elemtype;
typedef elemtype ElemType; 
struct SqStack
{
	elemtype stack[N+1];
	int top;
	int base;
}s1,s2;
 struct QNode
{
	elemtype data;
	QNode *next;
};
struct LinkQueue
{
	QNode *front;
	QNode *rear;
}Q;
SqStack IniStack(SqStack S)       //ջ�ĳ�ʼ��
{
	S.top=S.base;
	return S;
 }
SqStack Push(SqStack S,ElemType e)   //��ջ
{
	S.top++;
	S.stack[S.top]=e;
	return S; 
}
SqStack Pop(SqStack S)         //��ջ
{
	S.top--;
	return S;
 }
ElemType GetTop(SqStack S)      //ȡջ��Ԫ��
{
	return S.stack[S.top];
}
int empty1(SqStack S)              //��ջ��
{
	if(S.top==S.base)
		return OK;
	else return ERROR;
}
LinkQueue IniQueue(LinkQueue Q)     //���г�ʼ��
{
	QNode *p;
	p=new QNode;
	p->next=NULL;
	Q.front=Q.rear=p;
	return Q;
}
LinkQueue EnQueue(LinkQueue Q,elemtype e)     //���
{
	QNode *p;
	p=new QNode;
	p->data=e;
	p->next=Q.rear->next;
	Q.rear->next=p;
	Q.rear=p;
	return Q;
}
LinkQueue DeQueue(LinkQueue Q)             //����
{
	QNode *p=Q.front;
	Q.front=p->next;
	delete p;
	return Q;
}
elemtype GetHead(LinkQueue s)            //ȡ��ͷԪ��
{
	return s.front->next->data;
}
int empty2(LinkQueue s)                 
{
	if (s.front==s.rear)return OK;
	else return ERROR;
}         
void arrive(elemtype e)    //����ͣ����
{
	if(s1.top==N)
		Q=EnQueue(Q,e);   
	else s1=Push(s1,e);   
}       
void delive(elemtype e)    //�����뿪������
{
	int f=1;
	elemtype y;
	QNode *r;	
	while((!empty1(s1))&&(f==1))   //��ͣ��������Ҫ�뿪�ĳ���
		{
			if (s1.stack[s1.top].num!=e.num)  //�ж�ջ���Ƿ�Ϊ��Ӧ����
		{
			y=GetTop(s1);
			s1=Pop(s1);
			s2=Push(s2,y);     //�����ڶ�Ӧ����߽��ĳ� ����s2ջ
		}
		else                   //ͣ�������ҵ���Ӧ����
		 {
		 	f=0;
			y=GetTop(s1);      //ջ����Ϊ��Ӧ����
			s1=Pop(s1);
			cout<<"				   ͣ�������б��Ϊ"<<e.num<<"��"<<endl;
			cout<<"				   �ó����뿪,Ӧ��ͣ����:"<<(e.arrtime-y.arrtime)*M<<"Ԫ"<<endl<<endl;
			while(!empty1(s2))      //��ʱջs2�е�Ԫ�ؽ���s1
			{
				y=GetTop(s2);
				s2=Pop(s2);
				s1=Push(s1,y);
			}   	   
			if(!empty2(Q))    //ͣ�������뿪һ������,����ϵ�һ��������ͣ����
			{
				y=GetHead(Q);      //ȡ��ͷԪ��
				Q=DeQueue(Q);      //����
				s1=Push(s1,y);     //��ջ
			}
		 }
	   }
		if(empty1(s1))          //ͣ�������޸����ĳ���,�򵽱������
		{
			while(!empty1(s2))  
			{
				y=GetTop(s2);
				s2=Pop(s2);
				s1=Push(s1,y);
			}
			if(!empty2(Q))
			{
				QNode *p=Q.front;
				while((p!=NULL)&&(p->data.num!=e.num))
				{
					r=p;
					p=p->next;
				}
				if(p!=NULL)
				{
					cout<<"				   ������б��Ϊ"<<e.num<<"�ĳ���"<<endl;
					cout<<"				     �ó����뿪,Ӧ��ͣ����0.00Ԫ:"<<endl<<endl;
					r->next=p->next;
					delete p;
				} 
				  else cout<<"				   ������������!!!"<<endl<<"					������ĳ���������!!!"<<endl<<endl;
		     }
		  }					
}
void pr1()      //���ͣ�����еĳ�����ź͵���ʱ��
{
	int t=s1.top;
	while(t!=0)
	{
	
		cout<<"				   ͣ���������еĳ������:"<<s1.stack[t].num<<" ����ʱ��:"<<s1.stack[t].arrtime<<endl;
		t--;
	}
	cout<<endl;
}
void pr2()    //�������еĳ�����ź͵���ʱ��  
{
	QNode *p=Q.front->next;
	while(p!=NULL)
	{
		cout<<"				   ��������еĳ������:"<<p->data.num<<" ����ʱ��:"<<p->data.arrtime<<endl;
		p=p->next;
	}
	cout<<endl;}
void main()
{
	int n;
	elemtype e;
	s1=IniStack(s1);
	s2=IniStack(s2);
	Q=IniQueue(Q);
	cout<<"\t\t\t*****��ӭ����ͣ��������ϵͳ*****"<<endl;
	while(1)
	{
	cout<<endl;
	cout<<"\t\t\t\t�����복�����:";cin>>e.num;
	cout<<"\t\t\t\t����ʱ����뿪ʱ��:";cin>>e.arrtime;
	cout<<"\t\t\t\t�����봦�����Ĵ���(1:���� 2:�뿪 3:����):";cin>>n;
	cout<<endl;
	if(n==1){arrive(e);pr1();pr2();}
	else if (n==2){delive(e);pr1();pr2();}
	else if(n==3)break;
	else cout<<"				   ������������";
	}
	cout<<endl;
}