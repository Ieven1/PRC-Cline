#ifndef studenth
#define studenth

struct Student {
    char lastName[50];
    char firstName[50];
    char gender;
    int age;
    char group[20];
    float mathGrade;
    float physicsGrade;
    float chemistryGrade;
};

void initStudent(struct Student* student, const char* lastName, const char* firstName,
                 char gender, int age, const char* group,
                 float mathGrade, float physicsGrade, float chemistryGrade);


#endif