#ifndef STRUCTURE_DEFINE

//���� �� ��������� ������ �ҷ��� �� ���ٸ� include. ����ü ���Ǵ� ������ ����Ǹ� �ȵǴϱ�..
#define STRUCTURE_DEFINE

typedef struct roominfo {						//�� ���ǽ��� ������ ����ִ� ����ü
	char collname[21], deptname[41];			//�ܰ����, �а���
	char classloc[2][6];						//���ǽǸ�(�ѱ� �ѱ���+����(4�ڸ�����))(�� -> ��202, ��1011)
	int studnum;								//�����ο�
	int classcnt, classres;						//������ ���� ����, ������(�Ʒ��� ����)
	int classdaytime[5][22];					//�ð�ǥ(�˰��� �� ��꿡 Ȱ���)
	int classdaytime_max[5][22];				//ù��° ����� �ð�ǥ	
	int classdaytime_max2[5][22];				//�ι�° ����� �ð�ǥ
	int classdaytime_max3[5][22];				//����° ����� �ð�ǥ
} RI;

typedef struct classlist {						//�� ������ ������ ����ִ� ����ü
	char classname[41], profname[21];			//���Ǹ�, ������
	char deptname[41], collname[21];			//�ܰ����, �а���

	char classtime1T[10], classtimecomp1T[10];	//���ǽð��� �ؽ�Ʈ ����, ���ǽð�(��ǻ�ͽǽ�)�� �ؽ�Ʈ ���� -> 1����
	char classtime2T[10], classtimecomp2T[10];	//���ǽð��� �ؽ�Ʈ ����, ���ǽð�(��ǻ�ͽǽ�)�� �ؽ�Ʈ ���� -> 2����
	char classtime3T[10], classtimecomp3T[10];	//���ǽð��� �ؽ�Ʈ ����, ���ǽð�(��ǻ�ͽǽ�)�� �ؽ�Ʈ ���� -> 3����
	char classdaycomp1T[3], classday1T[2][3];	//���ǿ���(��ǻ�ͽǽ�)�� �ؽ�Ʈ ����, ���ǿ���(��)�� �ؽ�Ʈ ���� -> 1����
	char classdaycomp2T[3], classday2T[2][3];	//���ǿ���(��ǻ�ͽǽ�)�� �ؽ�Ʈ ����, ���ǿ���(��)�� �ؽ�Ʈ ���� -> 2����
	char classdaycomp3T[3], classday3T[2][3];	//���ǿ���(��ǻ�ͽǽ�)�� �ؽ�Ʈ ����, ���ǿ���(��)�� �ؽ�Ʈ ���� -> 3����
												//(cf. ���ǽð��� 30�� �������� index 1�� ����)
	int classtime1[22], classday1[2];			//���ǽð��� ������ �迭 ����, ���ǿ���(��)�� ������ �迭 ���� -> 1����
	int classtime2[22], classday2[2];			//���ǽð��� ������ �迭 ����, ���ǿ���(��)�� ������ �迭 ���� -> 2����
	int classtime3[22], classday3[2];			//���ǽð��� ������ �迭 ����, ���ǿ���(��)�� ������ �迭 ���� -> 3����
	int classtimecomp1[22], classdaycomp1;		//���ǽð�(��ǻ�ͽǽ�)�� ������ �迭 ����, ���ǿ���(��ǻ�ͽǽ�)�� ���� ���� -> 1����
	int classtimecomp2[22], classdaycomp2;		//���ǽð�(��ǻ�ͽǽ�)�� ������ �迭 ����, ���ǿ���(��ǻ�ͽǽ�)�� ���� ���� -> 2����
	int classtimecomp3[22], classdaycomp3;		//���ǽð�(��ǻ�ͽǽ�)�� ������ �迭 ����, ���ǿ���(��ǻ�ͽǽ�)�� ���� ���� -> 3����

	int studnum, classres;						//�����ο�, �ʿ� ������(�Ʒ��� ����)
	char classloc[2][6];						//���ǽǸ�(�ѱ� �ѱ���+����(4�ڸ�����))(�� -> ��202, ��1011)
	int classtype;								//��������(�Ʒ��� ����)

	RI** ableroom;								//������ ���ǽ� ���(������)	(�˰��� �� ��꿡 Ȱ���)
	int ablenum;								//������ ���ǽ� ����			(�˰��� �� ��꿡 Ȱ���)
}CL;


//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
/*
-classtype
0=�̷�
1=�ǽ�
2=�̷�+�ǽ�
3=�̷�+�ǽ�(��ǻ�ͽǽ�)
4=��ǻ�ͽǽ�(only)(�ϳ�¥��)->������ ��

-classres
0=
1=
2=
*/



#endif

