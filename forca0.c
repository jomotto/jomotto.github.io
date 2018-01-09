#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX 2
#define MAXLINE 32
#define MAXROW 3
#define MAXCOL 2
#define MYTABLE 'M'
#define YOURTABLE 'Y'

int mytablet[MAXROW][MAXCOL];
int yourtablet[MAXROW][MAXCOL];

int completeTable( char whichTable, char who )
{
    int    i, j;
    int    aleatorio;
    time_t start, now;


    for (j=0; j <= MAXROW; j++)
    {
        for (i=0; i <= MAXCOL; i++)
        {
            if ( whichTable == MYTABLE )
            {
		time(&start);
		if ( who == 'P' )
		{
			do
			{
				time(&now);
			} while( !difftime(now,start ));
		}
		else
		{

			do
			{
				time(&now);
			} while( difftime(now,start ) > 2);
		}

		srand(time(NULL));

		aleatorio = rand()%MAX;

                mytablet[i][j] = aleatorio;
            }
            else
            {
                yourtablet[i][j] = -1;
            }
        }
    }
    return 0;
}

int viewTable( char whichTable, char who )
{
    int i, j;

    printf("<%c>\n", who);
    for (i=0; i < MAXROW; i++)
    {
        for (j=0; j < MAXCOL; j++)
        {
            if ( whichTable == MYTABLE )
            {
                printf("%d ", mytablet[i][j]);
            }
            else
            {
                printf("%d ", yourtablet[i][j]);
            }
        }

        printf("\n");
    }
    return 0;
}

int child(int fd0, int fd1)
{

	int		n, fd[2];
	pid_t	pid;
	char	linep[MAXLINE];
	char	linec[MAXLINE];
  int index;
  int aleatorio;

		srand(time(NULL));

		aleatorio = rand();
		index = aleatorio%MAX;

		n = read(fd0, linec, 1);
                if (*linec == 'I')
               {
                sprintf(linec, "%d", index);

		printf("CHILD %s\n", linec);
		write(fd1, linec, 1);
                }

  return 0;
}


int parent(int fd0, int fd1)
{
	int		n;
	char	linep[MAXLINE];

	write(fd1, "I", 1);
	system("sleep 1");

	n = read(fd0, linep, 1);

	printf("PT %s\n", linep);
  return 0;
}

int main()
{
	int		n, fd[2];
	pid_t	pid;
	char	linep[MAXLINE];
	char	linec[MAXLINE];
     int index;
     int aleatorio;
     pid_t   pid2;
     int     status;




	if (pipe(fd) < 0)
		puts("pipe error");

	if ( (pid = fork()) < 0)
		puts("fork error");

	else if (pid > 0) {		/* parent */


           completeTable( MYTABLE, 'P');
           completeTable( YOURTABLE, 'P' );
           viewTable( MYTABLE, 'P' );
           viewTable( YOURTABLE, 'P' );

                parent( fd[0], fd[1]);
            printf("Espero mi pollo\n");
            if(pid != waitpid(pid, NULL, 0))
               printf("waitpid error %d\n", pid);
            printf("sali del hijo\n");

	} else {				/* child */

            completeTable( MYTABLE, 'C' );
            completeTable( YOURTABLE, 'C' );
            viewTable( MYTABLE, 'C' );
            viewTable( YOURTABLE, 'C' );

		child(fd[0], fd[1]);
                exit(0);
	}
}
