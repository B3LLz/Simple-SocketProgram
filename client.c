#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUF 4096

int main(int argc, char** argv){
    int sock, recv_len, port;
    struct sockaddr_in addr;
    char* send_buf = "Hello I am Client!!!\n";
    char buf[MAX_BUF];

    if(argc != 3){
        printf("USAGE: ./client [ip] [port]\n");
    }

    char* ip = argv[1];
    port = atoi(argv[2]);

    /* socket 생성. IPv4 프로토콜(PF_INET)과 TCP(SOCK_STREAM)을 사용. */
    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        return 0;
    }

    /* 주소 정보 setting */
    memset(&addr, 0x00, sizeof(addr));
    addr.sin_family = AF_INET;              // IPv4 주소형식 사용(AF_INET).
    addr.sin_addr.s_addr = inet_addr(ip);   // Server로 접속할 server ip setting.
    addr.sin_port = htons(port);            // 접속될 PORT setting.

    /* Server와 접속 */
    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        perror("connect");
        return 0;
    }

    /* Server로 데이터를 보냄(send) */
    if(send(sock, send_buf, strlen(send_buf), 0) < 0){
        perror("send");
        return 0;
    }

    /* Server로부터 전송된 데이터를 받음(recv) */
    recv_len = recv(sock, buf, sizeof(buf), 0);
    if(recv_len < 0){
        perror("recv");
        return 0;
    }
    printf("%s", buf);

    close(sock);
}