#include "auth.c"
#include <time.h>

#define BUFFER_SIZE 1000

const char *RECORDS = "../data/records.txt";

bool removeaccountfromfile(const char* filename, struct Record rec) {
    // Ouvrir le fichier en lecture et en écriture
  FILE* file = fopen(filename, "r");
  FILE* tmp = fopen("temp.txt","w");
  struct Record r;
  if (file == NULL || tmp == NULL) {
    fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", filename);
    return FALSE;
  }

    while (fscanf(file, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %lf %s",
                &r.id,
		        &r.userId,
		        r.name,
                &r.accountNbr,
                &r.deposit.month,
                &r.deposit.day,
                &r.deposit.year,
                &r.deposit.heure,
                &r.deposit.min,
                &r.deposit.sec,
                r.country,
                r.phone,
                &r.amount,
                r.accountType) != EOF){
                    if (rec.id != r.id){
                        fprintf(tmp,"%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %.2lf %s\n\n", r.id,
		        r.userId,
		        r.name,
                r.accountNbr,
                r.deposit.month,
                r.deposit.day,
                r.deposit.year,
                r.deposit.heure,
                   r.deposit.min,
                   r.deposit.sec,
                r.country,
                r.phone,
                r.amount,
                r.accountType);
                    }
                }
  fclose(file);
  fclose(tmp);
  remove(filename);
  rename("temp.txt",filename);

  return TRUE;
}
bool replace_line(const char* filename, struct Record rec) {
  // Ouvrir le fichier en lecture et en écriture
  FILE* file = fopen(filename, "r");
  FILE* tmp = fopen("temp.txt","w");
  struct Record r;
  if (file == NULL || tmp == NULL) {
    fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", filename);
    return FALSE;
  }

    while (fscanf(file, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %lf %s",
                &r.id,
		        &r.userId,
		        r.name,
                &r.accountNbr,
                &r.deposit.month,
                &r.deposit.day,
                &r.deposit.year,
                &r.deposit.heure,
                &r.deposit.min,
                &r.deposit.sec,
                r.country,
                r.phone,
                &r.amount,
                r.accountType) != EOF){
                    if (rec.id != r.id){
                        fprintf(tmp,"%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %.2lf %s\n\n", r.id,
		        r.userId,
		        r.name,
                r.accountNbr,
                r.deposit.month,
                r.deposit.day,
                r.deposit.year,
                r.deposit.heure,
                   r.deposit.min,
                   r.deposit.sec,
                r.country,
                r.phone,
                r.amount,
                r.accountType);
                    } else {
                        fprintf(tmp,"%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %.2lf %s\n\n", rec.id,
		        rec.userId,
		        rec.name,
                rec.accountNbr,
                rec.deposit.month,
                rec.deposit.day,
                rec.deposit.year,
                rec.deposit.heure,
                   rec.deposit.min,
                   rec.deposit.sec,
                rec.country,
                rec.phone,
                rec.amount,
                rec.accountType);
                    }
                }
  fclose(file);
  fclose(tmp);
  remove(filename);
  rename("temp.txt",filename);

  return TRUE;
}


