#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<conio.h>
#define Maxbook 100

typedef struct welcome//Declares a structure to store the login data
{
	char name[25];
	char pass[10];
}login; //alias for the login struct

typedef union INPUT//Declares a union
{
	int search;
}input; //alias for the input union

	typedef struct bookInfo //structure for the book information
{
	int isbn,access;
	char book_title[30],author[50],condition[15];
}BOOK; //alias for the book information

	typedef struct date //structure for the date
	{
		int day, month, year;
	}DATE; //alias for the date structure
typedef struct memberInfo //structure for the member information
{
	int mem_id, phone_num;
	char f_name[25], l_name[25], address[50],mem_type[25], allowance[25];
	DATE date; // nested structure variable of type DATE
}MEMBER; // alias for the member information structure
typedef struct borrowInfo //borrow book information structure
{
	int mem_id, isbn;
	DATE borrow;
	DATE to_return;
}BORROW; //alias for the borrow book information structure
typedef struct lateInfo //late information structure
{
	int mem_id, isbn;
	float l_charge;
	DATE returned;
}LATE; // alias for the late information structure

// Functions
void menu();
void resetLogin();

//Book Functions//
void bookMenu();
void AddNewBook();
void UpdateBook();
void DeleteBook();
void DisplayBooks();

//Member Functions//
void memberMenu();
void AddNewMember();
void UpdateMember();
void DeleteMember();
void DisplayMember();
void AllMember();


//Borrow Functions//
void borrowRB();
void borrowBook();
void displayBorrow();
void returnBook();
void checkCharges();
void displayCharges();
void makePayment();
int main()
{
	system("color D7");

	char username[25]="Empty";
	char pass[10]="Empty";
	login enter;
	FILE* fptr;
	int s = 0, i=0,valid=1;
	if ((fptr = fopen("Login.bin", "rb")) == NULL)
	{
		strcpy(enter.name, "admin");
		strcpy(enter.pass, "welcome1");
		fptr = fopen("Login.bin", "wb");
			fwrite(&enter, sizeof(enter), 1, fptr);
	}
	else
	{
		fread(&enter, sizeof(enter), 1, fptr);
		do
		{
			printf("\t\t\t\t*******************************************************************\n");
        	printf("\t\t\t\t*   WELCOME TO THE OFFICIAL LIBRARY MANAGEMENT SYSTEM 2019        *\n");
        	printf("\t\t\t\t*             **********************************                  *\n");
			printf("\t\t\t\t*                   Enter Username:                               *\n");
			printf("\t\t\t\t\t\t\t");
			fflush(stdin);
			gets(username); //used to scan or read a line of text that was inputed
			strlwr(username); //Used to convert the user specified characters or string into Lowercase letters.

			printf("\t\t\t\t*                  Enter Password [8] characters:                 *\n");
			printf("\t\t\t\t\t\t\t");
			for (i = 0; i < 8; i++)
			{
				char ch = getch();
				pass[i] = ch;
				ch = '*';
				printf("%c", ch);
			}
			strlwr(pass);
			system("cls");
			if (strcmp(username, enter.name) == 0) 
			{
				if (strcmp(pass, enter.pass) == 0)
				{
					valid = 0;
					s = 3; // this allows the program to shut down after inputting the password 3 times
				}
				else
					printf("\t\t\t\tInvalid password\n\t\t\t\tTry Again\n");
					//system("pause");
					//system("cls");
					printf("\t\t\t\t\n");
			}
			else
			{
				if (strcmp(pass, enter.pass) != 0) 
					printf("\t\t\t\tInvalid username and password\n");
				else
					printf("\t\t\t\tInvalid username\n\t\t\t\tTry Again\n");
				//	system("pause");
				//	system("cls");
					printf("\t\t\t\t\n");
			}
			s++;
		} while (s < 3);
		fclose(fptr);
		if (valid == 0)
			menu();
		else
		{
			printf("\t\t\t\tYou have been locked out of the system\n");
			printf("\t\t\t\tPlease contact Administrator!\n");
			printf("\t\t\t\t Goodbye\n");
	   }
	}
	return 0;
}

