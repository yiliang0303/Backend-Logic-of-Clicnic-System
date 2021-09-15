#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include "patientAppointmentsModule.h"
#include "patientInformationModule.h"
#include "medicalSuppliesModule.h"
#pragma warning (disable : 4996)

void registerApp()     //All character will be toupper -1
{
	FILE*fptr = fopen("Appointment.bin", "wb");

	if (fptr == NULL) {
		printf("Error in file opening...\n");
		exit(-1);
	}

	int counter = 0, i = 0, num = 0;
	char response;
	Module app[1000];


	do
	{
		printf("=========================================================================\n");
		printf("\nNo.%d", ++num);
		printf("\nToday's Date(DD/MM/YY)    :");
		scanf("%d/%d/%d", &app[i].date.day, &app[i].date.month, &app[i].date.year);
		rewind(stdin);
		printf("Staff on Duty             :");
		scanf("%[^\n]", &app[i].staff);
		rewind(stdin);
		printf("Appointment Date(DD/MM/YY):");
		scanf("%d/%d/%d", &app[i].appDate.day, &app[i].appDate.month, &app[i].appDate.year);
		rewind(stdin);
		printf("Appointment Time(xx:xx)   :");
		scanf("%d:%d", &app[i].time.hour, &app[i].time.minutes);
		rewind(stdin);
		printf("Patient Name              :");
		scanf("%[^\n]", &app[i].patient);
		rewind(stdin);
		do
		{
			printf("ID                        :");
			scanf("%s", &app[i].id);
			rewind(stdin);
		} while (IDvalidation(app[i].id) || strlen(app[i].id) != 7);

		printf("Preferred Doctor          :");
		scanf("%[^\n]", &app[i].doctor);
		rewind(stdin);
		printf("Any Remarks :             :");
		scanf("%[^\n]", app[i].remark);
		rewind(stdin);

		fwrite(&app[i], sizeof(Module), 1, fptr);

		printf("=========================================================================\n");
		printf("Need to Continue?(y/n)  :");
		scanf(" %c", &response);
		counter++;

	} while (toupper(response) == 'Y');

	printf("\nAppointment add on:%d\n", counter);
	printf("=========================================================================\n");
	//return menu

	fclose(fptr);
}

void searchApp()      //All character will be toupper -1				//The record which is found cant found again -2
{
	FILE*sptr = fopen("Appointment.bin", "rb");


	if (sptr == NULL)
	{
		printf("Error in file opening...\n");
		exit(-1);
	}
	fclose(sptr);
	Module app;
	char userID[20];
	char ask;
	int found = 0;

	do
	{
		sptr = fopen("Appointment.bin", "rb");
		printf("=========================================================================\n");
		do
		{
			printf("Enter the user.ID for searching >>");
			scanf("%s", userID);
			rewind(stdin);
		} while (IDvalidation(userID) || strlen(userID) != 7);

		while (fread(&app, sizeof(Module), 1, sptr) != 0)
		{
			if (strcmp(app.id, userID) == 0)
			{
				found = 1;
				printf("=========================================================================\n");
				printf("\nToday's Date(DD/MM/YY)    :%d/%d/%d\n", app.date.day, app.date.month, app.date.year);
				printf("Staff on Duty             :%s\n", app.staff);
				printf("Appointment Date(DD/MM/YY):%d/%d/%d\n", app.appDate.day, app.appDate.month, app.appDate.year);
				printf("Appointment Time          :%d:%d\n", app.time.hour, app.time.minutes);
				printf("Patient Name              :%s\n", app.patient);
				printf("ID                        :%s\n", app.id);
				printf("Preferred Doctor          :%s\n", app.doctor);
				printf("Any Remarks :             :%s\n\n", app.remark);
				printf("=========================================================================\n");
			}
		}
		fclose(sptr);

		if (found == 0)
		{
			printf("\n\n******************************");
			printf("Invalid Input");
			printf("******************************\n\n");
		}

		printf("Searching record?(y=yes/other=no) >>");
		scanf(" %c", &ask);

	} while (toupper(ask) == 'Y');

}

