#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define SIZE1 13
//#define SIZE2 27
//define size for both tables

typedef struct
{
    char CourseName[40];
    int CourseHours;
    char CourseCode[40];
    char CourseDepartment[40];
    char CourseTopics[300];
    int status; // 0:Empty , 1:Occupied , 2:Deleted

} Course;

typedef struct
{
    Course Courses;
    int status; // 0:Empty , 1:Occupied , 2:Deleted
} Hash_Struct;

Course hash_table_1[100];
Course hash_table_2[100];

int Table_1_Counter = 0;
int Table_2_Counter = 0;
int Table_1_Collision_Counter = 0;
int Table_2_Collision_Counter = 0;
int Size_Counter = 0;
int Load_Factor_1;
int SIZE;

int hash(char name[], int tableSize)
{

    int sum = 0;

    // shift by  5 steps = mul by 2^5 = 32
    // we used mod here for don't make overflow when the String so large length
    for (int i = 0; name[i] != '\0'; ++i)
    {
        sum = ((sum << 5) + name[i])% tableSize;
    }

    return sum;
}

int hash2(char key[],int tableSize)
{
    int sum = 0;

    for(int i = 0 ; i<strlen(key);i++)
    {
        sum += key[i];
    }
    int newsum = Least_Prime(tableSize) - (sum%Least_Prime(tableSize));

	return newsum;
}

void Initialize_Hash_Table_1()
{
    for(int i = 0 ; i < SIZE ; i++)
    {
        hash_table_1[i].status = 0;
    }
}

void Initialize_Hash_Table_2()
{
    for(int i = 0 ; i < SIZE ; i++)
    {
        hash_table_2[i].status = 0;
    }
}

void Print_Table_1()
{
    printf("\tTable_1\n");
    for (int i = 0 ; i < SIZE ; i++)
    {
        if(hash_table_1[i].status==0)
        {
            printf("\t%i\t__\n",i);
        }
        else if(hash_table_1[i].status==1)
        {
            printf("\t%i\t%s\n",i,hash_table_1[i].CourseName);
        }
        else
        {
            printf("\t%i\t__(Deleted)\n",i);
        }
    }
}

void Print_Table_2()
{
    printf("\n\tTable_2:\n");
    for (int i = 0 ; i < SIZE ; i++)
    {
        if(hash_table_2[i].status==0)
        {
            printf("\t%i\t__\n",i);
        }
        else if(hash_table_2[i].status==1)
        {
            printf("\t%i\t%s\n",i,hash_table_2[i].CourseName);
        }
        else
        {
            printf("\t%i\t__(Deleted)\n",i);
        }
    }
}

void Insert_Table_1(Course C)//Collisions were dealt with using Linear probing
{

    int Index = hash(C.CourseName,SIZE);

    if(Table_1_Counter == SIZE)
    {
        printf("Table -1- is full!!!!");
        return;
    }

    if(hash_table_1[Index].status==0 || hash_table_1[Index].status==2)
    {
        hash_table_1[Index].status = 1;
        hash_table_1[Index].CourseHours = C.CourseHours;
        strcpy(hash_table_1[Index].CourseCode,C.CourseCode);
        strcpy(hash_table_1[Index].CourseDepartment,C.CourseDepartment);
        strcpy(hash_table_1[Index].CourseName,C.CourseName);
        strcpy(hash_table_1[Index].CourseTopics,C.CourseTopics);

        Table_1_Counter++;

    }
    else if ( hash_table_1[Index].status==1)
    {

        for(int i = 0 ; i< SIZE; i++)
        {
            Table_1_Collision_Counter++;
            int New_Index = (Index+i) % SIZE;
            if(hash_table_1[New_Index].status != 1)
            {
                hash_table_1[New_Index].status = 1;
                hash_table_1[New_Index].CourseHours = C.CourseHours;
                strcpy(hash_table_1[New_Index].CourseCode,C.CourseCode);
                strcpy(hash_table_1[New_Index].CourseDepartment,C.CourseDepartment);
                strcpy(hash_table_1[New_Index].CourseName,C.CourseName);
                strcpy(hash_table_1[New_Index].CourseTopics,C.CourseTopics);

                Table_1_Counter++;
                break;
            }
        }
    }

}

