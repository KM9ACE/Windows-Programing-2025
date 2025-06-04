#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <windows.h> // GetAsyncKeyState �Լ� ��� ���� ����
#include <math.h>

// ���� ����: ��ũ ���¿� �� ��� ���� ����
int isWink = 0;      // 0: ��ũ �ƴ�, 1: ��ũ ����
int faceShape = 0;   // 0=��, 1=�簢��, 2=�ﰢ��, 3=Ÿ��

// ------------------- �� ���� �׸��� �Լ��� -------------------

// ���� �ﰢ�� ������ �׸��� �Լ�
// cx, cy: �� �߽� ��ǥ
// r: ������
// num_segments: ���� �ٻ��� �� ���� (Ŭ���� �ε巯��)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);  // ����� �󱼻� ����
    glVertex2f(cx, cy);            // �߽��� ���� �׸���
    for (int i = 0; i <= num_segments; i++) {
        // �� ���� ������ 0 ~ 2�� �������� �յ� ����
        float theta = 2.0f * 3.14159265358979323846f * i / num_segments;
        // ���� x, y ��ǥ ���
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        // �߽� ��ǥ�� ��� ��ǥ ���ؼ� ������ ����
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Ÿ���� �ﰢ�� ������ �׸��� �Լ�
// rx, ry: x��� y�� ���� ������
// ������ �Ķ���ʹ� ���� ����
void drawEllipse(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);  // ����� �󱼻�
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.14159265358979323846f * i / num_segments;
        // ���� �޸� x�� y�� ���� �ٸ� ������ ����
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// �簢�� �� �׸��� �Լ�
// cx, cy: �߽� ��ǥ, size: �� �� ����
void drawSquareFace(float cx, float cy, float size) {
    float half = size / 2.0f; // �� �� ���� ���
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);  // ����� �󱼻�
    // �ð�������� �簢�� �� ������ ����
    glVertex2f(cx - half, cy - half);
    glVertex2f(cx + half, cy - half);
    glVertex2f(cx + half, cy + half);
    glVertex2f(cx - half, cy + half);
    glEnd();
}

// �ﰢ�� �� �׸��� �Լ� (���ﰢ��)
// cx, cy: �߽� ��ǥ, size: ���� ����
void drawTriangleFace(float cx, float cy, float size) {
    float height = size * 0.866f; // ���ﰢ�� ���� (sqrt(3)/2 * size)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);  // ����� �󱼻�
    // �� ������ (�߽� ����)
    glVertex2f(cx, cy + height / 2);
    // ���� �Ʒ� ������
    glVertex2f(cx - size / 2, cy - height / 2);
    // ������ �Ʒ� ������
    glVertex2f(cx + size / 2, cy - height / 2);
    glEnd();
}

// ------------------- �ܼ� �� �׸��� �Լ� -------------------
// x1,y1 ���� x2,y2 ���� ������ �׸���
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// ------------------- �� ��翡 ���� �� �׸��� �б� -------------------
void drawFaceShape(int shape) {
    switch (shape) {
    case 0: // ���� ��
        drawCircle(0.0f, 0.0f, 0.8f, 360);
        break;
    case 1: // �簢�� ��
        drawSquareFace(0.0f, 0.0f, 1.6f);
        break;
    case 2: // �ﰢ�� ��
        drawTriangleFace(0.0f, 0.0f, 1.6f);
        break;
    case 3: // Ÿ�� �� (���� ��� ���δ� �� ����)
        drawEllipse(0.0f, 0.0f, 0.8f, 0.5f, 360);
        break;
    default: // �⺻ ���� ��
        drawCircle(0.0f, 0.0f, 0.8f, 360);
    }
}

// ------------------- ������ �� �׸��� -------------------
// wink: 1�̸� ������ �� ��ũ, 0�̸� ���� ��
// shape: �� ��� ��ȣ
void drawSmileMan(int wink, int shape) {
    // �� �׸���
    drawFaceShape(shape);

    glColor3f(0.0f, 0.0f, 0.0f); // ���� ���� ������

    // ���� �� (�׻� ���� �� ���)
    drawLine(-0.3f, 0.3f, -0.2f, 0.4f);
    drawLine(-0.2f, 0.4f, -0.1f, 0.3f);

    // ������ �� (��ũ ���ο� ���� �ٸ��� �׸�)
    if (wink) {
        // ��ũ ���� '<' ��� (�밢�� �� ��)
        drawLine(0.2f, 0.3f, 0.1f, 0.4f);
        drawLine(0.1f, 0.4f, 0.0f, 0.3f);
    }
    else {
        // ���� �� ���
        drawLine(0.1f, 0.3f, 0.2f, 0.4f);
        drawLine(0.2f, 0.4f, 0.3f, 0.3f);
    }

    // ���� �� ��� (�� ������ ǥ��)
    drawLine(-0.3f, -0.3f, -0.1f, -0.5f);
    drawLine(-0.1f, -0.5f, 0.1f, -0.5f);
    drawLine(0.1f, -0.5f, 0.3f, -0.3f);
}

// ------------------- Ű���� �Է� �ݹ� -------------------
// GLFW�� Ű �Է��� �����ϸ� ȣ��Ǵ� �Լ�
// ��ũ ���¿� �� ��� ���� Ű ó��
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // W Ű ����/�ݺ� �� ��ũ ���·� ����
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        isWink = 1;
    }
    // W Ű ���� ��ũ ����
    if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
        isWink = 0;
    }

    // ����Ű 1~4�� �� ��� ���� (���� ������)
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_1) faceShape = 0; // ���� ��
        if (key == GLFW_KEY_2) faceShape = 1; // �簢�� ��
        if (key == GLFW_KEY_3) faceShape = 2; // �ﰢ�� ��
        if (key == GLFW_KEY_4) faceShape = 3; // Ÿ�� ��
    }
}

// ------------------- main �Լ� -------------------
int main(void) {
    // GLFW �ʱ�ȭ ���н� ����
    if (!glfwInit())
        return -1;

    // 800x600 ���� ũ�� ������ ����
    GLFWwindow* window = glfwCreateWindow(800, 600, "Smile Man Wink - Face Shape + Ellipse", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // 2D ���� ��ǥ�� ����: �¿�, ���� -1 ~ 1
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    // Ű �Է� �ݹ� ���
    glfwSetKeyCallback(window, key_callback);

    // ���� ����
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // GetAsyncKeyState�� WŰ ���� �ǽð� üũ
        // (Ű �ݹ鿡�� ��ģ ��� ���Ͽ�)
        if ((GetAsyncKeyState('W') & 0x8000) != 0) {
            isWink = 1;
        }
        else {
            isWink = 0;
        }

        // ���� ���¿� �°� ������ �� �׸���
        drawSmileMan(isWink, faceShape);

        glfwSwapBuffers(window); // ȭ�� ������Ʈ
        glfwPollEvents();        // �̺�Ʈ ó��
    }

    // ���� �� ���ҽ� ����
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
