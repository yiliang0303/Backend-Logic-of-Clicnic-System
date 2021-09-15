#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<windows.h>
#include "patientVisit.h"
#include "patientInformationModule.h"
#include "medicalSuppliesModule.h"
#pragma warning(disable:4996)

void functions()
{
	animation1("\n===================================\n");
	animation1("1. Add patient information \n");
	animation1("2. Search patient information \n");
	animation1("3. Modify patient information \n");
	animation1("4. Display patient information \n");
	animation1("5. Delete patient information \n");
	animation1("6. Exit \n");
}
void addInfo()
{
	system("cls");
	INFO patientInfo;
	char respond;
	FILE*aptr;
	aptr = fopen("PatientVisit.txt", "a");
	if (aptr == NULL)
	{
		printf("Error opening file.");
		exit(-1);
	}
	do
	{
		printf("Staff in-charged: ");
		scanf(" %[^\n]", patientInfo.staff);

		do
		{
			printf("Patient ID: ");
			scanf(" %[^\n]", patientInfo.patientID);
		} while (IDvalidation(patientInfo.patientID) || strlen(patientInfo.patientID) != 7);

		printf("Name of patient: ");
		scanf(" %[^\n]", patientInfo.name);

		printf("Date of visit: ");
		scanf(" %d/%d/%d", &patientInfo.visitDate.day, &patientInfo.visitDate.month, &patientInfo.visitDate.year);

		rewind(stdin);
		printf("Remarks: ");
		scanf("%[^\n]", patientInfo.remarks);

		printf("Charges: ");
		scanf(" %lf", &patientInfo.charges);

		fprintf(aptr, "%s|%s|%d-%d-%d|%s|%.2f|%s\n", patientInfo.patientID, patientInfo.name, patientInfo.visitDate.day, patientInfo.visitDate.month, patientInfo.visitDate.year, patientInfo.remarks, patientInfo.charges, patientInfo.staff);

		printf("Would you like to continue?(Y/N) : ");
		scanf(" %c", &respond);

		respond = toupper(respond);

	} while (respond == 'Y');
	fclose(aptr);

}
void searchInfo()
{
	system("cls");
	INFO patientInfo[1000];
	char searchID[50];
	int i = 0, count, x = 0;
	FILE*sptr;
	sptr = fopen("PatientVisit.txt", "r");
	if (sptr == NULL)
	{
		printf("Error opening file.");
		exit(-1);
	}

	while (fscanf(sptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%lf|%[^\n]\n", patientInfo[i].patientID, patientInfo[i].name, &patientInfo[i].visitDate.day, &patientInfo[i].visitDate.month, &patientInfo[i].visitDate.year, patientInfo[i].remarks, &patientInfo[i].charges, patientInfo[i].staff) != EOF)
		i++;

	do
	{
		printf("Enter patient ID: ");
		scanf(" %[^\n]", searchID);
	} while (IDvalidation(searchID) || strlen(searchID) != 7);

	count = i;
	for (x = 0; x < count; x++)
	{
		if (strcmp(searchID, patientInfo[x].patientID) == 0)
		{
			printf("\\****************************************************************************************************************\n");
			printf("Patient ID\t\tPatient Name\tVisit Date\t\tRemarks\t\tCharges\n");
			printf("\\****************************************************************************************************************\n");
			printf("%s\t\t%s\t\t%d-%d-%d\t\t%s\t\t%.2f\t%s\n", patientInfo[x].patientID, patientInfo[x].name, patientInfo[x].visitDate.day, patientInfo[x].visitDate.month, patientInfo[x].visitDate.year, patientInfo[x].remarks, patientInfo[x].charges, patientInfo[x].staff);
		}
	}

	fclose(sptr);

}
void modifyInfo()
{
	system("cls");
	INFO patientInfo[1000];
	int i = 0, count, modifyCount = 0;
	char respond, searchID[50];
	FILE*m1ptr;
	m1ptr = fopen("PatientVisit.txt", "r");

	if (m1ptr == NULL)
	{
		printf("Error opening file.");
		exit(-1);
	}

	while (fscanf(m1ptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%lf|%[^\n]\n", patientInfo[i].patientID, patientInfo[i].name, &patientInfo[i].visitDate.day, &patientInfo[i].visitDate.month, &patientInfo[i].visitDate.year, patientInfo[i].remarks, &patientInfo[i].charges, patientInfo[i].staff) != EOF)
		i++;

	count = i;
	do
	{
		do
		{
			printf("Enter patient ID to modify: ");
			scanf(" %s", searchID);
		} while (IDvalidation(searchID) || strlen(searchID) != 7);

		for (i = 0; i < count; i++)
		{
			if (strcmp(searchID, patientInfo[i].patientID) == 0)
			{
				printf("New Patient ID :");
				scanf(" %s", patientInfo[i].patientID);
			}
		}
		++modifyCount;
		printf("Do you want to continue modify (y=yes) : ");
		scanf(" %c", &respond);


	} while (toupper(respond) == 'Y');
	fclose(m1ptr);

	FILE*m2ptr;
	m2ptr = fopen("PatientVisit.txt", "w");

	if (m2ptr == NULL)
	{
		printf("Error opening file.");
		exit(-1);
	}

	for (i = 0; i < count; i++)
	{
		fprintf(m2ptr, "%s|%s|%d-%d-%d|%s|%.2f|%s\n", patientInfo[i].patientID, patientInfo[i].name, patientInfo[i].visitDate.day, patientInfo[i].visitDate.month, patientInfo[i].visitDate.year, patientInfo[i].remarks, patientInfo[i].charges, patientInfo[i].staff);
	}

	fclose(m2ptr);
}
void displayInfomation()
{
	system("cls");
	INFO patientInfo;
	FILE*dptr;
	dptr = fopen("PatientVisit.txt", "r");
	if (dptr == NULL)
	{
		printf("Error opening file.");
		exit(-1);
	}
	printf("\\****************************************************************************************************************\n");
	printf("Patient ID\tPatient Name\tVisit Date\t\tRemarks\t\tCharges\t\tStaff\n");
	printf("\\****************************************************************************************************************\n");
	while (fscanf(dptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%lf|%[^\n]\n", patientInfo.patientID, patientInfo.name, &patientInfo.visitDate.day, &patientInfo.visitDate.month, &patientInfo.visitDate.year, patientInfo.remarks, &patientInfo.charges, patientInfo.staff) != EOF)
	{
		printf("%s\t\t%s\t\t%d-%d-%d\t\t%s\t\t%.2f\t\t%s\n", patientInfo.patientID, patientInfo.name, patientInfo.visitDate.day, patientInfo.visitDate.month, patientInfo.visitDate.year, patientInfo.remarks, patientInfo.charges, patientInfo.staff);
	}
	fclose(dptr);
}
void deleteInfo()
{
	system("cls");
	INFO patientInfo[1000];
	int i = 0,j=0, k = 0;//j is updated item spot,k is total amount of patient
	char searchID[20];
	FILE*dptr = fopen("PatientVisit.txt", "r");
	if (dptr == NULL) {
		printf("Error in file opening...\n");
		exit(-1);
	}
	int found = 0;
	do
	{
		printf("Which ID do you want to delete: ");
		scanf("%[^\n]", searchID);
		rewind(stdin);
	} while (IDvalidation(searchID) || strlen(searchID) != 7);

	while (fscanf(dptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%lf|%[^\n]\n", patientInfo[i].patientID, patientInfo[i].name, &patientInfo[i].visitDate.day,
		&patientInfo[i].visitDate.month, &patientInfo[i].visitDate.year, patientInfo[i].remarks, &patientInfo[i].charges, patientInfo[i].staff) != EOF)
	{
		++i;
		++k;
	}
	int condition = k;
	for (i = 0; j < condition; i++)
	{
		if (strcmp(searchID, patientInfo[i].patientID) == 0)
		{
			j = i + 1;
			patientInfo[i] = patientInfo[j];
			k = k - 1;
		}
		else
		{
			patientInfo[i] = patientInfo[j];
		}
		j++;
	}
	fclose(dptr);


	FILE*dptr1 = fopen("PatientVisit.txt", "w");

	if (dptr1 == NULL) {
		printf("Error opening file.");
		exit(-1);
	}

	for (int k = 0; k < i; k++)
	{
		fprintf(dptr1, "%s|%s|%d-%d-%d|%s|%lf|%s\n", patientInfo[k].patientID, patientInfo[k].name, patientInfo[k].visitDate.day, patientInfo[k].visitDate.month, patientInfo[k].visitDate.year, patientInfo[k].remarks, patientInfo[k].charges, patientInfo[k].staff);
	}
	fclose(dptr1);

	
}
void visit()
{
	int choice;
	do 
	{
		functions();
		printf("Select your choice: ");
		scanf(" %d", &choice);
		rewind(stdin);
		switch (choice)
		{
		case 1:addInfo();
			break;
		case 2:searchInfo();
			break;
		case 3:modifyInfo();
			break;
		case 4:displayInfomation();
			break;
		case 5:deleteInfo();
			break;
		case 6:printf("Thank you for using our services.Please come again.\n");
			break;
		default:printf("Thank you.\n");
			break;
		}
	} while (choice != 6);

	system("pause");
}