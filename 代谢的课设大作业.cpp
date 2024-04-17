#include<stdio.h>
#include<string.h>//�����ַ��� 
#include<stdlib.h>//malloc()���� ,���ص�������void*��Ҫ��������ת��
#include<windows.h>//��������ͷ�ļ� 
#include<time.h>//���ò���ʾ��ǰʱ�� 
#include<conio.h> //�����������뺯��getch()��ͷ�ļ� 
#include <windows.h>
char password[20], key[20];//��ʼ���� 
 
void save_password(char s[]) {//���޸ĺ�����뱣�� 
	FILE* fp = fopen("password.txt", "w+");
	fprintf(fp, "%s", s);
	fclose(fp);
}
 
typedef struct Node {
	long long id;//ѧ��
	char name[50];//����
	char sex[10];//�Ա�
	int math, english, phisics, scatter, generation;
	int sum;//�ܷ�
 
	struct Node* next;
}node;
 
node List;//���� 
 
void hide_password(char* pswd, unsigned maxlen) {//��������������� 
	int index = 0;
	char buff = '\0';
 
	while ((buff = getch()) != '\r') {
		if (buff == '\b' && index != 0) {
			index--;
			printf("\b \b");
		}
		else if (index < maxlen - 1 && buff != '\b') {
			pswd[index++] = buff;
			putchar('*');
		}
	}
	pswd[index] = '\0';
}
 
int readFile(node* L) {//��ȡ�ļ� 
	FILE* fpr = fopen("score.txt", "r");
	node st;
	node* s;
	node* t = L;
	if (fpr == NULL) {
		return 0;
	}
	else {
		while (fscanf(fpr, "%lld %s %s %d %d %d %d %d %d", &st.id, st.name, st.sex, &st.math, &st.english, &st.phisics, &st.scatter, &st.generation, &st.sum) != EOF) {
			s = (node*)malloc(sizeof(node));
			*s = st;
			t->next = s;
			t = s;
			t->next = NULL;
		}
	}
	fclose(fpr);//�ر��ļ�ָ�� 
	return 1;
}
 
int saveFile(node* L) {//�����ļ�
	FILE* fpw = fopen("score.txt", "w");
	if (fpw == NULL) return 0;//���ļ�ʧ�� 
	node* p = L->next;
	while (p != NULL) {
		fprintf(fpw, "%lld %s %s %d %d %d %d %d %d\n", p->id, p->name, p->sex, p->math, p->english, p->phisics, p->scatter, p->generation, p->sum);
		p = p->next;
	}
	fclose(fpw);//�ر��ļ�ָ�� 
	return 1;
}
 


void welcome() {//���˵����� 
	system("cls");//���� 
	time_t t;
	struct tm* p;
	time(&t);
	p = gmtime(&t);

	printf("\n\n*********************���༶�ɼ�����ϵͳ���̺Ͳţ�208231030 ***************\n");	//�޸ĳ��Լ���ѧ������
	printf("**********            1��������Ϣ       **********\n");
	printf("**********            2����ʾ��Ϣ       **********\n");
	printf("**********            3��������Ϣ       **********\n");
	printf("**********            4��������Ϣ       **********\n");
	//���Ը����Լ���������ʵ�������ֻҪ������д�ļ����ܾ���
	printf("**********            5����ȡ�ļ���Ϣ   **********\n");
	printf("**********            6��ɾ����Ϣ       **********\n");
	printf("**********            0�����沢�˳�ϵͳ **********\n");

	printf("����������Ҫ���еĲ��������֣�: ");
}
 

 
void insertlist(node* L, node e) {//ͷ�巨,��ѧ����Ϣ���뵽���� 
	node* h = L;//ͷ�ڵ� 
	node* s = (node*)malloc(sizeof(node));
	*s = e;
	s->next = h->next;
	h->next = s;
	saveFile(L);
}
 
node* searchid(long long id, node* L) {//��ѧ�Ų��� 
	node* p = L;
	while (p->next != NULL) {//�������� 
		if (p->next->id == id) {
			return p;
		}
		p = p->next;
 
	}
	return NULL;
}
 
