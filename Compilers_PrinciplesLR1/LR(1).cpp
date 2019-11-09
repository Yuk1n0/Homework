#include"LR(1).h"
/*Program*/
/*Program���캯��*/
Program::Program(char l, string r, set<char> s, int rank) 
{
	this->left = l;
	this->right = r;
	this->search = s;
	this->rank = rank;
}

/*�ж�����Program�Ƿ����*/
bool operator == (const Program& a, const  Program& b) 
{
	if (a.left == b.left) 
    {
		if (a.right == b.right && a.rank == b.rank) 
        {	//����ʽ�󲿣��Ҳ������ķ��ĸ�����������
			return true;
		}
	}
	return false;
}

Program& Program::operator = (const Program& b) 
{	//���ظ�ֵ���������һ����Ŀ��ֵ����һ��
	left = b.left;
	right = b.right;
	search = b.search;
	return *this;
}

/*Item*/
/*�ж�����Item�Ƿ����*/
bool operator == (const Item& a, const Item& b) 
{	//����==���������������Ŀ���е���Ŀһһ�ȶ�
	vector<Program> pa = a.pro, pb = b.pro;
	if (pa.size() != pb.size()) 
    {
		return false;
	}

	else {
		for (vector<Program> ::iterator it = pa.begin(); it != pa.end(); it++) 
        {
			vector<Program> ::iterator res = find(pb.begin(), pb.end(), *it);
			if (res == pb.end()) 
            {
				return false;
			}
			else {
				if ((*it).search == (*res).search) 
                {
					return true;
				}
				else 
                {
					return false;
				}
			}
		}
		return false;
	}
}

/*��Item����Ŀ���м����µ���Ŀ*/
bool Item::addPro(const Program& p, Item& i) 
{
	vector<Program>::iterator res = find(i.pro.begin(), i.pro.end(), p);	//�жϲ�����
	if (res == i.pro.end()) 
    {
		i.pro.push_back(p);
		return true;
	}
	else 
    {
		return false;
	}
}

/*������Ŀ���ķ��ս����*/
void Item::insertVN(Item& i) 
{
	for (vector<Program>::size_type j = 0; j < i.pro.size(); j++) 
    {	//���ķ��еķ��ս������Ŀ�Ĳ���ʽ��һһ�ȶ�
		vector<char>::iterator res = find(i.vn.begin(), i.vn.end(), i.pro[j].left);
		if (res == i.vn.end()) 
        {
			i.vn.push_back(i.pro[j].left);
		}
	}
}

/*������Ŀ�����ս����*/
void Item::insertVT(Item& i, Item g) 
{
	for (vector<Program>::size_type j = 0; j < i.pro.size(); j++) 
    {
		string r = i.pro[j].right;	//�õ�����ʽ�Ҳ���һ��һ���ַ��ж�
		for (unsigned int j = 0; j < r.size(); j++) 
        {
			vector<char>::iterator res1 = find(g.vn.begin(), g.vn.end(), r[j]);
			if (res1 == g.vn.end()) 
            {
				vector<char>::iterator res2 = find(i.vt.begin(), i.vt.end(), r[j]);
				if (res2 == i.vt.end()) 
                {
					i.vt.push_back(r[j]);
				}
			}
		}
	}
	i.vt.push_back('#');	//����ٲ��롮#��
}

/*������Ŀ�����з��ż�*/
void Item::insertV(Item& i) 
{	//���ս�����ͷ��ս�����ϲ�
	for (vector<char>::iterator it = i.vn.begin(); it != i.vn.end(); it++) 
    {
		i.v.push_back(*it);
	}
	for (vector<char>::iterator it = i.vt.begin(); it != i.vt.end(); it++) 
    {
		i.v.push_back(*it);
	}
}

/*LR(1)*/

/*���캯��*/
LR::LR(char start, Item g, string input) 
{
	this->start = start;
	this->g = g;
	this->input = input;
	Item i;
	i.addPro(g.pro[0], i);
	getClosure(i);
	i.insertVN(i);
	i.insertVT(i, g);
	i.insertV(i);
	M.push_back(i);
}

