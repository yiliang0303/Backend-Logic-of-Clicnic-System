#pragma once

void registerApp();
void searchApp();
void editApp();
void viewApp();
void deleteApp();
void appointment();

struct Date {
	int day, month, year;

};

struct Time {
	int minutes, hour;
};

typedef struct {
	struct Time time;
	struct Date date, appDate;
	char staff[30];
	char patient[30];
	char id[20];
	char doctor[30];
	char remark[60];

}Module;
