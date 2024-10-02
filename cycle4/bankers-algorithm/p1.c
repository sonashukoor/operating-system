#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10
#define MAX_INSTANCES 20

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int work[MAX_RESOURCES];
int finish[MAX_PROCESSES];
int safe_sequence[MAX_PROCESSES];

int n_processes;
int n_resources;
int n_instances[MAX_INSTANCES];

void input_data()
{
    int i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &n_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &n_resources);

    printf("Enter the Instances of each  resources:\n");
    for (i = 0; i < n_resources; i++)
        {printf("Resource %d::",i+1);
         scanf("%d", &n_instances[i]);
        }

    printf("Enter the maximum demand of each process:\n");
    for (i = 0; i < n_processes; i++)
    {
        printf("For process %d: ", i);
        for (j = 0; j < n_resources; j++)
            scanf("%d", &maximum[i][j]);
    }

    printf("Enter the allocated resources of each process:\n");
    for (i = 0; i < n_processes; i++)
    {
        printf("For process %d: ", i);
        for (j = 0; j < n_resources; j++)
        {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
  for(i=0;i<n_resources;i++)
    available[i]=0;
    
  for(i=0;i<n_resources;i++)
    {for(j=0;j<n_processes;j++)
      {available[i]+=allocation[j][i];
      }
    }
  printf("\nAvailable Matrix:");
  for(i=0;i<n_resources;i++)
    {available[i]=n_instances[i]-available[i];
     printf("  %d",available[i]);
    }
  
}

void init()
{
    int i, j;

    for (i = 0; i < n_processes; i++)
        finish[i] = 0;

    for (j = 0; j < n_resources; j++)
        work[j] = available[j];
}

int find_safe_sequence()
{
    int i, j, k, found;
    int count = 0;

    init();

    while (count < n_processes)
    {
        found = 0;

        for (i = 0; i < n_processes; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < n_resources; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == n_resources)
                {
                    for (k = 0; k < n_resources; k++)
                        work[k] += allocation[i][k];

                    finish[i] = 1;
                    safe_sequence[count++] = i;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    return count == n_processes;
}

void print_need_matrix()
{
    int i, j;

    printf("Need Matrix:\n");
    for (i = 0; i < n_processes; i++)
    {
        printf("Process %d: ", i);
        for (j = 0; j < n_resources; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}

void print_safe_sequence()
{
    int i;

    printf("Safe Sequence: ");
    for (i = 0; i < n_processes; i++)
        printf("P%d ", safe_sequence[i]);
    printf("\n");
}

int is_request_granted(int process, int request[])
{
    int i, j;

    for (i = 0; i < n_resources; i++)
    {
        if (request[i] > need[process][i] || request[i] > available[i])
            return 0;
    }

    for (i = 0; i < n_resources; i++)
    {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (find_safe_sequence())
        return 1;

    for (i = 0; i < n_resources; i++)
    {
        available[i] += request[i];
        allocation[process][i] -= request[i];
        need[process][i] += request[i];
    }

    return 0;
}

int main()
{
    int i, process;
    int request[MAX_RESOURCES];

    input_data();

    if (find_safe_sequence())
    {
        printf("\n\nSystem is in a safe state.\n\n");
        print_need_matrix();
        print_safe_sequence();
    }
    else
    {
        printf("\n\nSystem is in an unsafe state.\n\n");
        return 0;
    }

    printf("Enter the process number (0-%d) for resource request: ", n_processes - 1);
    scanf("%d", &process);

    printf("Enter the resource request for process %d:\n", process);
    for (i = 0; i < n_resources; i++)
        scanf("%d", &request[i]);

    if (is_request_granted(process, request))
        printf("Request is granted.\n");
    else
        printf("Request is denied.\n");

    return 0;
}
