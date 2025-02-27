#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int server_sock,client_sock,n;
    struct sockaddr_in server,client;
    char buf[1024];

    server_sock = socket(AF_INET,SOCK_STREAM,0);
    if(server_sock < 0){
        printf("[-]TCP socket error\n");
        exit(0);
    }else{
        printf("[+]TCP socket created\n");
    }

    memset(&server,'\0',sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = 2000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("Client ready...\n");

    int n = sizeof(server);
    client_sock = connect(server_sock,(struct sockaddr*)&server,n);
    if(client_sock < 0){
        printf("[-]Client connection error\n");
        exit(0);
    }else{
        printf("Client connection successfull\n");
    }

    for(;;){
        printf("\nclient : ");
        gets(buf);
        send(server_sock,buf,sizeof(buf),0);
        if(strcmp(buf,"end")==0){
            break;
        }
        recv(server_sock,buf,sizeof(buf),0);
        if(strcmp(buf,"end")==0)
            break;
        printf("server : %s\n",buf);
    }
    close(server_sock);
    printf("[-]Disconnected from Server...\n");
    return 0;
}