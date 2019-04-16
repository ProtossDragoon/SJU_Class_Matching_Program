/*
***This is an automatic classroom assigning program***
***Developed by team SOO. Sejong University, South Korea***

COPYRIGHTⓒ 2018-2019, SOO. All rights reserved.
*/

/*
V1.0 - 2018/12/28 - Hyeonjin Kim, Hyeyeon Choi, Hanjoo Kim, Janghoo Lee 
-initial release

V1.1 - 2019/03/01 - Hanjoo Kim
-added comments(code & screen) + more descriptions
-classday input : 1digit -> 1digit or 2digits
-solution to computer LAB classes(classes with a 3rd day)
-now writes day and time for classes in the final txt file
-fixed timetables not being updated after finding max values
-added an option to view timetables(only for the first max)

V1.1.1 - 2019/03/03 - Janghoo Lee
-added Korean comments(code) + more Korean descriptions
*/




//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//CODE START
#define _CRT_SECURE_NO_WARNINGS


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//include header files
#ifndef MYHEADER_H
#include"myheader.h"
#endif

#ifdef VERSION_B
#include"struct_def_B.h"


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//global variables
CL *cl;
RI *ri;
int classcnt = 0;
int roomcnt = 0;
void find_time();
int *max;
double max_score = 0;
int *max2;
double max2_score = 0;
int *max3;
double max3_score = 0; 
#endif


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//main fn
int main() {


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//local variables


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//variables for reading data from txt
	FILE *fp1, *fp2;
	FILE *finfp;
	char pname[21], clname[41], dname[41], coname[21], ctime1[22], ctime2[22], ctime3[22];
	int tn, tm, check, num, fday, ftime[22], fj, sc, al;
	int cday1, cday2, cday3, snum, cres, ctype;
	char dayt1[3], dayt2[3], dayt3[3], comp;
	char all[200], *pall;
	char cloc[2][5];
	

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//variables for combining single data txt files into one
		//알고리즘 설명 : 우선 파일의 갯수가 몇개 있는지 판별. 9999개까지 읽기가능.
		//				이름을 모두 조각내서 하나씩 붙이고 다시 붙여 파일 이름을 읽어들임
		//				강의실배정, ,(,N,),.txt 를 접합하는 방식
		//				만들어낸 파일 이름으로 파일을 열고 내용물을 읽어들여 하나의 txt 파일로 접합
		//ex)
		//강의실배정.txt
		//강의실배정 (1).txt
		//강의실배정 (2).txt

	int fi, fk;
	int findone = 0; //일의자리수 판단하는 int.
	int name_count = 0;
	char name_default[12] = { "강의실배정" };
	char name_opendoor[3] = { " (" };
	char name_number[5] = { 0 };
	char name_closedoor[2] = { ")" };
	char name_txt[5] = { ".txt" };
	char name_final[25] = { 0 };
	char read_tmp[150];
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//variables for saving day & time data as text to memory
		//ex)
		//1200-1330
		//0900-1200
	char daylist[5][3] = { "월","화","수","목","금" };
	char timestart[5], mid[2] = { "-" }, timeend[5];


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//miscellaneous variables
	int i, j, k, c, n, l, m, q, t, u;
	int selectionnum;
	char selection;
	

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//combinine single data txt files into one
	printf("//SINGLE TXT FILES THAT WERE READ AND COMBINED INTO ONE\n");

	fp_write = fopen("classlist.txt", "w");
	fclose(fp_write);
	fp_write = fopen("classlist.txt", "a");

	while (1) {
		strcpy(name_final, name_default);

		if (name_count >= 1) {
			strcat(name_final, name_opendoor);

			if (name_count >= 1000) { //1248
				name_number[0] = name_count / 1000 % 10 + '0';
				name_number[1] = name_count / 100 % 10 + '0';
				name_number[2] = name_count / 10 % 10 + '0';
				name_number[3] = name_count % 10 + '0';
			}
			else if (name_count >= 100) {
				name_number[0] = name_count / 100 % 10 + '0';
				name_number[1] = name_count / 10 % 10 + '0';
				name_number[2] = name_count % 10 + '0';
			}
			else if (name_count >= 10) {
				name_number[0] = name_count / 10 % 10 + '0';
				name_number[1] = name_count % 10 + '0';
			}
			else {
				name_number[0] = name_count + '0';
			}
			strcat(name_final, name_number);
			strcat(name_final, name_closedoor);
		}

		strcat(name_final, name_txt); //.txt

		fp_read = fopen(name_final, "r");
		if (fp_read == NULL) break;

		printf("%s\n", name_final);
		for (fi = 0; fi < strlen(name_final); fi++) {
			name_final[fi] = 0;
		}

		fscanf(fp_read, "%s", read_tmp);
		fclose(fp_read);

		fprintf(fp_write, "%s\n", read_tmp);

		name_count++;

	}
	fclose(fp_write);
	
	
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//read data from txt + save to memory

	
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//count how many classes there are from classlist.txt + allocation
	fp1 = fopen("classlist.txt", "r");
	fscanf(fp1, "%s", all);
	while (!feof(fp1)) {
		classcnt++;
		fscanf(fp1, "%s", all);
	}
	fclose(fp1);
	cl = (CL *)malloc(sizeof(CL)*(classcnt));   // 입력받은 파일 총 개수 세기 + 동적할당


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//count how many rooms there are from roominfo.txt + allocation
	fp2 = fopen("roominfo.txt", "r");
	fscanf(fp2, "%s", all);
	while (!feof(fp2)) {
		roomcnt++;
		fscanf(fp2, "%s", all);
	}
	fclose(fp2);
	ri = (RI *)malloc(sizeof(RI)*(roomcnt));   // 갖고있는 파일 총 개수 세기 + 동적할당


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//reset timetable for all rooms(in RI[])
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


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//reset timetable for all classes(in CL[])
	for (i = 0;i < classcnt;i++) {
		cl[i].classday1[0] = cl[i].classday2[0] = cl[i].classday3[0] = 0;
		cl[i].classday1[1] = cl[i].classday2[1] = cl[i].classday3[1] = 0;
		cl[i].classdaycomp1 = cl[i].classdaycomp2 = cl[i].classdaycomp3 = 0;
		
		for (j = 0;j < 22;j++) {
			cl[i].classtime1[j] = cl[i].classtime2[j] = cl[i].classtime3[j] = 0;
			cl[i].classtimecomp1[j] = cl[i].classtimecomp2[j] = cl[i].classtimecomp3[j] = 0;
		}
	}


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//save data to memory(to CL[])
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

		//cl[i].classdaycomp1 = 0;
		//cl[i].classdaycomp2 = 0;
		//cl[i].classdaycomp3 = 0;
		for (comp = 0;comp < 22;comp++) {
			cl[i].classtimecomp1[comp] = 0;
			cl[i].classtimecomp2[comp] = 0;
			cl[i].classtimecomp3[comp] = 0;
		}
		//(this is for setting comp values to 0)

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
		cl[i].classres = cres;      // 파일에서 구조체 i번째꺼 꺼내기 완료
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
			if ((cl[i].studnum <= ri[j].studnum)) {      // 인원수 조건 부합 시
				if (ri[j].classres == cl[i].classres)
					check = 1;
				if (cl[i].classres == 0)   // 기자재 필요없음
					check = 1;
				if (check == 1) {      // 인원수 + 자재 조건 부합 시 
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


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//find comp classes and combine them with its regular(theory) classes
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


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//print all data saved to memory(from classlixt.txt)(for testing)
	printf("\n\n//ALL DATA SAVED TO MEMORY(FROM CLASSLIST.TXT)");
	for (i = 0;i < classcnt;i++) {
		if (cl[i].classdaycomp1 != 0) {
			printf("\n*%s %s %s %s %d\n", cl[i].classname, cl[i].profname, cl[i].deptname, cl[i].collname, cl[i].classtype);
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
			printf("\n%s %s %s %s %d\n", cl[i].classname, cl[i].profname, cl[i].deptname, cl[i].collname, cl[i].classtype);
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


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//calculation + write to file
	//system("cls");
	
	printf("\n\n\n//ABLENUM VALUES FOR EACH CLASS");
	for (i = 0; i < classcnt; i++) {
		//printf("cl[%d].ablenum : %d ", i, cl[i].ablenum);
		printf("\n%s : %d", cl[i].classname, cl[i].ablenum);
	}
	printf("\n(if any have a value of 0, classroom assignment is impossible.)\n");

	max = (int *)malloc(classcnt * sizeof(int));
	max2 = (int *)malloc(classcnt * sizeof(int));
	max3 = (int *)malloc(classcnt * sizeof(int));


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//find_time fn(calculation)
	find_time();


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//save day & time as text(to CL[])
	for (i = 0;i < classcnt;i++) {


			//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
			//day
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
		

			//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
			//time


				//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
				//1st
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


				//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
				//2nd
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


				//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
				//3rd
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


				//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
				//comp


					//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
					//1st
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


			//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
			//2nd
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


			//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
			//3rd
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


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//print result on screen + save result via txt
	printf("\n\n//MAX INDEX VALUES");
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
	printf("\n");


	printf("\n\n//RESULTS BASED ON DIFFERENT PRIORITIES\n");
	printf("단과대끼리 묶는 배치를 최우선으로 고려한 해 : \n");
	for (i = 0; i < classcnt; i++) {
		strcpy(cl[i].classloc[0], cl[i].ableroom[max[i]]->classloc[0]);
		strcpy(cl[i].classloc[1], cl[i].ableroom[max[i]]->classloc[1]);
	}

	for (i = 0; i < classcnt; i++) {
		if (cl[i].classtype == 3)
			printf("%s , %s , %s%s%s/%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classdaycomp1T, cl[i].classtimecomp1T, cl[i].classloc[0], cl[i].classloc[1]);
		else
			printf("%s , %s , %s%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classloc[0], cl[i].classloc[1]);
	}
	printf("\n");

	finfp = fopen("단과대 최우선.txt", "w");   // 최종파일에 출력
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
		fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);


	printf("한 강의실당 많은 강의가 들어가 효율적인 강의실 운영을 최우선으로 고려한 해 : \n");
	for (i = 0; i < classcnt; i++) {
		strcpy(cl[i].classloc[0], cl[i].ableroom[max2[i]]->classloc[0]);
		strcpy(cl[i].classloc[1], cl[i].ableroom[max2[i]]->classloc[1]);
	}

	for (i = 0; i < classcnt; i++) {
		if (cl[i].classtype == 3)
			printf("%s , %s , %s%s%s/%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classdaycomp1T, cl[i].classtimecomp1T, cl[i].classloc[0], cl[i].classloc[1]);
		else
			printf("%s , %s , %s%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classloc[0], cl[i].classloc[1]);
	}
	printf("\n");

	finfp = fopen("강의수 최우선.txt", "w");   // 최종파일에 출력
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
			fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);


	printf("강의실의 유휴공간 제거를 최우선으로 고려하여 인원수에 걸맞는 강의실을 최우선으로 고려한 해 : \n");
	for (i = 0; i < classcnt; i++) {
		strcpy(cl[i].classloc[0], cl[i].ableroom[max3[i]]->classloc[0]);
		strcpy(cl[i].classloc[1], cl[i].ableroom[max3[i]]->classloc[1]);
	}

	for (i = 0; i < classcnt; i++) {
		if (cl[i].classtype == 3)
			printf("%s , %s , %s%s%s/%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classdaycomp1T, cl[i].classtimecomp1T, cl[i].classloc[0], cl[i].classloc[1]);
		else
			printf("%s , %s , %s%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classloc[0], cl[i].classloc[1]);
	}
	printf("\n");

	finfp = fopen("인원수 최우선.txt", "w");   // 최종파일에 출력
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
			fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//option to view the timetable
	printf("\n//TIMETABLES\n");
	for (;;) {
		printf("Would you like to view the timetables? (Y/N) ");
		scanf("%c", &selection);getchar();
		if (selection == 'Y') {
			j = 0;
			for (;;) {
				printf("\nSelect which classroom you would like to view\n");
				for (i = 0;i < roomcnt;i++) {
					printf("%2d. %s%s\t", i + 1, ri[i].classloc[0], ri[i].classloc[1]);
					j++;
					if (j % 7 == 0)
						printf("\n");
				}
				scanf("%d", &selectionnum);getchar();
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
					if (selection == 'Y')
						break;
					else if (selection == 'N')
						break;
					else
						continue;
				}
				if (selection == 'Y')
					continue;
				else
					break;
			}
			if (selection == 'N')
				break;
		}
		else if (selection == 'N')
			break;
		else
			continue;
	}


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//close FILE + free variables
	fclose(fp1);
	free(cl);
	free(ri);
	
	return 0;
}


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//엑셀 읽는법(현재로서) : 엑셀파일 -> csv파일로 저장 -> 저장된 txt파일을 ANSI형식으로 다시 저장

//해결해야 할 것들
//1. classlist 안에 내용(이론/실습, 기자재)
//2. 가중치의 문제
//3. 1,2,3 순위 입력받은 것을 어떻게 할지
//4. 한 교수가 같은 수업을 2번 이상 하는 경우(우선순위에서 가져오기(?))
//5. free() more precisely
//6. classres 종류
//7. classtype 3 -> 예외(?), 특수수업