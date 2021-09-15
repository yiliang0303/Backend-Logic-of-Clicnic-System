#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "patientInformationModule.h"
#include "medicalSuppliesModule.h"
#pragma warning (disable : 4996)

//back door
void addFirst()
{
	FILE * first;
	first = fopen("security.bin", "wb");

	printf("username :");
	scanf("%s", input.username);
	printf("pin :");
	scanf("%s", input.pin);
	printf("password:");
	scanf("%s", input.password);

	fwrite(&input, sizeof(struct PASSWORD), 1, first);
	fclose(first);
}

void mainSecurity()
{
	int security, loop;
	logo();
	do
	{
		system("color f0");
		security = selectSecurity();
		switch (security)
		{
		case 1: registration(); break;
		case 2: loop = loginPin(2); break;
		case 3: changePassword(); break;
		case 4: exit(-1); break;
		default: wrong();  printf("***Please enter 1,2, or 4***\a\n\n"); break;
		}
	} while (security != 2 || loop);
}

int selectSecurity()
{
	float security;
	printf("New Staff Registration : (1)\n");
	printf("Login                  : (2)\n");
	printf("Change Password        : (3)\n");
	printf("Exit program           : (4)\n");

	printf("\nPlease select an integer : ");
	while (scanf("%f", &security) != 1 || (int)security != security) //only allow integer input.
	{
		printf("Please select an integer : ");
		rewind(stdin);
	}
	rewind(stdin);

	return security;
}

void enterPin()
{
	do
	{
		printf("\n<6-digits>\n");
		do
		{
			printf("Enter PIN number : ");
			scanf("%[^\n]", input.pin);
			rewind(stdin);
		} while (numValidation(input.pin) || strlen(input.pin) != 6);

		do
		{
			printf("Confirm PIN      : ");
			scanf("%[^\n]", comfirm.pin);
			rewind(stdin);
		} while (numValidation(comfirm.pin) || strlen(comfirm.pin) != 6);
	} while (comparison(1, input.pin, comfirm.pin));
}

void enterPassword()
{
	do
	{
		printf("\n[You need to enter a strong password.\nStrong passwords contain at least 8 characters.\nDo not include common words or names,\nAnd combine uppercase letters, lowercase letters, numbers, and symbols.]\n");
		do
		{
			printf("Enter PASSWORD      : ");
			scanf("%[^\n]", input.password);
			rewind(stdin);
		} while (strlen(input.password) <= 7); //atleast 8character/symbol/numerical number and allow space

		printf("Confirm PASSWORD : "); //validation is not needed for comfirmation.
		scanf("%[^\n]", comfirm.password);
		rewind(stdin);
	} while (comparison(2, input.password, comfirm.password));
}

void registration()
{
	int a; //to control the if-else statement
	int exist = 0;
	char yesno;

	FILE * wptr;
	FILE * read;
	read = fopen("security.bin", "rb");
	if (read == NULL)
	{
		printf("***Error in opening file***\n");
	}
	else
	{
		do
		{
			printf("\nEnter username   : ");
			scanf("%[^\n]", newStaff.username);
			rewind(stdin);
		} while (usernameValidation(newStaff.username));

		//validation
		while (fread(&comfirm, sizeof(struct PASSWORD), 1, read) != 0)
		{
			if (strcmp(newStaff.username, comfirm.username) == 0)
				exist = 1; //username exist
		}
		fclose(read);
	}

	wptr = fopen("security.bin", "ab");
	if (exist == 0) //if username does not exist
	{
		do
		{
			printf("\n<6-digits>\n");
			do
			{
				printf("Enter PIN number : ");
				scanf("%[^\n]", newStaff.pin);
				rewind(stdin);
			} while (numValidation(newStaff.pin) || strlen(newStaff.pin) != 6);

			do
			{
				printf("Confirm PIN      : ");
				scanf("%[^\n]", comfirm.pin);
				rewind(stdin);
			} while (numValidation(comfirm.pin) || strlen(comfirm.pin) != 6);
		} while (comparison(1, newStaff.pin, comfirm.pin));

		do
		{
			printf("\n<You need to enter a strong password.\nStrong passwords contain at least 8 characters.\nDo not include common words or names,\nand combine uppercase letters, lowercase letters, numbers, and symbols.>\n");
			do
			{
				printf("Enter PASSWORD   : ");
				scanf("%[^\n]", newStaff.password);
				rewind(stdin);
			} while (strlen(newStaff.password) <= 7); //atleast 6character/symbol/numerical number and allow space

			printf("Confirm PASSWORD : "); //validation is not needed for comfirmation.
			scanf("%[^\n]", comfirm.password);
			rewind(stdin);
		} while (comparison(2, newStaff.password, comfirm.password));

		printf("\nApprove (y/Y=YES)? ");
		scanf("%c", &yesno);
		rewind(stdin);

		if (toupper(yesno) == 'Y')
		{
			printf("\nAPPROVE BY :");
			a = loginPin(1);

			if (a != 1) //correct OR found username; correct PIN will return 0, thus it still fullfill the statement.
			{
				if (a != 0) //wrong PIN
				{
					a = loginPassword(a - 99, 1); //(a-99): to change it back to the correct username array number.
					if (a == 0) //correct PASSWORD
					{
						printf("***REGISTRATION SUCCESS***\n\n");
						fwrite(&newStaff, sizeof(struct PASSWORD), 1, wptr);
					}
					else //wrong PASSWORD
					{
						wrong();
						printf("***REGISTRATION FAIL***\n\n");
					}
				}
				else //correct PIN
				{
					printf("***REGISTRATION SUCCESS***\n\n");
					fwrite(&newStaff, sizeof(struct PASSWORD), 1, wptr);
				}
			}
			else //not found username
				printf("***REGISTRATION FAIL***\n\n");
		}
		else
		{
			system("cls");
			printf("***Registration Denied***\n\n");
		}
	}
	else //username existed
	{
		wrong();
		printf("***Username Exist***\a\n\n");
	}
	fclose(wptr);
}

