#include "background.h"
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define M_PI 3.14159265358979323846


extern int* arrx;
extern int* arry;
extern int* arrs;

int scale = 5;

void drawBackGround(float x, float y, float z) {
    x *= scale;
    y *= scale;

    for (float i = -0.9 * scale; i <= 1 * scale; i += 0.2 * scale) {
        largeBlock(x + i, y + 0.9f * scale, z);
    }

    for (float i = -0.95 * scale; i <= 1 * scale; i += 0.1 * scale) {
        smallBlock(x + i, y + 0.775f * scale, z);
    }

    for (float i = -1.0 * scale; i <= 1.1 * scale; i += 0.1 * scale) {
        smallBlock(x + i, y + 0.725f * scale, z);
    }

    // Draw medium blocks
    for (float i = -1.025 * scale; i <= 1.1 * scale; i += 0.1333f * scale) {
        medBlock(x + i, y + 0.595f * scale, z);
    }

    for (float i = -0.9 * scale; i <= 1 * scale; i += 0.2 * scale) {
        largeBlock(x + i, y + 0.4f * scale, z);
    }

    for (float i = -0.99 * scale; i <= 1.2 * scale; i += 0.2 * scale) {
        largeBlock(x + i, y + 0.2f * scale, z);
    }

    for (float i = -0.95 * scale; i <= 1 * scale; i += 0.1 * scale) {
        smallBlock(x + i, y + 0.075f * scale, z);
    }

    for (float i = -1.0 * scale; i <= 1.1 * scale; i += 0.1 * scale) {
        smallBlock(x + i, y + 0.025f * scale, z);
    }

    for (float i = -0.95 * scale; i <= 1 * scale; i += 0.1 * scale) {
        smallBlock(x + i, y - 0.025f * scale, z);
    }

    for (float i = -1.0 * scale; i <= 1.1 * scale; i += 0.1 * scale) {
        smallBlock(x + i, y - 0.075f * scale, z);
    }

    for (float i = -0.9 * scale; i <= 1 * scale; i += 0.2 * scale) {
        largeBlockMedH(x + i, y - 0.156f * scale, z);
    }

    for (float i = -0.99 * scale; i <= 1.2 * scale; i += 0.2 * scale) {
        largeBlock(x + i, y - 0.3f * scale, z);
    }

    for (float i = -1.0 * scale; i <= 1.1 * scale; i += 0.1333f * scale) {
        medBlock(x + i, y - 0.5f * scale, z);
    }

    for (float i = -0.99 * scale; i <= 1.2 * scale; i += 0.2 * scale) {
        largeBlock(x + i, y - 0.7f * scale, z);
    }

    for (float i = -0.9 * scale; i <= 1.0 * scale; i += 0.2 * scale) {
        largeBlock(x + i, y - 0.9f * scale, z);
    }

    borderwindow(x - 0.5f * scale, y + 0.0f * scale, z);
    window(x - 0.5f * scale, y - 0.015f * scale, z);

    borderwindow(x + 0.5f * scale, y + 0.0f * scale, z);
    window(x + 0.5f * scale, y - 0.015f * scale, z);

    torch(x + 0.0f * scale, y + 0.45f * scale, z);
    torch(x - 0.9f * scale, y + 0.45f * scale, z);
    torch(x + 0.9f * scale, y + 0.45f * scale, z);
}

void DrawCircle(float cx, float cy, float r, int num_segments, float z) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex3f(x + cx, y + cy, z);//output vertex
    }
    glEnd();
}

void DrawMoon(float cx, float cy, float r, int num_segments, float z) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
        float x = r * cosf(theta) / 2;//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex3f(x + cx, y + cy, z);//output vertex
    }
    glEnd();
}

