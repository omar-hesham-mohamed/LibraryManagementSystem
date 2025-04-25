#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int month;
    int year;
} date;

typedef struct
{
    char ISBN[100];
    char title[100];
    char aname[100];
    int quantity;
    float price;
    date pdate;
} book;

char name[100], pass[100];
book books[100];
int bc;

int NumValid(char test[50])
{
    int i=0;
    while(test[i]!='\0')
    {
        if (test[i]>'9')
            return 0;
        i++;
    }
    return 1;
}

int start()
{
    int entry;
    char test[50];
    printf("Enter 1 to Login or 0 to Quit: ");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error, invalid entry\n");
        printf("Enter 1 to Login or 0 to Quit: ");
        gets(test);
    }
    entry= atoi(test);
    while(entry!=1 && entry!=0)
    {
        printf("Error invalid option chosen\n");
        printf("Please try again\n\n");
        printf("Enter 1 to Login or 0 to Quit: ");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error, invalid entry\n");
            printf("Enter 1 to Login or 0 to Quit: ");
            gets(test);
        }
        entry= atoi(test);

    }
    return entry;
}

void menu()
{
    int i;
    char test[50];
    printf("Choose from the following:\n");
    printf("1-ADD\n2-DELETE\n3-MODIFY\n4-SEARCH\n5-ADVANCED SEARCH\n6-PRINT\n7-SAVE\n8-QUIT\n9-OTHERWISE REPEAT(LOGIN OR QUIT)\n");
    getchar();
    gets(test);
    while(!NumValid(test))
    {
        printf("Error, invalid entry\n");
        printf("Choose from the following:\n");
        printf("1-ADD\n2-DELETE\n3-MODIFY\n4-SEARCH\n5-ADVANCED SEARCH\n6-PRINT\n7-SAVE\n8-QUIT\n9-OTHERWISE REPEAT(LOGIN OR QUIT)\n");
        gets(test);
    }
    i=atoi(test);
    switch(i)
    {
    case 1:
        add();
        break;
    case 2:
        deletes();
        break;
    case 3:
        modify();
        break;
    case 4:
        search();
        break;
    case 5:
        advsearch();
        break;
    case 6:
        sort();
        break;
    case 7:
        save();
        break;
    case 8:
        quit();
        break;
    case 9:
        main();
        break;
    default:
        printf("Error, Choose a valid option\n");
        menu();
    }

}

void printbook(int i)
{
    char m[20];
    switch (books[i].pdate.month)
    {
    case 1:
        strcpy(m,"January");
        break;
    case 2:
        strcpy(m,"February");
        break;
    case 3:
        strcpy(m,"March");
        break;
    case 4:
        strcpy(m,"April");
        break;
    case 5:
        strcpy(m,"May");
        break;
    case 6:
        strcpy(m,"June");
        break;
    case 7:
        strcpy(m,"July");
        break;
    case 8:
        strcpy(m,"August");
        break;
    case 9:
        strcpy(m,"September");
        break;
    case 10:
        strcpy(m,"October");
        break;
    case 11:
        strcpy(m,"November");
        break;
    case 12:
        strcpy(m,"December");
        break;
    }
    printf("ISBN: %s\n", books[i].ISBN);
    printf("Title: %s\n", books[i].title);
    printf("Author: %s\n", books[i].aname);
    printf("Quantity: %d\n", books[i].quantity);
    printf("Price: %.2f$\n", books[i].price);
    printf("Published: %s %d\n", m, books[i].pdate.year);
    printf("\n");
}

void bookcount()
{
    int count=0;
    FILE* f=fopen("books.txt","r");
    char c;
    for (c=getc(f); c!= EOF ; c=getc(f))
        if (c=='\n')
            count++;
    fclose(f);
    bc=count;
}

int ISBNvalid(char ISBN[100])
{
    if (strlen(ISBN)!=13)
    {
        printf("Invalid ISBN, enter a 13 digit ISBN:");
        return 0;
    }
    for (int p=0; p<13; p++)
        if (ISBN[p]>'9')
        {
            printf("Error, enter an ISBN without characters:");
            return 0;
        }
    return 1;
}