int loginPin(int type)
{
	int a = 0, found = 1; 
	FILE * rptr;
	rptr = fopen("security.bin", "rb");

	if (rptr == NULL)
		printf("***Error in opening file***\a\n");
	else
	{
		do
		{
			printf("\nUSERNAME   : ");
			scanf("%[^\n]", &input.username);
			rewind(stdin);
		} while (usernameValidation(input.username));

		while (fread(&staff[a], sizeof(struct PASSWORD), 1, rptr) != 0)
		{
			if (strcmp(staff[a].username, input.username) == 0)
			{
				found = 0; //username found
				for (int i = 0; i < 3; i++)
				{
					do
					{
						printf("PIN number (6-digits): ");
						scanf("%[^\n]", &input.pin);
						rewind(stdin);
					} while (strlen(input.pin) != 6 || numValidation(input.pin));

					if (strcmp(staff[a].pin, input.pin) == 0) //correct PIN
					{
						system("color 2f");
						_sleep(1000);
						system("cls");
						return found; 
					}
					else //wrong PIN; 
					{
						system("color 4f");
						printf("\a\n***WRONG PIN PLEASE TRY AGAIN***\n");
						if (i == 2)
						{
							if (type == 1) //for registration
							{
							//(a+99): TO AVOID RETURN 0 OR 1 BECAUSE THE CORRECT USERNAME ARRAY NUMBER MAY BE 1 OR 0.
								return a + 99; 
							}
							else //for login
								loginPassword(a,type); //pass the correct username array number and type.
						}
					}
				}
			}
			a++;
		}
	}
	fclose(rptr);

	//username not found 
	if (found == 1)
	{
		wrong();
		printf("***USERNAME NOT FOUND***\a\n\n");
	}
		return found;
}

int loginPassword(int a, int type)
{
	int loop, i = 0;

	do
	{
		loop = 0;

		//if wrong 5times
		if (i == 5)
		{
			if (type == 2)
			{
				printf("\nSYSTEM SHUT DOWN\a\n");
				system("pause");
				exit(-1);
			}
			else
				return 1;
		}


		printf("PASSWORD   : ");
		scanf("%[^\n]", &input.password);
		rewind(stdin);

		//wrong password
		if (strcmp(staff[a].password, input.password) != 0)
		{
			loop = 1;
			system("color 4f");
			if (i < 4)
				printf("\a\n***WRONG PASSWORD PLEASE TRY AGAIN***\n");
		}

		i++;
	} while (loop);

	//correct password
	system("color 2f");
	_sleep(1000);
	system("cls");
	return 0;
}

int selectChange()
{
	float change;
	printf("\nChange PIN             : (1)\n");
	printf("Change PASSWORD        : (2)\n");
	printf("Forget PIN or PASSWORD : (3)\n");
	printf("         Exit          : Other\n");

	printf("\nPlease select an integer : ");
	while (scanf("%f", &change) != 1 || (int)change != change) //only allow integer input.
	{
		printf("Please select an integer : ");
		rewind(stdin);
	}
	rewind(stdin);

	return change;
}

void changePassword()
{
	int y = 0, change, f, fail = 0, found = 0;
	FILE * rchange;
	FILE * wchange;
	rchange = fopen("security.bin", "rb");

	if (rchange == NULL)
		printf("***Error in opning file***\n");
	else
	{
		do
		{
			printf("\nEnter Username : ");
			scanf("%[^\n]", input.username);
			rewind(stdin);
		} while (usernameValidation(input.username));

		while (fread(&staff[y], sizeof(struct PASSWORD), 1, rchange) != 0)
		{
			if (strcmp(input.username, staff[y].username) == 0) //found staff to change password and pin.
			{
				found = 1;
				f = y;
				change = selectChange();
				switch (change)
				{
				case 1: //change pin
					do
					{
						printf("\nEnter OLD PIN : "); //enter old pin to change new pin
						scanf("%[^\n]", input.pin);
						rewind(stdin);
					} while (numValidation(input.pin) || strlen(input.pin) != 6);

					if (strcmp(staff[y].pin, input.pin) == 0) //old pin correct
					{
						printf("\n<NEW>");
						enterPin();
						strcpy(staff[y].pin, input.pin);
					}
					else //old pin wrong, use old password to change pin
					{
						printf("\n***WRONG PIN***\n");
						do
						{
							printf("Enter old PASSWORD : ");
							scanf("%[^\n]", input.password);
							rewind(stdin);
						} while (strlen(input.password) <= 5);

						if (strcmp(staff[y].password, input.password) == 0) //old password correct.
						{
							printf("\n<NEW>");
							enterPin();
							strcpy(staff[y].pin, input.pin);
						}
						else //wrong old pin and password
						{
							fail = 1;
							wrong();
							printf("***FAIL TO CHANGE PIN***\a\n\n");
						}
					}
					break;

				case 2: //change pssword
					do
					{
						printf("\nEnter OLD PIN : "); //use old pin to change password
						scanf("%[^\n]", input.pin);
						rewind(stdin);
					} while (numValidation(input.pin) || strlen(input.pin) != 6);

					if (strcmp(staff[y].pin, input.pin) == 0) //old pin correct
					{
						printf("\n<NEW>");
						enterPassword();
						strcpy(staff[y].password, input.password);
					}
					else //old pin wrong, use old password to change password
					{
						printf("\n***WRONG PIN***\n");
						do
						{
							printf("Enter old PASSWORD : ");
							scanf("%[^\n]", input.password);
							rewind(stdin);
						} while (strlen(input.password) <= 5);

						if (strcmp(staff[y].password, input.password) == 0) //old password correct
						{
							printf("\n<NEW>");
							enterPassword();
							strcpy(staff[y].password, input.password);
						}
						else //wrong old pin and password.
						{
							fail = 1;
							wrong();
							printf("***FAIL TO CHANGE PASSWORD***\a\n\n");
						}
					}
					break;

				case 3: // forget password and pin
					//finish reading the file
					y = y + 1;
					while (fread(&staff[y], sizeof(struct PASSWORD), 1, rchange) != 0)
					{
						y++;
					}

					printf("\nAPPROVE BY : ");
					do
					{
						printf("\nUsername : ");
						scanf("%[^\n]", input.username);
						rewind(stdin);
					} while (usernameValidation(input.username));

					do
					{
						printf("PIN <6-digits>: ");
						scanf("%[^\n]", input.pin);
						rewind(stdin);
					} while (numValidation(input.pin) || strlen(input.pin) != 6);

					do
					{
						printf("PASSWORD : ");
						scanf("%[^\n]", input.password);
						rewind(stdin);
					} while (strlen(input.password) <= 5);

					for (int k = 0; k < y; k++)
					{
						//approvement success when username, pin and password correct.
						if (strcmp(staff[k].username, input.username) == 0 && strcmp(staff[k].pin, input.pin) == 0 && strcmp(staff[k].password, input.password) == 0)
						{
							printf("\n<NEW PIN AND PASSWORD>");
							enterPin();
							enterPassword();
							strcpy(staff[f].pin, input.pin);
							strcpy(staff[f].password, input.password);
							break; //break the loop
						}
						else //approvement fail
						{
							if (k == y - 1)
							{
								fail = 1;
								wrong();
								printf("***APPROVEMENT FAIL***\a\n\n");
								break; //break the loop
							}
						}
					}
					break;
				default: fail = 1; system("cls");  break;
				}
			}
			y++;
		}
		fclose(rchange);

		if(found == 0) //username not found
		{
			wrong();
			printf("***Username not found***\a\n\n");
		}
		else
		{
			if (fail == 0)
			{
				wchange = fopen("security.bin", "wb");

				if (change != 3)
				{
					for (int k = 0; k < y; k++)
						fwrite(&staff[k], sizeof(struct PASSWORD), 1, wchange);
				}
				else
				{
					for (int k = 0; k < y - 1; k++)
						fwrite(&staff[k], sizeof(struct PASSWORD), 1, wchange);
				}
				fclose(wchange);

				system("cls");
				if (change == 1)
					printf("***Successful to change PIN***\n\n");
				else if (change == 2)
					printf("***Successful to change PASSWORD***\n\n");
				else if (change == 3)
					printf("***Successful to change PIN AND PASSWORD***\n\n");
			}
		}
	}
}