void drawStretchedLowerHalfCircle(float x, float y, float radius, float z) {
    int num_segments = 100; // Number of segments to approximate the half circle

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, z); // Center of the circle

    for (int i = 0; i <= num_segments; i++) {
        float theta = M_PI + (M_PI * float(i) / float(num_segments)); // Angle in radians
        float dx = radius * cosf(theta) / 2.0f; // x component
        float dy = radius * sinf(theta); // y component (stretched by 2:1 ratio)

        glVertex3f(x + dx, y + dy, z);
    }

    glEnd();
}

void drawFlame(float x, float y, float baseWidth, float height, float z) {
    float flicker = (rand() % 100) / 900.0f; // Random flicker effect

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.5f + flicker, 0.0f); // Orange color
    glVertex3f(x - baseWidth / 2, y, z);
    glVertex3f(x + baseWidth / 2, y, z);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    glVertex3f(x, y + height + flicker, z); // Tip of the flame
    glEnd();
}

void drawStar(float x, float y, float Size, float z) {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex3f(x, y + Size, z);
    glVertex3f(x - Size / 2, y - Size / 2, z);
    glVertex3f(x + Size / 2, y - Size / 2, z);

    glVertex3f(x, y - Size, z);
    glVertex3f(x - Size / 2, y + Size / 2, z);
    glVertex3f(x + Size / 2, y + Size / 2, z);

    glEnd();
}

void drawNightSky(float x, float y, float width, float height, float z) {
    // Draw gradient background (dark blue to black)
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.3f); // Darker blue at the top
    glVertex3f(x - width / 2, y + height / 2, z); // Top-left
    glVertex3f(x + width / 2, y + height / 2, z); // Top-right
    glColor3f(0.0f, 0.0f, 0.0f); // Black at the bottom
    glVertex3f(x + width / 2, y - height / 2, z); // Bottom-right
    glVertex3f(x - width / 2, y - height / 2, z); // Bottom-left
    glEnd();

    // Draw stars
    int numStars = 50;
    for (int i = 0; i < numStars; i++) {
        float xxx = x + (arrx[i] % 1000 / 1000.0f * (width - 0.01) - (width - 0.01) / 2);
        float yyy = y + (arry[i] % 1000 / 1000.0f * (height - 0.01) - (height - 0.01) / 2);
        float Size = (arrs[i] % 5 + 1) / 400.0f; // Random size between 0.01 and 0.05
        drawStar(xxx, yyy, Size, z);
    }
}

void largeBlock(float x, float y, float z) {
    setGLColor(223, 191, 156);

    glBegin(GL_QUADS);

    glVertex3f(x - 0.1, y - 0.1, z);
    glVertex3f(x - 0.1, y + 0.1, z);
    glVertex3f(x + 0.1, y + 0.1, z);
    glVertex3f(x + 0.1, y - 0.1, z);

    glEnd();

    setGLColor(77, 58, 35);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x - 0.1f, y - 0.1f, z);
    glVertex3f(x - 0.1f, y + 0.1f, z);
    glVertex3f(x + 0.1f, y + 0.1f, z);
    glVertex3f(x + 0.1f, y - 0.1f, z);
    glEnd();

    glLineWidth(1.0f);
}

void largeBlockMedH(float x, float y, float z) {
    //setGLColor(215,215,225);
    setGLColor(223, 191, 156);
    glBegin(GL_QUADS);

    glVertex3f(x - 0.1, y - 0.05, z);
    glVertex3f(x - 0.1, y + 0.05, z);
    glVertex3f(x + 0.1, y + 0.05, z);
    glVertex3f(x + 0.1, y - 0.05, z);

    glEnd();

    setGLColor(77, 58, 35);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x - 0.1f, y - 0.05f, z);
    glVertex3f(x - 0.1f, y + 0.05f, z);
    glVertex3f(x + 0.1f, y + 0.05f, z);
    glVertex3f(x + 0.1f, y - 0.05f, z);
    glEnd();
    glLineWidth(1.0f);
}

