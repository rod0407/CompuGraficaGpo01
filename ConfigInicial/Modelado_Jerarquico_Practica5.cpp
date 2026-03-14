//Practica5									Lopez Lopez Jose Rodrigo
//Fecha de entrega: 13 de Marzo de 2026		320098446

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 1200, HEIGHT = 800;

float movX = 0.0f,
movY = 0.0f,
movZ = -16.0f,
rot = 0.0f;

float hombro = 0.0f,
codo = 0.0f,
muneca = 0.0f,
dedo1 = 0.0f,
dedo2 = 0.0f,
dedo3 = 0.0f;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado jerarquico Practica5 Lopez Lopez Jose Rodrigo", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    float vertices[] = {
        -0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f,  0.5f,  0.5f, 0.5f,  0.5f,  0.5f, 0.5f, -0.5f,  0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f,-0.5f,  0.5f, -0.5f,-0.5f,  0.5f,  0.5f,-0.5f,  0.5f,  0.5f,-0.5f, -0.5f,  0.5f,-0.5f, -0.5f, -0.5f,-0.5f,
         0.5f, -0.5f, 0.5f,  0.5f, -0.5f,-0.5f,  0.5f,  0.5f,-0.5f,  0.5f,  0.5f,-0.5f,  0.5f,  0.5f, 0.5f,  0.5f, -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f, -0.5f,  0.5f,-0.5f, -0.5f, -0.5f,-0.5f, -0.5f, -0.5f,-0.5f, -0.5f, -0.5f, 0.5f, -0.5f,  0.5f, 0.5f,
        -0.5f, -0.5f,-0.5f,  0.5f, -0.5f,-0.5f,  0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f,-0.5f,
        -0.5f,  0.5f,-0.5f,  0.5f,  0.5f,-0.5f,  0.5f,  0.5f, 0.5f,  0.5f,  0.5f, 0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f,-0.5f,
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        Inputs(window);
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();
        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);
        glm::mat4 modelTemp = glm::mat4(1.0f);
        glm::mat4 modelTemp2 = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
        GLint uniformColor = ourShader.uniformColor;

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);

        model = glm::translate(model, glm::vec3(0.0f, -6.0f, 0.0f));

        //Hombro
        model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
        model = glm::scale(model, glm::vec3(1.2f, 3.0f, 1.2f));
        color = glm::vec3(0.92f, 0.74f, 0.62f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Codo
        model = glm::translate(modelTemp, glm::vec3(0.0f, 1.5f, 0.0f));
        model = glm::rotate(model, glm::radians(codo), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.0f));
        color = glm::vec3(0.92f, 0.74f, 0.62f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Muneca
        model = glm::translate(modelTemp, glm::vec3(0.0f, 1.5f, 0.0f));
        model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp2 = model;

        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.8f, 2.0f, 0.6f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange1 - dedo1
        model = glm::translate(modelTemp2, glm::vec3(-1.0f, 2.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::scale(model, glm::vec3(0.35f, 0.6f, 0.35f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange2 - dedo1
        model = glm::translate(modelTemp, glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.25f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
        color = glm::vec3(0.88f, 0.67f, 0.56f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange3 - dedo1
        model = glm::translate(modelTemp, glm::vec3(0.0f, 0.25f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
        model = glm::scale(model, glm::vec3(0.25f, 0.4f, 0.25f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange1 - dedo2
        model = glm::translate(modelTemp2, glm::vec3(-0.35f, 2.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.4f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.8f, 0.4f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange2 - dedo2
        model = glm::translate(modelTemp, glm::vec3(0.0f, 0.4f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::scale(model, glm::vec3(0.35f, 0.6f, 0.35f));
        color = glm::vec3(0.88f, 0.67f, 0.56f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange3 - dedo2
        model = glm::translate(modelTemp, glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.25f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange1 - dedo3
        model = glm::translate(modelTemp2, glm::vec3(0.35f, 2.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
        model = glm::scale(model, glm::vec3(0.42f, 0.9f, 0.42f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange2 - dedo3
        model = glm::translate(modelTemp, glm::vec3(0.0f, 0.45f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.35f, 0.0f));
        model = glm::scale(model, glm::vec3(0.38f, 0.7f, 0.38f));
        color = glm::vec3(0.88f, 0.67f, 0.56f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange3 - dedo3
        model = glm::translate(modelTemp, glm::vec3(0.0f, 0.35f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::scale(model, glm::vec3(0.32f, 0.6f, 0.32f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange1 - dedo4
        model = glm::translate(modelTemp2, glm::vec3(1.0f, 2.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.4f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.8f, 0.4f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange2 - dedo4
        model = glm::translate(modelTemp, glm::vec3(0.0f, 0.4f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::scale(model, glm::vec3(0.35f, 0.6f, 0.35f));
        color = glm::vec3(0.88f, 0.67f, 0.56f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange3 - dedo4
        model = glm::translate(modelTemp, glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.25f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange1 - dedo5 Pulgar
        model = glm::translate(modelTemp2, glm::vec3(1.5f, 0.8f, 0.0f));
        model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.35f, 0.0f));
        model = glm::scale(model, glm::vec3(0.45f, 0.7f, 0.45f));
        color = glm::vec3(0.88f, 0.67f, 0.56f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //falange2 - dedo5 Pulgar
        model = glm::translate(modelTemp, glm::vec3(0.0f, 0.35f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.25f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.4f));
        color = glm::vec3(0.96f, 0.80f, 0.69f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) movX += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) movX -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) movY -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) movY += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) movZ += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) movZ -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rot += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rot -= 0.18f;


    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) hombro += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) hombro -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) codo += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) codo -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) muneca += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) muneca -= 0.18f;


    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) dedo1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) dedo1 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) dedo2 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) dedo2 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) dedo3 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) dedo3 -= 0.18f;

    hombro = glm::clamp(hombro, -90.0f, 90.0f);
    codo = glm::clamp(codo, 0.0f, 140.0f);
    muneca = glm::clamp(muneca, -90.0f, 90.0f);

    dedo1 = glm::clamp(dedo1, 0.0f, 90.0f);
    dedo2 = glm::clamp(dedo2, 0.0f, 90.0f);
    dedo3 = glm::clamp(dedo3, 0.0f, 90.0f);
}