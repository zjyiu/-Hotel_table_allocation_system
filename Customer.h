#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include"Moment.h"
#include"Table.h"
#include<vector>

class Customer {//�˿͵��ඨ��
private:
	Moment arrive;//����ʱ��
	Moment wait;//�ȴ�ʱ��
	Moment starteat;//��ʼ�ò͵�ʱ��
	Moment eattime;//�Է�ʱ��
	Moment leave;//�뿪ʱ��
	int number;//�˿�����
public:
	Customer();
	friend void create(std::vector<Customer>& Customers);
	friend void handle(std::vector<Customer>& Customers, std::vector<std::vector<Table>>&Tables);
	friend void out(std::vector<Customer>& Customers);
	friend bool comp(Customer& a, Customer& b);//����sort����
};

void creattxt();//�����˿���Ϣ���浽input_custome.txt��
void create(std::vector<Customer>& Customers);//�����˿͵ļ��ϣ����ļ��ж�ȡ��Ϣ
void handle(std::vector<Customer>& Customers, std::vector<std::vector<Table>>& Tables);
//����˿ͣ��õ����ǵ�ʱ����Ϣ
void out(std::vector<Customer>& Customers);//������

#endif // !CUSTOMER_H

