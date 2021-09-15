//1DCN1
//Lee Jia Zhe - 18PMD06178

//preprocessor directivses
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "medicalSuppliesModule.h"
#pragma warning (disable : 4996)

//main part of this module


//void main()
//{
//	logo(); //call logo function
//
//	system("color F0"); //able to use this because we used #include <stdlib.h>
//
//	mainMenu(); //
//
//	system("pause");
//}

void logo() { //show the user the logo
	system("color 08");
	delay(7000);
	system("color F0");
	delay(7000);
	animation1(" |=================================================================================| \n");
	animation1(" | 01010111  11010101  111010       11010101  11        10  11    01  10  11010101 | \n");
	animation1(" | 11    01  00        00    01     00        00        10  001   10  10  00       | \n");
	animation1(" | 00111100  10        01     1     10        01        01  01 0  10  01  10       | \n");
	animation1(" | 01        11        11    11     11        01        00  10  0100  00  11       | \n");
	animation1(" | 00        01011110  000100       01011110  11101110  11  01   111  11  01011110 | \n");
	animation1(" |=================================================================================| \n\a\n");
	system("color FC");
	delay(7000);
	system("color F9");
	delay(7000);
	system("color F3");
	delay(7000);
	system("color F2");
	delay(7000);
	system("color F6");
	delay(7000);
	system("color F5");
	delay(7000);
	system("color F8");
	delay(7000);
	system("color F0");
}

void mainMenu() {
	medicalSuppliesMenu();
	/*
	int select;
	do {
	printf("\n\n");
	animation1(" |========================|\n");
	animation1(" | Main Menu              |\n");
	animation1(" |========================|\n");
	animation1(" | Pateint Menu     : (1) |\n");
	animation1(" | Pateint Checkout : (2) |\n");
	animation1(" | Staff Details    : (3) |\n");
	animation1(" | Medical Supplies : (4) |\n");
	animation1(" | Exit             :Other|\n");
	animation1(" |========================|\n");
	animation1(" Please Select > ");
	scanf("%d", &select); rewind(stdin);

	switch (select) {
	case 1:
	break;
	case 2:
	break;
	case 3:
	break;
	case 4:
	medicalSuppliesMenu();
	break;
	case 5:
	break;
	case 6:
	break;
	default:
	printf(" <Incorrect Input> \n");
	break;
	}
	} while (select != 6);*/
}

void medicalSuppliesMenu() {
	viewInventory();
	register int select;
	do {
		printf("\n\n");
		animation1(" |==================================|\n");
		animation1(" |        Medical Supply Menu       |\n");
		animation1(" |==================================|\n");
		animation1(" | Add New Medical Supplies   : (1) |\n");
		animation1(" | Search Supply Inventory    : (2) |\n");
		animation1(" | Edit Supply Details        : (3) |\n");
		animation1(" | Change Stock Inventory(Qty): (4) |\n");
		animation1(" | Delete Medical Supplies    : (5) |\n");
		animation1(" | Sort Stock Inventory       : (6) |\n");
		animation1(" | View Stock Inventory       : (7) |\n");
		animation1(" | EXIT To Main Menu          : (8) |\n");
		animation1(" |==================================|\n");

		select = selectOption();

		system("color F0");
		switch (select) {
		case 1:
			addNewSupplies();
			break;
		case 2:
			searchSupplies();
			break;
		case 3:
			editDetails();
			break;
		case 4:
			changeStock();
			break;
		case 5:
			deleteSupplies();
			break;
		case 6:
			sortInventory();
			break;
		case 7:
			viewInventory();
			break;
		case 8:
			break;
		default:
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
			break;
		}
	} while (select != 8);
}

