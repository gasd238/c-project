#include <stdio.h>
#include <stdlib.h>  //system("cls")
#include <string.h> //���ڿ� ��
#pragma warning (disable:4996)

long totalday(int y, int m, int d);

int main()
{
	char reas[100];
	FILE *fp;  //������.txt�� ����� ������
	FILE *fs;  //������1.txt�̳� ���.txt�� ����� ������
	int a, b, c, fy, fm, fd, sy, sm, sd, end, cnt = 0;
	long dates;
	char sub[10], chk[10], buf[10], s, name[100]; 
back:
	system("cls");
	printf("\n\n������ ���� ���α׷�\n\n");
	printf("----------------------------------\n");
	printf("1. ������ ���� ���\n");
	printf("2. ������ �߰�\n");
	printf("3. ������ ����\n");
	printf("4. ������ ��� �� ����\n");
	printf("0. ����\n\n");
	printf("�Է�: ");
	scanf("%d", &a);
	if (a == 1) {
		system("cls");
		printf("���� ��¥�� �Է��� �ּ���\n");
		printf("----------------------------------\n");
		printf("����: 2018 9 14) >");
		scanf("%d %d %d", &fy, &fm, &fd);
		fp = fopen("������.txt", "r"); //������.txt�� �б� �������� �ҷ��� fp�� ����
		system("cls");
		while (!feof(fp)) //fp�� ���� �ƴҶ����� ���ư�
		{
			fscanf(fp, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
			if (fread(&buf, 1, 1, fp) == 0) break;//�о����� ��������� while�� ����(�������� �ι� ��� ����)
			dates = totalday(sy, sm, sd) - totalday(fy, fm, fd); //totalday�Լ��� ���� �ϼ��� ���� ����
			printf("\n\n%s %d %d %d %s %d�ϳ��ҽ��ϴ�.", sub, sy, sm, sd, name, dates);
			printf("\n\n----------------------------------\n");
		}
		fclose(fp);
		printf("g�� �ԷµǸ� �ʱ�ȭ������ ���ư��ϴ�.> ");
		re:
		scanf("%s", &s);
		if (s == 'g') { system("cls"); goto back; }
		else goto re;
	}
	else if (a == 2) {
		system("cls");
		printf("�Է��� ������ ������ �Է� �Ͻÿ�> ");
		scanf("%d", &end);
		fp = fopen("������.txt", "a"); //������.txt�� �� �߰� ������� �ҷ��� fp�� ����
		for (int i = 0; i < end; i++) {
			printf("�Է��� �����򰡸� �Է��Ͻʽÿ�\n");
			printf("��: ���� 2018 7 3 ����غ�> ");
			scanf("%s %d %d %d %s", sub, &sy, &sm, &sd, name);	//�����򰡸� �Է¹���
			fprintf(fp, "%s %d %d %d %s\n", sub, sy, sm, sd, name);	//������.txt�� �Է�
		}
		fclose(fp); goto back;
	}
	else if (a == 3) {
		system("cls");
		printf("\n\n������ ���� ���α׷�\n\n");
		printf("----------------------------------\n");
		printf("���Ͻô� ���� ����� ������ �ּ���\n");
		printf("1. �ڵ� ����(��¥�� ���� ������ �ڵ� ����)\n");
		printf("2. ����� ���� ���� ����\n");
		scanf("%d", &b);
		if (b == 1) {
			system("cls");
			printf("���� ��¥�� �Է��� �ּ���\n");
			printf("----------------------------------\n");
			printf("����: 2018 9 14) >");
			scanf("%d %d %d", &fy, &fm, &fd);
			fp = fopen("������.txt", "r");		//������.txt�� �б� �������� �ҷ��� fp�� ����
			fs = fopen("������1.txt", "w");	//������1.txt�� ��������� �ҷ��� fs�� ����
			while (!feof(fp))   //������.txt���� ������ ���� �κ� ���� �ٸ� ���� ������1.txt�� ����
			{
				fscanf(fp, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
				dates = totalday(sy, sm, sd) - totalday(fy, fm, fd);
				if (fread(&buf, 1, 1, fp) == 0) break;
				if (dates < 0) continue;  //������ �������� �ƴ��� üũ
				fprintf(fs, "%s %d %d %d %s\n", sub, sy, sm, sd, name);
			}
			fclose(fp); fclose(fs);
			fp = fopen("������.txt", "w");
			fs = fopen("������1.txt", "r");
			while (!feof(fs))		//������1.txt�� ������ �� ������.txt�� �ٽ� ��
			{
				fscanf(fs, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
				if (fgets(buf, 80, fs) == NULL) break;
				fprintf(fp, "%s %d %d %d %s\n", sub, sy, sm, sd, name);
			}
			fclose(fp); fclose(fs); goto back;
		}
		if (b == 2) {
			printf("������ ������ �Է��Ͻÿ�: ");
			scanf("%s", chk);
			fp = fopen("������.txt", "r");		//������.txt�� �б� �������� �ҷ��� fp�� ����
			fs = fopen("������1.txt", "w");	//������1.txt�� ��������� �ҷ��� fs�� ����
			while (!feof(fp))   //������.txt���� ������ ���� �κ� ���� �ٸ� ���� ������1.txt�� ����
			{
				fscanf(fp, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
				if (fread(&buf, 1, 1, fp) == 0) break;
				if (strcmp(chk, sub) == 0) continue;  //������ �������� �ƴ��� üũ
				fprintf(fs, "%s %d %d %d %s\n", sub, sy, sm, sd, name);
			}
			fclose(fp); fclose(fs);
			fp = fopen("������.txt", "w");
			fs = fopen("������1.txt", "r");
			while (!feof(fs))		//������1.txt�� ������ �� ������.txt�� �ٽ� ��
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
			printf("\n\n������ ���� ���α׷�\n\n");
			printf("----------------------------------\n");
			printf("���Ͻô� ����� ������ �ּ���\n");
			printf("1. ���\n");
			printf("2. ����\n");
			printf("�Է�: ");
			scanf("%d", &c);
				if (c == 1) {
					fp = fopen("������.txt", "r");
					fs = fopen("���.txt", "w");
					while (!feof(fp))	//������.txt�� ������ �� ���.txt�� �ٽ� ��
					{
						fscanf(fp, "%s %d %d %d %s", sub, &sy, &sm, &sd, name);
						if (fgets(buf, 80, fp) == NULL) break;
						fprintf(fs, "%s %d %d %d &s\n", sub, sy, sm, sd, name);
					}
					fclose(fp); fclose(fs); system("cls"); goto back;
				}
				else if (c == 2) {
					fp = fopen("������.txt", "w");
					fs = fopen("���.txt", "r");
					while (!feof(fs))		//���.txt�� ������ �� ������.txt�� �ٽ� ��
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
		printf("\n������ ���� ���α׷�\n\n");
		printf("----------------------------------\n");
		printf("������ּż� �����մϴ�.\n\n\n");
	}
	else {
		system("cls");
		printf("�ٽ� �Է��� �ּ���.\n\n");
		goto back;
	}
}

long totalday(int y, int m, int d)  //�Է¹��� �⵵, ��, ��¥�� �Ű������� �޾ƿ�
{
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 }, i; //������ ������ �迭�� ����
	long total = 0; 
	total = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;  //������� 2018�� 7�� 8�� �� �Է�ٸ� 2018���� �������� �ϼ��� ���
	if (!(y % 4) && y % 100 || !(y % 400)) months[1]++; //�����̸� 1���� �� 2������ 29�Ϸ� �����ؼ� ����
	for (i = 0; i < m - 1; i++) {
		total += months[i]; //�״޿� �ϼ��� ��ü�� ���ذ�
	}
	total += d;  //��¥�� �ϼ��� ����
	return total;  //total ���� ��ȯ
}