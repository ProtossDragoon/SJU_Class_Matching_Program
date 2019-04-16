//CODE START
#define _CRT_SECURE_NO_WARNINGS


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//include header files
//헤더 파일을 include 합니다.
#include"myheader.h"
#include"struct_def.h"


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//combine_files fn
//combine_files함수
void combine_files() {


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//variables for combining single data txt files into one
	//알고리즘 설명 : 우선 파일의 갯수가 몇개 있는지 판별. 9999개까지 읽기가능.
	//				 이름을 모두 조각내서 하나씩 붙이고 다시 붙여 파일 이름을 읽어들임
	//				 강의실배정, ,(,N,),.txt 를 접합하는 방식
	//				 만들어낸 파일 이름으로 파일을 열고 내용물을 읽어들여 하나의 txt 파일로 접합
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
	//combinine single data txt files into one
	//하나짜리의 텍스트 파일들을 하나의 텍스트 파일로 결합
	#if TEST
	printf("//SINGLE TXT FILES THAT WERE READ AND COMBINED INTO ONE\n");
	printf("//하나의 파일로 합치기 위해 읽어들인 하나짜리 텍스트 파일들\n");
	#endif

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

		#if TEST
		printf("%s\n", name_final);
		#endif
		for (fi = 0; fi < strlen(name_final); fi++) {
			name_final[fi] = 0;
		}

		fscanf(fp_read, "%s", read_tmp);
		fclose(fp_read);

		fprintf(fp_write, "%s\n", read_tmp);

		name_count++;
	}
	fclose(fp_write);
}