void editApp()
{
	FILE*sptr = fopen("Appointment.bin", "rb");


	if (sptr == NULL) {
		printf("Error in file opening...\n");
		exit(-1);
	}

	Module app[1000];
	char response;
	char userID[20];
	int i = 0, found = 0, x = 0, a;


	do
	{
		printf("=========================================================================\n");
		do
		{
			printf("Enter the user.ID for searching >>");
			scanf("%s", userID);
			rewind(stdin);
		} while (IDvalidation(userID) || strlen(userID) != 7);

		while (fread(&app[x], sizeof(Module), 1, sptr) != 0)
		{
			if (strcmp(app[x].id, userID) == 0)
			{
				found = 1;
				a = x;
				printf("=========================================================================\n");
				printf("Before Editing..............\n");
				printf("=========================================================================\n");
				printf("\nToday's Date(DD/MM/YY)    :%d/%d/%d\n", app[x].date.day, app[x].date.month, app[x].date.year);
				printf("Staff on Duty             :%s\n", app[x].staff);
				printf("Appointment Date(DD/MM/YY):%d/%d/%d\n", app[x].appDate.day, app[x].appDate.month, app[x].appDate.year);
				printf("Appointment Time          :%d:%d\n", app[x].time.hour, app[x].time.minutes);
				printf("Patient Name              :%s\n", app[x].patient);
				printf("ID                        :%s\n", app[x].id);
				printf("Preferred Doctor          :%s\n", app[x].doctor);
				printf("Any Remarks :             :%s\n\n", app[x].remark);
			}
			x++;
		}
		fclose(sptr);

		FILE*wptr = fopen("Appointment.bin", "wb");

		if (wptr == NULL) {
			printf("Error in file opening...\n");
			exit(-1);
		}


		if (found = 1)
		{
			printf("=========================================================================\n");
			printf("EDITING..................\n");
			printf("=========================================================================\n");
			printf("\nToday's Date(DD/MM/YY)    :");
			scanf("%d/%d/%d", &app[a].date.day, &app[a].date.month, &app[a].date.year);
			rewind(stdin);
			printf("Staff on Duty             :");
			scanf("%[^\n]", &app[a].staff);
			rewind(stdin);
			printf("Appointment Date(DD/MM/YY):");
			scanf("%d/%d/%d", &app[a].appDate.day, &app[a].appDate.month, &app[a].appDate.year);
			rewind(stdin);
			printf("Appointment Time          :");
			scanf("%d:%d", &app[a].time.hour, &app[a].time.minutes);
			rewind(stdin);
			printf("Patient Name              :");
			scanf("%[^\n]", &app[a].patient);
			rewind(stdin);
			printf("ID                        :");
			scanf("%s", &app[a].id);
			rewind(stdin);
			printf("Preferred Doctor          :");
			scanf("%[^\n]", &app[a].doctor);
			rewind(stdin);
			printf("Any Remarks :             :");
			scanf("%[^\n]", app[a].remark);
			rewind(stdin);
			printf("=========================================================================\n");
		}
		else
		{
			printf("\n\n******************************");
			printf("Invalid Input");
			printf("******************************\n\n");
		}
		for (int k = 0; k < x; k++)
		{

			fwrite(&app[k], sizeof(Module), 1, wptr);
		}

		fclose(wptr);
		printf("=========================================================================\n");
		printf("New Data..................\n");
		printf("");
		printf("=========================================================================\n");
		printf("Need to Continue?(y/n)  :");
		scanf(" %c", &response);
	} while (toupper(response) == 'Y');

}

