/*
 * GLFW + OpenGL 1.1 애니메이션 데모
 * - 오른쪽에 스마일맨(원 + 눈 + 웃는 입) 배치
 * - 스마일맨은 화면 중심을 기준으로 공전
 * - 얼굴(눈/입)은 자전 공전에 반대 방향으로 회전해 항상 수평 유지
 * - 스마일맨 주변에 육망성(별)이 공전하며 자체적으로 빠르게 자전
 */

#include <GLFW/glfw3.h>
#include <math.h>

#pragma comment(lib, "opengl32.lib")

#define PI 3.1415926535f

 // 원 그리기: 반지름 r, 세그먼트 수 seg
void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);            // 중심
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);
    }
    glEnd();
}

// 스마일맨 얼굴(눈 + 입) 그리기
void drawFace(float eyeR, float eyeOffsetX, float eyeOffsetY) {
    // 왼쪽 눈
    glPushMatrix();
    glTranslatef(-eyeOffsetX, eyeOffsetY, 0.0f);
    drawCircle(eyeR, 16);
    glPopMatrix();

    // 오른쪽 눈
    glPushMatrix();
    glTranslatef(eyeOffsetX, eyeOffsetY, 0.0f);
    drawCircle(eyeR, 16);
    glPopMatrix();

    // 웃는 입 (반원 아크)
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 20; ++i) {
        // -30° .. -150° 사이
        float a = (-30.0f - 120.0f * i / 20.0f) * (PI / 180.0f);
        glVertex2f(cosf(a) * 0.5f * eyeOffsetX, sinf(a) * 0.5f * eyeOffsetY);
    }
    glEnd();
}

// 육망성(별) 그리기: 반지름 r
void drawHexagram(float r) {
    float h = r * 0.866f; // sqrt(3)/2 * r
    glBegin(GL_TRIANGLES);
    // 윗 삼각형
    glVertex2f(0.0f, r);
    glVertex2f(-h, -r * 0.5f);
    glVertex2f(h, -r * 0.5f);
    // 아랫 삼각형 (역방향)
    glVertex2f(0.0f, -r);
    glVertex2f(-h, r * 0.5f);
    glVertex2f(h, r * 0.5f);
    glEnd();
}

int main(void) {
    // 1) GLFW 초기화
    if (!glfwInit()) return -1;

    // 2) 윈도우 생성 & 컨텍스트 바인딩
    GLFWwindow* window = glfwCreateWindow(800, 600, "Smiley Orbit & Hexagram", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // 3) 2D 직교 투영 설정 (좌표계 -1..1)
    glOrtho(-1, 1, -1, 1, -1, 1);

    // 애니메이션 파라미터
    const float smileOrbitR = 0.6f;   // 스마일맨 공전 반경
    const float smileRadius = 0.15f;  // 스마일맨 얼굴 반경
    const float eyeR = 0.02f;         // 눈 반경
    const float eyeOffX = 0.05f,
        eyeOffY = 0.07f;      // 눈 위치 오프셋
    const float hexOrbitR = 0.3f;     // 육망성 공전 반경
    const float hexRadius = 0.07f;    // 육망성 크기

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        float t = (float)glfwGetTime();

        // 공전/자전 각도 계산
        float smileOrbitAng = t * 20.0f;     // 스마일맨 공전 속도
        float hexOrbitAng = t * 60.0f;     // 별 공전 속도 (빠름)
        float hexSelfAng = t * 200.0f;    // 별 자체 자전 속도 (더 빠름)

        // 4) 화면 클리어
        glClear(GL_COLOR_BUFFER_BIT);

        // 5) 스마일맨 공전 궤도
        glPushMatrix();
        glRotatef(smileOrbitAng, 0, 0, 1);                // 중심 기준 공전
        glTranslatef(smileOrbitR, 0.0f, 0.0f);          // 궤도 반경만큼 이동

        // 얼굴 그리기
        glColor3f(1.0f, 1.0f, 0.0f);                    // 노랑 얼굴
        drawCircle(smileRadius, 64);

        // 얼굴 특징(눈/입)은 역회전으로 수평 유지
        glPushMatrix();
        glRotatef(-smileOrbitAng, 0, 0, 1);
        glColor3f(0.0f, 0.0f, 0.0f);                  // 눈/입 검정
        drawFace(eyeR, eyeOffX, eyeOffY);
        glPopMatrix();

        // 6) 육망성 공전 & 자전
        glPushMatrix();
        glRotatef(hexOrbitAng, 0, 0, 1);                // 스마일맨 기준 공전
        glTranslatef(hexOrbitR, 0.0f, 0.0f);          // 궤도 반경만큼 이동
        glRotatef(hexSelfAng, 0, 0, 1);                 // 별 자체 자전
        glColor3f(0.2f, 0.6f, 1.0f);                  // 파랑 별
        drawHexagram(hexRadius);
        glPopMatrix();

        glPopMatrix();  // 스마일맨 공전 행렬 복원

        // 7) 버퍼 스왑 & 이벤트 처리
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 8) 정리
    glfwTerminate();
    return 0;
}