/*�ϲ���������*/
void LR::unionSet(Program& a, const Program& b) 
{
	for (set<char>::iterator it = b.search.begin(); it != b.search.end(); it++) 
    {
		set<char>::iterator res = find(a.search.begin(), a.search.end(), (*it));
		if (res == a.search.end()) 
        {
			a.search.insert((*it));
		}
	}
}
/*�õ���Ŀ����CLOSURE�հ�*/
Item LR::getClosure(Item& i) 
{
	vector<Program> p = i.pro;
	int len = p.size();
	if (len == 0) 
    {	//�������Ŀ����û����Ŀ��ֱ�ӷ���
		return i;
	}
	else 
    {
		int l_length = p.size();	//��հ�ǰ����Ŀ������
		int n_length = p.size();	//��հ������Ŀ������
		for (vector<Program>::size_type k = 0; k < p.size(); k++) 
        {
			set<char> last = p[k].search;	//�������֮ǰ����������
			string r = p[k].right;	//�õ�����Ŀ����ʽ���Ҳ�
			if (r.size() == 0) 
            {
				continue;
			}
			vector<char>::iterator res1 = find(g.vn.begin(), g.vn.end(), r[0]);
			if (res1 != g.vn.end()) 
            {	//�������ʽ�Ҳ��ĵ�һ���ַ��Ƿ��ս��
				for (vector<Program>::size_type j = 0; j < g.pro.size(); j++) 
                {
					if (r[0] == g.pro[j].left) 
                    {	//���ķ����ҵ��÷��ս����Ӧ�Ĳ���ʽ
						Program pg = g.pro[j];
						if (r.size() != 1) 
                        {	//����÷��ս�����滹�з��������µ���������
							string temp = r;
							temp = temp.substr(1);
							pg.search = getFirst(temp, temp[0]);
							last = pg.search;
						}
						pg.search = last;	//������������

						vector<Program>::iterator res2 = find(i.pro.begin(), i.pro.end(), pg);
						if (res2 == i.pro.end()) 
                        {	//�������Ŀ����Ŀ���в�����
							i.pro.push_back(pg);	//��������Ŀ
							n_length = i.pro.size();
							p = i.pro;
						}
						else {
							if ((*res2).search != pg.search) 
                            {	//������Ҳ�����ȶ�������������ȣ���ϲ�
								unionSet(*res2, pg);
								p = i.pro;
							}
						}
					}
				}
			}
		}
		return i;
	}
}

/*�õ���ǰ��������*/
set<char> LR::getFirst(const string& s, const char& N) 
{ //sΪ.����ķ��Ŵ���NΪ.���һ���ַ�
	vector<char>::iterator it = find(g.vn.begin(), g.vn.end(), s[0]);
	if (it != g.vn.end()) {	//�������ַ��Ƿ��ս��
		for (vector<Program>::size_type i = 0; i < g.pro.size(); i++) 
        {
			if (g.pro[i].left == s[0]) 
            {	//���ķ��ķ��������Ĳ���ʽ
				getFirst(g.pro[i].right, s[0]);	//�ݹ���FIRST
			}
		}
	}
	FIRST[N].insert(s[0]);	//����Ƿ��ս������ֱ�Ӿ�Ϊ������ս��
	return FIRST[N];
}

/*����GO����*/
void LR::go() 
{
	for (vector<Item>::size_type it = 0; it < M.size(); it++) 
    {	//ѭ������������Ŀ�����ж�
		int r1 = it;
		vector<char> V = M[it].v;	//ȡ����Ŀ�������з��ż�
		for (vector<char>::iterator w = V.begin(); w != V.end(); w++) 
        {	//�����з��ż�����ѭ�������ж�
			char word;
			Item i;
			for (vector<Program>::iterator p = M[it].pro.begin(); p != M[it].pro.end(); p++) 
            {
				string r = (*p).right;	//��Ŀ���Ҳ����Ŵ�
				if (r.size() != 0) 
                {
					if ((*w) == r[0]) 
                    {	//������Ŵ��Ҳ�����ż��е�ĳһ�������
						word = (*w);
						Program pro((*p).left, r.substr(1), (*p).search, (*p).rank);
						i.addPro(pro, i);	//����Ŀ���в����������Ŀ
					}
				}
			}

			if (i.pro.size() != 0) 
            {	//��Ŀ��������Ŀ
				getClosure(i);	//�������Ŀ����CLOSURE�հ�
				int temp = M.size() - 1;
				int r2 = 0;
				for (vector<Item>::size_type mx = 0; mx < M.size(); mx++) 
                {
					r2 = mx;
					if (i == M[mx]) 
                    {	//�������Ŀ���Ѵ���
						break;
					}

				}
				if (r2 == temp) 
                {	//���������Ŀ���в�������ͬ����Ŀ�����������Ŀ
					i.insertVN(i);	//�õ���Ŀ���ķ��ս����
					i.insertVT(i, g);	//�õ���Ŀ�����ս����
					i.insertV(i);	//�õ���Ŀ�������з��ż���������з��ţ��ս����ս�����е�Ԫ��ֻ����.����ķ��ţ�.ǰ��ķ��Ŷ��ں���ĳ�������û��Ӱ��
					M.push_back(i);
					r2 += 1;
				}
				GO[pair<int, char>(r1, word)] = r2;	//ͬʱ����Ŀ���Ĺ�ϵ���浽GO����
			}
		}
	}
}

