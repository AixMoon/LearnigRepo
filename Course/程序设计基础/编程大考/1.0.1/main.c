#include <stdio.h>
#include <string.h>
#define MAXL 100000
int replace(char * origin, char * source, char * target, int lenO) {
	char * pt;
	int lenS = (int)strlen(source);
	int lenT = (int)strlen(target);
	int position = 0, gap = 0;
	if (strstr(origin, source) == NULL) return 0; //δ���ҵ��쳣����
	while ((pt = strstr(origin + gap, source)) != NULL) {
		lenO = (int)strlen(origin);
		int i = 0;
		position = pt - origin;
		for (i = 0; i < lenS; i++) *(pt + i) = '\1';
		//�ж�����Ӧλ��Ӧ�����ƻ�������
		if (lenS >= lenT) {
			strncpy(pt, target, lenT);
			for (i = 0; i < lenO - position; i++) *(pt + lenT + i) = *(pt + i + lenS);
		}
		else {
			if (lenO - lenS + lenT >= MAXL) return -1; //�����쳣����
			for (i = lenO - position; i >= 0; i--) *(pt + lenT + i) = *(pt + i + lenS);
			strncpy(pt, target, lenT);
		}
		gap = position + lenT;//gap���ڷ�ֹѭ���滻��ʹ�ڶ����������滻֮���λ�ÿ�ʼ
	}
	return (int)strlen(origin);
}
int main() {
	//��������
	char s1[MAXL], s2[MAXL], s3[MAXL];
	int len1, len2, len3;
	printf("��������s1�е������Ӵ����滻���滻ǰ��ĳ����޶�Ϊ%d�ֽڡ�\n", MAXL);
	puts("������ԭ��s1��");
	fgets(s1, MAXL, stdin);
	len1 = (int)strlen(s1) - 1;
	s1[len1] = '\0';
	printf("ԭ��s1�ĳ�����%d�������ǣ�%s\n", len1, s1);
	puts("��������Ҵ�s2��");
	fgets(s2, MAXL, stdin);
	len2 = (int)strlen(s2) - 1;
	s2[len2] = '\0';
	printf("���Ҵ�s2�ĳ���Ϊ%d�������ǣ�%s\n", len2, s2);
	puts("�������滻��s3��");
	fgets(s3, MAXL, stdin);
	len3 = (int)strlen(s3) - 1;
	s3[len3] = '\0';
	printf("�滻��s3�ĳ�����%d�������ǣ�%s\n", len3, s3);
	//�滻�������³���
	char snew[MAXL];
	int lennew;
	strncpy(snew, s1, len1);
	lennew = replace(s1, s2, s3, len1);
	if (!lennew)
		puts("δ�ܲ��ҵ�ƥ�����������ԡ�");
	else if (lennew == -1)
		puts("�滻�󳬳��������ƣ������ԡ�");
	else
		printf("�滻���s1����Ϊ%d�������ǣ�%s\n", lennew, s1);
	system("pause");
	return 0;
}
