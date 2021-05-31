#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class Server_socket{
    ifstream file;

    int PORT;
    
    int general_socket_descriptor;
    int new_socket_descriptor;

    struct sockaddr_in address;
    int address_length;

    public:
        Server_socket(string filename,int port){
            create_socket();
            PORT = port;

            address.sin_family = AF_INET; 
            address.sin_addr.s_addr = INADDR_ANY; 
            address.sin_port = htons( PORT );
            address_length = sizeof(address);

            bind_socket();
            set_listen_set();
            accept_connection();

            file.open(filename, std::ifstream::binary | std::ifstream::in);
            if(file.is_open()){
                cout<<" File opened.\n";
            }
            else{
                cout<<"Error. \n";
                exit(EXIT_FAILURE);
            }
        }

        void create_socket(){
            if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
                perror(" Socket failed");
                exit(EXIT_FAILURE);
            }
            cout<<"Socket Created Successfully.\n";
        }

        void bind_socket(){
            if (bind(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address))<0) {
                perror(" Bind failed");
                exit(EXIT_FAILURE);
            }
            cout<<" Bind Successful.\n";
        }

        void set_listen_set(){
            if (listen(general_socket_descriptor, 3) < 0) {
                perror(" Listen");
                exit(EXIT_FAILURE);
            }
            cout<<"Socket in Listen State (Max Connection Queue: 3)\n";
        }

        void accept_connection(){
            if ((new_socket_descriptor = accept(general_socket_descriptor, (struct sockaddr *)&address, (socklen_t*)&address_length))<0) { 
                perror("Error Accept");
                exit(EXIT_FAILURE);
            }
            cout<<"Connected to Client.\n";
        }

        void transmit_file(){
            std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            cout<<" Transmission Data Size "<<contents.length()<<" Bytes.\n";                   

            int bytes_sent = send(new_socket_descriptor , contents.c_str() , contents.length() , 0 );
            cout<<"Transmitted Data Size "<<bytes_sent<<" Bytes.\n";

            }
};

int main(){
    Server_socket S1("pic1.JPG",8050);
    Server_socket S2("pic2.jpg",8051);
    Server_socket S3("pic3.jpg",8052);
    
    S1.transmit_file();
    S2.transmit_file();
    S3.transmit_file();
    
    return 0;
}
