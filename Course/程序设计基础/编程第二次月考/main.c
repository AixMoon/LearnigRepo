#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAXL 1000
int main() {
	char input[MAXL];
	puts("����һ���ַ���������Ч��16������ת��Ϊ10����");
	while (printf("������һ���ַ��� (����END�˳�)��\n") && gets_s(input, MAXL) && strcmp(input, "END")) {
		int i, len = strlen(input);
		bool available = false;
		int hex;
		if (input[0] == '0' && (input[1] == 'x' || input[1] == 'X')) {
			if (sscanf(input, "%x", &hex)) {
				available = true;
			}
		}
		printf("�ַ���s1�ĳ�����%d��������%s\n", len, input);
		if (available == true) printf("ת�����ʮ������Ϊ%d\n", hex);
		else printf("�Ƿ���16������ֵ\n");
	}
	return 0;
}