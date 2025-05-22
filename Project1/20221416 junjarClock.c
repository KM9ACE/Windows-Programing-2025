#include <GLFW/glfw3.h>

#pragma comment(lib, "Opengl32.lib")

//
//0 -> 0b1111110
//1 -> 0b0110000
//2 -> 0b1101101
//3 -> 0b1111001
//4 -> 0b0110011
//5 -> 0b1011011
//6 -> 0b1011111
//7 -> 0b1110000
//8 -> 0b1111111
//9 -> 0b1111011


// ������ �׸��� ���� �Լ�
void drawLine(float x1, float y1, float x2, float y2) 
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int main(void) 
{
    if (!glfwInit()) 
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cross in Center", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 2D ���� ����

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // ȭ�� �߾ӿ� ���� ��� �׸���
        // �»�
        drawLine(-0.25f, 0.5f, -0.25f, 0.0f);
        // ��
        drawLine(-0.25f, 0.5f, 0.25f, 0.5f);
        // ���
        drawLine(0.25f, 0.5f, 0.25f, 0.0f);

        // ��
        drawLine(-0.25f, 0.0f, 0.25f, 0.0f);

        // ����
        drawLine(-0.25f, 0.0f, -0.25f, -0.5f);
        // ��
        drawLine(-0.25f, -0.5f, 0.25f, -0.5f);
        // ����
        drawLine(0.25f, 0.0f, 0.25f, -0.5f);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}