int selectModule()
{
	float module;

	animation1("Patient Information Module : (1)\n");
	animation1("Patient Visit Module\t   : (2)\n");
	animation1("Appointments Module\t   : (3)\n");
	animation1("Medical Supplies Module\t   : (4)\n");
	animation1("        Exit               : Others\n");

	printf("\nPlease select an integer : ");
	while (scanf("%f", &module) != 1 || (int)module != module) //only allow integer input.
	{
		printf("Please select an integer : ");
		rewind(stdin);
	}
	rewind(stdin);

	return module;
}

void moduleFunction()
{
	int function, loop;

	do
	{
		loop = 1;
		system("cls");
		function = selectFunction();
		switch (function)
		{
		case 1: recordInfo();   break;
		case 2: searchRecord(); break;
		case 3: editRecord();   break;
		case 4: displayAll();   break;
		default: loop = 0; break;
		}	
	} while (loop);
}

int selectFunction()
{
	float function;

	animation1("Record New Patient Information  : (1)\n");
	animation1("Search Patient Information      : (2)\n");
	animation1("Delete/Edit Patient Information : (3)\n");
	animation1("Show ALL Patient Information    : (4)\n");
	animation1("             Exit               : Others\n");

	printf("\nPlease select an integer : ");
	while (scanf("%f", &function) != 1 || (int)function != function)
	{
		printf("Please select an integer : ");
		rewind(stdin);
	}
	rewind(stdin);

	return function;
}

void recordInfo()
{
	//VARIABLE DECLARATION AND INITIALIZATION
	char yesno, allergies[50];
	int male = 0, female = 0, malaysian = 0, nonMalaysian = 0;
	FILE * avoid;
	FILE * aptr;

	//ALL DATA ARE STORED AS UPPERCASE.
	do
	{
		int exist = 0, x = 0;
		//OPEN FILE
		avoid = fopen("patientInformation.bin", "rb");
		if (avoid == NULL)
			printf("***FILE DOES NOT EXIST***\a\n");
		else
		{
			while (fread(&checking[x], sizeof(struct INFORMATION), 1, avoid) != 0)
			{
				x++;
			}
			fclose(avoid);
		}

		aptr = fopen("patientInformation.bin", "ab");
		char createID[8];
		printf("\n***TO EXIT KEY IN """"CANCLE"""" OR 'X' ON GENDER AND CITIZEN***\n");
		//NAME
		printf("\nPatient Name \t      : ");
		scanf("%[^\n]", patient[x].detail.name);
		rewind(stdin);
		if (strcmp(patient[x].detail.name, "CANCLE") == 0)
			break;
		strcpy(patient[x].detail.name, strupr(patient[x].detail.name));

		//IC NUMBER
		do
		{
			printf("IC No. \t\t      : ");
			scanf("%[^\n]", patient[x].detail.icNo);
			rewind(stdin);
			if (strcmp(patient[x].detail.icNo, "CANCLE") == 0)
				break;
		} while (strlen(patient[x].detail.icNo) != 12 || numValidation(patient[x].detail.icNo));
		if (strcmp(patient[x].detail.icNo, "CANCLE") == 0)
			break;

		//check existing
		for (int i = 0; i < x; i++)
		{
			if (strcmp(checking[i].detail.icNo, patient[x].detail.icNo) == 0)
			{
				exist = 1;
				break;
			}
		}

		if (exist == 0)
		{
			//CITIZEN
			do
			{
				printf("Citizen (Y=YES,N=NO)  : ");
				scanf("%c", &patient[x].detail.nationality);
				rewind(stdin);
				if (patient[x].detail.nationality == 'X')
					break;
			} while (toupper(patient[x].detail.nationality) != 'Y' && toupper(patient[x].detail.nationality) != 'N');
			if (patient[x].detail.nationality == 'X')
				break;
			patient[x].detail.nationality = toupper(patient[x].detail.nationality);

			//GENDER
			do
			{
				printf("Gender (M/F) \t      : ");
				scanf("%c", &patient[x].detail.gender);
				rewind(stdin);
				if (patient[x].detail.gender == 'X')
					break;
			} while (toupper(patient[x].detail.gender) != 'M' && toupper(patient[x].detail.gender) != 'F');
			if (patient[x].detail.gender == 'X')
				break;
			patient[x].detail.gender = toupper(patient[x].detail.gender);

			//ID
			switch (patient[x].detail.gender)
			{
			case 'M':
				createID[0] = 'M';
				break;

			case 'F':
				createID[0] = 'F';
				break;
			}
			for (int c = 6; c < 13; c++)
				createID[c - 5] = patient[x].detail.icNo[c];
			strcpy(patient[x].detail.ID, createID);
			printf("Patient ID            : %s\n", patient[x].detail.ID);

			//CONTACT NUMBER
			do
			{
				printf("Contact No. \t      : ");
				scanf("%[^\n]", patient[x].detail.contactNO);
				rewind(stdin);
				if (strcmp(patient[x].detail.contactNO, "CANCLE") == 0)
					break;
			} while (numValidation(patient[x].detail.contactNO));
			if (strcmp(patient[x].detail.contactNO, "CANCLE") == 0)
				break;

			//EMERGENCY CONTACT NUMBER
			do
			{
				printf("Emergency Contact No. : ");
				scanf("%[^\n]", patient[x].emergencyNo);
				rewind(stdin);
				if (strcmp(patient[x].emergencyNo, "CANCLE") == 0)
					break;
			} while (numValidation(patient[x].emergencyNo));
			if (strcmp(patient[x].emergencyNo, "CANCLE") == 0)
				break;

			//ADDRESS
			printf("Address \t      : ");
			scanf("%[^\n]", patient[x].detail.address);
			rewind(stdin);
			if (strcmp(patient[x].detail.address, "CANCLE") == 0)
				break;
			strcpy(patient[x].detail.address, strupr(patient[x].detail.address));

			//ALLERGIES
			int a = 0;
			strcpy(patient[x].allergies, "");
			do
			{
				printf("Allergies \t      : ");
				scanf("%[^\n]", allergies);
				rewind(stdin);
				if (strcmp(allergies, "CANCLE") == 0)
					break;
				strcpy(patient[x].allergies[a], strupr(allergies));
				printf("\nAdd Allergies (y/Y=YES)? ");
				scanf("%c", &yesno);
				rewind(stdin);
				a++;
			} while (toupper(yesno) == 'Y');
			if (strcmp(allergies, "CANCLE") == 0)
				break;

			//decide to calculate after allergy to avoid extra patient when cancle rigister after citizen and gender
			switch (patient[x].detail.gender)
			{
			case 'M':
				male = calCurrentGender(patient[x].detail.gender, &female);
				break;

			case 'F':
				male = calCurrentGender(patient[x].detail.gender, &female);
				break;
			}

			if (patient[x].detail.nationality == 'Y')
				calCurrentCitizen(patient[x].detail.nationality, &malaysian, &nonMalaysian);
			else
				calCurrentCitizen(patient[x].detail.nationality, &malaysian, &nonMalaysian);

			//DISPLAY NEW RECORD
			system("cls");
			printf("***Your registration had success***\a\n\n");
			displayInfo(x, a);

			//WRITE INTO FILE
			fwrite(&patient[x], sizeof(struct INFORMATION), 1, aptr);
			fclose(aptr);
		}
		else
		{
			wrong();
			printf("***Patient Existed***\a\n\n");
		}

		printf("Add Patient (y/Y=yes)? ");
		scanf("%c", &yesno);
		rewind(stdin);
	} while (tolower(yesno) == 'y');

	//COUNT THE TOTAL NUMBER OF TODAY'S PATIENT
	printf("\nTotal Patients: %d\n", male + female);
	printf("Male   : %d\t Citizen     : %d\n", male, malaysian);
	printf("Female : %d\t Non-Citizen : %d\n\n", female, nonMalaysian);
	system("pause");
}

