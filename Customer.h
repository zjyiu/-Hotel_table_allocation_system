#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include"Moment.h"
#include"Table.h"
#include<vector>

class Customer {//顾客的类定义
private:
	Moment arrive;//到达时间
	Moment wait;//等待时间
	Moment starteat;//开始用餐的时间
	Moment eattime;//吃饭时长
	Moment leave;//离开时间
	int number;//顾客人数
public:
	Customer();
	friend void create(std::vector<Customer>& Customers);
	friend void handle(std::vector<Customer>& Customers, std::vector<std::vector<Table>>&Tables);
	friend void out(std::vector<Customer>& Customers);
	friend bool comp(Customer& a, Customer& b);//用于sort排序
};

void creattxt();//创建顾客信息，存到input_custome.txt中
void create(std::vector<Customer>& Customers);//创建顾客的集合，从文件中读取信息
void handle(std::vector<Customer>& Customers, std::vector<std::vector<Table>>& Tables);
//处理顾客，得到他们的时间信息
void out(std::vector<Customer>& Customers);//输出结果

#endif // !CUSTOMER_H

