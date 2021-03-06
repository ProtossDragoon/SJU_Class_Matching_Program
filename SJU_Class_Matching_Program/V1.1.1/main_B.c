/*
***This is an automatic classroom assigning program***
***Developed by team SOO. Sejong University, South Korea***

COPYRIGHT使 2018-2019, SOO. All rights reserved.
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
-added Korean comments(both code & console)
-combine_files function encapsulation for code readablity
-added struct roominfo classloc number([2][5] -> [2][6])
-optimizations for the option to view timetables
	-discards invalid inputs
	-now recognizes lower-case inputs
*/



/*
//縈撚 檗朝徹(⑷營煎憮) : 縈撚だ橾 -> csvだ橾煎 盪濰 -> 盪濰脹 txtだ橾擊 ANSI⑽衝戲煎 棻衛 盪濰

*п唸п撿 й 匙菟*
1. classlist 寰縑 頂辨(檜煩/褒蝗, 晦濠營)
2. 陛醞纂曖 僥薯
3. 1,2,3 牖嬪 殮溘嫡擎 匙擊 橫飩啪 й雖
4. 渦 �膩�瞳檣 縈撚だ橾 籀葬
5. и 掖熱陛 偽擎 熱機擊 2廓 檜鼻 ж朝 唳辦(辦摹牖嬪縑憮 陛螳螃晦(?))
6. free() more precisely
7. classres 謙盟
8. classtype 3 -> 蕨諼(?), か熱熱機
9. 檜葷縑 奢寥檜 氈朝 掖熱椒菟(諼措檣 掖熱椒菟)
10. 偽擎 婁縑憮朝 螃楚脹 薑掖熱 試盪 寡薑ж朝 唳辦紫 氈棻堅 л(辦摹牖嬪 堅溥)
*/	




//天天天天天天天天天天天天天天天天
//CODE START
#define _CRT_SECURE_NO_WARNINGS


//天天天天天天天天天天天天天天天天
//include header files
//④渦だ橾 蹺陛
#ifndef MYHEADER_H
#include"myheader.h"
#endif

#ifdef VERSION_B
#include"struct_def_B.h"


//天天天天天天天天天天天天天天天天
//global variables
//瞪羲滲熱菟
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
#endif


