#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#define INFINIT 99999

typedef struct Citty
{
    char name[30];
    int num;
} City;

typedef struct Graphh
{
    int distance;
    City From;
    City To;
} Graph;

City cities[15];
City temp1,temp2;
FILE *INFILE,*INFILE1,*OUTFILE;
int numoflines=15;
int lines=0;

int main()
{
    INFILE = fopen("cities.txt","r");
    INFILE1 = fopen("cities.txt","r");
    char c[128],Srs[30],Dest[30],temper[5];
    int input,x,y;

    //defining cities in the country
    strcpy(cities[0].name,"Akka");
    strcpy(cities[1].name,"Bethlehem");
    strcpy(cities[2].name,"Haifa");
    strcpy(cities[3].name,"Hebron");
    strcpy(cities[4].name,"Jenin");
    strcpy(cities[5].name,"Jericho");
    strcpy(cities[6].name,"Jerusalem");
    strcpy(cities[7].name,"Nablus");
    strcpy(cities[8].name,"Nazareth");
    strcpy(cities[9].name,"Qalqilya");
    strcpy(cities[10].name,"Ramallah");
    strcpy(cities[11].name,"Salfit");
    strcpy(cities[12].name,"Tubas");
    strcpy(cities[13].name,"Tulkarem");
    strcpy(cities[14].name,"Yafa");

    for(int o =0 ; o <15; o++) //defining numbers to get the index for each city
    {
        cities[o].num = o;
    }

    while(fgets(c, sizeof(c), INFILE) != NULL)
    {
        lines++;
    }

    Graph Country[numoflines][numoflines];

    for(int z=0; z<numoflines; z++)//defining all the cities that they are not connected to each other
    {
        for(int q=0; q<numoflines; q++)
        {
            Country[z][q].distance = INFINIT;
        }
    }

    do
    {
        printf("\n1. Load cities\n");
        printf("2. Enter source city:\n");
        printf("3. Enter destination city: \n");
        printf("4. Exit: \n");
        scanf("%d",&input);

        switch(input)
        {
        case 1:
            while(fgets(c, sizeof(c), INFILE1) != NULL)
            {
                Graph temp;
                char *cutter = strtok(c,"\t");
                strcpy(temp.From.name,cutter);
                printf("%s ->",temp.From.name);

                cutter = strtok(NULL,"\t");
                strcpy(temp.To.name,cutter);
                printf("%s:",temp.To.name);

                cutter = strtok(NULL,"km");
                temp.distance = atoi(cutter);
                printf("%dKm\n",temp.distance);

                Add_Edge(Country,temp.From.name,temp.To.name,temp.distance);//adding the connection between the two cities and adding distance
            }

            break;
        case 2:
            printf("Enter Source City:\n");
            scanf("%s",&Srs);

            for(int i = 0; i < numoflines; i++)//to get the index of the entered city
            {
                if(strcmp(cities[i].name,Srs)==0)
                {
                    x = i;//X (from index)
                }
            }

            break;
        case 3:
            printf("Enter destination city:\n");
            scanf("%s",&Dest);

            for(int i = 0; i < numoflines; i++)//to get the index of the entered city
            {
                if(strcmp(cities[i].name,Dest)==0)
                {
                    y = i;//y (to index)
                }
            }

            dijkstra(Country,x,y);

            break;
        case 4:

            FILE_dijkstra(Country,x,y);
            fclose(OUTFILE);
            break;
        default:
            printf("Enter numbers between 1-4\n");
        }
    }
    while(input != 4);

    return 0;
}

void Add_Edge(Graph country[numoflines][numoflines],char from[],char to[],int dist)//insert cities in the first empty place in array
{
    for(int a=0; a<15; a++)
    {
        if(strcmp(cities[a].name,from)==0)
        {
            temp1.num = cities[a].num;
            strcpy(temp1.name,cities[a].name);
        }
    }

    for(int b=0; b<15; b++)
    {
        if(strcmp(cities[b].name,to)==0)
        {
            temp2.num = cities[b].num;
            strcpy(temp2.name,cities[b].name);
        }
    }

    country[temp1.num][temp2.num].From = temp1;
    country[temp1.num][temp2.num].To = temp2;
    country[temp1.num][temp2.num].distance = dist;

}//end of funtion


void dijkstra(Graph Country[numoflines][numoflines],int From,int To)
{
    OUTFILE = fopen("shortest_path.txt", "w");
    int cost[numoflines][numoflines],distance[numoflines],pred[numoflines];
    int visited[numoflines],count,mindistance,after,i,j,a,b;

    for(a=0;a<numoflines;a++)
    {
        for(b=0;b<numoflines;b++)
        {
            cost[a][b] = Country[a][b].distance;
        }
    }

    for(i=0; i<numoflines; i++)
    {
        distance[i]=cost[From][i];
        pred[i]=From;
        visited[i]=0;
    }
    distance[From]=0;
    visited[From]=1;
    count=1;

    while(count<numoflines-1)
    {
        mindistance=INFINIT;

        for(i=0; i<numoflines; i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                after=i;
            }

        visited[after]=1;
        for(i=0; i<numoflines; i++)
            if(!visited[i])
                if(mindistance+cost[after][i]<distance[i])
                {
                    distance[i]=mindistance+cost[after][i];
                    pred[i]=after;
                }
        count++;
    }

    for(i=0; i<numoflines; i++)
        if(i!=From && (cities[i].num==To))
        {
            printf("\nDistance To %s=%d\n",cities[i].name,distance[i]);
            printf("Path = %s(%dKM)",cities[i].name,cost[pred[i]][i]);
            j=i;
            do
            {
                j=pred[j];
                printf("<-%s(%dKM)",cities[j].name,cost[pred[j]][j]);

            }
            while(j!=From);
        }
}


void FILE_dijkstra(Graph Country[numoflines][numoflines],int From,int To)
{
    int cost[numoflines][numoflines],distance[numoflines],pred[numoflines];
    int visited[numoflines],count,mindistance,after,i,j,a,b;

    for(a=0;a<numoflines;a++)
    {
        for(b=0;b<numoflines;b++)
        {
            cost[a][b] = Country[a][b].distance;
        }
    }

    for(i=0; i<numoflines; i++)
    {
        distance[i]=cost[From][i];
        pred[i]=From;
        visited[i]=0;
    }
    distance[From]=0;
    visited[From]=1;
    count=1;

    while(count<numoflines-1)
    {
        mindistance=INFINIT;

        for(i=0; i<numoflines; i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                after=i;
            }

        visited[after]=1;
        for(i=0; i<numoflines; i++)
            if(!visited[i])
                if(mindistance+cost[after][i]<distance[i])
                {
                    distance[i]=mindistance+cost[after][i];
                    pred[i]=after;
                }
        count++;
    }

    for(i=0; i<numoflines; i++)
        if(i!=From && (cities[i].num==To))
        {
            fprintf(OUTFILE,"\nDistance To %s=%d\n",cities[i].name,distance[i]);
            fprintf(OUTFILE,"Path = %s(%dKM)",cities[i].name,cost[pred[i]][i]);
            j=i;
            do
            {
                j=pred[j];
                fprintf(OUTFILE,"<-%s(%dKM)",cities[j].name,cost[pred[j]][j]);

            }
            while(j!=From);
        }
}
