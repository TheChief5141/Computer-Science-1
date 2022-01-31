#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    int id;
    char* lname;
    float* scores;
    float std_avg;
}student;

typedef struct course{
    char* course_name;
    int num_sections;
    student **sections;
    int *num_students;
    int *num_scores;
}course;

course *read_courses(FILE *fp, int *num_courses);
student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections);
void process_courses(course *courses, int num_courses);
void release_courses(course *courses, int num_courses);