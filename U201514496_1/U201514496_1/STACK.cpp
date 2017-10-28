#include "STACK.h"
#include<iostream>

using namespace std;
void initSTACK(STACK *const p, int m) {		//��ʼ��pָ���ջ��mΪԪ��������ֵ
	p->elems = (int*)(malloc(sizeof(int)*m));			//Ϊ�µ�ջ�����ڴ�
	if (p->elems == nullptr) {
		cout << "NO enough memory for a new STACK!" << endl;
		p->max = 0;
		p->pos = 0;
	}
	else {
		p->max = m;
		p->pos = 0;
	}
}

void destroySTACK(STACK *const p) {					//����pָ���ջ
	if (p->elems != nullptr) {
		free(p->elems);
	}
	p->max = 0;
	p->pos = 0;
}

void initSTACK(STACK *const p, const STACK &s) {//��sջ��ʼ��pָ���ջ
	destroySTACK(p);
	p->elems = (int*)(malloc(sizeof(int)*s.max));		//Ϊ�µ�ջ�����ڴ�
	if (p->elems == nullptr) {
		cout << "NO enough memory for a new STACK" << endl;
		p->max = 0;
		p->pos = 0;
	}
	else {
		p->max = s.max;
		p->pos = s.pos;
		for (int cnt_num = 0; cnt_num < p->max; cnt_num++) {
			p->elems[cnt_num] = s.elems[cnt_num];
		}
	}
}

int size(const STACK *const p) {				//����pָ���ջ�����Ԫ�ظ���max
	return p->max;
}

int howMany(const STACK *const p) {				//����pָ���ջ��ʵ�ʸ���pos
	return p->pos;
}

int getelem(const STACK *const p, int x) {		//ȡ�±�x����ջԪ��
	int get_elem;
	get_elem = p->elems[x];
	return get_elem;
}

STACK *const push(STACK *const p, int e) {		//��e��ջ��������p
	p->elems[p->pos] = e;
	p->pos++;
	return p;
}

STACK *const pop(STACK *const p, int &e) {		//��ջ��e��������p
	e = p->elems[p->pos];
	p->pos--;
	return p;
}

STACK *const assign(STACK *const p, const STACK &s) {//��s��pָ��ջ��������p
	destroySTACK(p);
	p->elems = (int*)(malloc(sizeof(int)*s.max));
	if (p->elems == nullptr) {
		cout << "NO enough memory for a new STACK!!" << endl;
		return nullptr;
	}
	p->max = s.max;
	p->pos = s.pos;
	for (int cnt_assi = 0; cnt_assi < p->pos; cnt_assi++) {
		p->elems[cnt_assi] = s.elems[cnt_assi];
	}
	return p;
}

void print(const STACK *const p, FILE *fp) {					//��ջ�е��ļ���ӡ��ָ�����ļ���
	for (int cnt_pri = 0; cnt_pri < p->pos; cnt_pri++) {
		fprintf(fp, "%d  ", p->elems[cnt_pri]);
	}
}

