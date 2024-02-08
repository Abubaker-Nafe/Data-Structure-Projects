#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// A program to assign passengers to various busses to help them commute based on their scheduled times

typedef struct Passenger //linked list for passengers
{
    int ID;
    int Date;
    char Time[4];
    char From[10];
    char To[10];
    struct Passenger *next;
} Passengers;

typedef struct Busses//linked list for busses
{
    int Num;
    int Date;
    char Time[10];
    char From[10];
    char To[10];
    int Price;
    int Capacity;
    struct Bus *next;
    struct Passenger *Passengers_in_bus;
} Bus;

typedef struct Unmatchedd//linked list for Unmatched passengers
{
    int ID;
    int Date;
    char Time[10];
    char From[10];
    char To[10];
    struct Passenger *next;
    int i;
}Unmatched;




void AssignPassToBus(Passengers *Pass_Head,Bus *Bus_Head,Unmatched *Unmatched_Head);
void Print();

int input;

int main()
{
    char c[128];
    FILE* PFile;
    FILE* BFile;

    Bus *Bus_Head;
    Bus_Head = (Bus*) malloc(sizeof(Bus));
    Bus_Head->next = NULL;

    Passengers *Pass_Head;
    Pass_Head = (Passengers*) malloc(sizeof(Passengers));
    Pass_Head->next = NULL;

    Unmatched *Unmatched_Head;
    Unmatched_Head = (Unmatched*) malloc(sizeof(Unmatched));
    Unmatched_Head->next = NULL;

    int Number;
    int PasID;
    int PasDate;
    char PasTime[10];
    char PasFrom[10];
    char PasTo[10];
    int DeletePass;
    int BusDelete;

    do
    {
        Print();

        switch(input)
        {
        case 1:

            BFile = fopen("busses.txt","r");
            //reading from file line by line
            while(fgets(c, sizeof(c), BFile) != NULL)
            {

                // c is one line (1#18042022#14:30#Birzeit#Ramallah#6#15)

                char *token;

                token = strtok(c,"#"); // gives us the bus number
                int BusNumber = atoi(token);

                token = strtok(NULL,"#");//date
                int BusDate = atoi(token);

                //------------------------------

                token = strtok(NULL,"#");//time
                char BusTime[10];
                strcpy(BusTime,token);

                //-------------------------------

                token = strtok(NULL,"#");//from
                char BusFrom[10];
                strcpy(BusFrom,token);

                //---------------------------

                token = strtok(NULL,"#");//to
                char BusTo[10];
                strcpy(BusTo,token);

                //---------------------------

                token = strtok(NULL,"#");//price
                int BusPrice = atoi(token);

                //----------------------------

                token = strtok(NULL,"#");//capacity
                int BusCapacity = atoi(token);

                //inserting data into struct
                Bus *New_Bus,*temp;

                New_Bus = (Bus*)malloc(sizeof(Bus));

                New_Bus->Num = BusNumber;
                New_Bus->Date = BusDate;
                strcpy(New_Bus->Time,BusTime);
                strcpy(New_Bus->From,BusFrom);
                strcpy(New_Bus->To,BusTo);
                New_Bus->Price = BusPrice;
                New_Bus->Capacity = BusCapacity;
                New_Bus->next = NULL;

                //printing result
                printf("%d\t %d\t %s\t %s\t %s\t %d\t %d\t\n",New_Bus->Num, New_Bus->Date,New_Bus->Time, New_Bus->From, New_Bus->To,New_Bus->Price,New_Bus->Capacity);

                //creating Bus Linked list

                if(Bus_Head->next == NULL)
                {
                    Bus_Head->next = New_Bus;
                    New_Bus->next = NULL;
                }
                else
                {
                    temp = Bus_Head;
                    while(temp->next != NULL)
                    {
                        temp=temp->next;
                    }
                    temp->next = New_Bus;
                    New_Bus->next = NULL;
                }
            }
            printf("\nBUSSES FILE LOADED..\n");

            break;
        case 2:

            PFile = fopen("passengers.txt","r");
            //Reading from file line by line
            while(fgets(c, sizeof(c), PFile) != NULL)
            {

                // c is one line 1190001#18042022#14:00#Birzeit#Nablus

                char *token;

                token = strtok(c,"#"); // gives us the bus number
                int PassID = atoi(token);

                token = strtok(NULL,"#");//date
                int PassDate = atoi(token);

                //------------------------------

                token = strtok(NULL,"#");//time
                char PassTime[10];
                strcpy(PassTime,token);

                //-------------------------------

                token = strtok(NULL,"#");//from
                char PassFrom[10];
                strcpy(PassFrom,token);

                //---------------------------

                token = strtok(NULL,"#");//to
                char PassTo[10];
                strcpy(PassTo,token);
//------------------------------------------------
                //creating passenger struct to insert/store data in
                struct Passenger *New_Passenger,*temp;

                New_Passenger =(Passengers*) malloc(sizeof(Passengers));


                New_Passenger->next = NULL;
                New_Passenger->ID = PassID;
                New_Passenger->Date = PassDate;
                strcpy(New_Passenger->Time,PassTime);
                strcpy(New_Passenger->From,PassFrom);
                strcpy(New_Passenger->To,PassTo);

                //Creating the Passengers linked list
                //problem with Time
                printf("%d\t %d\t %s\t %s\t %s\t \n",New_Passenger->ID,New_Passenger->Date,New_Passenger->Time,New_Passenger->From,New_Passenger->To);

                if(Pass_Head->next == NULL)
                {
                    Pass_Head->next = New_Passenger;
                    New_Passenger->next = NULL;
                }
                else
                {
                    temp = Pass_Head;
                    while(temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->next = New_Passenger;
                    New_Passenger->next = NULL;
                }
            }
            printf("\nPASSENGERS FILE LOADED..\n");

            break;

        case 3://Assigning passengers and printing each bus with it's passengers

            AssignPassToBus(Pass_Head,Bus_Head,Unmatched_Head);

            break;

        case 4://PRint a specific bus info along with it's passengers info (ID's)
                printf("Enter the bus number you want info for:\n");
                scanf("%d",&Number);
                Print_Bus(Bus_Head,Number);

            break;

        case 5:
            //printing unmatched passnegers
            //these passengers shouuld be in a seperate linked list

            Print_Unmatched(Unmatched_Head);

            break;

        case 6://Adding new passenger

                printf("Enter Passenger ID\n");
                scanf("%d",&PasID);
                printf("Enter Passenger's Date (it should be in this form 16072022)\n");
                scanf("%d",&PasDate);
                printf("Enter Passenger's Time (It should be in this form 11:00)\n");
                scanf("%s",&PasTime);
                printf("Where are you going from\n");
                scanf("%s",&PasFrom);
                printf("Where are you heading\n");
                scanf("%s",&PasTo);
                //creating a struct to insert it into the created linked list
                struct Passenger *New_Passengerr,*tempp;

                New_Passengerr =(Passengers*) malloc(sizeof(Passengers));


                New_Passengerr->next = NULL;
                New_Passengerr->ID = PasID;
                New_Passengerr->Date = PasDate;
                strcpy(New_Passengerr->Time,PasTime);
                strcpy(New_Passengerr->From,PasFrom);
                strcpy(New_Passengerr->To,PasTo);

                //Creating the Passengers linked list
                //problem with Time reading...

                printf("%d\t %d\t %s\t %s\t %s\t \n",New_Passengerr->ID,New_Passengerr->Date,New_Passengerr->Time,New_Passengerr->From,New_Passengerr->To);

                if(Pass_Head->next == NULL)
                {
                    Pass_Head->next = New_Passengerr;
                    New_Passengerr->next = NULL;
                }
                else
                {
                    tempp = Pass_Head;
                    while(tempp->next != NULL)
                    {
                        tempp = tempp->next;
                    }
                    tempp->next = New_Passengerr;
                    New_Passengerr->next = NULL;
                }

            break;

        case 7://delete passenger

            printf("Enter the passenger's ID you want to delete:\n");
            scanf("%d",&DeletePass);

            Passengers *temppp = Pass_Head;

            while(temppp->next != NULL)
            {
                if(temppp->next->ID == DeletePass)
                {
                    temppp->next = temppp->next->next;
                    temppp->next = NULL;
                }
                temppp = temppp->next;
            }

            break;

        case 8://Deleting bus number does not delete the passengers of that bus
            //Deleting bus by number

            printf("Enter the ID to delete the bus:\n");
            scanf("%d",&BusDelete);

            Bus *temper = Bus_Head;

            while(temper->next != NULL)
            {
                if(temper->Num == BusDelete)
                {
                    //temper->next = temper->next->next;
                    //temper->next = NULL;
                    free(temper);
                }
                temper = temper->next;
            }

            AssignPassToBus(Pass_Head,Bus_Head,Unmatched_Head);

            break;

        case 9:
            exit(0);
            break;
        }
    }
    while(input != 9);

    fclose(PFile);
    fclose(BFile);
    return 0;
}


void Print()
{
    printf("\nChoose an Operation\n");
    printf("1. Load the bus information file\n");
    printf("2. Load the passenger information file\n");
    printf("3. Assign passengers and print assignment information of allbusses\n");
    printf("4. Print a specific bus information along with its passengers information (names and IDs)\n");
    printf("5. Print unmatched passengers\n");
    printf("6. Add new passenger\n");
    printf("7. Delete passenger\n");
    printf("8. Delete bus number");
    printf("9. Exit\n");
    scanf("%d",&input);
}

void AssignPassToBus(Passengers *Pass_Head,Bus *Bus_Head,Unmatched *Unmatched_Head)
{
    Passengers* Pass = Pass_Head->next;
    Bus *Busss = Bus_Head->next;

    printf("Busses information\n");
    printf("Number\t  Date\t\t Time\t From\t To\t Price \t Capacity\n");
    while(Busss != NULL)
    {
        printf("%d\t %d\t %s\t %s\t %s\t %d\t %d\t\n",Busss->Num, Busss->Date,Busss->Time, Busss->From, Busss->To,Busss->Price,Busss->Capacity);
        Busss = Busss->next;
    }
    printf("\n");

    while (Pass != NULL)//reading every passenger in the linked list
    {
        bool matched = false;//using bool to check if the passenger got matched or not

        while (Busss != NULL)//reading every bus in the linked list
        {
            if( (Pass->Date == Busss->Date) && (strcmp(Busss->To,Pass->To)==0) && (strcmp(Busss->From,Pass->From)) )
            {
                matched = true;
                Passengers *New_Pass;
                New_Pass = (Passengers*) malloc(sizeof(Passengers));
                New_Pass->ID = Pass->ID;
                New_Pass->Date = Pass->Date;
                strcpy(New_Pass->From, Pass->From);
                strcpy(New_Pass->To, Pass->To);
                strcpy(New_Pass->Time, Pass->Time);
                New_Pass->next = NULL;
                //insert into linked list
                Busss->Passengers_in_bus->next = New_Pass;

                printf("Passenger with ID : %d got matched with Bus with number : %d",Pass->ID,Busss->Num);
            }
            printf("\n");

            Busss = Busss->next;
        }

        if(matched == false)
        {
            printf("Passenger with ID : %d is unmatched",Pass->ID);

            //insert into unmatched list

            Unmatched *New_Unmatched,*temp;

            New_Unmatched = (Unmatched*)malloc(sizeof(Unmatched));

            New_Unmatched->ID = Pass->ID;
            New_Unmatched->Date = Pass->Date;
            strcpy(New_Unmatched->From, Pass->From);
            strcpy(New_Unmatched->To, Pass->To);
            strcpy(New_Unmatched->Time, Pass->Time);
            New_Unmatched->i = 1;
            New_Unmatched->next = NULL;

            //creating Bus Linked list

            if(Unmatched_Head->next == NULL)
            {
                Unmatched_Head->next = New_Unmatched;
                New_Unmatched->next = NULL;
            }
            else
            {
                temp = Unmatched_Head;
                while(temp->next != NULL)
                {
                    temp=temp->next;
                }
                temp->next = New_Unmatched;
                New_Unmatched->next = NULL;
            }
        }
        printf("\n\n");
        Pass = Pass->next;
    }

    printf("\n");
}

void Print_Bus(Bus *Bus_Head,int Number)
{

    Bus *temp;
    Bus *Buses = Bus_Head;

    while(Buses->next != NULL)
    {
        if(Buses->Num == Number)
        {
            temp = Buses;
            printf("Bus information:\n");
            printf("%d\t %d\t %s\t %s\t %s\t %d\t %d\t\n",temp->Num, temp->Date,temp->Time, temp->From, temp->To,temp->Price,temp->Capacity);
        }
        Buses = Buses->next;
    }

    while(Buses->next != NULL)
    {
        if(Buses->Num == Number)
        {
            temp = Buses;
            printf("Passengers information:\n");
            printf("%d\t %d\t %s\t %s\t %s\n",temp->Passengers_in_bus->ID,temp->Passengers_in_bus->Date,temp->Passengers_in_bus->Time,temp->Passengers_in_bus->From,temp->Passengers_in_bus->To);
        }
        Buses->Passengers_in_bus = Buses->Passengers_in_bus->next;
    }
}

void Print_Unmatched(Unmatched *Unmatched_Head)
{
    Unmatched *temp = Unmatched_Head->next;

    printf("Unmatched passengers:\n");

    while(temp != NULL)
    {
        if(temp->i==1)
        {
            printf("%d\t %d\t %s\t %s\t %s\t \n",temp->ID,temp->Date,temp->Time,temp->From,temp->To);
        }
        temp = temp->next;
    }
    printf("\n");
}