int selectSearch(int exclude)
{
	float choice;
	int number = 0;

	//every patient have their own ID and IC so filter is not needed.
	if (exclude == 0) 
		printf("ID        : (%d)\n", ++number);
	if (exclude != 2)
		printf("Name      : (%d)\n", ++number);
	if (exclude == 0)
		printf("IC No.    : (%d)\n", ++number);
	if (exclude != 4)
		printf("Gender    : (%d)\n", ++number);
	if (exclude != 5)
		printf("Citizen   : (%d)\n", ++number);
	printf("Allergies : (%d)\n", ++number);
	printf("Exit      : Others\n");

	printf("\nPlease select an integer : ");
	while (scanf("%f", &choice) != 1 || (int)choice != choice)
	{
		printf("Please select an integer : ");
		rewind(stdin);
	}
	rewind(stdin);

	//adjust the choice to the correct switch case.
	if (choice != 0 && exclude != 0)
	{
		if (exclude == 2)
			choice += 1;
		else if (exclude == 4)
		{
			if (choice >= 2)
				choice += 1;
		}
		else if (exclude == 5)
		{
			if (choice == 3)
				choice += 1;
		}
	}

	return choice;
}

void searchRecord()  
{
	int choice, c;
	char yesno;

	//OPEN FILE TO CHECK
	FILE *rSptr;
	rSptr = fopen("patientInformation.bin", "rb");

	//CHECK FILE
	if (rSptr == NULL) 
		printf("***FILE DOES NOT EXIST***\a\n");
	else
	{
		//CLOSE THE FILE TO OPEN THE FILE IN DO-WHILE LOOP AGAIN.
		fclose(rSptr);
		do
		{
			system("cls");
			printf("[SEARCH FUNCTION]\n\n");
			//OPEN THE FILE IN DO-WHILE LOOP TO SEARCH ANOTHER INFORMATION AFTER SEARCH AN INFORMATION
			//BECAUSE CLOSE THE FILE AND REOPEN ONLY CAN READ THE FILE AGAIN.
			rSptr = fopen("patientInformation.bin", "rb");

			int s = 0, f = 0, count = 0, found = 0;
			choice = selectSearch(0);

			switch (choice)
			{
			case 1: //SEARCH ID
				do
				{
					printf("\nEnter Patient ID (M/F123456): ");
					scanf("%[^\n]", searchEdit.detail.ID);
					rewind(stdin);
					if (strcmp(searchEdit.detail.ID, "CANCLE") == 0)
						break;
				} while (IDvalidation(searchEdit.detail.ID) || strlen(searchEdit.detail.ID) != 7);

				if (strcmp(searchEdit.detail.ID, "CANCLE") == 0)
				{
					found = 2;
					break;
				}
				else
				{
					printf("\n");
					while (fread(&patient[s], sizeof(patient[s]), 1, rSptr) != 0)
					{
						if (strcmp(patient[s].detail.ID, strupr(searchEdit.detail.ID)) == 0)
						{
							c = calAllergies(s);
							displayInfo(s, c);
							found = 1; //FOUND PATIENT
						}
						s++;
					}
				}
				break;

			case 2: //SEARCH NAME
				printf("\nEnter Patient NAME : ");
				scanf("%[^\n]", searchEdit.detail.name);
				rewind(stdin);
				if (strcmp(searchEdit.detail.name, "CANCLE") == 0)
				{
					found = 2;
					break;
				}
				else
				{
					printf("\n");
					while (fread(&patient[s], sizeof(patient[s]), 1, rSptr) != 0)
					{
						if (strcmp(patient[s].detail.name, strupr(searchEdit.detail.name)) == 0)
						{
							patient[count] = patient[s]; //for filter looping purpose
							count++;
							c = calAllergies(s);
							displayInfo(s, c);
							found = 1;
						}
						s++;
					}
					if (found == 1)
						printf("%d patients called %s.\n", count, strupr(searchEdit.detail.name));
					else
						printf("Nobody called %s.\n", strupr(searchEdit.detail.name));
				}
				break;

			case 3: //SEARCH IC NO.
				do
				{
					printf("\nEnter Patient IC No. : ");
					scanf("%[^\n]", &searchEdit.detail.icNo);
					rewind(stdin);
					if (strcmp(searchEdit.detail.icNo, "CANCLE") == 0)
						break;
				} while (strlen(searchEdit.detail.icNo) != 12 || numValidation(searchEdit.detail.icNo));

				if (strcmp(searchEdit.detail.icNo, "CANCLE") == 0)
				{
					found = 2;
					break;
				}
				else
				{
					printf("\n");
					while (fread(&patient[s], sizeof(patient[s]), 1, rSptr) != 0)
					{
						if (strcmp(patient[s].detail.icNo, searchEdit.detail.icNo) == 0)
						{
							c = calAllergies(s);
							displayInfo(s, c);
							found = 1;
						}
						s++;
					}
					if (found != 1)
						printf("No Such Patient.\n");
				}
				break;

			case 4: //SEARCH GENDER
				do
				{
					printf("\nEnter Patient GENDER (M/F): ");
					scanf("%c", &searchEdit.detail.gender);
					rewind(stdin);
					if (searchEdit.detail.gender == 'X')
						break;
					searchEdit.detail.gender = toupper(searchEdit.detail.gender);
				} while (searchEdit.detail.gender != 'M' && searchEdit.detail.gender != 'F');
				if (searchEdit.detail.gender == 'X')
				{
					found = 2;
					break;
				}
				else
				{
					printf("\n");
					while (fread(&patient[s], sizeof(patient[s]), 1, rSptr) != 0)
					{
						if (patient[s].detail.gender == searchEdit.detail.gender)
						{
							patient[count] = patient[s];
							count++;
							c = calAllergies(s);
							displayInfo(s, c);
							found = 1;
						}
						s++;
					}
					if (found == 1)
					{
						if (searchEdit.detail.gender == 'M')
							printf("There are %d MALE patients.\n", count);
						else
							printf("There are %d FEMALE patients.\n", count);
					}
					else
					{
						if (searchEdit.detail.gender == 'M')
							printf("No MALE patient.\n");
						else
							printf("No FEMALE patient.\n");
					}
				}
				break;

			case 5: //SEARCH CITIZEN
				do
				{
					printf("Citizen (Y=YES,N=NO)? ");
					scanf("%c", &searchEdit.detail.nationality);
					rewind(stdin);
					if (searchEdit.detail.nationality == 'X')
						break;
					searchEdit.detail.nationality = toupper(searchEdit.detail.nationality);
				} while (searchEdit.detail.nationality != 'Y' && searchEdit.detail.nationality != 'N');

				if (searchEdit.detail.nationality == 'X')
				{
					found = 2;
					break;
				}
				else
				{
					printf("\n");
					while (fread(&patient[s], sizeof(patient[s]), 1, rSptr) != 0)
					{
						if (patient[s].detail.nationality == searchEdit.detail.nationality)
						{
							patient[count] = patient[s];
							count++;
							c = calAllergies(s);
							displayInfo(s, c);
							found = 1;
						}
						s++;
					}
					if (found == 1)
					{
						if (searchEdit.detail.nationality == 'Y')
							printf("There are %d MALAYSIAN.\n", count);
						else
							printf("There are %d NON-MALAYSIAN.\n", count);
					}
					else
					{
						if (searchEdit.detail.nationality == 'Y')
							printf("No MALAYSIAN.\n");
						else
							printf("No NON-MALAYSIAN.\n");
					}
				}
				break;

			case 6: //SEARCH ALLERGIES
				printf("\nEnter patient Allergies : ");
				scanf("%[^\n]", searchEdit.allergies);
				rewind(stdin);
				if (strcmp(searchEdit.allergies, "CANCLE") == 0)
				{
					found = 2;
					break;
				}
				else
				{
					printf("\n");
					while (fread(&patient[s], sizeof(patient[s]), 1, rSptr) != 0)
					{
						//compare the allergies 50times
						for (int x = 0; x < 50; x++)
						{
							if (strcmp(patient[s].allergies[x], strupr(searchEdit.allergies)) == 0)
							{
								patient[count] = patient[s];
								count++;
								c = calAllergies(s);
								displayInfo(s, c);
								found = 1;
							}
						}
						s++;
					}
					if (found == 1)
						printf("There are %d patients have %s.\n", count, searchEdit.allergies);
					else
						printf("No Patient have %s.\n", searchEdit.allergies);
				}
				break;
			default: found = -1; break;
			}

			//input 1,2,3,4,5,6
			if (found == 1 || found == 0)
			{
				if (found == 0) //NOT FOUND ANY PATIENT.
					printf("***Please make registration at Module(1) -> Function(1)***\a\n\n");
				else //FOUND PATIENT OR CANCLE
				{
					//double filter
					if (choice == 2 || choice >= 4 && choice <= 6)
					{
						printf("\nFilter this list (y/Y=yes)? ");
						scanf("%c", &yesno);
						rewind(stdin);

						if (tolower(yesno) == 'y')
							found = searchFilter(choice, count);
						else
							found = 0;
					}
					else
						found = 0;
				}
				if (found == 0)
				{
					printf("Continue to search (y/Y=yes)? ");
					scanf("%c", &yesno);
					rewind(stdin);
				}
			}
			else if(found == 2) //make CANCLE
				yesno = 'y';
			else //straight exit search module
				yesno = 'n';

			//CLOSE THE FILE IN DO-WHILE LOOP SO THAT CAN OPEN THE FILE TO
			//CONTINUE TO READ THE FILE AGAIN FROM BEGINNING TO SEARCH OTHER INFORMATION.
			fclose(rSptr);
		} while (tolower(yesno) == 'y');
	}
}

