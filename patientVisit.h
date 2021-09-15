#pragma once

void functions();
void addInfo();
void searchInfo();
void modifyInfo();
void displayInfomation();
void deleteInfo();
void visit();

struct DATE
{
	int day, month, year;
};
typedef struct
{
	char staff[50];
	char name[50];
	struct DATE visitDate;
	char patientID[20];
	char remarks[50];
	double charges;
}INFO;