/*����ACTION��*/
void LR::getAction() 
{
	for (unsigned int i = 0; i < M.size(); i++) 
    {
		for (vector<char>::iterator it = g.vt.begin(); it != g.vt.end(); it++) 
        {	//ѭ�������ս��
			if (GO[pair<int, char>(i, (*it))] != NULL) 
            {	//���GO���д��ڸ��ս���Ĺ�ϵ�������Ķ���Ϊ�ƽ�
				int S = GO[pair<int, char>(i, (*it))];
				ACTION[pair<int, char>(i, (*it))] = pair<act, int>(shift, S);
			}
			else 
            {
				ACTION[pair<int, char>(i, (*it))] = pair<act, int>(error, -1);	//������ǳ���
			}
		}
	}

	//����ʽ�Ҳ�����Ϊ0����Ŀ���ǹ�Լ��Ŀ
	for (vector<Item>::size_type mx = 0; mx < M.size(); mx++) 
    {
		for (vector<Program>::size_type px = 0; px < M[mx].pro.size(); px++) 
        {
			if (M[mx].pro[px].right.size() == 0) 
            {
				for (set<char>::iterator it = M[mx].pro[px].search.begin(); it != M[mx].pro[px].search.end(); it++)
                {
					if (M[mx].pro[px].left == this->start) 
                    {
						ACTION[pair<int, char>(mx, (*it))] = pair<act, int>(accept, -1);	//�����Ϊ��ʼ���ţ�������Ϊaccept
					}
					else 
                    {
						ACTION[pair<int, char>(mx, (*it))] = pair<act, int>(reduce, M[mx].pro[px].rank);	//��Լ���ķ��ж�Ӧ�Ĳ���ʽ
					}
				}
			}
		}
	}
}

/*����GOTO��*/
void LR::getGoto() 
{
	for (unsigned int i = 0; i < M.size(); i++) 
    {
		for (vector<char>::iterator it = g.vn.begin(); it != g.vn.end(); it++) 
        {	//�Է��ս�����б�����������GO���ж�
			if ((*it) == start) 
            {
				continue;
			}
			if (GO[pair<int, char>(i, (*it))] != NULL) 
            {
				int G = GO[pair<int, char>(i, (*it))];
				GOTO[pair<int, char>(i, (*it))] = G;
			}
			else 
            {
				GOTO[pair<int, char>(i, (*it))] = -1;
			}
		}
	}
}

/*��ջ�е�Ԫ��ת��Ϊ�ַ���*/
template <typename T>
string LR::turnFromStack(stack<T> s, int type) 
{	//type��ֵ���ΪINT���״̬ջ����ת����CHAR��Է���ջ����ת��
	int len = s.size();
	string str = "";
	switch (type) 
    {
	case INT:
		while (len--) 
        {
			int n = s.top();
			s.pop();
			str.append(to_string(static_cast<long long>(n)));
		}
		break;
	case CHAR:
		char* t = new char[len + 1];
		int i = 0;
		while (len--) 
        {
			char w = s.top();
			s.pop();
			t[i] = w;
			i++;
		}
		t[i] = '\0';
		str = t;
		break;
	}
	reverse(str.begin(), str.end());
	return str;
}

