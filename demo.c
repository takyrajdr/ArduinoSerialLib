#include <stdio.h> 
#include <string.h>
#include <unistd.h>  
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

/* change this definition for the correct port */
#define DEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1


int open_port(void){
  int fd; /* File descriptor for the port */
  fd = open( DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1){
    fprintf(stderr,"open_port: Unable to open serial port - \n");
    return 1;
  }
  else
    fcntl(fd, F_SETFL, 0); //blocking mode - waits for data in input buffer
  //port opened
  //now set options
  struct termios options; //port optinons
  /*
   * Get the current options for the port...
   */
  tcgetattr(fd, &options);

  /*
   * Set the baud rates to 19200...
   */
  cfsetispeed(&options, B19200);
  cfsetospeed(&options, B19200);
  /*
   * Enable the receiver and set local mode...
   */
  options.c_cflag |= (CLOCAL | CREAD);
  /*
   * Set the new options for the port...
   */
  tcsetattr(fd, TCSANOW, &options);  
  //baudrates set
  //byte size
  options.c_cflag &= ~CSIZE; /* Mask the character size bits */
  options.c_cflag |= CS8;    /* Select 8 data bits */
  //no parity
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  /*
   * raw input mode
   */
   options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  return (fd);
}



int main(){
  unsigned char buffer [100];
  int port = open_port();
  sleep(1);
  int j = 0;
  while( 1 ){
    j++;
    int n = read (port, buffer, 100);  // read up to 100 characters if ready to read
    /*if( n > 0 ){
      usleep(100);
      printf("\nRead %d bytes in %d. round\n",n,j );
    }*/
    for (int i = 0; i < n; ++i){
      printf("%c",buffer[i] );  
    }
    //printf("buffer empty\n");
  }  
  return 0;

}    