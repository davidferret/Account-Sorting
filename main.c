#include <stdio.h>
#include <string.h>
#define MAXLINE 8
#define MAXCHAR 30

void readData(int acc[], char name[][MAXCHAR], float balance[], int *size);
void sortData(int acc[], char name[][MAXCHAR], float balance[], int size, int sortBy);
void displayData(int acc[], char name[][MAXCHAR], float balance[], int size);
void saveToFile(int acc[], char name[][MAXCHAR], float balance[], int size);

int main(void) {
    int acc[MAXLINE], size, sortBy;
    char name[MAXLINE][MAXCHAR];
    float balance[MAXLINE];
    
    readData(acc, name, balance, &size);
    
    printf("Choose sorting method:\n");
    printf("1 - Sort by Account Number\n");
    printf("2 - Sort by Name (Alphabetically)\n");
    printf("3 - Sort by Balance (Descending)\n");
    printf("Enter choice: ");
    scanf("%d", &sortBy);
    
    sortData(acc, name, balance, size, sortBy);
    displayData(acc, name, balance, size);
    saveToFile(acc, name, balance, size);
    
    printf("Data saved to 'newdata.txt'.\n");
    return 0;
}

void readData(int acc[], char name[][MAXCHAR], float balance[], int *size) {
    FILE *fpt = fopen("data.txt", "r");
    if (fpt == NULL) {
        printf("FILE NOT FOUND.\n");
        return;
    }
    
    *size = 0;
    while (fscanf(fpt, "%d %s %f", &acc[*size], name[*size], &balance[*size]) != EOF) {
        (*size)++;
    }
    fclose(fpt);
}

void sortData(int acc[], char name[][MAXCHAR], float balance[], int size, int sortBy) {
    int temp_acc;
    char temp_name[MAXCHAR];
    float temp_balance;
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            int condition = 0;
            
            if (sortBy == 1) {
                condition = acc[j] > acc[j + 1];
            } else if (sortBy == 2) {
                condition = strcmp(name[j], name[j + 1]) > 0;
            } else if (sortBy == 3) {
                condition = balance[j] < balance[j + 1];
            }
            
            if (condition) {
                temp_acc = acc[j];
                acc[j] = acc[j + 1];
                acc[j + 1] = temp_acc;
                
                strcpy(temp_name, name[j]);
                strcpy(name[j], name[j + 1]);
                strcpy(name[j + 1], temp_name);
                
                temp_balance = balance[j];
                balance[j] = balance[j + 1];
                balance[j + 1] = temp_balance;
            }
        }
    }
}


void displayData(int acc[], char name[][MAXCHAR], float balance[], int size) {
    printf("%7s%13s%13s\n", "Account", "Name", "Balance");
    for (int j = 0; j < size; j++) {
        printf("%7d%13s%13.2f\n", acc[j], name[j], balance[j]);
    }
}

void saveToFile(int acc[], char name[][MAXCHAR], float balance[], int size) {
    FILE *fpw = fopen("newdata.txt", "w");
    if (!fpw) {
        printf("Error creating file!\n");
        return;
    }
    
    for (int j = 0; j < size; j++) {
        fprintf(fpw, "%d %s %.2f\n", acc[j], name[j], balance[j]);
    }
    fclose(fpw);
}
