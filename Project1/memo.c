#include <GLFW/glfw3.h>
#include <math.h>

#pragma comment(lib, "Opengl32.lib")  // OpenGL 라이브러리 링크

#define PI 3.1415926535f  // 원주율 정의

// 2D 벡터 구조체 (x, y 좌표)
typedef struct
{
    float x, y;
} Vec2;

// 고정 도형 //

// 타원(원)

void drawEllipse(float cx, float cy, float rx, float ry, int num_segments, float r_color, float g_color, float b_color)
{
    int i;

    glColor3f(r_color, g_color, b_color);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);

    for (i = 0; i <= num_segments; i++)
    {
        float angle = 2.0f * PI * (float)i / (float)num_segments;

        float x_offset = cosf(angle) * rx;
        float y_offset = sinf(angle) * ry;

        glVertex2f(cx + x_offset, cy + y_offset);
    }
    glEnd();
}

// 삼각형

void drawTriangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y, float r_color, float g_color, float b_color)
{
    glColor3f(r_color, g_color, b_color);

    glBegin(GL_TRIANGLES);
    glVertex2f(v1x, v1y); // 첫 번째 꼭짓점
    glVertex2f(v2x, v2y); // 두 번째 꼭짓점
    glVertex2f(v3x, v3y); // 세 번째 꼭짓점
    
    glEnd();
}

// 사각형

void drawRectangle(float x, float y, float width, float height, float r_color, float g_color, float b_color)
{
    glColor3f(r_color, g_color, b_color);

    glBegin(GL_QUADS);
    glVertex2f(x, y);  
    glVertex2f(x + width, y); 
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);

    glEnd();
}

// 선

void drawLine(float x1, float y1, float x2, float y2, float lineWidth, float r_color, float g_color, float b_color)
{
    glLineWidth(lineWidth);
    
    glColor3f(r_color, g_color, b_color);

    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();
}

// 네모난 선

void drawNLine(float x1, float y1, float x2, float y2, float lineWidth, float r, float g, float b)
{
    glColor3f(r, g, b);

    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = sqrtf(dx * dx + dy * dy);

    float nx = -dy / length;
    float ny = dx / length;

    float offsetX = (lineWidth / 2.0f) * nx;
    float offsetY = (lineWidth / 2.0f) * ny;

    float x1a = x1 + offsetX;
    float y1a = y1 + offsetY;
    float x1b = x1 - offsetX;
    float y1b = y1 - offsetY;

    float x2a = x2 + offsetX;
    float y2a = y2 + offsetY;
    float x2b = x2 - offsetX;
    float y2b = y2 - offsetY;

    glBegin(GL_POLYGON);
    glVertex2f(x1a, y1a);
    glVertex2f(x2a, y2a);
    glVertex2f(x2b, y2b);
    glVertex2f(x1b, y1b);

    glEnd();
}

// 움직이는 도형 //

typedef struct 
{
    Vec2 position;  // 객체의 화면상 기준점 위치 (x, y)
    float rotation;  // 객체의 회전 각도 (라디안 단위)
    Vec2 scale;     // 객체의 크기 비율 (x, y). 기본 크기에 이 비율이 곱해짐.
} Transform;

// 움직이는 타원 

typedef struct 
{
    Transform transform; // 위치, 회전, 크기 정보
    Vec2 radii;          // 타원의 기본 X반지름, Y반지름 (transform.scale 적용 전)
    float color_r, color_g, color_b; // 타원의 R, G, B 색상
    int segments;        // 타원을 그릴 때 사용할 선분 개수
} EllipseObject;

