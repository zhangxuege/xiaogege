#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 5
typedef int ElemType;
typedef struct student{
	char name[20];
	char code[20];
	int math;
	int C;
	int English;
	struct student* next;
}stu;
//初始化链表
stu* initList()
{
	stu *head=(stu*)malloc(sizeof(stu));
	head->next=NULL;
	return head;
}

//在指定位置添加数据
int insertNode(stu *L,int pos)
{
	stu *p=L;	//node指向头节点
	int i=0;
	while(i<pos-1)
	{
		p=p->next;
		i++;
		if(p==NULL)
		{
			return 0;
		}
	}
	stu *q=(stu*)malloc(sizeof(stu));
	scanf("%s%s%d%d%d",q->name,q->code,&q->math,&q->C,&q->English);
	q->next=p->next;
	p->next=q;
	return 1;
}
//找到尾节点
stu *get_tail(stu *L)
{
	stu *p=L;
	while(p->next!=NULL)
	{
		p=p->next;
	} 
	return p;
}
//添加数据
stu *insertTail(stu *tail)	
{
	stu *p=(stu*)malloc(sizeof(stu));
	scanf("%s%s%d%d%d",p->name,p->code,&p->math,&p->C,&p->English);
	tail->next=p;	//node指向下一个节点
	p->next=NULL;
	return p;
}
//删除节点数据
int deleteNode(stu *L,int pos)
{
	if(L == NULL || pos < 1) 
	{
	    printf("删除失败：头结点为空或位置错误\n");
	    return 0;
	}
	stu *p=L;	//p为头节点	node指向的节点不变
	int i=0;
	//遍历链表，找到要删除节点的前驱。
	while(i<pos-1)
	{
		p=p->next;
		i++;
		if(p==NULL)
		{
			return 0;
		}
	}
	if(p->next==NULL)
	{
		printf("要删除的位置错误\n");
		return 0;
	}
	stu *q=p->next;
	p->next=q->next;
	free(q);
	return 1;
}



// 辅助函数：获取指定课程的成绩
int getScore(stu *s, const char *course) 
{
    if(strcmp(course, "math") == 0) return s->math;
    else if(strcmp(course, "C") == 0) return s->C;
    else if(strcmp(course, "English") == 0) return s->English;
    else if(strcmp(course, "总分") == 0) return s->math + s->C + s->English;
    else return -1; // 无效课程
}

// 格形式打印链表
void printListTable(stu *L)
{
    stu *p = L->next;			//node指向的节点不变
    if(p == NULL) {
        printf("链表为空！\n");
        return;
    }
    // 打印表头
    printf("+----------------+----------------+--------+--------+----------+--------+\n");
    printf("| 姓名           | 学号           | 数学   | C语言  | 英语     | 总分   |\n");
    printf("+----------------+----------------+--------+--------+----------+--------+\n");
    // 打印数据行
    while(p != NULL) {
        int total = p->math + p->C + p->English;
        printf("| %-14s | %-14s | %6d | %6d | %8d | %6d |\n",
               p->name, p->code, p->math, p->C, p->English, total);
        p = p->next;
    }
    printf("+----------------+----------------+--------+--------+----------+--------+\n");
}