node* searchname(char name[], node* L) {//���������� 
	node* p = L;
	node* q = L;
	while (p->next != NULL) {//�������� 
		if (strcmp(name, p->next->name) == 0) {
			return p;
		}
		p = p->next;
 
	}
	return NULL;
}
 
void new_student(node* L) {//����ѧ����Ϣ 
	system("cls");
	node st;
	printf("\n\n**********��������Ϣ���̺Ͳţ�208231030 **********\n");	//�޸ĳ��Լ���ѧ������
	int choice = 0;
	while (1) {
		printf("����������ѧ�������Ϣ\n");
		printf("ѧ��(10λ��)��");
		while (1) {
			scanf("%lld", &st.id);
			node* p = searchid(st.id, L);
			if (p == NULL && st.id >= 1000000000 && st.id <= 9999999999) {
				break;
			}
			else {
				printf("��ѧ����ѧ���Ѵ��ڻ򳤶Ȳ���������������ѧ�ţ�\n");
			}
		}
		printf("����(�������Ҫ��4����)��");
		while (1) {
			scanf("%s", st.name);
			node* p = searchname(st.name, L);
			int len = strlen(st.name);
			if (p == NULL && len <= 10) {
				break;
			}
			else {
				printf("��ѧ���������Ѵ��ڻ򳤶Ȳ���������������������\n");
			}
		}
		printf("�Ա�(��|Ů)��");
		while (1) {
			scanf("%s", st.sex);
			if (strlen(st.sex) == 2) {
				break;
			}
			else {
				printf("���벻����(�Ա�ӦΪ���� / Ů)�����������Ա�\n");
			}
		}
		printf("��ѧ�ɼ�(0~100)��");
		while (1) {
			scanf("%d", &st.math);
			if (st.math >= 0 && st.math <= 100) {
				break;
			}
			else {
				printf("����ķ���������Ӧ��0~100֮�䣡������������ѧ�ɼ���\n");
			}
		}
		printf("Ӣ��ɼ�(0~100)��");
		while (1) {
			scanf("%d", &st.english);
			if (st.english >= 0 && st.english <= 100) {
				break;
			}
			else {
				printf("����ķ���������Ӧ��0~100֮�䣡����������Ӣ��ɼ���\n");
			}
		}
		printf("����ɼ�(0~100)��");
		while (1) {
			scanf("%d", &st.phisics);
			if (st.phisics >= 0 && st.phisics <= 100) {
				break;
			}
			else {
				printf("����ķ���������Ӧ��0~100֮�䣡��������������ɼ���\n");
			}
		}
		printf("��ѧ�ɼ�(0~100)��");
		while (1) {
			scanf("%d", &st.scatter);
			if (st.scatter >= 0 && st.scatter <= 100) {
				break;
			}
			else {
				printf("����ķ���������Ӧ��0~100֮�䣡���������뻯ѧ�ɼ���\n");
			}
		}
		printf("���ĳɼ�(0~100)��");
		while (1) {
			scanf("%d", &st.generation);
			if (st.generation >= 0 && st.generation <= 100) {
				break;
			}
			else {
				printf("����ķ���������Ӧ��0~100֮�䣡�������������ĳɼ���\n");
			}
		}
		st.sum = st.math + st.english + st.phisics + st.scatter + st.generation;
		insertlist(&List, st);
		printf("�Ƿ���Ҫ��������ѧ����Ϣ�����ǣ�1 / ��0��\n");
		scanf("%d", &choice);
		if (choice == 0) {
			break;
		}
	}
}
 
void deletestu(node* pr) {//ɾ��ѧ����Ϣ 
	node* s = pr->next;
	pr->next = s->next;
	s->next = NULL;
	free(s);//�ͷŽڵ�ռ� 
}
 
