#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class Client_socket{
    fstream file;

    int PORT;
    
    int general_socket_descriptor;

    struct sockaddr_in address;
    int address_length;

    public:
        Client_socket(string filename, int port){
            create_socket();
            PORT = port;

            address.sin_family = AF_INET;
            address.sin_port = htons( PORT );
            address_length = sizeof(address);
            if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0) { 
                cout<<"Invalid address\n";
            }

            create_connection();
            
            file.open(filename, std::fstream::out);
            if(file.is_open()){
                cout<<" File Created.\n";
            }
            else{
                cout<<" File creation failed, Exititng.\n";
                exit(EXIT_FAILURE);
            }
        }

        void create_socket(){
            if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
                perror("Socket failed.\n");
                exit(EXIT_FAILURE);
            }
            cout<<"Socket Created Successfully.\n";
        }

        void create_connection(){
            if (connect(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address)) < 0) { 
                perror(" connection attempt failed.\n");
                exit(EXIT_FAILURE);
            }
            cout<<"Connection Successfull.\n";
        }

        void receive_file(){
            char buffer[1024] = {};
            //int valread = read(general_socket_descriptor , buffer,1024);
            int valread;
             while ((valread = read(general_socket_descriptor, buffer, sizeof(buffer)-1)) > 0)
             {
                cout<<" Data received "<<valread<<" bytes\n";
                       
                file<<buffer;
              
             }    


        }
};

int main(){
    Client_socket C1("rcv1.JPG",8050);
    Client_socket C2("rcv2.JPG",8051);
    Client_socket C3("rcv3.JPG",8052);
    
    C1.receive_file();
    C2.receive_file();
    C3.receive_file();
    
    return 0;
}
