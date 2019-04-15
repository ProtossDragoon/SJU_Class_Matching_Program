/*
***This is an automatic classroom assigning program***
***Developed by team SOO. Sejong University, South Korea***

COPYRIGHTⓒ 2018-2019, SOO. All rights reserved.
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
-한글 주석 추가(코드 & 콘솔창)

V1.1.2 - 2019/03/10 - 김한주
-조건부 컴파일 관련 코드 정리
	-불필요 코드 삭제
	-콘솔창에 텍스트 포시여부 변경가능(#define TEST 0)
-콘솔창에 구조체 ri[]의 정보 출력하는 기능 추가(디버깅용) + cl[]정보 추가 출력
-계산에 걸린 시간 및 진행 상태 표시 기능(디버깅용)
-findmax함수
	-학과가 같을 경우도 고려
	-단과대, 학과가 다를 때, "공용"인 경우와 아예 다른 경우를 구별
	-인원수 비율 관련 가중치 증가(반영비율이 너무 적기 때문)
-동적할당 메모리 free() 관련 코드 수정(더 꼼꼼하게 free함)
*/

/*
//엑셀 읽는법(현재로서) : 엑셀파일 -> csv파일로 저장 -> 저장된 txt파일을 ANSI형식으로 다시 저장

*해결해야 할 것들*
1. classlist 안에 내용(이론/실습, 기자재)
2. 가중치의 문제**
3. 1,2,3 순위 입력받은 것을 어떻게 할지
4. 더 효과적인 엑셀파일 처리
5. 한 교수가 같은 수업을 2번 이상 하는 경우(우선순위에서 가져오기(?))
6. classres 종류 + classres 여러 종류 동시(?)**
7. classtype 3 -> 예외(?), 특수수업
8. 이름에 공백이 있는 교수님들(외국인 교수님들)
9. 같은 과에서는 오래된 정교수 먼저 배정하는 경우도 있다고 함(우선순위 고려)
10. 교수님들이 시간이나 인원수를 입력하지 않는 경우에는 어떻게 할 것인가
11. 시간표 타임테이블같은거 기억 안나는데 코드에 표시를 하든 명확히 기록해두기
12. 강의실의 단과대 및 학과가 2개 이상일 때 -> 무시?
13. classtype 사용? - 현재 컴퓨터실습 구분, 이론/실습 구분에만 사용
14. 데이터 많아지면 시간 겁나 오래 걸림 ㅋㅋㅋㅋㅋㅋㅋㅋㅋ
15. ablenum이 0인 경우?
*/




//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//CODE START
#define _CRT_SECURE_NO_WARNINGS


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//include header files
//헤더파일 추가
#include"myheader.h"
#include"struct_def_B.h"


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//global variables
//전역변수들
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

