#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 6
int main(int argc, char* argv[])
{
  int fd[2];
  char buf[BUFSIZE];
  int open_fd, pid, size;

  if (pipe(fd) < 0)
    {
      printf("Błąd-  nie utworzono pipe'a");
    }

  pid = fork();

  if (pid > 0)   //// KOD RODZICA ////
    {
      close (fd[0]);   //brak dostepu do odczytu
      open_fd = open (argv[1], O_RDONLY);    //Otwarcie pliku tekstowego

      while (read(open_fd, &buf, BUFSIZE) > 0)
	{
	  write(fd[1], &buf, BUFSIZE);  
	}
	
      close(fd[1]); // zamknij zapis do potoku
	  
     
      
    }

  if (pid == 0) //// KOD DZIECKA ////
    {
      close (fd[1]); //brak dostepu do zapisu
     
      while ( read( fd[0], &buf, BUFSIZE )> 0)
	{
	  write (1, "#", 1);
	  write (1, &buf, BUFSIZE);
	  write (1, "#", 1);
	}

      close(fd[0]);// zamknij odczyt z potoku

     
      
    }

  if (pid < 0) //// ERROR ////
    {
      printf ("Nieudana proba fork");
    }

  
  return 0;
  
}
