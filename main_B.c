/*
***This is an automatic classroom assigning program***
***Developed by team SOO. Sejong University, South Korea***

COPYRIGHT�� 2018-2019, SOO. All rights reserved.
*/

/*
V1.0 - 2018/12/28 - Hyeonjin Kim, Hyeyeon Choi, HanJu Kim, Janghoo Lee
-initial release

V1.1 - 2019/03/01 - HanJu Kim
-added comments(code & console) + more descriptions
-classday input : 1digit -> 1digit or 2digits
-solution to computer LAB classes(classes with a 3rd day)
-now writes day and time for classes in the final txt file
-fixed timetables not being updated after finding max values
-added an option to view timetables(only for the first max)

V1.1.1 - 2019/03/03 - Janghoo Lee, Hyunjin Kim, HanJu Kim
-added comments for struct_def_B.h
-combine_files function encapsulation for code readablity
-added struct roominfo classloc number([2][5] -> [2][6])
-optimizations for the option to view timetables
	-discards invalid inputs
	-now recognizes lower-case inputs
-�ѱ� �ּ� �߰�(�ڵ� & �ܼ�â)

V1.1.2 - 2019/03/10 - ������
-���Ǻ� ������ ���� �ڵ� ����
	-���ʿ� �ڵ� ����
	-�ܼ�â�� �ؽ�Ʈ ���ÿ��� ���氡��(#define TEST 0)
-�ܼ�â�� ����ü ri[]�� ���� ����ϴ� ��� �߰�(������) + cl[]���� �߰� ���
-��꿡 �ɸ� �ð� �� ���� ���� ǥ�� ���(������)
-findmax�Լ�
	-�а��� ���� ��쵵 ���
	-�ܰ���, �а��� �ٸ� ��, "����"�� ���� �ƿ� �ٸ� ��츦 ����
	-�ο��� ���� ���� ����ġ ����(�ݿ������� �ʹ� ���� ����)
-�����Ҵ� �޸� free() ���� �ڵ� ����(�� �Ĳ��ϰ� free��)
*/

/*
//���� �д¹�(����μ�) : �������� -> csv���Ϸ� ���� -> ����� txt������ ANSI�������� �ٽ� ����

*�ذ��ؾ� �� �͵�*
1. classlist �ȿ� ����(�̷�/�ǽ�, ������)
2. ����ġ�� ����**
3. 1,2,3 ���� �Է¹��� ���� ��� ����
4. �� ȿ������ �������� ó��
5. �� ������ ���� ������ 2�� �̻� �ϴ� ���(�켱�������� ��������(?))
6. classres ���� + classres ���� ���� ����(?)**
7. classtype 3 -> ����(?), Ư������
8. �̸��� ������ �ִ� �����Ե�(�ܱ��� �����Ե�)
9. ���� �������� ������ ������ ���� �����ϴ� ��쵵 �ִٰ� ��(�켱���� ���)
10. �����Ե��� �ð��̳� �ο����� �Է����� �ʴ� ��쿡�� ��� �� ���ΰ�
11. �ð�ǥ Ÿ�����̺����� ��� �ȳ��µ� �ڵ忡 ǥ�ø� �ϵ� ��Ȯ�� ����صα�
12. ���ǽ��� �ܰ��� �� �а��� 2�� �̻��� �� -> ����?
13. classtype ���? - ���� ��ǻ�ͽǽ� ����, �̷�/�ǽ� ���п��� ���
14. ������ �������� �ð� �̳� ���� �ɸ� ������������������
15. ablenum�� 0�� ���?
*/




//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//CODE START
#define _CRT_SECURE_NO_WARNINGS


//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//include header files
//������� �߰�
#include"myheader.h"
#include"struct_def_B.h"


//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//global variables
//����������
CL *cl;
RI *ri;
int classcnt = 0;
int roomcnt = 0;
void find_time();
void combine_files();
int *max;
double max_score = 0;
int *max2;
double max2_score = 0;
int *max3;
double max3_score = 0;

clock_t start, finish;		//for calculating duration
int progress = 0, ablenumtot = 1;		//for showing progress

