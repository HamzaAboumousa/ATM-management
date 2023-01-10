#include "system.c"

void mainMenu(struct User u)
{   
    int option;
    system("clear");
    menu :
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        // student TODO : add your **Update account information** function
        // here
        update(u);
        break;
    case 3:
        // student TODO : add your **Check the details of existing accounts** function
        // here
        int account;
        printf("give the account number : ");
        scanf("%i", &account);
        checkAccount(u, account);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // student TODO : add your **Make transaction** function
        // here
        maketransaction(u);
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        // here
        removeaccount(u);
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        transferowner(u);
        break;
    case 8:
        exit(1);
        break;
    default:
        system("clear");
        printf("Invalid operation!\n");
        goto menu;
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("\n\nPassword Match!");
            }
            else
            {   
                printf("\nWrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            // student TODO : add your **Registration** function
            // here
            registerMenu(u->name, u->password);

                  FILE *fp;
                fp = fopen("../data/users.txt", "a+");
                if (fp == NULL)
                {
                    printf("Error! opening file");
                    exit(1);
                }
                int newid;
                char a[100];
                char b[100];
            while (fscanf(fp, "%d %s %s",&newid, a, b) != EOF)
            {  
                continue;
            }
            fp = fopen("../data/users.txt", "a+");
            if (fp == NULL)
                {
                    printf("Error! opening file");
                    exit(1);
                }
            fprintf(fp, "%d %s %s \n",newid+1,u->name, u->password);
                fclose(fp);
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
        }
    }
};

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
