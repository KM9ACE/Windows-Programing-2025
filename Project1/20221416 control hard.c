//이전에 누른 적이 없고 호출 시점에서 안눌린 상태 : 0 (0x0000)
//이전에 누른 적이 없고 호출 시점에서 눌린 상태 : 0x8000
//이전에 누른 적이 있고 호출 시점에서 눌린 상태 : 0x8001
//이전에 누른 적이 있고 호출 시점에서 안눌린 상태 : 1 (0x0001)
#include <windows.h>
#include <stdio.h>

int main() 
{
    while (1) 
    {
        // W 키가 눌렸는지 확인 (key down)
        if (GetAsyncKeyState(0x57) & 0x8000)
        {
            printf("W 키 눌림 (Key Down)\n");
        }

        // S 키가 눌렸는지 확인 (key down)
        if (GetAsyncKeyState(0x53) & 0x8000)
        {
            printf("S 키 눌림 (Key Down)\n");
        }

        // W 키가 떼어졌는지 확인 (key up)
        if (!(GetAsyncKeyState(0x57) & 0x8000))
        {
            printf("W 키 떼어짐 (Key Up)\n");
        }

        // S 키가 떼어졌는지 확인 (key up)
        if (!(GetAsyncKeyState(0x53) & 0x8000))
        {
            printf("S 키 떼어짐 (Key Up)\n");
        }       
      
        // 프로그램 종료 조건
        if (GetAsyncKeyState(0x51) & 0x8000)
        {
            printf("게임 종료\n");
            break;  // Q 키를 누르면 종료
        }
        // 잠시 대기 (CPU 사용 최적화)
        Sleep(100);
    }

    return 0;
}