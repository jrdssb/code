#include<iostream>
using namespace std;

class node
{
public:
	int value=0;			//Ȩ��
	node* left;
	node* right;
	bool selected = false;   //�жϸýڵ��Ƿ����ڽ���
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
	int elementcount = 10;  //�ж�����Ҫת��code�ĵ���
	node *root=new node(100);
	int* arr = new int[elementcount];//���Ƶ��
	node* p = new node[30];//������ڵ�����
	int cursize = elementcount;//��ǰ����Ҫ������������

	void maketree(int* a)
	{
		for (int i = 0; i < 10; i++)		//����Ȩ��
		{
			node*temp = new node(a[i]);
			p[i] = *temp;
		}
		cout << endl;
		while (cursize<30)//С��maxsize
		{
			int index1 = -1;
			int index2 = -1;
			getmin(index1, index2);		//�ҵ�Ŀǰ���ڵ����У����ڵ�Ȩ����С����������Ӧ���±�
			merge(&p[index1], &p[index2], p[cursize]); //������������Ϊ���ҽڵ㣬selected����Ϊtrue�����浽������һ����λ��
			p[index1].selected = true, p[index2].selected = true;
			cursize++;
			if (selectednum() == cursize - 1)		//�����ʱ��������������ѡ��Ĵ��������ֻ��һ��û��ѡ��˵���������������ϵ���һ��
			{
				*root = p[cursize - 1];
				break;
			}
		}
	}
	void merge(node *left, node *right, node &parent)  //���Ϻ���
	{
		node *temp = new node(left->value + right->value, left, right);
		parent = *temp;
		return;
	}

	void getmin(int& index1, int& index2)		//���������С�±�
	{
		int min1 = INT_MAX-1;
		int min2 = INT_MAX;  //������������Сֵ��Ϊ���
		for (int i = 0; i < cursize; i++)
		{
			if (p[i].selected == true)continue;     //����selected==true˵�������Ѿ�������continue
			if (p[i].value < min1 || p[i].value < min2)			//ֻҪС������֮һ���ͰѸ�ֵ��ֵ��������Ǹ�
			{
				if (min1 < min2)
				{
					min2 = p[i].value;
					index2 = i;				//��ö�Ӧ�±�ֵ
				}
				else
				{
					min1 = p[i].value;
					index1 = i;
				}	
			}
		}
	}

	int selectednum()		//selected��������
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

	string getcode(node*p,int weight,string s)//��ȡ��������
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

	//��ӡ��
	void printInShape(node* T, int level,string s)
	{
		for (int i = 0; i < level - 1; i++)
		{
			cout << "     ";
		}
		T->code = s;   //�����Ĺ��̰Ѷ���������Ҷ�ڵ�
		cout << T->value << " "<<T->code<<" "<<endl;
	}
	void outInShape(node* p, int lev,string s)
	{
		if (p != NULL) {
			outInShape(p->left, lev + 1,s+"1");//ÿ�α���������level������һ
			printInShape(p, lev,s);
			outInShape(p->right, lev + 1,s+"0");
		}
	}

	char findcode(string s)//��ѹ
	{
		for (int i = 0; i < elementcount; i++)
		{
			if (s == p[i].code)//����Ѱ�Ҷ�Ӧ��
			{
				return 'a'+i;
			}
		}
	}
};

void countfre(int *p,string s)//����
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

void compress(string &s,hufftree hf)//ѹ��
{
	string temp;
	for (int i = 0; i < s.size(); i++)
	{
		temp += hf.p[s[i] - 'a'].code+" ";
	}
	s = temp;
	return;
}

void ease(string& s, hufftree hf)//��ѹ
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
	string s = "cfbbajheabceiiddbcbdaahggccbbbgefaebccfdcffhddaaegadaae";//���Զ��һ���ַ����������������Ӧ�ĵ��ʺ�Ȩ��һ�𱣴��Ҷ�ڵ�
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