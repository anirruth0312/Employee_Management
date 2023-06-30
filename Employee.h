#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <windows.h>

using namespace std;

class Employee
{
private:
    char name[30];
    char id[5];
    char designation[10];
    int age;
    int experience;

    void waitForEnter(void);

    void displayEmployees(void);

    void addEmployee(void);

    void updateEmployee(void);

    void deleteEmployee(void);

public:
    void operations(void);
};

#endif // EMPLOYEE_H
