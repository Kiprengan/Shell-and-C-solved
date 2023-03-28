#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 100
#define MAXNAMELEN 25

typedef struct {
    char firstname[25];
    char lastname[25];
    int midterm1;
    int midterm2;
    int final;
    double average;
    char grade;
} student_t;

void compute_student_average(student_t *student) {
    student->average = (student->midterm1 + student->midterm2 + student->final) / 3.0;
    if ((student->average)>=90){
    student->grade = 'A';
    } else if(((student->average)>=80) && ((student->average)<90)){
    student->grade = 'B';
    } else if (((student->average)>=70) && ((student->average)<80)){
    student->grade = 'C';
    } else if (((student->average)>=60) && ((student->average)<70)){
    student->grade = 'D';
    } else{
    student->grade = 'F';
    }
}

void print_student_info(FILE *output_file, student_t *student) {
    fprintf(output_file, "%s\t%s\t%d\t%d\t%d\t%c\n", student->firstname, student->lastname,
            student->midterm1, student->midterm2, student->final, student->grade);
}

int main() {
    FILE *input_file, *output_file;
    char line[MAX_LINE_LEN];
    char filename[MAXNAMELEN];
    memset(filename, '\0', MAXNAMELEN);
    scanf("%20s", filename);
    student_t student;
    

    // Open the input file
    input_file = fopen(filename, "r");
    if (input_file == NULL) {
        printf("Error: Could not open input file\n");
        exit(1);
    }

    // Open the output file
    output_file = fopen("report.txt", "w");
    if (output_file == NULL) {
        printf("Error: Could not open output file\n");
        exit(1);
    }
    double midterm1t=0.0;
    double midterm2t=0.0;
    double finalt=0.0;
    double i=0.0;
    // Read the input file line by line
    while (fgets(line, MAX_LINE_LEN, input_file)) {
        char *token;
        // Extract student information from the line
        token = strtok(line, "\t");
        strcpy(student.firstname, token);
        token = strtok(NULL, "\t");
        strcpy(student.lastname, token);
        token = strtok(NULL, "\t");
        student.midterm1 = atof(token);
        token = strtok(NULL, "\t");
        student.midterm2 = atof(token);
        token = strtok(NULL, "\t");
        student.final = atof(token);

        // Totals of midterm1, midterm2 and final
        i = i + 1;
        midterm1t = midterm1t + student.midterm1;
        midterm2t = midterm2t + student.midterm2;
        finalt = finalt + student.final;
        // Compute the student's average
        compute_student_average(&student);

        // Write the student's information to the output file
        print_student_info(output_file, &student);
    }
    fprintf(output_file, "\nAverages: midterm1 %.2f, midterm2 %.2f, final %.2f\n",midterm1t/i,midterm2t/i,finalt/i);

    // Close the files
    fclose(input_file);
    fclose(output_file);

    return 0;
}
