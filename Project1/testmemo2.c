#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <Windows.h>  // GetAsyncKeyState �Լ� ����� ���� ����

#define PI 3.14159265358979323846

// ���� �׸��� �Լ�
// x, y : �� �߽� ��ǥ
// r : ������
// red, green, blue : RGB ���� (0.0 ~ 1.0)
void drawCircle(float x, float y, float r, float red, float green, float blue) {
    int segments = 100;  // ���� �ٰ������� �ٻ��� �� ����� �� ����

    glColor3f(red, green, blue);  // ���� ����
    glBegin(GL_TRIANGLE_FAN);     // �ﰢ�� �� ��� ���� (�߽��� + �ֺ������� �� ����)

    glVertex2f(x, y);             // �߽��� ��ǥ

    // �� �ѷ��� ���� ��� �ﰢ�� �� ����
    for (int i = 0; i <= segments; i++) {
        // 0 ~ 2�� ���� ���� ��� (�� �ѷ��� ����)
        float theta = 2.0f * PI * i / segments;

        // �� �ѷ� ���� x, y ��ǥ ���
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);

        // �߽� ��ǥ�� ���� ���� �� ��ġ ����
        glVertex2f(x + dx, y + dy);
    }

    glEnd();  // ���� �׸��� ����
}

int main() {
    // GLFW ���̺귯�� �ʱ�ȭ (OpenGL ������ ������)
    if (!glfwInit()) return -1;

    // 800x800 ũ���� â ����, Ÿ��Ʋ ����
    GLFWwindow* window = glfwCreateWindow(800, 800, "Solar System Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // ���� â�� ���� OpenGL ���ؽ�Ʈ�� ����
    glfwMakeContextCurrent(window);

    // 2D ��ǥ�踦 -1���� 1������ ���� (���� �Ʒ�(-1,-1), ������ ��(1,1))
    glOrtho(-1, 1, -1, 1, -1, 1);

    // �ùķ��̼� �ð� ���� (�� ����ó�� ���)
    float time = 0.0f;

    // ���� ����: â�� ������ ������ �ݺ�
    while (!glfwWindowShouldClose(window)) {
        // ȭ�� �ʱ�ȭ (���� Ŭ����)
        glClear(GL_COLOR_BUFFER_BIT);

        // --------------------------------
        // Ű ���� Ȯ�� (GetAsyncKeyState ���)
        // --------------------------------
        // VK_RIGHT : ������ ȭ��ǥ Ű �ڵ�
        // VK_LEFT  : ���� ȭ��ǥ Ű �ڵ�
        //
        // GetAsyncKeyState �Լ��� �ش� Ű�� ���������� �ֻ��� ��Ʈ(0x8000)�� 1�� ��Ʈ��
        SHORT rightKey = GetAsyncKeyState(VK_RIGHT);
        SHORT leftKey = GetAsyncKeyState(VK_LEFT);

        // ������ Ű�� ���������� time ���� (�ð� �帧 ������)
        if (rightKey & 0x8000) {
            time += 0.01f;  // ������ ���� ����
        }
        // ���� Ű�� ���������� time ���� (�ð� �Ųٷ� �帧)
        else if (leftKey & 0x8000) {
            time -= 0.01f;  // ���ҷ� ���� ����
        }
        // �� Ű ��� �� ������ time ���� (����)

        // -------------------------------
        // �¾� �׸��� (���� ��ġ)
        // -------------------------------
        // �����, ������ 0.2, �߽� (0,0)
        drawCircle(0.0f, 0.0f, 0.2f, 1.0f, 1.0f, 0.0f);

        // -------------------------------
        // ���� ���� �� ���� ���� ���
        // -------------------------------
        // ����: time ���� ��� (�ݽð� ����)
        float earthOrbitAngle = time;

        // ����: �ð� �����̹Ƿ� ������ ó��, �ӵ��� ���Ƿ� 5�� ������ ����
        float earthRotationAngle = -time * 5.0f;

        // ���� ������ 0.6�� ������ ���� ��ġ ��� (�¾� �߽� ����)
        float earthX = 0.6f * cosf(earthOrbitAngle);
        float earthY = 0.6f * sinf(earthOrbitAngle);

        // -------------------------------
        // ���� �׸���
        // -------------------------------
        glPushMatrix();  // ���� ��ǥ�� ���� ����

        // ���� ��ġ�� �̵� (�¾� �߽ɿ��� ���� ���� ��ġ)
        glTranslatef(earthX, earthY, 0);

        // ���� ���� (Z�� ���� ȸ��)
        glRotatef(earthRotationAngle * 180.0f / PI, 0, 0, 1);

        // �Ķ���, ������ 0.1�� ���� �� �׸���
        drawCircle(0, 0, 0.1f, 0.0f, 0.0f, 1.0f);

        glPopMatrix();   // ��ǥ�� ���� (�ٸ� ��ü�� ���� �� �ֱ� ����)

        // -------------------------------
        // �� ���� �� ���� ���� ���
        // -------------------------------
        // �� ������ ���� �������� 12�� ���� (���� ����)
        float moonOrbitAngle = time * 12.0f;

        // �� ������ �������� ���� �ӵ�, �ð� ����
        float moonRotationAngle = -time * 12.0f * 5.0f;

        // �� ��ġ (���� ����, ���� ������ 0.2)
        float moonX = earthX + 0.2f * cosf(moonOrbitAngle);
        float moonY = earthY + 0.2f * sinf(moonOrbitAngle);

        // -------------------------------
        // �� �׸���
        // -------------------------------
        glPushMatrix();

        // �� ��ġ�� �̵�
        glTranslatef(moonX, moonY, 0);

        // �� ���� ȸ��
        glRotatef(moonRotationAngle * 180.0f / PI, 0, 0, 1);

        // ȸ��, ������ 0.05�� �� �� �׸���
        drawCircle(0, 0, 0.05f, 0.5f, 0.5f, 0.5f);

        glPopMatrix();

        // ---------------------------------
        // ȭ�� ���� ��ȯ �� �̺�Ʈ ó��
        // ---------------------------------
        glfwSwapBuffers(window);  // �׸� ������ ȭ�鿡 ǥ��
        glfwPollEvents();         // �Է� �� â �̺�Ʈ ó��
    }

    glfwTerminate();  // GLFW ����
    return 0;
}
