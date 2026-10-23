#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

int search_by_phone(AddressBook *addressBook);
int search_by_mail(AddressBook *addressBook);

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria

    int i,j;
    Contact temp;
    for ( i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            if(strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
    
    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d | %s | %s | %s \n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validate_name(char *name)
{
    int i;
    for(i=0; name[i]!='\0'; i++)
    {
        if((name[i]>='A' && name[i] <='Z') || (name[i]>='a' && name[i] <='z') || (name[i] == ' ' || name[i] == '.'))
        {
            return 1;
        }
    }
}

int validate_phone(char *str, AddressBook *addressBook)
{
    int len = strlen(str);
    if (len != 10)
    {
        return 0;
    }

    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return 0;
        }
    }

    for ( i = 0; str[i] != '\0'; i++)
    {
        if (strcmp(addressBook->contacts[i].phone ,str) == 0)
        {
            printf("Number already exists\n");
            return 0;
        }

    }
    return 1;    
    
}

int validate_mail(char *str, AddressBook *addressBook)
{
    int i;

    for ( i = 0; str[i] != '\0'; i++)
    {
        if((str[i]>='a' && str[i] <='z') || (str[i] == '@' || str[i] == '.'))
        {
            return 1;
        }
        if (strcmp(addressBook->contacts[i].email ,str) == 0)
        {
            printf("Email already exists\n");
            return 0;
        }
    }   
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    char name[20];
    int valid;

    while(1)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", name);

        valid = validate_name(name);
        if(valid == 1)// valid
        break;
    }

    char mobile[11];
    while(1)
    {
        printf("Enter the phone : ");
        scanf(" %[^\n]", mobile);

        valid = validate_phone(mobile,addressBook);
        if(valid == 1)// valid
            break;
    }

    char mail[30];
    while (1)
    {
        printf("Enter the mail : ");
        scanf(" %[^\n]",mail);

        valid = validate_mail(mail,addressBook);
        if(valid == 1)
        break;
    }
    
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, mobile);
    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
    addressBook->contactCount++;

}

int search_by_name(AddressBook *addressBook)
{
    char str[50];
    int count=0,ind=0,i;
    printf("Enter the name: ");
    scanf(" %[^\n]",str);
        for(i=0; i< addressBook->contactCount; i++)
        {
            if((strcasecmp(str,addressBook->contacts[i].name)) == 0)
            {
                printf("%s %s %s \n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                ind = i;
                count++;
            }
        }
    
    if(count == 0)
    {
        printf("No contact found with that name.\n");
        return -1;
    }
    else if(count == 1)
    {
        return ind;
    }
    else
    {
        printf("Multiple contacts found. \n");
        return search_by_phone(addressBook);
    }
}

int search_by_phone(AddressBook *addressBook)
{
    char str[11];
    int i;
    printf("Enter the phone number : ");
    scanf(" %[^\n]", str);

    for ( i = 0; i < addressBook->contactCount; i++)
    {
       if(strcmp(str,addressBook->contacts[i].phone) == 0)
       {
        printf("%s %s %s \n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        return i;
       }
    }

    printf("No contact found with that phone number.\n");
    return -1;
}

int search_by_mail(AddressBook *addressBook)
{
    char str[50];
    int i;
    printf("Enter the Email Id : ");
    scanf(" %[^\n]", str);

    for ( i = 0; i < addressBook->contactCount; i++)
    {
       if(strcmp(str,addressBook->contacts[i].email) == 0)
       {
        printf("%s %s %s \n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        return i;
       }
    }

    printf("No contact found with that email.\n");
    return -1;
}

void searchContact(AddressBook *addressBook) 
{
    int option;
    printf("\nSearch by : \n");
    printf("1.Name\n");
    printf("2.Mobile\n");
    printf("3.Email\n");
    printf("Enter the option: ");
    scanf("%d",&option);

    switch (option)
    {
    case 1:
        search_by_name(addressBook);
        break;
    
    case 2:
        search_by_phone(addressBook);
        break;

    case 3:
        search_by_mail(addressBook);
        break;    
    default:
        printf("Invalid option. Please try again\n");
        break;
    }
}

void edit_name(AddressBook *addressBook,int res)
{
    char name[50];
    printf("Enter the name : ");
    scanf(" %[^\n]",name);
    strcpy(addressBook->contacts[res].name,name);
    printf("%s %s %s \n",addressBook->contacts[res].name,addressBook->contacts[res].phone,addressBook->contacts[res].email);
}

void edit_phone(AddressBook *addressBook, int res)
{
    char phone[11];
    printf("Enter the phone number : ");
    scanf(" %[^\n]",phone);
    strcpy(addressBook->contacts[res].phone,phone);
    printf("%s %s %s \n",addressBook->contacts[res].name,addressBook->contacts[res].phone,addressBook->contacts[res].email);
}

void edit_mail(AddressBook *addressBook, int res)
{
    char mail[50];
    printf("Enter the mail : ");
    scanf(" %[^\n]",mail);
    strcpy(addressBook->contacts[res].email,mail);
    printf("%s %s %s \n",addressBook->contacts[res].name,addressBook->contacts[res].phone,addressBook->contacts[res].email);
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int option, res;
    printf("\nSearch by : \n");
    printf("1.Name\n");
    printf("2.Mobile\n");
    printf("3.Email\n");
    printf("Enter the option: ");
    scanf("%d",&option);

    switch (option)
    {
    case 1:
        res = search_by_name(addressBook);
        break;
    
    case 2:
        res = search_by_phone(addressBook);
        break;

    case 3:
        res = search_by_mail(addressBook);
        break;    
    default:
        printf("Invalid option. Please try again\n");
        return;
    }

    if (res < 0 || res >= addressBook->contactCount) {
        printf("No contact found to edit.\n");
        return;
    }

    printf("\nEdit by : \n");
    printf("1.Name\n");
    printf("2.Mobile\n");
    printf("3.Email\n");
    printf("Enter the option: ");
    scanf("%d",&option);

    switch (option)
    {
    case 1:
        edit_name(addressBook,res);
        break;

    case 2:
        edit_phone(addressBook,res);
        break;

    case 3:
        edit_mail(addressBook,res);
        break;

    default:
        printf("Invalid option. Please try again\n");
        break;
    }
}

void deleteContact(AddressBook *addressBook)
{
    int res = search_by_name(addressBook);
    int i;
    if(res != -1)
    {
        for(i = res; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
        printf("Contact deleted successfully\n");
    }
}