int searchFilter(int exclude, int f)
{
	int found = 0, choice, x, count = 0, c;
	choice = selectSearch(exclude);

	switch (choice)
	{
	case 1: //filter name
		printf("\nEnter Patient Name : ");
		scanf("%[^\n]", searchEdit.detail.name);
		rewind(stdin);
		system("cls");

		for (x = 0; x < f; x++)
		{
			if (strcmp(patient[x].detail.name, strupr(searchEdit.detail.name)) == 0)
			{
				count++;
				c = calAllergies(x);
				displayInfo(x, c);
				found = 1; //FOUND PATIENT
			}
		}
		if(found == 1)
			printf("There are %d patients called %s on this list.\n", count, searchEdit.detail.name);
		break;

	case 2: //filter gender
		do
		{
			printf("\nEnter Patient GENDER (M/F): ");
			scanf("%c", &searchEdit.detail.gender);
			rewind(stdin);
			searchEdit.detail.gender = toupper(searchEdit.detail.gender);
		} while (searchEdit.detail.gender != 'M' && searchEdit.detail.gender != 'F');
		system("cls");

		for (x = 0; x < f; x++)
		{
			if (patient[x].detail.gender == searchEdit.detail.gender)
			{
				count++;
				c = calAllergies(x);
				displayInfo(x, c);
				found = 1;
			}
		}
		if (found == 1)
		{
			if (searchEdit.detail.gender == 'M')
				printf("There are %d MALE patients on this list.\n", count);
			else
				printf("There are %d FEMALE patients on this list.\n", count);
		}
		break;

	case 3: //filter citizen
		do
		{
			printf("Citizen (Y=YES,N=NO)? ");
			scanf("%c", &searchEdit.detail.nationality);
			rewind(stdin);
			searchEdit.detail.nationality = toupper(searchEdit.detail.nationality);
		} while (searchEdit.detail.nationality != 'Y' && searchEdit.detail.nationality != 'N');
		system("cls");

		for (x = 0; x < f; x++)
		{
			if (patient[x].detail.nationality == searchEdit.detail.nationality)
			{
				count++;
				c = calAllergies(x);
				displayInfo(x, c);
				found = 1;
			}
		}
		if (found == 1)
		{
			if (searchEdit.detail.nationality == 'Y')
				printf("There are %d MALAYSIAN on this list.\n", count);
			else
				printf("There are %d NON-MALAYSIAN on this list.\n", count);
		}
		break;

	case 4: //filter allergies
		printf("\nEnter patient Allergies : ");
		scanf("%[^\n]", searchEdit.allergies);
		rewind(stdin);
		system("cls");

		//loop for previous search list
		for (x = 0; x < f; x++)
		{
			//loop for compare allergies
			for (int a = 0; a < 50; a++)
			{
				if (strcmp(patient[x].allergies[a], strupr(searchEdit.allergies)) == 0)
				{
					count++;
					c = calAllergies(x);
					displayInfo(x, c);
					found = 1;
				}
			}
		}
		if (found == 1)
			printf("There are %d patients have %s on this list.\n", count, searchEdit.allergies);
		break;
	default: return 1; break;
	}
	if (found != 1)
		printf("\n\t***No such Patient on this list***\a\n***Please make registration at Module(1) -> Function(1)***\n");
	return 0;
}

