#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>  // GLFW 라이브러리 (창 생성, 입력, OpenGL 컨텍스트 관리)
#include <math.h>        // 삼각함수 등 수학 함수
#include <windows.h>     // GetAsyncKeyState 함수 사용 (윈도우 키 입력 감지)

// M_PI가 정의되어 있지 않을 경우를 대비해 직접 정의 (파이 값)
#define M_PI 3.14159265358979323846

// 윈도우 크기 지정
int windowWidth = 800;
int windowHeight = 600;

// 윙크 상태 플래그 (0 = 윙크 아님, 1 = 윙크)
int isWinking = 0;

// 얼굴 모드 변수 (1=원, 2=사각, 3=삼각, 4=타원, 5=다이아몬드)
int faceMode = 1;

// 원을 그리는 함수
// cx, cy : 원 중심 좌표
// r : 반지름
// num_segments : 원을 근사할 점 개수 (클수록 부드러운 원)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);  // 삼각형 팬 모드 시작 (중심에서 주변 점들로 채움)
    glVertex2f(cx, cy);        // 중심점
    for (int i = 0; i <= num_segments; ++i) {
        // 각도를 0부터 2파이까지 균등 분할
        float angle = 2.0f * M_PI * i / num_segments;
        // 원주 위 점 좌표 계산
        float x = cx + cosf(angle) * r;
        float y = cy + sinf(angle) * r;
        glVertex2f(x, y);      // 원주 위 점 지정
    }
    glEnd();
}

// 사각형 그리기 함수
// cx, cy : 사각형 중심 좌표
// size : 한 변의 길이
void drawSquare(float cx, float cy, float size) {
    float half = size / 2.0f;  // 중심에서 한 변 끝까지 거리
    glBegin(GL_QUADS);         // 사각형 그리기 시작
    glVertex2f(cx - half, cy - half);  // 왼쪽 아래
    glVertex2f(cx + half, cy - half);  // 오른쪽 아래
    glVertex2f(cx + half, cy + half);  // 오른쪽 위
    glVertex2f(cx - half, cy + half);  // 왼쪽 위
    glEnd();
}

// 삼각형 그리기 함수 (정삼각형이 아니라 정방향 삼각형)
// cx, cy : 삼각형 중심 좌표
// size : 밑변 길이
void drawTriangle(float cx, float cy, float size) {
    float half = size / 2.0f;  // 밑변의 반 길이
    glBegin(GL_TRIANGLES);     // 삼각형 그리기 시작
    glVertex2f(cx, cy + half);      // 위쪽 꼭짓점
    glVertex2f(cx - half, cy - half); // 왼쪽 아래 꼭짓점
    glVertex2f(cx + half, cy - half); // 오른쪽 아래 꼭짓점
    glEnd();
}

// 타원 그리기 함수
// cx, cy : 타원 중심 좌표
// rx, ry : x축과 y축 반지름
// num_segments : 타원을 근사할 점 개수
void drawEllipse(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);  // 삼각형 팬 모드 시작
    glVertex2f(cx, cy);        // 중심점
    for (int i = 0; i <= num_segments; ++i) {
        float angle = 2.0f * M_PI * i / num_segments;
        float x = cx + cosf(angle) * rx;  // x축 방향 반지름 적용
        float y = cy + sinf(angle) * ry;  // y축 방향 반지름 적용
        glVertex2f(x, y);
    }
    glEnd();
}

// 다이아몬드 모양 그리기 함수 (사각형을 45도 회전한 모양)
// cx, cy : 다이아몬드 중심 좌표
// size : 대각선 길이 (가로 및 세로)
void drawDiamond(float cx, float cy, float size) {
    float half = size / 2.0f;  // 중심에서 꼭짓점까지 거리
    glBegin(GL_QUADS);         // 사각형 그리기 시작
    glVertex2f(cx, cy + half);    // 위쪽 꼭짓점
    glVertex2f(cx + half, cy);    // 오른쪽 꼭짓점
    glVertex2f(cx, cy - half);    // 아래쪽 꼭짓점
    glVertex2f(cx - half, cy);    // 왼쪽 꼭짓점
    glEnd();
}