void delete_student(node* L) {//ɾ��ѧ����Ϣ 
	system("cls");
	long long id;
	node* p;
	printf("������ɾ��ѧ����ѧ��(10λ��)��");
	scanf("%lld", &id);
	node* st = searchid(id, L);
	p = st;
	if (st == NULL) {
		printf("���޴��ˣ�");
		return;
	}
	st = st->next;
	printf("_________________________________________________________________________________\n");
	printf("|ѧ��\t\t|����\t|�Ա�\t|��ѧ\t|Ӣ��\t|����\t|��ѧ\t|����\t|�ܷ�\t|\n");;
	printf("_________________________________________________________________________________\n");
	printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
	printf("_________________________________________________________________________________\n");
	deletestu(p);
	saveFile(L);
}
 
void modify_student(node* L) {//�޸�ѧ����Ϣ 
	system("cls");
	printf("\n\n**********��������Ϣ���̺Ͳţ�208231030 **********\n");
	int choice = -1;
	long long  id;
	printf("������Ҫ���ҵ�ѧ��ѧ��(10λ��)��");
	scanf("%lld", &id);
	node* st = searchid(id, L);
 
	if (st == NULL) {
		printf("���޴��ˣ�");
		return;
	}
	st = st->next;
	while (1) {
		system("cls");
		printf("_________________________________________________________________________________\n");
		printf("|ѧ��\t\t|����\t|�Ա�\t|��ѧ\t|Ӣ��\t|����\t|��ѧ\t|����\t|�ܷ�\t|\n");
		printf("_________________________________________________________________________________\n");
		printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
		printf("_________________________________________________________________________________\n");
		printf("\n\n*********************���༶�ɼ�����ϵͳ���̺Ͳţ�208231030 ***************\n");	//�޸ĳ��Լ���ѧ������
	printf("**********            1��������Ϣ       **********\n");
	printf("**********            2����ʾ��Ϣ       **********\n");
	printf("**********            3��������Ϣ       **********\n");
	printf("**********            4��������Ϣ       **********\n");
	//���Ը����Լ���������ʵ�������ֻҪ������д�ļ����ܾ���
	printf("**********            5����ȡ�ļ���Ϣ   **********\n");
	printf("**********            6��ɾ����Ϣ       **********\n");
	printf("**********            0�����沢�˳�ϵͳ **********\n");

		printf("������Ҫ�޸ĵ���Ϣ��");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			printf("����������(�������Ҫ����4����)��");
			while (1) {
				char newname[50];
				scanf("%s", newname);
				node* p = searchname(newname, L);
				int len = strlen(newname);
				if (p == NULL && len <= 10) {
					strcpy(st->name, newname);
					break;
				}
				else {
					printf("�������Ѵ��ڻ򳤶Ȳ���������������������\n");
				}
			}
 
			break;
		case 2:
			printf("�������Ա�(��|Ů)��");
			while (1) {
				scanf("%s", st->sex);
				if (strlen(st->sex) == 2) {
					break;
				}
				else {
					printf("���벻����(�Ա�ӦΪ���� / Ů)�����������Ա�\n");
				}
			}
			break;
		case 3:
			printf("��������ѧ�ɼ�(0~100)��");
			while (1) {
				scanf("%d", &st->math);
				if (st->math >= 0 && st->math <= 100) {
					break;
				}
				else {
					printf("����ķ���������Ӧ��0~100֮�䣡������������ѧ�ɼ���\n");
				}
			}
			break;
		case 4:
			printf("������Ӣ��ɼ�(0~100)��");
			while (1) {
				scanf("%d", &st->english);
				if (st->english >= 0 && st->english <= 100) {
					break;
				}
				else {
					printf("����ķ���������Ӧ��0~100֮�䣡����������Ӣ��ɼ���\n");
				}
			}
			break;
		case 5:
			printf("����������ɼ�(0~100)��");
			while (1) {
				scanf("%d", &st->phisics);
				if (st->phisics >= 0 && st->phisics <= 100) {
					break;
				}
				else {
					printf("����ķ���������Ӧ��0~100֮�䣡��������������ɼ���\n");
				}
			}
			break;
		case 6:
			printf("�����뻯ѧ�ɼ�(0~100)��");
			while (1) {
				scanf("%d", &st->scatter);
				if (st->scatter >= 0 && st->scatter <= 100) {
					break;
				}
				else {
					printf("����ķ���������Ӧ��0~100֮�䣡���������뻯ѧ�ɼ���\n");
				}
			}
			break;
		case 7:
			printf("���������ĳɼ�(0~100)��");
			while (1) {
				scanf("%d", &st->generation);
				if (st->generation >= 0 && st->generation <= 100) {
					break;
				}
				else {
					printf("����ķ���������Ӧ��0~100֮�䣡�������������ĳɼ���\n");
				}
			}
			break;
		}
		st->sum = st->math + st->english + st->phisics + st->scatter + st->generation;
		printf("�Ƿ�����޸ĸ�ѧ������Ϣ��(�ǣ�1/��0)\n");
		scanf("%d", &choice);
		if (choice == 0) {
			printf("�޸ĳɹ����޸ĺ��ѧ������Ϣ��ɼ����£�\n");
			break;
		}
	}
	printf("_________________________________________________________________________________\n");
	printf("|ѧ��\t\t|����\t|�Ա�\t|��ѧ\t|Ӣ��\t|����\t|��ѧ\t|����\t|�ܷ�\t|\n");
	printf("_________________________________________________________________________________\n");
	printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
	printf("_________________________________________________________________________________\n");
	saveFile(L);
}
 
