#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// �w�肵�����̓�����Ԃ�
int NumberOfDays(int year, int month)
{
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			return 29;
		else
			return 28;
	}
	else
		return 31;
}

// �w�肵������1���̗j����Ԃ�(���Ȃ�0)
int GetFirstDayOfWeek(int year, int month)
{
	// 1����2����O�N��13����14���Ƃ��Ĉ���
	if (month <= 2)
	{
		year -= 1;
		month += 12;
	}
	// �j���ԍ���Ԃ�
	return (1 + ((8 + (13 * month)) / 5) + (year + (year / 4) - (year / 100) + (year / 400))) % 7;
}

// ���͕����񂪌��������Ă��邩�N�������Ă��邩���肷��
// 1�ȏォ��12�ȉ��̐��l�͌��Ɛ�����1��Ԃ�
// 0�܂���12���傫���V���ȉ��̐��l�Ȃ�N�Ɛ�����2��Ԃ�
// ����ȊO�Ȃ�0��Ԃ�
int MonthOrYear(const wchar_t *str, int *out)
{
	if (str && str[0] && isdigit(str[0]))
	{
		if (str[1] == L'\0' || str[2] == L'\0' || str[3] == L'\0' || str[4] == L'\0' ||
			str[5] == L'\0' || str[6] == L'\0' || str[7] == L'\0' || str[8] == L'\0')
		{
			const int n = _wtoi(str);
			if (out) *out = n;
			return (1 <= n && n <= 12) ? 1 : 2;
		}
	}
	if (out)
		*out = 0;
	return 0;
}

//�w�肳�ꂽ�N���̃J�����_�[��\������
void PrintCal(int year, int month)
{
	printf("%9d�N%2d��\n", year, month);
	printf("�� �� �� �� �� �� �y\n");
	// ���݂̌���1�������j�������ׂ�
	int w = GetFirstDayOfWeek(year, month);
	// ���݂̌��̓����𒲂ׂ�
	const int d = NumberOfDays(year, month);
	for (int i = 0; i < w; i++) printf(i ? "   " : "  ");
	for (int i = 1; i <= d; i++, w++)
	{
		printf(w % 7 ? "%3d" : "%2d", i);
		if (w % 7 == 6) printf("\n");
	}
	// �Ō�Ɉ�s��s��ǉ�
	if (w % 7 != 0) printf("\n");
	printf("\n");
}

int wmain(int argc, wchar_t*argv[])
{
	int year = 0, month = 0;
	if (argc == 1)
	{
		time_t t = time(0);
		struct tm l = {};
		errno_t error = localtime_s(&l, &t);
		if (error != 0) {
			return 0;
		}
		year = l.tm_year + 1900;
		month = l.tm_mon + 1;
	}
	else if (argc == 2 || argc == 3)
	{
		int n[2];
		for (int i = 0; i < argc - 1; i++)
		{
			switch (MonthOrYear(argv[i + 1], &n[i]))
			{
			case 1:
				month = n[i];
				break;
			case 2:
				year = n[i];
				break;
			}
		}
	}
	if (year > 0 && month > 0)
		PrintCal(year, month);
	return 0;
}