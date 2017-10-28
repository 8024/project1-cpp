#include "STACK.h"
#include <iostream>
#include <string.h>
#include <stdio.h>


using namespace std;
/*	S I O A C N G
*/

void initSTACK(STACK *const p, int m);		//初始化p指向的栈，最多m个元素
void initSTACK(STACK *const p, const STACK &s);//用s栈初始化p指向的栈
int size(const STACK *const p);				//返回p指向的栈的最大元素个数max
int howMany(const STACK *const p);			//返回p指向的栈的实际元素个数pos
int getelem(const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e);	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e);	//出栈到e，并返回p
STACK *const assign(STACK *const p, const STACK &s);		//赋s给p指的栈，并返回p
void print(const STACK *const p, FILE *fp);			//将栈中的元素打印到指定文件中
void destroySTACK(STACK *const p);			//销毁p指向的栈

int main(int agrc, char *agrv[]) {
	STACK stack;
	STACK *pstack = &stack;
	int get_num = NULL;
	int num_cnt = 3;			//由于真正的输入和输出在第三个字符串开始，所以默认agrv[0]为路径，agrv[1]="-S",agrv[2]=int num已知。
	int lost_num = NULL;

	char filename[20] = "U201514496_1.txt";
	FILE *fp = fopen(filename, "w+");

	if (!strcmp("-S", agrv[1])) {
		get_num = atoi(agrv[2]);
		fprintf(fp, "%c  %d  ", 'S', get_num);
		if (!get_num) {		//当-S的数字为0时，说明栈的创建错误，需要结束程序
			fprintf(fp, "%c", 'E');
			fclose(fp);
			cout << "the length of stack is 0,input error!" << endl;
			return 0;
		}
		initSTACK(pstack, get_num);		//	创建初始化栈
		if (pstack->elems == nullptr) {
			cout << "Errors!" << endl;
			fprintf(fp, "%c", 'E');
			destroySTACK(pstack);
			fclose(fp);
			return 0;
		}
	}
	else {		//当输入的第一个参数不是"-S"，则输入错误，结束程序
		cout << "the input is wrong!" << endl;
		fclose(fp);
		cout << "the first input is wrong,errors!" << endl;
		return 0;
	}

	while (num_cnt < agrc) {
		if (!strcmp("-I", agrv[num_cnt])) {		//输入栈数据
			cout << "1" << endl;
			fprintf(fp, "%c  ", 'I');
			++num_cnt;
			while ((strcmp("-I",agrv[num_cnt])&&strcmp("-O", agrv[num_cnt])&&strcmp("-A",agrv[num_cnt])&&strcmp("-C",agrv[num_cnt])&&strcmp("-N",agrv[num_cnt])&&strcmp("-G",agrv[num_cnt])) && (num_cnt < agrc - 1)) {
				get_num = atoi(agrv[num_cnt]);
				if ((pstack->max) <= pstack->pos) {	//	栈溢出时打印E，并结束程序
					cout << "errors!" << endl;
			//		print(pstack, fp);
					fprintf(fp, "%c", 'E');
					fclose(fp);
					destroySTACK(pstack);
					return 0;
				}
				else push(pstack, get_num);
				++num_cnt;
			}
			if (num_cnt == agrc - 1) {	//	如果不添加，则会丢失输入的最后的数据
				get_num = atoi(agrv[num_cnt]);
				if ((pstack->max) <= pstack->pos) {	//	栈溢出时打印E，并结束程序
					cout << "errors!" << endl;
					//		print(pstack, fp);
					fprintf(fp, "%c", 'E');
					fclose(fp);
					destroySTACK(pstack);
					return 0;
				}
				else push(pstack, get_num);
				++num_cnt;
			}

			print(pstack, fp);
		}
		else if (!strcmp("-A", agrv[num_cnt])) {		//	实现栈与栈的转换
			cout << "2" << endl;
			fprintf(fp, "%c  ", 'A');
			++num_cnt;
			get_num = atoi(agrv[num_cnt]);
			STACK stack_new_A;							//	创建一个新的栈，栈的大小由

			initSTACK(&stack_new_A, get_num);
			if (stack_new_A.elems == nullptr) {
				cout << "Errors!" << endl;
				fprintf(fp, "%c", 'E');
				destroySTACK(pstack);
				fclose(fp);
				return 0;
			}
			if (assign(&stack_new_A, *pstack) == nullptr) {			//	赋值操作
				cout << "Errors!" << endl;
				fprintf(fp, "%c", 'E');
				destroySTACK(pstack);
				fclose(fp);
				return 0;
			};				//	将旧栈的数据拷贝到新栈中
			destroySTACK(pstack);						//	销毁旧栈
			pstack = &stack_new_A;						//同时将结构指针指向新的栈
			print(pstack, fp);

			++num_cnt;
		}
		else if (!strcmp("-C", agrv[num_cnt])) {
			cout << "3" << endl;
			fprintf(fp, "%c  ", 'C');
			STACK stack_new_C;
			initSTACK(&stack_new_C, pstack->max);
			if (stack_new_C.elems == nullptr) {
				cout << "Errors!" << endl;
				fprintf(fp, "%c", 'E');
				destroySTACK(pstack);
				fclose(fp);
				return 0;
			}
			initSTACK(&stack_new_C, *pstack);
			if (stack_new_C.elems == nullptr) {
				cout << "Errors!" << endl;
				fprintf(fp, "%c", 'E');
				destroySTACK(pstack);
				fclose(fp);
				return 0;
			}
			destroySTACK(pstack);
			pstack = &stack_new_C;
			print(pstack, fp);

			++num_cnt;
		}
		else if (!strcmp("-N", agrv[num_cnt])) {
			cout << "4" << endl;
			fprintf(fp, "%c  ", 'N');
			fprintf(fp, "%d  ", howMany(pstack));

			++num_cnt;
		}
		else if (!strcmp("-G", agrv[num_cnt])) {
			cout << "5" << endl;
			fprintf(fp, "%c  ", 'G');
			++num_cnt;
			get_num = atoi(agrv[num_cnt]);
			if (get_num < howMany(pstack)){
				fprintf(fp, "%d  ", getelem(pstack, get_num));
			}
			else {
				cout << "Errors!" << endl;
				fprintf(fp, "%c", 'E');
				destroySTACK(pstack);
				fclose(fp);
				return 0;
			}
			++num_cnt;
		}
		else if (!strcmp("-O", agrv[num_cnt])) {	//出栈
			cout << "6" << endl;
			fprintf(fp, "%c  ", 'O');
			++num_cnt;
			get_num = atoi(agrv[num_cnt]);
			for (; get_num > 0; get_num--) {
				if (pstack->pos <= 0) {		//栈中的数据已经为空时，显示"S"，结束程序
					cout << "Errors!" << endl;
					fprintf(fp, "%c", 'E');
					destroySTACK(pstack);
					fclose(fp);
					return 0;
				}
				else pop(pstack, lost_num);
			}
			print(pstack, fp);
			++num_cnt;
		}
		else {			//当-S输入之后不符合标准时，结束程序
			cout << "the input is wrong!!" << endl;
			destroySTACK(pstack);
			fclose(fp);
			return 0;
		}
	}
	cout << "the operations are done!" << endl;
	destroySTACK(pstack);
	fclose(fp);
	return 0;
}