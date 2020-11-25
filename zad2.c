#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 512
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
      close (0); //zamknij deskryptor STDIN
      dup (fd[0]); // duplikuj deskryptor  odczytu (koniec czytający pipe'a pojawi się na stdin)


      close(fd[0]);// zamknij odczyt z potoku


      execlp ("display","display", "-", NULL);
     
      
    }

  if (pid < 0) //// ERROR ////
    {
      printf ("Nieudana proba fork");
    }

  
  return 0;
  
}
