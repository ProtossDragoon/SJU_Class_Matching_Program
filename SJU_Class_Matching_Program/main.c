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


V1.1.3 - 2019/04/16 - 이장후
-GIT저장소 등록
-파일명 수정
*/


#define _CRT_SECURE_NO_WARNINGS
#include"essential_headers.h"
#include"structures_define.h"

int main() {



	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//combinine single data txt files into one(combine_files fn)
	//하나짜리의 텍스트 파일들을 하나의 텍스트 파일로 결합(combine_files함수)
	combine_files();




	return 0;
}