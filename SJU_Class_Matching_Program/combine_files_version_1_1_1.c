//CODE START
#define _CRT_SECURE_NO_WARNINGS


//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//include header files
//��� ������ include �մϴ�.
#include"myheader.h"
#include"struct_def.h"


//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//combine_files fn
//combine_files�Լ�
void combine_files() {


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//variables for combining single data txt files into one
	//�˰��� ���� : �켱 ������ ������ � �ִ��� �Ǻ�. 9999������ �бⰡ��.
	//				 �̸��� ��� �������� �ϳ��� ���̰� �ٽ� �ٿ� ���� �̸��� �о����
	//				 ���ǽǹ���, ,(,N,),.txt �� �����ϴ� ���
	//				 ���� ���� �̸����� ������ ���� ���빰�� �о�鿩 �ϳ��� txt ���Ϸ� ����
	//ex)
	//���ǽǹ���.txt
	//���ǽǹ��� (1).txt
	//���ǽǹ��� (2).txt


	int fi, fk;
	int findone = 0; //�����ڸ��� �Ǵ��ϴ� int.
	int name_count = 0;
	char name_default[12] = { "���ǽǹ���" };
	char name_opendoor[3] = { " (" };
	char name_number[5] = { 0 };
	char name_closedoor[2] = { ")" };
	char name_txt[5] = { ".txt" };
	char name_final[25] = { 0 };
	char read_tmp[150];
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//combinine single data txt files into one
	//�ϳ�¥���� �ؽ�Ʈ ���ϵ��� �ϳ��� �ؽ�Ʈ ���Ϸ� ����
	#if TEST
	printf("//SINGLE TXT FILES THAT WERE READ AND COMBINED INTO ONE\n");
	printf("//�ϳ��� ���Ϸ� ��ġ�� ���� �о���� �ϳ�¥�� �ؽ�Ʈ ���ϵ�\n");
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