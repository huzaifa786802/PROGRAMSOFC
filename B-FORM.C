#include <stdio.h>
#include <stdlib.h>

int main() {
    // Writing data to a file
    FILE *filePointer;
    char fileName[] = "student_info.txt";
    filePointer = fopen(fileName, "w"); // Open file in write mode

    if (filePointer == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Writing information to the file
    fprintf(filePointer, "Name: John Doe\n");
    fprintf(filePointer, "Father's Name: Mike Doe\n");
    fprintf(filePointer, "Registration Number: 12345\n");
    fprintf(filePointer, "Class: 10\n");

    // Closing the file
    fclose(filePointer);

    // Reading data from the file and saving it into a variable
    char data[100]; // Assuming a maximum of 100 characters per line
    filePointer = fopen(fileName, "r"); // Open file in read mode
    if (filePointer == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    int i = 0;
    while (fgets(data + i, sizeof(data) - i, filePointer) != NULL) {
        i += strlen(data + i);
    }
    // Closing the file
    fclose(filePointer);
    printf("Data read from the file:\n%s", data);
    return 0;
}