#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "visualSpace/cloud.cpp"
#include "visualSpace/perspective.cpp"

pointCloud GeneratedPoints;
perspective DefaultViewpoint(0, 0, 3);

const char* vertexShaderSrc = R"(
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
    vColor = aColor;
}
)";

const char* fragmentShaderSrc = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0);
}
)";

GLuint compileShader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

GLuint createProgram()
{
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

pointCloud generatePointCloud(int count){
    pointCloud data(count);
    Point newPoint;
    for (int i = 0; i < count; i++){
        newPoint.x = ((rand() % 200) / 100.0f) - 1.0f;
        newPoint.y = ((rand() % 200) / 100.0f) - 1.0f;
        newPoint.z = ((rand() % 200) / 100.0f) - 1.0f;

        newPoint.r = (rand() % 100) / 100.0f;
        newPoint.g = (rand() % 100) / 100.0f;
        newPoint.b = (rand() % 100) / 100.0f;

        data.addPoint(newPoint);
    }
    return data;
}

void processInput(GLFWwindow* window)
{
    float speed = 0.02f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) DefaultViewpoint.camYaw -= speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) DefaultViewpoint.camYaw += speed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) DefaultViewpoint.camPitch += speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) DefaultViewpoint.camPitch -= speed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) DefaultViewpoint.camRadius -= speed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) DefaultViewpoint.camRadius += speed;

    if (DefaultViewpoint.camRadius < 0.5f) DefaultViewpoint.camRadius = 0.5f;
    if (DefaultViewpoint.camPitch >  1.5f) DefaultViewpoint.camPitch =  1.5f;
    if (DefaultViewpoint.camPitch < -1.5f) DefaultViewpoint.camPitch = -1.5f;
}

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Point Cloud", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to init GLAD\n");
        return -1;
    }

    glEnable(GL_PROGRAM_POINT_SIZE);

    GeneratedPoints = generatePointCloud(100000);

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, GeneratedPoints.getPoints().size() * sizeof(Point), GeneratedPoints.getPoints().data(), GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
    glEnableVertexAttribArray(0);

    //colour
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //opacity
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //concern
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(3);

    GLuint program = createProgram();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        float aspect = (float)width / (float)height;

        glm::mat4 model = glm::mat4(1.0f);

        float camX = DefaultViewpoint.camRadius * cos(DefaultViewpoint.camPitch) * sin(DefaultViewpoint.camYaw);
        float camY = DefaultViewpoint.camRadius * sin(DefaultViewpoint.camPitch);
        float camZ = DefaultViewpoint.camRadius * cos(DefaultViewpoint.camPitch) * cos(DefaultViewpoint.camYaw);

        glm::mat4 view = glm::lookAt(
            glm::vec3(camX, camY, camZ),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 proj = glm::perspective(
            glm::radians(60.0f),
            aspect,
            0.1f,
            100.0f
        );

        glm::mat4 MVP = proj * view * model;

        GLuint loc = glGetUniformLocation(program, "MVP");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(MVP));
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);

        glDrawArrays(GL_POINTS, 0, GeneratedPoints.getPoints().size() / 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}