int Anamvalid (char aname[100])
{
    int i, n=strlen(aname);
    for(i=0; i<n; i++)
        if (!('a'<=aname[i] && aname[i]<='z') && !('A'<=aname[i] && aname[i]<='Z') && aname[i]!=' ' && aname[i]!=',' && aname[i]!='.' && aname[i]!='-' && aname[i]!='_')
        {
            printf("Error, No numbers in author's name\n");
            return 0;
        }
    return 1;
}

void add()
{
    int i=bc;
    char test[50];
    printf("Enter the ISBN: ");
    scanf("%s", books[i].ISBN);
    while (!ISBNvalid(books[i].ISBN))
        scanf("%s", books[i].ISBN);
    printf("Enter The Title: ");
    getchar();
    gets(books[i].title);
    printf("Enter The Author Name: ");
    gets(books[i].aname);
    while (!Anamvalid(books[i].aname))
    {
        printf("Enter The Author Name: ");
        gets(books[i].aname);
    }
    printf("Enter The Quantity: ");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error, enter a number\n");
        gets(test);
    }
    books[i].quantity= atoi(test);
    printf("Enter the price: ");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error, enter a number\n");
        gets(test);
    }
    books[i].price=atof(test);
    printf("Enter the month: ");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error, enter the month in numbers:\n");
        gets(test);
    }
    books[i].pdate.month= atoi(test);
    while(books[i].pdate.month>12 || books[i].pdate.month<1)
    {
        printf("Enter a valid number of month:");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error, enter the month in numbers:\n");
            gets(test);
        }
        books[i].pdate.month=atoi(test);
    }
    printf("Enter the year: ");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error enter a number\n");
        gets(test);
    }
    books[i].pdate.year= atoi(test);
    while(books[i].pdate.year>2022 || books[i].pdate.year<0)
    {
        printf("Enter a valid year:");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error enter a number\n");
            gets(test);
        }
        books[i].pdate.year=atoi(test);
    }
    bc=bc+1;
    int flag;
    printf("If you want to add another book press 1\nTo return to the menu press 2\n");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error invalid entry\n");
        gets(test);
    }
    flag= atoi(test);
    while(flag!=1 && flag!=2)
    {
        printf("Error invalid entry\n");
        printf("If you want to add another book press 1\nTo return to the menu press 2\n");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error invalid entry\n");
            printf("If you want to add another book press 1\nTo return to the menu press 2\n");
            gets(test);
        }
        flag=atoi(test);
    }
    if (flag==1)
        add();
    else
        {
            printf("Enter 1 for menu\n");
            getchar();
            menu();
        }
}

void deletes()
{
    int i=bc;
    char ISBNcheck[100];
    printf("Enter ISBN of the book you want to delete: ");
    scanf("%s", ISBNcheck);
    while (!ISBNvalid(ISBNcheck))
        scanf("%s", ISBNcheck);
    int y;
    int n;
    for(y=0; y<i; y++)
    {
        if(!(strcmp(ISBNcheck,books[y].ISBN)))
        {
            for(n=y; n<i; n++)
            {
                strcpy(books[n].ISBN,books[n+1].ISBN);
                strcpy(books[n].title,books[n+1].title);
                strcpy(books[n].aname,books[n+1].aname);
                books[n].quantity=books[n+1].quantity;
                books[n].price=books[n+1].price;
                books[n].pdate.month=books[n+1].pdate.month;
                books[n].pdate.year=books[n+1].pdate.year;
            }
            break;
        }

    }
    if (y==i)
        printf("ISBN not found.\n");
    else
    {
        printf("Book have been deleted successfully\n");
        bc=bc-1;
    }
    char test[50];
    int flag;
    printf("If you want to delete another book press 1\nTo return to the menu press 2\n");
    getchar();
    gets(test);
    while(!NumValid(test))
    {
        printf("Error invalid entry\n");
        gets(test);
    }
    flag= atoi(test);
    while(flag!=1 && flag!=2)
    {
        printf("Error invalid entry\n");
        printf("If you want to delete another book press 1\nTo return to the menu press 2\n");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error invalid entry\n");
            printf("If you want to delete another book press 1\nTo return to the menu press 2\n");
            gets(test);
        }
        flag=atoi(test);
    }
    if (flag==1)
        deletes();
    else
        {
            printf("Enter 1 for menu\n");
            getchar();
            menu();
        }


}