/*���������*/
void LR::showTable() 
{	//��ACTION��GOTO����ȡ����Ӧ�Ĺ�ϵ
	string tabAct = "";
	string tabGoto = "";
	unsigned int j, k;
	for (j = 0; j <= (g.vt.size() / 2 + 1); j++) 
    {
		tabAct.append("\t");

	}
	for (k = 0; k <= g.vt.size() - j + 1; k++) 
    {
		tabGoto.append("\t");
	}
	cout << tabAct << "ACTION" << tabGoto << "GOTO" << endl;
	cout << '\t';
	char* VT = new char[g.vt.size() + 1];
	char* VN = new char[g.vn.size() - 1];
	int i = 0;
	cout << "\t";
	for (vector<char>::iterator it = g.vt.begin(); it != g.vt.end(); it++) 
    {
		cout << (*it) << '\t';
		VT[i] = (*it);
		i++;
	}
	i = 0;
	for (vector<char>::iterator it = g.vn.begin(); it != g.vn.end(); it++) 
    {
		if ((*it) != start) 
        {
			cout << (*it) << '\t';
			VN[i] = (*it);
			i++;
		}
	}
	cout << '\n';
	int len = M.size();
	i = 0;
	while (len--) 
    {
		cout << '\t' << i;
		int j = g.vt.size();
		int c = 0;
		cout << '\t';
		while (j--) 
        {
			pair<act, int> a = ACTION[pair<int, char>(i, VT[c])];
			act fir = a.first;
			int sec = a.second;
			if (fir == shift) 
            {
				cout << "S" + to_string(static_cast<long long>(sec)) << '\t';
			}
			else if (fir == reduce) 
            {
				cout << "R" + to_string(static_cast<long long>(sec)) << '\t';
			}
			else if (fir == error) 
            {
				cout << " " << '\t';
			}
			else if (fir == accept) 
            {
				cout << "acc" << '\t';
			}
			c++;
		}
		j = g.vn.size() - 1;
		c = 0;
		while (j--) 
        {
			int a = GOTO[pair<int, char>(i, VN[c])];
			if (a != -1) 
            {
				cout << a << '\t';
			}
			else if (a == -1) 
            {
				cout << " " << '\t';
			}
			c++;
		}
		i++;
		cout << endl;
	}
	free(VT);
	free(VN);
}

/*����tab�����������ʽ*/
void setFormat(const string& STATE, const string& SYMBOL, const string& in, string& tabSym, string& tabIn, string& tabAct);

/*�����봮���з���*/
bool LR::analyse() 
{	//ͨ��ACTION���GOTO������ж�
	int STEP = 1;
	string STATE = "0";
	string SYMBOL = "#";
	string in = input;
	string ACT = "";
	string GT = "";
	state.push(0);
	symbol.push('#');
	string tabSym = "";
	string tabIn = "";
	string tabAct = "";
	while (true) 
    {
		STATE = turnFromStack(state, INT);
		SYMBOL = turnFromStack(symbol, CHAR);
		setFormat(STATE, SYMBOL, in, tabSym, tabIn, tabAct);
		cout << '\t' << STEP << "\t\t" << STATE << tabSym << SYMBOL << tabIn << in;
		int sta = state.top();
		pair<act, int> a = ACTION[pair<int, char>(sta, in[0])];
		act action = a.first;
		int nextSta = a.second;

		/*������ƽ�*/
		if (action == shift) 
        {
			ACT = "S" + to_string(static_cast<long long>(nextSta));
			symbol.push(in[0]);
			state.push(nextSta);
			in = in.substr(1);
		}

		/*����ǹ�Լ*/
		else if (action == reduce) 
        {
			ACT = "R" + to_string(static_cast<long long>(nextSta));
			int length = g.pro[nextSta].right.size();
			while (length--) 
            {
				state.pop();
				symbol.pop();
			}
			int nextSta_gt = GOTO[pair<int, char>(state.top(), g.pro[nextSta].left)];
			GT = to_string(static_cast<long long>(nextSta_gt));
			state.push(nextSta_gt);
			symbol.push(g.pro[nextSta].left);
		}

		/*����Ǵ���*/
		else if (action == error) 
        {
			ACT = "����";
		}

		/*����ǽ���*/
		else if (action == accept) 
        {
			ACT = "acc";
		}
		STEP++;
		cout << tabAct << ACT << "\t\t" << GT << endl;
		GT = "";
		if (ACT == "����") 
        {
			break;
		}
		else if (ACT == "acc") 
        {
			return true;
		}
	}
	return false;
}

/*����tab�����������ʽ*/
void setFormat(const string& STATE, const string& SYMBOL, const string& in, string& tabSym, string& tabIn, string& tabAct) 
{
	if (STATE.size() >= 8) 
    {
		tabSym = "\t\t";
	}
	else 
    {
		tabSym = "\t\t\t";
	}
	if (SYMBOL.size() >= 8) 
    {
		tabIn = "\t";
	}
	else 
    {
		tabIn = "\t\t";
	}
	if (in.size() >= 8) 
    {
		tabAct = "\t";
	}
	else 
    {
		tabAct = "\t\t";
	}
}