void draw_ellipse_object(const EllipseObject* ellipse) 
{
    int i = 0;

    if (ellipse == NULL) return;

    glPushMatrix();

    glTranslatef(ellipse->transform.position.x, ellipse->transform.position.y, 0.0f);
    glRotatef(ellipse->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    glScalef(ellipse->transform.scale.x, ellipse->transform.scale.y, 1.0f);

    glColor3f(ellipse->color_r, ellipse->color_g, ellipse->color_b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // 로컬 원점 (0,0)이 부채꼴의 중심
    for (i = 0; i <= ellipse->segments; i++) 
    {
        float angle = 2.0f * PI * (float)i / (float)ellipse->segments;
        float x_pos = cosf(angle) * ellipse->radii.x;
        float y_pos = sinf(angle) * ellipse->radii.y;
        glVertex2f(x_pos, y_pos);
    }
    glEnd();

    glPopMatrix();
}

// 움직이는 삼각형

typedef struct 
{
    Transform transform; // 위치, 회전, 크기 정보
    Vec2 local_v1;       // 로컬 좌표계 기준 첫 번째 꼭짓점
    Vec2 local_v2;       // 로컬 좌표계 기준 두 번째 꼭짓점
    Vec2 local_v3;       // 로컬 좌표계 기준 세 번째 꼭짓점
    float color_r, color_g, color_b; // 삼각형의 R, G, B 색상
} TriangleObject;

void draw_triangle_object(const TriangleObject* triangle) 
{
    if (triangle == NULL) return;

    glPushMatrix();

    glTranslatef(triangle->transform.position.x, triangle->transform.position.y, 0.0f);
    glRotatef(triangle->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    glScalef(triangle->transform.scale.x, triangle->transform.scale.y, 1.0f);

    glColor3f(triangle->color_r, triangle->color_g, triangle->color_b);
    glBegin(GL_TRIANGLES);
    glVertex2f(triangle->local_v1.x, triangle->local_v1.y);
    glVertex2f(triangle->local_v2.x, triangle->local_v2.y);
    glVertex2f(triangle->local_v3.x, triangle->local_v3.y);
    glEnd();

    glPopMatrix();
}

// 움직이는 사각형

typedef struct 
{
    Transform transform; // 위치, 회전, 크기 정보
    // 사각형은 아래 draw_square_object 함수에서 로컬 (0,0) 중심의 단위 크기(1x1)로 그리므로,
    // transform.scale이 실제 너비와 높이가 됩니다.
    // 필요하다면 Vec2 base_size; 같은 멤버를 추가하여 기본 크기를 별도로 정의할 수도 있습니다.
    float color_r, color_g, color_b; // 사각형의 R, G, B 색상
} SquareObject;

void draw_square_object(const SquareObject* square) {
    if (square == NULL) return;

    glPushMatrix();

    glTranslatef(square->transform.position.x, square->transform.position.y, 0.0f);
    glRotatef(square->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    glScalef(square->transform.scale.x, square->transform.scale.y, 1.0f);

    glColor3f(square->color_r, square->color_g, square->color_b);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, 0.5f); // 왼쪽 위
    glVertex2f(0.5f, 0.5f); // 오른쪽 위
    glVertex2f(0.5f, -0.5f); // 오른쪽 아래
    glVertex2f(-0.5f, -0.5f); // 왼쪽 아래
    glEnd();

    glPopMatrix();
}

// 움직이는 선

typedef struct 
{
    Transform transform; // 위치, 회전, 크기 정보
    Vec2 local_p1;       // 로컬 좌표계 기준 선의 시작점
    Vec2 local_p2;       // 로컬 좌표계 기준 선의 끝점
    float thickness;     // 선의 기본 두께 (transform.scale 적용 전)
    float color_r, color_g, color_b; // 선의 R, G, B 색상
} LineObject;

void draw_line_object(const LineObject* line)
{
    if (line == NULL) return;

    glPushMatrix();

    glTranslatef(line->transform.position.x, line->transform.position.y, 0.0f);
    glRotatef(line->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    glScalef(line->transform.scale.x, line->transform.scale.y, 1.0f);

    // --- 로컬 좌표 기준으로 두꺼운 선 그리기 시작 (이전 draw_line 로직 활용) ---
    // LineObject의 local_p1, local_p2, thickness, color를 사용합니다.
    // 이 좌표와 두께는 이미 위에서 적용된 glScalef의 영향을 받게 됩니다.
    // (정확히는, glScalef로 인해 변환된 좌표계에서 아래 로직이 실행됩니다)

    float x1 = line->local_p1.x;
    float y1 = line->local_p1.y;
    float x2 = line->local_p2.x;
    float y2 = line->local_p2.y;
    float current_thickness = line->thickness; // 이 두께 값도 scale의 영향을 받음

    glColor3f(line->color_r, line->color_g, line->color_b);

    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrtf(dx * dx + dy * dy);

    if (length < 0.0001f)
    {
        if (current_thickness > 0)
        {
            float half_thick = current_thickness / 2.0f;

            glBegin(GL_QUADS);
            glVertex2f(x1 - half_thick, y1 - half_thick);
            glVertex2f(x1 + half_thick, y1 - half_thick);
            glVertex2f(x1 + half_thick, y1 + half_thick);
            glVertex2f(x1 - half_thick, y1 + half_thick);
            glEnd();
        }
        glPopMatrix();
        return;
    }

    float nx = -dy / length;
    float ny = dx / length;

    float offsetX = (current_thickness / 2.0f) * nx;
    float offsetY = (current_thickness / 2.0f) * ny;

    float x1a = x1 + offsetX; float y1a = y1 + offsetY;
    float x1b = x1 - offsetX; float y1b = y1 - offsetY;
    float x2a = x2 + offsetX; float y2a = y2 + offsetY;
    float x2b = x2 - offsetX; float y2b = y2 - offsetY;

    glBegin(GL_POLYGON);
    glVertex2f(x1a, y1a); glVertex2f(x2a, y2a);
    glVertex2f(x2b, y2b); glVertex2f(x1b, y1b);
    glEnd();

    glPopMatrix();
}


int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL Ellipses + Line", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glOrtho(0, 500, 0, 500, -1, 1); // 픽셀 좌표계
    glClearColor(1, 1, 1, 1);  // 배경 흰색

    glfwSwapInterval(1); // VSync 활성화

    // --- 각 도형 객체 생성 및 초기화 ---

   // 1. 원(타원) 객체 초기화
    EllipseObject myEllipse;
    myEllipse.transform.position = (Vec2){ 120.0f, 380.0f }; // 화면상 기준 위치
    myEllipse.transform.rotation = 0.0f;                  // 초기 회전 (라디안)
    myEllipse.transform.scale = (Vec2){ 1.0f, 1.0f };       // 초기 크기 비율
    myEllipse.radii = (Vec2){ 60.0f, 30.0f };               // 기본 X, Y 반지름
    myEllipse.color_r = 1.0f; myEllipse.color_g = 0.5f; myEllipse.color_b = 0.2f; // 주황 계열
    myEllipse.segments = 100;

    // 2. 삼각형 객체 초기화
    TriangleObject myTriangle;
    myTriangle.transform.position = (Vec2){ 250.0f, 250.0f };
    myTriangle.transform.rotation = PI / 6.0f; // 초기 30도 회전 (라디안)
    myTriangle.transform.scale = (Vec2){ 1.3f, 1.3f }; // 기본 크기보다 1.3배
    // 로컬 (0,0)을 중심으로 하는 이등변 삼각형의 꼭짓점들 (위로 뾰족)
    myTriangle.local_v1 = (Vec2){ 0.0f, 30.0f };
    myTriangle.local_v2 = (Vec2){ -20.0f, -15.0f };
    myTriangle.local_v3 = (Vec2){ 20.0f, -15.0f };
    myTriangle.color_r = 0.2f; myTriangle.color_g = 0.8f; myTriangle.color_b = 0.3f; // 초록 계열

    // 3. 사각형 객체 초기화
    SquareObject mySquare;
    mySquare.transform.position = (Vec2){ 380.0f, 120.0f };
    mySquare.transform.rotation = 0.0f;
    // scale이 실제 너비/높이가 됨 (draw_square_object가 1x1 단위 사각형을 그리므로)
    mySquare.transform.scale = (Vec2){ 80.0f, 60.0f }; // 너비 80, 높이 60
    mySquare.color_r = 0.3f; mySquare.color_g = 0.3f; mySquare.color_b = 0.9f; // 파랑 계열

    // 단일 선 객체 (LineObject) 초기화
    LineObject myAnimatedLine;
    myAnimatedLine.transform.position = (Vec2){ 250.0f, 250.0f }; // 초기 위치는 화면 중앙
    myAnimatedLine.transform.rotation = 0.0f;                  // 초기 회전 없음
    myAnimatedLine.transform.scale = (Vec2){ 1.0f, 1.0f };    // 초기 크기 비율 (기본 크기)
    // 로컬 (0,0)을 중심으로 하는 길이 80의 수평선
    myAnimatedLine.local_p1 = (Vec2){ -40.0f, 0.0f };
    myAnimatedLine.local_p2 = (Vec2){ 40.0f, 0.0f };
    myAnimatedLine.thickness = 6.0f; // 기본 두께
    myAnimatedLine.color_r = 0.6f; myAnimatedLine.color_g = 0.1f; myAnimatedLine.color_b = 0.6f; // 보라색 계열

    float rotation_speed = 0.015f; // 공통 회전 속도 (라디안/프레임)
    float time_val = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        time_val = (float)glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        // 고정 도형 //

        drawEllipse(250.0f, 250.0f, 200.0f, 100.0f, 100, 0.0f, 0.0f, 0.0f); // ( 좌표 x, 좌표 y, 반지름, 높이, 세그먼트, R, G, B ) 

        drawTriangle(50.0f, 50.0f, 150.0f, 50.0f, 100.0f, 150.0f, 1.0f, 0.5f, 0.0f); // ( 좌표1 x, 좌표1 y, 좌표2 x, 좌표2 y, 좌표3 x, 좌표3 y, R, G, B )

        drawRectangle(200.0f, 50.0f, 100.0f, 75.0f, 0.5f, 0.8f, 1.0f); // ( 좌표 x, 좌표 y, 너비, 높이, R, G, B )

        drawLine(50.0f, 200.0f, 150.0f, 200.0f, 2.0f, 1.0f, 0.2f, 0.2f); // ( 시작점 좌표 x, 시작점 좌표 y, 끝점 좌표 x, 끝점 좌표 y, 굵기, R, G, B )

        drawNLine(50.0f, 300.0f, 150.0f, 300.0f, 4.0f, 1.0f, 0.2f, 0.2f); // ( 시작점 좌표 x, 시작점 좌표 y, 끝점 좌표 x, 끝점 좌표 y, 굵기, R, G, B )

        // 움직이는 도형 //

         // --- 1. 타원 애니메이션: 이동(좌우 반복) + 회전 + 크기(맥박처럼) ---
        // 이동: myEllipse.transform.position 값 변경
        myEllipse.transform.position.x = 100.0f + 50.0f * sinf(time_val * 1.2f); // 50 ~ 150 사이를 왕복
        // myEllipse.transform.position.y = 400.0f; // Y 위치는 고정 (또는 다르게 애니메이션)

        // 회전: myEllipse.transform.rotation 값 변경 (라디안)
        myEllipse.transform.rotation += 0.02f; // 일정한 속도로 회전
        if (myEllipse.transform.rotation > 2.0f * PI) myEllipse.transform.rotation -= 2.0f * PI;

        // 크기: myEllipse.transform.scale 값 변경 (X, Y 동일하게)
        float ellipse_scale_factor = 1.0f + 0.2f * sinf(time_val * 3.0f); // 0.8 ~ 1.2 사이로 스케일 변경
        myEllipse.transform.scale = (Vec2){ ellipse_scale_factor, ellipse_scale_factor };

        draw_ellipse_object(&myEllipse);


        // --- 2. 삼각형 애니메이션: 이동(원형) + 회전(느리게) + 크기(Y축만) ---
        // 이동: myTriangle.transform.position 값 변경
        float tri_orbit_radius = 30.0f;
        myTriangle.transform.position.x = 250.0f + tri_orbit_radius * cosf(time_val * 0.5f);
        myTriangle.transform.position.y = 250.0f + tri_orbit_radius * sinf(time_val * 0.5f);

        // 회전: myTriangle.transform.rotation 값 변경 (라디안)
        myTriangle.transform.rotation -= 0.005f; // 느리게 반대 방향으로 회전
        if (myTriangle.transform.rotation < 0.0f) myTriangle.transform.rotation += 2.0f * PI;

        // 크기: myTriangle.transform.scale 값 변경 (Y축만 변경)
        float triangle_y_scale = 1.0f + 0.4f * sinf(time_val * 2.5f); // 0.6 ~ 1.4 사이로 Y 스케일 변경
        myTriangle.transform.scale.y = triangle_y_scale;
        // myTriangle.transform.scale.x = 1.0f; // X 스케일은 고정 (또는 다르게 애니메이션)

        draw_triangle_object(&myTriangle);

        // --- 3. 사각형 애니메이션: 이동(고정) + 회전(진자처럼) + 크기(X,Y 비대칭) ---
        // 이동: mySquare.transform.position 값은 고정 (또는 애니메이션)
        // mySquare.transform.position = (Vec2){400.0f, 100.0f};

        // 회전: mySquare.transform.rotation 값 변경 (라디안)
        mySquare.transform.rotation = (PI / 4.0f) * sinf(time_val * 1.0f); // -45도 ~ +45도 사이를 왕복

        // 크기: mySquare.transform.scale 값 변경 (너비와 높이가 다르게)
        // transform.scale이 실제 너비/높이가 됨
        mySquare.transform.scale.x = 60.0f + 25.0f * cosf(time_val * 1.8f); // 너비 변경
        mySquare.transform.scale.y = 60.0f - 25.0f * sinf(time_val * 1.8f); // 높이 변경 (최소값 주의)
        if (mySquare.transform.scale.y < 10.0f) mySquare.transform.scale.y = 10.0f; // 최소 높이 보장

        draw_square_object(&mySquare);

        // --- 선(myAnimatedLine) 애니메이션: 이동 + 회전 + 크기 조절 모두 적용 ---

        // 1. 이동: 화면을 대각선으로 왕복 (sin, cos 조합)
        float move_radius = 100.0f;
        float move_speed = 0.7f;
        myAnimatedLine.transform.position.x = 250.0f + move_radius * cosf(time_val * move_speed);
        myAnimatedLine.transform.position.y = 250.0f + move_radius * sinf(time_val * move_speed * 0.6f); // Y축은 다른 속도로

        // 2. 회전: 계속 회전
        float rotation_speed_line = 1.0f; // 라디안/초
        myAnimatedLine.transform.rotation = time_val * rotation_speed_line;

        // 3. 크기 조절: 길이(scale.x)와 두께(scale.y)가 주기적으로 변경
        // scale.x는 선의 길이에, scale.y는 선의 두께에 주로 영향을 줍니다.
        float base_line_scale_x = 1.0f; // 기본 길이 비율
        float base_line_scale_y = 1.0f; // 기본 두께 비율
        float scale_amplitude = 0.4f;
        myAnimatedLine.transform.scale.x = base_line_scale_x + scale_amplitude * sinf(time_val * 2.0f); // 길이 파동
        myAnimatedLine.transform.scale.y = base_line_scale_y + scale_amplitude * cosf(time_val * 2.0f + PI); // 두께 파동 (위상차)
        // 스케일 값이 너무 작아지지 않도록 (예: 0.1 이하 방지)
        if (myAnimatedLine.transform.scale.x < 0.1f) myAnimatedLine.transform.scale.x = 0.1f;
        if (myAnimatedLine.transform.scale.y < 0.1f) myAnimatedLine.transform.scale.y = 0.1f;
        
        draw_line_object(&myAnimatedLine);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