int getAccountFromFile(FILE *ptr, char name[50], struct Record *r) {
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %lf %s\n",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                &r->deposit.heure,
                &r->deposit.min,
                &r->deposit.sec,
                  r->country,
                  r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %.2lf %s\n\n",
            r.id,
	    r.userId,
	    u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.deposit.heure,
                r.deposit.min,
                r.deposit.sec,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    FILE *fp, *ptr;
    ptr = fopen("../data/records.txt", "rw");
    if (ptr == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    fp = fopen("../data/users.txt", "rw");
    if (fp == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    /////////////////////////
    int newid;
    char a[100];
    char b[100];
    while (fscanf(ptr, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %lf %s",
                &r.id,
		        &r.userId,
		        r.name,
                &r.accountNbr,
                &r.deposit.month,
                &r.deposit.day,
                &r.deposit.year,
                &r.deposit.heure,
                &r.deposit.min,
                &r.deposit.sec,
                r.country,
                r.phone,
                &r.amount,
                r.accountType) != EOF)
    {  
        continue;
    }
    r.id++;

    while (fscanf(fp, "%d %s %s",&newid, a, b) != EOF)
    {      
        if(strcmp(a,u.name) == 0){
        break;
    }
    }
    r.userId = newid; 
/////////////////////////
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

    system("clear");
    printf("\t\t\t===== New record =====\n");
    noAccount :
    printf("\nDate(mm/dd/yyyy):");
    time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf(" %d-%02d-%02d %02d:%02d:%02d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    r.deposit.year = tm.tm_year + 1900;
    r.deposit.month = tm.tm_mon + 1;
    r.deposit.day = tm.tm_mday;
    r.deposit.heure = tm.tm_hour;
    r.deposit.min = tm.tm_min;
    r.deposit.sec = tm.tm_sec;

    printf("\nEnter the account number:");
    r.accountNbr = -1;
    while (r.accountNbr<0){
        scanf("%d", &r.accountNbr);
    }
    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {   
            system("clear");
            printf("✖ This Account already exists for you \n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%s", r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    choix :
    printf("\nChoose the type of account:\n\n-> [1]saving\n\n-> [2]current\n\n-> [3]fixed01(for 1 year)\n\n-> [4]fixed02(for 2 years)\n\n-> [5]fixed03(for 3 years)\n\n\tEnter your choice:");
    int choix;
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        strcpy(r.accountType,"saving");
        break;
    case 2:
        strcpy(r.accountType,"current");
        break;
    case 3:
        strcpy(r.accountType,"fixed01");
        break;
    case 4:
        strcpy(r.accountType,"fixed02");
        break;
    case 5:
        strcpy(r.accountType,"fixed03");
        break;
    
    default:
    printf("Insert a valid operation!\n");
        goto choix;
        break;
    }
    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d %02d:%02d:%02d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.deposit.heure,
                   r.deposit.min,
                   r.deposit.sec,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
            if (strcmp(r.accountType,"saving") == 0){
                printf("Interest rate %lf every %d in the mounth\n", 0.07*r.amount,r.deposit.day);
            }
            if (strcmp(r.accountType,"fixed01") == 0){
                printf("Interest rate %lf at %d/%d/%d\n",0.04*r.amount,r.deposit.day, r.deposit.month, r.deposit.year+1);
            }
            if (strcmp(r.accountType,"fixed02") == 0){
                printf("Interest rate %lf at %d/%d/%d\n",0.05*r.amount,r.deposit.day, r.deposit.month, r.deposit.year+2);
            }
            if (strcmp(r.accountType,"fixed03") == 0){
                printf("Interest rate %lf at %d/%d/%d\n",0.08*r.amount,r.deposit.day, r.deposit.month, r.deposit.year+3);
            }
            if (strcmp(r.accountType,"current") == 0){
                printf("You will not get interests because the account is of type current.\n");
            }
        }
    }
    fclose(pf);
    success(u);
}

void checkAccount(struct User u, int account){
        char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== Account %i from user, %s =====\n\n",account ,u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if ((strcmp(userName, u.name) == 0) && (r.accountNbr == account))
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d %02d:%02d:%02d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.deposit.heure,
                   r.deposit.min,
                   r.deposit.sec,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
            if (strcmp(r.accountType,"saving") == 0){
                printf("Interest rate %lf every %d in the mounth\n", 0.07*r.amount,r.deposit.day);
            }
            if (strcmp(r.accountType,"fixed01") == 0){
                printf("Interest rate %lf at %d/%d/%d\n",0.04*r.amount,r.deposit.day, r.deposit.month, r.deposit.year+1);
            }
            if (strcmp(r.accountType,"fixed02") == 0){
                printf("Interest rate %lf at %d/%d/%d\n",0.05*r.amount,r.deposit.day, r.deposit.month, r.deposit.year+2);
            }
            if (strcmp(r.accountType,"fixed03") == 0){
                printf("Interest rate %lf at %d/%d/%d\n",0.08*r.amount,r.deposit.day, r.deposit.month, r.deposit.year+3);
            }
            if (strcmp(r.accountType,"current") == 0){
                printf("You will not get interests because the account is of type current.\n");
            }
        }
    }
    fclose(pf);
    success(u);
}

void registerMenu(char a[50], char pass[50]){
    struct termios oflags, nflags;

    system("clear");
redone:
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);
    if (strcmp(a, getuser(a)) == 0)
            {
                printf("\n\nName Match!");
                goto redone; 
            }
    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password:"); 
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
}

