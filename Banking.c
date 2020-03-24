#include<stdlib.h>
#include<stdio.h>

#include<string.h>
int h[100];
struct bank
{
        char name[100];
        int accn,aadharcardno,password,key;
        int activity[5];
        float balance;
        struct bank *next;
};
struct bank* acc=NULL;
struct bank* temp;
void balance()
{
        printf("Current balance:%f",temp->balance);
}
int hash(int val)
{
        int hk,hk1,i,c=0,c1=3,c2=5;
        do
        {
                hk1=val%10;
                hk=(hk1+c*c1+c2*c*c)%10;
                if(h[hk]==-1)
                {
                        h[hk]=val;
                        return hk;
                }
                else if(hk==10)
                {
                        printf("Value cannot be stored.\n");
                        break;
                }
                else
                        c++;
        }while(h[hk]!=-1);
}
struct bank* lastactivity(struct bank *acc)
{
        int i,j=0;
        while(temp->activity[j]!=0)
        {
                j++;
        }
        printf("The latest activities are: \n");
        for(i=j-1;i>=0;i--)
        {
                printf("%d\n",temp->activity[i]);
        }
}
struct bank* withdraw(struct bank *acc)
{
        int i=0;
        float amount;
        printf("Enter the amount:");
        scanf("%f",&amount);
        if(amount>temp->balance)
        {
                printf("Insufficient balance.");

        }
        else
        {
                temp->balance=(temp->balance)-amount;
        }
        while(temp->activity[i]!=0)
        {
                i++;
        }
        temp->activity[i]=-amount;
}
struct bank* deposit(struct bank *acc)
{

        int i=0;
        float amount;
        printf("Enter the amount: ");
        scanf("%f",&amount);
        temp->balance=(temp->balance)+amount;
        while(temp->activity[i]!=0)
        {
                i++;
        }
        temp->activity[i]=amount;
}

struct bank* create_account(struct bank *acc)
{
        int adc,i,acn,pass,choice;
        char name1[100];
        struct bank *new_bank,*ptr;
        do
        {
                printf("Enter Name: ");
                scanf("%s",name1);
                printf("Enter Aadhar card number: ");
                scanf("%d",&adc);
                printf("Enter your Password: ");
                scanf("%d",&pass);
                new_bank=(struct bank *)malloc(sizeof(struct bank));
                strcpy(new_bank->name,name1);
                new_bank->aadharcardno=adc;
                new_bank->key=hash(pass);
                new_bank->balance=0;
                new_bank->accn=new_bank->aadharcardno+5789;
                printf("Your Account No. is: %d \n",new_bank->accn);
                for(i=0;i<=4;i++)
                {
                        new_bank->activity[i]=0;
                }
                if(acc==NULL)
                {
                        new_bank->next=NULL;
                        acc=new_bank;
                }
                else
                {
                        ptr=acc;
                        while(ptr->next!=NULL)
                                ptr=ptr->next;
                        ptr->next=new_bank;
                        new_bank->next=NULL;
                }
                printf("DO YOU WANT TO CREATE A NEW ACCOUNT?\n1.YES\n2.NO");
                printf("\nEnter your choice: ");
                scanf("%d",&choice);
        }while(choice!=2);
        return acc;
}
struct bank* login(struct bank *acc)
{
        int pass,acn;
        char name1[50],a;
        struct bank *ptr;
        reenter:
        ptr=acc;
        printf("Enter account number: ");
        scanf("%d",&acn);
        printf("Enter your password: ");
        scanf("%d",&pass);
        while((ptr!=NULL)&&(ptr->accn!=acn))
        {
                ptr=ptr->next;
        }
        if(ptr==NULL)
        {
                printf("ACCOUNT DOESN'T EXISTS or INVALID ACCOUNT NUMBER or PASSWORD \n PLEASE RE-ENTER YOUR DETAILS.");
                goto reenter;
        }
        if(h[ptr->key]==pass)
        {
                printf("LOGIN SUCCESSFUL.\nWELCOME %s\n",ptr->name);
                temp=ptr;
        }
        else
        {
                printf("ACCOUNT DOESN'T EXISTS or INVALID ACCOUNT NUMBER or PASSWORD \n PLEASE RE-ENTER YOUR DETAILS.");
                goto reenter;
        }

        return acc;
}
int main()
{

        int i,choice,option,opt;
        printf("************PHD BANK*************\n");
        printf("     ******MAIN MENU******    \n");
        for(i=0;i<=9;i++)
                h[i]=-1;
        printf("1.CREATE ACCOUNT \n2.LOGIN\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        if(choice==1)
                acc=create_account(acc);
        printf("DO YOU WANT TO LOGIN?\n1.YES\n2.NO");
        printf("\nEnter your choice: ");
        scanf("%d",&opt);
        if(opt==1)
        {
                acc=login(acc);
                do
                {
                        printf("1.Withdraw\n2.Deposit\n3.Latest Transactions\n4.Balance\n5.Logout\nEnter your choice: ");
                        scanf("%d",&option);
                        switch(option)
                        {
                        case 1:
                                acc=withdraw(acc);
                                printf("Amount has been withdrawn.\n");
                                break;
                        case 2:
                                acc= deposit(acc);
                                printf("Amount has been deposited.\n");
                                break;
                        case 3:
                                acc=lastactivity(acc);
                                break;
                        case 4:
                                balance();
                                break;
                        case 5:
                                printf("YOU HAVE BEEN LOGGED OUT SUCCESSFULLY.\n");
                                break;

                        default:printf("Invalid input.");
                        }
                }while(option!=5);
        }
        return 0;

}
