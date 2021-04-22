#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"

void readName(payrecord payroll[], int i){
	int j; 
	
	printf("\nEnter User Information\n");
	for(j = 0; j < i; j++){
		printf("\nEnter last name: "); 
		scanf("%s",payroll[j].name.last); 
		
		printf("Enter first name: "); 
		scanf("%s",payroll[j].name.first); 
		
		printf("Enter middle name: "); 
		scanf("%s",payroll[j].name.middle); 
	}
}

void printName(payrecord payroll[], int i){
	int j; 

	for(j = 0; j < i; j++){
		printf("\nEmployee Name: ");
		printf("%s, %s %s.", payroll[j].name.last, 
							 payroll[j].name.first, 
							 payroll[j].name.middle);
	}
}

void printSummary(double gross, double tax){
	printf("\n==Total Gross and Total Tax Withheld==");
	printf("\nTotal gross pay: %.2lf\nTotal tax withheld: %.2lf\n", gross, tax); 
}

void readRecords(payrecord payroll[], int n){
	int j; 
	
	printf("\n\nInput Employee Information:\n");
	
	for(j = 0; j < n; j++){
		
		printf("\nEnter employee ID: "); 
		scanf("%d", &payroll[j].id); 
		
		printf("Enter work hours(weekly): "); 
		scanf("%f", &payroll[j].hours); 
		
		printf("Enter salary rate: "); 
		scanf("%f", &payroll[j].rate);
	}
}

void printRecords(payrecord payroll[], int n){
	int i; 
	
	printf("\n===Record Summary===");
	for(i = 0; i < n; i++){
		printf("\nEmployee ID: %d\n", payroll[i].id);
		printf("Name: %s, %s %s\n", payroll[i].name.last,
								    payroll[i].name.first, 
								    payroll[i].name.middle); 
								    
		printf("Worked Hours: %.2lf\n", payroll[i].hours);
		
		printf("Pay rate: %.2lf\n", payroll[i].rate);
		
		printf("Regular Pay: %.2lf\n", payroll[i].regular);
		
		printf("Overtime Pay: %.2lf\n", payroll[i].overtime);
		
		printf("Gross income: %.2lf\n", payroll[i].gross);
		
		printf("Net pay: %.2lf\n", payroll[i].net);							  
	}
}

double calcRecords(payrecord payroll[], int n, double *taxptr){
	int j; 
	float overtime_rate = 1.50, overtime_pay, overtimeHours; 
	float tax_deduction; 
	double total_tax = 0, total_gross = 0; 
	
	for(j = 0; j < n; j++){
		
		// Tax withheld 
		if(payroll[j].rate < 500){
			payroll[j].tax_withheld = 0.15; 
		}
		else if (payroll[j].rate > 500 && payroll[j].rate > 1000){
			payroll[j].tax_withheld = 0.28; 
		}
		else {
			payroll[j].tax_withheld = 0.33;
		}	
		
		// Regular and overtime pay computation ( 150% )  
		if(payroll[j].hours <= 40){
			
			// Regular pay 
			payroll[j].regular = payroll[j].hours * payroll[j].rate; 	
			payroll[j].overtime = 0; 
			
			// Total Gross
			payroll[j].gross = 4 * 12 * payroll[j].regular; 
			
			// Net Pay (with tax withheld) 
			tax_deduction = payroll[j].tax_withheld * payroll[j].gross;
			payroll[j].net = payroll[j].gross - tax_deduction; 
		}
		else if (payroll[j].hours > 40){
			
			// Overtime and regular pay 
			overtimeHours = 40 - payroll[j].hours; 
			overtime_pay = overtimeHours * payroll[j].rate * overtime_rate;  
			payroll[j].overtime = ((payroll[j].hours - overtimeHours) * payroll[j].rate) + overtime_pay; 
			payroll[j].regular = (payroll[j].hours - overtimeHours) * payroll[j].rate;  
			
			// Total Gross
			payroll[j].gross = 4 * 12 * payroll[j].overtime; 
			
			// Net Pay (with tax withheld)  
			tax_deduction = payroll[j].tax_withheld * payroll[j].gross;
			payroll[j].net = payroll[j].gross - tax_deduction; 
		}
		total_gross += payroll[j].gross; 		
		total_tax += payroll[j].tax_withheld;
	}
	*taxptr = total_tax; 
	
	return total_gross; 
} 

// Function Helpers
char displayOptions(){
	
	char userInput = 'a'; 
	
	printf("\n\n===C Payroll System====\n\n"); 
	printf("Menu choices: "); 
	printf("\na. Record Summary Details\n"); 
	printf("b. Display Employee Name\n");
	printf("c. Display Summary Gross and Tax Withheld\n");
	
	printf("\nEnter choice: "); 
	scanf("%s", &userInput);
	
	return userInput; 
}

void makeQuery(payrecord payroll[], int n, double gross, double tax, char userInput){
	
	switch (userInput){
		case 'a': printRecords(payroll, n);		
		break; 
			
		case 'b': printName(payroll, n);
		break; 
		
		case 'c': printSummary(gross, tax); 
		break; 
		
		default: printf("Invalid input!");		
	}
}
