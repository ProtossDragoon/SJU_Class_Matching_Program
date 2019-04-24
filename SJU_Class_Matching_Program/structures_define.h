#ifndef STRUCTURE_DEFINE

//만약 이 헤더파일이 이전에 불려진 적 없다면 include. 구조체 정의는 여러번 시행되면 안되니까..
#define STRUCTURE_DEFINE

typedef struct roominfo {						//각 강의실의 정보가 담겨있는 구조체
	char collname[21], deptname[41];			//단과대명, 학과명
	char classloc[2][6];						//강의실명(한글 한글자+숫자(4자리까지))(예 -> 율202, 광1011)
	int studnum;								//수용인원
	int classcnt, classres;						//배정된 강의 개수, 기자재(아래쪽 참고)
	int classdaytime[5][22];					//시간표(알고리즘 내 계산에 활용됨)
	int classdaytime_max[5][22];				//첫번째 결과의 시간표	
	int classdaytime_max2[5][22];				//두번째 결과의 시간표
	int classdaytime_max3[5][22];				//세번째 결과의 시간표
} RI;

typedef struct classlist {						//각 수업의 정보가 담겨있는 구조체
	char classname[41], profname[21];			//강의명, 교수명
	char deptname[41], collname[21];			//단과대명, 학과명

	char classtime1T[10], classtimecomp1T[10];	//강의시간의 텍스트 형식, 강의시간(컴퓨터실습)의 텍스트 형식 -> 1순위
	char classtime2T[10], classtimecomp2T[10];	//강의시간의 텍스트 형식, 강의시간(컴퓨터실습)의 텍스트 형식 -> 2순위
	char classtime3T[10], classtimecomp3T[10];	//강의시간의 텍스트 형식, 강의시간(컴퓨터실습)의 텍스트 형식 -> 3순위
	char classdaycomp1T[3], classday1T[2][3];	//강의요일(컴퓨터실습)의 텍스트 형식, 강의요일(들)의 텍스트 형식 -> 1순위
	char classdaycomp2T[3], classday2T[2][3];	//강의요일(컴퓨터실습)의 텍스트 형식, 강의요일(들)의 텍스트 형식 -> 2순위
	char classdaycomp3T[3], classday3T[2][3];	//강의요일(컴퓨터실습)의 텍스트 형식, 강의요일(들)의 텍스트 형식 -> 3순위
												//(cf. 강의시간은 30분 간격으로 index 1씩 증가)
	int classtime1[22], classday1[2];			//강의시간의 정수형 배열 형식, 강의요일(들)의 정수형 배열 형식 -> 1순위
	int classtime2[22], classday2[2];			//강의시간의 정수형 배열 형식, 강의요일(들)의 정수형 배열 형식 -> 2순위
	int classtime3[22], classday3[2];			//강의시간의 정수형 배열 형식, 강의요일(들)의 정수형 배열 형식 -> 3순위
	int classtimecomp1[22], classdaycomp1;		//강의시간(컴퓨터실습)의 정수형 배열 형식, 강의요일(컴퓨터실습)의 정수 형태 -> 1순위
	int classtimecomp2[22], classdaycomp2;		//강의시간(컴퓨터실습)의 정수형 배열 형식, 강의요일(컴퓨터실습)의 정수 형태 -> 2순위
	int classtimecomp3[22], classdaycomp3;		//강의시간(컴퓨터실습)의 정수형 배열 형식, 강의요일(컴퓨터실습)의 정수 형태 -> 3순위

	int studnum, classres;						//수강인원, 필요 기자재(아래쪽 참고)
	char classloc[2][6];						//강의실명(한글 한글자+숫자(4자리까지))(예 -> 율202, 광1011)
	int classtype;								//강의유형(아래쪽 참고)

	RI** ableroom;								//가능한 강의실 목록(포인터)	(알고리즘 내 계산에 활용됨)
	int ablenum;								//가능한 강의실 개수			(알고리즘 내 계산에 활용됨)
}CL;


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
/*
-classtype
0=이론
1=실습
2=이론+실습
3=이론+실습(컴퓨터실습)
4=컴퓨터실습(only)(하나짜리)->삭제될 것

-classres
0=
1=
2=
*/



#endif

