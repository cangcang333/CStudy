#include <stdio.h>
#include <stdlib.h>

/* This function returns non-zero if year is a leap year. Must use 4 digits years. */
int leap_year(int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

char *day_of_week(int day, int month, int year)
{
	int cent;
	char *dayofweek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

	/* Adjust months so February is the last one */
	month -= 2;
	if (month < 1)
	{
		month += 12;
		year--;
	}
	/* Split by centery */
	cent = year / 100;
	year %= 100;
	return (dayofweek[((26 * month - 2) / 10 + day + year + year / 4 + cent / 4 + 5 * cent) % 7]);
}

int main(int argc, char **argv)
{
	int year = 2019;
	if (leap_year(year))
	{
		printf("%d is a leap year\n", year);
	}
	else
	{
		printf("%d is not a leap year\n", year);
	}

	int day = 15;
	int month = 6;
	char *dayofweek;
//	dayofweek = (char *)malloc(sizeof(char) * 10);
	dayofweek = day_of_week(day, month, year);
	printf("day of week is %s\n", dayofweek);

	return 0;
}
