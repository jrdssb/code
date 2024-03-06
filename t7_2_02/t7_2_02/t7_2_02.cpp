#include<iostream>
using namespace std;

class node
{
public:
	int value=0;			//权重
	node* left;
	node* right;
	bool selected = false;   //判断该节点是否用于建树
	string code="";
	node() {
		value = 0;
		left = NULL;
		right = NULL;
		selected = false;
	}
	node(int e) {
		value = e;
		left = NULL;
		right = NULL;
		selected = false;
	}
	node(int e,node*l,node*r) {
		value = e;
		left = l;
		right = r;
		selected = false;
	}
};

class hufftree
{
public:
	int elementcount = 10;  //有多少种要转成code的单词
	node *root=new node(100);
	int* arr = new int[elementcount];//存放频率
	node* p = new node[30];//存放树节点数组
	int cursize = elementcount;//当前还需要处理树的数量

	void maketree(int* a)
	{
		for (int i = 0; i < 10; i++)		//传入权重
		{
			node*temp = new node(a[i]);
			p[i] = *temp;
		}
		cout << endl;
		while (cursize<30)//小于maxsize
		{
			int index1 = -1;
			int index2 = -1;
			getmin(index1, index2);		//找到目前存在的树中，跟节点权重最小的两个数对应的下标
			merge(&p[index1], &p[index2], p[cursize]); //将这两个树作为左右节点，selected设置为true，保存到数组下一个空位置
			p[index1].selected = true, p[index2].selected = true;
			cursize++;
			if (selectednum() == cursize - 1)		//计算此时数组中所有树被选择的次数，如果只有一个没被选择，说明所有树都被集合到了一起
			{
				*root = p[cursize - 1];
				break;
			}
		}
	}
	void merge(node *left, node *right, node &parent)  //整合函数
	{
		node *temp = new node(left->value + right->value, left, right);
		parent = *temp;
		return;
	}

	void getmin(int& index1, int& index2)		//获得两个最小下标
	{
		int min1 = INT_MAX-1;
		int min2 = INT_MAX;  //先设置两个最小值都为最大
		for (int i = 0; i < cursize; i++)
		{
			if (p[i].selected == true)continue;     //遇到selected==true说明该树已经建过，continue
			if (p[i].value < min1 || p[i].value < min2)			//只要小于其中之一，就把该值赋值给更大的那个
			{
				if (min1 < min2)
				{
					min2 = p[i].value;
					index2 = i;				//获得对应下标值
				}
				else
				{
					min1 = p[i].value;
					index1 = i;
				}	
			}
		}
	}

	int selectednum()		//selected计数函数
	{
		int i = 0;
		int count = 0;
		while (p[i].value != 0)
		{
			if (p[i].selected == true)
			{
				count++;
			}
			i++;
		}
		return count;
	}

	string getcode(node*p,int weight,string s)//获取二进制码
	{
		if (p->value == weight)
		{
			cout << s;
			return s;
		}
		else
			return "";
		if(p->left!=NULL)
			getcode(p->left, weight, s + "1");
		else if (p->right != NULL)
			getcode(p->right, weight, s + "0");
	}

	//打印树
	void printInShape(node* T, int level,string s)
	{
		for (int i = 0; i < level - 1; i++)
		{
			cout << "     ";
		}
		T->code = s;   //遍历的过程把二进制码存进叶节点
		cout << T->value << " "<<T->code<<" "<<endl;
	}
	void outInShape(node* p, int lev,string s)
	{
		if (p != NULL) {
			outInShape(p->left, lev + 1,s+"1");//每次遍历传进的level参数加一
			printInShape(p, lev,s);
			outInShape(p->right, lev + 1,s+"0");
		}
	}

	char findcode(string s)//解压
	{
		for (int i = 0; i < elementcount; i++)
		{
			if (s == p[i].code)//遍历寻找对应码
			{
				return 'a'+i;
			}
		}
	}
};

void countfre(int *p,string s)//计数
{
	for (int i = 0; i < 10; i++)
	{
		p[i] = 0;
	}
	for (int i = 0; i < s.size(); i++)
	{
		p[s[i] - 'a']++;
	}
	return;
}

void compress(string &s,hufftree hf)//压缩
{
	string temp;
	for (int i = 0; i < s.size(); i++)
	{
		temp += hf.p[s[i] - 'a'].code+" ";
	}
	s = temp;
	return;
}

void ease(string& s, hufftree hf)//解压
{
	string temp0;
	string temp = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			temp += s[i];
		}
		else
		{
			temp0 += hf.findcode(temp);
			temp = "";
		}
	}
	s = temp0;
}

int main()
{
	int* p = new int[10];
	string s = "cfbbajheabceiiddbcbdaahggccbbbgefaebccfdcffhddaaegadaae";//可以多存一个字符串数组用来保存对应的单词和权重一起保存进叶节点
	countfre(p, s);
	hufftree hf;
	hf.maketree(p);
	hf.outInShape(hf.root, 1,"");
	cout << endl;
	compress(s,hf);
	cout << s<<endl<<endl;
	ease(s, hf);
	cout << s;
	return 0;
}