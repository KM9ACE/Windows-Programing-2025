#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <windows.h> // GetAsyncKeyState 함수 사용 위해 포함
#include <math.h>

// 전역 변수: 윙크 상태와 얼굴 모양 선택 변수
int isWink = 0;      // 0: 윙크 아님, 1: 윙크 상태
int faceShape = 0;   // 0=원, 1=사각형, 2=삼각형, 3=타원

// ------------------- 얼굴 도형 그리기 함수들 -------------------

// 원을 삼각형 팬으로 그리는 함수
// cx, cy: 원 중심 좌표
// r: 반지름
// num_segments: 원을 근사할 점 개수 (클수록 부드러움)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);  // 노란색 얼굴색 지정
    glVertex2f(cx, cy);            // 중심점 먼저 그리기
    for (int i = 0; i <= num_segments; i++) {
        // 각 점의 각도를 0 ~ 2π 범위에서 균등 분할
        float theta = 2.0f * 3.14159265358979323846f * i / num_segments;
        // 원의 x, y 좌표 계산
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        // 중심 좌표에 상대 좌표 더해서 꼭짓점 지정
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// 타원을 삼각형 팬으로 그리는 함수
// rx, ry: x축과 y축 방향 반지름
// 나머지 파라미터는 원과 동일
void drawEllipse(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);  // 노란색 얼굴색
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.14159265358979323846f * i / num_segments;
        // 원과 달리 x와 y에 서로 다른 반지름 적용
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// 사각형 얼굴 그리기 함수
// cx, cy: 중심 좌표, size: 한 변 길이
void drawSquareFace(float cx, float cy, float size) {
    float half = size / 2.0f; // 반 변 길이 계산
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);  // 노란색 얼굴색
    // 시계방향으로 사각형 네 꼭짓점 지정
    glVertex2f(cx - half, cy - half);
    glVertex2f(cx + half, cy - half);
    glVertex2f(cx + half, cy + half);
    glVertex2f(cx - half, cy + half);
    glEnd();
}

// 삼각형 얼굴 그리기 함수 (정삼각형)
// cx, cy: 중심 좌표, size: 변의 길이
void drawTriangleFace(float cx, float cy, float size) {
    float height = size * 0.866f; // 정삼각형 높이 (sqrt(3)/2 * size)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);  // 노란색 얼굴색
    // 위 꼭짓점 (중심 위쪽)
    glVertex2f(cx, cy + height / 2);
    // 왼쪽 아래 꼭짓점
    glVertex2f(cx - size / 2, cy - height / 2);
    // 오른쪽 아래 꼭짓점
    glVertex2f(cx + size / 2, cy - height / 2);
    glEnd();
}

// ------------------- 단순 선 그리기 함수 -------------------
// x1,y1 부터 x2,y2 까지 직선을 그린다
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// ------------------- 얼굴 모양에 따른 얼굴 그리기 분기 -------------------
void drawFaceShape(int shape) {
    switch (shape) {
    case 0: // 원형 얼굴
        drawCircle(0.0f, 0.0f, 0.8f, 360);
        break;
    case 1: // 사각형 얼굴
        drawSquareFace(0.0f, 0.0f, 1.6f);
        break;
    case 2: // 삼각형 얼굴
        drawTriangleFace(0.0f, 0.0f, 1.6f);
        break;
    case 3: // 타원 얼굴 (가로 길고 세로는 반 정도)
        drawEllipse(0.0f, 0.0f, 0.8f, 0.5f, 360);
        break;
    default: // 기본 원형 얼굴
        drawCircle(0.0f, 0.0f, 0.8f, 360);
    }
}

// ------------------- 스마일 맨 그리기 -------------------
// wink: 1이면 오른쪽 눈 윙크, 0이면 정상 눈
// shape: 얼굴 모양 번호
void drawSmileMan(int wink, int shape) {
    // 얼굴 그리기
    drawFaceShape(shape);

    glColor3f(0.0f, 0.0f, 0.0f); // 눈과 입은 검은색

    // 왼쪽 눈 (항상 정상 눈 모양)
    drawLine(-0.3f, 0.3f, -0.2f, 0.4f);
    drawLine(-0.2f, 0.4f, -0.1f, 0.3f);

    // 오른쪽 눈 (윙크 여부에 따라 다르게 그림)
    if (wink) {
        // 윙크 눈은 '<' 모양 (대각선 두 줄)
        drawLine(0.2f, 0.3f, 0.1f, 0.4f);
        drawLine(0.1f, 0.4f, 0.0f, 0.3f);
    }
    else {
        // 정상 눈 모양
        drawLine(0.1f, 0.3f, 0.2f, 0.4f);
        drawLine(0.2f, 0.4f, 0.3f, 0.3f);
    }

    // 웃는 입 모양 (세 선으로 표현)
    drawLine(-0.3f, -0.3f, -0.1f, -0.5f);
    drawLine(-0.1f, -0.5f, 0.1f, -0.5f);
    drawLine(0.1f, -0.5f, 0.3f, -0.3f);
}

// ------------------- 키보드 입력 콜백 -------------------
// GLFW가 키 입력을 감지하면 호출되는 함수
// 윙크 상태와 얼굴 모양 변경 키 처리
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // W 키 눌림/반복 시 윙크 상태로 변경
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        isWink = 1;
    }
    // W 키 떼면 윙크 해제
    if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
        isWink = 0;
    }

    // 숫자키 1~4로 얼굴 모양 변경 (눌린 순간만)
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_1) faceShape = 0; // 원형 얼굴
        if (key == GLFW_KEY_2) faceShape = 1; // 사각형 얼굴
        if (key == GLFW_KEY_3) faceShape = 2; // 삼각형 얼굴
        if (key == GLFW_KEY_4) faceShape = 3; // 타원 얼굴
    }
}

// ------------------- main 함수 -------------------
int main(void) {
    // GLFW 초기화 실패시 종료
    if (!glfwInit())
        return -1;

    // 800x600 고정 크기 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "Smile Man Wink - Face Shape + Ellipse", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // 2D 직교 좌표계 설정: 좌우, 상하 -1 ~ 1
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    // 키 입력 콜백 등록
    glfwSetKeyCallback(window, key_callback);

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // GetAsyncKeyState로 W키 상태 실시간 체크
        // (키 콜백에서 놓친 경우 보완용)
        if ((GetAsyncKeyState('W') & 0x8000) != 0) {
            isWink = 1;
        }
        else {
            isWink = 0;
        }

        // 현재 상태에 맞게 스마일 맨 그리기
        drawSmileMan(isWink, faceShape);

        glfwSwapBuffers(window); // 화면 업데이트
        glfwPollEvents();        // 이벤트 처리
    }

    // 종료 전 리소스 해제
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
