#include <stdio.h>
#include <stdlib.h>  //system("cls")
#include <string.h> //문자열 비교
#pragma warning (disable:4996)

long totalday(int y, int m, int d);

int main()
{
	char reas[100];
	FILE *fp;  //수행평가.txt가 저장될 포인터
	FILE *fs;  //수행평가1.txt이나 백업.txt가 저장될 포인터
	int a, b, c, fy, fm, fd, sy, sm, sd, end, cnt = 0;
	long dates;
	char sub[10], chk[10], buf[10], s, name[100]; 
back:
	system("cls");
	printf("\n\n수행평가 관리 프로그램\n\n");
	printf("----------------------------------\n");
	printf("1. 수행평가 과목 출력\n");
	printf("2. 수행평가 추가\n");
	printf("3. 수행평가 삭제\n");
	printf("4. 수행평가 백업 및 복원\n");
	printf("0. 종료\n\n");
	printf("입력: ");
	scanf("%d", &a);
	if (a == 1) {
		system("cls");
		printf("오늘 날짜를 입력해 주세요\n");
		printf("----------------------------------\n");
		printf("형식: 2018 9 14) >");
		scanf("%d %d %d", &fy, &fm, &fd);
		fp = fopen("수행평가.txt", "r"); //수행평가.txt를 읽기 전용으로 불러와 fp에 저장
		system("cls");
		while (!feof(fp)) //fp의 끝이 아닐때까지 돌아감
		{
			fscanf(fp, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
			if (fread(&buf, 1, 1, fp) == 0) break;//읽었을때 비어있으면 while문 종료(마지막줄 두번 출력 방지)
			dates = totalday(sy, sm, sd) - totalday(fy, fm, fd); //totalday함수를 통해 일수를 구해 구함
			printf("\n\n%s %d %d %d %s %d일남았습니다.", sub, sy, sm, sd, name, dates);
			printf("\n\n----------------------------------\n");
		}
		fclose(fp);
		printf("g가 입력되면 초기화면으로 돌아갑니다.> ");
		re:
		scanf("%s", &s);
		if (s == 'g') { system("cls"); goto back; }
		else goto re;
	}
	else if (a == 2) {
		system("cls");
		printf("입력할 수행평가 개수를 입력 하시오> ");
		scanf("%d", &end);
		fp = fopen("수행평가.txt", "a"); //수행평가.txt를 글 추가 기능으로 불러와 fp에 저장
		for (int i = 0; i < end; i++) {
			printf("입력할 수행평가를 입력하십시오\n");
			printf("예: 국어 2018 7 3 토론준비> ");
			scanf("%s %d %d %d %s", sub, &sy, &sm, &sd, name);	//수행평가를 입력받음
			fprintf(fp, "%s %d %d %d %s\n", sub, sy, sm, sd, name);	//수행평가.txt에 입력
		}
		fclose(fp); goto back;
	}
	else if (a == 3) {
		system("cls");
		printf("\n\n수행평가 관리 프로그램\n\n");
		printf("----------------------------------\n");
		printf("원하시는 삭제 방식을 선택해 주세요\n");
		printf("1. 자동 삭제(날짜가 지난 수행평가 자동 삭제)\n");
		printf("2. 사용자 지정 과목 삭제\n");
		scanf("%d", &b);
		if (b == 1) {
			system("cls");
			printf("오늘 날짜를 입력해 주세요\n");
			printf("----------------------------------\n");
			printf("형식: 2018 9 14) >");
			scanf("%d %d %d", &fy, &fm, &fd);
			fp = fopen("수행평가.txt", "r");		//수행평가.txt를 읽기 전용으로 불러와 fp에 저장
			fs = fopen("수행평가1.txt", "w");	//수행평가1.txt를 쓰기용으로 불러와 fs에 저장
			while (!feof(fp))   //수행평가.txt에서 삭제할 과목 부분 제외 다른 과목만 수행평가1.txt로 저장
			{
				fscanf(fp, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
				dates = totalday(sy, sm, sd) - totalday(fy, fm, fd);
				if (fread(&buf, 1, 1, fp) == 0) break;
				if (dates < 0) continue;  //삭제할 과목인지 아닌지 체크
				fprintf(fs, "%s %d %d %d %s\n", sub, sy, sm, sd, name);
			}
			fclose(fp); fclose(fs);
			fp = fopen("수행평가.txt", "w");
			fs = fopen("수행평가1.txt", "r");
			while (!feof(fs))		//수행평가1.txt에 저장됬던 걸 수행평가.txt로 다시 씀
			{
				fscanf(fs, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
				if (fgets(buf, 80, fs) == NULL) break;
				fprintf(fp, "%s %d %d %d %s\n", sub, sy, sm, sd, name);
			}
			fclose(fp); fclose(fs); goto back;
		}
		if (b == 2) {
			printf("삭제할 과목을 입력하시오: ");
			scanf("%s", chk);
			fp = fopen("수행평가.txt", "r");		//수행평가.txt를 읽기 전용으로 불러와 fp에 저장
			fs = fopen("수행평가1.txt", "w");	//수행평가1.txt를 쓰기용으로 불러와 fs에 저장
			while (!feof(fp))   //수행평가.txt에서 삭제할 과목 부분 제외 다른 과목만 수행평가1.txt로 저장
			{
				fscanf(fp, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
				if (fread(&buf, 1, 1, fp) == 0) break;
				if (strcmp(chk, sub) == 0) continue;  //삭제할 과목인지 아닌지 체크
				fprintf(fs, "%s %d %d %d %s\n", sub, sy, sm, sd, name);
			}
			fclose(fp); fclose(fs);
			fp = fopen("수행평가.txt", "w");
			fs = fopen("수행평가1.txt", "r");
			while (!feof(fs))		//수행평가1.txt에 저장됬던 걸 수행평가.txt로 다시 씀
			{
				fscanf(fs, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
				if (fgets(buf, 80, fs) == NULL) break;
				fprintf(fp, "%s %d %d %d %s\n", sub, sy, sm, sd, name);
			}
			fclose(fp); fclose(fs); goto back;
		}
	}
		else if (a == 4) {
		system("cls");
			printf("\n\n수행평가 관리 프로그램\n\n");
			printf("----------------------------------\n");
			printf("원하시는 기능을 선택해 주세요\n");
			printf("1. 백업\n");
			printf("2. 복원\n");
			printf("입력: ");
			scanf("%d", &c);
				if (c == 1) {
					fp = fopen("수행평가.txt", "r");
					fs = fopen("백업.txt", "w");
					while (!feof(fp))	//수행평가.txt에 저장됬던 걸 백업.txt로 다시 씀
					{
						fscanf(fp, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
						if (fgets(buf, 80, fp) == NULL) break;
						fprintf(fs, "%s %d %d %d &s\n", sub, sy, sm, sd, name);
					}
					fclose(fp); fclose(fs); system("cls"); goto back;
				}
				else if (c == 2) {
					fp = fopen("수행평가.txt", "w");
					fs = fopen("백업.txt", "r");
					while (!feof(fs))		//백업.txt에 저장됬던 걸 수행평가.txt로 다시 씀
					{
						fscanf(fs, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
						if (fgets(buf, 80, fs) == NULL) break;
						fprintf(fp, "%s %d %d %d %s\n", sub, sy, sm, sd, name);
					}
					fclose(fp); fclose(fs); system("cls"); goto back;
				}
		}
	else if (a == 0) {
		system("cls");
		printf("\n수행평가 관리 프로그램\n\n");
		printf("----------------------------------\n");
		printf("사용해주셔서 감사합니다.\n\n\n");
	}
	else {
		system("cls");
		printf("다시 입력해 주세요.\n\n");
		goto back;
	}
}

long totalday(int y, int m, int d)  //입력받은 년도, 달, 날짜를 매개변수로 받아옴
{
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 }, i; //각달의 끝날을 배열에 저장
	long total = 0; 
	total = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;  //예를들어 2018년 7월 8일 이 입력됬다면 2018년이 몇일인지 일수로 계산
	if (!(y % 4) && y % 100 || !(y % 400)) months[1]++; //윤년이면 1번방 즉 2월달을 29일로 변경해서 구함
	for (i = 0; i < m - 1; i++) {
		total += months[i]; //그달에 일수를 전체에 더해감
	}
	total += d;  //날짜에 일수를 더함
	return total;  //total 값을 반환
}