#pragma once
#include "global.h" 

//ʹ������״̬�Զ�����ʵ�ֹ���

//ɾ������������ע��
void delzs(fstream &in, fstream &out);

//ɾ�����������ж���Ŀո�,tab�Լ��س�
void delblank(fstream &in, fstream &out);

//������ݹ��Լ�����������
void delleftrecursion(fstream &in, fstream &out);

//���﷨����|���
void splitgrammar(fstream &in, fstream &out);