void search_student(node* L) {//��ѯѧ����Ϣ 
	system("cls");
	printf("\n\n**********����ѯ��Ϣ���̺Ͳţ�208231030 **********\n");
	int choice = 0;
	long long id;
	char name[50];
	node* st;
	printf("��ѧ�Ų�ѯ----- 1\n");
	printf("��������ѯ----- 2\n");
	printf("�������ѯ��ʽ��");
	scanf("%d", &choice);
	if (choice == 1) {
		printf("������Ҫ��ѯ��ѧ��(10λ��)��");
		scanf("%lld", &id);
		st = searchid(id, L);
		if (st == NULL) {
			printf("���޴��ˣ�\n");
		}
		else {
			st = st->next;
			printf("_________________________________________________________________________________\n");
			printf("|ѧ��\t\t|����\t|�Ա�\t|��ѧ\t|Ӣ��\t|����\t|��ѧ\t|����\t|�ܷ�\t|\n");
			printf("_________________________________________________________________________________\n");
			printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
			printf("_________________________________________________________________________________\n");
		}
	}
	else if (choice == 2) {
		printf("������Ҫ��ѯ��������");
		scanf("%s", name);
		st = searchname(name, L);
		if (st == NULL) {
			printf("���޴��ˣ�\n");
		}
		else {
			st = st->next;
			printf("_________________________________________________________________________________\n");
			printf("|ѧ��\t\t|����\t|�Ա�\t|��ѧ\t|Ӣ��\t|����\t|��ѧ\t|����\t|�ܷ�\t|\n");
			printf("_________________________________________________________________________________\n");
			printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
			printf("_________________________________________________________________________________\n");
		}
	}
}
int maxscore(node* L, int mode) {//���Ҹ�����߷� 
	int max = 0;
	node* p = L->next;
	if (mode == 1) {//������߷� 
		while (p != NULL) {
			if (p->math > max) {
				max = p->math;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 2) {//Ӣ����߷� 
		while (p != NULL) {
			if (p->english > max) {
				max = p->english;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 3) {//������߷� 
		while (p != NULL) {
			if (p->phisics > max) {
				max = p->phisics;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 4) {//��ɢ��߷� 
		while (p != NULL) {
			if (p->scatter > max) {
				max = p->scatter;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 5) {//�ߴ���߷� 
		while (p != NULL) {
			if (p->generation > max) {
				max = p->generation;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 6) {//�ܷ���߷� 
		while (p != NULL) {
			if (p->sum > max) {
				max = p->sum;
			}
			p = p->next;
		}
		return max;
	}
 
}
 
bool cmp(node a, node b) {//����ȽϹ��� 
	return a.sum > b.sum;//�Ӵ�С����
}
 
void ScoreSort(node* L) {//��ѧ���ɼ��������򣬴Ӹߵ��� 
	for (node* p = L->next; p != NULL; p = p->next) {
		for (node* q = p; q != NULL; q = q->next) {
			if (!cmp(*p, *q)) {//��������������������н��� 
				//����������
				node t = *p;
				*p = *q;
				*q = t;
				//����ָ����
				t.next = p->next;
				p->next = q->next;
				q->next = t.next;
			}
		}
	}
}

 



void output_sort(node* L) {//���ѧ����Ϣ 
	system("cls");
	printf("\n\n**********����ʾ��Ϣ���̺Ͳţ�208231030 **********\n");
	ScoreSort(&List);
	node* p = L->next;
	if (p != NULL) {
		printf("_________________________________________________________________________________\n");
		printf("|ѧ��\t\t|����\t|�Ա�\t|��ѧ\t|Ӣ��\t|����\t|��ѧ\t|����\t|�ܷ�\t|\n");
		printf("_________________________________________________________________________________\n");
		while (p != NULL) {
			printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", p->id, p->name, p->sex, p->math, p->english, p->phisics, p->scatter, p->generation, p->sum);
			printf("_________________________________________________________________________________\n");;
			p = p->next;
		}
	}
	printf("��ѧ��߷֣�%d  ", maxscore(&List, 1)); printf("Ӣ����߷֣�%d\n", maxscore(&List, 2));
	printf("������߷֣�%d  ", maxscore(&List, 3)); printf("��ѧ��߷֣�%d\n", maxscore(&List, 4));
	printf("������߷֣�%d  ", maxscore(&List, 5)); printf("�ܷ���߷֣�%d\n", maxscore(&List, 6));
 
}
void output_sort1(node* L) {//
	system("cls");
	printf("\n\n**********����ȡ�ļ����̺Ͳţ�208231030 **********\n");
	ScoreSort(&List);
	node* p = L->next;
	if (p != NULL) {
		printf("_________________________________________________________________________________\n");
		printf("|ѧ��\t\t|����\t|�Ա�\t|��ѧ\t|Ӣ��\t|����\t|��ѧ\t|����\t|�ܷ�\t|\n");
		printf("_________________________________________________________________________________\n");
		jixu:
		int i=5;
		while (p != NULL) {
			if(i>0)
			{
			printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", p->id, p->name, p->sex, p->math, p->english, p->phisics, p->scatter, p->generation, p->sum);
			printf("_________________________________________________________________________________\n");;
			p = p->next;
			i--;
		}
		else{
			printf("����6�鿴��һҳ,����7�˳�");
			int i;
			scanf("%d",&i);
			if(i==6)
			{
				system("cls");
				goto jixu;
			 } 
			 else if(i==7)
			 {
			 	return;
			 }
			 else
			 {
			 	printf("��������룬�ѻص�������"); 
			 }
		}
	}

 
}
}

 void goodbye(){
 
	system("cls");
	printf("\n\n**********�������ļ����̺Ͳţ�208231030 **********\n");
	Sleep(10);
	printf("�ټ�");
	exit(0);
}

int main()//������ 
{
	int choice = 0;

	readFile(&List);//���������ȶ�ȡ�ļ�,�������֮ǰ��ĳɼ������������ 
	while (1) {
		welcome();
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			new_student(&List);//����ѧ����Ϣ 
			break;
		 
			
		case 4:
			modify_student(&List);//�޸�ѧ����Ϣ 
			break;
		case 3:
			search_student(&List);//��ѯѧ����Ϣ 
			break;
		case 2:
			output_sort(&List);//����ɼ����� 
			break;
		case 5:
			output_sort1(&List);
			break;
			case 6:
		delete_student(&List);
			break;
		case 0:
			goodbye();//��������
			break;
		}
		printf("�Ƿ���Ҫ����������(�ǣ�1/��0)\n");
		scanf("%d", &choice);
		if (choice == 0) {
			goodbye();
		}
	}
	return 0;
}
