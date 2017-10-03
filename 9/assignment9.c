#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct Student {

  int roll;
  char name[100];
  float percentage;

}Student;

char *file_path = "temp.txt";

void write_student(Student student) {

  printf("In Write\n");
  int fd = open(file_path, O_CREAT | O_WRONLY);
  write(fd, &student, sizeof(student));
  close(fd);

}

Student read_student() {

  Student student;
  printf("In Read\n");
  int fd = open(file_path, O_RDONLY);
  read(fd, &student, sizeof(student));
  close(fd);
  return student;

}

int main(int argc, char const *argv[]) {

  Student student;

  printf("Enter the Roll Number, Name and Percentage\n");
  scanf("%d%s%f", &student.roll, student.name, &student.percentage);

  write_student(student);

  student = read_student();

  printf("Name: %s\nRoll Number: %d\nPercentage: %f\n", student.name, student.roll, student.percentage);

  return 0;
}
