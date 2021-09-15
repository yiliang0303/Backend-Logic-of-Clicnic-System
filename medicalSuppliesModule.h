#pragma once

void logo();
void mainMenu();
void medicalSuppliesMenu();
int selectOption();
//the sub-functions
void addNewSupplies();
void searchSupplies();
void editDetails();
void changeStock();
void deleteSupplies();
void sortInventory();
void viewInventory();
//to be used in sub-functions
int checkManuYear(int itemYear);
int checkExpiYear(int itemYear, int itemExYear);
int checkMonth(int itemMonth);
void checkDay(int itemMonth, int itemDay, int *correct);
int checkQty(int itemQty);
int checkPrice(double itemPrice);
int increase();
int decrease();
//to be used inside searchSupplies();
void searchByID();
void searchByName();
void searchByManuYear();
void searchByExpiYear();
void searchByMaker();
void searchByPrice();
//presentation(style)
void animation1(const char a[150]);
void animation2(const char b[150]);
void delay(int z);

typedef struct {
	int day, month, year;
} Date;

struct {
	char itemID[8], itemName[100];
	Date manuftDate, expiryDate;
	char fromWhere[100];
	int stock;
	double price;
} Supplies[1000], forSorting;
