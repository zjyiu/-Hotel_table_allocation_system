#include"Table.h"
#include<fstream>

using namespace std;

Table::Table() {
	isusing = false;
}

//以下为接口函数和改变私有成员的函数-
Moment Table::gettime() {
	return availtime;
}

bool Table::getuse() {
	return isusing;
}

void Table::changetime(Moment t) {
	availtime = t;
}

void Table::changeuse(bool u) {
	isusing = u;
}

void change(vector<vector<Table>>& Tables, Moment t) {//更新桌位信息
	for(auto i=Tables.begin();i!=Tables.end();i++)
		for (auto j = (*i).begin();j != (*i).end();j++) {
			if ((*j).getuse() && isless((*j).gettime(), t))
				(*j).changeuse(false);
		}
}

bool gettable(vector<vector<Table>>& Tables, int n, int& x, int& y) {
	//查找适合顾客的桌子，将桌子的座位数和编号存在x和y中
	bool ext = false;//ext表示空桌子的存在情况
	x = n;y = 0;
	auto i = Tables.begin();
	for (;(i + x) != Tables.end();x++) {
		y = 0;
		auto j = (*(i + x)).begin();
		for(;(j+y)!= (*(i + x)).end();y++)
			if (!(*(j + y)).getuse()) { ext = true;break; }
		if (ext) break;
	}
	if (ext) return ext;//如果有空桌子，返回true
	Moment temp;
	temp.hour = 10;
	temp.minute = 59;
	x = n;y = 0;
	int p = x;int q = y;
	for (;(i + x) != Tables.end();x++) {
		auto j = (*(i + x)).begin();
		for (;(j + y) != (*(i + x)).end();y++)
			if (isless((*(j + y)).gettime(), temp)) {//寻找结束使用时间最小的桌子
				temp.hour = (*(j + y)).gettime().hour;
				temp.minute = (*(j + y)).gettime().minute;
				p = x;q = y;
			}
		y = 0;
	}
	x = p;y = q;
	return ext;
}

void create(vector<std::vector<Table>>& Tables) {//读取储存桌子信息
	ifstream in("input_table.txt");
	int a, b;
	while (in.peek() != EOF) {
		in >> a >> b;
		while (Tables.size() <= b) {//对桌子种类进行扩充
			vector<Table> temp1;
			Tables.push_back(temp1);
		}
		while (Tables[b].size() < a) {//对桌子张数进行扩充
			Table temp2;
			Tables[b].push_back(temp2);
		}
	}
	in.close();
}