#include"Customer.h"
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<iostream>

using namespace std;

Customer::Customer(){//���캯��
	eattime.hour = 0;
}

void creattxt() {
	ofstream out("input_customer.txt");
	srand((unsigned)time(NULL));
	int n = 99 + rand() % 901;
	vector<int> as;
	vector<int> ahs;
	vector<int> ams;//�������ϴ����Ѿ����ɵĹ˿���Ϣ
	for (int i = 0;i < n;i++) {
		int a = 1 + rand() % 8;//�˿������趨1��8����
		int ah = 11 + rand() % 14;//�涨�賿1�㿪ʼ���Ӵ�����
		int am = rand() % 60;
		int e = 5 + rand() % 26;//�趨�˿��ò�ʱ��Ϊ5��30����
		bool ext = false;
		for (int j = 0;j < i;j++)//�Ƚ����ɵ���Ϣ�Ƿ�����ظ�
			if (as[j] == a && ahs[j] == ah && ams[j] == am) { ext = true;break; }
		if (ext) { i--;continue; }
		as.push_back(a);ahs.push_back(ah);ams.push_back(am); 
		out << a << "\t" << ah % 24 << "\t" << am << "\t" << e << endl;
	}
	out.close();
}

void create(vector<Customer>& Customers) {/��/��ȡ����˿���Ϣ
	creattxt();
	ifstream in("input_customer.txt");
	while (in.peek() != EOF) {
		Customer temp;
		in >> temp.number >> temp.arrive.hour >> temp.arrive.minute >> temp.eattime.minute;
		Customers.push_back(temp);
	}
	in.close();
}

bool comp(Customer& a, Customer& b) {//sort�е�comp����
	if (isless(a.arrive, b.arrive)) return true;
	if (a.arrive.hour == b.arrive.hour && a.arrive.minute == b.arrive.minute && a.number < b.number)
		return true;
	return false;
}

void handle(vector<Customer>& Customers, vector<vector<Table>>& Tables) {
	sort(Customers.begin(), Customers.end(), comp);//����
	for (auto i = Customers.begin();i != Customers.end();i++) {
		change(Tables, (*i).arrive);//����������Ϣ
		int p, q;
		if (gettable(Tables, (*i).number, p, q)) {//�п����ӵ����
			(*i).starteat = (*i).arrive;
			(*i).wait.hour = (*i).wait.minute = 0;
			(*i).leave = addm((*i).starteat, (*i).eattime);
			Tables[p][q].changeuse(true);//����������Ϣ
			Tables[p][q].changetime((*i).leave);
		}
		else {//û�п����ӵ����
			Moment temp = Tables[p][q].gettime();
			(*i).wait = subm(temp, (*i).arrive);
			(*i).starteat = addm((*i).arrive, (*i).wait);
			(*i).leave = addm((*i).starteat, (*i).eattime);
			Tables[p][q].changetime((*i).leave);//����������Ϣ
		}
	}
}

void out(vector<Customer>& Customers) {
	ofstream out("output_customer.txt");//�����Ҫ��3�����˿͵���Ϣ
	int n, waitminute, stayminute;//�洢��š��ȴ�ʱ���ͣ��ʱ��
	double avgwait, avgstay;//ƽ���ȴ�ʱ���ƽ��ͣ��ʱ��
	n = waitminute = stayminute = 0;
	Moment end;
	end.hour = 11;
	end.minute = 0;
	auto i = Customers.begin();
	out << "���" << "\t" << "�˿�����" << "\t" << "����ʱ��" << "\t"
		"�ȴ���ʱ" << "\t" << "�Ͳ�ʱ��" << "\t" << "�Ͳ���ʱ" << "\t" << "�뿪ʱ��" << endl;
	for (;i != Customers.end();i++) {
		if (isless(end,(*i).leave)) end = (*i).leave;
		n++;
		waitminute = waitminute + (*i).wait.minute + (*i).wait.hour * 60;
		stayminute += (*i).eattime.minute;
		out.setf(ios::right);
		out.width(3);
		out.fill('0');
		out << n << "\t\t\t";
		out << (*i).number << "\t\t";
		out.width(2);
		out << (*i).arrive.hour << ":";
		out.width(2);
		out << (*i).arrive.minute << "\t\t";
		out << (*i).wait.hour << ":";
		out.width(2);
		out << (*i).wait.minute << "\t\t";
		out.width(2);
		out << (*i).starteat.hour << ":";
		out.width(2);
		out << (*i).starteat.minute << "\t\t";
		out << (*i).eattime.hour << ":";
		out.width(2);
		out << (*i).eattime.minute << "\t\t";
		out.width(2);
		out << (*i).leave.hour << ":";
		out.width(2);
		out << (*i).leave.minute << endl;
	}
	out.close();
	ofstream out_("output_data.txt");//�����Ҫ��1��2
	stayminute += waitminute;
	avgwait = (double)waitminute / n;
	avgstay = (double)stayminute / n;
	out_ << "��һ���й˿͵�ƽ����λʱ��Ϊ" << "\t" << avgwait << "����" << endl;
	out_ << "��һ���й˿͵�ƽ��ͣ��ʱ��Ϊ" << "\t" << avgstay << "����" << endl;
	out_ << "���һ���뿪����Ĺ˿͵��뿪ʱ��Ϊ" << "\t" << end.hour << ":" << end.minute << endl;
	out_.close();
}