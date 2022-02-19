#pragma once
#ifndef MOMENT_H
#define MOMENT_H

struct Moment{//时间的结构定义
	int hour;
	int minute;
};

Moment addm(Moment a, Moment b);//加法
Moment subm(Moment a, Moment b);//减法（a-b）
bool isless(Moment a, Moment b);//判断a<b

#endif // !MOMENT_H

