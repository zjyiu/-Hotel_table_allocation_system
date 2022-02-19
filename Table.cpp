#include"Table.h"
#include<fstream>

using namespace std;

Table::Table() {
	isusing = false;
}

//����Ϊ�ӿں����͸ı�˽�г�Ա�ĺ���-
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

void change(vector<vector<Table>>& Tables, Moment t) {//������λ��Ϣ
	for(auto i=Tables.begin();i!=Tables.end();i++)
		for (auto j = (*i).begin();j != (*i).end();j++) {
			if ((*j).getuse() && isless((*j).gettime(), t))
				(*j).changeuse(false);
		}
}

bool gettable(vector<vector<Table>>& Tables, int n, int& x, int& y) {
	//�����ʺϹ˿͵����ӣ������ӵ���λ���ͱ�Ŵ���x��y��
	bool ext = false;//ext��ʾ�����ӵĴ������
	x = n;y = 0;
	auto i = Tables.begin();
	for (;(i + x) != Tables.end();x++) {
		y = 0;
		auto j = (*(i + x)).begin();
		for(;(j+y)!= (*(i + x)).end();y++)
			if (!(*(j + y)).getuse()) { ext = true;break; }
		if (ext) break;
	}
	if (ext) return ext;//����п����ӣ�����true
	Moment temp;
	temp.hour = 10;
	temp.minute = 59;
	x = n;y = 0;
	int p = x;int q = y;
	for (;(i + x) != Tables.end();x++) {
		auto j = (*(i + x)).begin();
		for (;(j + y) != (*(i + x)).end();y++)
			if (isless((*(j + y)).gettime(), temp)) {//Ѱ�ҽ���ʹ��ʱ����С������
				temp.hour = (*(j + y)).gettime().hour;
				temp.minute = (*(j + y)).gettime().minute;
				p = x;q = y;
			}
		y = 0;
	}
	x = p;y = q;
	return ext;
}

void create(vector<std::vector<Table>>& Tables) {//��ȡ����������Ϣ
	ifstream in("input_table.txt");
	int a, b;
	while (in.peek() != EOF) {
		in >> a >> b;
		while (Tables.size() <= b) {//�����������������
			vector<Table> temp1;
			Tables.push_back(temp1);
		}
		while (Tables[b].size() < a) {//������������������
			Table temp2;
			Tables[b].push_back(temp2);
		}
	}
	in.close();
}