//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//main fn
//�����Լ�
int main() {


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//local variables
	//����������


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//variables for reading data from txt
		//�ؽ�Ʈ ���Ͽ��� ������ �о���̱� ���� ���Ǵ� ������
	FILE *fp1, *fp2;
	FILE *finfp;
	char pname[21], clname[41], dname[41], coname[21], ctime1[22], ctime2[22], ctime3[22];
	int tn, tm, check, num, fday, ftime[22], fj, sc, al;
	int cday1, cday2, cday3, snum, cres, ctype;
	char dayt1[3], dayt2[3], dayt3[3], comp;
	char all[200], *pall;
	char cloc[2][5];
	

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//variables for saving day & time data as text to memory
		//���ϰ� �ð� ������ �ؽ�Ʈ �������� �����ϱ� ���� ���Ǵ� ������
		//ex)
		//1200-1330
		//0900-1200
	char daylist[5][3] = { "��","ȭ","��","��","��" };
	char timestart[5], mid[2] = { "-" }, timeend[5];


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//miscellaneous variables
		//��Ÿ ������
	int i, j, k, c, n, l, m, q, t, u;
	int selectionnum;
	char selection;
	

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//combinine single data txt files into one(combine_files fn)
	//�ϳ�¥���� �ؽ�Ʈ ���ϵ��� �ϳ��� �ؽ�Ʈ ���Ϸ� ����(combine_files�Լ�)
	combine_files();
	

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//read data from txt + save to memory
	//�ؽ�Ʈ ������ �������� �о���̰� �޸𸮿� ����

	
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//count how many classes there are from classlist.txt + allocation(cl[])
		//classlist.txt ���Ͽ��� ���Ǽ��� ����, cl[]����ü �迭�� �����Ҵ�
	fp1 = fopen("classlist.txt", "r");
	fscanf(fp1, "%s", all);
	while (!feof(fp1)) {
		classcnt++;
		fscanf(fp1, "%s", all);
	}
	fclose(fp1);
	cl = (CL *)malloc(sizeof(CL)*(classcnt));   // �Է¹��� ���� �� ���� ���� + �����Ҵ�


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//count how many rooms there are from roominfo.txt + allocation(ri[])
		//roominfo.txt ���Ͽ��� ���ǽǼ��� ����, ri[]����ü �迭�� �����Ҵ�
	fp2 = fopen("roominfo.txt", "r");
	fscanf(fp2, "%s", all);
	while (!feof(fp2)) {
		roomcnt++;
		fscanf(fp2, "%s", all);
	}
	fclose(fp2);
	ri = (RI *)malloc(sizeof(RI)*(roomcnt));   // �����ִ� ���� �� ���� ���� + �����Ҵ�


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//reset timetable for all rooms(in ri[])
		//ri[]����ü �迭�� �ִ� ��� ���ǽ��� �ð�ǥ�� 0���� �ʱ�ȭ
	for (k = 0; k < roomcnt; k++) {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 22; j++) {
				ri[k].classdaytime[i][j] = 0;
			}
		}
	}

	for (i = 0; i < roomcnt; i++) {
		for (j = 0; j < 5; j++) {
			for (k = 0; k < 22; k++) {
				ri[i].classdaytime[j][k] = 0;
			}
		}
		ri[i].classcnt = 0;
	}


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//reset timetable for all classes(in cl[])
		//cl[]����ü �迭�� �ִ� ��� ������ �ð�ǥ�� 0���� �ʱ�ȭ
	for (i = 0;i < classcnt;i++) {
		cl[i].classday1[0] = cl[i].classday2[0] = cl[i].classday3[0] = 0;
		cl[i].classday1[1] = cl[i].classday2[1] = cl[i].classday3[1] = 0;
		cl[i].classdaycomp1 = cl[i].classdaycomp2 = cl[i].classdaycomp3 = 0;
		
		for (j = 0;j < 22;j++) {
			cl[i].classtime1[j] = cl[i].classtime2[j] = cl[i].classtime3[j] = 0;
			cl[i].classtimecomp1[j] = cl[i].classtimecomp2[j] = cl[i].classtimecomp3[j] = 0;
		}
	}


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//save data to memory(cl[] & ri[])
		//�ؽ�Ʈ ������ �������� �о���̰� �޸𸮿� ����(cl[] & ri[])
	fp1 = fopen("classlist.txt", "r");
	fscanf(fp1, "%s", all);
	i = 0;

	while (!feof(fp1)) {
		cl[i].ablenum = 0;
		cl[i].ableroom = (RI **)malloc(sizeof(RI *)*roomcnt);
		n = 0;
		sc = 0;
		al = strlen(all);
		for (c = 0; c < al; c++) {
			if (all[c] == ',') {
				all[c] = '\0';
				if (n == 0)
					strcpy(pname, all + sc);
				else if (n == 1)
					strcpy(clname, all + sc);
				else if (n == 2)
					//cday1 = atoi(all + sc);
					strcpy(dayt1, all + sc);
				else if (n == 3)
					strcpy(ctime1, all + sc);
				else if (n == 4)
					//cday2 = atoi(all + sc);
					strcpy(dayt2, all + sc);
				else if (n == 5)
					strcpy(ctime2, all + sc);
				else if (n == 6)
					//cday3 = atoi(all + sc);
					strcpy(dayt3, all + sc);
				else if (n == 7)
					strcpy(ctime3, all + sc);
				else if (n == 8)
					snum = atoi(all + sc);
				else if (n == 9)
					strcpy(coname, all + sc);
				else if (n == 10)
					strcpy(dname, all + sc);
				else if (n == 11)
					cres = atoi(all + sc);
				sc = c + 1;
				n++;
			}
			if (n == 12)
				ctype = atoi(all + sc);
		}
		//printf("%s %s %s\n", pname, clname, ctime2);
		strcpy(cl[i].profname, pname);
		strcpy(cl[i].classname, clname);
		//cl[i].classday1 = cday1;
		//cl[i].classday2 = cday2;
		//cl[i].classday3 = cday3;
		
		cl[i].classday1[0] = dayt1[0] - '0';
		if (((dayt1[1] - '0') >= 1) && ((dayt1[1] - '0') <= 5))
			cl[i].classday1[1] = dayt1[1] - '0';
		else
			cl[i].classday1[1] = 0;
		cl[i].classday2[0] = dayt2[0] - '0';
		if (((dayt2[1] - '0') >= 1) && ((dayt2[1] - '0') <= 5))
			cl[i].classday2[1] = dayt2[1] - '0';
		else
			cl[i].classday2[1] = 0;
		cl[i].classday3[0] = dayt3[0] - '0';
		if (((dayt3[1] - '0') >= 1) && ((dayt3[1] - '0') <= 5))
			cl[i].classday3[1] = dayt3[1] - '0';
		else
			cl[i].classday3[1] = 0;
		//(if the second digit is 0, then there is only one classday for that class)
		//(�ι�° ���ڰ� 0�̸�, �� 1ȸ �����Դϴ�)

		//cl[i].classdaycomp1 = 0;
		//cl[i].classdaycomp2 = 0;
		//cl[i].classdaycomp3 = 0;
		for (comp = 0;comp < 22;comp++) {
			cl[i].classtimecomp1[comp] = 0;
			cl[i].classtimecomp2[comp] = 0;
			cl[i].classtimecomp3[comp] = 0;
		}
		//(this is for setting comp values to 0)
		//(comp�� �ش��ϴ� ������ 0���� �ʱ�ȭ�ϴ� �۾��Դϴ�)

		cl[i].classtype = ctype;
		for (j = 0; j < 22; j++)
		{
			cl[i].classtime1[j] = 0;
			cl[i].classtime2[j] = 0;
			cl[i].classtime3[j] = 0;
		}
		ctime1[4] = '\0';
		tn = (((ctime1[0] - '0') * 10 + ctime1[1] - '0') * 60 + ((ctime1[2] - '0') * 10 + ctime1[3] - '0') - 9 * 60) / 30;
		tm = (((ctime1[5] - '0') * 10 + ctime1[6] - '0') * 60 + ((ctime1[7] - '0') * 10 + ctime1[8] - '0') - (((ctime1[0] - '0') * 10 + ctime1[1] - '0') * 60 + ((ctime1[2] - '0') * 10 + ctime1[3] - '0'))) / 30;
		for (j = 0; j < tm; j++)
			cl[i].classtime1[tn + j] = 1;
		ctime2[4] = '\0';
		tn = (((ctime2[0] - '0') * 10 + ctime2[1] - '0') * 60 + ((ctime2[2] - '0') * 10 + ctime2[3] - '0') - 9 * 60) / 30;
		tm = (((ctime2[5] - '0') * 10 + ctime2[6] - '0') * 60 + ((ctime2[7] - '0') * 10 + ctime2[8] - '0') - (((ctime2[0] - '0') * 10 + ctime2[1] - '0') * 60 + ((ctime2[2] - '0') * 10 + ctime2[3] - '0'))) / 30;
		for (j = 0; j < tm; j++)
			cl[i].classtime2[tn + j] = 1;
		ctime3[4] = '\0';
		tn = (((ctime3[0] - '0') * 10 + ctime3[1] - '0') * 60 + ((ctime3[2] - '0') * 10 + ctime3[3] - '0') - 9 * 60) / 30;
		tm = (((ctime3[5] - '0') * 10 + ctime3[6] - '0') * 60 + ((ctime3[7] - '0') * 10 + ctime3[8] - '0') - (((ctime3[0] - '0') * 10 + ctime3[1] - '0') * 60 + ((ctime3[2] - '0') * 10 + ctime3[3] - '0'))) / 30;
		for (j = 0; j < tm; j++)
			cl[i].classtime3[tn + j] = 1;
		cl[i].studnum = snum;
		strcpy(cl[i].collname, coname);
		strcpy(cl[i].deptname, dname);
		cl[i].classres = cres;      // ���Ͽ��� ����ü i��°�� ������ �Ϸ�
		fp2 = fopen("roominfo.txt", "r");
		fscanf(fp2, "%s", all);
		j = 0;
		while (!feof(fp2)) {
			n = 0;
			sc = 0;
			al = strlen(all);
			for (c = 0; c < al; c++) {
				if (all[c] == ',') {
					all[c] = '\0';
					if (n == 0)
						strcpy(cloc[0], all + sc);
					else if (n == 1)
						strcpy(cloc[1], all + sc);
					else if (n == 2)
						snum = atoi(all + sc);
					else if (n == 3)
						strcpy(coname, all + sc);
					else if (n == 4)
						strcpy(dname, all + sc);
					sc = c + 1;
					n++;
				}
				if (n == 5)
					cres = atoi(all + sc);
			}
			strcpy(ri[j].classloc[0], cloc[0]);
			strcpy(ri[j].classloc[1], cloc[1]);
			ri[j].studnum = snum;
			strcpy(ri[j].collname, coname);
			strcpy(ri[j].deptname, dname);
			ri[j].classres = cres;
			check = 0;
			if ((cl[i].studnum <= ri[j].studnum)) {      // �ο��� ���� ���� ��
				if (ri[j].classres == cl[i].classres)
					check = 1;
				if (cl[i].classres == 0)   // ������ �ʿ����
					check = 1;
				if (check == 1) {      // �ο��� + ���� ���� ���� �� 
					cl[i].ableroom[cl[i].ablenum] = &ri[j];
					cl[i].ablenum++;
					//printf("%d ", cl[i].ablenum);
				}
			}
			fscanf(fp2, "%s", all);
			j++;
		}
		fclose(fp2);
		fscanf(fp1, "%s", all);
		i++;
	}
	fclose(fp1);


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//find comp classes and combine them with its regular(theory) classes
		//comp������ ã��, �ش�Ǵ� �̷м����� ����
	for (i = 0;i < classcnt;i++) {
		if (cl[i].classtype == 4) {
			cl[i - 1].classdaycomp1 = cl[i].classday1[0];
			cl[i - 1].classdaycomp2 = cl[i].classday2[0];
			cl[i - 1].classdaycomp3 = cl[i].classday3[0];
			for (j = 0;j < 22;j++) {
				cl[i - 1].classtimecomp1[j] = cl[i].classtime1[j];
				cl[i - 1].classtimecomp2[j] = cl[i].classtime2[j];
				cl[i - 1].classtimecomp3[j] = cl[i].classtime3[j];
			}
			cl[i - 1].classtype = 3;

			for (k = i;k < classcnt - 1;k++) {
				cl[k] = cl[k + 1];
			}
			classcnt--;
			realloc(cl, classcnt * sizeof(CL));
		}
	}


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//print all data saved to memory(for testing)
		//�޸𸮿� ������ �������� ���� ���(������)
	#if TEST
	printf("\n\n//DATA SAVED TO MEMORY(FROM ROOMINFO.TXT)");
	printf("\n//�޸𸮿� ����� ������(ri����ü �迭)");
	for (i = 0;i < roomcnt;i++) {
		printf("\n%s%s %s %s %d %d", ri[i].classloc[0], ri[i].classloc[1], ri[i].collname, ri[i].deptname, ri[i].studnum, ri[i].classres);
	}

	printf("\n\n\n//DATA SAVED TO MEMORY(FROM CLASSLIST.TXT)");
	printf("\n//�޸𸮿� ����� ������(cl����ü �迭)");
	for (i = 0;i < classcnt;i++) {
		if (cl[i].classdaycomp1 != 0) {
			printf("\n*%s %s %s %s %d %d %d\n", cl[i].classname, cl[i].profname, cl[i].deptname, cl[i].collname, cl[i].studnum, cl[i].classres, cl[i].classtype);
			printf("%d %d / %d , ", cl[i].classday1[0], cl[i].classday1[1], cl[i].classdaycomp1);
			for (j = 0;j < 22;j++) {
				if (cl[i].classtime1[j] == 1) {
					printf("%d ", j);
				}
			}
			printf("/ ");
			for (j = 0;j < 22;j++) {
				if (cl[i].classtimecomp1[j] == 1) {
					printf("%d ", j);
				}
			}
			printf("\n%d %d / %d , ", cl[i].classday2[0], cl[i].classday2[1], cl[i].classdaycomp2);
			for (j = 0;j < 22;j++) {
				if (cl[i].classtime2[j] == 1) {
					printf("%d ", j);
				}
			}
			printf("/ ");
			for (j = 0;j < 22;j++) {
				if (cl[i].classtimecomp2[j] == 1) {
					printf("%d ", j);
				}
			}
			printf("\n%d %d / %d , ", cl[i].classday3[0], cl[i].classday3[1], cl[i].classdaycomp3);
			for (j = 0;j < 22;j++) {
				if (cl[i].classtime3[j] == 1) {
					printf("%d ", j);
				}
			}
			printf("/ ");
			for (j = 0;j < 22;j++) {
				if (cl[i].classtimecomp3[j] == 1) {
					printf("%d ", j);
				}
			}
		}
		else {
			printf("\n%s %s %s %s %d %d %d\n", cl[i].classname, cl[i].profname, cl[i].deptname, cl[i].collname, cl[i].studnum, cl[i].classres, cl[i].classtype);
			printf("%d %d , ", cl[i].classday1[0], cl[i].classday1[1]);
			for (j = 0;j < 22;j++) {
				if (cl[i].classtime1[j] == 1) {
					printf("%d ", j);
				}
			}
			printf("\n%d %d , ", cl[i].classday2[0], cl[i].classday2[1]);
			for (j = 0;j < 22;j++) {
				if (cl[i].classtime2[j] == 1) {
					printf("%d ", j);
				}
			}
			printf("\n%d %d , ", cl[i].classday3[0], cl[i].classday3[1]);
			for (j = 0;j < 22;j++) {
				if (cl[i].classtime3[j] == 1) {
					printf("%d ", j);
				}
			}
		}
	}
	printf("\n(* computer LAB class.)");
	printf("\n(* �� ��ǻ�ͽǽ��� �ִ� �����Դϴ�.)");
	#endif


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//calculation + write to file
	//�ִ밪 ��� + ���Ϸ� ���
	//system("cls");
	
	#if TEST
	printf("\n\n\n//ABLENUM VALUES FOR EACH CLASS");
	printf("\n//�� ���ǿ� �ش�Ǵ� ablenum����");
	for (i = 0; i < classcnt; i++) {
		//printf("cl[%d].ablenum : %d ", i, cl[i].ablenum);
		printf("\n%s : %d", cl[i].classname, cl[i].ablenum);
		ablenumtot *= cl[i].ablenum;
	}
	printf("\n(if any have a value of 0, classroom assignment is impossible.)\n");
	printf("(0�� ���� �ϳ��� �����ϸ�, ���ǽ� ������ �Ұ����մϴ�.)\n");
	#endif

	max = (int *)malloc(classcnt * sizeof(int));
	max2 = (int *)malloc(classcnt * sizeof(int));
	max3 = (int *)malloc(classcnt * sizeof(int));


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//find_time fn(calculation)
		//find_time�Լ��� �̿��� ��� + �ð�����
	#if TEST
	printf("\n\n//MAX-FINDING ALGORITHM\n");
	printf("//�ִ밪 ���ϴ� �˰���\n");
	start = clock();
	find_time();
	finish = clock();
	printf("\n(Calculation took %.3fseconds.)\n", ((double)finish - (double)start) / 1000.0);
	printf("(�ִ밪 ��꿡 %.3f�� �ɷȽ��ϴ�.)\n", ((double)finish - (double)start) / 1000.0);
	#endif


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//save day & time as text(to cl[])
		//cl[]�� ���ϰ� �ð� ������ �ؽ�Ʈ �������� ����
	for (i = 0;i < classcnt;i++) {


			//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
			//day
			//��������
		strcpy(cl[i].classday1T[0], daylist[cl[i].classday1[0] - 1]);
		if (cl[i].classday1[1] != 0)
			strcpy(cl[i].classday1T[1], daylist[cl[i].classday1[1] - 1]);
		else
			strcpy(cl[i].classday1T[1], "\0");
		strcpy(cl[i].classday2T[0], daylist[cl[i].classday2[0] - 1]);
		if (cl[i].classday2[1] != 0)
			strcpy(cl[i].classday2T[1], daylist[cl[i].classday2[1] - 1]);
		else 
			strcpy(cl[i].classday2T[1], "\0");
		strcpy(cl[i].classday3T[0], daylist[cl[i].classday3[0] - 1]);
		if (cl[i].classday3[1] != 0)
			strcpy(cl[i].classday3T[1], daylist[cl[i].classday3[1] - 1]);
		else
			strcpy(cl[i].classday3T[1], "\0");
		if (cl[i].classtype == 3) {
			strcpy(cl[i].classdaycomp1T, daylist[cl[i].classdaycomp1 - 1]);
			strcpy(cl[i].classdaycomp2T, daylist[cl[i].classdaycomp2 - 1]);
			strcpy(cl[i].classdaycomp3T, daylist[cl[i].classdaycomp3 - 1]);
		}
		

			//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
			//time
			//�ð�����


				//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
				//1st
				//1����
		for (j = 0;j < 22;j++) {
			if (cl[i].classtime1[j] == 1) {
				if (cl[i].classtime1[j - 1] == 0)
					tn = j;
				if ((cl[i].classtime1[j + 1] == 0) || j==21)
					tm = j;
			}
		}
		tn = (60 * 9) + (30 * tn);
		t = tn / 60;
		u = tn % 60;
		timestart[0] = '0' + t / 10;
		timestart[1] = '0' + t % 10;
		timestart[2] = '0' + u / 10;
		timestart[3] = '0' + u % 10;
		timestart[4] = '\0';
		tm = (60 * 9) + (30 * (tm + 1));
		t = tm / 60;
		u = tm % 60;
		timeend[0] = '0' + t / 10;
		timeend[1] = '0' + t % 10;
		timeend[2] = '0' + u / 10;
		timeend[3] = '0' + u % 10;
		timeend[4] = '\0';
		cl[i].classtime1T[0] = '\0';
		strcat(cl[i].classtime1T, timestart);
		strcat(cl[i].classtime1T, mid);
		strcat(cl[i].classtime1T, timeend);


				//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
				//2nd
				//2����
		for (j = 0;j < 22;j++) {
			if (cl[i].classtime2[j] == 1) {
				if (cl[i].classtime2[j - 1] == 0)
					tn = j;
				if ((cl[i].classtime2[j + 1] == 0) || j == 21)
					tm = j;
			}
		}
		tn = (60 * 9) + (30 * tn);
		t = tn / 60;
		u = tn % 60;
		timestart[0] = '0' + t / 10;
		timestart[1] = '0' + t % 10;
		timestart[2] = '0' + u / 10;
		timestart[3] = '0' + u % 10;
		timestart[4] = '\0';
		tm = (60 * 9) + (30 * (tm + 1));
		t = tm / 60;
		u = tm % 60;
		timeend[0] = '0' + t / 10;
		timeend[1] = '0' + t % 10;
		timeend[2] = '0' + u / 10;
		timeend[3] = '0' + u % 10;
		timeend[4] = '\0';
		cl[i].classtime2T[0] = '\0';
		strcat(cl[i].classtime2T, timestart);
		strcat(cl[i].classtime2T, mid);
		strcat(cl[i].classtime2T, timeend);


				//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
				//3rd
				//3����
		for (j = 0;j < 22;j++) {
			if (cl[i].classtime3[j] == 1) {
				if (cl[i].classtime3[j - 1] == 0)
					tn = j;
				if ((cl[i].classtime3[j + 1] == 0) || j == 21)
					tm = j;
			}
		}
		tn = (60 * 9) + (30 * tn);
		t = tn / 60;
		u = tn % 60;
		timestart[0] = '0' + t / 10;
		timestart[1] = '0' + t % 10;
		timestart[2] = '0' + u / 10;
		timestart[3] = '0' + u % 10;
		timestart[4] = '\0';
		tm = (60 * 9) + (30 * (tm + 1));
		t = tm / 60;
		u = tm % 60;
		timeend[0] = '0' + t / 10;
		timeend[1] = '0' + t % 10;
		timeend[2] = '0' + u / 10;
		timeend[3] = '0' + u % 10;
		timeend[4] = '\0';
		cl[i].classtime3T[0] = '\0';
		strcat(cl[i].classtime3T, timestart);
		strcat(cl[i].classtime3T, mid);
		strcat(cl[i].classtime3T, timeend);


				//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
				//comp
				//��ǻ�ͽǽ� ����


					//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
					//1st
					//1����
		if (cl[i].classtype == 3) {
			for (j = 0;j < 22;j++) {
				if (cl[i].classtimecomp1[j] == 1) {
					if (cl[i].classtimecomp1[j - 1] == 0)
						tn = j;
					if ((cl[i].classtimecomp1[j + 1] == 0) || j == 21)
						tm = j;
				}
			}
			tn = (60 * 9) + (30 * tn);
			t = tn / 60;
			u = tn % 60;
			timestart[0] = '0' + t / 10;
			timestart[1] = '0' + t % 10;
			timestart[2] = '0' + u / 10;
			timestart[3] = '0' + u % 10;
			timestart[4] = '\0';
			tm = (60 * 9) + (30 * (tm + 1));
			t = tm / 60;
			u = tm % 60;
			timeend[0] = '0' + t / 10;
			timeend[1] = '0' + t % 10;
			timeend[2] = '0' + u / 10;
			timeend[3] = '0' + u % 10;
			timeend[4] = '\0';
			cl[i].classtimecomp1T[0] = '\0';
			strcat(cl[i].classtimecomp1T, timestart);
			strcat(cl[i].classtimecomp1T, mid);
			strcat(cl[i].classtimecomp1T, timeend);


					//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
					//2nd
					//2����
			for (j = 0;j < 22;j++) {
				if (cl[i].classtimecomp2[j] == 1) {
					if (cl[i].classtimecomp2[j - 1] == 0)
						tn = j;
					if ((cl[i].classtimecomp2[j + 1] == 0) || j == 21)
						tm = j;
				}
			}
			tn = (60 * 9) + (30 * tn);
			t = tn / 60;
			u = tn % 60;
			timestart[0] = '0' + t / 10;
			timestart[1] = '0' + t % 10;
			timestart[2] = '0' + u / 10;
			timestart[3] = '0' + u % 10;
			timestart[4] = '\0';
			tm = (60 * 9) + (30 * (tm + 1));
			t = tm / 60;
			u = tm % 60;
			timeend[0] = '0' + t / 10;
			timeend[1] = '0' + t % 10;
			timeend[2] = '0' + u / 10;
			timeend[3] = '0' + u % 10;
			timeend[4] = '\0';
			cl[i].classtimecomp2T[0] = '\0';
			strcat(cl[i].classtimecomp2T, timestart);
			strcat(cl[i].classtimecomp2T, mid);
			strcat(cl[i].classtimecomp2T, timeend);


					//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
					//3rd
					//3����
			for (j = 0;j < 22;j++) {
				if (cl[i].classtimecomp3[j] == 1) {
					if (cl[i].classtimecomp3[j - 1] == 0)
						tn = j;
					if ((cl[i].classtimecomp3[j + 1] == 0) || j == 21)
						tm = j;
				}
			}
			tn = (60 * 9) + (30 * tn);
			t = tn / 60;
			u = tn % 60;
			timestart[0] = '0' + t / 10;
			timestart[1] = '0' + t % 10;
			timestart[2] = '0' + u / 10;
			timestart[3] = '0' + u % 10;
			timestart[4] = '\0';
			tm = (60 * 9) + (30 * (tm + 1));
			t = tm / 60;
			u = tm % 60;
			timeend[0] = '0' + t / 10;
			timeend[1] = '0' + t % 10;
			timeend[2] = '0' + u / 10;
			timeend[3] = '0' + u % 10;
			timeend[4] = '\0';
			cl[i].classtimecomp3T[0] = '\0';
			strcat(cl[i].classtimecomp3T, timestart);
			strcat(cl[i].classtimecomp3T, mid);
			strcat(cl[i].classtimecomp3T, timeend);			
		}
	}


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//print result on screen + save result via txt
		//����� �ܼ�â�� ǥ�� + �ؽ�Ʈ ���Ϸ� ���
	#if TEST
	printf("\n\n//MAX INDEX VALUES");
	printf("\n//�ִ밪�� �ش�Ǵ� �ε��� ����");
	printf("\nmax_idx : ");
	for (i = 0; i < classcnt; i++) {
		printf("%d ", max[i]);
	}
	printf("\nmax2_idx : ");
	for (i = 0; i < classcnt; i++) {
		printf("%d ", max2[i]);
	}
	printf("\nmax3_idx : ");
	for (i = 0; i < classcnt; i++) {
		printf("%d ", max3[i]);
	}
	#endif

	#if TEST
	printf("\n\n\n//RESULTS BASED ON DIFFERENT PRIORITIES\n");
	printf("//����ٸ� ����ġ�� ����� �������\n");
	#endif

	#if TEST
	printf("�ܰ��볢�� ���� ��ġ�� �ֿ켱���� ����� �� : \n");
	#endif
	for (i = 0; i < classcnt; i++) {
		strcpy(cl[i].classloc[0], cl[i].ableroom[max[i]]->classloc[0]);
		strcpy(cl[i].classloc[1], cl[i].ableroom[max[i]]->classloc[1]);
	}

	#if TEST
	for (i = 0; i < classcnt; i++) {
		if (cl[i].classtype == 3)
			printf("%s , %s , %s%s%s/%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classdaycomp1T, cl[i].classtimecomp1T, cl[i].classloc[0], cl[i].classloc[1]);
		else
			printf("%s , %s , %s%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classloc[0], cl[i].classloc[1]);
	}
	printf("\n");
	#endif

	finfp = fopen("�ܰ��� �ֿ켱.txt", "w");   // �������Ͽ� ���
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
		fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);

	#if TEST
	printf("�� ���ǽǴ� ���� ���ǰ� �� ȿ������ ���ǽ� ��� �ֿ켱���� ����� �� : \n");
	#endif
	for (i = 0; i < classcnt; i++) {
		strcpy(cl[i].classloc[0], cl[i].ableroom[max2[i]]->classloc[0]);
		strcpy(cl[i].classloc[1], cl[i].ableroom[max2[i]]->classloc[1]);
	}

	#if TEST
	for (i = 0; i < classcnt; i++) {
		if (cl[i].classtype == 3)
			printf("%s , %s , %s%s%s/%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classdaycomp1T, cl[i].classtimecomp1T, cl[i].classloc[0], cl[i].classloc[1]);
		else
			printf("%s , %s , %s%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classloc[0], cl[i].classloc[1]);
	}
	printf("\n");
	#endif

	finfp = fopen("���Ǽ� �ֿ켱.txt", "w");   // �������Ͽ� ���
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
			fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);

	#if TEST
	printf("���ǽ��� ���ް��� ���Ÿ� �ֿ켱���� ����Ͽ� �ο����� �ɸ´� ���ǽ��� �ֿ켱���� ����� �� : \n");
	#endif
	for (i = 0; i < classcnt; i++) {
		strcpy(cl[i].classloc[0], cl[i].ableroom[max3[i]]->classloc[0]);
		strcpy(cl[i].classloc[1], cl[i].ableroom[max3[i]]->classloc[1]);
	}

	#if TEST
	for (i = 0; i < classcnt; i++) {
		if (cl[i].classtype == 3)
			printf("%s , %s , %s%s%s/%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classdaycomp1T, cl[i].classtimecomp1T, cl[i].classloc[0], cl[i].classloc[1]);
		else
			printf("%s , %s , %s%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classloc[0], cl[i].classloc[1]);
	}
	printf("\n");
	#endif

	finfp = fopen("�ο��� �ֿ켱.txt", "w");   // �������Ͽ� ���
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
			fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//option to view the timetable
	//�ð�ǥ�� Ȯ���� �� �ִ� �ɼ�
	#if TEST
	printf("\n//TIMETABLES\n");
	printf("//�ð�ǥ Ȯ��\n");
	for (;;) {
		printf("Would you like to view the timetables? (Y/N) ");
		scanf("%c", &selection);getchar();
		if (selection == 'Y' || selection == 'y') {
			j = 0;
			for (;;) {
				for (;;) {
					printf("\nSelect which classroom you would like to view\n");
					for (i = 0;i < roomcnt;i++) {
						printf("%2d. %s%s\t", i + 1, ri[i].classloc[0], ri[i].classloc[1]);
						j++;
						if (j % 7 == 0)
							printf("\n");
					}
					if (j % 7 != 0)
						printf("\n");
					scanf("%d", &selectionnum);getchar();
					if ((selectionnum >= 1) && (selectionnum <= roomcnt))
						break;
				}
				printf("\n%s%s\n",ri[selectionnum - 1].classloc[0], ri[selectionnum - 1].classloc[1]);
				for (k = 0;k < 5;k++) {
					for (l = 0;l < 22;l++) {
						printf("%d ", ri[selectionnum - 1].classdaytime_max[k][l]);
					}
					printf("\n");
				}
				for (;;) {
					printf("\nWould you like to view another one? (Y/N) ");
					scanf("%c", &selection);getchar();
					if (selection == 'Y' || selection == 'y')
						break;
					else if (selection == 'N' || selection == 'n')
						break;
					else
						continue;
				}
				if (selection == 'Y' || selection == 'y')
					continue;
				else
					break;
			}
			if (selection != 'Y' && selection != 'y')
				break;
		}
		else if (selection == 'N' || selection == 'n')
			break;
		else
			continue;
	}
	#endif


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//free variables
	//�����Ҵ� �޸� ����
	for (i = 0;i < classcnt;i++)
		free(cl[i].ableroom);
	free(cl);
	free(ri);
	free(max);
	free(max2);
	free(max3);
	
	return 0;
}