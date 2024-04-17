#include<stdio.h>
#include<string.h>//操作字符串 
#include<stdlib.h>//malloc()函数 ,反回的类型是void*，要进行类型转换
#include<windows.h>//清屏函数头文件 
#include<time.h>//调用并显示当前时间 
#include<conio.h> //隐藏密码输入函数getch()的头文件 
#include <windows.h>
char password[20], key[20];//初始密码 
 
void save_password(char s[]) {//将修改后的密码保存 
	FILE* fp = fopen("password.txt", "w+");
	fprintf(fp, "%s", s);
	fclose(fp);
}
 
typedef struct Node {
	long long id;//学号
	char name[50];//姓名
	char sex[10];//性别
	int math, english, phisics, scatter, generation;
	int sum;//总分
 
	struct Node* next;
}node;
 
node List;//链表 
 
void hide_password(char* pswd, unsigned maxlen) {//隐藏密码进行输入 
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
 
int readFile(node* L) {//读取文件 
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
	fclose(fpr);//关闭文件指针 
	return 1;
}
 
int saveFile(node* L) {//保存文件
	FILE* fpw = fopen("score.txt", "w");
	if (fpw == NULL) return 0;//打开文件失败 
	node* p = L->next;
	while (p != NULL) {
		fprintf(fpw, "%lld %s %s %d %d %d %d %d %d\n", p->id, p->name, p->sex, p->math, p->english, p->phisics, p->scatter, p->generation, p->sum);
		p = p->next;
	}
	fclose(fpw);//关闭文件指针 
	return 1;
}
 


void welcome() {//主菜单界面 
	system("cls");//清屏 
	time_t t;
	struct tm* p;
	time(&t);
	p = gmtime(&t);

	printf("\n\n*********************【班级成绩管理系统】晏和才，208231030 ***************\n");	//修改成自己的学号姓名
	printf("**********            1：输入信息       **********\n");
	printf("**********            2：显示信息       **********\n");
	printf("**********            3：查找信息       **********\n");
	printf("**********            4：更新信息       **********\n");
	//可以根据自己的设计做适当调整，只要包含读写文件功能就行
	printf("**********            5：读取文件信息   **********\n");
	printf("**********            6：删除信息       **********\n");
	printf("**********            0：保存并退出系统 **********\n");

	printf("请输入你想要进行的操作（数字）: ");
}
 

 
void insertlist(node* L, node e) {//头插法,将学生信息插入到链表 
	node* h = L;//头节点 
	node* s = (node*)malloc(sizeof(node));
	*s = e;
	s->next = h->next;
	h->next = s;
	saveFile(L);
}
 
node* searchid(long long id, node* L) {//按学号查找 
	node* p = L;
	while (p->next != NULL) {//遍历链表 
		if (p->next->id == id) {
			return p;
		}
		p = p->next;
 
	}
	return NULL;
}
 
node* searchname(char name[], node* L) {//按姓名查找 
	node* p = L;
	node* q = L;
	while (p->next != NULL) {//遍历链表 
		if (strcmp(name, p->next->name) == 0) {
			return p;
		}
		p = p->next;
 
	}
	return NULL;
}
 
void new_student(node* L) {//增加学生信息 
	system("cls");
	node st;
	printf("\n\n**********【输入信息】晏和才，208231030 **********\n");	//修改成自己的学号姓名
	int choice = 0;
	while (1) {
		printf("请输入新增学生相关信息\n");
		printf("学号(10位数)：");
		while (1) {
			scanf("%lld", &st.id);
			node* p = searchid(st.id, L);
			if (p == NULL && st.id >= 1000000000 && st.id <= 9999999999) {
				break;
			}
			else {
				printf("该学生的学号已存在或长度不合理！请重新输入学号！\n");
			}
		}
		printf("姓名(中文最长不要超4个字)：");
		while (1) {
			scanf("%s", st.name);
			node* p = searchname(st.name, L);
			int len = strlen(st.name);
			if (p == NULL && len <= 10) {
				break;
			}
			else {
				printf("该学生的姓名已存在或长度不合理！请重新输入姓名！\n");
			}
		}
		printf("性别(男|女)：");
		while (1) {
			scanf("%s", st.sex);
			if (strlen(st.sex) == 2) {
				break;
			}
			else {
				printf("输入不合理！(性别应为：男 / 女)请重新输入性别！\n");
			}
		}
		printf("数学成绩(0~100)：");
		while (1) {
			scanf("%d", &st.math);
			if (st.math >= 0 && st.math <= 100) {
				break;
			}
			else {
				printf("输入的分数不合理！应在0~100之间！请重新输入数学成绩！\n");
			}
		}
		printf("英语成绩(0~100)：");
		while (1) {
			scanf("%d", &st.english);
			if (st.english >= 0 && st.english <= 100) {
				break;
			}
			else {
				printf("输入的分数不合理！应在0~100之间！请重新输入英语成绩！\n");
			}
		}
		printf("物理成绩(0~100)：");
		while (1) {
			scanf("%d", &st.phisics);
			if (st.phisics >= 0 && st.phisics <= 100) {
				break;
			}
			else {
				printf("输入的分数不合理！应在0~100之间！请重新输入物理成绩！\n");
			}
		}
		printf("化学成绩(0~100)：");
		while (1) {
			scanf("%d", &st.scatter);
			if (st.scatter >= 0 && st.scatter <= 100) {
				break;
			}
			else {
				printf("输入的分数不合理！应在0~100之间！请重新输入化学成绩！\n");
			}
		}
		printf("语文成绩(0~100)：");
		while (1) {
			scanf("%d", &st.generation);
			if (st.generation >= 0 && st.generation <= 100) {
				break;
			}
			else {
				printf("输入的分数不合理！应在0~100之间！请重新输入语文成绩！\n");
			}
		}
		st.sum = st.math + st.english + st.phisics + st.scatter + st.generation;
		insertlist(&List, st);
		printf("是否需要继续输入学生信息？（是：1 / 否：0）\n");
		scanf("%d", &choice);
		if (choice == 0) {
			break;
		}
	}
}
 
void deletestu(node* pr) {//删除学生信息 
	node* s = pr->next;
	pr->next = s->next;
	s->next = NULL;
	free(s);//释放节点空间 
}
 
void delete_student(node* L) {//删除学生信息 
	system("cls");
	long long id;
	node* p;
	printf("请输入删除学生的学号(10位数)：");
	scanf("%lld", &id);
	node* st = searchid(id, L);
	p = st;
	if (st == NULL) {
		printf("查无此人！");
		return;
	}
	st = st->next;
	printf("_________________________________________________________________________________\n");
	printf("|学号\t\t|姓名\t|性别\t|数学\t|英语\t|物理\t|化学\t|语文\t|总分\t|\n");;
	printf("_________________________________________________________________________________\n");
	printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
	printf("_________________________________________________________________________________\n");
	deletestu(p);
	saveFile(L);
}
 
void modify_student(node* L) {//修改学生信息 
	system("cls");
	printf("\n\n**********【更新信息】晏和才，208231030 **********\n");
	int choice = -1;
	long long  id;
	printf("请输入要查找的学生学号(10位数)：");
	scanf("%lld", &id);
	node* st = searchid(id, L);
 
	if (st == NULL) {
		printf("查无此人！");
		return;
	}
	st = st->next;
	while (1) {
		system("cls");
		printf("_________________________________________________________________________________\n");
		printf("|学号\t\t|姓名\t|性别\t|数学\t|英语\t|物理\t|化学\t|语文\t|总分\t|\n");
		printf("_________________________________________________________________________________\n");
		printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
		printf("_________________________________________________________________________________\n");
		printf("\n\n*********************【班级成绩管理系统】晏和才，208231030 ***************\n");	//修改成自己的学号姓名
	printf("**********            1：输入信息       **********\n");
	printf("**********            2：显示信息       **********\n");
	printf("**********            3：查找信息       **********\n");
	printf("**********            4：更新信息       **********\n");
	//可以根据自己的设计做适当调整，只要包含读写文件功能就行
	printf("**********            5：读取文件信息   **********\n");
	printf("**********            6：删除信息       **********\n");
	printf("**********            0：保存并退出系统 **********\n");

		printf("请输入要修改的信息：");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			printf("请输入姓名(中文最长不要超过4个字)：");
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
					printf("该姓名已存在或长度不合理！请重新输入姓名！\n");
				}
			}
 
			break;
		case 2:
			printf("请输入性别(男|女)：");
			while (1) {
				scanf("%s", st->sex);
				if (strlen(st->sex) == 2) {
					break;
				}
				else {
					printf("输入不合理！(性别应为：男 / 女)请重新输入性别！\n");
				}
			}
			break;
		case 3:
			printf("请输入数学成绩(0~100)：");
			while (1) {
				scanf("%d", &st->math);
				if (st->math >= 0 && st->math <= 100) {
					break;
				}
				else {
					printf("输入的分数不合理！应在0~100之间！请重新输入数学成绩！\n");
				}
			}
			break;
		case 4:
			printf("请输入英语成绩(0~100)：");
			while (1) {
				scanf("%d", &st->english);
				if (st->english >= 0 && st->english <= 100) {
					break;
				}
				else {
					printf("输入的分数不合理！应在0~100之间！请重新输入英语成绩！\n");
				}
			}
			break;
		case 5:
			printf("请输入物理成绩(0~100)：");
			while (1) {
				scanf("%d", &st->phisics);
				if (st->phisics >= 0 && st->phisics <= 100) {
					break;
				}
				else {
					printf("输入的分数不合理！应在0~100之间！请重新输入物理成绩！\n");
				}
			}
			break;
		case 6:
			printf("请输入化学成绩(0~100)：");
			while (1) {
				scanf("%d", &st->scatter);
				if (st->scatter >= 0 && st->scatter <= 100) {
					break;
				}
				else {
					printf("输入的分数不合理！应在0~100之间！请重新输入化学成绩！\n");
				}
			}
			break;
		case 7:
			printf("请输入语文成绩(0~100)：");
			while (1) {
				scanf("%d", &st->generation);
				if (st->generation >= 0 && st->generation <= 100) {
					break;
				}
				else {
					printf("输入的分数不合理！应在0~100之间！请重新输入语文成绩！\n");
				}
			}
			break;
		}
		st->sum = st->math + st->english + st->phisics + st->scatter + st->generation;
		printf("是否继续修改该学生的信息？(是：1/否：0)\n");
		scanf("%d", &choice);
		if (choice == 0) {
			printf("修改成功！修改后该学生的信息与成绩如下：\n");
			break;
		}
	}
	printf("_________________________________________________________________________________\n");
	printf("|学号\t\t|姓名\t|性别\t|数学\t|英语\t|物理\t|化学\t|语文\t|总分\t|\n");
	printf("_________________________________________________________________________________\n");
	printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
	printf("_________________________________________________________________________________\n");
	saveFile(L);
}
 