int selectOption() {
	int select;
	do {
		select = 0;
		animation1(" Please Select > ");
		scanf("%d", &select); rewind(stdin);
		if (select == 0) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (select == 0); //Validation(to avoid user from entering something unreadable by %d such as a char
	return select;
}

//the functions below are to be used in the sub-functions
int checkManuYear(int itemYear) {
	if (2000 <= itemYear && itemYear <= 2018)
		return 1;
	else
		return 0;
}
int checkExpiYear(int itemYear, int itemExYear) {
	if (itemYear < itemExYear && itemExYear <= 2030)
		return 1;
	else
		return 0;
}
int checkMonth(int itemMonth) {
	if (itemMonth <= 12 && itemMonth > 0)
		return 1;
	else
		return 0;
}
void checkDay(int itemMonth, int itemDay, int *correct) {
	int dateLimit = 0;
	switch (itemMonth) {
	case 1:
		dateLimit = 31; break;
	case 2:
		dateLimit = 28; break;
	case 3:
		dateLimit = 31; break;
	case 4:
		dateLimit = 30; break;
	case 5:
		dateLimit = 31; break;
	case 6:
		dateLimit = 30; break;
	case 7:
		dateLimit = 31; break;
	case 8:
		dateLimit = 31; break;
	case 9:
		dateLimit = 30; break;
	case 10:
		dateLimit = 31; break;
	case 11:
		dateLimit = 30; break;
	case 12:
		dateLimit = 31; break;
	}
	if (dateLimit >= itemDay && itemDay > 0)
		*correct = 1;
	else
		*correct = -1;
}
int checkQty(int itemQty) {
	if (itemQty >= 0 && itemQty <= 99999)
		return 1;
	else
		return -1;
}
int checkPrice(double itemPrice) {
	if (itemPrice >= 0 && itemPrice <= 99999)
		return 1;
	else
		return 0;
}

void addNewSupplies() {
	int i = 0, error, checking = 0, correct = 0; double itemPrice = 0;
	int itemYear = 0, itemMonth = 0, itemDay = 0, itemExYear = 0, itemExMonth = 0, itemExDay = 0, itemQty = -1;

	printf("  New Medine Entry  \n");
	printf(" ================== \n");

	
		char inputItemID[100] = "", itemID[8] = "Y";
		printf(" Enter Medical Supply ID: Y");
		scanf("%[^\n]", inputItemID); rewind(stdin);
		while (strlen(inputItemID) != 6) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> <MUST HAVE 6 DIGITS> \n");
			printf(" Enter Medical Supply ID: Y");
			scanf("%[^\n]", &inputItemID); rewind(stdin);
		}
		system("color F0");
		strcat(itemID, inputItemID);
		strcpy(Supplies[i].itemID, itemID);

	

	system("color F0");

	FILE *addNew;
	addNew = fopen("medicalSupplies.txt", "a");
	if (addNew == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	printf(" Enter Medical Supply Name: ");
	scanf("%[^\n]", Supplies[i].itemName); rewind(stdin);
	while (strlen(Supplies[i].itemName) > 30) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		printf(" Enter Medical Supply Name: ");
		scanf("%[^\n]", Supplies[i].itemName); rewind(stdin);
	}
	system("color F0");

	do { //Get Manufacture Year(2000-2018)
		printf(" Enter Manufacture Year   : ");
		scanf("%d", &itemYear); rewind(stdin);
		checking = checkManuYear(itemYear);
		if (checking == 0) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (checkManuYear(itemYear) == 0);
	Supplies[i].manuftDate.year = itemYear;
	system("color F0");

	do { //Get Manufacture Month(1-12)
		printf(" Enter Manufacture Month  : ");
		scanf("%d", &itemMonth); rewind(stdin);
		checking = checkMonth(itemMonth);
		if (checking == 0) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (checking == 0);
	Supplies[i].manuftDate.month = itemMonth;
	system("color F0");

	do { //Get Manufacture Day based on Manufacture Month
		printf(" Enter Manufacture Day    : ");
		scanf("%d", &itemDay); rewind(stdin);
		checkDay(itemMonth, itemDay, &correct);
		checking = correct;
		if (checking != 1) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (checking != 1);
	Supplies[i].manuftDate.day = itemDay;
	system("color F0");

	do { //Get Expiry Year(itemYear-2030)
		printf(" Enter Expiry Year        : ");
		scanf("%d", &itemExYear); rewind(stdin);
		checking = checkExpiYear(itemYear, itemExYear);
		if (checking == 0) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (checking == 0);
	Supplies[i].expiryDate.year = itemExYear;
	system("color F0");

	do { //Get Expiry Month(1-12)
		printf(" Enter Expiry Month       : ");
		scanf("%d", &itemExMonth); rewind(stdin);
		checking = checkMonth(itemExMonth);
		if (checking == 0) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (checking == 0);
	Supplies[i].expiryDate.month = itemExMonth;
	system("color F0");

	do { //Get Expiry Day based on Expiry Month
		printf(" Enter Expiry Day         : ");
		scanf("%d", &itemExDay); rewind(stdin);
		checkDay(itemExMonth, itemExDay, &correct);
		checking = correct;
		if (checking != 1) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (checking != 1);
	Supplies[i].expiryDate.day = itemExDay;
	system("color F0");

	printf(" Manufacturer/Country     : ");
	scanf("%[^\n]", Supplies[i].fromWhere); rewind(stdin);
	while (strlen(Supplies[i].fromWhere) > 30) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		printf(" Enter Medical Supply Name: ");
		scanf("%[^\n]", Supplies[i].fromWhere); rewind(stdin);
	}
	system("color F0");

	printf(" Quantity of New Supplies : "); //Get Qty(0-99999)
	scanf("%d", &itemQty); rewind(stdin);
	checking = checkQty(itemQty);
	for (; checking != 1;) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		printf(" Quantity of New Supplies : "); //Get Qty(0-99999)
		scanf("%d", &itemQty); rewind(stdin);
		checking = checkQty(itemQty);
	}
	Supplies[i].stock = itemQty;
	system("color F0");

	do { //Get Price Per Supply(0-99999)
		printf(" Enter Price Per Supply   : ");
		scanf("%lf", &itemPrice); rewind(stdin);
		checking = checkPrice(itemPrice);
		if (checking == 0) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (checking == 0);
	Supplies[i].price = itemPrice;
	system("color F0");

	fprintf(addNew, "%s|%s|%02d-%02d-%02d|%02d-%02d-%02d|%s|%d|%.2f\n", Supplies[i].itemID, Supplies[i].itemName, Supplies[i].manuftDate.day, Supplies[i].manuftDate.month, Supplies[i].manuftDate.year,
		Supplies[i].expiryDate.day, Supplies[i].expiryDate.month, Supplies[i].expiryDate.year, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
	fclose(addNew);

	viewInventory();
	printf(" | Successfully Added New Medical Supply   |\n");
	printf(" |=========================================|\n\n");
}

void searchSupplies() {
	int select;
	do {
		printf("\n\n");
		animation1(" |===========================|\n");
		animation1(" | Search By?                |\n");
		animation1(" |===========================|\n");
		animation1(" | Item ID             : (1) |\n");
		animation1(" | Item Name           : (2) |\n");
		animation1(" | Manufacture Year    : (3) |\n");
		animation1(" | Expiry Year         : (4) |\n");
		animation1(" | Manufacturer/Country: (5) |\n");
		animation1(" | Price               : (6) |\n");
		animation1(" | Exit From Here      : (7) |\n");
		animation1(" |===========================|\n");
		do {
			select = 0;
			animation1(" Please Select > ");
			scanf("%d", &select); rewind(stdin);
			if (select == 0) {
				system("color FC"); printf("\a");
				printf(" <INVALID INPUT> \n");
			}
		} while (select == 0); //Validation(to avoid user from entering something unreadable by %d such as a char
		system("color F0");
		switch (select) {
		case 1:
			searchByID();
			break;
		case 2:
			searchByName();
			break;
		case 3:
			searchByManuYear();
			break;
		case 4:
			searchByExpiYear();
			break;
		case 5:
			searchByMaker();
			break;
		case 6:
			searchByPrice();
			break;
		case 7:
			break;
		default:
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
			break;
		}
	} while (select != 7);
}

//below are functions to be called by searchSupplies based on switch
void searchByID() {
	FILE *searchID;
	searchID = fopen("medicalSupplies.txt", "r");
	if (searchID == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0;
	char inputItemID[100] = "", itemID[8] = "Y";
	printf(" Enter Medical Supply ID: Y");
	scanf("%[^\n]", inputItemID); rewind(stdin);
	while (strlen(inputItemID) != 6) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		printf(" Enter Medical Supply ID: Y");
		scanf("%[^\n]", &inputItemID); rewind(stdin);
	}
	strcat(itemID, inputItemID);
	system("color F0");

	printf("\n\n |===========================================================================================================================================| \n");
	printf(" |                                                        Medical Supplies Inventory                                                         | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Item ID |           Item Name           | Manufacture Date |   Expiry Date    |      Manufacturer/Country      | Stock | Price(per stock) | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	while (fscanf(searchID, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		if (strcmp(Supplies[i].itemID, strupr(itemID)) == 0) {
			printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
				Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
			++totalItem;
		}
		++i;
	}
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Number of Medical Supplies Found: %-5d | \n", totalItem);
	printf(" |=========================================|\n");
	fclose(searchID);
}
void searchByName() {
	FILE *searchName;
	searchName = fopen("medicalSupplies.txt", "r");
	if (searchName == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0;
	char itemName[100];
	printf(" Enter Medical Supply Name: ");
	scanf("%[^\n]", itemName); rewind(stdin);
	while (strlen(itemName) > 30) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		printf(" Enter Medical Supply Name: ");
		scanf("%[^\n]", itemName); rewind(stdin);
	}
	system("color F0");

	printf("\n\n |===========================================================================================================================================| \n");
	printf(" |                                                        Medical Supplies Inventory                                                         | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Item ID |           Item Name           | Manufacture Date |   Expiry Date    |      Manufacturer/Country      | Stock | Price(per stock) | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	while (fscanf(searchName, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		if (strcmp(Supplies[i].itemName, itemName) == 0) {
			printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
				Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
			++totalItem;
		}
		++i;
	}
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Number of Medical Supplies Found: %-5d | \n", totalItem);
	printf(" |=========================================|\n");
	fclose(searchName);
}
void searchByManuYear() {
	FILE *searchManuYear;
	searchManuYear = fopen("medicalSupplies.txt", "r");
	if (searchManuYear == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0, checking = 0, manuYear = 0, manuMonth = 0;
	char yesnoMonth = 'N';
	do { //Get Manufacture Year(2000-2018)
		printf(" Enter Manufacture Year : ");
		scanf("%d", &manuYear); rewind(stdin);
		checking = checkManuYear(manuYear);
		if (checking == 0) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (checkManuYear(manuYear) == 0);
	system("color F0");
	printf(" Would you like you also filter by Month(Y=Yes//Others=No)>>");
	scanf("%c", &yesnoMonth); rewind(stdin); //will be 'N' if user entered something unreadable
	yesnoMonth = toupper(yesnoMonth);
	if (yesnoMonth == 'Y') {
		do {
			printf(" Enter Manufacture Month: ");
			scanf("%d", &manuMonth); rewind(stdin);
			checking = checkMonth(manuMonth);
			if (checking == 0) {
				system("color FC"); printf("\a");
				printf(" <INVALID INPUT> \n");
			}
		} while (checking == 0);
	}
	system("color F0");

	printf("\n\n |===========================================================================================================================================| \n");
	printf(" |                                                        Medical Supplies Inventory                                                         | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Item ID |           Item Name           | Manufacture Date |   Expiry Date    |      Manufacturer/Country      | Stock | Price(per stock) | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	while (fscanf(searchManuYear, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		if (manuYear == Supplies[i].manuftDate.year) {
			if (yesnoMonth == 'Y') {
				if (manuMonth == Supplies[i].manuftDate.month) {
					printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
						Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
					++totalItem;
				}
			}
			else {
				printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
					Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
				++totalItem;
			}
		}
		++i;
	}
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Number of Medical Supplies Found: %-5d | \n", totalItem);
	printf(" |=========================================|\n");
	fclose(searchManuYear);
}
void searchByExpiYear() {
	FILE *searchExpiYear;
	searchExpiYear = fopen("medicalSupplies.txt", "r");
	if (searchExpiYear == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0, checking = 0, expiYear = 0, expiMonth = 0;
	char yesnoMonth = 'N';
	printf(" Enter Expiry Year : ");
	scanf("%d", &expiYear); rewind(stdin);
	printf(" Would you like you also filter by Month(Y=Yes//Others=No)>>");
	scanf("%c", &yesnoMonth); rewind(stdin); //will be 'N' if user entered something unreadable
	yesnoMonth = toupper(yesnoMonth);
	if (yesnoMonth == 'Y') {
		do {
			printf(" Enter Expiry Month: ");
			scanf("%d", &expiMonth); rewind(stdin);
			checking = checkMonth(expiMonth);
			if (checking == 0) {
				system("color FC"); printf("\a");
				printf(" <INVALID INPUT> \n");
			}
		} while (checking == 0);
	}
	system("color F0");

	printf("\n\n |===========================================================================================================================================| \n");
	printf(" |                                                        Medical Supplies Inventory                                                         | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Item ID |           Item Name           | Manufacture Date |   Expiry Date    |      Manufacturer/Country      | Stock | Price(per stock) | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	while (fscanf(searchExpiYear, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		if (expiYear == Supplies[i].expiryDate.year) {
			if (yesnoMonth == 'Y') {
				if (expiMonth == Supplies[i].manuftDate.month) {
					printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
						Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
					++totalItem;
				}
			}
			else {
				printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
					Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
				++totalItem;
			}
		}
		++i;
	}
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Number of Medical Supplies Found: %-5d | \n", totalItem);
	printf(" |=========================================|\n");
	fclose(searchExpiYear);
}
void searchByMaker() {
	FILE *searchMaker;
	searchMaker = fopen("medicalSupplies.txt", "r");
	if (searchMaker == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0;
	char maker[100];
	printf(" Enter Maker of Supply: ");
	scanf("%[^\n]", maker); rewind(stdin);
	while (strlen(maker) > 30) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		printf(" Enter Maker of Supply: ");
		scanf("%[^\n]", maker); rewind(stdin);
	}
	system("color F0");

	printf("\n\n |===========================================================================================================================================| \n");
	printf(" |                                                        Medical Supplies Inventory                                                         | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Item ID |           Item Name           | Manufacture Date |   Expiry Date    |      Manufacturer/Country      | Stock | Price(per stock) | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	while (fscanf(searchMaker, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		if (strcmp(Supplies[i].fromWhere, maker) == 0) {
			printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
				Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
			++totalItem;
		}
		++i;
	}
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Number of Medical Supplies Found: %-5d | \n", totalItem);
	printf(" |=========================================|\n");
	fclose(searchMaker);
}
void searchByPrice() {
	FILE *searchPrice;
	searchPrice = fopen("medicalSupplies.txt", "r");
	if (searchPrice == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0, checking = 0;
	double itemPrice;
	do { //Get Price Per Supply(0-99999)
		printf(" Enter Price Per Supply   : ");
		scanf("%lf", &itemPrice); rewind(stdin);
		checking = checkPrice(itemPrice);
		if (checking == 0) {
			system("color FC"); printf("\a");
			printf(" <INVALID INPUT> \n");
		}
	} while (checking == 0);
	system("color F0");

	printf("\n\n |===========================================================================================================================================| \n");
	printf(" |                                                        Medical Supplies Inventory                                                         | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Item ID |           Item Name           | Manufacture Date |   Expiry Date    |      Manufacturer/Country      | Stock | Price(per stock) | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	while (fscanf(searchPrice, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		if (itemPrice == Supplies[i].price) {
			printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
				Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
			++totalItem;
		}
		++i;
	}
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Number of Medical Supplies Found: %-5d | \n", totalItem);
	printf(" |=========================================|\n");
	fclose(searchPrice);
}

void editDetails() {
	viewInventory(); //Shows the user what is in the file first
	FILE *whichDetails;
	whichDetails = fopen("medicalSupplies.txt", "r");
	if (whichDetails == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0, error = 0, select = 0, checking = 0, correct = 0;
	int itemYear = 0, itemMonth = 0, itemDay = 0, itemExYear = 0, itemExMonth = 0, itemExDay = 0;
	double itemPrice = 0;
	char inputItemID[100] = "", itemID[8] = "Y";
	printf(" Which Medical Supply Details To Edit?\n");
	printf(" Enter Medical Supply ID: Y");
	scanf("%[^\n]", inputItemID); rewind(stdin);
	while (strlen(inputItemID) != 6) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT>  <MUST HAVE 6 DIGITS>\n");
		printf(" Enter Medical Supply ID : Y");
		scanf("%[^\n]", &inputItemID); rewind(stdin);
	}
	strcat(itemID, inputItemID);
	system("color F0");

	printf("\n\n |===========================================================================================================================================| \n");
	printf(" |                                                        Medical Supplies Inventory                                                         | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Item ID |           Item Name           | Manufacture Date |   Expiry Date    |      Manufacturer/Country      | Stock | Price(per stock) | \n");
	printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	while (fscanf(whichDetails, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		if (strcmp(Supplies[i].itemID, strupr(itemID)) == 0) {
			printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
				Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
			printf(" |=========|===============================|==================|==================|================================|=======|==================| \n");
			do {
				printf("\n");
				animation1(" |===========================|\n");
				animation1(" | What Do You Want To Edit? |\n");
				animation1(" |===========================|\n");
				animation1(" | Item ID             : (1) |\n");
				animation1(" | Item Name           : (2) |\n");
				animation1(" | Manufacture Date    : (3) |\n");
				animation1(" | Expiry Date         : (4) |\n");
				animation1(" | Manufacturer/Country: (5) |\n");
				animation1(" | Price               : (6) |\n");
				animation1(" | Exit from here      : (7) |\n");
				animation1(" |===========================|\n");
				do {
					select = 0;
					animation1(" Please Select > ");
					scanf("%d", &select); rewind(stdin);
					if (select == 0) {
						system("color FC"); printf("\a");
						printf(" <INVALID INPUT> \n");
					}
				} while (select == 0); //Validation(to avoid user from entering something unreadable by %d such as a char
				system("color F0");
				switch (select) {
				case 1:
				
						i = 0, error = 0;
						strcpy(inputItemID, "");
						strcpy(itemID, "Y");
						printf("\n Enter New Medical Supply ID: Y");
						scanf("%[^\n]", inputItemID); rewind(stdin);
						while (strlen(inputItemID) != 6) {
							system("color FC"); printf("\a");
							printf(" <INVALID INPUT> <MUST HAVE 6 DIGITS> \n");
							printf(" Enter New Medical Supply ID: Y");
							scanf("%[^\n]", inputItemID); rewind(stdin);
						}
						strcat(itemID, inputItemID);
						strcpy(Supplies[i].itemID, itemID);
						system("color F0");

	
					system("color F0");
					break;
				case 2:
					printf(" Enter Medical Supply Name: ");
					scanf("%[^\n]", Supplies[i].itemName); rewind(stdin);
					while (strlen(Supplies[i].itemName) > 30) {
						system("color FC"); printf("\a");
						printf(" <INVALID INPUT> \n");
						printf(" Enter Medical Supply Name: ");
						scanf("%[^\n]", Supplies[i].itemName); rewind(stdin);
					}
					system("color F0");
					break;
				case 3:
					do { //Get Manufacture Year(2000-2018)
						printf(" Enter Manufacture Year   : ");
						scanf("%d", &itemYear); rewind(stdin);
						checking = checkManuYear(itemYear);
						if (checking == 0) {
							system("color FC"); printf("\a");
							printf(" <INVALID INPUT> \n");
						}
					} while (checkManuYear(itemYear) == 0);
					Supplies[i].manuftDate.year = itemYear;
					system("color F0");

					do { //Get Manufacture Month(1-12)
						printf(" Enter Manufacture Month  : ");
						scanf("%d", &itemMonth); rewind(stdin);
						checking = checkMonth(itemMonth);
						if (checking == 0) {
							system("color FC"); printf("\a");
							printf(" <INVALID INPUT> \n");
						}
					} while (checking == 0);
					Supplies[i].manuftDate.month = itemMonth;
					system("color F0");

					do { //Get Manufacture Day based on Manufacture Month
						printf(" Enter Manufacture Day    : ");
						scanf("%d", &itemDay); rewind(stdin);
						checkDay(itemMonth, itemDay, &correct);
						checking = correct;
						if (checking != 1) {
							system("color FC"); printf("\a");
							printf(" <INVALID INPUT> \n");
						}
					} while (checking != 1);
					Supplies[i].manuftDate.day = itemDay;
					system("color F0");

					break;
				case 4:
					do { //Get Expiry Year(Supplies[i].manuftDate.year-2030)
						printf(" Enter Expiry Year        : ");
						scanf("%d", &itemExYear); rewind(stdin);
						checking = checkExpiYear(Supplies[i].manuftDate.year, itemExYear);
						if (checking == 0) {
							system("color FC"); printf("\a");
							printf(" <INVALID INPUT> \n");
						}
					} while (checking == 0);
					Supplies[i].expiryDate.year = itemExYear;
					system("color F0");

					do { //Get Expiry Month(1-12)
						printf(" Enter Expiry Month       : ");
						scanf("%d", &itemExMonth); rewind(stdin);
						checking = checkMonth(itemExMonth);
						if (checking == 0) {
							system("color FC"); printf("\a");
							printf(" <INVALID INPUT> \n");
						}
					} while (checking == 0);
					Supplies[i].expiryDate.month = itemExMonth;
					system("color F0");

					do { //Get Expiry Day based on Expiry Month
						printf(" Enter Expiry Day         : ");
						scanf("%d", &itemExDay); rewind(stdin);
						checkDay(itemExMonth, itemExDay, &correct);
						checking = correct;
						if (checking != 1) {
							system("color FC"); printf("\a");
							printf(" <INVALID INPUT> \n");
						}
					} while (checking != 1);
					Supplies[i].expiryDate.day = itemExDay;
					system("color F0");

					break;
				case 5:
					printf(" Manufacturer/Country     : ");
					scanf("%[^\n]", Supplies[i].fromWhere); rewind(stdin);
					while (strlen(Supplies[i].fromWhere) > 30) {
						system("color FC"); printf("\a");
						printf(" <INVALID INPUT> \n");
						printf(" Enter Medical Supply Name: ");
						scanf("%[^\n]", Supplies[i].fromWhere); rewind(stdin);
					}
					system("color F0");
					break;
				case 6:
					do { //Get Price Per Supply(0-99999)
						printf(" Enter Price Per Supply   : ");
						scanf("%lf", &itemPrice); rewind(stdin);
						checking = checkPrice(itemPrice);
						if (checking == 0) {
							system("color FC"); printf("\a");
							printf(" <INVALID INPUT> \n");
						}
					} while (checking == 0);
					Supplies[i].price = itemPrice;
					system("color F0");
					break;
				case 7:
					break;
				default:
					system("color FC"); printf("\a");
					printf(" <INVALID INPUT> \n");
					break;
				}
			} while (select != 7);
		}
		++i; ++totalItem;
	}
	fclose(whichDetails);

	FILE *changDetails;
	changDetails = fopen("medicalSupplies.txt", "w");
	if (changDetails == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}
	for (i = 0; i < totalItem; i++) {
		fprintf(changDetails, "%s|%s|%02d-%02d-%02d|%02d-%02d-%02d|%s|%d|%.2f\n", Supplies[i].itemID, Supplies[i].itemName, Supplies[i].manuftDate.day, Supplies[i].manuftDate.month, Supplies[i].manuftDate.year,
			Supplies[i].expiryDate.day, Supplies[i].expiryDate.month, Supplies[i].expiryDate.year, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
	}
	fclose(changDetails);

	viewInventory();
	printf(" | Successfully Edited Medical Supply      |\n");
	printf(" |=========================================|\n\n");
}

//below are to be used in changeStock()
int increase() { //using function call function to validate
	int checking = 0, increaseBy = 0;
	printf(" Inventory Increase By : "); //Get Qty(0-99999)
	scanf("%d", &increaseBy); rewind(stdin);
	checking = checkQty(increaseBy);
	if (checking != 1) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		increase();
	}
	system("color F0");
	return increaseBy;
}
int decrease() { //validate by using pass by reference
	int checking = 0, decreaseBy = 0;
	printf(" Inventory Decrease By : "); //Get Qty(0-99999)
	scanf("%d", &decreaseBy); rewind(stdin);
	checking = checkQty(decreaseBy);
	while (checking != 1) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		printf(" Inventory Decrease By : "); //Get Qty(0-99999)
		scanf("%d", &decreaseBy); rewind(stdin);
		checking = checkQty(decreaseBy);
	}
	system("color F0");
	return decreaseBy;
}

void changeStock() {
	viewInventory(); //Shows the user what is in the file first

	FILE *editInv;
	editInv = fopen("medicalSupplies.txt", "r");
	if (editInv == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0, increaseBy = 0, decreaseBy = 0;
	char inputItemID[100] = "", itemID[8] = "Y", select = 'O';
	printf("\n Which Medical Supply Stock To Change?\n");
	printf(" Enter Medical Supply ID: Y");
	scanf("%[^\n]", inputItemID); rewind(stdin);
	while (strlen(inputItemID) != 6) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		printf(" Enter Medical Supply ID  : Y");
		scanf("%[^\n]", &inputItemID); rewind(stdin);
	}
	strcat(itemID, inputItemID);
	system("color F0");

	while (fscanf(editInv, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		if (strcmp(Supplies[i].itemID, strupr(itemID)) == 0) {
			do {
				animation1(" |===========================|\n");
				animation1(" | Increase Inventory  : (I) |\n");
				animation1(" | Decrease Inventory  : (D) |\n");
				animation1(" | Exit from Here      : (E) |\n");
				animation1(" |===========================|\n");
				do {
					select = 'O';
					animation1(" Please Select > ");
					scanf("%c", &select); rewind(stdin);
					if (select == 'O') {
						system("color FC"); printf("\a");
						printf(" <INVALID INPUT> \n");
					}
				} while (select == 'O'); //validation for when user input something that isn't char
				system("color F0");
				select = toupper(select);
				switch (select) {
				case 'I':
					increaseBy = increase();
					Supplies[i].stock += increaseBy;
					break;
				case 'D':
					decreaseBy = decrease();
					Supplies[i].stock -= decreaseBy;
					break;
				case 'E':
					break;
				default:
					system("color FC"); printf("\a");
					printf(" <INVALID INPUT> \n");
					break;
				}
				system("color F0");
			} while (select != 'E');
		}
		++i; ++totalItem;
	}
	fclose(editInv);

	FILE *newInv;
	newInv = fopen("medicalSupplies.txt", "w");
	if (newInv == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	for (int i = 0; i < totalItem; i++) {
		fprintf(newInv, "%s|%s|%02d-%02d-%02d|%02d-%02d-%02d|%s|%d|%.2f\n", Supplies[i].itemID, Supplies[i].itemName, Supplies[i].manuftDate.day, Supplies[i].manuftDate.month, Supplies[i].manuftDate.year,
			Supplies[i].expiryDate.day, Supplies[i].expiryDate.month, Supplies[i].expiryDate.year, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
	}
	fclose(newInv);
}

void deleteSupplies() {
	viewInventory(); //Shows the user what is in the file first

	FILE *whichDelete;
	whichDelete = fopen("medicalSupplies.txt", "r");
	if (whichDelete == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, j = 0, totalItem = 0;
	char inputItemID[100] = "", itemID[8] = "Y";
	printf(" Which Medical Supply Details To Delete?\n");
	printf(" Enter Medical Supply ID: Y");
	scanf("%[^\n]", inputItemID); rewind(stdin);
	while (strlen(inputItemID) != 6) {
		system("color FC"); printf("\a");
		printf(" <INVALID INPUT> \n");
		printf(" Enter Medical Supply ID: Y");
		scanf("%[^\n]", &inputItemID); rewind(stdin);
	}
	strcat(itemID, inputItemID);
	system("color F0");

	while (fscanf(whichDelete, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		++i; ++totalItem;
	}

	int loopCondition = totalItem;
	for (int i = 0; j < loopCondition; i++) {
		if (strcmp(Supplies[i].itemID, strupr(itemID)) == 0) {
			//This is to remove the stucture(array) that is the inputted ID
			j = i + 1;
			Supplies[i] = Supplies[j];
			totalItem = totalItem - 1;
		}
		else {
			Supplies[i] = Supplies[j]; //When it isn't the ID that the user want to delete
		}
		j++;
	}

	fclose(whichDelete);

	FILE *afterDelete;
	afterDelete = fopen("medicalSupplies.txt", "w");
	if (afterDelete == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	for (int i = 0; i < totalItem; i++) {
		fprintf(afterDelete, "%s|%s|%02d-%02d-%02d|%02d-%02d-%02d|%s|%d|%.2f\n", Supplies[i].itemID, Supplies[i].itemName, Supplies[i].manuftDate.day, Supplies[i].manuftDate.month, Supplies[i].manuftDate.year,
			Supplies[i].expiryDate.day, Supplies[i].expiryDate.month, Supplies[i].expiryDate.year, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
	}

	fclose(afterDelete);

	viewInventory();
	printf(" | Successfully Added New Medical Supply   |\n");
	printf(" |=========================================|\n\n");
}

void sortInventory() {
	FILE *beforeSort;
	beforeSort = fopen("medicalSupplies.txt", "r");
	if (beforeSort == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0;
	while (fscanf(beforeSort, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{

		++i; ++totalItem;
	}

	int loopCondition = totalItem, j = 0;
	i = 0;
	for (i = 0; i < loopCondition - 1; i++) {
		for (j = i + 1; j < loopCondition; j++) {
			if (strcmp(Supplies[i].itemID, Supplies[j].itemID) > 0) {
				forSorting = Supplies[i];
				Supplies[i] = Supplies[j];
				Supplies[j] = forSorting;
			}
		}
	}

	FILE *afterSort;
	afterSort = fopen("medicalSupplies.txt", "w");
	if (afterSort == NULL) {
		printf(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	for (int i = 0; i < totalItem; i++) {
		fprintf(afterSort, "%s|%s|%02d-%02d-%02d|%02d-%02d-%02d|%s|%d|%.2f\n", Supplies[i].itemID, Supplies[i].itemName, Supplies[i].manuftDate.day, Supplies[i].manuftDate.month, Supplies[i].manuftDate.year,
			Supplies[i].expiryDate.day, Supplies[i].expiryDate.month, Supplies[i].expiryDate.year, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
	}
	fclose(afterSort);

	viewInventory();
}

void viewInventory() {
	FILE *showInv;
	showInv = fopen("medicalSupplies.txt", "r");
	if (showInv == NULL) {
		animation1(" <Unable to Open File> \n"); system("pause"); exit(-1);
	}

	int i = 0, totalItem = 0;
	animation2("\n\n |===========================================================================================================================================| \n");
	animation2(" |                                                        Medical Supplies Inventory                                                         | \n");
	animation2(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	animation2(" | Item ID |           Item Name           | Manufacture Date |   Expiry Date    |      Manufacturer/Country      | Stock | Price(per stock) | \n");
	animation2(" |=========|===============================|==================|==================|================================|=======|==================| \n");

	while (fscanf(showInv, "%[^|]|%[^|]|%d-%d-%d|%d-%d-%d|%[^|]|%d|%lf\n", Supplies[i].itemID, Supplies[i].itemName, &Supplies[i].manuftDate.day, &Supplies[i].manuftDate.month, &Supplies[i].manuftDate.year,
		&Supplies[i].expiryDate.day, &Supplies[i].expiryDate.month, &Supplies[i].expiryDate.year, Supplies[i].fromWhere, &Supplies[i].stock, &Supplies[i].price) != EOF)
	{
		printf(" | %-7s | %-30s|    %02d-%02d-%-4d    |    %02d-%02d-%-4d    | %-30s | %5d | %16.2f | \n", Supplies[i].itemID, Supplies[i].itemName,
			Supplies[i].manuftDate, Supplies[i].expiryDate, Supplies[i].fromWhere, Supplies[i].stock, Supplies[i].price);
		++i; ++totalItem;
	}
	animation2(" |=========|===============================|==================|==================|================================|=======|==================| \n");
	printf(" | Total Number of Medical Supplies: %-5d | \n", totalItem);
	printf(" |=========================================|\n");
	fclose(showInv);
}

void animation1(const char a[150]) //pass by parameter
{
	int n, m;
	for (n = 0; a[n] != NULL; ++n)
	{
		printf("%c", a[n]);
		for (m = 0; m < 400000; ++m)
		{
			
		}
	}
}
void animation2(const char b[150]) //pass by parameter
{
	int n, m;
	for (n = 0; b[n] != NULL; ++n)
	{
		printf("%c", b[n]);
		for (m = 0; m < 100000; ++m)
		{

		}
	}
}

void delay(int z) //pass by parameter
{
	int x, y;
	for (x = 0; x <= z; x++)
		for (y = 1; y <= z; y++)
		{

		}
}