void medBlock(float x, float y, float z) {
    float halfWidth = 0.1f * 2.0f / 3.0f; // 2/3 of the original width
    float halfHeight = 0.1f;

    // Draw the main quad
    //setGLColor(215,215,225);
    setGLColor(223, 191, 156);
    glBegin(GL_QUADS);
    glVertex3f(x - halfWidth, y - halfHeight, z);
    glVertex3f(x - halfWidth, y + halfHeight, z);
    glVertex3f(x + halfWidth, y + halfHeight, z);
    glVertex3f(x + halfWidth, y - halfHeight, z);
    glEnd();

    // Draw the black border
    setGLColor(77, 58, 35);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x - halfWidth, y - halfHeight, z);
    glVertex3f(x - halfWidth, y + halfHeight, z);
    glVertex3f(x + halfWidth, y + halfHeight, z);
    glVertex3f(x + halfWidth, y - halfHeight, z);
    glEnd();
    glLineWidth(1.0f);
}

void smallBlock(float x, float y, float z) {
    setGLColor(215, 87, 66);
    glBegin(GL_QUADS);

    glVertex3f(x - 0.05, y - 0.025, z);
    glVertex3f(x - 0.05, y + 0.025, z);
    glVertex3f(x + 0.05, y + 0.025, z);
    glVertex3f(x + 0.05, y - 0.025, z);

    glEnd();

    setGLColor(249, 235, 235);
    glLineWidth(4.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x - 0.05, y - 0.025, z);
    glVertex3f(x - 0.05, y + 0.025, z);
    glVertex3f(x + 0.05, y + 0.025, z);
    glVertex3f(x + 0.05, y - 0.025, z);
    glEnd();
    glLineWidth(1.0f);
}

void window(float x, float y, float z) {
    //setGLColor(206,159,111);
    setGLColor(109, 67, 42);
    glBegin(GL_TRIANGLE_FAN);
    // Blue fill
    glVertex3f(x, y + 0.5f, z);   // Center of the circle
    for (int i = 0; i <= 100; ++i) {
        float theta = static_cast<float>(i) / static_cast<float>(100) * M_PI;
        float xx = x + 0.15f * cos(theta);
        float yy = y + 0.5f + 0.15f * sin(theta);
        glVertex3f(xx, yy, z);
    }
    glEnd();
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    setGLColor(86, 41, 19); // White border
    for (int i = 0; i <= 100; ++i) {
        float theta = static_cast<float>(i) / static_cast<float>(100) * M_PI;
        float xx = x + 0.15f * cos(theta);
        float yy = y + 0.5f + 0.15f * sin(theta);
        glVertex3f(xx, yy, z);
    }
    glEnd();
    glLineWidth(1.0f);

    setGLColor(109, 67, 42);
    glBegin(GL_QUADS);

    glVertex3f(x - 0.15, y - 0.5, z);
    glVertex3f(x - 0.15, y + 0.5, z);
    glVertex3f(x + 0.15, y + 0.5, z);
    glVertex3f(x + 0.15, y - 0.5, z);

    glEnd();

    setGLColor(86, 41, 19);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);

    glVertex3f(x - 0.15, y + 0.5, z);
    glVertex3f(x - 0.15, y - 0.5, z);
    glVertex3f(x + 0.15, y - 0.5, z);
    glVertex3f(x + 0.15, y + 0.5, z);

    glEnd();
    glLineWidth(1.0f);

    glColor3f(0.0f, 0.0f, 0.3f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y + 0.48f, z);   // Center of the circle
    for (int i = 0; i <= 100; ++i) {
        float theta = static_cast<float>(i) / static_cast<float>(100) * M_PI;
        float xx = x + 0.13f * cos(theta);
        float yy = y + 0.48f + 0.13f * sin(theta);
        glVertex3f(xx, yy, z);
    }
    glEnd();
}