void viewApp()
{
	FILE*vptr = fopen("Appointment.bin", "rb");


	if (vptr == NULL) {
		printf("Error in file opening...\n");
		exit(-1);
	}

	Module app[1000];
	int i = 0;
	int num = 0;

	printf("=========================================================================\n");
	printf("|\t\t\tThe Appointment Details\t\t\t\t|\n");

	while (fread(&app, sizeof(Module), 1, vptr) != 0)
	{
		printf("=========================================================================\n");
		printf("\nNo.%d", ++num);
		printf("\nToday's Date(DD/MM/YY)    :%d/%d/%d\n", app[i].date.day, app[i].date.month, app[i].date.year);
		printf("Staff on Duty             :%s\n", app[i].staff);
		printf("Appointment Date(DD/MM/YY):%d/%d/%d\n", app[i].appDate.day, app[i].appDate.month, app[i].appDate.year);
		printf("Appointment Time          :%d:%d\n", app[i].time.hour, app[i].time.minutes);
		printf("Patient Name              :%s\n", app[i].patient);
		printf("ID                        :%s\n", app[i].id);
		printf("Preferred Doctor          :%s\n", app[i].doctor);
		printf("Any Remarks :             :%s\n", app[i].remark);
		printf("=========================================================================\n");
	}

	fclose(vptr);
}

void deleteApp()
{
	FILE*dptr = fopen("Appointment.bin", "rb");


	if (dptr == NULL) {
		printf("Error in file opening...\n");
		exit(-1);
	}

	Module app[1000];
	int x = 0, a;
	char userId[20];
	char yn;
	int found = 0;

	do
	{
		printf("=========================================================================\n");
		printf("Which ID want to delete???       :");
		scanf("%s", userId);
		rewind(stdin);
		printf("=========================================================================\n");
		while (strlen(userId) != 7 || IDvalidation(userId))
		{
			printf("**************************\n");
			printf("Incorrect input!\n");
			printf("**************************\n");
			printf("ID                        :");
			scanf("%s", &userId);
			rewind(stdin);

		}
		while (fread(&app[x], sizeof(Module), 1, dptr) != 0)
		{
			if (strcmp(app[x].id, userId) == 0)
			{
				found = 1;
				a = x;
				printf("=========================================================================\n");
				printf("Before Deleting..............\n");
				printf("=========================================================================\n");
				printf("\nToday's Date(DD/MM/YY)    :%d/%d/%d\n", app[x].date.day, app[x].date.month, app[x].date.year);
				printf("Staff on Duty             :%s\n", app[x].staff);
				printf("Appointment Date(DD/MM/YY):%d/%d/%d\n", app[x].appDate.day, app[x].appDate.month, app[x].appDate.year);
				printf("Appointment Time          :%d:%d\n", app[x].time.hour, app[x].time.minutes);
				printf("Patient Name              :%s\n", app[x].patient);
				printf("ID                        :%s\n", app[x].id);
				printf("Preferred Doctor          :%s\n", app[x].doctor);
				printf("Any Remarks :             :%s\n\n", app[x].remark);
			}
			x++;
		}
		fclose(dptr);


		FILE*wptr = fopen("Appointment.bin", "wb");

		if (wptr == NULL) {
			printf("Error in file opening...\n");
			exit(-1);
		}




		for (int k = 0; k < x; k++)
		{
			k = k + 1;
			fwrite(&app[k], sizeof(Module), 1, dptr);

		}
		printf("=========================================================================\n");
		printf("This record has been deleted!!!\n");
		printf("=========================================================================\n");
		fclose(wptr);
		printf("=========================================================================\n");
		printf("Need to Continue?(y/n)  :");
		scanf(" %c", &yn);

	} while (toupper(yn) == 'Y');

}

void appointment()
{
	int function;


	do {

		animation1("1.Register Appointment \n");
		animation1("2.Search Appointment \n");
		animation1("3.Edit Appointment \n");
		animation1("4.View All Appointment \n");
		animation1("5.Delete Appointment\n");
		animation1("6.back To Menu\n");



		printf("\nWhat function you choose?>>>");
		scanf(" %d", &function);


		switch (function)
		{
		case 1:
			registerApp();
			break;
		case 2:
			searchApp();
			break;
		case 3:
			editApp();
			break;
		case 4:
			viewApp();
			break;
		case 5:
			deleteApp();
			break;
		default:
			printf("menu\n");
		}

	} while (function != 6);


	system("pause");

}