void modify()
{
    char ISBNcheck[100];
    char test[50];
    printf("Enter ISBN of the book you want to modify: ");
    scanf("%s", ISBNcheck);
    while (!ISBNvalid(ISBNcheck))
        scanf("%s", ISBNcheck);
    int y, n, found=0;
    for(y=0; y<bc; y++)
    {
        if(!(strcmp(ISBNcheck,books[y].ISBN)))
        {
            printf("Enter the modified ISBN:");
            scanf("%s", books[y].ISBN);
            while (!ISBNvalid(books[y].ISBN))
                scanf("%s", books[y].ISBN);
            printf("Enter the modified title:");
            getchar();
            gets(books[y].title);
            printf("Enter the modified authors's name:");
            gets(books[y].aname);
            while (!Anamvalid(books[y].aname))
            {
                printf("Enter the modified authors's name:");
                gets(books[y].aname);
            }
            printf("Enter the modified quantity:");
            gets(test);
            while(!NumValid(test))
            {
                printf("Error enter a number\n");
                gets(test);
            }
            books[y].quantity= atoi(test);
            printf("Enter the modified price:");
            gets(test);
            while(!NumValid(test))
            {
                printf("Error enter a number\n");
                gets(test);
            }
            books[y].price=atof(test);
            printf("Enter the modified number of the published month:");
            gets(test);
            while(!NumValid(test))
            {
                printf("Error enter a number\n");
                gets(test);
            }
            books[y].pdate.month= atoi(test);
            while(books[y].pdate.month>12 || books[y].pdate.month<1)
            {
                printf("Enter a valid number of month:");
                gets(test);
                while(!NumValid(test))
                {
                    printf("Error enter a number\n");
                    gets(test);
                }
                books[y].pdate.month= atoi(test);
            }
            printf("Enter the modified number of the published year:");
            gets(test);
            while(!NumValid(test))
            {
                printf("Error enter a number\n");
                gets(test);
            }
            books[y].pdate.year= atoi(test);
            while(books[y].pdate.year>2022 || books[y].pdate.year<0)
            {
                printf("Enter a valid year:");
                gets(test);
                while(!NumValid(test))
                {
                    printf("Error enter a number\n");
                    gets(test);
                }
                books[y].pdate.year=atoi(test);
            }
            found=1;
        }
    }
    if (!found)
    {
        printf("ISBN not found\n");
        getchar();
    }
    else printf("Books with this ISBN have been modified successfully\n");
    int flag;
    printf("If you want to modify another book press 1\nTo return to the menu press 2\n");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error invalid entry\n");
        gets(test);
    }
    flag=atoi(test);
    while(flag!=1 && flag!=2)
    {
        printf("Error invalid entry\n");
        printf("If you want to modify another book press 1\nTo return to the menu press 2\n");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error invalid entry\n");
            printf("If you want to modify another book press 1\nTo return to the menu press 2\n");
            gets(test);
        }
        flag=atoi(test);
    }
    if (flag==1)
        modify();
    else
        {
            printf("Enter 1 for menu\n");
            getchar();
            menu();
        }
}

void search()
{
    char key[100];
    printf("Enter ISBN:");
    scanf("%s", key);
    while (!ISBNvalid( key))
        scanf("%s", key);
    int flag=0,i;
    for (i=0; i<100; i++)
        if (!strcmp(key,books[i].ISBN))
        {
            flag=1;
            break;
        }
    if (flag)
    {
        printf("\n");
        printbook(i);
        getchar();
    }
    else
    {
        printf("\n");
        printf("Book not found\n");
        getchar();
    }
    int flag2;
    char test[50];
    printf("If you want to search for another key enter 1\nTo return to the menu enter 2\n");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error invalid entry\n");
        gets(test);
    }
    flag2=atoi(test);
    while(flag2!=1 && flag2!=2)
    {
        printf("Error invalid entry\n");
        printf("If you want to search for another key enter 1\nTo return to the menu enter 2\n");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error invalid entry\n");
            printf("If you want to search for another key enter 1\nTo return to the menu enter 2\n");
            gets(test);
        }
        flag2=atoi(test);
    }
    if (flag2==1)
        search();
    else
        {
            printf("Enter 1 for menu\n");
            getchar();
            menu();
        }
}

