#include<iostream>
using namespace std;
const int N=2;             //停车场栈的长度
const int M=1;             //单位时间内停车场收费值
#define OK 1
#define ERROR 0   
typedef struct
{
	int num;            //车辆编号
	int arrtime;        //到达和离开时间
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
SqStack IniStack(SqStack S)       //栈的初始化
{
	S.top=S.base;
	return S;
 }
SqStack Push(SqStack S,ElemType e)   //入栈
{
	S.top++;
	S.stack[S.top]=e;
	return S; 
}
SqStack Pop(SqStack S)         //出栈
{
	S.top--;
	return S;
 }
ElemType GetTop(SqStack S)      //取栈顶元素
{
	return S.stack[S.top];
}
int empty1(SqStack S)              //判栈空
{
	if(S.top==S.base)
		return OK;
	else return ERROR;
}
LinkQueue IniQueue(LinkQueue Q)     //队列初始化
{
	QNode *p;
	p=new QNode;
	p->next=NULL;
	Q.front=Q.rear=p;
	return Q;
}
LinkQueue EnQueue(LinkQueue Q,elemtype e)     //入队
{
	QNode *p;
	p=new QNode;
	p->data=e;
	p->next=Q.rear->next;
	Q.rear->next=p;
	Q.rear=p;
	return Q;
}
LinkQueue DeQueue(LinkQueue Q)             //出队
{
	QNode *p=Q.front;
	Q.front=p->next;
	delete p;
	return Q;
}
elemtype GetHead(LinkQueue s)            //取队头元素
{
	return s.front->next->data;
}
int empty2(LinkQueue s)                 
{
	if (s.front==s.rear)return OK;
	else return ERROR;
}         
void arrive(elemtype e)    //进入停车场
{
	if(s1.top==N)
		Q=EnQueue(Q,e);   
	else s1=Push(s1,e);   
}       
void delive(elemtype e)    //车辆离开的情形
{
	int f=1;
	elemtype y;
	QNode *r;	
	while((!empty1(s1))&&(f==1))   //在停车场中找要离开的车辆
		{
			if (s1.stack[s1.top].num!=e.num)  //判断栈顶是否为对应车辆
		{
			y=GetTop(s1);
			s1=Pop(s1);
			s2=Push(s2,y);     //将排在对应车后边进的车 进入s2栈
		}
		else                   //停车场中找到对应车辆
		 {
		 	f=0;
			y=GetTop(s1);      //栈顶即为对应车辆
			s1=Pop(s1);
			cout<<"				   停车场中有编号为"<<e.num<<"车"<<endl;
			cout<<"				   该车将离开,应收停车费:"<<(e.arrtime-y.arrtime)*M<<"元"<<endl<<endl;
			while(!empty1(s2))      //临时栈s2中的元素进入s1
			{
				y=GetTop(s2);
				s2=Pop(s2);
				s1=Push(s1,y);
			}   	   
			if(!empty2(Q))    //停车场中离开一辆车后,便道上第一辆车进入停车场
			{
				y=GetHead(Q);      //取对头元素
				Q=DeQueue(Q);      //出队
				s1=Push(s1,y);     //进栈
			}
		 }
	   }
		if(empty1(s1))          //停车场中无给定的车辆,则到便道上找
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
					cout<<"				   便道上有编号为"<<e.num<<"的车辆"<<endl;
					cout<<"				     该车将离开,应收停车费0.00元:"<<endl<<endl;
					r->next=p->next;
					delete p;
				} 
				  else cout<<"				   您的输入有误!!!"<<endl<<"					您输入的车辆不存在!!!"<<endl<<endl;
		     }
		  }					
}
void pr1()      //输出停车场中的车辆编号和到达时间
{
	int t=s1.top;
	while(t!=0)
	{
	
		cout<<"				   停车场中现有的车辆编号:"<<s1.stack[t].num<<" 到达时间:"<<s1.stack[t].arrtime<<endl;
		t--;
	}
	cout<<endl;
}
void pr2()    //输出便道中的车辆编号和到达时间  
{
	QNode *p=Q.front->next;
	while(p!=NULL)
	{
		cout<<"				   便道中现有的车辆编号:"<<p->data.num<<" 到达时间:"<<p->data.arrtime<<endl;
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
	cout<<"\t\t\t*****欢迎来到停车场管理系统*****"<<endl;
	while(1)
	{
	cout<<endl;
	cout<<"\t\t\t\t请输入车辆编号:";cin>>e.num;
	cout<<"\t\t\t\t到达时间或离开时间:";cin>>e.arrtime;
	cout<<"\t\t\t\t请输入处理车辆的代号(1:到达 2:离开 3:结束):";cin>>n;
	cout<<endl;
	if(n==1){arrive(e);pr1();pr2();}
	else if (n==2){delive(e);pr1();pr2();}
	else if(n==3)break;
	else cout<<"				   您的输入有误！";
	}
	cout<<endl;
}