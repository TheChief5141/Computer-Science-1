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

int main(){
    int test_cases;
    int num_courses;
    FILE* fPtr;
    fPtr = fopen("assignment1input->txt", "r");
    fscanf(fPtr,"%d", &test_cases);
    for(int w = 0; w < test_cases; w++){
        struct course ** mainTemp = (struct course**)malloc((test_cases) * sizeof(course));
        fscanf(fPtr,"%d", &num_courses);
        mainTemp[w]->sections = read_courses(fPtr, &num_courses);
        process_courses(mainTemp[w], *num_courses);
        release_courses(mainTemp[w], *num_courses);


    }



}

course *read_courses(FILE *fp, int *num_courses){
    student **ftr;
    char *word_course[50];
    struct course* temp = (struct course*)malloc(num_courses * (sizeof(struct course)));
    for(int i = 0; i < num_courses; i++){
        fscanf(fp, "%s", word_course);
        struct course** tmp = (struct course**)malloc(strlen(word_course) * sizeof(char));
        for(int x = 0; x < strlen(word_course); x++){
            tmp[i]->course_name= word_course[i];
        }
        temp[i]->course_name = tmp;
        fscanf(fp, "%d", temp[i]->num_sections);
        for(int v = 0; v < temp[i]->num_sections; v++){
            fscanf(fp, "%d %d", temp[i]->num_students, temp[i]->num_scores);
            ftr = readSections(fp, temp[i]->num_students, temp[i]->num_scores, temp[i]->num_sections);
        }
       
        
        
    }

    return ftr;
    



}

student **read_sections(FILE *fp, int num_students, int num_scores, int num_sections){
    char *lnameLength[50];
    struct student* newTemp = (struct student*)malloc((num_students) * sizeof(struct student));
    struct student* scoreTemp = (struct student*)malloc((num_scores) * sizeof(float));
    for(int c = 0; c < num_sections; c++){
        fscanf(fp, "%d %s", newTemp[c]->id, lnameLength);
        for(int y = 0; y < strlen(lnameLength); y++){
                newTemp[y]->lname = lnameLength[y];
        }
        for(int d = 0; d < num_scores; d++){
            fscanf(fp, "%f", scoreTemp[d]);
            newTemp[c]->std_avg += scoreTemp[d];//make sure to divide this by num_scores at the end
            
        }
    }


    return newTemp;
}

void process_courses(course *courses, int num_courses){
    int max_total = 0;
    int max_total_index = 0;
    int max_total_index_u = 0;
    int passCount = 0;
    int u = 0;
    for(int i = 0; i < num_courses; i++){
        printf("%s", courses[i]->course_name);
        printf("%d", passCount);
        for(u = 0; u < courses[i]->sections[u]->num_sections; u++){
            if(courses[i]->sections[u]->std_avg > max_total){
			    max_total = courses[i]->sections[u]->std_avg;
			    max_total_index = i;
                max_total_index_u = u;
		    }
            if((courses[i]->sections[u]->std_avg/courses[i]->sections[u]->num_scores) >= 70.0){
                passCount+=1;
                for(int h = 0; h < passCount; h++){
                    printf("%f", courses[i]->sections[u]->std_avg/courses[i]->sections[u]->num_scores);
                }
            }
        }
    }
    printf("%d %s %f", courses[max_total_index]->sections[max_total_index_u]->id, courses[max_total_index]->sections[max_total_index_u]->lname, courses[max_total_index]->sections[max_total_index_u]->std_avg/courses[max_total_index]->sections[max_total_index_u]->num_scores);
}

void release_courses(course *courses, int num_courses){
    int f = 0;
    for(int d = 0; d < num_courses; d++){
        for(f = 0; f < courses[d]->sections[f]->num_sections; f++){
            free(courses[d]->sections[f]->lname);
            free(courses[d]->sections[f]->scores);
            free(courses[d]->course_name);
            free(courses[d]->num_students);
            free(courses[d]->num_scores);
            

        }
    }
    free(courses);

}