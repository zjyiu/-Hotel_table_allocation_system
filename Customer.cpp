#include"Customer.h"
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<iostream>

using namespace std;

Customer::Customer(){//构造函数
	eattime.hour = 0;
}

void creattxt() {
	ofstream out("input_customer.txt");
	srand((unsigned)time(NULL));
	int n = 99 + rand() % 901;
	vector<int> as;
	vector<int> ahs;
	vector<int> ams;//三个集合储存已经生成的顾客信息
	for (int i = 0;i < n;i++) {
		int a = 1 + rand() % 8;//顾客人数设定1到8个人
		int ah = 11 + rand() % 14;//规定凌晨1点开始不接待客人
		int am = rand() % 60;
		int e = 5 + rand() % 26;//设定顾客用餐时间为5到30分钟
		bool ext = false;
		for (int j = 0;j < i;j++)//比较生成的信息是否存在重复
			if (as[j] == a && ahs[j] == ah && ams[j] == am) { ext = true;break; }
		if (ext) { i--;continue; }
		as.push_back(a);ahs.push_back(ah);ams.push_back(am); 
		out << a << "\t" << ah % 24 << "\t" << am << "\t" << e << endl;
	}
	out.close();
}

void create(vector<Customer>& Customers) {/。/读取储存顾客信息
	creattxt();
	ifstream in("input_customer.txt");
	while (in.peek() != EOF) {
		Customer temp;
		in >> temp.number >> temp.arrive.hour >> temp.arrive.minute >> temp.eattime.minute;
		Customers.push_back(temp);
	}
	in.close();
}

bool comp(Customer& a, Customer& b) {//sort中的comp函数
	if (isless(a.arrive, b.arrive)) return true;
	if (a.arrive.hour == b.arrive.hour && a.arrive.minute == b.arrive.minute && a.number < b.number)
		return true;
	return false;
}

void handle(vector<Customer>& Customers, vector<vector<Table>>& Tables) {
	sort(Customers.begin(), Customers.end(), comp);//排序
	for (auto i = Customers.begin();i != Customers.end();i++) {
		change(Tables, (*i).arrive);//更新桌子信息
		int p, q;
		if (gettable(Tables, (*i).number, p, q)) {//有空桌子的情况
			(*i).starteat = (*i).arrive;
			(*i).wait.hour = (*i).wait.minute = 0;
			(*i).leave = addm((*i).starteat, (*i).eattime);
			Tables[p][q].changeuse(true);//更新桌子信息
			Tables[p][q].changetime((*i).leave);
		}
		else {//没有空桌子的情况
			Moment temp = Tables[p][q].gettime();
			(*i).wait = subm(temp, (*i).arrive);
			(*i).starteat = addm((*i).arrive, (*i).wait);
			(*i).leave = addm((*i).starteat, (*i).eattime);
			Tables[p][q].changetime((*i).leave);//更新桌子信息
		}
	}
}

void out(vector<Customer>& Customers) {
	ofstream out("output_customer.txt");//先输出要求3，即顾客的信息
	int n, waitminute, stayminute;//存储编号、等待时间和停留时间
	double avgwait, avgstay;//平均等待时间和平均停留时间
	n = waitminute = stayminute = 0;
	Moment end;
	end.hour = 11;
	end.minute = 0;
	auto i = Customers.begin();
	out << "编号" << "\t" << "顾客人数" << "\t" << "到来时刻" << "\t"
		"等待用时" << "\t" << "就餐时刻" << "\t" << "就餐用时" << "\t" << "离开时刻" << endl;
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
	ofstream out_("output_data.txt");//再输出要求1和2
	stayminute += waitminute;
	avgwait = (double)waitminute / n;
	avgstay = (double)stayminute / n;
	out_ << "这一天中顾客的平均等位时间为" << "\t" << avgwait << "分钟" << endl;
	out_ << "这一天中顾客的平均停留时间为" << "\t" << avgstay << "分钟" << endl;
	out_ << "最后一组离开饭店的顾客的离开时间为" << "\t" << end.hour << ":" << end.minute << endl;
	out_.close();
}