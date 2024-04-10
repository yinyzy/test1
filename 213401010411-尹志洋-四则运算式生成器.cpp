#include"stdio.h"
#include"stdlib.h"
#include"iostream"
#include"time.h"
#include"string.h"
using namespace std;
#define K 32767
//#define N 50
//#define M 0
#define NUM 10
#define MAX 1000
#define MIN -1000
template<class T>
struct Stack {
	T* top;
	T* base;
};
template<class T>
void instack(Stack<T>* P)
{
	P->base = new T[20];
	P->top = P->base;
}
template<class T>
void Push(Stack<T>* P, T c1)
{
	*P->top = c1;
	P->top++;
}
template<class T>
void Pop(Stack<T>* P)
{
	if (P->top == P->base)
	{
		cout << "ERROR1";
		return;
	}
	P->top--;
}
template<class T>
bool pan(Stack<T>* P)
{
	if (P->top == P->base)
		return true;
	return false;
}
template<class T>
T  Gettop(Stack<T>* P)
{
	return *(P->top - 1);
}
int fun11(char ch)//给运算符赋值为fun1服务
{
	if (ch == '+') { return 0; }
	if (ch == '-') { return 1; }
	if (ch == '*') { return 2; }
	if (ch == '/') { return 3; }
	if (ch == '(') { return 4; }
	if (ch == ')') { return 5; }
	if (ch == '#') { return 6; }
	cout << "输入算式不规范";
	return 7;
}
int fun1(char c1, char c2)//比较两个运算符的优先级
{
	int T[7][7] = { 1,1,-1,-1,-1,1,1,
				   1,1,-1,-1,-1,1,1,
				   1,1,1,1,-1,1,1,
				   1,1,1,1,-1,1,1,
				   -1,-1,-1,-1,-1,0,K,
				   K,K,K,K,K,K,K,
				   -1,-1,-1,-1,-1,-1,0 };
	return T[fun11(c1)][fun11(c2)];

}
float fun21(Stack<float>* P, char ch)
{
	float temp;
	switch (fun11(ch))
	{
	case 0:temp = *(P->top - 2) + *(P->top - 1); break;
	case 1:temp = *(P->top - 2) - *(P->top - 1); break;
	case 2:temp = *(P->top - 2) * *(P->top - 1); break;
	case 3:temp = *(P->top - 2) / *(P->top - 1); break;
	}
	return temp;
}
float fun2(char ch[])
{
	int i = 0;
	Stack<float>* P;
	Stack<char>* T;
	P = new Stack<float>;
	T = new Stack<char>;
	instack(T);
	instack(P);
	Push(T, '#');
	int pt = 0;//用于判断运算符之前是否还有未入栈的数
	float temp;
	float num = 0;
	while (ch[i] != '\0')
	{

		if (ch[i] == '*' || ch[i] == '/' || ch[i] == '+' || ch[i] == '-' || ch[i] == '#' || ch[i] == '(' || ch[i] == ')')
		{
			if (pt != 0)
			{
				Push(P, num);
				pt = 0;
				num = 0;
			}
			switch (fun1(Gettop(T), ch[i]))
			{
			case -1:Push(T, ch[i]); break;
			case 0:Pop(T);  break;
			case 1:temp = fun21(P, *(T->top - 1)); Pop(T); Pop(P); Pop(P); Push(P, temp); continue;
			default:
				cout << "ERROR2";
			}
		}
		else
		{
			pt = 1;
			num = num * 10 + ch[i] - '0';
			//cout << "#1";
		}
		i++;
	}
	return Gettop(P);
}


