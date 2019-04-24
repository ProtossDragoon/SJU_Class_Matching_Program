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


V1.1.3 - 2019/04/16 - ������
-GIT����� ���
-���ϸ� ����
*/


#define _CRT_SECURE_NO_WARNINGS
#include"essential_headers.h"
#include"structures_define.h"

int main() {



	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//combinine single data txt files into one(combine_files fn)
	//�ϳ�¥���� �ؽ�Ʈ ���ϵ��� �ϳ��� �ؽ�Ʈ ���Ϸ� ����(combine_files�Լ�)
	combine_files();




	return 0;
}