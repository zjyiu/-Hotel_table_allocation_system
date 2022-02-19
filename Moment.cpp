#include"Moment.h"

//���ǵ�ʱ��Ϊ11�㵽�ڶ���2�㣬����ĺ�������11��Ϊ����
//С��11���Ϊ�ڶ��죬����11���Ϊ����

Moment addm(Moment a, Moment b) {
	int h = a.hour + b.hour;
	int m = a.minute + b.minute;
	Moment temp;
	if (m >= 60) { m = m % 60;h += 1; }
	if (h >= 24) { h = h % 24; }
	temp.hour = h;
	temp.minute = m;
	return temp;
}

Moment subm(Moment a, Moment b) {
	if (a.hour < 11) a.hour += 24;
	if (b.hour < 11) b.hour += 24;//��11��Ϊ����
	int h = a.hour - b.hour;
	int m = a.minute - b.minute;
	if (m < 0) { m += 60;h -= 1; }
	Moment temp;
	temp.hour = h;
	temp.minute = m;
	return temp;
}

bool isless(Moment a, Moment b) {
	if (a.hour >= 11 && b.hour < 11) return true;
	if (b.hour >= 11 && a.hour < 11) return false;//��11��Ϊ����
	if (a.hour < b.hour) return true;
	else if (a.hour == b.hour && a.minute < b.minute) return true;
	return false;
}