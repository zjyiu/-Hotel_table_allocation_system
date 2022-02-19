#pragma once
#ifndef TABLE_H
#define TABLE_H

#include"Moment.h"
#include<vector>

class Table {//���ӵ��ඨ��
private:
	bool isusing;//ʹ�����
	Moment availtime;//������ڱ�ʹ�ã���ʾ�ܹ�ʹ�õ�ʱ��
public:
	Table();
	Moment gettime();
	bool getuse();//�ӿں���
	void changetime(Moment t);
	void changeuse(bool u);//�ı�˽�г�Ա�ĺ���
};

void change(std::vector<std::vector<Table>>& Tables, Moment t);
//�ú����ı�ʱ���tʱ�Ѿ�����Ͷ��ʹ�õ����ӵ�isusing����ʹ�����
bool gettable(std::vector<std::vector<Table>>& Tables, int n, int& x, int& y);
//ѡȡ���ӵĺ���������п����ӷ���true�����򷵻�false��
//û�п�����ѡ��availtime��С��һ�ţ����ӵ�λ��������x�У���Ŵ���y��
void create(std::vector<std::vector<Table>>& Tables);
//�������ӵļ��ϣ����ı��ж�ȡ��Ϣ
//Tables[i]��ʾ��i����λ�����ӵļ��ϣ�������Ϊ��i����λ�����ӵı��

#endif // !TABLE_H
