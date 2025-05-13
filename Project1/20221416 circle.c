#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.14159265358979323846

float angle = 0.0f; // 회전 각도
int numSegments = 100; // 원을 구성하는 삼각형의 수

void drawCircle(float radius) 
{
    glBegin(GL_TRIANGLE_FAN); // 삼각형 팬을 사용하여 원을 그림
    glColor3f(1.0f, 1.0f, 0.0f); // 원의 색상 (노란색)
    glVertex2f(0.0f, 0.0f); // 원의 중심 (0, 0)

    int i = 0;
    // 원을 구성하는 점들을 삼각형으로 그리기
    for (i = 0; i <= numSegments; i++) 
    {
        float theta = 2.0f * PI * i / numSegments; // 각도 계산
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

int main()
{
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: Rotating Circle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix(); // 현재 변환 상태 저장

        // 회전 행렬 적용
        glRotatef(angle, 0.0f, 0.0f, 1.0f); // z축을 기준으로 회전

        drawCircle(0.5f); // 반지름 0.5의 원을 그림

        glPopMatrix(); // 변환 상태 복원

        angle += 0.5f; // 각도를 증가시켜서 계속 회전

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