int selectEdit()
{
	float selection;
	printf("DELETE patient             : (999)\n");
	printf("Edit Name                  : (1)\n");
	printf("Edit IC No                 : (2)\n");
	printf("Edit Gender                : (3)\n");
	printf("Edit Nationality           : (4)\n");
	printf("Edit Contact No.           : (5)\n");
	printf("Edit Emergency Contact No. : (6)\n");
	printf("Edit Address               : (7)\n");
	printf("Edit/Add Allergies         : (8)\n");
	printf("EXIT                       : Others\n");

	printf("\nPlease select an integer : ");
	while (scanf("%f", &selection) != 1 || (int)selection != selection)
	{
		printf("Please select an integer : ");
		rewind(stdin);
	}
	rewind(stdin);

	return selection;
}

void editRecord()
{
	char yesno;
	int selection, choice, remember, c, loop, ed;
	FILE * rEptr;
	FILE * wEptr;

	//OPEN THE FILE TO CHECK THE EXISTANCE OF FILE.
	rEptr = fopen("patientInformation.bin", "rb");
	
	if (rEptr == NULL)
		printf("***FILE DOES NOT EXIST***\a\n");
	else
	{
		//CLOSE FILE TO OPEN THE FILE IN DO-WHILE LOOP.
		fclose(rEptr);
		do
		{
			int e = 0, found = 0, countDelete = 0, editBefore = 0;
			system("cls");
			printf("[EDIT/DELETE FUNCTION]\n");

			//ID IS REQUIRE TO EDIT THE PATIENT.
			do
			{
				printf("\nEnter Patient ID : ");
				scanf("%[^\n]", searchEdit.detail.ID);
				rewind(stdin);
				if (strcmp(searchEdit.detail.ID, "CANCLE") == 0)
					break;
			} while (IDvalidation(searchEdit.detail.ID) || strlen(searchEdit.detail.ID) != 7);
			if (strcmp(searchEdit.detail.ID, "CANCLE") == 0)
				break;
			else
			{
				//OPEN THE FILE IN DO-WHILE LOOP TO EDIT ANOTHER PATIENT.
				rEptr = fopen("patientInformation.bin", "rb");
			}

			//READ THE FILE
			while (fread(&patient[e], sizeof(struct INFORMATION), 1, rEptr) != 0)
			{
				if (strcmp(patient[e].detail.ID, strupr(searchEdit.detail.ID)) == 0)
				{
					printf("\n\t ***Patient Found***\a\n");
					found = 1; //FOUND THE PATIENT
					c = calAllergies(e);
					remember = e;
					printf("\n\t  ***OLD RECORD***\n");
					displayInfo(remember, c);
					do
					{
						selection = selectEdit();
						if (selection >= 1 && selection <= 8)
							editBefore = 1;

						switch (selection)
						{
						case 999:
							editBefore = 2; found = 2; countDelete++;
							//replace array[6] to array[5] and continue to read to get all patient for rewrite. 
							while (fread(&patient[e], sizeof(struct INFORMATION), 1, rEptr) != 0)
							{
								e++;
							}
							printf("***Success to DELETE patient %s***\a\n", searchEdit.detail.ID);

							do
							{
								int control = 0; //print not found patient.
								printf("\nDELETE another patient (y/Y=YES)? ");
								scanf("%c", &yesno);
								rewind(stdin);

								if (tolower(yesno) == 'y')
								{
									loop = 1;
									do
									{
										printf("\nEnter Patient ID : ");
										scanf("%[^\n]", searchEdit.detail.ID);
										rewind(stdin);
										if (strcmp(searchEdit.detail.ID, "CANCLE") == 0)
											break;
									} while (IDvalidation(searchEdit.detail.ID) || strlen(searchEdit.detail.ID) != 7);
									if (strcmp(searchEdit.detail.ID, "CANCLE") == 0)
										break;

									for (int f = 0; f < e; f++)
									{
										if (strcmp(patient[f].detail.ID, strupr(searchEdit.detail.ID)) == 0)
										{
											control = 1;
											c = calAllergies(f);
											printf("\n\t  ***OLD RECORD***\n");
											displayInfo(f, c);
											printf("Enter (y/Y) to delete : ");
											scanf("%c", &yesno);
											rewind(stdin);
				
											if (tolower(yesno) == 'y')
											{
												countDelete++;
												// e-f to get how many times the array need to move up.
												for (int i = 0; i < e - f; i++)
													patient[f + i] = patient[f + i + 1]; //eg. copy array[3] to array[2].
												printf("\n***Success to DELETE patient %s***\a\n", searchEdit.detail.ID);
											}
											break;
										}
									}
									if(control == 0)
										printf("\n***Please make registration at Module(1) -> Funtion(1)***\a\n");
								}
								else
									loop = 0;
							} while (loop);
							break;

						case 1: //EDIT NAME
							editBefore = 1;
							printf("Enter the name : ");
							scanf("%[^\n]", searchEdit.detail.name);
							rewind(stdin);
							strcpy(patient[e].detail.name, strupr(searchEdit.detail.name));
							printf("\n");
							break;

						case 2: //EDIT IC NO.
							editBefore = 1;
							do
							{
								printf("Enter IC No. : ");
								scanf("%[^\n]", searchEdit.detail.icNo);
								rewind(stdin);
							} while (strlen(searchEdit.detail.icNo) != 12 || numValidation(searchEdit.detail.icNo));
							strcpy(patient[e].detail.icNo, searchEdit.detail.icNo);
							printf("\n");
							break;

						case 3: //EDIT GENDER
							editBefore = 1;
							//GET THE GENDER AND STRAIGHT CHANGE THE PATIENT GENDER, BCS THERE IS ONLY 2 OPTIONS. 
							if (patient[e].detail.gender == 'M')
							{
								patient[e].detail.gender = 'F';
								printf("\n***Success to change from Male to Female***\n\n");
							}
							else
							{
								patient[e].detail.gender = 'M';
								printf("\n***Success to change from Female to Male***\n\n");
							}
							break;

						case 4: //EDIT NATIONALITY
							editBefore = 1;
							//GET THE NATIONALITY AND STRAIGHT CHANGE IT.
							if (patient[e].detail.nationality == 'Y')
							{
								patient[e].detail.nationality = 'N';
								printf("\n***Success to change from Citizen to Non-citizen***\n\n");
							}
							else
							{
								patient[e].detail.nationality = 'Y';
								printf("\n***Success to change from Non-citizen to Citizen***\n\n");
							}
							break;

						case 5: //EDIT CONTACT NO.
							editBefore = 1;
							do
							{
								printf("Enter Contact No. : ");
								scanf("%[^\n]", searchEdit.detail.contactNO);
								rewind(stdin);
							} while (numValidation(searchEdit.detail.contactNO));
							strcpy(patient[e].detail.contactNO, searchEdit.detail.contactNO);
							printf("\n");
							break;

						case 6: //EDIT EMERGENCY CONTACT NO.
							editBefore = 1;
							do
							{
								printf("Enter EMERGENCY CONTACT No. : ");
								scanf("%[^\n]", searchEdit.emergencyNo);
								rewind(stdin);
							} while (numValidation(searchEdit.emergencyNo));
							strcpy(patient[e].emergencyNo, searchEdit.emergencyNo);
							printf("\n");
							break;

						case 7: //EDIT ADDRESS
							editBefore = 1;
							printf("Enter Address : ");
							scanf("%[^\n]", searchEdit.detail.address);
							rewind(stdin);
							strcpy(patient[e].detail.address, strupr(searchEdit.detail.address));
							printf("\n");
							break;

						case 8: //EDIT, ADD OR DELETE ALLERGIES
							editBefore = 1;
							do
							{
								printf("\nEDIT   : (1)\n");
								printf("ADD    : (2)\n");
								printf("DELETE : (3)\n\n");

								do
								{
									printf("Enter 1/2/3 : ");
									scanf("%d", &choice);
									rewind(stdin);
								} while (choice != 1 && choice != 2 && choice != 3);

								if (choice == 1) //EDIT
								{
									do
									{
										printf("Allergies : ");
										for (int k = 0; k < c; k++)
											printf("%d. %s\n\t    ", k + 1, patient[e].allergies[k]);

										do
										{
											printf("\nEnter an integer : ");
											scanf("%d", &ed);
											rewind(stdin);
										} while (ed <= 0 || ed > c);
										ed = ed - 1; //(ed-1) to follow the array. Example, no.2 is array[1];

										printf("\nRename Allergies : ");
										scanf("%[^\n]", searchEdit.allergies[ed]);
										rewind(stdin);
										strcpy(patient[e].allergies[ed], strupr(searchEdit.allergies[ed]));

										printf("\nEdit another Allergy (y/Y=YES)? ");
										scanf("%c", &yesno);
										rewind(stdin);
									} while (toupper(yesno) == 'Y');
									printf("Continue to Add or DELETE Allergies (y/Y=YES)? ");
								}
								else if (choice == 2) //ADD
								{
									do
									{
										printf("\nADD Allergies \t    : ");
										scanf("%[^\n]", searchEdit.allergies[c]);
										rewind(stdin);
										strcpy(patient[e].allergies[c], strupr(searchEdit.allergies[c]));

										printf("\nAdd another allergies (y/Y=YES)? ");
										scanf("%c", &yesno);
										rewind(stdin);
										c++; //the number of allergies increased after add.
									} while (toupper(yesno) == 'Y');
									printf("Continue to EDIT or DELETE Allergies (y/Y=YES)? ");
								}
								else //DELETE
								{
									do
									{
										if (c != 0)
										{
											printf("Allergies : ");
											for (int k = 0; k < c; k++)
												printf("%d. %s\n\t    ", k + 1, patient[e].allergies[k]);

											do
											{
												printf("\nEnter an integer : ");
												scanf("%d", &ed);
												rewind(stdin);
											} while (ed <= 0 || ed > c);

											//same concept as delete patient. +1 bcs the ed is not follow the number of array
											for (int j = 0; j < c - ed + 1; j++)
												strcpy(patient[e].allergies[ed - 1 + j], patient[e].allergies[ed + j]);

											printf("\nSuccess to DELETE Allergy (%d).", ed);
											printf("\nDELETED another allergies (y/y=YES)? ");
											scanf("%c", &yesno);
											rewind(stdin);
											c--; //number of allergies decreased after delete.
										}
										else
										{
											printf("\n***No Allergies***\n\n");
											yesno = 'n';
										}
									} while (toupper(yesno) == 'Y');
									printf("Continue to EDIT or ADD Allergies (y/Y=YES)? ");
								}

								scanf("%c", &yesno);
								rewind(stdin);
							} while (toupper(yesno) == 'Y');
							break;
						default: found = -1; break;
						}

						//ASK FOR STILL NEED TO EDIT THE SAME PATIENT OR NOT. 
						if (found != 2 && found != -1)
						{
							printf("Continue Edit this Patient(y/Y=yes)? ");
							scanf("%c", &yesno);
							rewind(stdin);
							printf("\n");
						}
						else //(found == 2 or found == -1) 
							yesno = 'n'; //bcs the patient is deleted or exit this function
					} while (toupper(yesno) == 'Y');
				}
				e++;
			}
			//CLOSE THE FILE SO THAT CAN EDIT ANOTHER PATIENT.
			fclose(rEptr);

			if (found == -1 && editBefore == 0) //break this loop to exit.
				break;
			else
			{
				if (editBefore == 1) //EDIT PATIENT
				{
					//RE-WRITE THE FILE.
					wEptr = fopen("patientInformation.bin", "wb");
					for (int w = 0; w < e; w++)
						fwrite(&patient[w], sizeof(struct INFORMATION), 1, wEptr);
					fclose(wEptr);

					printf("\t ***NEW RECORD***\n");
					displayInfo(remember, c);
				}
				else if (editBefore == 2) //DELETE PATIENT
				{
					//RE-WRITE THE FILE.
					wEptr = fopen("patientInformation.bin", "wb");
					//e-countDelte bcs numbers of the array is deleted.
					for (int w = 0; w < e - countDelete; w++)
						fwrite(&patient[w], sizeof(struct INFORMATION), 1, wEptr);
					fclose(wEptr);
				}
				else //NOT FOUND PATIENT
					printf("\n***Please make registration at Module(1) -> Funtion(1)***\a\n");

				printf("Continue to edit other patient (y/Y=yes)? ");
				scanf("%c", &yesno);
				rewind(stdin);
			}
		} while (toupper(yesno) == 'Y');
	}
}

