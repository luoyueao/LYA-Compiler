#pragma once
#include "global.h" 

//使用有限状态自动机来实现功能

//删除程序中所有注释
void delzs(fstream &in, fstream &out);

//删除程序中所有多余的空格,tab以及回车
void delblank(fstream &in, fstream &out);

//消除左递归以及公共左因子
void delleftrecursion(fstream &in, fstream &out);

//将语法根据|拆分
void splitgrammar(fstream &in, fstream &out);
