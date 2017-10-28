#include "STACK.h"
#include<iostream>

using namespace std;
void initSTACK(STACK *const p, int m) {		//初始化p指向的栈，m为元素最大个数值
	p->elems = (int*)(malloc(sizeof(int)*m));			//为新的栈申请内存
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

void destroySTACK(STACK *const p) {					//销毁p指向的栈
	if (p->elems != nullptr) {
		free(p->elems);
	}
	p->max = 0;
	p->pos = 0;
}

void initSTACK(STACK *const p, const STACK &s) {//用s栈初始化p指向的栈
	destroySTACK(p);
	p->elems = (int*)(malloc(sizeof(int)*s.max));		//为新的栈申请内存
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

int size(const STACK *const p) {				//返回p指向的栈的最大元素个数max
	return p->max;
}

int howMany(const STACK *const p) {				//返回p指向的栈的实际个数pos
	return p->pos;
}

int getelem(const STACK *const p, int x) {		//取下标x处的栈元素
	int get_elem;
	get_elem = p->elems[x];
	return get_elem;
}

STACK *const push(STACK *const p, int e) {		//将e入栈，并返回p
	p->elems[p->pos] = e;
	p->pos++;
	return p;
}

STACK *const pop(STACK *const p, int &e) {		//出栈到e，并返回p
	e = p->elems[p->pos];
	p->pos--;
	return p;
}

STACK *const assign(STACK *const p, const STACK &s) {//赋s给p指的栈，并返回p
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

void print(const STACK *const p, FILE *fp) {					//将栈中的文件打印到指定的文件中
	for (int cnt_pri = 0; cnt_pri < p->pos; cnt_pri++) {
		fprintf(fp, "%d  ", p->elems[cnt_pri]);
	}
}

