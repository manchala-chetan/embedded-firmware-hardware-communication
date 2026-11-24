#include <stdio.h>
#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint32_t id;
	uint8_t fullName[100];
	uint8_t branch[30];
	uint8_t DOB[15];
	uint8_t semester;
} Student_t;

uint32_t studentCount = 0, maxStudentCount = 2;
Student_t students[10] = {};

void displayAllStudents(void);
void addNewStudent(void);
void removeStudent(uint32_t studentId);

int main(){
	uint8_t choice = 0;

	SetConsoleOutputCP(CP_UTF8);
	printf("----- Students Management Program -----\n");

	while(1){
		printf("\nOptions:\n");
		printf("1. Display all Students\n2. Add new Student\n3. Remove an Student\n4. Exit application\n");

		printf("\nEnter your choice: ");
		if(scanf("%hhu", &choice) != 1){
			printf("Invalid option!\n");

			while(getchar() != '\n');
			continue;
		}

		switch (choice) {
			case 1:
				displayAllStudents();
				break;
			case 2:
				addNewStudent();
				break;
			case 3:
				printf("\n--- Remove an Student ---\n");

				int32_t studentId = 0;

				if(studentCount > 0){
					printf("Enter Student ID: ");
					if(scanf("%d", &studentId) != 1 || studentId <= 0){
						printf("\nInvalid input!\nRemoving an student failed!\n");

						studentId = 0;

						while(getchar() != '\n');
						break;
					} else
						removeStudent(studentId);
				} else
					printf("\nThere are no students to delete!\n");

				studentId = 0;

				break;
			case 4:
				return 0;
			default:
				printf("Invalid option!\n");
				break;
		}
	}

	return 0;
}

void displayAllStudents(void){
	printf("\n--- Display all Students ---\n");

	if(studentCount > 0){
		for(uint32_t i = 0; i < maxStudentCount; i++){
			if(students[i].id != 0){
				printf("ID···········: %d\n", students[i].id);
				printf("Full name····: %s\n", students[i].fullName);
				printf("Date of birth: %s\n", students[i].DOB);
				printf("Branch·······: %s\n", students[i].branch);
				printf("Semester·····: %d\n\n", students[i].semester);
			}
		}
	} else
		printf("\nThere are no students to display!\n");
}

void addNewStudent(void){
	printf("\n--- Add new Student ---\n");

	if(studentCount < maxStudentCount){
		for(uint32_t i = 0; i < maxStudentCount; i++){
			if(students[i].id == 0){
				// Set Student ID
				int32_t studentId;

				printf("Enter the ID: ");
				if(scanf("%d", &studentId) != 1 || studentId <= 0){
					printf("\nInvalid input!\nAdding a new student failed!\n");

					while(getchar() != '\n');
					break;
				}

				for(uint32_t j = 0; j < maxStudentCount; j++){
					if(students[j].id == studentId){
						printf("\nThe entered ID currently belongs to another student!\nAdding a new student failed!\n");

						studentId = 0;

						while(getchar() != '\n');
						break;
					}
				}

				if(studentId != 0)
					students[i].id = studentId;
				else
					break;

				// Set Student Full name
				printf("Enter Full name: ");
				scanf(" %99[^\n]s", students[i].fullName);

				// Set Student Branch
				printf("Enter Branch: ");
				scanf(" %29[^\n]s", students[i].branch);

				// Set Student DOB
				printf("Enter Date of birth: ");
				scanf(" %14[^\n]s", students[i].DOB);

				// Set Student Semester
				printf("Enter Semester: ");
				int8_t studentSemester;
				if(scanf("%hhu", &studentSemester) != 1 || studentSemester <= 0){
					printf("\nInvalid input!\nAdding a new student failed!\n");

					students[i].id = 0;
					students[i].fullName[0] = '\0';
					students[i].branch[0] = '\0';
					students[i].DOB[0] = '\0';
					students[i].semester = 0;

					while(getchar() != '\n');
					break;
				}

				students[i].semester = studentSemester;

				studentCount++;

				printf("\nThe student was successfully added.\n");

				break;
			}
		}
	} else
		printf("\nThere is no space to add a student!\n");
}

void removeStudent(uint32_t studentId){
	bool found = false;

	for(uint32_t i = 0; i < maxStudentCount; i++){
		if(studentId == students[i].id){
			found = true;

			students[i].id = 0;
			students[i].fullName[0] = '\0';
			students[i].branch[0] = '\0';
			students[i].DOB[0] = '\0';
			students[i].semester = 0;

			studentCount--;

			printf("\nThe desired student was successfully removed.\n");
		}
	}

	if(!found)
		printf("\nNo student with ID \"%d\" found!\n", studentId);
}
