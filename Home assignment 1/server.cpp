#include <stdio.h>
#include <iostream>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <map>
#include <string>
#include <sstream>

#define TRUE   1
#define FALSE  0
#define PORT 8888
 
int main(int argc , char *argv[])
{
    std::map<int,int> mymap;        //defined map
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[30] , max_clients = 30 , activity, i , sd;
    int max_sd;
    struct sockaddr_in serv_addr;
      
    char buffer[256];  //data buffer 256 Bytes
      
    //set of socket descriptors
    fd_set readfds;
      
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) {    client_socket[i] = 0;   }
      
    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  exit(EXIT_FAILURE);
  
    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )    exit(EXIT_FAILURE);
  
    //type of socket created
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( PORT );
      
    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)      exit(EXIT_FAILURE);

   std::cout<<"Listener on port " <<PORT<<std::endl;
     
    //try to specify maximum of 5 pending connections for the master socket
    if (listen(master_socket, 5) < 0)    exit(EXIT_FAILURE);

    //accept the incoming connection
    addrlen = sizeof(serv_addr);


    while(TRUE) 
    {
        //clear the socket set
        FD_ZERO(&readfds);
  
        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;
         
        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
            sd = client_socket[i];
             
            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);
             
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }
  
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
    
          
        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(master_socket, &readfds)) 
        {
            new_socket = accept(master_socket, (struct sockaddr *)&serv_addr, (socklen_t*)&addrlen);
            
            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) 
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;                // printf("Adding to list of sockets as %d\n" , i);
                     
                    break;
                }
            }
        }        

        //else its some IO operation on some other socket :)
        for (i = 0; i < max_clients; i++) 
        {
            sd = client_socket[i];
              
            if (FD_ISSET( sd , &readfds)) 
            {
                //Check if it was for closing , and also read the incoming message
                if ((read( sd , buffer, 255)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&serv_addr , (socklen_t*)&addrlen);                // printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(serv_addr.sin_addr) , ntohs(serv_addr.sin_port));
                      
                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }
                  
            //Now only one left to change state of socket is one transmitting data
                else
                {
            ///Do stuff
                    
                //For Bye
                    if(buffer[0]=='B'&&buffer[1]=='y'&&buffer[2]=='e')  
                    {
                        //Close the socket and mark as 0 in list for reuse
                        write(sd,"Goodbye\n",8);
                        close(sd);
                        client_socket[i] = 0;
                        break;
                                    }
                            
                    //For put
                        else if(buffer[0]=='p' && buffer[1]=='u' && buffer[2]=='t' )
                        {
                            int keyy = buffer[4]-'0';
                            int value = buffer[6]-'0';
                            std::map<int,int>::iterator it = mymap.find(keyy);
                            if(it!=mymap.end())
                            {
                                write(sd,"Key already exists\n",18);
                            }
                            else 
                            {
                                mymap[keyy]=value;
                                write(sd,"OK\n",2);
                            }
                        }

                    //For  del
                    else if(buffer[0]=='d' && buffer[1]=='e' && buffer[2]=='l' )
                    {
                       	int keyy = buffer[4]-'0';
                            std::map<int,int>::iterator it = mymap.find(keyy);
                                
                            if(it!=mymap.end())
                            {
                                mymap.erase(it);
                                write(sd,"OK\n",2);
                            }
                            else 
                            {
                                write(sd,"Key not found\n",13);
                            }
                    }

                   //For  get
                  
                    else if(buffer[0]=='g' && buffer[1]=='e' && buffer[2]=='t' )
                    {
                        int keyy = buffer[4];
                            
                        std::map<int,int>::iterator it = mymap.find(keyy-'0');
                              
                        if(it!=mymap.end()) 
                            {
                                        
                                std::string s;
                                std::stringstream out;
                                out << it->second ;
                                s = out.str();
                                char const *pchar = s.c_str();
                                    
                                send(sd,pchar,1,0);
                            }       
                        else   write(sd,"Key not found\n",14);
                    }
                }
            }
        }
    }
    return 0;
}