#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUF 4096
#define PORT 21

int main(int argc, char** argv){
    int sock, client_sock, addr_len, recv_len;
    struct sockaddr_in addr, client_addr;
    char buf[MAX_BUF];
    char* send_buf = "Hello I am Server!!!\n";

    /* socket 생성. IPv4 프로토콜(PF_INET)과 TCP(SOCK_STREAM)을 사용. */
    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        return 0;
    }

    /* 주소 정보 setting */
    memset(&addr, 0x00, sizeof(addr));
    addr.sin_family = AF_INET;                  // IPv4 주소형식 사용(AF_INET).
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   // Client로 부터 접속될 ip setting. 모든 IP로 부터 접속받기 위해 INADDR_ANY 매크로를 사용.
    addr.sin_port = htons(PORT);                // 접속될 PORT setting.

    /* 주소 정보를 소켓에 할당(bind) */
    if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        perror("bind");
        return 0;
    }

    /* Client로 부터 연결 대기(listen) */
    if(listen(sock, 5) < 0){
        perror("listen");
        return 0;
    }
    puts("Waiting Client.....");

    addr_len = sizeof(client_sock);
    /* Client 연결 수락(accept) */
    client_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len); // client_addr 구조체에는 client의 주소 정보가 들어감.

    /* client로부터 전송된 데이터를 받음(recv) */
    recv_len = recv(client_sock, buf, sizeof(buf), 0);
    if(recv_len < 0){
        perror("recv");
        return 0;
    }
    printf("%s", buf);

    /* client로 데이터를 보냄 (send) */
    if(send(client_sock, send_buf, strlen(send_buf), 0) < 0){
        perror("send");
        return 0;
    }

    close(client_sock);
    close(sock);
}