// 冒泡排序（指定课程+升降序）
void bubbleSort(stu *L, const char *course, int order) 
{
    if(L == NULL || L->next == NULL || L->next->next == NULL) {
        printf("无需排序（链表为空或只有一个节点）\n");
        return;
    }

    // 计算链表长度
    int len = 0;
    stu *count_p = L->next;			//node指向的节点不变
    while(count_p != NULL) {
        len++;
        count_p = count_p->next;
    }

    // 冒泡排序核心
    stu *p, *q;
    for(int i=0; i<len-1; i++) {
        p = L->next;
        q = p->next;
        for(int j=0; j<len-1-i; j++) {
            int score_p = getScore(p, course);
            int score_q = getScore(q, course);
            
            // order=0：升序，order=1：降序
            int needSwap = 0;
            if(order == 0 && score_p > score_q) needSwap = 1;
            if(order == 1 && score_p < score_q) needSwap = 1;

            if(needSwap) {
                // 交换节点内容
                char temp_name[20], temp_code[20];
                int temp_math, temp_C, temp_English;
                strcpy(temp_name, p->name);
                strcpy(temp_code, p->code);
                temp_math = p->math;
                temp_C = p->C;
                temp_English = p->English;

                strcpy(p->name, q->name);
                strcpy(p->code, q->code);
                p->math = q->math;
                p->C = q->C;
                p->English = q->English;

                strcpy(q->name, temp_name);
                strcpy(q->code, temp_code);
                q->math = temp_math;
                q->C = temp_C;
                q->English = temp_English;
            }
            p = q;
            q = q->next;
        }
    }
    printf("冒泡排序完成！\n");
}
int main()
{
	int n=N;
	stu *node=initList();
	FILE *fp=NULL;
	if((fp=fopen("text.txt","w"))==NULL)
	{
		perror("打开文件失败");
		return 1;
	}
	//学生信息数据
	stu *tail=get_tail(node);
	for(int i=0;i<n;i++)
	{
		stu* newcode=insertTail(tail);
		if (newcode == NULL) 
		{
		    printf("第%d个学生插入失败，终止输入\n", i+1);
		}
		fwrite(newcode,sizeof(stu),1,fp);
		tail=newcode;
	}
	char ider01[3];
	printf("是否修改学生信息：\n");
	scanf("%s",ider01);
	if(strcmp(ider01,"是")==0){
		for(int i=0;;i++)
		{
			char a[10];
			int b,f=0;
			printf("请输入进行的操作(增加数据/删除数据/修改数据/信息查询/保存)");
			scanf("%s",a);
			if(!strcmp(a,"增加数据"))
				b=1;
			else if(!strcmp(a,"删除数据"))
				b=2;
			else if(!strcmp(a,"修改数据"))
				b=3;
			else if(!strcmp(a,"信息查询"))
				b=4;
			else if(!strcmp(a,"保存"))
				b=5;
			switch (b) 
			{
				case 1:
					{
						int pos;
						printf("请输入增加数据的位置：\n");
						scanf("%d",&pos);
						insertNode(node,pos);
						n++;
					}
					break;
				case 2:
					{
						int pos;
						printf("请输入删除数据的位置：\n");
						scanf("%d",&pos);
						deleteNode(node,pos);
						n--;
					}
					break;
			case 3:
				{
					int pos;
					printf("请输入修改数据的位置：\n");
					scanf("%d",&pos);
					deleteNode(node,pos);
					insertNode(node,pos);
				}
					break;
				case 4:
					{
						char b[20];
						int flag=0;
							printf("请输入要查询的信息：\n");
							scanf("%s",b);
							stu* newcode=node;
							for(int i=0;i<n;i++)
							{
								if(strcmp(b,newcode->name)==0)
									flag=1;
								if(strcmp(b,newcode->code)==0)
									flag=1;
								if(flag==1)	
								{
									printf("姓名：%s 学号：%s 数学：%d C：%d 英语：%d\n",newcode->name,newcode->code,newcode->math,newcode->C,newcode->English);
									break;
								}
								newcode=newcode->next;
							}
					}
					break;
				case 5:
					f=1;
					break;
			}
			if(f==1)
				break;
		}
	}
	//排序
	char ider[3];
	printf("是否排序后输出：\n");
	scanf("%s",ider);
	if(strcmp(ider,"是")==0)
	{
		char course[10];
		char paixu[5];
		int order;
		printf("请输入课程名：\n");
		scanf("%s",course);
		printf("请选择降序或升序：\n");
		scanf("%s",paixu);
		order=!strcmp(paixu,"降序");
		bubbleSort(node,course,order) ;
		printListTable(node);
	}
	//重新存入
	if((fp=fopen("text.txt","w"))==NULL)
		{
			perror("打开文件失败");
			return 1;
		}
	fwrite(node,sizeof(stu),1,fp);
	//成绩统计
	char course[10];
	int min,max;
	printf("请输入课程名称及分数区间：\n");
	scanf("%s%d-%d",course,&min,&max);
	stu *new=node;
	int num=0;
	for(int i=0;i<n;i++)
	{
		stu *p=new;
		if(strcmp(course,"math")==0)
		{
			if(p->math>=min&&p->math<=max)
			{
				printf("姓名%s 学号%s\n",p->name,p->code);
				num++;
			}					
							
		}
		if(strcmp(course,"C")==0)
		{
			if(p->C>=min&&p->C<=max)
			{
				printf("姓名%s 学号%s\n",p->name,p->code);
				num++;
			}									
		}
		if(strcmp(course,"English")==0)
		{
			if(p->English>=min&&p->English<=max)
			{
				printf("姓名%s 学号%s\n",new->name,new->code);
				num++;
			}											
		}
		new=new->next;
		p=new;
		
	}
	printf("总人数：%d",num);
	fclose(fp);
	return 0;
}
