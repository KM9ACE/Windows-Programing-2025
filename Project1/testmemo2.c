#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <Windows.h>  // GetAsyncKeyState 함수 사용을 위해 포함

#define PI 3.14159265358979323846

// 원을 그리는 함수
// x, y : 원 중심 좌표
// r : 반지름
// red, green, blue : RGB 색상값 (0.0 ~ 1.0)
void drawCircle(float x, float y, float r, float red, float green, float blue) {
    int segments = 100;  // 원을 다각형으로 근사할 때 사용할 점 개수

    glColor3f(red, green, blue);  // 색상 설정
    glBegin(GL_TRIANGLE_FAN);     // 삼각형 팬 모드 시작 (중심점 + 주변점으로 원 구성)

    glVertex2f(x, y);             // 중심점 좌표

    // 원 둘레에 점을 찍어 삼각형 팬 구성
    for (int i = 0; i <= segments; i++) {
        // 0 ~ 2π 범위 각도 계산 (원 둘레를 따라)
        float theta = 2.0f * PI * i / segments;

        // 원 둘레 점의 x, y 좌표 계산
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);

        // 중심 좌표에 더해 실제 점 위치 지정
        glVertex2f(x + dx, y + dy);
    }

    glEnd();  // 도형 그리기 종료
}

int main() {
    // GLFW 라이브러리 초기화 (OpenGL 윈도우 생성용)
    if (!glfwInit()) return -1;

    // 800x800 크기의 창 생성, 타이틀 설정
    GLFWwindow* window = glfwCreateWindow(800, 800, "Solar System Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // 만든 창을 현재 OpenGL 컨텍스트로 설정
    glfwMakeContextCurrent(window);

    // 2D 좌표계를 -1부터 1까지로 설정 (왼쪽 아래(-1,-1), 오른쪽 위(1,1))
    glOrtho(-1, 1, -1, 1, -1, 1);

    // 시뮬레이션 시간 변수 (초 단위처럼 사용)
    float time = 0.0f;

    // 메인 루프: 창이 닫히기 전까지 반복
    while (!glfwWindowShouldClose(window)) {
        // 화면 초기화 (버퍼 클리어)
        glClear(GL_COLOR_BUFFER_BIT);

        // --------------------------------
        // 키 상태 확인 (GetAsyncKeyState 사용)
        // --------------------------------
        // VK_RIGHT : 오른쪽 화살표 키 코드
        // VK_LEFT  : 왼쪽 화살표 키 코드
        //
        // GetAsyncKeyState 함수는 해당 키가 눌려있으면 최상위 비트(0x8000)가 1로 세트됨
        SHORT rightKey = GetAsyncKeyState(VK_RIGHT);
        SHORT leftKey = GetAsyncKeyState(VK_LEFT);

        // 오른쪽 키가 눌려있으면 time 증가 (시간 흐름 앞으로)
        if (rightKey & 0x8000) {
            time += 0.01f;  // 증가량 조절 가능
        }
        // 왼쪽 키가 눌려있으면 time 감소 (시간 거꾸로 흐름)
        else if (leftKey & 0x8000) {
            time -= 0.01f;  // 감소량 조절 가능
        }
        // 두 키 모두 안 눌리면 time 고정 (정지)

        // -------------------------------
        // 태양 그리기 (고정 위치)
        // -------------------------------
        // 노란색, 반지름 0.2, 중심 (0,0)
        drawCircle(0.0f, 0.0f, 0.2f, 1.0f, 1.0f, 0.0f);

        // -------------------------------
        // 지구 공전 및 자전 각도 계산
        // -------------------------------
        // 공전: time 값에 비례 (반시계 방향)
        float earthOrbitAngle = time;

        // 자전: 시계 방향이므로 음수로 처리, 속도는 임의로 5배 빠르게 설정
        float earthRotationAngle = -time * 5.0f;

        // 공전 반지름 0.6을 적용해 지구 위치 계산 (태양 중심 기준)
        float earthX = 0.6f * cosf(earthOrbitAngle);
        float earthY = 0.6f * sinf(earthOrbitAngle);

        // -------------------------------
        // 지구 그리기
        // -------------------------------
        glPushMatrix();  // 현재 좌표계 상태 저장

        // 지구 위치로 이동 (태양 중심에서 지구 공전 위치)
        glTranslatef(earthX, earthY, 0);

        // 지구 자전 (Z축 기준 회전)
        glRotatef(earthRotationAngle * 180.0f / PI, 0, 0, 1);

        // 파란색, 반지름 0.1인 지구 원 그리기
        drawCircle(0, 0, 0.1f, 0.0f, 0.0f, 1.0f);

        glPopMatrix();   // 좌표계 복원 (다른 물체에 영향 안 주기 위해)

        // -------------------------------
        // 달 공전 및 자전 각도 계산
        // -------------------------------
        // 달 공전은 지구 공전보다 12배 빠름 (임의 설정)
        float moonOrbitAngle = time * 12.0f;

        // 달 자전도 공전보다 빠른 속도, 시계 방향
        float moonRotationAngle = -time * 12.0f * 5.0f;

        // 달 위치 (지구 기준, 공전 반지름 0.2)
        float moonX = earthX + 0.2f * cosf(moonOrbitAngle);
        float moonY = earthY + 0.2f * sinf(moonOrbitAngle);

        // -------------------------------
        // 달 그리기
        // -------------------------------
        glPushMatrix();

        // 달 위치로 이동
        glTranslatef(moonX, moonY, 0);

        // 달 자전 회전
        glRotatef(moonRotationAngle * 180.0f / PI, 0, 0, 1);

        // 회색, 반지름 0.05인 달 원 그리기
        drawCircle(0, 0, 0.05f, 0.5f, 0.5f, 0.5f);

        glPopMatrix();

        // ---------------------------------
        // 화면 버퍼 교환 및 이벤트 처리
        // ---------------------------------
        glfwSwapBuffers(window);  // 그린 내용을 화면에 표시
        glfwPollEvents();         // 입력 및 창 이벤트 처리
    }

    glfwTerminate();  // GLFW 종료
    return 0;
}