void  menu()
{
	system("cls");
	int choice=1;
	while(choice !=5){
        printf("\t\t\t\t********************************************************************\n");
        printf("\t\t\t\t*  WELCOME TO THE OFFICIAL LIBRARY MANAGEMENT SYSTEM 2019          *\n");
        printf("\t\t\t\t*              **********************************                  *\n");
        printf("\t\t\t\t*                     ***MAIN MENU***                              *\n");
        printf("\t\t\t\t*                  1) Reset Login Credentials                      *\n");
        printf("\t\t\t\t*                  2) Books                                        *\n");
        printf("\t\t\t\t*                  3) Member                                       *\n");
        printf("\t\t\t\t*                  4) Borrow, Return and Balances                  *\n");
        printf("\t\t\t\t*                  5) Exit                                         *\n");
      	printf("\t\t\t\t********************************************************************\n");
      	printf("\t\t\t\t Select choice:");
        scanf("%d",&choice);
		switch (choice)
		{
		case 1:
			resetLogin();
			break;
		case 2:
			bookMenu();
			break;
		case 3:
			memberMenu();
			break;
		case 4:
			borrowRB();
			break;
		case 5:
			printf("\t\t\t\tYou Have Successfully Logged Out Of the System\n\t\t\t\tThank You!\n");
			break;
		}
		if (choice >= 1 && choice <= 5)
	//	system("pause");
	//	system("cls");
	if (choice < 1 || choice>5)
		{
			printf("\t\t\t\tInvalid choice\n");
			printf("\t\t\t\tPress enter on the keyboard to try again\n");
		}
	//	system("pause");
	//	system("cls");
	}
}
void resetLogin()
{
	system("cls");
	char username[25]="Empty";
	char pass[10]="Empty";
	login enter;
	FILE* fptr = NULL;
	fptr = fopen("LateCharges.bin", "wb");
	fflush(stdin);
	printf("\t\t\t\tEnter new username: ");
	gets(username);
	fflush(stdin);
	printf("\t\t\t\tEnter new password [8 characters]: ");
	gets(pass);
	while (strlen(pass) > 8 || strlen(pass) < 8)
	{
		printf("\t\t\t\tPassword can only be 8 characters long\n");
		printf("\t\t\t\tEnter new password [8 characters]: ");
		fgets(pass, sizeof(pass), stdin);
	}
	strcpy(enter.name,username);
	strcpy(enter.pass, pass);
	fwrite(&enter, sizeof(enter), 1, fptr);
	fclose(fptr);
}
void bookMenu()
{
	int opt = 0;
	do
	{
		system("cls");
		printf("\t\t\t\t********************************************************************\n");
        printf("\t\t\t\t*  WELCOME TO THE OFFICIAL LIBRARY MANAGEMENT SYSTEM 2019          *\n");
        printf("\t\t\t\t*              **********************************                  *\n");
        printf("\t\t\t\t*                     ***BOOKS MENU***                             *\n");
        printf("\t\t\t\t*                  1) Add New Book                                 *\n");
        printf("\t\t\t\t*                  2) Update Book                                  *\n");
        printf("\t\t\t\t*                  3) Delete Book                                  *\n");
        printf("\t\t\t\t*                  4) Display Book                                 *\n");
        printf("\t\t\t\t*                  5) Exit Back to Main menu                       *\n");
      	printf("\t\t\t\t********************************************************************\n");
      	printf("\t\t\t\tSelect Choice:");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1:
			AddNewBook();
			break;
		case 2:
			UpdateBook();
			break;
		case 3:
			DeleteBook();
			break;
		case 4:
			DisplayBooks();
			break;
		case 5:
			menu();
			break;
		}
		if (opt >= 1 && opt <= 5)
			system("pause");
		system("cls");
		if (opt < 1 || opt>5)
			printf("\t\t\t\tInvalid choice\n\t\t\t\tPlease try again\n");

	} while (opt != 5);
}
void memberMenu()
{
	system("cls");
	int opt = 0;
	do {
		printf("\t\t\t\t********************************************************************\n");
        printf("\t\t\t\t*  WELCOME TO THE OFFICIAL LIBRARY MANAGEMENT SYSTEM 2019          *\n");
        printf("\t\t\t\t*              **********************************                  *\n");
        printf("\t\t\t\t*                     ***MEMBER MENU***                            *\n");
        printf("\t\t\t\t*                  1) Add New Member                               *\n");
        printf("\t\t\t\t*                  2) Update Member Information                    *\n");
        printf("\t\t\t\t*                  3) Delete Member Information                    *\n");
        printf("\t\t\t\t*                  4) Display Member Information                   *\n");
        printf("\t\t\t\t*                  5) Display all Member Information               *\n");
        printf("\t\t\t\t*                  6) Exit Back to Main menu                       *\n");
      	printf("\t\t\t\t********************************************************************\n");
      	printf("\t\t\t\tSelect Choice:");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1:
			AddNewMember();
			break;
		case 2:
			UpdateMember();
			break;
		case 3:
			DeleteMember();
			break;
		case 4:
			DisplayMember();
			break;
		case 5:
			AllMember();
			break;
		case 6:
			menu();
			break;
		}
		if (opt >= 1 && opt <= 6)
			system("pause");
		system("cls");
		if (opt < 1 || opt>6)
			printf("\t\t\t\tInvalid choice\n\t\t\t\tTry Again\n");
	} while (opt != 6);
}
void borrowRB()
{
	system("cls");
	int opt;
	do
	{
	//	printf("1.Borrow Book\n2.Display All Books On Loan\n3..Return book\n4..Check Member Charges\n5...Display Late Charges\n6...Make Payment\n7...exit to Main Menu\n");
		printf("\t\t\t\t********************************************************************\n");
        printf("\t\t\t\t*  WELCOME TO THE OFFICIAL LIBRARY MANAGEMENT SYSTEM 2019          *\n");
        printf("\t\t\t\t*              **********************************                  *\n");
        printf("\t\t\t\t*              **BORROW,RETURN AND BALANCES MENU**                 *\n");
        printf("\t\t\t\t*                  1) Borrow Book                                  *\n");
        printf("\t\t\t\t*                  2) Display All Books On Loan                    *\n");
        printf("\t\t\t\t*                  3) Return Book                                  *\n");
        printf("\t\t\t\t*                  4) Check Member Charges                         *\n");
        printf("\t\t\t\t*                  5) Display Late Charges                         *\n");
        printf("\t\t\t\t*                  6) Make Payment                                 *\n");
        printf("\t\t\t\t*                  7) Exit to main menu                            *\n");
      	printf("\t\t\t\t********************************************************************\n");
      	printf("\t\t\t\tSelect Choice:");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1:
			borrowBook();
			break;
		case 2:
			displayBorrow();
			break;
		case 3:
			returnBook();
			break;
		case 4:
			checkCharges();
			break;
		case 5:
			displayCharges();
			break;
		case 6:
			makePayment();
			break;
		case 7:
			menu();
			break;
		}
		if (opt >= 1 && opt <= 7)
			system("pause");
		system("cls");
		if (opt < 1 || opt>7)
			printf("\t\t\t\tInvalid choice\n");
	} while (opt != 7);
}