// 얼굴 전체 그리기 함수
// faceMode 값에 따라 다양한 모양 그리기
void drawFace() {
    glColor3f(1.0f, 1.0f, 0.0f);  // 노란색 설정
    switch (faceMode) {
    case 1: drawCircle(0.0f, 0.0f, 0.8f, 360); break;      // 원
    case 2: drawSquare(0.0f, 0.0f, 1.6f); break;           // 사각형
    case 3: drawTriangle(0.0f, 0.0f, 1.6f); break;          // 삼각형
    case 4: drawEllipse(0.0f, 0.0f, 0.8f, 0.5f, 360); break; // 타원
    case 5: drawDiamond(0.0f, 0.0f, 1.6f); break;           // 다이아몬드
    }
}

// 눈 그리기 함수
// 윙크 상태에 따라 오른쪽 눈 모양 변경
void drawEyes() {
    glLineWidth(5.0f);             // 선 굵기 5.0으로 설정
    glColor3f(0.0f, 0.0f, 0.0f);  // 검정색

    // 왼쪽 눈: 단순한 선으로 표시
    glBegin(GL_LINES);
    glVertex2f(-0.3f, 0.3f);       // 왼쪽 끝
    glVertex2f(-0.2f, 0.3f);       // 오른쪽 끝
    glEnd();

    // 오른쪽 눈
    glBegin(GL_LINES);
    if (isWinking) {
        // 윙크 상태: '<' 모양으로 눈을 표현 (두 개의 선분)
        glVertex2f(0.2f, 0.32f);
        glVertex2f(0.25f, 0.3f);

        glVertex2f(0.25f, 0.3f);
        glVertex2f(0.2f, 0.28f);
    }
    else {
        // 정상 상태: 단순 선으로 눈 표현
        glVertex2f(0.2f, 0.3f);
        glVertex2f(0.3f, 0.3f);
    }
    glEnd();
}

// 웃는 입 그리기 함수
// 반원 형태로 선을 연결하여 웃는 입 모양 생성
void drawSmile() {
    glColor3f(0.0f, 0.0f, 0.0f);   // 검정색
    glLineWidth(5.0f);             // 선 굵기 5.0
    glBegin(GL_LINE_STRIP);        // 연결된 선 그리기 시작
    for (int i = 0; i <= 180; ++i) {
        // 0 ~ 180도까지 각도 생성 (0~파이 라디안)
        float angle = M_PI * i / 180.0f;
        // x는 반원의 반지름 * cos(각도)
        float x = 0.4f * cosf(angle);
        // y는 -0.4 * sin(각도) + 아래로 약간 이동(-0.2)
        float y = -0.4f * sinf(angle) - 0.2f;
        glVertex2f(x, y);
    }
    glEnd();
}

int main() {
    // GLFW 초기화 (실패 시 프로그램 종료)
    if (!glfwInit()) return -1;

    // 윈도우 생성 (크기 800x600, 제목 "Multi-Face Wink Extended")
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Multi-Face Wink Extended", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // 현재 스레드의 OpenGL 컨텍스트로 설정

    // 메인 루프: 창이 닫힐 때까지 반복
    while (!glfwWindowShouldClose(window)) {
        // GetAsyncKeyState로 키 상태 체크
        // 'W'키가 눌리면 윙크 상태로 변경, 아니면 해제
        if (GetAsyncKeyState('W') & 0x8000) isWinking = 1;
        else isWinking = 0;

        // 숫자키 1~5 눌림 여부에 따라 얼굴 모양 변경
        if (GetAsyncKeyState('1') & 0x8000) faceMode = 1;
        if (GetAsyncKeyState('2') & 0x8000) faceMode = 2;
        if (GetAsyncKeyState('3') & 0x8000) faceMode = 3;
        if (GetAsyncKeyState('4') & 0x8000) faceMode = 4;
        if (GetAsyncKeyState('5') & 0x8000) faceMode = 5;

        glClear(GL_COLOR_BUFFER_BIT);  // 화면 지우기

        drawFace();   // 얼굴 모양 그리기
        drawEyes();   // 눈 그리기 (윙크 상태 반영)
        drawSmile();  // 웃는 입 그리기

        glfwSwapBuffers(window);  // 버퍼 교체 (화면에 표시)
        glfwPollEvents();         // 이벤트 처리 (키보드 등)
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}
