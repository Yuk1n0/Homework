#include"LR(1).h"
/*Program*/
/*Program构造函数*/
Program::Program(char l, string r, set<char> s, int rank) 
{
	this->left = l;
	this->right = r;
	this->search = s;
	this->rank = rank;
}

/*判断两个Program是否相等*/
bool operator == (const Program& a, const  Program& b) 
{
	if (a.left == b.left) 
    {
		if (a.right == b.right && a.rank == b.rank) 
        {	//产生式左部，右部，由文法哪个产生得来的
			return true;
		}
	}
	return false;
}

Program& Program::operator = (const Program& b) 
{	//重载赋值运算符，将一个项目赋值给另一个
	left = b.left;
	right = b.right;
	search = b.search;
	return *this;
}

/*Item*/
/*判断两个Item是否相等*/
bool operator == (const Item& a, const Item& b) 
{	//重载==运算符，将两个项目集中的项目一一比对
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

/*往Item的项目集中加入新的项目*/
bool Item::addPro(const Program& p, Item& i) 
{
	vector<Program>::iterator res = find(i.pro.begin(), i.pro.end(), p);	//判断不存在
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

/*构造项目集的非终结符集*/
void Item::insertVN(Item& i) 
{
	for (vector<Program>::size_type j = 0; j < i.pro.size(); j++) 
    {	//将文法中的非终结符跟项目的产生式左部一一比对
		vector<char>::iterator res = find(i.vn.begin(), i.vn.end(), i.pro[j].left);
		if (res == i.vn.end()) 
        {
			i.vn.push_back(i.pro[j].left);
		}
	}
}

/*构造项目集的终结符集*/
void Item::insertVT(Item& i, Item g) 
{
	for (vector<Program>::size_type j = 0; j < i.pro.size(); j++) 
    {
		string r = i.pro[j].right;	//得到产生式右部，一个一个字符判断
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
	i.vt.push_back('#');	//最后再插入‘#’
}

/*构造项目集所有符号集*/
void Item::insertV(Item& i) 
{	//将终结符集和非终结符集合并
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

/*构造函数*/
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

/*合并搜索符集*/
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
/*得到项目集的CLOSURE闭包*/
Item LR::getClosure(Item& i) 
{
	vector<Program> p = i.pro;
	int len = p.size();
	if (len == 0) 
    {	//如果该项目集中没有项目则直接返回
		return i;
	}
	else 
    {
		int l_length = p.size();	//求闭包前的项目集长度
		int n_length = p.size();	//求闭包后的项目集长度
		for (vector<Program>::size_type k = 0; k < p.size(); k++) 
        {
			set<char> last = p[k].search;	//保存操作之前的搜索符集
			string r = p[k].right;	//得到该项目产生式的右部
			if (r.size() == 0) 
            {
				continue;
			}
			vector<char>::iterator res1 = find(g.vn.begin(), g.vn.end(), r[0]);
			if (res1 != g.vn.end()) 
            {	//如果产生式右部的第一个字符是非终结符
				for (vector<Program>::size_type j = 0; j < g.pro.size(); j++) 
                {
					if (r[0] == g.pro[j].left) 
                    {	//从文法中找到该非终结符对应的产生式
						Program pg = g.pro[j];
						if (r.size() != 1) 
                        {	//如果该非终结符后面还有符号则求新的搜索符集
							string temp = r;
							temp = temp.substr(1);
							pg.search = getFirst(temp, temp[0]);
							last = pg.search;
						}
						pg.search = last;	//更新搜索符集

						vector<Program>::iterator res2 = find(i.pro.begin(), i.pro.end(), pg);
						if (res2 == i.pro.end()) 
                        {	//如果改项目在项目集中不存在
							i.pro.push_back(pg);	//插入新项目
							n_length = i.pro.size();
							p = i.pro;
						}
						else {
							if ((*res2).search != pg.search) 
                            {	//如果左部右部都相等而搜索符集不相等，则合并
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

/*得到向前搜索符集*/
set<char> LR::getFirst(const string& s, const char& N) 
{ //s为.后面的符号串，N为.后第一个字符
	vector<char>::iterator it = find(g.vn.begin(), g.vn.end(), s[0]);
	if (it != g.vn.end()) {	//如果这个字符是非终结符
		for (vector<Program>::size_type i = 0; i < g.pro.size(); i++) 
        {
			if (g.pro[i].left == s[0]) 
            {	//用文法的符合条件的产生式
				getFirst(g.pro[i].right, s[0]);	//递归求FIRST
			}
		}
	}
	FIRST[N].insert(s[0]);	//如果是非终结符，则直接就为这个非终结符
	return FIRST[N];
}

/*构造GO函数*/
void LR::go() 
{
	for (vector<Item>::size_type it = 0; it < M.size(); it++) 
    {	//循环遍历所有项目集来判断
		int r1 = it;
		vector<char> V = M[it].v;	//取出项目集的所有符号集
		for (vector<char>::iterator w = V.begin(); w != V.end(); w++) 
        {	//对所有符号集进行循环遍历判断
			char word;
			Item i;
			for (vector<Program>::iterator p = M[it].pro.begin(); p != M[it].pro.end(); p++) 
            {
				string r = (*p).right;	//项目的右部符号串
				if (r.size() != 0) 
                {
					if ((*w) == r[0]) 
                    {	//如果符号串右部与符号集中的某一符号相等
						word = (*w);
						Program pro((*p).left, r.substr(1), (*p).search, (*p).rank);
						i.addPro(pro, i);	//往项目集中插入这个新项目
					}
				}
			}

			if (i.pro.size() != 0) 
            {	//项目集中有项目
				getClosure(i);	//对这个项目集求CLOSURE闭包
				int temp = M.size() - 1;
				int r2 = 0;
				for (vector<Item>::size_type mx = 0; mx < M.size(); mx++) 
                {
					r2 = mx;
					if (i == M[mx]) 
                    {	//如果该项目集已存在
						break;
					}

				}
				if (r2 == temp) 
                {	//如果所有项目集中不存在相同的项目，则插入新项目
					i.insertVN(i);	//得到项目集的非终结符集
					i.insertVT(i, g);	//得到项目集的终结符集
					i.insertV(i);	//得到项目集的所有符号集，这个所有符号，终结或非终结符集中的元素只包含.后面的符号，.前面的符号对于后面的程序运行没有影响
					M.push_back(i);
					r2 += 1;
				}
				GO[pair<int, char>(r1, word)] = r2;	//同时将项目集的关系保存到GO表中
			}
		}
	}
}

/*构造ACTION表*/
void LR::getAction() 
{
	for (unsigned int i = 0; i < M.size(); i++) 
    {
		for (vector<char>::iterator it = g.vt.begin(); it != g.vt.end(); it++) 
        {	//循环遍历终结符
			if (GO[pair<int, char>(i, (*it))] != NULL) 
            {	//如果GO表中存在该终结符的关系，则它的动作为移进
				int S = GO[pair<int, char>(i, (*it))];
				ACTION[pair<int, char>(i, (*it))] = pair<act, int>(shift, S);
			}
			else 
            {
				ACTION[pair<int, char>(i, (*it))] = pair<act, int>(error, -1);	//否则就是出错
			}
		}
	}

	//产生式右部长度为0的项目就是规约项目
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
						ACTION[pair<int, char>(mx, (*it))] = pair<act, int>(accept, -1);	//如果左部为开始符号，则动作就为accept
					}
					else 
                    {
						ACTION[pair<int, char>(mx, (*it))] = pair<act, int>(reduce, M[mx].pro[px].rank);	//规约到文法中对应的产生式
					}
				}
			}
		}
	}
}

/*构造GOTO表*/
void LR::getGoto() 
{
	for (unsigned int i = 0; i < M.size(); i++) 
    {
		for (vector<char>::iterator it = g.vn.begin(); it != g.vn.end(); it++) 
        {	//对非终结符进行遍历，并根据GO表判断
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

/*将栈中的元素转化为字符串*/
template <typename T>
string LR::turnFromStack(stack<T> s, int type) 
{	//type的值如果为INT则对状态栈进行转化，CHAR则对符号栈进行转化
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

/*输出分析表*/
void LR::showTable() 
{	//从ACTION和GOTO表中取出对应的关系
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

/*设置tab，控制输出格式*/
void setFormat(const string& STATE, const string& SYMBOL, const string& in, string& tabSym, string& tabIn, string& tabAct);

/*对输入串进行分析*/
bool LR::analyse() 
{	//通过ACTION表和GOTO表进行判断
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

		/*如果是移进*/
		if (action == shift) 
        {
			ACT = "S" + to_string(static_cast<long long>(nextSta));
			symbol.push(in[0]);
			state.push(nextSta);
			in = in.substr(1);
		}

		/*如果是规约*/
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

		/*如果是错误*/
		else if (action == error) 
        {
			ACT = "出错";
		}

		/*如果是接受*/
		else if (action == accept) 
        {
			ACT = "acc";
		}
		STEP++;
		cout << tabAct << ACT << "\t\t" << GT << endl;
		GT = "";
		if (ACT == "出错") 
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

/*设置tab，控制输出格式*/
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
