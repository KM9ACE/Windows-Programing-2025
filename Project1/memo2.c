/*
 * GLFW + OpenGL 1.1 �ִϸ��̼� ����
 * - �����ʿ� �����ϸ�(�� + �� + ���� ��) ��ġ
 * - �����ϸ��� ȭ�� �߽��� �������� ����
 * - ��(��/��)�� ���� ������ �ݴ� �������� ȸ���� �׻� ���� ����
 * - �����ϸ� �ֺ��� ������(��)�� �����ϸ� ��ü������ ������ ����
 */

#include <GLFW/glfw3.h>
#include <math.h>

#pragma comment(lib, "opengl32.lib")

#define PI 3.1415926535f

 // �� �׸���: ������ r, ���׸�Ʈ �� seg
void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);            // �߽�
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);
    }
    glEnd();
}

// �����ϸ� ��(�� + ��) �׸���
void drawFace(float eyeR, float eyeOffsetX, float eyeOffsetY) {
    // ���� ��
    glPushMatrix();
    glTranslatef(-eyeOffsetX, eyeOffsetY, 0.0f);
    drawCircle(eyeR, 16);
    glPopMatrix();

    // ������ ��
    glPushMatrix();
    glTranslatef(eyeOffsetX, eyeOffsetY, 0.0f);
    drawCircle(eyeR, 16);
    glPopMatrix();

    // ���� �� (�ݿ� ��ũ)
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 20; ++i) {
        // -30�� .. -150�� ����
        float a = (-30.0f - 120.0f * i / 20.0f) * (PI / 180.0f);
        glVertex2f(cosf(a) * 0.5f * eyeOffsetX, sinf(a) * 0.5f * eyeOffsetY);
    }
    glEnd();
}

// ������(��) �׸���: ������ r
void drawHexagram(float r) {
    float h = r * 0.866f; // sqrt(3)/2 * r
    glBegin(GL_TRIANGLES);
    // �� �ﰢ��
    glVertex2f(0.0f, r);
    glVertex2f(-h, -r * 0.5f);
    glVertex2f(h, -r * 0.5f);
    // �Ʒ� �ﰢ�� (������)
    glVertex2f(0.0f, -r);
    glVertex2f(-h, r * 0.5f);
    glVertex2f(h, r * 0.5f);
    glEnd();
}

int main(void) {
    // 1) GLFW �ʱ�ȭ
    if (!glfwInit()) return -1;

    // 2) ������ ���� & ���ؽ�Ʈ ���ε�
    GLFWwindow* window = glfwCreateWindow(800, 600, "Smiley Orbit & Hexagram", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // 3) 2D ���� ���� ���� (��ǥ�� -1..1)
    glOrtho(-1, 1, -1, 1, -1, 1);

    // �ִϸ��̼� �Ķ����
    const float smileOrbitR = 0.6f;   // �����ϸ� ���� �ݰ�
    const float smileRadius = 0.15f;  // �����ϸ� �� �ݰ�
    const float eyeR = 0.02f;         // �� �ݰ�
    const float eyeOffX = 0.05f,
        eyeOffY = 0.07f;      // �� ��ġ ������
    const float hexOrbitR = 0.3f;     // ������ ���� �ݰ�
    const float hexRadius = 0.07f;    // ������ ũ��

    // ���� ����
    while (!glfwWindowShouldClose(window)) {
        float t = (float)glfwGetTime();

        // ����/���� ���� ���
        float smileOrbitAng = t * 20.0f;     // �����ϸ� ���� �ӵ�
        float hexOrbitAng = t * 60.0f;     // �� ���� �ӵ� (����)
        float hexSelfAng = t * 200.0f;    // �� ��ü ���� �ӵ� (�� ����)

        // 4) ȭ�� Ŭ����
        glClear(GL_COLOR_BUFFER_BIT);

        // 5) �����ϸ� ���� �˵�
        glPushMatrix();
        glRotatef(smileOrbitAng, 0, 0, 1);                // �߽� ���� ����
        glTranslatef(smileOrbitR, 0.0f, 0.0f);          // �˵� �ݰ游ŭ �̵�

        // �� �׸���
        glColor3f(1.0f, 1.0f, 0.0f);                    // ��� ��
        drawCircle(smileRadius, 64);

        // �� Ư¡(��/��)�� ��ȸ������ ���� ����
        glPushMatrix();
        glRotatef(-smileOrbitAng, 0, 0, 1);
        glColor3f(0.0f, 0.0f, 0.0f);                  // ��/�� ����
        drawFace(eyeR, eyeOffX, eyeOffY);
        glPopMatrix();

        // 6) ������ ���� & ����
        glPushMatrix();
        glRotatef(hexOrbitAng, 0, 0, 1);                // �����ϸ� ���� ����
        glTranslatef(hexOrbitR, 0.0f, 0.0f);          // �˵� �ݰ游ŭ �̵�
        glRotatef(hexSelfAng, 0, 0, 1);                 // �� ��ü ����
        glColor3f(0.2f, 0.6f, 1.0f);                  // �Ķ� ��
        drawHexagram(hexRadius);
        glPopMatrix();

        glPopMatrix();  // �����ϸ� ���� ��� ����

        // 7) ���� ���� & �̺�Ʈ ó��
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 8) ����
    glfwTerminate();
    return 0;
}