void AddNewBook() {

	int book_total = 0;
	char ans='Y';
	FILE* fp = NULL;
	BOOK info;
	if ((fp = fopen("Book.bin", "ab")) == NULL)
		printf("\t\t\t\tError opening this file\n");
	else
	{
		do
		{
			system("cls");
			printf("\n\t\t\t\tEnter the following Book Information:-\n");
			printf("\n\t\t\t\tEnter the Book Title: ");
			fflush(stdin);
			gets(info.book_title);
			printf("\n\t\t\t\tEnter the Book Author: ");
			fflush(stdin);
			fgets(info.author, sizeof(info.author), stdin);
			printf("\n\t\t\t\tEnter the Book Status(D for donated or P for purchase): ");
			fflush(stdin);
			fgets(info.condition, sizeof(info.condition), stdin);
			printf("\n\t\t\t\tEnter the Book ISBN #(12 digits): ");
			fflush(stdin);
			scanf("%d", &info.isbn);
			printf("\n\t\t\t\tEnter the Book Accession #(6 digits): ");
			fflush(stdin);
			scanf("%d", &info.access);
			book_total += 1;
			printf("\n\t\t\t\tWould you like to add another Book?\n\t\t\t\t Select Y for Yes or N for No   :  ");
			fflush(stdin);
			scanf("%c", &ans);
			fwrite(&info, sizeof(info), 1, fp);
			system("cls");
		}while (ans != 'n' && ans != 'N');
		printf("\t\t\t\tBOOK INFORMATION HAS BEEN SUCCESSFULLY STORED!\n\n");
		fclose(fp);
	}
}

void UpdateBook() {
	BOOK info, update;
	int found = 0, i = 0, q = 0;
	FILE* fptr = NULL;
	char ans = 'Y';
	system("cls");
	if ((fptr = fopen("Book.bin", "rb+")) == NULL)
		printf("\t\t\t\tNO BOOKS ARE AVAILABLE AT THIS TIME!\n\n");
	else
	{
		do
		{
			printf("\n\t\t\t\tEnter the title of the book you would like to update: ");
			fflush(stdin);
			gets(update.book_title);
			system("cls");
			fread(&info, sizeof(info), 1, fptr);
			while (!feof(fptr))
			{
				if (strcmp(update.book_title, info.book_title) == 0)
				{
					found = 1;
					q = i;
				}
				i++;
				fread(&info, sizeof(info), 1, fptr);
			}
			if (found == 1)
			{
				printf("\n\t\t\t\tEnter the following Book Information:-\n");
				printf("\t\t\t\tEnter the Book Title: ");
				fflush(stdin);
				gets(update.book_title);
				printf("\n\t\t\t\tEnter the Book Author: ");
				fflush(stdin);
				fgets(update.author, sizeof(update.author), stdin);
				printf("\n\t\t\t\tEnter the Book Status: ");
				fflush(stdin);
				fgets(update.condition, sizeof(update.condition), stdin);
				printf("\n\t\t\t\tEnter the Book ISBN #(12 digits): ");
				fflush(stdin);
				scanf("%d", &update.isbn);
				printf("\n\t\t\t\tEnter the Book Accession #(6 digits): ");
				fflush(stdin);
				scanf("%d", &update.access);
				fseek(fptr, (q * sizeof(update)), SEEK_SET);
				fwrite(&update, sizeof(update), 1, fptr);
				printf("\t\t\t\t\nBOOK INFORMATION HAS BEEN SUCCESSFULLY STORED!\n\n");
			}
			else
				printf("\t\t\t\tUnfortunately, This book has not been located \n");
			printf("\n\t\t\t\tWould you like to update another Book?\n\t\t\t\tSelect Y for Yes or N for No  :  ");
			fflush(stdin);
			scanf("%c", &ans);
			system("cls");
		} while (ans != 'n' && ans != 'N');
		fclose(fptr);
	}
}
void DeleteBook(){
	BOOK info[Maxbook];
	char title[30]="";
	int i = 0,found=0,q=0,x=0;
	FILE* fptr = NULL;
	system("cls");
	if ((fptr = fopen("Book.bin", "rb")) == NULL)
		printf("\t\t\t\tNO BOOKS ARE AVAILABLE AT THIS TIME!\n\n");
	else
	{
		printf("\n\t\t\t\tEnter the title of the book you would like to delete: ");
		fflush(stdin);
		gets(title);
		system("cls");
		fread(&info[i], sizeof(info[i]), 1, fptr);
		while (!feof(fptr))
		{
			if (strcmp(title,info[i].book_title)==0)
			{
				found = 1;
				q = i;
			}
			i++;
			fread(&info[i], sizeof(info[i]), 1, fptr);
		}
		fclose(fptr);
		if (found == 1)
		{
			fptr = fopen("Book.bin", "wb");
			for (x = 0; x <= i; x++)
			{
				if (strcmp(title, info[x].book_title) != 0)
					fwrite(&info[x], sizeof(info[x]), 1, fptr);
			}
		printf("\n\t\t\t\tBOOK INFORMATION HAS BEEN SUCCESSFULLY DELETED!\n");
			fclose(fptr);
		}
		else
			printf("\t\t\t\tUNFORTUNATELY, BOOK INFORMATION COULD NOT BE LOCATED\n");
	}
}
void DisplayBooks() {
	BOOK info;
	FILE* fptr = NULL;
	int c=1;
	system("cls");
	if ((fptr = fopen("Book.bin", "rb")) == NULL)
		printf("\t\t\t\tNO BOOKS ARE AVAILABLE AT THIS TIME!\n\n");
	else
	{
		fread(&info, sizeof(info), 1, fptr);
		while (!feof(fptr))
		{
			printf("\n\t\t\t\tThis is Book #%d:\n\t\t\t\tTitle Of Book:%s\n\t\t\t\tAuthor Of Book:%s\n\t\t\t\tCondition Of Book:%s\n\t\t\t\tIsbn #:%d\n\t\t\t\tAccess #:%d\n", c, info.book_title, info.author, info.condition, info.isbn, info.access);
			c++;
			fread(&info, sizeof(info), 1, fptr);
		}
	}
	fclose(fptr);
}

