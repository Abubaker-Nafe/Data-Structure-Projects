#include <stdio.h>
#include <stdlib.h>

struct Course
{
    char courseName[50];
    int courseCredit;
    char courseCode[50];
    char courseDep[50];
    char topic[500];
};

typedef struct courseAVL *AVLNode;

struct courseAVL
{
    struct Course coursePtr;
    AVLNode Left;
    AVLNode Right;
    int Height; //Balance information
};

int Height( AVLNode P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}


int Max( int a, int b )
{
    return (a > b) ? a : b;
}



AVLNode SingleRotateRight( AVLNode K2 )
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}

AVLNode SingleRotateLeft( AVLNode K1 )
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;
}

AVLNode DoubleRotateLeftRight( AVLNode K3 )
{

    K3->Left = SingleRotateLeft( K3->Left );


    return SingleRotateRight( K3 );
}

AVLNode DoubleRotateRightLeft( AVLNode K1 )
{

    K1->Right = SingleRotateRight( K1->Right );


    return SingleRotateLeft( K1 );
}



AVLNode Insert( struct Course X, AVLNode T )
{
    if( T == NULL )
    {

        T = (struct courseAVL*)malloc( sizeof( struct courseAVL ) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            T->coursePtr=X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if(strcmp(X.courseCode,T->coursePtr.courseCode) <0 )
    {
        T->Left = Insert( X, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if( strcmp(X.courseCode,T->Left->coursePtr.courseCode)<0  )
                T = SingleRotateRight( T );
            else
                T = DoubleRotateLeftRight( T );
    }
    else if( strcmp(X.courseCode,T->coursePtr.courseCode) == 1 )
    {
        T->Right = Insert( X, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
            if( strcmp(X.courseCode,T->Right->coursePtr.courseCode)>0  )
                T = SingleRotateLeft( T );
            else
                T = DoubleRotateRightLeft( T );
    }


    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}


//in-order print to see the elements
void PrintInOrder( AVLNode t)
{
    if( t != NULL)
    {
        PrintInOrder( t->Left );
        printf("%s\n", t->coursePtr.courseCode);
        PrintInOrder( t->Right );
    }
}



void PrintInOrderDep( AVLNode t,char c[])
{
    if( t != NULL)
    {
        PrintInOrderDep( t->Left,c );

        if(strcasecmp(t->coursePtr.courseDep,c) == 0)
        {
            printf("\nCourse Code:%s\tCourse Name:%s\tCourse Hours:%d\n", t->coursePtr.courseCode,t->coursePtr.courseName,t->coursePtr.courseCredit);
        }

        PrintInOrderDep( t->Right,c );
    }
}

void PrintInOrderDetailed( AVLNode t)
{
    if( t != NULL)
    {
        PrintInOrderDetailed( t->Left );
        printf("\n%s  %d  %s\n", t->coursePtr.courseCode,t->coursePtr.courseCredit,t->coursePtr.topic);
        PrintInOrderDetailed( t->Right );
    }
}

void PrintInOrderToFile(FILE* insertFile, AVLNode t)
{
    if( t != NULL)
    {

        PrintInOrderToFile(insertFile, t->Left );
        insertFile=fopen("offered_courses.txt","a+");
        fprintf(insertFile, "%s:%d#%s#%s/%s\n", t->coursePtr.courseName,t->coursePtr.courseCredit,t->coursePtr.courseCode,t->coursePtr.courseDep,t->coursePtr.topic);
        PrintInOrderToFile(insertFile, t->Right );

    }
}

int getBalance(AVLNode N)
{
    if (N == NULL)
        return 0;
    return Height(N->Left) - Height(N->Right);
}


AVLNode MakeEmpty( AVLNode T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );

    }
    return NULL;
}

AVLNode Find( char courseCode[50], AVLNode T )
{
    if( T == NULL )
        return NULL;
    if( strcmp(courseCode, T->coursePtr.courseCode)<0 )
        return Find( courseCode, T->Left );
    else if( strcmp(courseCode, T->coursePtr.courseCode)>0 )
        return Find( courseCode, T->Right );
    else
        return T;
}

AVLNode FindDep( char courseDep[50], AVLNode T )
{
    if( T == NULL )
        return NULL;
    if( strcmp(courseDep, T->coursePtr.courseDep)<0 )
        return FindDep( courseDep, T->Left );
    else if( strcmp(courseDep, T->coursePtr.courseDep)>0)
        return FindDep( courseDep, T->Right );
    else
        return T;
}

AVLNode minValueNode(AVLNode node)
{
    AVLNode current = node;

    while (current->Left != NULL)
        current = current->Left;

    return current;
}

AVLNode deleteNode(AVLNode root, struct Course key)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( strcmp(key.courseCode,root->coursePtr.courseCode) <0  )
        root->Left = deleteNode(root->Left, key);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( strcmp(key.courseCode, root->coursePtr.courseCode) >0 )
        root->Right = deleteNode(root->Right, key);

    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->Left == NULL) || (root->Right == NULL) )
        {
            AVLNode temp = root->Left ? root->Left : root->Right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            AVLNode temp = minValueNode(root->Right);



            // Copy the inorder successor's data to this node
            root->coursePtr=temp->coursePtr;

            // Delete the inorder successor
            root->Right = deleteNode(root->Right, temp->coursePtr);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->Height = 1 + Max(Height(root->Left),
                           Height(root->Right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->Left) >= 0)
        return SingleRotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->Left) < 0)
    {
        root->Left =  SingleRotateLeft(root->Left);
        return SingleRotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->Right) <= 0)
        return SingleRotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->Right) > 0)
    {
        root->Right = SingleRotateRight(root->Right);
        return SingleRotateLeft(root);
    }

    return root;
}

