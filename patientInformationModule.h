#pragma once

//function declaration
//for SECURITY
void registration();
int loginPin(int type);
int loginPassword(int a, int type);
void changePassword();
void enterPin();
void enterPassword();
void wrong();
int comparison(int type, char x[], char y[]);

//for void main()
void mainSecurity();
void moduleFunction();

//selection
int selectSecurity();
int selectChange();
int selectFunction();
int selectSearch(int exclude);
int selectEdit();
int selectModule();

//module function
void recordInfo();
void searchRecord();
int searchFilter(int exclude, int f);
void editRecord();
void displayAll();

//output information
void displayInfo(int d, int c);

//calculation
int calCurrentGender(char a, int *girl);
void calCurrentCitizen(char b, int *citizen, int *nonCitizen);
void calTotalGenderCitizen(int *boy, int *girl, int *citizen, int *nonCitizen);
int calAllergies(int a);

//validation
int numValidation(char digits[]);
int IDvalidation(char id[]);
int usernameValidation(char user[]);

//structure
struct BASIC //can use it on patient or staff information module
{
	char name[50];
	char nationality;
	char icNo[13];
	char gender;
	char ID[8];
	char contactNO[12];
	char address[100];
}detail;

struct INFORMATION
{
	struct BASIC detail;
	char emergencyNo[12];
	char allergies[10][50];
}patient[1000], searchEdit, checking[1000];

struct PASSWORD
{
	char username[50];
	char pin[50], password[100];
}staff[50], input, comfirm, newStaff;
