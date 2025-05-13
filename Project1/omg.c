#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>

// 사인은 x값 코사인은 y값

float angle = 0.0f; // 회전 각도

int main()
{
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: Rotating Triangle", NULL, NULL);
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

        glBegin(GL_TRIANGLES);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.0f, 0.5f);

        glEnd();

        glPopMatrix(); // 변환 상태 복원

        angle += 0.5f; // 각도를 증가시켜서 계속 회전

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
