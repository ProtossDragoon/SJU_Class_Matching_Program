#define STRUCT_DEF_B

typedef struct roominfo {						//���ǽǿ� ���� ����
	char collname[21], deptname[41];			//collname : 
												//deptnmae : �ܰ����
	char classloc[2][5];						//classloc : ���ǽ� ��ġ (ex ��501)
	int studnum;								//studnum  : ���ǽ� �����ο�
	int classcnt, classres;						//classcnt : ���ǽǿ� ������ ������ ����, 
												//classres : ???
	int classdaytime[5][22];					//classdaytime : ���ǽ� ���� �ð�ǥ
	int classdaytime_max[5][22];				//classdaytime_max1 : 
	int classdaytime_max2[5][22];				//
	int classdaytime_max3[5][22];				//
} RI;
	


												
typedef struct classlist {						//������ ���� ����
	char classname[41], profname[21];			//classnmae : ���Ǹ�
												//profname  : ������
	char deptname[41], collname[21];			//deptname  : �ܰ����
												//collname  : 
	char classtime1T[10], classtimecomp1T[10];	//classtime1T :
	char classtime2T[10], classtimecomp2T[10];
	char classtime3T[10], classtimecomp3T[10];
	char classdaycomp1T[3], classday1T[2][3];
	char classdaycomp2T[3], classday2T[2][3];
	char classdaycomp3T[3], classday3T[2][3];

	int classtime1[22], classday1[2];			//classtime1 : �����ð�(30�а������� index �� 1�� ����)
												//classday1  : ������(���Ϻ��� ���� 1�� ����, 1���Ͽ� �ִ� �ι� ����)
	int classtime2[22], classday2[2];
	int classtime3[22], classday3[2];
	int classtimecomp1[22], classdaycomp1;
	int classtimecomp2[22], classdaycomp2;
	int classtimecomp3[22], classdaycomp3;

	int studnum, classres;						//
	char classloc[2][5];						//
	int classtype;								//����Ÿ�� (�̷�, �̼�, ��ǻ��, ����, �ǽ� ��..)

	RI **ableroom;								//���� ������ ���ǽ� ��� (**������ �迭�� ����)
	int ablenum;
}CL;


//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
/*
-classtype
0=�̷�
1=�ǽ�
2=�̷�+�ǽ�
3=�̷�+�ǽ�(��ǻ�ͼ���)
4=��ǻ�ͽǽ�(only)(�ϳ�¥��)->������ ��

-classres
0=
1=
2=
*/