void update(struct User u){
    struct Record r;
    bool found = FALSE;
    int cnbr;
    int option;
    FILE *ptr;
    ptr = fopen("../data/records.txt", "rw");
    if (ptr == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    system("clear");
    acountnbr :
    printf("\t\t\t===== Update acount =====\n");
    printf("\n\t\t-->> Enter the acount number :");
    scanf("%d",&cnbr);

   
    while (fscanf(ptr, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %lf %s",
                &r.id,
		        &r.userId,
		        r.name,
                &r.accountNbr,
                &r.deposit.month,
                &r.deposit.day,
                &r.deposit.year,
                &r.deposit.heure,
                &r.deposit.min,
                &r.deposit.sec,
                r.country,
                r.phone,
                &r.amount,
                r.accountType) != EOF)
    {   
        if (r.accountNbr == cnbr){
            if (strcmp(u.name,r.name) == 0){
            found = TRUE;
            break;
            }
        }
    }
    if(!found){
        printf("Enter a valid acount number\n");
        goto acountnbr;
    }
    fclose(ptr);
    scan:
    printf("\n\t\t-->> You want to update your :\n");
    printf("\n\t\t[1]- Country\n"); 
    printf("\n\t\t[2]- Number\n");
    printf("\n\t\t[3]- Exit\n");
    scanf("%d", &option);
        switch (option)
        {
        case 1:
            system("clear");
            printf("\t\t\t===== Update country =====\n");
            printf("\n\t\t-->> Enter the new country :");
            scanf("%s", r.country);
            break;
        case 2:
            system("clear");
            printf("\t\t\t===== Update number =====\n");
            printf("\n\t\t-->> Enter the new number :");
            scanf("%s", r.phone);
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
            goto scan;
        }
        if (replace_line("../data/records.txt",r)){
            success(u);
            }else {
                goto scan;
            }
}

bool maketransaction(struct User u){
    struct Record r;
    struct Record d;
    bool found = FALSE;
    int cnbr;
    int nbr2;
    int option;
    char dname[100];
    FILE *ptr;
    ptr = fopen("../data/records.txt", "rw");
    if (ptr == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    system("clear");
    acount :
    printf("\t\t\t===== Make transaction =====\n");
    printf("\n\t\t-->> Enter the acount number :");
    scanf("%d",&cnbr);
     while (fscanf(ptr, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %lf %s",
                &r.id,
		        &r.userId,
		        r.name,
                &r.accountNbr,
                &r.deposit.month,
                &r.deposit.day,
                &r.deposit.year,
                &r.deposit.heure,
                &r.deposit.min,
                &r.deposit.sec,
                r.country,
                r.phone,
                &r.amount,
                r.accountType) != EOF)
    {   
        if (r.accountNbr == cnbr){
            if (strcmp(u.name,r.name) == 0){
            found = TRUE;
            break;
            }
        }
    }
    if(!found){
        printf("Enter a valid acount number\n");
        goto acount;
    }
    fclose(ptr);
    scan:
    printf("\n\t\t-->> You want to :\n");
    printf("\n\t\t[1]- Transfer\n"); 
    printf("\n\t\t[2]- Withdraw\n");
    printf("\n\t\t[3]- Deposit\n");
    printf("\n\t\t[4]- Exit\n");
    scanf("%d", &option);
        switch (option)
        {
        case 1:
            system("clear");
            acount2 :
            printf("\t\t\t===== Transfer =====\n");
            printf("\n\t\t-->> Enter the account number that will reserve the transfer :");
            scanf("%d", &nbr2);
            printf("\n\t\t-->> Enter the name of the person that will reserve the transfer :");
            scanf("%s",dname);
            ptr = fopen("../data/records.txt", "rw");
            if (ptr == NULL)
            {
                printf("Error! opening file");
                exit(1);
            }
            while (fscanf(ptr, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %lf %s",
                        &d.id,
                        &d.userId,
                        d.name,
                        &d.accountNbr,
                        &d.deposit.month,
                        &d.deposit.day,
                        &d.deposit.year,
                        &d.deposit.heure,
                        &d.deposit.min,
                        &d.deposit.sec,
                        d.country,
                        d.phone,
                        &d.amount,
                        d.accountType) != EOF)
            {   
                if (d.accountNbr == nbr2){
                    if (strcmp(d.name,dname) == 0){
                    found = TRUE;
                    break;
                    }
                }
            }
            if(!found){
                system("clear");
                printf("Enter a valid acount number and name\n");
                goto acount2;
            }
            fclose(ptr);
            tr :
            printf("\n\t\t-->> Enter the amount to transfer :");
            double transfert;
            scanf("%lf",&transfert);
            if (transfert > r.amount || transfert <= 0){
                printf("Error your balance is insufficient or the ammount is nulle, enter a valide amount");
                goto tr;
            } else {
                d.amount = d.amount + transfert;
                r.amount = r.amount - transfert;
                if (replace_line("../data/records.txt",r) && replace_line("../data/records.txt",d)){
                success(u);
                }else {
                    printf("Error");
                    goto scan;
                }
            }
            
            break;
        case 2:
            system("clear");
            tr2 :
            printf("\t\t\t===== Withdraw =====\n");
            printf("\n\t\t-->> Enter the amount to be withdrawn :");
            scanf("%lf",&transfert);
            if (transfert > r.amount || transfert <= 0){
                printf("Error your balance is insufficient or the ammount is nulle, enter a valide amount");
                goto tr2;
            } else {
                r.amount = r.amount - transfert;
                if (replace_line("../data/records.txt",r)){
                success(u);
                }else {
                    printf("Error");
                    goto scan;
                }
            }
            break;
        case 3:
            system("clear");
            printf("\t\t\t===== Deposit =====\n");
            printf("\n\t\t-->> Enter the amount to be deposit :");
            double depose;
            scanf("%lf",&depose);
            if (depose <= 0){
                printf("Error your balance is insufficient or the ammount is nulle, enter a valide amount");
                goto tr2;
            } else {
                r.amount = r.amount - depose;
                if (replace_line("../data/records.txt",r)){
                success(u);
                }else {
                    printf("Error");
                    goto scan;
                }
            }
            break;
        case 4:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
            goto scan;
        }
        return TRUE;
}

bool removeaccount(struct User u){
    struct Record r;
    bool found = FALSE;
    int cnbr;
    char pw[50];
    FILE *ptr;
    ptr = fopen("../data/records.txt", "rw");
    if (ptr == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    system("clear");
    acount :
    printf("\t\t\t===== Remove existing account =====\n");
    printf("\n\t\t-->> Enter the acount number to remove :");
    scanf("%d",&cnbr);
     while (fscanf(ptr, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %lf %s",
                &r.id,
		        &r.userId,
		        r.name,
                &r.accountNbr,
                &r.deposit.month,
                &r.deposit.day,
                &r.deposit.year,
                &r.deposit.heure,
                &r.deposit.min,
                &r.deposit.sec,
                r.country,
                r.phone,
                &r.amount,
                r.accountType) != EOF)
    {   
        if (r.accountNbr == cnbr){
            if (strcmp(u.name,r.name) == 0){
            found = TRUE;
            break;
            }
        }
    }
    if(!found){
        system("clear");
        printf("Enter a valid acount number or press ctrl + c to Exit\n");
        goto acount;
    }
    fclose(ptr);
    printf("\n\t\t_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d %02d:%02d:%02d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.deposit.heure,
                   r.deposit.min,
                   r.deposit.sec,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
    Password :
    printf("\n\t\t-->> Confirme your password to remove the acount :");
    scanf("%s",pw);
    if (strcmp(pw,u.password) == 0){
        if (removeaccountfromfile("../data/records.txt",r)){
        success(u);
                }else {
                    system("clear");
                    printf("Error");
                    exit(0);
                }
    return TRUE;
    }else{
        system("clear");
        printf("Wrong password\n");
        exit(0);
    }
}

bool transferowner(struct User u){
     struct Record r;
    bool found = FALSE;
    int cnbr;
    int option;
    FILE *ptr;
    char newowner[50];
    ptr = fopen("../data/records.txt", "rw");
    if (ptr == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    system("clear");
    acountnbr :
    printf("\t\t\t===== Transfer owner =====\n");
    printf("\n\t\t-->> Enter the acount number :");
    scanf("%d",&cnbr);

   
    while (fscanf(ptr, "%d %d %s %d %d/%d/%d %02d:%02d:%02d %s %s %lf %s",
                &r.id,
		        &r.userId,
		        r.name,
                &r.accountNbr,
                &r.deposit.month,
                &r.deposit.day,
                &r.deposit.year,
                &r.deposit.heure,
                &r.deposit.min,
                &r.deposit.sec,
                r.country,
                r.phone,
                &r.amount,
                r.accountType) != EOF)
    {   
        if (r.accountNbr == cnbr){
            if (strcmp(u.name,r.name) == 0){
            found = TRUE;
            break;
            }
        }
    }
    if(!found){
        printf("Enter a valid acount number or press 'ctrl + c' to exite\n");
        goto acountnbr;
    }
    fclose(ptr);
    scan:
    printf("\n\t\t-->> Enter the name of the new owner:\n");
    scanf("%s", newowner);
    if (strcmp(getuser(newowner),newowner) == 0){  
        r.userId = getuserir(newowner);
        strcpy(r.name,newowner);
        if (replace_line("../data/records.txt",r)){
            success(u);
            }else {
                goto scan;
            }
        }else {
            system("clear");
            printf("No user found\n");
        }
}