char* p[NUM];//算式个数
int SCORE[100], Sint;//历史分数
float key[NUM];
class math {
public:
	char* T1(int N, int M);//一个数
	char* T2(int N);//两个数
	char* T3(int N);//三个数
	char* T4(int N, int M);//N(+-)
	char* T5(int N, int M);//N(*)
	char* T6();//81(/)
	char* T7(int N, int M);//N(/)
	char* T8(int N, int M);//3X2(*)
	char* T9(int N, int M);//3x2(/)
	char* T11(int N, int M);
};
void setA(math T);
void setB(math T);
void setC(math T);
void setD(math T);
void setE(math T);
void setF(math T);
void T61(int n, int k[], int& a)
{
	int j = 0;
	for (int i = 1; i <= n; i++)
	{
		if (n % i == 0)
		{
			k[j++] = i;
			if (i != 1 && i != n)
			{
				k[j++] = i;
				k[j++] = i;
				k[j++] = i;
				k[j++] = i;
				k[j++] = i;
			}
		}
	}
	a = j;
}
char* ibc(int n)//数字转成字符串
{
	int num = n, j = 1;
	char* ch;
	ch = new char[30];
	while (num >= 10)
	{
		num = num / 10;
		j++;
	}
	int i = j;
	num = n;
	while (j != 0)
	{
		ch[j - 1] = num % 10 + '0';
		num = num / 10;
		j--;
	}
	ch[i] = '\0';
	return ch;
}
char icc(int ch)//选择运算符号
{
	if (ch == 0) { return '+'; }
	if (ch == 1) { return '-'; }
	if (ch == 2) { return '*'; }
	if (ch == 3) { return '/'; }
	cout << "算式不规范";
	return 7;
}
void Strcat(char* p, char* q)//字符串连接
{
	int n = strlen(p);
	int i = n, j = 0;
	while (*(q + j) != '\0')
	{
		*(p + i) = *(q + j);
		i++;
		j++;
	}
	*(p + i) = '\0';
}
void Strcat(char* p, char q)
{
	int n = strlen(p);
	p[n] = q;
	p[n + 1] = '\0';
}
bool sushu(int n)
{
	if (n <= 1)
	{
		return true;
	}
	else
	{
		for (int i = 2; i < n; i++)
		{
			if (n % i == 0)
				return false;
		}
	}
	return true;
}
void setint(int& n, int N, int M)
{
	n = M + rand() % (N - M);
	while (sushu(n))
	{
		n = M + rand() % (N - M);
	}
}
void Print()
{
	for (int i = 0; i < NUM; i++)
	{
		cout << "(" << i + 1 << ") ";
		key[i] = fun2(p[i]);
		for (int j = 0; j < strlen(p[i]); j++)
		{
			switch (p[i][j])
			{
			case '#':break;
			case '*':cout << "x"; break;
			case '/':cout << "÷"; break;
			default:cout << p[i][j]; break;
			}
		}
		cout << endl;
	}
}
void history(int& n, int a[])
{
	char ch[100], str[20];
	int N = 0, i = 0;
	FILE* fp;
	if ((fp = fopen("file1", "r")) == NULL)
	{
		//cout<<"文件不存在";
	}
	else
	{
		fgets(ch, 99, fp);
		while (ch[i] != '\0')
		{
			if (ch[i] != '#')
			{
				SCORE[N] = SCORE[N] * 10 + ch[i] - '0';
				i++;
				continue;
			}
			i++;
			N++;
		}
		n = N;
		//cout<<ch;
		fclose(fp);
	}
}
void score()
{
	float n[NUM];
	int sum = 0, a = 100 / NUM;
	for (int i = 0; i < NUM; i++)
	{
		cout << "请输入第" << i + 1 << "题答案:";
		cin >> n[i];
		if (n[i] == key[i])
		{
			sum = sum + a;
		}
	}
	cout << endl << "考试结束，您的最终得分：" << sum << endl;
	cout << "上次成绩:" << SCORE[Sint - 1] << endl;
	if (sum > SCORE[Sint - 1])
	{
		cout << "恭喜您,进步了";
	}
	else if (sum < SCORE[Sint - 1])
	{
		cout << "很遗憾，退步了";
	}
	else
	{
		cout << "保持住了";
	}
	FILE* fp = fopen("file1", "a");
	char* ch;
	ch = ibc(sum);
	if (fp == NULL)
	{
		fp = fopen("file1", "w");
		Strcat(ch, '#');
		fputs(ch, fp);
	}
	else
	{
		Strcat(ch, '#');
		fputs(ch, fp);
	}
	fclose(fp);

}
void MAIN(math T)
{

	char option1;
	char option2;
	history(Sint, SCORE);
	cout << "                           小学生计算考试" << endl;
	cout << "1,进入考试" << endl << "2,查看历史成绩" << endl << "其他任意键退出系统" << endl << "请选择要进行的操作：";
	option1 = getchar();
	if (option1 == '1')
	{
		cout << endl << "A.一年级" << endl << "B.二年级" << endl << "C.三年级" << endl << "D.四年级-六年级" /* << endl << "E.五年级"*/ << endl << "请选择学生计算考试年级：";
		cin >> option2;
		int t = 0;
		while (t == 0)
		{
			t = 1;
			switch (option2)
			{
			case 'a':
			case 'A':setA(T); break;
			case 'b':
			case 'B':setB(T); break;
			case 'c':
			case 'C':setC(T); break;
			case 'd':
			case 'D':setD(T); break;
				/*case 'e':
				case 'E':setE(T);break;*/
			default:t = 0; cout << "输入年级有误，请重新选择："; cin >> option2; break;
			}
		}
		cout << endl << endl << "*******************************开始考试***************************" << endl << "请依次输入答案,按下Enter" << endl << "注:输入非数字会结束程序" << endl;
		Print();
		cout << endl << "答：";
		score();

	}
	else if (option1 == '2')
	{
		for (int i = 0; i < Sint; i++)
		{
			printf("第%d次成绩:", i + 1);
			cout << SCORE[i] << endl;
		}
	}
	else
	{
		exit(0);
	}
}
char* math::T1(int N, int M)
{
	int n1;
	char* str;
	str = new char[50];
	str[0] = '\0';
	n1 = M + rand() % N;
	Strcat(str, ibc(n1));
	return str;

}
char* math::T2(int N)
{
	int n1, n2, x1;
	char* str;
	str = new char[50];
	str[0] = '\0';
	n1 = rand() % N;
	n2 = rand() % N;
	x1 = rand() % 4;
	if (x1 == 2 && n2 == 0)
	{
		n2 = rand() % +1;
	}
	Strcat(str, ibc(n1));
	Strcat(str, icc(x1));
	Strcat(str, ibc(n2));
	return str;
}
char* math::T3(int N)
{
	int n1, n2, n3, x1, x2;
	char* str;
	str = new char[50];
	str[0] = '\0';
	n1 = rand() % N;
	n2 = rand() % N;
	n3 = rand() % N;
	x1 = rand() % 4;
	if (x1 == 2 && n2 == 0)
	{
		n2 = 1 + rand() % N;
	}
	x2 = rand() % 4;
	if (x2 == 2 && n3 == 0)
	{
		n3 = 1 + rand() % N;
	}
	Strcat(str, ibc(n1));
	Strcat(str, icc(x1));
	Strcat(str, ibc(n2));
	Strcat(str, icc(x2));
	Strcat(str, ibc(n3));
	return str;
}
char* math::T4(int N, int M)
{
	int n1, x1, n2;
	char* str;
	str = new char[50];
	str[0] = '\0';
	x1 = rand() % 2;
	if (x1 == 0)
	{
		n1 = M + rand() % N;
		n2 = M + rand() % (N - n1);
	}
	if (x1 == 1)
	{
		n1 = M + 1 + rand() % (N - 1);
		n2 = rand() % n1;
	}
	Strcat(str, ibc(n1));
	Strcat(str, icc(x1));
	Strcat(str, ibc(n2));
	return str;

}
char* math::T5(int N, int M)
{
	int n1, x1, n2;
	char* str;
	str = new char[50];
	str[0] = '\0';
	x1 = 2;
	n1 = M + 1 + rand() % N;
	n2 = M + 1 + rand() % N;
	Strcat(str, ibc(n1));
	Strcat(str, icc(x1));
	Strcat(str, ibc(n2));
	return str;

}
char* math::T6()
{
	int k1[20] = { 6,5,7,4,4,6,6,4,6,6,3,8,8,8,8,8,9,9,8,9 };
	int n1, x1, n2, k[100], n;
	char* str;
	str = new char[50];
	str[0] = '\0';
	x1 = 3;
	n1 = k1[rand() % 20];
	T61(n1, k, n);
	n2 = k[rand() % n];
	Strcat(str, ibc(n1));
	Strcat(str, icc(x1));
	Strcat(str, ibc(n2));
	return str;

}
char* math::T7(int N, int M)
{
	int n1, x1, n2, n;
	int k[1000];//除数合集
	char* str;
	str = new char[50];
	str[0] = '\0';
	x1 = 3;
	setint(n1, N, M);
	T61(n1, k, n);
	n2 = k[rand() % n];
	Strcat(str, ibc(n1));
	Strcat(str, icc(x1));
	Strcat(str, ibc(n2));
	char pt[50];
	int w = strlen(str);
	for (int i = 0; i < w; i++)
	{
		pt[i] = str[i];
	}
	pt[w] = '#';
	pt[w + 1] = '\0';
	if (fun2(pt) == n1)
	{
		str = T7(N, M);
	}
	return str;

}
char* math::T8(int N, int M)//3X2
{
	int a1, a2, a3, b1, b2, x1, x2, xy, y1;
	char* str;
	str = new char[50];
	str[0] = '\0';
	a1 = M + rand() % N;
	a2 = M + rand() % N;
	a3 = M + rand() % N;
	b1 = M + rand() % N;
	b2 = M + rand() % N;
	x1 = rand() % 3;
	x2 = rand() % 3;
	y1 = rand() % 3;
	xy = rand() % 3;
	if (x1 < 2 && x2 < 2 && y1 < 2)
	{
		xy = 2;
	}
	Strcat(str, '(');
	Strcat(str, ibc(a1));
	Strcat(str, icc(x1));
	Strcat(str, ibc(a2));
	Strcat(str, icc(x2));
	Strcat(str, ibc(a3));
	Strcat(str, ')');
	Strcat(str, icc(xy));
	Strcat(str, '(');
	Strcat(str, ibc(b1));
	Strcat(str, icc(y1));
	Strcat(str, ibc(b2));
	Strcat(str, ')');
	char pt[50];
	int n = strlen(str);
	for (int i = 0; i < n; i++)
	{
		pt[i] = str[i];
	}
	pt[n] = '#';
	pt[n + 1] = '\0';
	if (fun2(pt) >= MAX || fun2(pt) <= MIN)
	{
		str = T8(N, M);
	}

	return str;
}
char* math::T9(int N, int M)
{
	int a1, a2, a3, b1, b2, x1, x2, xy, y1;
	char* str;
	str = new char[50];
	str[0] = '\0';
	x1 = rand() % 3;
	xy = rand() % 2;
	if (x1 < 2)
	{
		a1 = M + rand() % N;
		Strcat(str, '(');
		Strcat(str, ibc(a1));
		Strcat(str, icc(x1));
		Strcat(str, T7(N, M));
		Strcat(str, ')');
		Strcat(str, icc(xy));
		Strcat(str, '(');
		Strcat(str, T7(N, M));
		Strcat(str, ')');

	}
	else
	{
		x2 = rand() % 2;
		a3 = M + rand() % N;
		Strcat(str, '(');
		Strcat(str, T7(N, M));
		Strcat(str, icc(x2));
		Strcat(str, ibc(a3));
		Strcat(str, ')');
		Strcat(str, icc(xy));
		Strcat(str, '(');
		Strcat(str, T7(N, M));
		Strcat(str, ')');

	}
	return str;
}
char* math::T11(int N, int M)
{
	int n[2], xy, t = 0;
	char* str;
	str = new char[50];
	str[0] = '\0';
	n[0] = rand() % 2;
	n[1] = rand() % 2;
	if (n[0] == 0 && n[1] == 0)
	{
		n[1]++;
	}
	xy = rand() % 2;
	for (int i = 0; i < 2; i++)
	{
		switch (n[i])
		{
		case 0:Strcat(str, T1(N, M)); break;
		case 1:Strcat(str, '('); Strcat(str, T4(N, M)); Strcat(str, ')'); break;
		}
		if (t == 0)
		{
			Strcat(str, icc(xy)); t++;
		}

	}
	return str;

}
void setA(math T)
{
	int n;
	for (int i = 0; i < 10; i++)
	{
		p[i] = T.T4(20, 0);
		n = strlen(p[i]);
		p[i][n] = '#';
		p[i][n + 1] = '\0';

	}
}
void setB(math T)
{
	int n, m;
	for (int i = 0; i < 10; i++)
	{
		m = rand() % 10;
		switch (m)
		{
		case 0:p[i] = T.T4(100, 30); break;
		case 1:
		case 2:
		case 3:p[i] = T.T6(); break;
		case 4:
		case 5:
		case 6:p[i] = T.T5(9, 0); break;
		case 7:
		case 8:
		case 9:p[i] = T.T11(50, 20); break;
		}
		n = strlen(p[i]);
		p[i][n] = '#';
		p[i][n + 1] = '\0';

	}
}
void setC(math T)
{
	int n, m;
	for (int i = 0; i < 10; i++)
	{
		m = rand() % 3;
		switch (m)
		{
		case 0:p[i] = T.T7(200, 30); break;
		case 1:p[i] = T.T5(100, 10); break;
		case 2:p[i] = T.T11(500, 80); break;
		}
		n = strlen(p[i]);
		p[i][n] = '#';
		p[i][n + 1] = '\0';

	}
}
void setD(math T)
{
	int n, m;
	for (int i = 0; i < 10; i++)
	{
		m = rand() % 2;
		switch (m)
		{
		case 0:p[i] = T.T8(100, 10); break;
		case 1:p[i] = T.T9(400, 100); break;
		case 2:p[i] = T.T7(500, 300);
		case 3:p[i] = T.T5(200, 100);

		}
		n = strlen(p[i]);
		p[i][n] = '#';
		p[i][n + 1] = '\0';

	}
}
int main()
{
	math T;
	srand(time(0));
	MAIN(T);//命题
	getchar(); getchar();
}