#pragma once
#ifndef MOMENT_H
#define MOMENT_H

struct Moment{//ʱ��Ľṹ����
	int hour;
	int minute;
};

Moment addm(Moment a, Moment b);//�ӷ�
Moment subm(Moment a, Moment b);//������a-b��
bool isless(Moment a, Moment b);//�ж�a<b

#endif // !MOMENT_H

