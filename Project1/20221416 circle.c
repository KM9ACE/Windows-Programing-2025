#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.14159265358979323846

float angle = 
int numSegments = 100; // 원을 구성하는 삼각형의 수

void drawCircle(float radius) 
{
    glBegin(GL_TRIANGLE_FAN); // 삼각형 팬을 사용하여 원을 그림
    glColor3f(1.0f, 1.0f, 0.0f); // 원의 색상 (노란색)
    glVertex2f(0.0f, 0.0f);

    int i = 0;
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

        glPushMatrix();

        glRotatef(angle, 0.0f, 0.0f, 1.0f); // z축을 기준으로 회전

        drawCircle(0.5f); // 반지름 0.5의 원을 그림

        glPopMatrix();

        angle += 0.5f; // 각도를 증가시켜서 계속 회전

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

