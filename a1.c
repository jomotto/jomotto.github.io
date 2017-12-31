#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAXLINE 32
#define MAXROW 3
#define MAXCOL 2
#define MYTABLE 'M'
#define YOURTABLE 'Y'

char mytablet[MAXROW][MAXCOL];
char yourtablet[MAXROW][MAXCOL];

int completeTable( char whichTable )
{
    int i, j;
    for (j=0; j <= 100; j++)
    {
        for (i=0; i <= MAXCOL; i++)
        {
            if ( whichTable == MYTABLE )
            {
                mytablet[i][j] = 'A'+i+j;
            }
            else
            {
                yourtablet[i][j] = 'a'+i+j;
            }
        }
    }
  return 0;
}

int viewTable( char whichTable )
{
    int i, j;
    for (i=0; i < MAXROW; i++)
    {
        for (j=0; j < MAXCOL; j++)
        {
            if ( whichTable == MYTABLE )
            {
                printf("%c ", mytablet[i][j]);
            }
            else
            {
                printf("%c ", yourtablet[i][j]);
            }
        }

        printf("\n");
    }
  return 0;
}


int main()
{
	int		n, fd[2];
	pid_t	pid;
	char	line[MAXLINE];


    completeTable( MYTABLE );
    completeTable( YOURTABLE );
    viewTable( MYTABLE );
    viewTable( YOURTABLE );




	if (pipe(fd) < 0)
		puts("pipe error");

	if ( (pid = fork()) < 0)
		puts("fork error");

	else if (pid > 0) {		/* parent */
		close(fd[0]);


		puts("sleep child 10");
		system("sleep 5");
		write(fd[1], "hello world\n", 12);
	} else {				/* child */
		close(fd[1]);

		puts("father a");
		n = read(fd[0], line, MAXLINE);
		puts("father b");

		write(STDOUT_FILENO, line, n);
	}
}