void displayAll()
{
	system("cls");
	int d = 0, c;
	int male, female, malaysian, nonMalaysian;
	
	FILE * rDptr;
	rDptr = fopen("patientInformation.bin", "rb");

	if (rDptr == NULL)
		printf("***FILE DOES NOT EXIST***\a\n");
	else
	{
		while (fread(&patient[d], sizeof(struct INFORMATION), 1, rDptr) != 0)
		{
			c = calAllergies(d);
			displayInfo(d, c);
			d++;
		}
		printf("TOTAL Patient : %d\n", d);
		calTotalGenderCitizen(&male, &female, &malaysian, &nonMalaysian);
		printf("MALE   : %d\t CITIZEN     : %d\n", male, malaysian);
		printf("FEMALE : %d\t NON-CITIZEN : %d\n\n", female, nonMalaysian);
	}
	fclose(rDptr);
	system("pause");
}

int calAllergies(int a)
{
	int c = 0;
	for (c = 0; c < 50; c++)
	{
		if (patient[a].allergies[c][0] == '\0')
			break;
	}

	return c;
}

void displayInfo(int d, int c)
{
	printf("ID \t\t      : %s\n", patient[d].detail.ID);
	printf("NAME \t\t      : %s\n", patient[d].detail.name);
	printf("IC No. \t\t      : %s\n", patient[d].detail.icNo);
	if (patient[d].detail.nationality == 'Y')
		printf("Citezen \t      : YES\n");
	else
		printf("Citizen \t      : NO\n");
	if (patient[d].detail.gender == 'M')
		printf("Gender \t\t      : MALE\n");
	else
		printf("Gender \t\t      : FEMALE\n");
	printf("Contact No. \t      : %s\n", patient[d].detail.contactNO);
	printf("Emergency Contact No. : %s\n", patient[d].emergencyNo);
	printf("Address \t      : %s\n", patient[d].detail.address);
	printf("Allergies \t      : ");
	for (int k = 0; k < c; k++)
		printf("%d. %s\n\t\t        ", k+1, patient[d].allergies[k]);
	printf("\n");
}

