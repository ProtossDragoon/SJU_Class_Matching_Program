//CODE START
#define _CRT_SECURE_NO_WARNINGS


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//include header files
//헤더 파일을 include 합니다.
#include"myheader.h"
#include"struct_def_B.h"


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//include external variables
//외부 참조 변수를 정의합니다.
extern CL *cl;
extern RI *ri;
extern int classcnt;
extern int roomcnt;
extern int *max;
extern double max_score;
extern int *max2;
extern double max2_score;
extern int *max3;
extern double max3_score;

extern int progress, ablenumtot;


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//global variables and functions for this source file
//전역변수와 이 소스파일 내의 함수원형을 선언(extern)합니다.
void find_real_able_room(int cnt, int j);
void savepairs(int *arr);
void findmax(int *arr);
int *arr;


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//find_time fn
//find_time 함수입니다. 소스파일의 제목과는 상관이 없습니다.
//find_time 함수의 기능 ::
void find_time() {

	#ifdef NOT_READY
	cl = (CL *)malloc(sizeof(CL) * classcnt);
	cl = (CL *)malloc(sizeof(CL) * roomcnt);
	#endif

	int cnt = 0;
	arr = (int *)malloc(sizeof(int) * classcnt); //나중에 전달할놈입니다.
	find_real_able_room(cnt, 0);
}


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//findmax fn
//findmax 함수의 기능 ::
void findmax(int *arr) {


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//variables
	//지역변수 선언 (findmax)
	int a, b, c;
	int i, j, k, l, m, n;
	int possible = 1;
	double score = 0;
	double score2 = 0;
	double score3 = 0;


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//reset
	//새로운 계산을 위해 시간표 초기화
	for (i = 0; i < classcnt; i++) {
		for (j = 0; j < cl[i].ablenum; j++) {
			for (k = 0; k < 5; k++) {
				for (l = 0; l < 22; l++) {
					cl[i].ableroom[j]->classdaytime[k][l] = 0;
				}
			}
			cl[i].ableroom[j]->classcnt = 0;
		}
	}


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//print index numbers(for reference)
	//savepairs함수에서 전달받은 인덱스값을 콘솔창에 표시(디버깅용)
	/*
	for(k=0;k<classcnt;k++){
	   printf("%d ",arr[k]);
	}
	printf("\n");
	*/


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//findmax
	//최대값 계산을 위한 알고리즘
	for (i = 0; i < classcnt; i++) {
		possible = 1;
		if (cl[i].classtype == 3) {
			for (j = 0; j < 22; j++) {
				if (cl[i].classtime1[j] == 1) {
					if ((cl[i].ableroom[arr[i]]->classdaytime[cl[i].classday1[0]-1][j] == 1) || (cl[i].ableroom[arr[i]]->classdaytime[cl[i].classday1[1]-1][j] == 1)) {
						possible = 0;
						break;
					}
				}
				if (cl[i].classtimecomp1[j] == 1) {
					if (cl[i].ableroom[arr[i]]->classdaytime[cl[i].classdaycomp1-1][j] == 1) {
						possible = 0;
						break;
					}
				}
			}
		}
		else {
			for (j = 0; j < 22; j++) {
				if (cl[i].classtime1[j] == 1) {
					if ((cl[i].ableroom[arr[i]]->classdaytime[cl[i].classday1[0]-1][j] == 1) || (cl[i].ableroom[arr[i]]->classdaytime[cl[i].classday1[1]-1][j] == 1)) {
						possible = 0;
						break;
					}
				}
			}
		}
		if (possible == 0) {
			break;
		}
		else {
			if (cl[i].classtype == 3) {
				for (j = 0; j < 22; j++) {
					if (cl[i].classtime1[j] == 1) {
						cl[i].ableroom[arr[i]]->classdaytime[cl[i].classday1[0]-1][j] = 1;
						if (cl[i].classday1[1] != 0) {
							cl[i].ableroom[arr[i]]->classdaytime[cl[i].classday1[1]-1][j] = 1;
						}
					}
					if (cl[i].classtimecomp1[j] == 1) {
						cl[i].ableroom[arr[i]]->classdaytime[cl[i].classdaycomp1-1][j] = 1;
					}
				}
			}
			else {
				for (j = 0; j < 22; j++) {
					if (cl[i].classtime1[j] == 1) {
						cl[i].ableroom[arr[i]]->classdaytime[cl[i].classday1[0]-1][j] = 1;
						if (cl[i].classday1[1] != 0) {
							cl[i].ableroom[arr[i]]->classdaytime[cl[i].classday1[1]-1][j] = 1;
						}
					}
				}
			}

			if (strcmp(cl[i].collname, cl[i].ableroom[arr[i]]->collname) == 0) {
				if (strcmp(cl[i].deptname, cl[i].ableroom[arr[i]]->deptname) == 0) {
					score += 10;
					score2 += 7;
					score3 += 5;
				}
				else {
					if (strcmp(cl[i].ableroom[arr[i]]->deptname, "공용") == 0) {
						score += 8;
						score2 += 5;
						score3 += 3;
					}
					else {
						score += 5;
						score2 += 3;
						score3 += 2;
					}
				}
			}
			else {
				if (strcmp(cl[i].ableroom[arr[i]]->collname, "공용") == 0) {
					score += 3;
					score2 += 2;
					score3 += 1;
				}
			}
			
			score += (double)cl[i].studnum / (double)cl[i].ableroom[arr[i]]->studnum * 4;
			score2 += ((double)cl[i].studnum / (double)cl[i].ableroom[arr[i]]->studnum) * 3;
			score3 += ((double)cl[i].studnum / (double)cl[i].ableroom[arr[i]]->studnum) * 5;

			score += (cl[i].ableroom[arr[i]]->classcnt) * 2;
			score2 += (cl[i].ableroom[arr[i]]->classcnt) * 4;
			score3 += (cl[i].ableroom[arr[i]]->classcnt) * 3;

			(cl[i].ableroom[arr[i]]->classcnt)++;
		}
	}
	if (possible == 1) {
		/*printf("index : ");
		for (k = 0; k < classcnt; k++) {
			printf("%d ", arr[k]);
		}
		printf(" -> POSSIBLE : %.2f %.2f %.2f\n", score, score2, score3);*/
		if (score >= max_score) {
			max_score = score;
			for (k = 0; k < classcnt; k++) {
				max[k] = arr[k];
			}
			for (a = 0;a < roomcnt;a++) {
				for (b = 0;b < 5;b++) {
					for (c = 0;c < 22;c++) {
						ri[a].classdaytime_max[b][c] = ri[a].classdaytime[b][c];
					}
				}
			}
		}
		if (score2 >= max2_score) {
			max2_score = score2;
			for (k = 0; k < classcnt; k++) {
				max2[k] = arr[k];
			}
			for (a = 0;a < roomcnt;a++) {
				for (b = 0;b < 5;b++) {
					for (c = 0;c < 22;c++) {
						ri[a].classdaytime_max2[b][c] = ri[a].classdaytime[b][c];
					}
				}
			}
		}
		if (score3 >= max3_score) {
			max3_score = score3;
			for (k = 0; k < classcnt; k++) {
				max3[k] = arr[k];
			}
			for (a = 0;a < roomcnt;a++) {
				for (b = 0;b < 5;b++) {
					for (c = 0;c < 22;c++) {
						ri[a].classdaytime_max3[b][c] = ri[a].classdaytime[b][c];
					}
				}
			}
		}
	}
	/*else {
		printf("index : ");
		for (k = 0; k < classcnt; k++) {
			printf("%d ", arr[k]);
		}
		printf(" -> IMPOSSIBLE!\n");
	}*/
	#if TEST
	progress++;
	printf("\r[%.2f%% / 100.00%%]", ((double)progress / (double)ablenumtot) * 100);
	#endif
}


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//find_real_able_room fn
//find_real_able_room함수
void find_real_able_room(int cnt, int j) {

	int k;

	arr[cnt - 1] = j;


	if (cnt == classcnt) {
		//printf("CASE : accepted\n");
		savepairs(arr);
	}
	else {
		for (j = 0; j < cl[cnt].ablenum; j++) {
			find_real_able_room(cnt + 1, j);
		}
	}
}


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//savepairs fn
//savepairs함수
void savepairs(int *arr) {

	int i;
	int size;

	for (i = 0; i < classcnt; i++) {
		//printf("%d ", arr[i]);
	}
	//printf("\n");

	findmax(arr);
}