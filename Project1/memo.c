﻿#include <GLFW/glfw3.h>
#include <math.h>

#pragma comment(lib, "Opengl32.lib")  // OpenGL 라이브러리 링크

#define PI 3.1415926535f  // 원주율 정의

// 2D 벡터 구조체 (x, y 좌표)
typedef struct
{
    float x, y;
} Vec2;

// 변환 구조체 (위치, 회전, 크기)
typedef struct
{
    Vec2 position;  // 객체의 위치 (x, y)
    float rotation;  // 객체의 회전 각도 (라디안)
    Vec2 scale;  // 객체의 크기 (x, y)
} Transform;

// 삼각형 구조체 (변환 정보 포함)
typedef struct
{
    Transform transform;  // 삼각형의 위치, 회전, 크기 정보
} Triangle;

// 삼각형을 그리는 함수
void draw_triangle(Triangle* tri)
{
    glPushMatrix();  // 현재 변환 행렬 저장

    // 위치 변환 (이동)
    glTranslatef(tri->transform.position.x, tri->transform.position.y, 0.0f);
    // 회전 변환 (회전)
    glRotatef(tri->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    // 크기 변환 (스케일)
    glScalef(tri->transform.scale.x, tri->transform.scale.y, 1.0f);

    glBegin(GL_TRIANGLES);  // 삼각형 그리기 시작
    glColor3f(1.0f, 0.0f, 0.0f);  // 삼각형 색상은 빨간색
    // 삼각형의 3개의 꼭짓점 정의
    glVertex2f(0.0f, 0.5f);  // 위쪽 꼭짓점
    glVertex2f(-0.5f, -0.5f);  // 왼쪽 아래 꼭짓점
    glVertex2f(0.5f, -0.5f);  // 오른쪽 아래 꼭짓점
    glEnd();  // 삼각형 그리기 종료

    glPopMatrix();  // 저장된 변환 행렬 복원
}

// 사각형 구조체 (변환 정보 포함)
typedef struct
{
    Transform transform;  // 사각형의 위치, 회전, 크기 정보
} Square;

// 사각형을 그리는 함수
void draw_square(Square* sq)
{
    glPushMatrix();  // 현재 변환 행렬 저장

    // 위치 변환 (이동)
    glTranslatef(sq->transform.position.x, sq->transform.position.y, 0.0f);
    // 회전 변환 (회전)
    glRotatef(sq->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    // 크기 변환 (스케일)
    glScalef(sq->transform.scale.x, sq->transform.scale.y, 1.0f);

    glBegin(GL_QUADS);  // 사각형 그리기 시작
    glColor3f(r, g, b);  // 사각형 색상은 초록색
    // 사각형의 4개의 꼭짓점 정의
    glVertex2f(-0.5f, 0.5f);  // 왼쪽 위 꼭짓점
    glVertex2f(0.5f, 0.5f);  // 오른쪽 위 꼭짓점
    glVertex2f(0.5f, -0.5f);  // 오른쪽 아래 꼭짓점
    glVertex2f(-0.5f, -0.5f);  // 왼쪽 아래 꼭짓점
    glEnd();  // 사각형 그리기 종료

    glPopMatrix();  // 저장된 변환 행렬 복원
}

// 원 구조체 (변환 정보 포함)
typedef struct
{
    Transform transform;  // 원의 위치, 회전, 크기 정보
    int segments;  // 원을 그리기 위한 세그먼트 수 (원주를 몇 개의 삼각형으로 나눠서 그릴지)
} Circle;

// 원을 그리는 함수
void draw_circle(Circle* c)
{
    glPushMatrix();  // 현재 변환 행렬 저장

    // 위치 변환 (이동)
    glTranslatef(c->transform.position.x, c->transform.position.y, 0.0f);
    // 회전 변환 (회전)
    glRotatef(c->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    // 크기 변환 (스케일)
    glScalef(c->transform.scale.x, c->transform.scale.y, 1.0f);

    glBegin(GL_TRIANGLE_FAN);  // 원을 그리기 시작 (팬 형태)
    glColor3f(0.0f, 0.0f, 1.0f);  // 원의 색상은 파란색
    glVertex2f(0.0f, 0.0f);  // 원의 중심

    // 원을 그리기 위한 점들 계산 (세그먼트 수에 따라 원을 나눔)
    for (int i = 0; i <= c->segments; ++i)
    {
        float angle = 2.0f * PI * i / c->segments;  // 각도 계산
        glVertex2f(cosf(angle) * 0.5f, sinf(angle) * 0.5f);  // 원주 위의 점 계산
    }

    glEnd();  // 원 그리기 종료

    glPopMatrix();  // 저장된 변환 행렬 복원
}

// main 함수
int main()
{
    if (!glfwInit())  // GLFW 초기화 실패시 종료
        return -1;

    // 윈도우 크기 설정
    int width = 500, height = 500;
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL C Demo", NULL, NULL);
    if (!window)  // 윈도우 생성 실패시 종료
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // OpenGL 컨텍스트 설정

    // 픽셀 기준 좌표계 설정 (왼쪽 상단이 (0, 0))
    glOrtho(0, width, height, 0, -1, 1);  // 2D 직교 투영 설정

    // 객체 초기화 (삼각형, 사각형, 원)
    Triangle tri = { {{width / 2, height / 2}, 0, {100, 100}} };  // 삼각형: 화면 중앙에 배치, 크기 100x100
    Square sq = { {{100, 100}, 0, {100, 100}} };  // 사각형: (100, 100) 위치, 크기 100x100
    Circle cir = { {{width / 2, height / 2}, 0, {100, 100}}, 32 };  // 원: 화면 중앙에 배치, 크기 100x100, 세그먼트 32개

    // 메인 렌더링 루프
    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();  // 시간 값을 가져옴

        // 객체 변환 업데이트 (애니메이션 효과)
        tri.transform.position.x = (sin(time) + 1) * width / 2;  // 삼각형 X축 이동 (sin 파동)
        tri.transform.position.y = (cos(time) + 1) * height / 2;  // 삼각형 Y축 이동 (cos 파동)

        sq.transform.rotation = time;  // 사각형 회전 (시간에 따라 회전)
        cir.transform.scale.x = 1.0f + 0.5f * sinf(time);  // 원 크기 변경 (시간에 따라 크기 변동)

        glClear(GL_COLOR_BUFFER_BIT);  // 화면을 지움 (배경을 흰색으로 초기화)

        // 객체들 그리기
        draw_triangle(&tri);  // 삼각형 그리기
        draw_square(&sq);  // 사각형 그리기
        draw_circle(&cir);  // 원 그리기

        glfwSwapBuffers(window);  // 화면 갱신 (프레임 버퍼를 교환)
        glfwPollEvents();  // 윈도우 이벤트 처리 (예: 키보드, 마우스 이벤트)
    }

    glfwTerminate();  // GLFW 종료
    return 0;
}
