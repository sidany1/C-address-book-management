#include"PhoneList.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void PhoneListInit(PL* pl) {
	memset(pl->Name, 0, sizeof(pl->Name));
	memset(pl->TeleNum , 0, sizeof(pl->TeleNum ));
	pl->Size = 0;

}//初始化

void PhoneListPush(PL* pl,char **name, char **tele_num,int cal_num) {
	for (int j = 0; j < cal_num; j++) {
		strcpy_s(pl->Name[pl->Size], name[j]);
		strcpy_s(pl->TeleNum[pl->Size], tele_num[j]);
		pl->Size++;
	}
}//插入

void PhoneListPop(PL* pl,char PopName[]) {

	int num=0;
	do {
		if (PopName == pl->Name[num]) {
			goto out;
		}
		num++;
	} while (num<pl->Size );
	printf("查询失败\n");
	return ;
	out:
	for (int i = num; i < pl->Size; i++) {
		strcpy_s(pl->Name[i - 1],pl->Name[i]);
		strcpy_s(pl->TeleNum[ i - 1], pl->TeleNum [i]);
	}
		
		pl->Size--;
}//删除

void PhoneListPrintf(PL* pl, int numBegin, int numEnd) {
	if (numEnd<numBegin) {
		printf("数据输入错误\n");
		return;
	}
	else if (numEnd > pl->Size) {
		numEnd = pl->Size;
	}
	else if (numBegin < 0||numEnd < 0) {
		printf("begin输入错误\n");
		return;
	}
	else if (numBegin > pl->Size) {
		numBegin = pl->Size;
	}

	for (int j = numBegin; j < numEnd; j++) {
		printf("%d.", j+1);
		printf("%s\t", pl->Name[j]);
		printf("%s\n", pl->TeleNum[j]);
	}
}//打印



void PhoneListFind(PL*pl,char FindName[],int Nwidth) {
	int num = 0;
	for (num = 0;num<pl->Size ; num++) {//C语言中数组与数组之间是无法直接判断相等的
		for (int i = 0; i < Nwidth; i++) {
			if (FindName[i] != pl->Name[num][i]) 
				break;
			
			if (i ==(Nwidth - 1)) 
				goto out;
			
		}

	}
	printf("查询失败\n");
	return;
out:
	printf("%s\t", pl->Name[num]);
	printf("%s\n", pl->TeleNum[num]);

}//查找



void PhonrListSaveAs(PL* pl) {
	FILE* fp;
	fopen_s(&fp,"PhoneList.txt", "w");
	if (fp == NULL) {
		printf("文件创建/打开失败\n");
		return ;
	}
	for (int i = 0; i < pl->Size; i++) {
	fprintf(fp, "%s\t", pl->Name[i]);
	fprintf(fp, "%s\n", pl->TeleNum[i]);
	}

	fclose(fp);
}//另存为

void PhoneListImport(PL* pl){//导入文件数据
	FILE* fp;
	int place;//文件总字节数
	char a;
	fopen_s(&fp, "PhoneList.txt", "r");
	if (fp == NULL) {
		printf("文件打开失败");
		return;
	}

	fseek(fp, 0l, SEEK_END);//把光标移到文件末尾
	place = ftell(fp);//得到文件总字节数（当前位置）
	fseek(fp, 0l, SEEK_SET);//移回来



while (place!=ftell(fp)){//将姓名与电话分别输入数组
		
		for (int j = 0; a = fgetc(fp)!= '\t'; j++) {
			if (a < 0) {
				pl->Name[pl->Size][j] = a;
				pl->Name[pl->Size][j++] = fgetc(fp);
			}
			printf("%s",pl->Name[pl->Size]);
			pl->Name[pl->Size][j] = a;
			a = fgetc(fp);
		}
		a = fgetc(fp);
		for (int j = 0; a != '\n',a!=EOF; j++) {
			pl->TeleNum[pl->Size][j] = a;
			a = fgetc(fp);
		}
		pl->Size++;
	}

	fclose(fp);
}