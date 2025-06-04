#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>

#pragma comment(lib, "opengl32.lib")  // OpenGL 라이브러리 링크 (윈도우 환경)

#define PI 3.1415926535f  // 원주율 정의

// 2D 벡터 구조체
typedef struct {
    float x, y;
} Vec2;

// 위치, 회전, 스케일 정보를 담는 구조체
typedef struct {
    Vec2 position;   // 위치
    float rotation;  // 회전 (라디안)
    Vec2 scale;      // 크기 (x, y)
} Transform;

// 삼각형 객체 구조체 (변환 정보 포함)
typedef struct {
    Transform transform;
} TriangleObject;

// 사각형 객체 구조체 (변환 정보 포함)
typedef struct {
    Transform transform;
} SquareObject;

// 그룹 객체 구조체
// 그룹 자체에 변환(transform)이 있고, 그 안에 삼각형과 사각형이 있음
typedef struct {
    Transform transform;   // 그룹 전체 변환
    TriangleObject triangle;  // 삼각형 자식 객체
    SquareObject square;      // 사각형 자식 객체
} GroupObject;

// 삼각형 그리기 함수
// 로컬 좌표계(중심이 0,0) 기준 삼각형을 그린다
void draw_triangle_object(const TriangleObject* tri)
{
    glPushMatrix(); // 현재 행렬 상태 저장

    // 삼각형의 위치, 회전, 크기 적용
    glTranslatef(tri->transform.position.x, tri->transform.position.y, 0.0f);
    glRotatef(tri->transform.rotation * 180.0f / PI, 0.0f, 0.0f, 1.0f);  // 라디안을 도 단위로 변환
    glScalef(tri->transform.scale.x, tri->transform.scale.y, 1.0f);

    // 삼각형 그리기 (빨간색)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);     // 꼭짓점 위쪽
    glVertex2f(-0.5f, -0.5f);   // 왼쪽 아래
    glVertex2f(0.5f, -0.5f);    // 오른쪽 아래
    glEnd();

    glPopMatrix(); // 행렬 상태 복원
}

// 사각형 그리기 함수
// 로컬 좌표계(중심이 0,0) 기준 사각형을 그린다
void draw_square_object(const SquareObject* sq)
{
    glPushMatrix(); // 현재 행렬 상태 저장

    // 사각형의 위치, 회전, 크기 적용
    glTranslatef(sq->transform.position.x, sq->transform.position.y, 0.0f);
    glRotatef(sq->transform.rotation * 180.0f / PI, 0.0f, 0.0f, 1.0f);  // 라디안을 도 단위로 변환
    glScalef(sq->transform.scale.x, sq->transform.scale.y, 1.0f);

    // 사각형 그리기 (파란색)
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.5f, 0.5f);   // 왼쪽 위
    glVertex2f(0.5f, 0.5f);    // 오른쪽 위
    glVertex2f(0.5f, -0.5f);   // 오른쪽 아래
    glVertex2f(-0.5f, -0.5f);  // 왼쪽 아래
    glEnd();

    glPopMatrix(); // 행렬 상태 복원
}

// 그룹 전체 그리기 함수
// 그룹 변환을 적용한 뒤에 자식 도형들을 그린다
void draw_group_object(const GroupObject* group)
{
    glPushMatrix();  // 현재 행렬 상태 저장

    // 그룹의 변환을 먼저 적용 (이동, 회전, 스케일)
    // 이 변환이 그룹 내부 모든 자식 도형에 영향을 준다.
    glTranslatef(group->transform.position.x, group->transform.position.y, 0.0f);
    glRotatef(group->transform.rotation * 180.0f / PI, 0.0f, 0.0f, 1.0f);
    glScalef(group->transform.scale.x, group->transform.scale.y, 1.0f);

    // 그룹 내 삼각형 그리기
    draw_triangle_object(&group->triangle);

    // 그룹 내 사각형 그리기
    draw_square_object(&group->square);

    glPopMatrix();  // 행렬 상태 복원
}

int main(void)
{
    // GLFW 초기화
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // 윈도우 생성 (800x800 크기)
    GLFWwindow* window = glfwCreateWindow(800, 800, "Group Transform Example", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // OpenGL 컨텍스트를 현재 윈도우에 연결

    // 뷰포트 설정 (윈도우 크기와 동일하게)
    glViewport(0, 0, 800, 800);

    // 투영 행렬 설정 (2D 정규 좌표계 -2 ~ 2 범위)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -1, 1);  // 좌표계 설정 (왼쪽, 오른쪽, 아래, 위, 앞, 뒤)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 그룹 객체 초기화
    GroupObject group = { 0 };

    // 그룹의 위치, 회전, 스케일 초기값 설정
    group.transform.position.x = 0.0f;
    group.transform.position.y = 0.0f;
    group.transform.rotation = 0.0f;
    group.transform.scale.x = 1.0f;
    group.transform.scale.y = 1.0f;

    // 삼각형의 로컬 위치를 그룹 기준으로 왼쪽에 배치
    group.triangle.transform.position.x = -1.0f;
    group.triangle.transform.position.y = 0.0f;
    group.triangle.transform.rotation = 0.0f;
    group.triangle.transform.scale.x = 1.0f;
    group.triangle.transform.scale.y = 1.0f;

    // 사각형의 로컬 위치를 그룹 기준으로 오른쪽에 배치
    group.square.transform.position.x = 1.0f;
    group.square.transform.position.y = 0.0f;
    group.square.transform.rotation = 0.0f;
    group.square.transform.scale.x = 1.0f;
    group.square.transform.scale.y = 1.0f;

    // 메인 루프 (윈도우가 닫힐 때까지 반복)
    while (!glfwWindowShouldClose(window))
    {
        // 화면 초기화 (배경색 초기화)
        glClear(GL_COLOR_BUFFER_BIT);

        // 그룹 이동 및 회전 업데이트
        group.transform.position.x += 0.001f;  // 오른쪽으로 천천히 이동
        group.transform.rotation += 0.01f;     // 반시계 방향으로 회전 (라디안)

        // 그룹과 자식 도형들 그리기
        draw_group_object(&group);

        // 화면 버퍼 스왑 (더블 버퍼링)
        glfwSwapBuffers(window);

        // 이벤트 처리 (키보드, 마우스 등)
        glfwPollEvents();
    }

    // 자원 정리
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
