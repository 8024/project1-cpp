#include "STACK.h"
#include <iostream>
#include <string.h>
#include <stdio.h>


using namespace std;
/*	S I O A C N G
*/

void initSTACK(STACK *const p, int m);		//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, const STACK &s);//��sջ��ʼ��pָ���ջ
int size(const STACK *const p);				//����pָ���ջ�����Ԫ�ظ���max
int howMany(const STACK *const p);			//����pָ���ջ��ʵ��Ԫ�ظ���pos
int getelem(const STACK *const p, int x);	//ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e);	//��e��ջ��������p
STACK *const pop(STACK *const p, int &e);	//��ջ��e��������p
STACK *const assign(STACK *const p, const STACK &s);		//��s��pָ��ջ��������p
void print(const STACK *const p, FILE *fp);			//��ջ�е�Ԫ�ش�ӡ��ָ���ļ���
void destroySTACK(STACK *const p);			//����pָ���ջ

int main(int agrc, char *agrv[]) {
	STACK stack;
	STACK *pstack = &stack;
	int get_num = NULL;
	int num_cnt = 3;			//�������������������ڵ������ַ�����ʼ������Ĭ��agrv[0]Ϊ·����agrv[1]="-S",agrv[2]=int num��֪��
	int lost_num = NULL;

	char filename[20] = "U201514496_1.txt";
	FILE *fp = fopen(filename, "w+");

	if (!strcmp("-S", agrv[1])) {
		get_num = atoi(agrv[2]);
		fprintf(fp, "%c  %d  ", 'S', get_num);
		if (!get_num) {		//��-S������Ϊ0ʱ��˵��ջ�Ĵ���������Ҫ��������
			fprintf(fp, "%c", 'E');
			fclose(fp);
			cout << "the length of stack is 0,input error!" << endl;
			return 0;
		}
		initSTACK(pstack, get_num);		//	������ʼ��ջ
		if (pstack->elems == nullptr) {
			cout << "Errors!" << endl;
			fprintf(fp, "%c", 'E');
			destroySTACK(pstack);
			fclose(fp);
			return 0;
		}
	}
	else {		//������ĵ�һ����������"-S"����������󣬽�������
		cout << "the input is wrong!" << endl;
		fclose(fp);
		cout << "the first input is wrong,errors!" << endl;
		return 0;
	}

	while (num_cnt < agrc) {
		if (!strcmp("-I", agrv[num_cnt])) {		//����ջ����
			cout << "1" << endl;
			fprintf(fp, "%c  ", 'I');
			++num_cnt;
			while ((strcmp("-I",agrv[num_cnt])&&strcmp("-O", agrv[num_cnt])&&strcmp("-A",agrv[num_cnt])&&strcmp("-C",agrv[num_cnt])&&strcmp("-N",agrv[num_cnt])&&strcmp("-G",agrv[num_cnt])) && (num_cnt < agrc - 1)) {
				get_num = atoi(agrv[num_cnt]);
				if ((pstack->max) <= pstack->pos) {	//	ջ���ʱ��ӡE������������
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
			if (num_cnt == agrc - 1) {	//	�������ӣ���ᶪʧ�������������
				get_num = atoi(agrv[num_cnt]);
				if ((pstack->max) <= pstack->pos) {	//	ջ���ʱ��ӡE������������
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
		else if (!strcmp("-A", agrv[num_cnt])) {		//	ʵ��ջ��ջ��ת��
			cout << "2" << endl;
			fprintf(fp, "%c  ", 'A');
			++num_cnt;
			get_num = atoi(agrv[num_cnt]);
			STACK stack_new_A;							//	����һ���µ�ջ��ջ�Ĵ�С��

			initSTACK(&stack_new_A, get_num);
			if (stack_new_A.elems == nullptr) {
				cout << "Errors!" << endl;
				fprintf(fp, "%c", 'E');
				destroySTACK(pstack);
				fclose(fp);
				return 0;
			}
			if (assign(&stack_new_A, *pstack) == nullptr) {			//	��ֵ����
				cout << "Errors!" << endl;
				fprintf(fp, "%c", 'E');
				destroySTACK(pstack);
				fclose(fp);
				return 0;
			};				//	����ջ�����ݿ�������ջ��
			destroySTACK(pstack);						//	���پ�ջ
			pstack = &stack_new_A;						//ͬʱ���ṹָ��ָ���µ�ջ
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
		else if (!strcmp("-O", agrv[num_cnt])) {	//��ջ
			cout << "6" << endl;
			fprintf(fp, "%c  ", 'O');
			++num_cnt;
			get_num = atoi(agrv[num_cnt]);
			for (; get_num > 0; get_num--) {
				if (pstack->pos <= 0) {		//ջ�е������Ѿ�Ϊ��ʱ����ʾ"S"����������
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
		else {			//��-S����֮�󲻷��ϱ�׼ʱ����������
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