Course Find_Table_1(char name[])
{
    int Index = hash(name,SIZE);

    for(int i = 0 ; i< SIZE ; i++)
    {
        int New_Index = (Index+i) % SIZE;
        if(hash_table_1[New_Index].status == 1 && strcmp(name,
                hash_table_1[New_Index].CourseName) == 0);
        {
            return hash_table_1[New_Index];
        }
    }
}

int Find_Index_Table_1(char name[])
{
    int Index = hash(name,SIZE);

    for(int i = 0 ; i< SIZE ; i++)
    {
        int New_Index = (Index+i) % SIZE;
        if(hash_table_1[New_Index].status == 1 && strcmp(name,
                hash_table_1[New_Index].CourseName) == 0);
        {
            return (New_Index-i);
        }
    }
}

void Delete_Table_1(char name[])
{
    int Index = hash(name,SIZE);

    for(int i = 0 ; i< SIZE ; i++)
    {
        int New_Index = (Index+i) % SIZE;
        if(hash_table_1[New_Index].status == 1 && strcmp(name,
                hash_table_1[New_Index].CourseName) == 0)
        {
            hash_table_1[New_Index].status = 2;
            Table_1_Counter--;
        }
    }
}

void Insert_Table_2(Course C)//Collisions were dealt with using double hashing
{

    int Index = hash(C.CourseName,SIZE);
    int Index2 = hash2(C.CourseName,SIZE);

    if(Table_2_Counter == SIZE)
    {
        printf("Table -2- is full!!");
        return;
    }

    if(hash_table_2[Index].status==0 || hash_table_2[Index].status==2)
    {
        hash_table_2[Index].status = 1;
        hash_table_2[Index].CourseHours = C.CourseHours;
        strcpy(hash_table_2[Index].CourseCode,C.CourseCode);
        strcpy(hash_table_2[Index].CourseDepartment,C.CourseDepartment);
        strcpy(hash_table_2[Index].CourseName,C.CourseName);
        strcpy(hash_table_2[Index].CourseTopics,C.CourseTopics);

        Table_2_Counter++;

    }
    else if ( hash_table_2[Index].status==1)
    {
        for(int i = 0 ; i< SIZE; i++)
        {
            Table_2_Collision_Counter++;
            int New_Index = (Index+ (i*Index2))% SIZE;
            if(hash_table_2[New_Index].status != 1)
            {
                hash_table_2[New_Index].status = 1;
                hash_table_2[New_Index].CourseHours = C.CourseHours;
                strcpy(hash_table_2[New_Index].CourseCode,C.CourseCode);
                strcpy(hash_table_2[New_Index].CourseDepartment,C.CourseDepartment);
                strcpy(hash_table_2[New_Index].CourseName,C.CourseName);
                strcpy(hash_table_2[New_Index].CourseTopics,C.CourseTopics);

                Table_2_Counter++;
                break;
            }
        }
    }
}

Course Find_Table_2(char name[])
{
    int Index = hash(name,SIZE);
    int Index2 = hash2(name,SIZE);

    for(int i = 0 ; i< SIZE ; i++)
    {
        int New_Index = (Index+ (i*Index2))% SIZE;
        if(hash_table_2[New_Index].status == 1 && strcmp(name,
                hash_table_2[New_Index].CourseName) == 0);
        {
            return hash_table_2[New_Index];
        }
    }
}