void calTotalGenderCitizen(int *boy, int *girl, int *citizen, int *nonCitizen)
{
	int c = 0;	
	int male = 0, female = 0, malaysian = 0, nonMalaysian = 0;

	FILE * rCptr;
	rCptr = fopen("patientInformation.bin", "rb");

	if (rCptr == NULL)
		printf("***FILE DOES NOT EXIST***\a\n");
	else
	{
		while (fread(&patient[c], sizeof(struct INFORMATION), 1, rCptr) != 0)
		{
			if (patient[c].detail.gender == 'M')
				male++;
			else
				female++;

			if (patient[c].detail.nationality == 'Y')
				malaysian++;
			else
				nonMalaysian++;
			c++;
		}
	}
	*boy = male; *girl = female; *citizen = malaysian; *nonCitizen = nonMalaysian;
}

int calCurrentGender(char a, int *girl)
{
	static int male = 0, female = 0;
	if (a == 'M')
		male++;
	else
		female++;

	*girl = female;

	return male;
}

void calCurrentCitizen(char b, int *citizen, int *nonCitizen)
{
	static int malaysian = 0, nonMalaysian = 0;

	if (b == 'Y')
		malaysian++;
	else 
		nonMalaysian++;

	*citizen = malaysian;
	*nonCitizen = nonMalaysian;
}

int numValidation(char digits[])
{
	int valid = 0;
	
	for (int k = 0; k < strlen(digits); k++)
	{
		if (isdigit(digits[k]) == 0)
		{
			valid = 1;
			printf("***Please Enter Digits***\n");
			break;
		}
	}
	return valid;
}

int IDvalidation(char id[])
{
	if (toupper(id[0]) == 'M' || toupper(id[0]) == 'F')
	{
		for (int k = 1; k < strlen(id); k++)
		{
			if (isdigit(id[k]) == 0)
			{
				printf("\n***Invalid ID***");
				return 1;
			}
		}
		return 0;
	}
	else
	{
		printf("\n***Invalid ID***");
		return 1;
	}
}

int usernameValidation(char user[])
{
	for (int k = 0; k < strlen(user); k++)
	{
		if (user[k] == ' ')
		{
			printf("\n***Invalid Username***\a");
			return 1;
		}
	}
	return 0;
}

void wrong()
{
	system("color 4f");
	_sleep(1000);
	system("cls");
}

int comparison(int type, char x[], char y[])
{
	
	if (strcmp(x, y) == 0)
		return 0;
	else
	{
		if(type == 1)
			printf("\n***Provided PINs don't match***\a");
		else
			printf("\n***These passwords don't match***\n");
		return 1;
	}
}

//void main()
//{
//	int function, module;
//	char yesno;
//
//	mainSecurity();
//	system("color f0");
//
//	do
//	{
//		system("cls");
//		module = selectModule();
//		switch (module)
//		{
//		case 1: 			
//			moduleFunction(); yesno = 'n';
//			break;
//		case 2: break;
//		case 3: break;
//		case 4: break;
//		case 5: break;
//		default: 
//			printf("Exit this program (y/Y=yes)? ");
//			scanf("%c", &yesno);
//			rewind(stdin);
//			printf("\n"); 
//			break;
//		}
//	} while (tolower(yesno) != 'y');
//}