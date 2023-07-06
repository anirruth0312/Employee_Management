#include "Employee.h"
#include <conio.h>
#include <unistd.h>

void Employee::waitForEnter()
{
    cout << "\n\nPress enter to go back\n\n";
    cin.get();
    cin.get();
}

void Employee::displayEmployees()
{
    system("cls");
    FILE *file = fopen("data.txt", "r");
    cout << "List of Employees\n";
    cout << "NAME\t|\tID\t|\tDesignation\t|\tAge\n";
    cout << "-------------------------------------------------------------\n";
    while (fscanf(file, "%s %s %s %d %d", name, id, designation, &age, &experience) != EOF)
    {
        // Convert name, id, and designation to uppercase
        for (int i = 0; name[i] != '\0'; i++)
            name[i] = toupper(name[i]);
        for (int i = 0; id[i] != '\0'; i++)
            id[i] = toupper(id[i]);
        for (int i = 0; designation[i] != '\0'; i++)
            designation[i] = toupper(designation[i]);

        cout << name << "\t|\t" << id << "\t|\t" << setw(15) << left << designation << "\t|\t" << age << "\n";
    }
    fclose(file);
    waitForEnter();
}

void Employee::addEmployee()
{
    system("cls");
    char add = 'Y';

    while (add == 'Y')
    {
        cout << "\nEnter Employee first name : ";
        cin >> name;
        cout << "\nEnter Employee designation : ";
        cin >> designation;
        cout << "\nEnter age : ";
        cin >> age;
        cout << "\nEnter experience (in years): ";
        cin >> experience;
        char lastId[5];
        FILE *file = fopen("data.txt", "r");
        bool fileIsEmpty = true;
        while (fscanf(file, "%*s %s %*s %*d %*d", lastId) != EOF)
        {
            // Continue reading until the last ID is obtained
            fileIsEmpty = false;
        }
        fclose(file);
        file = fopen("data.txt", "a");
        string newid = "";
        if (fileIsEmpty)
        {
            newid = "1";
            fprintf(file, "%s %s %s %d %d\n", name, newid.c_str(), designation, age, experience);
        }
        else
        {
            int val = atoi(lastId);
            newid = to_string(val + 1);
            fprintf(file, "%s %s %s %d %d\n", name, newid.c_str(), designation, age, experience);
        }
        fclose(file);
        cout << "\nNew Employee has been added to the database with ID: " << newid;
        cout << "\n\nDo you want to add another Employee? (Y/N): ";
        cin >> add;
        add = toupper(add);
    }
    cout << "\n";
}
void Employee::updateEmployee()
{
    system("cls");
    FILE *file = fopen("data.txt", "r");
    char newid[5];
    char newdesignation[100];
update:
    cout << "Enter the Employee id: ";
    cin >> newid;
    bool ispresent = false;
    while (fscanf(file, "%s %s %s %d %d", name, id, designation, &age, &experience) != EOF)
    {
        if (strcmp(newid, id) == 0)
        {
            ispresent = true;
        }
    }
    if (!ispresent)
    {
        cout << "\nEmployee ID doesn't exist. Enter a valid ID: ";
        goto update;
    }
    cout << "Enter new Employee designation: ";
    cin >> newdesignation;
    FILE *tempfile = fopen("tempfile.txt", "w");
    rewind(file); // Rewind the file pointer back to the beginning
    while (fscanf(file, "%s %s %s %d %d", name, id, designation, &age, &experience) != EOF)
    {
        if (strcmp(newid, id) == 0)
        {
            fprintf(tempfile, "%s %s %s %d %d\n", name, id, newdesignation, age, experience);
        }
        else
        {
            fprintf(tempfile, "%s %s %s %d %d\n", name, id, designation, age, experience);
        }
    }
    fclose(file);
    fclose(tempfile);
    int removed = remove("data.txt");
    int renamed = rename("tempfile.txt", "data.txt");
    if (removed == 0 && renamed == 0)
    {
        cout << "Employee details updated successfully";
    }
    else
    {
        cout << "Error updating employee details";
    }
    waitForEnter();
}

void Employee::deleteEmployee()
{
    system("cls");
    char newid[5];
    char newdesignation[100];

del:
    cout << "Enter the Employee ID: ";
    cin >> newid;

    bool isPresent = false;
    FILE *file = fopen("data.txt", "r");

    // Check if the employee ID exists in the file
    while (fscanf(file, "%s %s %s %d %d", name, id, designation, &age, &experience) != EOF)
    {
        if (strcmp(newid, id) == 0)
        {
            isPresent = true;
            break;
        }
    }

    fclose(file);

    if (!isPresent)
    {
        cout << "\nEmployee ID doesn't exist. Enter a valid ID.\n";
        goto del;
    }

    FILE *tempfile = fopen("tempfile.txt", "w");
    file = fopen("data.txt", "r");

    // Copy records to tempfile excluding the one to be deleted
    while (fscanf(file, "%s %s %s %d %d", name, id, designation, &age, &experience) != EOF)
    {
        if (strcmp(newid, id) == 0)
        {
            continue; // Skip the record to be deleted
        }
        else
        {
            fprintf(tempfile, "%s %s %s %d %d\n", name, id, designation, age, experience);
        }
    }

    fclose(file);
    fclose(tempfile);
    // Remove the original file and rename the tempfile
    int removed = remove("data.txt");
    int renamed = rename("tempfile.txt", "data.txt");
    if (removed == 0 && renamed == 0)
    {
        cout << "Employee record deleted successfully";
    }
    else
    {
        cout << "Error deleting employee record";
    }

    waitForEnter();
}

void Employee::operations()
{
    int flag = 1;
    while (flag)
    {
        cout << "\nEnter your choice\n\n";
        cout << "1) Add a new Employee\n";
        cout << "2) View all Employees \n";
        cout << "3) Update an existing record\n";
        cout << "4) Delete a record\n";
        cout << "5) Exit\n\n";
        cin >> flag;
        switch (flag)
        {
        case 1:
            addEmployee();
            break;
        case 2:
            displayEmployees();
            break;
        case 3:
            updateEmployee();
            break;
        case 4:
            deleteEmployee();
            break;
        case 5:
            flag = 0;
            break;
        default:
            cout << "\nInvalid choice entered. Please try again\n";
            break;
        }
    }
}
