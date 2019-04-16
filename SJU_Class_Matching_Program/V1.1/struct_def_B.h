#define STRUCT_DEF_B

typedef struct roominfo {						//강의실에 대한 정보
	char collname[21], deptname[41];			//collname : 
												//deptnmae : 단과대명
	char classloc[2][5];						//classloc : 강의실 위치 (ex 광501)
	int studnum;								//studnum  : 강의실 수용인원
	int classcnt, classres;						//classcnt : 강의실에 배정된 강의의 개수, 
												//classres : ???
	int classdaytime[5][22];					//classdaytime : 강의실 기준 시간표
	int classdaytime_max[5][22];				//classdaytime_max1 : 
	int classdaytime_max2[5][22];				//
	int classdaytime_max3[5][22];				//
} RI;
	


												
typedef struct classlist {						//수업에 대한 정보
	char classname[41], profname[21];			//classnmae : 강의명
												//profname  : 교수명
	char deptname[41], collname[21];			//deptname  : 단과대명
												//collname  : 
	char classtime1T[10], classtimecomp1T[10];	//classtime1T :
	char classtime2T[10], classtimecomp2T[10];
	char classtime3T[10], classtimecomp3T[10];
	char classdaycomp1T[3], classday1T[2][3];
	char classdaycomp2T[3], classday2T[2][3];
	char classdaycomp3T[3], classday3T[2][3];

	int classtime1[22], classday1[2];			//classtime1 : 수업시간(30분간격으로 index 가 1씩 증가)
												//classday1  : 수업일(요일별로 값이 1씩 증가, 1주일에 최대 두번 강의)
	int classtime2[22], classday2[2];
	int classtime3[22], classday3[2];
	int classtimecomp1[22], classdaycomp1;
	int classtimecomp2[22], classdaycomp2;
	int classtimecomp3[22], classdaycomp3;

	int studnum, classres;						//
	char classloc[2][5];						//
	int classtype;								//수업타입 (이론, 미술, 컴퓨터, 실험, 실습 등..)

	RI **ableroom;								//배정 가능한 강의실 목록 (**포인터 배열로 저장)
	int ablenum;
}CL;


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
/*
-classtype
0=이론
1=실습
2=이론+실습
3=이론+실습(컴퓨터수업)
4=컴퓨터실습(only)(하나짜리)->삭제될 것

-classres
0=
1=
2=
*/