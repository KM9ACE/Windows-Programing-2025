#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.14159265358979323846

float angle = 0.0f; // ȸ�� ����
int numSegments = 100; // ���� �����ϴ� �ﰢ���� ��

void drawCircle(float radius) 
{
    glBegin(GL_TRIANGLE_FAN); // �ﰢ�� ���� ����Ͽ� ���� �׸�
    glColor3f(1.0f, 1.0f, 0.0f); // ���� ���� (�����)
    glVertex2f(0.0f, 0.0f); // ���� �߽� (0, 0)

    int i = 0;
    // ���� �����ϴ� ������ �ﰢ������ �׸���
    for (i = 0; i <= numSegments; i++) 
    {
        float theta = 2.0f * PI * i / numSegments; // ���� ���
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

        glPushMatrix(); // ���� ��ȯ ���� ����

        // ȸ�� ��� ����
        glRotatef(angle, 0.0f, 0.0f, 1.0f); // z���� �������� ȸ��

        drawCircle(0.5f); // ������ 0.5�� ���� �׸�

        glPopMatrix(); // ��ȯ ���� ����

        angle += 0.5f; // ������ �������Ѽ� ��� ȸ��

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