int Find_Index_Table_2(char name[])
{
    int Index = hash(name,SIZE);
    int Index2 = hash2(name,SIZE);

    for(int i = 0 ; i< SIZE ; i++)
    {
        int New_Index = (Index+ (i*Index2))% SIZE;
        if(hash_table_2[New_Index].status == 1 && strcmp(name,
                hash_table_2[New_Index].CourseName) == 0);
        {
            return (New_Index- (i*Index2));
        }
    }
}

void Delete_Table_2(char name[])
{
    int Index = hash(name,SIZE);
    int Index2 = hash2(name,SIZE);

    for(int i = 0 ; i< SIZE ; i++)
    {
        int New_Index = (Index+ (i*Index2))% SIZE;
        if(hash_table_2[New_Index].status == 1 && strcmp(name,
                hash_table_2[New_Index].CourseName) == 0)
        {
            hash_table_2[New_Index].status = 2;
            Table_2_Counter--;
        }
    }
}

int Find_Size(int counter)
{

    for(int i= 2*counter;;i++)
    {
        if(IsPrime(i))
        {
            return i;
        }
    }

}

int IsPrime(int x)
{
    for(int i = 2;(i*i) <=x;i++)
    {
        if(x%i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int Least_Prime(int x)
{
    for(int i = x-1;;i--)
    {
        if(IsPrime(i))
        {
            return i;
        }
    }
}

void Rehash(int x)
{
        if(Load_Factor_1 > 70)
        {
            SIZE = Find_Size(SIZE);

            Load_Factor_1 = 0;
        }
}

void Load_Factor()
{
    Load_Factor_1 = (Table_1_Counter*100)/SIZE;
}

int main()
{

    Course tmp;
    int option;
    char EWord[40];
    int input;
    FILE *File;
    FILE *File_1;
    FILE *OutputFile;
    char info[3000];

    File = fopen("offered_courses.txt","r");
    File_1 = fopen("offered_courses.txt","r");

    while(!feof(File))// first we calculated the lines in the file to reach the size of the array
    {
        fgets(info,3000,File);
        int *token=strtok(info,"#:/\n");
        token=strtok(NULL,"#:/\n");
        token=strtok(NULL,"#:/\n");
        token=strtok(NULL,"#:/\n");
        token= strtok(NULL,"#:/\n");
        Size_Counter++;
    }

    SIZE = Find_Size(Size_Counter);

    Initialize_Hash_Table_1();
    Initialize_Hash_Table_2();

    while(!feof(File_1))//after we have known the size and created the array now we insert the values
    {
        Course temp;
        fgets(info,3000,File_1);
        int *cutter=strtok(info,"#:/\n");

        strcpy(temp.CourseName,cutter);

        cutter=strtok(NULL,"#:/\n");
        temp.CourseHours=atoi(cutter);

        cutter=strtok(NULL,"#:/\n");

        strcpy(temp.CourseCode,cutter);

        cutter=strtok(NULL,"#:/\n");

        strcpy(temp.CourseDepartment,cutter);

        cutter= strtok(NULL,"#:/\n");

        strcpy(temp.CourseTopics,cutter);

        Insert_Table_1(temp);
        Insert_Table_2(temp);
    }
    do
    {
        printf("\n1. Print hashed tables (including empty spots).\n");
        printf("2. Print out table size and the load factor.\n");
        printf("3. Print out the used hash functions. \n");//mo3adalat
        printf("4. Insert a new record to hash table (insertion will be done on both hash tables). \n");
        printf("5. Search for a specific word (specify which table to search in). \n");
        printf("6. Delete a specific record (from both tables)\n");
        printf("7. Compare between the two methods in terms of number of collisions occurred.\n");
        printf("8. Save hash table back to a file named saved_courses.txt (of the double hashing)\n");
        scanf("%d",&input);
        Rehash(SIZE);

        //Rehash(SIZE);

        switch(input)
        {

        case 1 :

            Print_Table_1();
            Print_Table_2();

            break;

        case 2:

            Load_Factor();

            printf("\nTable -1- Size: %d\nTable -1- Places filled:%d\nTable -1- Load Factor:%d%%\n"
                   ,SIZE,Table_1_Counter,Load_Factor_1);

            printf("\nTable -2- Size: %d\nTable -2- Places filled:%d\nTable -2- Load Factor:%d%%\n"
                   ,SIZE,Table_2_Counter,Load_Factor_1);

            break;

        case 3 :
            printf("\nHash function used in Hash Table-1- : (key + i) MOD (Table size)\t(Linear)\n");
            printf("Hash function used in Hash Table-2- : (h(key) + (i*hp(key))) MOD (Table size)\t(Double Hashing)\nhp(key)= (q-(key%(q))");

            break;

        case 4://Inserting to the 2nd table is left yet

            printf("********Inserting new Record to the hash table********\n");
            printf("Enter Course Name:\n");
            getchar();
            gets(tmp.CourseName);

            printf("Enter Course Hours:\n");
            scanf("%d",&tmp.CourseHours);

            printf("Enter Course Code:\n");
            scanf("%s",&tmp.CourseCode);

            printf("Enter Course Department:\n");
            getchar();
            gets(tmp.CourseDepartment);

            printf("Enter Course Topics: (with ,)\n");
            scanf("%s",&tmp.CourseTopics);

            Insert_Table_1(tmp);
            Insert_Table_2(tmp);
            break;

        case 5://table -2- still hasn't dealth with yet

            printf("Which table would you like to search from:\n1.Table -1-\n2.Table -2-\n");
            scanf("%d",&option);
            if(option == 1 )
            {
                printf("Enter Course Name:\n");
                getchar();
                gets(EWord);
                tmp = Find_Table_1(EWord);
                printf("\n%s\t%d\t%s\t%s\t\n%s\nIndex:%d\n",tmp.CourseName,tmp.CourseHours,
                       tmp.CourseCode,tmp.CourseDepartment,tmp.CourseTopics,Find_Index_Table_1(EWord));

            }
            else if(option == 2)
            {
                printf("Enter Course Name:\n");
                scanf("%s",&EWord);
                tmp = Find_Table_2(EWord);
                printf("\n%s\t%d\t%s\t%s\t\n%s\nIndex:%d\n",tmp.CourseName,tmp.CourseHours,
                       tmp.CourseCode,tmp.CourseDepartment,tmp.CourseTopics,Find_Index_Table_2(EWord));
            }

            break;

        case 6:
            printf("Enter Course Name to be deleted:\n");
            getchar();
            gets(EWord);
            Delete_Table_1(EWord);//from table -1-
            Delete_Table_2(EWord);//from table -2-

            break;

        case 7 :

            printf("Table -1- # of Collision :%d\t(Linear probing)\n",Table_1_Collision_Counter);
            printf("Table -2- # of Collision :%d\t(Double Hashing)\n",Table_2_Collision_Counter);
            if(Table_1_Collision_Counter > Table_2_Collision_Counter)
            {
                printf("Table -1- has more collisions than Table -2-\n");
            }
            else if(Table_1_Collision_Counter < Table_2_Collision_Counter)
            {
                printf("Table -2- has more collisions than Table -1-\n");
            }
            else
            {
                printf("Table -1- has same # of collisions for Table-2- \n");
            }
            break;

        case 8:

            OutputFile = fopen("saved_courses.txt", "w");

            for(int i = 0 ; i < SIZE ; i++)
                if(hash_table_2[i].status == 1)
                {
                    fprintf(OutputFile,"%s:%d#%s#%s/%s\n",hash_table_2[i].CourseName,hash_table_2[i].CourseHours,
                            hash_table_2[i].CourseCode,
                            hash_table_2[i].CourseDepartment,hash_table_2[i].CourseTopics);
                }
            fclose(OutputFile);
            break;

        default:
            printf("\nEnter number between 1-8\n\n");
        }

    }
    while(input != 8);
    return 0;
}