void borderwindow(float x, float y, float z) {
    setGLColor(245, 221, 195);
    glBegin(GL_TRIANGLE_FAN);
    // Blue fill
    glVertex3f(x, y + 0.5f, z);   // Center of the circle
    for (int i = 0; i <= 100; ++i) {
        float theta = static_cast<float>(i) / static_cast<float>(100) * M_PI;
        float xx = x + 0.2f * cos(theta);
        float yy = y + 0.5f + 0.2f * sin(theta);
        glVertex3f(xx, yy, z);
    }
    glEnd();
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
    setGLColor(89, 69, 50); // White border
    for (int i = 0; i <= 100; ++i) {
        float theta = static_cast<float>(i) / static_cast<float>(100) * M_PI;
        float xx = x + 0.2f * cos(theta);
        float yy = y + 0.5f + 0.2f * sin(theta);
        glVertex3f(xx, yy, z);
    }
    glEnd();
    glLineWidth(1.0f);

    //setGLColor(206,206,218);
    setGLColor(245, 221, 195);
    glBegin(GL_QUADS);

    glVertex3f(x - 0.2, y - 0.58, z);
    glVertex3f(x - 0.2, y + 0.52, z);
    glVertex3f(x + 0.2, y + 0.52, z);
    glVertex3f(x + 0.2, y - 0.58, z);

    glEnd();

    setGLColor(89, 69, 50);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);

    glVertex3f(x - 0.2, y + 0.52, z);
    glVertex3f(x - 0.2, y - 0.58, z);
    glVertex3f(x + 0.2, y - 0.58, z);
    glVertex3f(x + 0.2, y + 0.52, z);
    glEnd();
    glLineWidth(1.0f);

}

void torch(float x, float y, float z) {
    setGLColor(109, 67, 42);
    glBegin(GL_POLYGON);
    glVertex3f(x - 0.03, y, z);
    glVertex3f(x, y + 0.1, z);
    glVertex3f(x + 0.03, y, z);
    glVertex3f(x + 0.025, y - 0.2, z);
    glVertex3f(x, y - 0.28, z);
    glVertex3f(x - 0.025, y - 0.2, z);
    glEnd();

    setGLColor(86, 41, 19);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x - 0.03, y, z);
    glVertex3f(x, y + 0.1, z);
    glVertex3f(x + 0.03, y, z);
    glVertex3f(x + 0.025, y - 0.2, z);
    glVertex3f(x, y - 0.28, z);
    glVertex3f(x - 0.025, y - 0.2, z);
    glEnd();
    glLineWidth(1.0f);

    setGLColor(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(x - 0.004, y - 0.35, z);
    glVertex3f(x - 0.004, y, z);
    glVertex3f(x + 0.004, y, z);
    glVertex3f(x + 0.004, y - 0.35, z);
    glVertex3f(x, y - 0.4, z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x - 0.015, y - 0.07, z);
    glVertex3f(x - 0.00, y - 0.04, z);
    glVertex3f(x + 0.015, y - 0.07, z);
    glVertex3f(x + 0.00, y - 0.1, z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x - 0.015, y - 0.12, z);
    glVertex3f(x - 0.00, y - 0.09, z);
    glVertex3f(x + 0.015, y - 0.12, z);
    glVertex3f(x + 0.00, y - 0.15, z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x - 0.015, y - 0.21, z);
    glVertex3f(x - 0.00, y - 0.18, z);
    glVertex3f(x + 0.015, y - 0.21, z);
    glVertex3f(x + 0.00, y - 0.24, z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x - 0.015, y - 0.26, z);
    glVertex3f(x - 0.00, y - 0.23, z);
    glVertex3f(x + 0.015, y - 0.26, z);
    glVertex3f(x + 0.00, y - 0.29, z);
    glEnd();

    drawStretchedLowerHalfCircle(x, y + 0.05, 0.05, z);
    drawFlame(x, y + 0.05f, 0.03f, 0.05f, z);
}



void setGLColor(int red, int green, int blue) {
    GLfloat r = red / 255.0f;
    GLfloat g = green / 255.0f;
    GLfloat b = blue / 255.0f;
    glColor3f(r, g, b);
}

