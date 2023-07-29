#include <stdio.h>
#include <stdlib.h>

struct pcb      // Process control block
{
    int arrivaltime;
    int bursttime;
    int priority;
    int remaining_time;
};

int main(int argc, char *argv[])
{
    printf("---------------------------------------------------\n");
    printf("     Please enter one of Number for Simulation\n"); // Menu for which algo to be used;
    printf("---------------------------------------------------\n");
    printf("1).First-Come First-Served\n");
    printf("2).Shortest Job First\n");
    printf("3).Round Robin Scheduling\n");
    printf("4).Priority Scheduling\n");
    printf("5).Shortest Remaining Time First\n");
    printf("6).Longest remaining time first\n");
   
    int ch,n1,n2;
    FILE *fp = fopen("Test.txt", "r");
    FILE *fo = fopen("out.txt","w");

    if (fp == NULL)
    {
        printf("\n*********************\n");
        printf("   File not opened\n");
        printf("*********************\n");
    }
    else
    { 
        printf("\n******************************\n");
        printf("   File Opened Successfully\n");
        printf("******************************\n");
    }
    int count2 = 0, j, i, t;
    fscanf(fp,"%d",&count2);        // take a input from file to array of at, bt and priority.
    struct pcb p[count2];
    for(int i=0;i<count2;i++)fscanf(fp,"%d",&p[i].arrivaltime);
    for(int i=0;i<count2;i++)fscanf(fp,"%d",&p[i].bursttime);
    for(int i=0;i<count2;i++)fscanf(fp,"%d",&p[i].priority);
    int choice = 0;
    // for(int i=0;i<count2;i++)
    // {
    //     printf("%d",p[i].arrivaltime);
    // }
    scanf("%d", &choice);
    for (i = 0; i < count2 - 1; i++)        // sorting all processes at,bt and priority
    {
        for (j = i + 1; j < count2; j++)
        {
            if (p[i].arrivaltime > p[j].arrivaltime)
            {
                t = p[i].arrivaltime;
                p[i].arrivaltime = p[j].arrivaltime;
                p[j].arrivaltime = t;
                t = p[i].bursttime;
                p[i].bursttime = p[j].bursttime;
                p[j].bursttime = t;
                t = p[i].priority;
                p[i].priority = p[j].priority;
                p[j].priority = t;
            }
        }
    }

    if (choice == 1)
    {
        fprintf(fo,"1).First-Come First-Served\n");
        int ft[count2], tat[count2], wt[count2];    // finishtime, tat and waiting time of processes
        int sum = 0;
        fprintf(fo,"\n-----------------\n");
        fprintf(fo,"   Gantt Chart\n");
        fprintf(fo,"-----------------\n");
        for (i = 0; i < count2; i++)
        {
            for (j = 0; j < p[i].arrivaltime - sum; j++)
            {
                printf(" ");
            }
            if (p[i].arrivaltime > sum)
            {
                sum += p[i].arrivaltime;    // to calculate complition time we required at + bt
            }
            sum += p[i].bursttime;
            ft[i] = sum;
            for (j = 0; j < p[i].bursttime; j++)
            {
                fprintf(fo," P%d", i + 1);      // to print gantt chart
            }
        }
        fprintf(fo,"\n\n");
        for (i = 0; i < count2; i++)
        {
            tat[i] = ft[i] - p[i].arrivaltime;
            wt[i] = tat[i] - p[i].bursttime;
        }
        fprintf(fo,"Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for (int i = 0; i < count2; i++)
        {
            fprintf(fo,"   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n", p[i].priority, p[i].arrivaltime, p[i].bursttime, ft[i], tat[i], wt[i]);
        }
        float sum1 = 0;
        float sum2 = 0;
        for (i = 0; i < count2; i++)
        {
            sum1 += tat[i];
            sum2 += wt[i];
        }
        fprintf(fo,"Average Turn Around Time is: %.2f\n", sum1 / count2);
        fprintf(fo,"Average Waiting Time is: %.2f\n", sum2 / count2);
    }
    else if (choice == 2)
    {
        fprintf(fo,"2).Shortest Job First\n");
        int rt[count2];
        for (i = 0; i < count2; i++)
        {
            rt[i] = p[i].bursttime;
        }
        int com = 0;    // keep records of howmany processes are completed
        int ti = 0;     // total howmany processes are involved in gantt chart
        int s = 0;
        int finisht;    // finish-time of process.
        int check = 0;
        int minm = 1000;    // give some random num which are not assign to any process like "INTMAX"
        int wt[count2];
        int tat[count2];
        int ft[count2];
        while(com != count2)
        {
            for(j = 0; j < count2; j++)
            {
                if((p[j].arrivaltime <= ti) && (rt[j] < minm) && rt[j] > 0)
                {
                    minm = rt[j];
                    s = j;
                    check = 1;
                }
            }
            if (check == 0)
            {
                ti++;
                printf(" ");
                continue;
            }
            rt[s] = 0;
            minm = rt[s];
            if(minm == 0)
                minm = 1000;    // give some random num which are not assign to any process like "INTMAX"
            if(rt[s] == 0)
            {
                for(int k = 0; k < p[s].bursttime; k++)
                {
                    fprintf(fo," P%d", s + 1);
                }
                ti += p[s].bursttime;
                com++;
                check = 0;
                ft[s] = ti;
                wt[s] = ft[s] - p[s].arrivaltime - p[s].bursttime;
                if (wt[s] < 0)
                    wt[s] = 0;
            }
        }
        for (i = 0; i < count2; i++)
        {
            tat[i] = ft[i] - p[i].arrivaltime;
        }
        fprintf(fo,"\n");
        fprintf(fo,"Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for (int i = 0; i < count2; i++)
        {
            fprintf(fo,"   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n", p[i].priority, p[i].arrivaltime, p[i].bursttime, ft[i], tat[i], wt[i]);
        }
        float sum1 = 0;
        float sum2 = 0;
        for (i = 0; i < count2; i++)
        {
            sum1 += tat[i];
            sum2 += wt[i];
        }
        fprintf(fo,"Average Turn Around Time is: %.2f\n", sum1 / count2);
        fprintf(fo,"Average Waiting Time is: %.2f\n", sum2 / count2);
    }
    else if (choice == 3)
    {
        fprintf(fo,"3).Round Robin Scheduling\n");
        fprintf(fo,"--------------------------\n");
        int ft[count2+11], tat[count2+11], wt[count2+11];    // finishtime, tat and waiting time of processes
        int n=count2,sz,current_time=0,mn=0,completed=0,sel=0,first=0;
        printf("Enter quantum size: ");
        scanf("%d",&sz);

        int queue[n],bt[n];
        for(int i=0;i<n;i++)bt[i]=p[i].bursttime;
        int front=-1,rear=-1;
        int x,cr=0,last=-1;
        for(int time=-1;;time++)
        {
            int tst=1;
            if(rear==-1)tst=0;
            for(int i=0;i<n;i++)
            {
                if(p[i].arrivaltime==time)
                {
                    front=(front+1)%n;
                    queue[front]=i;
                    if(rear==-1)rear=rear+1;
                }
            }
            if(time==-1 || (!tst))continue;
            if(cr==0)x=queue[rear];
            else x=last;
            last=x;
            // printf("%d ",x);
            fprintf(fo,"P%d ",x+1);
            cr++;
            p[x].bursttime--;
            if(cr!=sz && p[x].bursttime!=0)continue;
            cr=0;
            rear=(rear+1)%n;
            if(p[x].bursttime!=0)
            {
                front=(front+1)%n;
                queue[front]=x;
            }
            else
            {
                ft[x]=time+1;
                tat[x]=ft[x]-p[x].arrivaltime;
                wt[x]=tat[x]-bt[x];
                completed++;
                if(completed==n)break;
            }
            // for(int i=0;i<n;i++) printf("%d: %d ",time,p[i].bursttime);
            // printf("\n");
        }
        fprintf(fo,"\n");
        fprintf(fo,"Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for (int i = 0; i < count2; i++)
        {
            fprintf(fo,"   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n", p[i].priority, p[i].arrivaltime,bt[i], ft[i], tat[i], wt[i]);
        }
        float sum1 = 0;
        float sum2 = 0;
        for (i = 0; i < count2; i++)
        {
            sum1 += tat[i];
            sum2 += wt[i];
        }
        fprintf(fo,"Average Turn Around Time is: %.2f\n", sum1 / count2);
        fprintf(fo,"Average Waiting Time is: %.2f\n", sum2 / count2);
    }
    else if (choice == 4)
    {
        fprintf(fo,"4).Priority Scheduling\n"); // similar to sjf.
        int rt[count2];
        int pt[count2];
        for (i = 0; i < count2; i++)
        {
            rt[i] = p[i].bursttime;
            pt[i] = p[i].priority;
        }
        int com = 0;
        int ct = 0;
        int s = 0;
        int finisht;
        int check = 0;
        int min = 1000;
        int wt[count2];
        int tat[count2];
        int ft[count2];
        while (com != count2)
        {
            for (i = 0; i < count2; i++)
            {
                if (rt[i] > 0 && pt[i] < min && ct >= p[i].arrivaltime)
                {
                    s = i;
                    check = 1;
                    min = pt[i];
                }
            }
            if (check == 0)
            {
                ct++;
                printf(" ");
                continue;
            }
            if (check == 1)
            {
                com++;
                ct += rt[s];
                ft[s] = ct;
                tat[s] = ft[s] - p[s].arrivaltime;
                wt[s] = tat[s] - p[s].bursttime;
                for (j = 0; j < p[s].bursttime; j++)
                {
                    fprintf(fo," P%d", s + 1);
                }
                rt[s] = 0;
                min = 1000;
            }
        }
        fprintf(fo,"\n");
        fprintf(fo,"Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for (int i = 0; i < count2; i++)
        {
            fprintf(fo,"   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n", p[i].priority, p[i].arrivaltime, p[i].bursttime, ft[i], tat[i], wt[i]);
        }
        float sum1 = 0;
        float sum2 = 0;
        for (i = 0; i < count2; i++)
        {
            sum1 += tat[i];
            sum2 += wt[i];
        }
        fprintf(fo,"Average Turn Around Time is: %.2f\n", sum1 / count2);
        fprintf(fo,"Average Waiting Time is: %.2f\n", sum2 / count2);
    }
    else if (choice == 5)
    {
        fprintf(fo,"5).Shortest Remaining Time First\n");
        int rt[count2];
        for (i = 0; i < count2; i++)
        {
            rt[i] = p[i].bursttime;
        }
        int com = 0;
        int ti = 0;
        int s = 0;
        int finisht;    // finish-time of any process
        int check = 0;
        int minm = 1000;    // give some random num which are not assign to any process like "INTMAX"
        int wt[count2];
        int tat[count2];
        int ft[count2];
        while (com != count2)
        {
            for (j = 0; j < count2; j++)
            {
                if((p[j].arrivaltime <= ti) && (rt[j] < minm) && rt[j] > 0)
                {
                    minm = rt[j];
                    s = j;
                    check = 1;
                }
            }
            if (check == 0)
            {
                ti++;
                printf(" ");
                continue;
            }
            rt[s]--;
            fprintf(fo," P%d", s + 1);
            minm = rt[s];
            if (minm == 0)
                minm = 1000;
            if (rt[s] == 0)
            {
                com++;
                check = 0;
                ft[s] = ti + 1;
                wt[s] = ft[s] - p[s].arrivaltime - p[s].bursttime;
                if (wt[s] < 0)
                    wt[s] = 0;
            }
            ti++;
        }
        for (i = 0; i < count2; i++)
        {
            tat[i] = ft[i] - p[i].arrivaltime;
        }
        fprintf(fo,"\n");
        fprintf(fo,"Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for (int i = 0; i < count2; i++)
        {
            fprintf(fo,"   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n", p[i].priority, p[i].arrivaltime, p[i].bursttime, ft[i], tat[i], wt[i]);
        }
        float sum1 = 0;
        float sum2 = 0;
        for (i = 0; i < count2; i++)
        {
            sum1 += tat[i];
            sum2 += wt[i];
        }
        fprintf(fo,"Average Turn Around Time is: %.2f\n", sum1 / count2);
        fprintf(fo,"Average Waiting Time is: %.2f\n", sum2 / count2);
    }
    else if (choice == 6)
    {
        fprintf(fo,"6).Longest remaining time first\n");
        int rt[count2];
        for (i = 0; i < count2; i++)
        {
            rt[i] = p[i].bursttime;
        }
        int com = 0;
        int ti = 0;
        int s = 0;
        int finisht;
        int check = 0;
        int maxm = 0;   // give some random num which are not assign to any process like "INTMIN"
        int wt[count2];
        int tat[count2];
        int ft[count2];
        while (com != count2)
        {
            for (j = 0; j < count2; j++)
            {
                if ((p[j].arrivaltime <= ti) && (rt[j] >= maxm) && rt[j] > 0)
                {
                    maxm = rt[j];
                    s = j;
                    check = 1;
                }
            }
            if (check == 0)
            {
                ti++;
                printf(" ");
                continue;
            }
            rt[s]--;
            fprintf(fo," P%d", s + 1);
            maxm = rt[s];
            if (rt[s] == 0)
            {
                com++;
                check = 0;
                ft[s] = ti + 1;
                wt[s] = ft[s] - p[s].arrivaltime - p[s].bursttime;
                if (wt[s] < 0)
                    wt[s] = 0;
            }
            ti++;
        }
        for (i = 0; i < count2; i++)
        {
            tat[i] = ft[i] - p[i].arrivaltime;
        }
        fprintf(fo,"\n");
        fprintf(fo,"Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for (int i = 0; i < count2; i++)
        {
            fprintf(fo,"   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n", p[i].priority, p[i].arrivaltime, p[i].bursttime, ft[i], tat[i], wt[i]);
        }
        float sum1 = 0;
        float sum2 = 0;
        for (i = 0; i < count2; i++)
        {
            sum1 += tat[i];
            sum2 += wt[i];
        }
        fprintf(fo,"Average Turn Around Time is: %.2f\n", sum1 / count2);
        fprintf(fo,"Average Waiting Time is: %.2f\n", sum2 / count2);
    }
    else
    {
        printf("You entered wrong number\n");
    }
    return 0;
}