void AddNewMember(){
	MEMBER info,*ptr=NULL;
	ptr=&info;
	int mem_ship;
	FILE* fptr=NULL;
	char ans = 'Y';
	if ((fptr = fopen("Member.txt", "a")) == NULL)
		printf("\t\t\t\tError opening this file\n");
	else
	{
		do
		{
			system("cls");
			printf("\t\t\t\tEnter the following information below:-\n\n");
			printf("\t\t\t\tMembership Type:-\n\n\t\t\t\t1. Ordinary\t\t2. Administrator\n\n");
			printf("\t\t\t\tSelect Membership type: ");
			fflush(stdin);
			scanf("%d", &mem_ship);
			while (mem_ship < 1 || mem_ship >2)
			{
				system("cls");
				printf("\t\t\t\tEnter the following information below:-\n\n");
				printf("\t\t\t\tMembership Type\n\n\t\t\t\t1. Ordinary\t\t2. Administrator\n\n");
				printf("\t\t\t\tSelect Membership type: ");
				fflush(stdin);
				scanf("%d", &mem_ship);
			}
			if (mem_ship == 1)
			{
				strcpy(ptr->mem_type, "Ordinary");
				strcpy(ptr->allowance, "Uniform");
			}
			else
			{
				strcpy(ptr->mem_type, "Administration");
				strcpy(ptr->allowance, "Travel");
			}
			printf("\n\t\t\t\tEnter your First Name: ");
			fflush(stdin);
			fgets(ptr->f_name, sizeof(info.f_name), stdin);
			printf("\n\t\t\t\tEnter your Last Name: ");
			fflush(stdin);
			fgets(ptr->l_name, sizeof(info.l_name), stdin);
			printf("\n\t\t\t\tEnter your Address: ");
			fflush(stdin);
			fgets(ptr->address, sizeof(info.address), stdin);
			printf("\n\t\t\t\tEnter Member ID #(10 digits): ");
			fflush(stdin);
			scanf("%d", &ptr->mem_id);
			printf("\n\t\t\t\tEnter your Date of Birth [DD/MM/YYYY] format: ");
			scanf("%d/%d/%d", &ptr->date.day, &ptr->date.month, &ptr->date.year);
			while ((ptr->date.day < 1 || ptr->date.month>31) || (ptr->date.month < 1 || ptr->date.month>12) || (ptr->date.year > 2019))
			{
				if (ptr->date.day < 1 || ptr->date.day>31)
				{
					printf("Invalid day, day should be atleast 1 and less then 32\n");
					printf("Enter another day\n");
					fflush(stdin);
					scanf("%d", &ptr->date.day);
				}
				if (ptr->date.month < 1 || ptr->date.month>12)
				{
					printf("\t\t\t\tInvalid day, day should be atleast 1 and less then 32\n");
					printf("\t\t\t\tEnter another day:\n");
					fflush(stdin);
					scanf("%d", &ptr->date.month);
				}
				if (ptr->date.year > 2019)
				{
					printf("\t\t\t\tInvalid month, month should be atleast 1 and less than 13\n");
					printf("\t\t\t\tEnter another month:\n");
					fflush(stdin);
					scanf("%d", &ptr->date.year);
				}
			}
			printf("\n\t\t\t\tEnter your Phone #: ");
			fflush(stdin);
			scanf("%d", &ptr->phone_num);
			fprintf(fptr, "%d %s %s %s %s %s %d %d %d %d\n", ptr->mem_id,ptr->address, ptr->allowance, ptr->mem_type, ptr->f_name, ptr->l_name, ptr->phone_num,ptr->date.day, ptr->date.month, ptr->date.year);
			printf("\n\n\t\t\t\tWould you want to add another Member?\n\t\t\t\tSelect Y for Yes or N for No  :  ");
			fflush(stdin);
			scanf("%c", &ans);
			printf("\n\n\t\t\t\tMEMBER INFORMATION HAS BEEN SUCCESSFULLY STORED!\n\n");
		} while (ans != 'n' && ans != 'N');
		fclose(fptr);
	}
}
void UpdateMember() {
	MEMBER info, update,*ptr=NULL;
	ptr=&info;
	int found = 0,mem_ship;
	FILE* fptr = NULL,*fp=NULL;
	system("cls");
	if ((fptr = fopen("Member.txt", "r")) == NULL)
		printf("\t\t\t\tNO MEMEBERS HAS BEEN REGISTERED!\n\n");
	else
	{
		printf("\t\t\t\tEnter Member ID #(10 digits) to search: ");
		fflush(stdin);
		scanf("%d", &update.mem_id);
		while (fscanf(fptr, "%d %s %s %s %s %s %d %d %d %d", &ptr->mem_id, ptr->address, ptr->allowance, ptr->mem_type, ptr->f_name, ptr->l_name, &ptr->phone_num, &ptr->date.day, &ptr->date.month, &ptr->date.year) != EOF)
		{
			if (update.mem_id == info.mem_id)
				found = 1;
		}
		fclose(fptr);
		if (found == 1)
		{
			system("cls");
			printf("\t\t\t\tEnter the following information below:-\n\n");
			printf("\t\t\t\tMembership Type\n\n\t\t\t\t1. Ordinary\t\t2. Administrator\n\n");
			printf("\t\t\t\tSelect Membership type: ");
			fflush(stdin);
			scanf("%d", &mem_ship);
			while (mem_ship < 1 || mem_ship>2)
			{
				system("cls");
				printf("\t\t\t\tEnter the following information below:-\n\n");
				printf("\t\t\t\tMembership Type\n\n\t\t\t\t1. Ordinary\t\t2. Administrator\n\n");
				printf("\t\t\t\tSelect Membership type: ");
				fflush(stdin);
				scanf("%d", &mem_ship);
			}

			if (mem_ship == 1)
			{
				strcpy(update.mem_type, "Ordinary");
				strcpy(update.allowance, "Uniform");
			}
			if (mem_ship == 2)
			{
				strcpy(update.mem_type, "Administration");
				strcpy(update.allowance, "Travel");
			}
			printf("\t\t\t\tEnter your First Name: ");
			fflush(stdin);
			fgets(update.f_name, sizeof(update.f_name), stdin);
			printf("\t\t\t\tEnter your Last Name: ");
			fflush(stdin);
			fgets(update.l_name, sizeof(update.l_name), stdin);
			printf("\t\t\t\tEnter your Address: ");
			fflush(stdin);
			fgets(update.address, sizeof(update.address), stdin);
			printf("\t\t\t\tEnter Member ID #(10 digits): ");
			fflush(stdin);
			scanf("%d", &update.mem_id);
			printf("\n\t\t\t\tEnter your Date of Birth [Day/Month/Year] format: ");
			scanf("%d/%d/%d", &update.date.day, &update.date.month, &update.date.year);
			while ((update.date.day < 1 || update.date.month>31) || (update.date.month < 1 || update.date.month>12) || (update.date.year > 2019))
			{
				if (update.date.day < 1 || update.date.day>31)
				{
					printf("\t\t\t\tInvalid day, day should be atleast 1 and less then 32\n");
					printf("\t\t\t\tEnter another day\n");
					fflush(stdin);
					scanf("%d", &update.date.day);
				}
				if (update.date.month < 1 || update.date.month>12)
				{
					printf("\t\t\t\tInvalid month, month should be atleast 1 and less than 13\n");
					printf("\t\t\t\tEnter another month\n");
					fflush(stdin);
					scanf("%d", &update.date.month);
				}
				if (update.date.year > 2019)
				{
					printf("\t\t\t\tInvalid year, year should be less than 2020\n");
					printf("\t\t\t\tEnter another year\n");
					fflush(stdin);
					scanf("%d", &update.date.year);
				}
			}
			printf("\t\t\t\tEnter your Phone #: ");
			fflush(stdin);
			scanf("%d", &update.phone_num);
			if ((fptr = fopen("Member.txt", "r")) == NULL)
				printf("\t\t\t\tError opening this file\n\n");
			else
			{
				if ((fp = fopen("Temp.txt", "w")) == NULL)
					printf("\t\t\t\tError opening this file\n\n");
				else
				{
					while (fscanf(fptr, "%d %s %s %s %s %s %d %d %d %d", &ptr->mem_id, ptr->address, ptr->allowance, ptr->mem_type, ptr->f_name, ptr->l_name, &ptr->phone_num, &ptr->date.day, &ptr->date.month, &ptr->date.year) != EOF)
					{

						if (update.mem_id == info.mem_id)
							fprintf(fp, "%d %s %s %s %s %s %d %d %d %d\n", update.mem_id, update.address, update.allowance, update.mem_type, update.f_name, update.l_name, update.phone_num, update.date.day, update.date.month, update.date.year);
						else
							fprintf(fp, "%d %s %s %s %s %s %d %d %d %d\n", ptr->mem_id, ptr->address, ptr->allowance, ptr->mem_type, ptr->f_name, ptr->l_name, ptr->phone_num, ptr->date.day, ptr->date.month, ptr->date.year);
					}
				}
			}
			fclose(fptr);
			fclose(fp);
			remove("Member.txt");
			rename("Temp.txt", "Member.txt");
		}
		else
			printf("\t\t\t\tUNFORTUNATELY, MEMEBER WAS NOT LOCATED!\n\n");
	}
}
void DeleteMember()
{
	MEMBER info,*ptr=NULL;
	ptr=&info;
	int mem_id,found=0;
	FILE* fptr = NULL,*fps=NULL;
	 system("cls");
	 if ((fptr = fopen("Member.txt", "r")) == NULL)
		 printf("\t\t\t\tNO MEMBERS REGISTERED AT THE MOMENT!\n\n");
	 else
	 {
		 printf("\t\t\t\tEnter Member ID #(10 digits) to search: ");
		 fflush(stdin);
		 scanf("%d", &mem_id);
		 if ((fps = fopen("Temp.txt", "w")) == NULL)
			 printf("\t\t\t\tError opening this file\n");
		 else
		 {
			 while (fscanf(fptr, "%d %s %s %s %s %s %d %d %d %d", &ptr->mem_id, ptr->address, ptr->allowance, ptr->mem_type, ptr->f_name, ptr->l_name, &ptr->phone_num, &ptr->date.day, &ptr->date.month, &ptr->date.year) != EOF)
			 {
				 if (ptr->mem_id != mem_id)
					 fprintf(fps, "%d %s %s %s %s %s %d %d %d %d\n", ptr->mem_id, ptr->address, ptr->allowance, ptr->mem_type, ptr->f_name, ptr->l_name, ptr->phone_num, ptr->date.day, ptr->date.month, ptr->date.year);
				 else
					found = 1;
			 }
			 fclose(fptr);
			 fclose(fps);
			 remove("Member.txt");
			 rename("Temp.txt", "Member.txt");
		 }
		 if (found != 1)
			 printf("\t\t\t\tMEMBER NOT LOCATED\n");
	 }
}
void AllMember() 
{
	MEMBER info,*ptr=NULL;
	ptr=&info;
	int c=1;
	FILE* fptr = NULL;
	system("cls");
	if ((fptr = fopen("Member.txt", "r")) == NULL)
		printf("\t\t\t\tNO MEMBERS REGISTERED AT THE MOMENT!\n\n");
	else
	{
		while (fscanf(fptr, "%d %s %s %s %s %s %d %d %d %d", &ptr->mem_id, ptr->address, ptr->allowance, ptr->mem_type, ptr->f_name, ptr->l_name, &ptr->phone_num, &ptr->date.day, &ptr->date.month, &ptr->date.year) != EOF)
		{
			printf("\t\t\t\t**** MEMBER %d ****\n", c);
			printf("\t\t\t\tMember ID #: %d", ptr->mem_id);
			printf("\n\t\t\t\tMember Name: %s %s", ptr->f_name, ptr->l_name);
			printf("\n\t\t\t\tMember Address: %s", ptr->address);
			printf("\n\t\t\t\tMember Date of Birth: %d/%d/%d", info.date.day, info.date.month, info.date.year);
			printf("\n\t\t\t\tMember Phone #: %d", ptr->phone_num);
			printf("\n\t\t\t\tMember Type: %s", ptr->mem_type);
			
			printf("\n\t\t\t\tAllowance: %s \n\n\n", ptr->allowance);
			c++;
		}
		fclose(fptr);
	}
}
void DisplayMember() {
	MEMBER info,*ptr=NULL;
	ptr=&info;
	int member_search=0, found = 0,c=1;
	FILE* fptr = NULL;
	system("cls");
	if ((fptr = fopen("Member.txt", "r")) == NULL)
		printf("\t\t\t\tNO MEMBERS REGISTERED AT THE MOMENT!\n\n");
	else
	{
		printf("Enter Member ID #(10 digits) to search: ");
		fflush(stdin);
		scanf("%d", &member_search);
		fflush(stdin);
		while (fscanf(fptr, "%d %s %s %s %s %s %d %d %d %d", &ptr->mem_id, ptr->address, ptr->allowance, ptr->mem_type, ptr->f_name, ptr->l_name, &ptr->phone_num, &ptr->date.day, &ptr->date.month, &ptr->date.year)!=EOF)
		{
			if (member_search == ptr->mem_id)
			{
				found = 1;
				printf("\t\t\t\t**** MEMBER %d ****\n", c);
				printf("\t\t\t\tMember ID #: %d\n", ptr->mem_id);
				printf("\t\t\t\tMember Name: %s %s\n", ptr->f_name, ptr->l_name);
				printf("\t\t\t\tMember Address: %s\n", ptr->address);
				printf("\t\t\t\tMember Date of Birth: %d/%d/%d\n", info.date.day, info.date.month, info.date.year);
				printf("\t\t\t\tMember Phone #: %d\n", ptr->phone_num);
				printf("\t\t\t\tMember Type: %s\n", ptr->mem_type);
				printf("\t\t\t\tAllowance: %s \n\n\n", ptr->allowance);
			}
			else
				c++;
		}
		fclose(fptr);
		if (found != 1)
			printf("\t\t\t\tMEMEBER WAS NOT LOCATED\n");
	}
}
void borrowBook()
{
	BORROW bInfo;
	MEMBER info;
	BOOK bk_Info;
	FILE* fp1 = NULL, * fps = NULL, * fptr = NULL;
	char title[30];
	int found = 0;
	if ((fptr = fopen("Member.txt", "r")) == NULL)
		printf("\t\t\t\tNO REGISTERED MEMBERS AT THE MOMENT!\n\n");
	else
	{
		do {
			printf("\t\t\t\tEnter Member ID #(10 digits) to search: ");
			fflush(stdin);
			scanf("%d", &bInfo.mem_id);
			while (fscanf(fptr, "%d %s %s %s %s %s %d %d %d %d", &info.mem_id, info.address, info.allowance, info.mem_type, info.f_name, info.l_name, &info.phone_num, &info.date.day, &info.date.month, &info.date.year)!=EOF)
			{
				if (bInfo.mem_id == info.mem_id)
					found = 1;
			}
			fclose(fptr);
			if (found == 1)
			{
				if ((fps = fopen("Book.bin", "rb")) == NULL)
					printf("\t\t\t\tNO BOOKS AVAILABLE AT THE MOMENT!\n\n");
				else
				{
					printf("\n\n\t\t\t\tPlease enter the title of the book you would like to borrow(-1 to stop): ");
					fflush(stdin);
					gets(title);
					fread(&bk_Info, sizeof(bk_Info), 1, fps);
					while (!feof(fps))
					{
						if (strcmp(title, bk_Info.book_title) == 0)
						{
							found = 2;
							bInfo.isbn = bk_Info.isbn;
						}
						fread(&bk_Info, sizeof(bk_Info), 1, fps);
					}
					fclose(fps);
					if (found == 2)
					{
						printf("\t\t\t\tEnter borrow date DD/MM/YYYY:\n\t\t\t\t");					
						scanf("%d/%d/%d", &bInfo.borrow.day, &bInfo.borrow.month, &bInfo.borrow.year);
						bInfo.to_return.day = bInfo.borrow.day + 14;
						bInfo.to_return.month = bInfo.borrow.month;
						bInfo.to_return.year = bInfo.borrow.year;
						fp1 = fopen("Borrow.bin", "ab");
						fwrite(&bInfo, sizeof(bInfo), 1, fp1);
					}
					fclose(fp1);
				}
			}
		} while (bInfo.mem_id != -1);
	}
}
void displayBorrow(){
	BORROW info;
	FILE* fptr = NULL;
	system("cls");
	if ((fptr = fopen("Borrow.bin", "rb")) == NULL)
		printf("\t\t\t\tNO BOOKS ARE CURRENTLY AVAILABLE!\n\n");
	else
	{
		fread(&info, sizeof(info), 1, fptr);
		while (!feof(fptr))
		{
			printf("\n\t\t\t\tMember ID #(10 digits): %d:\n\t\t\t\tIsbn #:\t%d\n\t\t\t\tBorrow Date:\t%d/%d/%d\n\t\t\t\tReturn Date:\t%d/%d/%d\n", info.mem_id, info.isbn, info.borrow.day,info.borrow.month,info.borrow.year, info.to_return.day, info.to_return.month,info.to_return.year);
			fread(&info, sizeof(info), 1, fptr);
		}
		fclose(fptr);
	}
}
void returnBook(){
	input userSearch;
	BORROW info[Maxbook];
	LATE record;
	int found = 1, i = 0,index=0,x=0;
	FILE* fptr = NULL;
	system("cls");
	if ((fptr = fopen("Borrow.bin", "rb")) == NULL)
		printf("\t\t\t\tNO MEMBER HAS BEEN REGISTERED!\n\n");
	else
	{
		printf("\t\t\t\tEnter Member ID #(10 digits) to search: ");
		fflush(stdin);
		scanf("%d", &userSearch.search);
		fread(&info[i], sizeof(info[i]), 1, fptr);
		while (!feof(fptr))
		{
			if (info[i].mem_id == userSearch.search)
			{
				index = i;
				found = 1;
			}
			i++;
			fread(&info[i], sizeof(info[i]), 1, fptr);
		}
		fclose(fptr);
		if (found == 1)
		{
			printf("\t\t\t\tEnter the date the  book was returned (DD/MM/YYYY): ");
			scanf("%d/%d/%d", &record.returned.day, &record.returned.month, &record.returned.year);
			fptr = fopen("Borrow.bin", "wb");
			for (x = 0; x <= i; x++)
			{
				if (info[x].mem_id != userSearch.search)
					fwrite(&info[x], sizeof(info[x]), 1, fptr);
			}
			fclose(fptr);
			record.mem_id = info[index].mem_id;
			record.isbn = info[index].isbn;
			if (record.returned.day > info[index].to_return.day)
			{
				record.l_charge = (record.returned.day-info[index].to_return.day) * 50;
				if ((fptr = fopen("LateCharges.bin", "ab")) == NULL)
					printf("Error opening file\n");
				else
				{
					fwrite(&record, sizeof(record), 1, fptr);
					fclose(fptr);
				}
			}
		}
	}
}
void checkCharges()
{
	input userSearch;
	LATE info;
	FILE* fptr = NULL;
	int found=0;
	float total = 0;
	system("cls");
	if ((fptr = fopen("LateCharges.bin", "rb")) == NULL)
		printf("\t\t\t\tNO MEMBER HAS BEEN REGISTERED!\n\n");
	else
	{
		printf("\t\t\t\tEnter Member ID #(10 digits) to search: ");
		fflush(stdin);
		scanf("%d", &userSearch.search);
		fread(&info, sizeof(info), 1, fptr);
		while (!feof(fptr))
		{
			if (info.mem_id == userSearch.search)
			{
				total += info.l_charge;
				found = 1;
			}
			fread(&info, sizeof(info), 1, fptr);
		}
		fclose(fptr);
		if (found == 0)
				printf("\t\t\t\tMember has not been located\n");
		else
			printf("\n\t\t\t\tTotal charge: %.2f", total);
	}
}
void displayCharges()
{
	LATE info;
	FILE* fptr = NULL;
	system("cls");
	if ((fptr = fopen("LateCharges.bin", "rb")) == NULL)
		printf("NO MEMBER HAS BEEN REGISTERED!\n\n");
	else
	{
		fread(&info, sizeof(info), 1, fptr);
		while (!feof(fptr))
		{
			printf("\n\t\t\t\tMember ID #(10 digits): %d", info.mem_id);
			printf("\n\t\t\t\tBook ISBN #: %d", info.isbn);
			printf("\n\t\t\t\tLate charge: %.2f", info.l_charge);
			printf("\n\t\t\t\tReturn Date: %d/%d/%d\n\n", info.returned.day, info.returned.month, info.returned.year);
			fread(&info, sizeof(info), 1, fptr);
		}
		fclose(fptr);
	}
}
void makePayment()
{
	input userSearch;
	LATE info;
	FILE* fptr = NULL,*fps=NULL;
	int found=0;
	float total = 0,payment=0;
	system("cls");
	if ((fptr = fopen("LateCharges.bin", "rb")) == NULL)
		printf("\t\t\t\tNO MEMBER HAS BEEN REGISTERED!\n\n");
	else
	{
		printf("\t\t\t\tEnter Member ID #(10 digits) to search: ");
		fflush(stdin);
		scanf("%d", &userSearch.search);
		fread(&info, sizeof(info), 1, fptr);
		while (!feof(fptr))
		{
			if (info.mem_id == userSearch.search)
			{
				total += info.l_charge;
				found = 1;
				printf("\n\t\t\t\tMember ID #(10 digits): %d", info.mem_id);
				printf("\n\t\t\t\tBook ISBN #: %d", info.isbn);
				printf("\n\t\t\t\tLate charge: %.2f", info.l_charge);
				printf("\n\t\t\t\tReturn Date: %d/%d/%d\n\n", info.returned.day, info.returned.month, info.returned.year);
			}
			fread(&info, sizeof(info), 1, fptr);
		}
		system("pause");
		system("cls");
		if (found == 1)
		{
			printf("\t\t\t\tEnter payment amount: ");
			scanf("%f", &payment);
			if (payment <= total)
			{
				fseek(fptr, 0 * sizeof(info), SEEK_SET);
				fps = fopen("Temp.bin", "wb");
				fread(&info, sizeof(info), 1, fptr);
				if (total == payment)
				{
					while (!feof(fptr))
					{
						if (info.mem_id != userSearch.search)
							fwrite(&info, sizeof(info), 1, fps);
						fread(&info, sizeof(info), 1, fptr);
					}
				}
				else
				{
					while (!feof(fptr))
					{
						if (info.mem_id == userSearch.search)
						{
							if (payment < info.l_charge)
								fwrite(&info, sizeof(info), 1, fps);
							else
								payment -= info.l_charge;
						}
						else
							fwrite(&info, sizeof(info), 1, fps);
						fread(&info, sizeof(info), 1, fptr);
					}
				}
				fclose(fptr);
				fclose(fps);
				remove("LateCharges.bin");
				rename("Temp.bin", "LateCharges.bin");
			}
		}
	}
}
