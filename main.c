#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int userSize = 0; 
	double tax = 0; 
	double gross = 0; 
	char userInput; 
	
	printf("\tPayroll System\n\n");
	printf("Enter no. of users: "); 
	scanf("%d", &userSize); 
	payrecord payroll[userSize];
	
	readName(payroll, userSize); 
	
	readRecords(payroll, userSize); 
	
	gross = calcRecords(payroll, userSize, &tax);
	
	userInput = displayOptions(); 
	
	makeQuery(payroll, userSize, gross, tax, userInput); 

	return 0;
}