void advsearch()
{
    char key[100];
    printf("Enter keyword:");
    scanf("%s", key);
    int i, flag=0;
    for (i=0; i<100; i++)
        if (strstr(books[i].title,key)!=NULL)
        {
            printf("\n");
            printbook(i);
            flag=1;
        }
    if (97<=key[0]<=122)
        key[0]=key[0]-32;
    else if (65<=key[0]<=90)
        key[0]=key[0]+32;
    for (i=0; i<100; i++)
        if (strstr(books[i].title,key)!=NULL)
        {
            printf("\n");
            printbook(i);
            flag=1;
        }
    if (!flag)
    {
        printf("\n");
        printf("No books found with this key\n");
    }
    int flag2;
    char test[50];
    printf("If you want to search with another key press 1\nTo return to the menu press 2\n");
    getchar();
    gets(test);
    while(!NumValid(test))
    {
        printf("Error invalid entry\n");
        gets(test);
    }
    flag2=atoi(test);
    while(flag2!=1 && flag2!=2)
    {
        printf("Error invalid entry\n");
        printf("If you want to search for another key enter 1\nTo return to the menu enter 2\n");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error invalid entry\n");
            printf("If you want to search for another key enter 1\nTo return to the menu enter 2\n");
            gets(test);
        }
        flag2=atoi(test);
    }
    if (flag2==1)
        advsearch();
    else
        {
            printf("Enter 1 for menu\n");
            getchar();
            menu();
        }
}

void sort()
{
    int x;
    book temp;
    char test[50];
    printf("To print books sorted by price from smallest to largest enter 1\nTo print books sorted by title name alphabetically enter 2\nTo print books sorted by date from newest to oldest enter 3\n");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error, invalid entry\n");
        printf("Choose from the following:\n");
        printf("To print books sorted by price from smallest to largest enter 1\nTo print books sorted by title name alphabetically enter 2\nTo print books sorted by date from newest to oldest enter 3\n");
        gets(test);
    }
    x=atoi(test);
    int pass,i;
    switch (x)
    {
    case 1:

        for (pass=1; pass<bc; pass++)
            for (i=0; i<bc-pass; i++)
                if(books[i].price>books[i+1].price)
                {
                    temp=books[i];
                    books[i]=books[i+1];
                    books[i+1]=temp;
                }
        break;
    case 2:
        for (pass=1; pass<bc; pass++)
            for (i=0; i<bc-pass; i++)
                if(strcmp(books[i].title,books[i+1].title)>0)
                {
                    temp=books[i];
                    books[i]=books[i+1];
                    books[i+1]=temp;
                }

        break;
    case 3:
        for (pass=1; pass<bc; pass++)
            for (i=0; i<bc-pass; i++)
            {
                if(books[i].pdate.year<books[i+1].pdate.year)
                {
                    temp=books[i];
                    books[i]=books[i+1];
                    books[i+1]=temp;
                }
                else if (books[i].pdate.year==books[i+1].pdate.year)
                    if (books[i].pdate.month<books[i+1].pdate.month)
                    {
                        temp=books[i];
                        books[i]=books[i+1];
                        books[i+1]=temp;
                    }
            }
        break;
    default:
        printf("Error please enter a valid choice\n");
        sort();
    }
    printf("\n");
    for (int i=0; i<bc; i++)
        printbook(i);
    int flag2;
    printf("To return to menu enter 0, to print again enter 1:");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error invalid entry\n");
        gets(test);
    }
    flag2=atoi(test);
    while(flag2!=0 && flag2!=1)
    {
        printf("Error invalid entry\n");
        printf("To return to menu enter 0, to print again enter 1:");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error invalid entry\n");
            printf("To return to menu enter 0, to print again enter 1:");
            gets(test);
        }
        flag2=atoi(test);
    }
    if (flag2)
        sort();
    else
        {
            printf("Enter 1 for menu\n");
            getchar();
            menu();
        }
}