//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//main fn
//메인함수
int main() {


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//local variables
	//지역변수들


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//variables for reading data from txt
		//텍스트 파일에서 정보를 읽어들이기 위해 사용되는 변수들
	FILE *fp1, *fp2;
	FILE *finfp;
	char pname[21], clname[41], dname[41], coname[21], ctime1[22], ctime2[22], ctime3[22];
	int tn, tm, check, num, fday, ftime[22], fj, sc, al;
	int cday1, cday2, cday3, snum, cres, ctype;
	char dayt1[3], dayt2[3], dayt3[3], comp;
	char all[200], *pall;
	char cloc[2][5];
	

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//variables for saving day & time data as text to memory
		//요일과 시간 정보를 텍스트 형식으로 저장하기 위해 사용되는 변수들
		//ex)
		//1200-1330
		//0900-1200
	char daylist[5][3] = { "월","화","수","목","금" };
	char timestart[5], mid[2] = { "-" }, timeend[5];


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//miscellaneous variables
		//기타 변수들
	int i, j, k, c, n, l, m, q, t, u;
	int selectionnum;
	char selection;
	

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//combinine single data txt files into one(combine_files fn)
	//하나짜리의 텍스트 파일들을 하나의 텍스트 파일로 결합(combine_files함수)
	combine_files();
	

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//read data from txt + save to memory
	//텍스트 파일의 정보들을 읽어들이고 메모리에 저장

	
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//count how many classes there are from classlist.txt + allocation(cl[])
		//classlist.txt 파일에서 강의수를 세고, cl[]구조체 배열을 동적할당
	fp1 = fopen("classlist.txt", "r");
	fscanf(fp1, "%s", all);
	while (!feof(fp1)) {
		classcnt++;
		fscanf(fp1, "%s", all);
	}
	fclose(fp1);
	cl = (CL *)malloc(sizeof(CL)*(classcnt));   // 입력받은 파일 총 개수 세기 + 동적할당


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//count how many rooms there are from roominfo.txt + allocation(ri[])
		//roominfo.txt 파일에서 강의실수를 세고, ri[]구조체 배열을 동적할당
	fp2 = fopen("roominfo.txt", "r");
	fscanf(fp2, "%s", all);
	while (!feof(fp2)) {
		roomcnt++;
		fscanf(fp2, "%s", all);
	}
	fclose(fp2);
	ri = (RI *)malloc(sizeof(RI)*(roomcnt));   // 갖고있는 파일 총 개수 세기 + 동적할당


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//reset timetable for all rooms(in ri[])
		//ri[]구조체 배열에 있는 모든 강의실의 시간표를 0으로 초기화
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
		//reset timetable for all classes(in cl[])
		//cl[]구조체 배열에 있는 모든 수업의 시간표를 0으로 초기화
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
		//save data to memory(cl[] & ri[])
		//텍스트 파일의 정보들을 읽어들이고 메모리에 저장(cl[] & ri[])
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
		//(두번째 숫자가 0이면, 주 1회 수업입니다)

		//cl[i].classdaycomp1 = 0;
		//cl[i].classdaycomp2 = 0;
		//cl[i].classdaycomp3 = 0;
		for (comp = 0;comp < 22;comp++) {
			cl[i].classtimecomp1[comp] = 0;
			cl[i].classtimecomp2[comp] = 0;
			cl[i].classtimecomp3[comp] = 0;
		}
		//(this is for setting comp values to 0)
		//(comp에 해당하는 값들을 0으로 초기화하는 작업입니다)

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
	fclose(fp1);


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//find comp classes and combine them with its regular(theory) classes
		//comp값들을 찾고, 해당되는 이론수업과 결합
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
		//print all data saved to memory(for testing)
		//메모리에 저장한 정보들을 전부 출력(디버깅용)
	#if TEST
	printf("\n\n//DATA SAVED TO MEMORY(FROM ROOMINFO.TXT)");
	printf("\n//메모리에 저장된 정보들(ri구조체 배열)");
	for (i = 0;i < roomcnt;i++) {
		printf("\n%s%s %s %s %d %d", ri[i].classloc[0], ri[i].classloc[1], ri[i].collname, ri[i].deptname, ri[i].studnum, ri[i].classres);
	}

	printf("\n\n\n//DATA SAVED TO MEMORY(FROM CLASSLIST.TXT)");
	printf("\n//메모리에 저장된 정보들(cl구조체 배열)");
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
	printf("\n(* 는 컴퓨터실습이 있는 수업입니다.)");
	#endif


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//calculation + write to file
	//최대값 계산 + 파일로 출력
	//system("cls");
	
	#if TEST
	printf("\n\n\n//ABLENUM VALUES FOR EACH CLASS");
	printf("\n//각 강의에 해당되는 ablenum값들");
	for (i = 0; i < classcnt; i++) {
		//printf("cl[%d].ablenum : %d ", i, cl[i].ablenum);
		printf("\n%s : %d", cl[i].classname, cl[i].ablenum);
		ablenumtot *= cl[i].ablenum;
	}
	printf("\n(if any have a value of 0, classroom assignment is impossible.)\n");
	printf("(0인 값이 하나라도 존재하면, 강의실 배정이 불가능합니다.)\n");
	#endif

	max = (int *)malloc(classcnt * sizeof(int));
	max2 = (int *)malloc(classcnt * sizeof(int));
	max3 = (int *)malloc(classcnt * sizeof(int));


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//find_time fn(calculation)
		//find_time함수를 이용한 계산 + 시간측정
	#if TEST
	printf("\n\n//MAX-FINDING ALGORITHM\n");
	printf("//최대값 구하는 알고리즘\n");
	start = clock();
	find_time();
	finish = clock();
	printf("\n(Calculation took %.3fseconds.)\n", ((double)finish - (double)start) / 1000.0);
	printf("(최대값 계산에 %.3f초 걸렸습니다.)\n", ((double)finish - (double)start) / 1000.0);
	#endif


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//save day & time as text(to cl[])
		//cl[]에 요일과 시간 정보를 텍스트 형식으로 저장
	for (i = 0;i < classcnt;i++) {


			//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
			//day
			//요일정보
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
			//시간정보


				//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
				//1st
				//1순위
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
				//2순위
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
				//3순위
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
				//컴퓨터실습 수업


					//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
					//1st
					//1순위
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
					//2순위
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
					//3순위
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
		//결과를 콘솔창에 표시 + 텍스트 파일로 출력
	#if TEST
	printf("\n\n//MAX INDEX VALUES");
	printf("\n//최대값에 해당되는 인덱스 값들");
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
	printf("//각기다른 가중치가 적용된 결과값들\n");
	#endif

	#if TEST
	printf("단과대끼리 묶는 배치를 최우선으로 고려한 해 : \n");
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

	finfp = fopen("단과대 최우선.txt", "w");   // 최종파일에 출력
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
		fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);

	#if TEST
	printf("한 강의실당 많은 강의가 들어가 효율적인 강의실 운영을 최우선으로 고려한 해 : \n");
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

	finfp = fopen("강의수 최우선.txt", "w");   // 최종파일에 출력
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
			fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);

	#if TEST
	printf("강의실의 유휴공간 제거를 최우선으로 고려하여 인원수에 걸맞는 강의실을 최우선으로 고려한 해 : \n");
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
	//시간표를 확인할 수 있는 옵션
	#if TEST
	printf("\n//TIMETABLES\n");
	printf("//시간표 확인\n");
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


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//free variables
	//동적할당 메모리 해제
	for (i = 0;i < classcnt;i++)
		free(cl[i].ableroom);
	free(cl);
	free(ri);
	free(max);
	free(max2);
	free(max3);
	
	return 0;
}