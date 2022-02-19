#pragma once
#ifndef TABLE_H
#define TABLE_H

#include"Moment.h"
#include<vector>

class Table {//桌子的类定义
private:
	bool isusing;//使用情况
	Moment availtime;//如果正在被使用，表示能够使用的时间
public:
	Table();
	Moment gettime();
	bool getuse();//接口函数
	void changetime(Moment t);
	void changeuse(bool u);//改变私有成员的函数
};

void change(std::vector<std::vector<Table>>& Tables, Moment t);
//该函数改变时间点t时已经可以投入使用的桌子的isusing，即使用情况
bool gettable(std::vector<std::vector<Table>>& Tables, int n, int& x, int& y);
//选取桌子的函数，如果有空桌子返回true，否则返回false。
//没有空桌子选择availtime最小的一张，桌子的位置数存在x中，编号存在y中
void create(std::vector<std::vector<Table>>& Tables);
//创建桌子的集合，从文本中读取信息
//Tables[i]表示有i个座位的桌子的集合，其索引为有i个座位的桌子的编号

#endif // !TABLE_H
