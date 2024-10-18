#ifndef SERVER_FUNCTION_H
#define SERVER_FUNCTION_H

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int server_fd;
struct sockaddr_in address;
int opt = 1;
int addrlen;
vector<thread> threads;

void Daemonize(); // 1. 서버 데몬화
void MakeSocket(); // 2. 소켓 생성
void SetSocketOption(); // 3. 소켓 옵션 설정
void BindAddress(); // 4. 주소 설정 및 바인딩
void SetWaitingMode(); // 5. 클라이언트 대기 상태 설정
void ServerService(); // 6. 서버 운영
void HandleClient(int clientSocket); // 6-(2) 클라이언트 요청 처리
void WaitForThreadEnd(); // 7. 모든 스레드 종료 대기

#endif