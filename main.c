#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {

int day;
int month;
int year;

} Date;


typedef struct {

int eid;
char *firstName;
char *lastName;
double gpa;
Date dateOfBirth;

} Student;

Student *createStudent( int eid,
                        char *firstName,
                        char *lastName,
                        double gpa,
                        int day,int month,int year);
int cmpIntAsc(const void *a, const void *b);
int cmpDoubleAsc(const void *a, const void *b);
void printRoster(Student * roster, int n);
int cmpStudentByName(const void *a, const void *b);
void printStudent (const Student *s);
int cmpStudentByEID(const void *a, const void *b);
int cmpStudentByGPA(const void *a, const void *b);



int main (int argc, char **argv) {

  int n=4;
  Student roster[4];
  roster[0]= *createStudent(12345678, "Jack", "Dorsey",3.8, 11,19,1976);
  roster[1]= *createStudent(33833456, "Anita", "Borg", 3.67, 1,17,1949);
  roster[2]= *createStudent(82934567, " Dennis", "Ritchie", 3.4, 9,9,1941);
  roster[3]= *createStudent(34567823, "Alan", "Turing",3.9, 6,23,1912);

  printf("\n");
  printf("*********Original roster:************\n");
  printRoster(roster, n);
  qsort(roster, n, sizeof(Student),cmpStudentByName);

  printf("\n");
  printf("*********Roster sorted by last name:************\n");
  printRoster(roster, n);

  qsort(roster, n, sizeof(Student),cmpStudentByEID);
  printf("\n");
  printf("*********Roster sorted by eid:************\n");
  printRoster(roster, n);
  
  qsort(roster, n, sizeof(Student),cmpStudentByGPA);
  printf("\n");
  printf("*********Roster sorted by GPA:************\n");
  printRoster(roster, n);

  printf("\n");
  printf("*********C generic search function: bsearch*****************\n");
  //Dummy student
  Student dkey={33833456,"" , " ", 0,0,0,0};
  //make sure array is sorted!
  qsort(roster, n, sizeof(Student),cmpStudentByEID);
  Student *s=bsearch(&dkey, roster, n, sizeof(Student),cmpStudentByEID);
  //cmpStudentByEID: comparator that we want to use to search for a match
  printf("Found!\n");
  printStudent(s);
  return 0;
}









int cmpIntAsc(const void *a, const void *b){

  const int *x= (const int *)a;
  const int *y= (const int *)b;

  if (*x < *y) {//in order
    return -1;
  } else if (*x > *y) {//out of order
    return 1;
  } else {
    return 0;
  } 
}

int cmpDoubleAsc(const void *a, const void *b){

  const double *x= (const double *)a;
  const double *y= (const double *)b;

  if (*x < *y) {//in order
    return -1;
  } else if (*x > *y) {//out of order
    return 1;
  } else {
    return 0;
  } 
}

Student *createStudent( int eid,
                        char *firstName,
                        char *lastName,
                        double gpa,
                        int day,int month,int year) {

                          
  Student *s= (Student *) malloc (sizeof(Student) * 1);
  s->eid=eid;
  s->firstName=(char *) malloc(sizeof(char) * (strlen(firstName)+1));
  strcpy(s->firstName, firstName);
  s->lastName=(char *) malloc(sizeof(char) * (strlen(lastName)+1));
  strcpy(s->lastName, lastName);
  s->gpa=gpa;
  s->dateOfBirth.day=day;
  s->dateOfBirth.month=month;
  s->dateOfBirth.year=year;

return s;
}


void printRoster(Student * roster, int n) {

for (int i=0; i < n; i++) {
  printf("\n");
  printStudent(&roster[i]);
  
}
}

int cmpStudentByName(const void *a, const void *b){

  const Student *x= (Student *) a;
  const Student *y= (Student *) b;

  int r=strcmp(x->lastName, y->lastName);
  if (r==0){
    return strcmp(x->firstName, y->firstName);
  } else {
    return r;
  }
}

void printStudent (const Student *s){

printf("%s, %s, %d, %0.2f, %d, %d, %d\n", s->lastName, s->firstName,s->eid,
s->gpa, s->dateOfBirth.day,s->dateOfBirth.month,s->dateOfBirth.year);
 
}

int cmpStudentByEID(const void *a, const void *b){

  const Student *x= (Student *) a;
  const Student *y= (Student *) b;

return cmpIntAsc (&(x->eid),&(y->eid));
}

int cmpStudentByGPA(const void *a, const void *b){

  const Student *x= (Student *) a;
  const Student *y= (Student *) b;

if (x->gpa < y->gpa){ //if x has less gpa, it goes after y
  return 1;
} else if (x->gpa > y->gpa){
  return -1;
} else {
  return 0;
}
}