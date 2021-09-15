#include <stdlib.h>
#include <stdio.h>
#include "patientInformationModule.h"
#include "patientVisit.h"
#include "patientAppointmentsModule.h"
#include "medicalSuppliesModule.h"
#pragma warning (disable:4996)

void main()
{
	int module;
	
	while (1)
	{
		int loop = 1;
		system("cls");
		mainSecurity();
		do
		{
			system("cls");
			system("color f0");
			module = selectModule();
			switch (module)
			{
			case 1:
				moduleFunction();
				break;
			case 2:
				system("cls"); visit();
				break;
			case 3:
				system("cls"); appointment();
				break;
			case 4:
				medicalSuppliesMenu();
				break;
			default:
				loop = 0;
				break;
			}
		} while (loop);
	}
}