#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

#define MAX_TRANSACTIONS 100
#define FILE_NAME "budget_tracker.txt"



struct Transaction {
    char type;    // 'I' for Income, 'E' for Expense
	
    float amount;
	int sec; 
	int min;
	int hour;
	int day;
	int month;
	int year;
    
};

struct BudgetTracker {
    struct Transaction transactions[MAX_TRANSACTIONS];
    int num_transactions;
    float balance;
};

// Function prototypes
void initialize(struct BudgetTracker *tracker);
void addTransaction(struct BudgetTracker *tracker, char type, float amount);
void viewTransactions(struct BudgetTracker *tracker);
void saveToFile(struct BudgetTracker *tracker);
void loadFromFile(struct BudgetTracker *tracker);



int main() {
   
    struct BudgetTracker tracker;

    initialize(&tracker);   //initializing num_transactions and balance to 0

    loadFromFile(&tracker); // at the begining previous transactions are loaded to the tracker variable 

    char option;
    float amount;

    printf("Welcome to the Budget Tracker!\n");

    do {
        printf("\nOptions:\n");
        printf("1. Add Income\n");
        printf("2. Add Expense\n");
        printf("3. View Transactions\n");
        printf("4. View Balance\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf(" %c", &option);

        switch (option) {
            case '1':
                printf("Enter income amount: ");
                scanf("%f", &amount);
                addTransaction(&tracker,'I',amount);
                break;

            case '2':
                printf("Enter expense amount: ");
                scanf("%f", &amount);
                addTransaction(&tracker, 'E', amount);
                break;

            case '3':
                viewTransactions(&tracker);
                break;

            case '4':
                printf("Current Balance: $%.2f\n", tracker.balance);
                break;

            case '5':
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option. Try again.\n"); 	//if the option is other than 1,2,3,4,5 then another chance is given to the user
        }
    } while (option != '5');           //if option is 5 (exit) ,transactions are saved to the file

    saveToFile(&tracker);

    return 0;
}

void initialize(struct BudgetTracker *tracker) {
    tracker->num_transactions = 0;
    tracker->balance = 0.0;
}

void addTransaction(struct BudgetTracker *tracker, char type, float amount) {
     time_t now= time(NULL);
    struct tm *transactDate=gmtime(&now);
    if (tracker->num_transactions < MAX_TRANSACTIONS) {
        tracker->transactions[tracker->num_transactions].type = type;
        tracker->transactions[tracker->num_transactions].amount = amount;
	tracker->transactions[tracker->num_transactions].sec=transactDate->tm_sec;
	tracker->transactions[tracker->num_transactions].min=transactDate->tm_min;
	tracker->transactions[tracker->num_transactions].hour=transactDate->tm_hour;
	tracker->transactions[tracker->num_transactions].day=transactDate->tm_mday;
	tracker->transactions[tracker->num_transactions].month=transactDate->tm_mon;
	tracker->transactions[tracker->num_transactions].year=transactDate->tm_year;

        tracker->num_transactions++;
	

        if (type == 'I') {
            tracker->balance += amount;
        } else {
            tracker->balance -= amount;
        }

        printf("Transaction added successfully.\n");
    } else {
        printf("Transaction limit reached. Cannot add more transactions.\n");
    }
}

void viewTransactions(struct BudgetTracker *tracker) {
    printf("\n--- Transactions ---\n");
    for (int i = 0; i < tracker->num_transactions; i++) {
        printf("%c %.2f %d-%d-%d  %d:%d:%d\n", tracker->transactions[i].type, tracker->transactions[i].amount,tracker->transactions[i].year,tracker->transactions[i].month,tracker->transactions[i].day,tracker->transactions[i].hour,tracker->transactions[i].min,tracker->transactions[i].sec);
    }
}

void saveToFile(struct BudgetTracker *tracker) {
    FILE *fptr = fopen(FILE_NAME, "w");
    if (fptr) {
      
        fprintf(fptr, "%.2f\n", tracker->balance); //writing balance in the file
        for (int i = 0; i < tracker->num_transactions; i++) {
            fprintf(fptr, "%c %.2f %d-%d-%d %d:%d:%d\n", tracker->transactions[i].type, tracker->transactions[i].amount,tracker->transactions[i].year,tracker->transactions[i].month,tracker->transactions[i].day,tracker->transactions[i].hour,tracker->transactions[i].min,tracker->transactions[i].sec);
        }
        fclose(fptr);
    } else {
        printf("Error: Unable to save data to file.\n");
    }
}

void loadFromFile(struct BudgetTracker *tracker) {
    FILE *fptr = fopen(FILE_NAME, "r");
    if (fptr) {
        fscanf(fptr, "%f\n", &tracker->balance);
    char type;
    float amount = 0.0;
	int sec = 0; 
	int min = 0;
	int hour = 0;
	int day = 0;
	int month = 0;
	int year = 0;
	
        
    while (fscanf(fptr,"%c %f %d-%d-%d %d:%d:%d\n", &type, &amount, &year, &month, &day, &hour, &min, &sec)==8) {
        
        // printf("mmmmmmmmmmmmmmmmm");
        tracker->transactions[tracker->num_transactions].type = type;
        tracker->transactions[tracker->num_transactions].amount = amount;
        tracker->transactions[tracker->num_transactions].sec = sec;
        tracker->transactions[tracker->num_transactions].min = min;
        tracker->transactions[tracker->num_transactions].hour = hour;
        tracker->transactions[tracker->num_transactions].day = day;
        tracker->transactions[tracker->num_transactions].month = month;
        tracker->transactions[tracker->num_transactions].year = year;
     
 
           tracker->num_transactions++;
           printf("%d\n",tracker->num_transactions);
}
        fclose(fptr);
    }
    printf("%d\n",tracker->num_transactions);
   
}