void search_student(node* L) {//查询学生信息 
	system("cls");
	printf("\n\n**********【查询信息】晏和才，208231030 **********\n");
	int choice = 0;
	long long id;
	char name[50];
	node* st;
	printf("按学号查询----- 1\n");
	printf("按姓名查询----- 2\n");
	printf("请输入查询方式：");
	scanf("%d", &choice);
	if (choice == 1) {
		printf("请输入要查询的学号(10位数)：");
		scanf("%lld", &id);
		st = searchid(id, L);
		if (st == NULL) {
			printf("查无此人！\n");
		}
		else {
			st = st->next;
			printf("_________________________________________________________________________________\n");
			printf("|学号\t\t|姓名\t|性别\t|数学\t|英语\t|物理\t|化学\t|语文\t|总分\t|\n");
			printf("_________________________________________________________________________________\n");
			printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
			printf("_________________________________________________________________________________\n");
		}
	}
	else if (choice == 2) {
		printf("请输入要查询的姓名：");
		scanf("%s", name);
		st = searchname(name, L);
		if (st == NULL) {
			printf("查无此人！\n");
		}
		else {
			st = st->next;
			printf("_________________________________________________________________________________\n");
			printf("|学号\t\t|姓名\t|性别\t|数学\t|英语\t|物理\t|化学\t|语文\t|总分\t|\n");
			printf("_________________________________________________________________________________\n");
			printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", st->id, st->name, st->sex, st->math, st->english, st->phisics, st->scatter, st->generation, st->sum);
			printf("_________________________________________________________________________________\n");
		}
	}
}
int maxscore(node* L, int mode) {//查找各科最高分 
	int max = 0;
	node* p = L->next;
	if (mode == 1) {//高数最高分 
		while (p != NULL) {
			if (p->math > max) {
				max = p->math;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 2) {//英语最高分 
		while (p != NULL) {
			if (p->english > max) {
				max = p->english;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 3) {//大物最高分 
		while (p != NULL) {
			if (p->phisics > max) {
				max = p->phisics;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 4) {//离散最高分 
		while (p != NULL) {
			if (p->scatter > max) {
				max = p->scatter;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 5) {//线代最高分 
		while (p != NULL) {
			if (p->generation > max) {
				max = p->generation;
			}
			p = p->next;
		}
		return max;
	}
	else if (mode == 6) {//总分最高分 
		while (p != NULL) {
			if (p->sum > max) {
				max = p->sum;
			}
			p = p->next;
		}
		return max;
	}
 
}
 
bool cmp(node a, node b) {//排序比较规则 
	return a.sum > b.sum;//从大到小排序
}
 
void ScoreSort(node* L) {//将学生成绩进行排序，从高到低 
	for (node* p = L->next; p != NULL; p = p->next) {
		for (node* q = p; q != NULL; q = q->next) {
			if (!cmp(*p, *q)) {//如果不符合排序规则则进行交换 
				//交换数据域
				node t = *p;
				*p = *q;
				*q = t;
				//交换指针域
				t.next = p->next;
				p->next = q->next;
				q->next = t.next;
			}
		}
	}
}

 



void output_sort(node* L) {//输出学生信息 
	system("cls");
	printf("\n\n**********【显示信息】晏和才，208231030 **********\n");
	ScoreSort(&List);
	node* p = L->next;
	if (p != NULL) {
		printf("_________________________________________________________________________________\n");
		printf("|学号\t\t|姓名\t|性别\t|数学\t|英语\t|物理\t|化学\t|语文\t|总分\t|\n");
		printf("_________________________________________________________________________________\n");
		while (p != NULL) {
			printf("|%lld\t|%s\t|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", p->id, p->name, p->sex, p->math, p->english, p->phisics, p->scatter, p->generation, p->sum);
			printf("_________________________________________________________________________________\n");;
			p = p->next;
		}
	}
	printf("数学最高分：%d  ", maxscore(&List, 1)); printf("英语最高分：%d\n", maxscore(&List, 2));
	printf("物理最高分：%d  ", maxscore(&List, 3)); printf("化学最高分：%d\n", maxscore(&List, 4));
	printf("语文最高分：%d  ", maxscore(&List, 5)); printf("总分最高分：%d\n", maxscore(&List, 6));
 
}
void output_sort1(node* L) {//
	system("cls");
	printf("\n\n**********【读取文件】晏和才，208231030 **********\n");
	ScoreSort(&List);
	node* p = L->next;
	if (p != NULL) {
		printf("_________________________________________________________________________________\n");
		printf("|学号\t\t|姓名\t|性别\t|数学\t|英语\t|物理\t|化学\t|语文\t|总分\t|\n");
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
			printf("输入6查看下一页,输入7退出");
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
			 	printf("错误的输入，已回到主界面"); 
			 }
		}
	}

 
}
}

 void goodbye(){
 
	system("cls");
	printf("\n\n**********【保存文件】晏和才，208231030 **********\n");
	Sleep(10);
	printf("再见");
	exit(0);
}

int main()//主函数 
{
	int choice = 0;

	readFile(&List);//进入程序后先读取文件,少了这句之前存的成绩都不能输出来 
	while (1) {
		welcome();
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			new_student(&List);//增加学生信息 
			break;
		 
			
		case 4:
			modify_student(&List);//修改学生信息 
			break;
		case 3:
			search_student(&List);//查询学生信息 
			break;
		case 2:
			output_sort(&List);//输出成绩排名 
			break;
		case 5:
			output_sort1(&List);
			break;
			case 6:
		delete_student(&List);
			break;
		case 0:
			goodbye();//结束程序
			break;
		}
		printf("是否需要继续操作？(是：1/否：0)\n");
		scanf("%d", &choice);
		if (choice == 0) {
			goodbye();
		}
	}
	return 0;
}
