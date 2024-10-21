#include "ServerFunction.h"

int main() {
    Daemonize();        // 1. 서버 데몬화
    MakeSocket();       // 2. 소켓 생성
    SetSocketOption();  // 3. 소켓 옵션 설정
    BindAddress();      // 4. 주소 설정 및 바인딩
    SetWaitingMode();   // 5. 클라이언트 대기 상태 설정
    ServerService();    // 6. 서버 운영
    WaitForThreadEnd(); // 7. 모든 스레드 종료 대기
    return 0;
}