//天天天天天天天天天天天天天天天天
//main fn
//詭檣л熱
int main() {


	//天天天天天天天天天天天天天天天天
	//local variables
	//雖羲滲熱菟


		//天天天天天天天天天天天天天天天天
		//variables for reading data from txt
		//臢蝶お だ橾縑憮 薑爾蒂 檗橫菟檜晦 嬪п 餌辨腎朝 滲熱菟
	FILE *fp1, *fp2;
	FILE *finfp;
	char pname[21], clname[41], dname[41], coname[21], ctime1[22], ctime2[22], ctime3[22];
	int tn, tm, check, num, fday, ftime[22], fj, sc, al;
	int cday1, cday2, cday3, snum, cres, ctype;
	char dayt1[3], dayt2[3], dayt3[3], comp;
	char all[200], *pall;
	char cloc[2][5];
	

		//天天天天天天天天天天天天天天天天
		//variables for saving day & time data as text to memory
		//蹂橾婁 衛除 薑爾蒂 臢蝶お ⑽衝戲煎 盪濰ж晦 嬪п 餌辨腎朝 滲熱菟
		//ex)
		//1200-1330
		//0900-1200
	char daylist[5][3] = { "錯","��","熱","跡","旎" };
	char timestart[5], mid[2] = { "-" }, timeend[5];


		//天天天天天天天天天天天天天天天天
		//miscellaneous variables
		//晦顫 滲熱菟
	int i, j, k, c, n, l, m, q, t, u;
	int selectionnum;
	char selection;
	

	//天天天天天天天天天天天天天天天天
	//combinine single data txt files into one(combine_files fn)
	//ж釭瞼葬曖 臢蝶お だ橾菟擊 ж釭曖 臢蝶お だ橾煎 唸м(combine_filesл熱)
	//虜菟橫雖朝 textfile 曖 檜葷擎 classlist.txt
	combine_files();
	

	//天天天天天天天天天天天天天天天天
	//read data from txt + save to memory
	//臢蝶お だ橾曖 薑爾菟擊 檗橫菟檜堅 詭賅葬縑 盪濰

	
		//天天天天天天天天天天天天天天天天
		//count how many classes there are from classlist.txt + allocation(cl[])
		//classlist.txt だ橾縑憮 鬼曖熱蒂 撮堅, cl[]掘褻羹 寡翮擊 翕瞳й渡 
		//**cl擎 Class List擊 曖嘐л. **classcnt : 鬼曖曖 偃熱
	fp1 = fopen("classlist.txt", "r");
	fscanf(fp1, "%s", all);
	while (!feof(fp1)) {
		classcnt++;
		fscanf(fp1, "%s", all);
	}
	fclose(fp1);
	cl = (CL *)malloc(sizeof(CL)*(classcnt));   // 殮溘嫡擎 だ橾 識 偃熱 撮晦 + 翕瞳й渡


		//天天天天天天天天天天天天天天天天
		//count how many rooms there are from roominfo.txt + allocation(ri[])
		//roominfo.txt だ橾縑憮 鬼曖褒熱蒂 撮堅, ri[]掘褻羹 寡翮擊 翕瞳й渡 
		//**ri朝 Room Info蒂 曖嘐л. **roomcnt : 鬼曖褒 偃熱
	fp2 = fopen("roominfo.txt", "r");
	fscanf(fp2, "%s", all);
	while (!feof(fp2)) {
		roomcnt++;
		fscanf(fp2, "%s", all);
	}
	fclose(fp2);
	ri = (RI *)malloc(sizeof(RI)*(roomcnt));   // 乾堅氈朝 だ橾 識 偃熱 撮晦 + 翕瞳й渡


		//天天天天天天天天天天天天天天天天
		//reset timetable for all rooms(in ri[])
		//ri[]掘褻羹 寡翮縑 氈朝 賅萇 鬼曖褒曖 衛除ル蒂 0戲煎 蟾晦�� (噙溯晦高 蟾晦��)

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


		//天天天天天天天天天天天天天天天天
		//reset timetable for all classes(in cl[])
		//cl[]掘褻羹 寡翮縑 氈朝 賅萇 熱機曖 衛除ル蒂 0戲煎 蟾晦�� (噙溯晦高 蟾晦��)
	for (i = 0;i < classcnt;i++) {
		cl[i].classday1[0] = cl[i].classday2[0] = cl[i].classday3[0] = 0;
		cl[i].classday1[1] = cl[i].classday2[1] = cl[i].classday3[1] = 0;
		cl[i].classdaycomp1 = cl[i].classdaycomp2 = cl[i].classdaycomp3 = 0;
		
		for (j = 0;j < 22;j++) {
			cl[i].classtime1[j] = cl[i].classtime2[j] = cl[i].classtime3[j] = 0;
			cl[i].classtimecomp1[j] = cl[i].classtimecomp2[j] = cl[i].classtimecomp3[j] = 0;
		}
	}


		//天天天天天天天天天天天天天天天天
		//save data to memory(cl[] & ri[])
		//臢蝶お だ橾曖 薑爾菟擊 檗橫菟檜堅 詭賅葬縑 盪濰(cl[] & ri[])
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
		//(舒廓簞 璋濠陛 0檜賊, 輿 1�� 熱機殮棲棻)

		//cl[i].classdaycomp1 = 0;
		//cl[i].classdaycomp2 = 0;
		//cl[i].classdaycomp3 = 0;
		for (comp = 0;comp < 22;comp++) {
			cl[i].classtimecomp1[comp] = 0;
			cl[i].classtimecomp2[comp] = 0;
			cl[i].classtimecomp3[comp] = 0;
		}
		//(this is for setting comp values to 0)
		//(comp縑 п渡ж朝 高菟擊 0戲煎 蟾晦�倆炴� 濛機殮棲棻)

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
		cl[i].classres = cres;      // だ橾縑憮 掘褻羹 i廓簞疏 疏頂晦 諫猿
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
			if ((cl[i].studnum <= ri[j].studnum)) {      // 檣錳熱 褻勒 睡м 衛
				if (ri[j].classres == cl[i].classres)
					check = 1;
				if (cl[i].classres == 0)   // 晦濠營 в蹂橈擠
					check = 1;
				if (check == 1) {      // 檣錳熱 + 濠營 褻勒 睡м 衛 
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


		//天天天天天天天天天天天天天天天天
		//find comp classes and combine them with its regular(theory) classes
		//comp高菟擊 瓊堅, п渡腎朝 檜煩熱機婁 唸м
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


		//天天天天天天天天天天天天天天天天
		//print all data saved to memory(from classlixt.txt)(for testing)
		//詭賅葬縑 盪濰и 薑爾菟擊 瞪睡 轎溘(classlixt.txt縑憮)(蛤幗梵辨)
	printf("\n\n//ALL DATA SAVED TO MEMORY(FROM CLASSLIST.TXT)");
	printf("\n//詭賅葬縑 盪濰脹 賅萇 薑爾菟(cl掘褻羹 寡翮)");
	for (i = 0;i < classcnt;i++) {
		if (cl[i].classdaycomp1 != 0) {
			printf("\n*%s %s %s %s %d\n", cl[i].classname, cl[i].profname, cl[i].deptname, cl[i].collname, cl[i].classtype);
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
			printf("\n%s %s %s %s %d\n", cl[i].classname, cl[i].profname, cl[i].deptname, cl[i].collname, cl[i].classtype);
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
	printf("\n(* 朝 闡У攪褒蝗檜 氈朝 熱機殮棲棻.)");


	//天天天天天天天天天天天天天天天天
	//calculation + write to file
	//譆渠高 啗骯 + だ橾煎 轎溘
	//system("cls");
	
	printf("\n\n\n//ABLENUM VALUES FOR EACH CLASS");
	printf("\n//陝 鬼曖縑 п渡腎朝 ablenum高菟");
	for (i = 0; i < classcnt; i++) {
		//printf("cl[%d].ablenum : %d ", i, cl[i].ablenum);
		printf("\n%s : %d", cl[i].classname, cl[i].ablenum);
	}
	printf("\n(if any have a value of 0, classroom assignment is impossible.)\n");
	printf("(0檣 高檜 ж釭塭紫 襄營ж賊, 鬼曖褒 寡薑檜 碳陛棟м棲棻.)\n");

	max = (int *)malloc(classcnt * sizeof(int));
	max2 = (int *)malloc(classcnt * sizeof(int));
	max3 = (int *)malloc(classcnt * sizeof(int));


		//天天天天天天天天天天天天天天天天
		//find_time fn(calculation)
		//find_timeл熱蒂 檜辨и 啗骯
	find_time();





		//天天天天天天天天天天天天天天天天
		//save day & time as text(to cl[])
		//cl[]縑 蹂橾婁 衛除 薑爾蒂 臢蝶お ⑽衝戲煎 盪濰
	for (i = 0;i < classcnt;i++) {


			//天天天天天天天天天天天天天天天天
			//day
			//蹂橾薑爾
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
		

			//天天天天天天天天天天天天天天天天
			//time
			//衛除薑爾


				//天天天天天天天天天天天天天天天天
				//1st
				//1牖嬪
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


				//天天天天天天天天天天天天天天天天
				//2nd
				//2牖嬪
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


				//天天天天天天天天天天天天天天天天
				//3rd
				//3牖嬪
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


				//天天天天天天天天天天天天天天天天
				//comp
				//闡У攪褒蝗 熱機


					//天天天天天天天天天天天天天天天天
					//1st
					//1牖嬪
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


					//天天天天天天天天天天天天天天天天
					//2nd
					//2牖嬪
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


					//天天天天天天天天天天天天天天天天
					//3rd
					//3牖嬪
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


		//天天天天天天天天天天天天天天天天
		//print result on screen + save result via txt
		//唸婁蒂 夔樂璽縑 ル衛 + 臢蝶お だ橾煎 轎溘
	printf("\n\n//MAX INDEX VALUES");
	printf("\n//譆渠高縑 п渡腎朝 檣策蝶 高菟");
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
	printf("\n");


	printf("\n\n//RESULTS BASED ON DIFFERENT PRIORITIES\n");
	printf("//陝晦棻艇 陛醞纂陛 瞳辨脹 唸婁高菟\n");
	printf("欽婁渠郭葬 僮朝 寡纂蒂 譆辦摹戲煎 堅溥и п : \n");
	for (i = 0; i < classcnt; i++) {
		strcpy(cl[i].classloc[0], cl[i].ableroom[max[i]]->classloc[0]);
		strcpy(cl[i].classloc[1], cl[i].ableroom[max[i]]->classloc[1]);
	}

	for (i = 0; i < classcnt; i++) {
		if (cl[i].classtype == 3)
			printf("%s , %s , %s%s%s/%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classdaycomp1T, cl[i].classtimecomp1T, cl[i].classloc[0], cl[i].classloc[1]);
		else
			printf("%s , %s , %s%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classloc[0], cl[i].classloc[1]);
	}
	printf("\n");

	finfp = fopen("欽婁渠 譆辦摹.txt", "w");   // 譆謙だ橾縑 轎溘
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
		fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);


	printf("и 鬼曖褒渡 號擎 鬼曖陛 菟橫陛 �螃窕�檣 鬼曖褒 遴艙擊 譆辦摹戲煎 堅溥и п : \n");
	for (i = 0; i < classcnt; i++) {
		strcpy(cl[i].classloc[0], cl[i].ableroom[max2[i]]->classloc[0]);
		strcpy(cl[i].classloc[1], cl[i].ableroom[max2[i]]->classloc[1]);
	}

	for (i = 0; i < classcnt; i++) {
		if (cl[i].classtype == 3)
			printf("%s , %s , %s%s%s/%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classdaycomp1T, cl[i].classtimecomp1T, cl[i].classloc[0], cl[i].classloc[1]);
		else
			printf("%s , %s , %s%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classloc[0], cl[i].classloc[1]);
	}
	printf("\n");

	finfp = fopen("鬼曖熱 譆辦摹.txt", "w");   // 譆謙だ橾縑 轎溘
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
			fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);


	printf("鬼曖褒曖 嶸�獉灠� 薯剪蒂 譆辦摹戲煎 堅溥ж罹 檣錳熱縑 勘蜃朝 鬼曖褒擊 譆辦摹戲煎 堅溥и п : \n");
	for (i = 0; i < classcnt; i++) {
		strcpy(cl[i].classloc[0], cl[i].ableroom[max3[i]]->classloc[0]);
		strcpy(cl[i].classloc[1], cl[i].ableroom[max3[i]]->classloc[1]);
	}

	for (i = 0; i < classcnt; i++) {
		if (cl[i].classtype == 3)
			printf("%s , %s , %s%s%s/%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classdaycomp1T, cl[i].classtimecomp1T, cl[i].classloc[0], cl[i].classloc[1]);
		else
			printf("%s , %s , %s%s%s -> %s%s\n", cl[i].profname, cl[i].classname, cl[i].classday1T[0], cl[i].classday1T[1], cl[i].classtime1T, cl[i].classloc[0], cl[i].classloc[1]);
	}
	printf("\n");

	finfp = fopen("檣錳熱 譆辦摹.txt", "w");   // 譆謙だ橾縑 轎溘
	for (k = 0; k < classcnt; k++) {
		if (cl[k].classtype == 3)
			fprintf(finfp, "%s,%s,%s%s%s/%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classdaycomp1T, cl[k].classtimecomp1T, cl[k].classloc[0], cl[k].classloc[1]);
		else
			fprintf(finfp, "%s,%s,%s%s%s,%s%s\n", cl[k].profname, cl[k].classname, cl[k].classday1T[0], cl[k].classday1T[1], cl[k].classtime1T, cl[k].classloc[0], cl[k].classloc[1]);
	}
	fclose(finfp);


	//天天天天天天天天天天天天天天天天
	//option to view the timetable
	//衛除ル蒂 �挫恉� 熱 氈朝 褫暮
	printf("\n//TIMETABLES\n");
	printf("//衛除ル �挫垥n");
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


	//天天天天天天天天天天天天天天天天
	//close FILE + free variables
	//FILE殘晦 壽 翕瞳詭賅葬 п薯
	fclose(fp1);
	free(cl);
	free(ri);
	
	return 0;
}