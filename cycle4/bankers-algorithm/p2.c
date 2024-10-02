/* @author Sona F Shukoor */

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int a[MAX][MAX], max[MAX][MAX], need[MAX][MAX], avail[MAX],work[MAX], f[MAX], s[MAX], n, m;

//s[] is safe state sequence, f[] finished

void print(int row, int col, int x[MAX][MAX])
{
    for(int i = 0; i < col; i++)
    {
        printf("\t%c", i+65);
    }
    printf("\n");
    for(int i = 0; i < row; i++)
    {
        printf("P%d\t", i+1);
        for(int j = 0; j < col; j++)
        {
            printf("%d\t", x[i][j]);
        }
        printf("\n");
    }
}
void initialise()
{
    for(int i = 0; i < n; i++)
        {
            f[i] = 0;
            s[i] = 0;
        }
    for(int i = 0; i < m; i++)
    {
        work[i] = avail[i];
    }
}

int safe_seq()
{   
    int safe, ind =0, flag;
    initialise();
    while(ind < n){
        safe = 0;
        for(int i = 0; i < n; i++)
        {   
            if(f[i] == 0)
            {
                for(int j = 0; j < m; j++)
                {
                    flag = 0;
                    if(need[i][j] > work[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0)
                {
                    s[ind++] = i+1;
                    for(int k = 0; k < m; k++)
                    {
                        work[k] += a[i][k];
                    }
                    f[i] = 1;
                    safe = 1;
                }
            }
        }
        if(safe == 0) //If resources can't be allocated safely
        {
            break;
        }
    }
    if(ind != n)
    {
        return 1;
    }
    return 0;
}

void request_res(int p)
{
    int r[m];
        
    printf("Enter resource request: ");
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &r[i]);
    }
    for(int i = 0; i < m; i++)
    {
        if((r[i] > need[p-1][i]) || (r[i] > avail[i]))
        {
            printf("Requested resources are not available.\n");
            return;
        }
    }
    for(int i = 0; i < m; i++)
    {
        avail[i] -=  r[i];
        a[p-1][i] += r[i];
        need[p-1][i] -= r[i];
    }
    if(safe_seq()) 
    {
        printf("Unsafe state!!\n");
        printf("Resource request denied.\n");
        
        for(int i = 0; i < m; i++)
    {
        avail[i] +=  r[i];
        a[p-1][i] -= r[i];
        need[p-1][i] += r[i];
    }
        exit(1);
    }

    printf("Process %d\n", p);
    printf("\t");
    for(int i = 0; i < m; i++)
    {
        printf("\t%c", i+65);
    }
    printf("\n");
    printf("Available:\t");
    for(int i = 0; i < m; i++)
    {
        printf("\t%d ", avail[i]);
    }
    printf("\n");
    printf("Allocation:\t");
    for(int i = 0; i < m; i++)
    {
        printf("\t%d ", a[p-1][i]);
    }
    printf("\n");
    printf("Need:\t\t");
    for(int i = 0; i < m; i++)
    {
        printf("\t%d ",need[p-1][i]);
    }
    printf("\n");
    printf("Safe state sequenece: <");
    for(int i = 0; i < n; i++)
    {
        printf("P%d ", s[i]);
    }
    printf(">\n");
    printf("Resource requested successfully.\n");
}

int main()
{
    printf("Enter number of process: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d",&m);
    
    
    printf("Enter the allocation of resources\n");
    for(int i = 0; i < n; i++)
    {
        printf("Process P%d: ", i+1);
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    printf("Enter the maximum of resources\n");
    for(int i = 0; i < n; i++)
    {
        printf("Process P%d: ", i+1);
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - a[i][j];
        }
    }
    printf("Enter the available resources\n");
    for(int i = 0; i < m; i++)
    {
        printf("Resource %c: ", i+65);
        scanf("%d", &avail[i]);
    }
    initialise();

    printf("Allocation Matrix:\n");
    print(n,m,a);

    printf("\nMax Matrix:\n");
    print(n,m,max);

    printf("\nNeed Matrix:\n");
    print(n,m,need);

    if(safe_seq()) 
    {
        printf("Unsafe state!!\n");
        exit(1);
    }
    printf("Safe state sequenece: <");
    for(int i = 0; i < n; i++)
    {
        printf("P%d ", s[i]);
    }
    printf(">\n");

    int choice, cont, pro;
    printf("Do you want to request resource? (0/1): ");
    scanf("%d", &choice);
    if(choice ==  1)
    {
        do{
            printf("Enter the process: ");
            scanf("%d", &pro);
            if(pro  > 0 && pro <= n)
            {
                request_res(pro);
            }
            else
            {
                printf("Invalid process requested\n");
                printf("Try again? (0/1) ");
                scanf("%d", &cont);
            }
            printf("Try another? (0/1) ");
            scanf("%d", &cont);
        }while(cont);
    }

    else
    {
        printf("Resource Allocated!\n");
    }
    
    return 0;
}