void save()
{
    int y;
    FILE *f2=fopen("books.txt","w");
        for(y=0; y<bc; y++)
        {
            fprintf(f2,"%s,",books[y].ISBN);
            fputs(books[y].title,f2);
            putc(',',f2);
            fputs(books[y].aname,f2);
            putc(',',f2);
            fprintf(f2,"%d,",books[y].quantity);
            fprintf(f2,"%.2f,",books[y].price);
            fprintf(f2,"%d-",books[y].pdate.month);
            fprintf(f2,"%d",books[y].pdate.year);
            fprintf(f2,"\n");
        }
    printf("File updated successfully.\n");
    menu();
}

int login()
{
    printf("Enter Username\n");
    scanf("%s", name);
    printf("Enter Password\n");
    scanf("%s", pass);
    int flag= load(1);
    return flag;
}

int load( int flag2)
{
    if(flag2)
    {
        char namecheck[100], passcheck[100];
        FILE* f1=fopen("credentials.txt","r");
        if(f1==NULL)
        {
            printf("Credentials file not found\n");
            exit(1);
        }
        else
        {
            int flag1=0;
            while(!feof(f1))
            {
                fscanf(f1,"%s %s", namecheck, passcheck);
                if (!(strcmp(name,namecheck)) && !(strcmp(pass,passcheck)))
                {
                    flag1=1;
                    break;
                }
            }
            fclose(f1);
            return flag1;
        }
    }
    else
    {
        FILE* f2=fopen("books.txt","r");
        if(f2==NULL)
        {
            printf("Books file not found\n");
            exit(1);
        }
        else
        {
            char hold[300];
            char c[]=",", d[]="-", e[]="\n";
            int i, m=bc;
            for (i=0; i<m; i++)
            {
                fgets(hold,300,f2);
                char* token=strtok(hold,c);
                strcpy(books[i].ISBN,token);
                token=strtok(NULL,c);
                strcpy(books[i].title,token);
                token=strtok(NULL,c);
                strcpy(books[i].aname,token);
                token=strtok(NULL,c);
                books[i].quantity=atoi(token);
                token=strtok(NULL,c);
                books[i].price=atof(token);
                token=strtok(NULL,d);
                books[i].pdate.month=atoi(token);
                token=strtok(NULL,e);
                books[i].pdate.year=atoi(token);
            }
            fclose(f2);
            return 1;
        }
    }
}

void quit()
{
    int x, sure;
    char test[50];
    printf("Enter 0 to quit, enter 1 to return to menu\n");
    gets(test);
    while(!NumValid(test))
    {
        printf("Error enter a number\n");
        gets(test);
    }
    x=atoi(test);
    while (x!=0 && x!=1)
    {
        printf("Invalid entry, enter 0 to quit, enter 1 to return to menu\n");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error enter a number\n");
            gets(test);
        }
        x=atoi(test);
    }
    if (x)
            {
                printf("Enter 1 for menu\n");
                getchar();
                menu();
            }
    else
    {
        printf("Are you sure you want to quit ? All unsaved data will be lost!\n");
        printf("Enter 0 to quit, enter 1 to return to menu\n");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error enter a number\n");
            gets(test);
        }
        sure=atoi(test);
        while (sure!=0 && sure!=1)
        {
        printf("Invalid entry, enter 0 to quit, enter 1 to return to menu\n");
        gets(test);
        while(!NumValid(test))
        {
            printf("Error enter a number\n");
            gets(test);
        }
        sure= atoi(test);
        }
        if(!sure)
        {
            printf("Good Bye!\n");
            return;
        }
        else
            {
                printf("Enter 1 for menu\n");
                getchar();
                menu();
            }
    }
}

int main()
{
    int entry=start();
    if(entry)
    {
        bookcount();
        while (!login())
            printf("Error invalid username and password\n");
        if(load(0))
            printf("Files loaded successfully\n");
        menu();
    }
    else
    {
        printf("Good Bye");
    }
    return 0;
}