AVLNode deleteDep(char delDep[50],AVLNode t)
{
    while(FindDep(delDep,t)!=NULL)
    {
        AVLNode temp=FindDep(delDep,t);
        t=deleteNode(t,temp->coursePtr);
    }

    return t;
}

AVLNode deleteChar(char c, AVLNode t)
{
    if( t != NULL)
    {
        deleteChar(c, t->Left );
        if(strcmp(c,t->coursePtr.courseName[0])==0)
        {
            AVLNode temp=   Find(t->coursePtr.courseCode,t);
            t=deleteNode(t,temp->coursePtr);
        }
        deleteChar(c, t->Right );
    }
    return t;
}

int main()
{
    char character;
    FILE* coursesFile;
    coursesFile=fopen("courses.txt","r+");
    char line[200];
    char* token;
    AVLNode courseTree=NULL;
    int choice;
    while(choice!=-1)
    {

        printf("\n1-Read the file courses.txt and create the tree\n");
        printf("2-Insert a new course from the user with all its associated data\n");
        printf("3-Find a course and support updating of its information.\n");
        printf("4-List courses in lexicographic order with their associated information (credit hours, IDs, and topics).\n");
        printf("5-List all topics associated with a given course. \n");
        printf("6-List all courses in lexicographic order that belong to the same department\n");
        printf("7-Delete a course\n");
        printf("8-Delete all courses that start with a specific letter.\n");
        printf("9-Delete all courses belong to a given department.\n");
        printf("10-Save all words in file offered_courses.txt and exit!\n");
        scanf("%d",&choice);



        switch(choice)
        {
        case 1:
            if(coursesFile == NULL)
            {
                printf("Error opening file");
            }
            while(fgets(line,200,coursesFile)!=NULL)
            {
                struct Course courseLine;
                //Course Name
                token=strtok(line,":");
                strcpy(courseLine.courseName,token);
                printf("\n%s\n",courseLine.courseName);
                //Course Credits
                token=strtok(NULL,"#");
                courseLine.courseCredit=atoi(token);
                printf("%d\n",courseLine.courseCredit);
                //Course Code
                token=strtok(NULL,"#");
                strcpy(courseLine.courseCode,token);
                printf("%s\n",courseLine.courseCode);
                //Course Major
                token=strtok(NULL,"/");
                strcpy(courseLine.courseDep,token);
                printf("%s\n",courseLine.courseDep);
                //Course Topics


                token=strtok(NULL,"\n");
                strcpy(courseLine.topic,token);
                printf("%s\n",courseLine.topic);
                printf("\n");

                courseTree = Insert(courseLine,courseTree);
            }

            break;

        case 2 :
            ;
            struct Course insertedCourse;
            coursesFile = fopen("courses.txt", "a+");
            if ( coursesFile == NULL)
            {
                printf("Error! Could not open file\n");
                exit(-1);
            }
            printf("Please enter Name:\n");

            char Name[200];
            getchar();
            gets(Name);
            strcpy(insertedCourse.courseName,Name);

            printf("Please enter Credit:\n");
            int Credit;
            scanf("%d",&Credit);
            insertedCourse.courseCredit=Credit;


            printf("Please enter Code:\n");
            char Code[50];
            scanf("%s",Code);
            strcpy(insertedCourse.courseCode,Code);


            printf("Please enter Major:\n");
            char Major[100];
            getchar();
            gets(Major);
            strcpy(insertedCourse.courseDep,Major);


            printf("Please enter topics:\n");
            char topics[500];
            getchar();
            gets(topics);
            strcpy(insertedCourse.topic,topics);

            courseTree=Insert(insertedCourse,courseTree);
            PrintInOrder(courseTree);

            break;

        case 3:
            printf("Please enter course Code:");
            char foundCourse[50];
            AVLNode tempNodePtr;
            scanf("%s",foundCourse);
            printf("%s\n",foundCourse);
            if(Find(foundCourse,courseTree)==NULL)
            {
                printf("No Course Found\n");
            }
            else
            {
                tempNodePtr=Find(foundCourse,courseTree);



                printf("%s\n",tempNodePtr->coursePtr.courseCode);
                int updateChoice;
                while(updateChoice!=6)
                {
                    printf("What do you want to update:\n");
                    printf("1.Course Name\n");
                    printf("2.Course Hours\n");
                    printf("3.Course Code\n");
                    printf("4.Course Department\n");
                    printf("5.Course Topics\n");
                    printf("6.Exit\n");

                    scanf("%d",&updateChoice);

                    switch(updateChoice)
                    {

                    case 1:
                        printf("Enter new Name:");
                        char newName[50];
                        getchar();
                        gets(newName);

                        strcpy(tempNodePtr->coursePtr.courseName,newName);

                        break;

                    case 2:
                        printf("Enter new Credits:");
                        int newCredit;
                        scanf("%d",&newCredit);
                        tempNodePtr->coursePtr.courseCredit=newCredit;

                        break;

                    case 3:
                        ;

                        AVLNode tempHolder;
                        tempHolder=tempNodePtr;

                        courseTree=deleteNode(courseTree,tempNodePtr->coursePtr);


                        printf("Enter new Code:");
                        char newCode[50];
                        getchar();
                        gets(newCode);

                        strcpy(tempHolder->coursePtr.courseCode,newCode);

                        courseTree=Insert(tempHolder->coursePtr,courseTree);
                        // printf("%s\n",tempNodePtr->coursePtr.courseCode);

                        break;

                    case 4:
                        printf("Enter new Major:");
                        char newMajor[50];
                        getchar();
                        gets(newMajor);

                        strcpy(tempNodePtr->coursePtr.courseDep,newMajor);

                        break;

                    case 5:
                        printf("add new Topic:");

                        char newTopic[50];
                        getchar();
                        gets(newTopic);

                        strcat(tempNodePtr->coursePtr.topic,",");
                        strcat(tempNodePtr->coursePtr.topic,newTopic);

                        break;
                    }
                }
                updateChoice=0;

            }

            break;
        case 4 :

            PrintInOrderDetailed(courseTree);
            break;


        case 5:

            printf("Enter course Code:");
            char topicPrintCourse[50];
            AVLNode tempNodePrint;
            scanf("%s",topicPrintCourse);

            if(Find(topicPrintCourse,courseTree)==NULL)
            {
                printf("No Course Found\n");
            }
            else
            {
                tempNodePrint=Find(topicPrintCourse,courseTree);

                printf("%s\n",tempNodePrint->coursePtr.topic);
            }

            break;

        case 6:

            printf("Enter Department:");
            char newDep[50];
            getchar();
            gets(newDep);

            PrintInOrderDep(courseTree,newDep);

            break;

        case 7:

            printf("Please enter course Code:");
            char deletedCourse[50];
            AVLNode tempNodedeletion;
            scanf("%s",deletedCourse);
            printf("%s\n",deletedCourse);
            if(Find(deletedCourse,courseTree)==NULL)
            {
                printf("No Course Found\n");
            }
            else
            {
                tempNodedeletion=Find(deletedCourse,courseTree);

                courseTree=deleteNode(courseTree,tempNodedeletion->coursePtr);
            }
            break;

        case 8:

            printf("Enter first letter of the cours ename to delete :\n");
            scanf("%c",&character);

            deleteChar(character,courseTree);

            break;
        case 9:
            printf("Please enter Department:");
            char depart[50];
            getchar();
            gets(depart);

            courseTree=deleteDep(depart,courseTree);

            break;
        case 10:
            ;
            FILE* insertFile=fopen("offered_courses.txt","w");

            printf("Done...\n");
            PrintInOrderToFile(insertFile,courseTree);
            fclose(insertFile);
            exit(0);


            break;
        default:
            printf("Enter numbers from 1-10\n");
        }
    }
    return 0;
}
