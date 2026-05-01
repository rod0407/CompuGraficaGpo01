// Practica 11                                    Lopez Lopez Jose Rodrigo 	
// Fecha de entrega : 1 de mayo de 2026           320098446

#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SOIL2/SOIL2.h"

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();

const GLuint WIDTH = 1000, HEIGHT = 800;
int SCREEN_WIDTH, SCREEN_HEIGHT;

Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;
bool    keys[1024];
bool    firstMouse = true;

glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool    active = false;
glm::vec3 Light1 = glm::vec3(0);

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f, 2.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f)
};

float vertices[] = {
     -0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f,
      0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f,
      0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f,
      0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f,
     -0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f,
     -0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f,

     -0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
     -0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

     -0.5f, 0.5f, 0.5f,-1.0f, 0.0f, 0.0f,
     -0.5f, 0.5f,-0.5f,-1.0f, 0.0f, 0.0f,
     -0.5f,-0.5f,-0.5f,-1.0f, 0.0f, 0.0f,
     -0.5f,-0.5f,-0.5f,-1.0f, 0.0f, 0.0f,
     -0.5f,-0.5f, 0.5f,-1.0f, 0.0f, 0.0f,
     -0.5f, 0.5f, 0.5f,-1.0f, 0.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
      0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
      0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
      0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

     -0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f,
      0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f,
      0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f,
      0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f,
     -0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f,
     -0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f,

     -0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
     -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
     -0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f
};

// --- Variables de Animación ---
float     rotacionPelota = 0.0f;
bool      animarPelota = false;
bool      animarPerroLibre = false;
float     rotacionPerroLibre = 0.0f;

// --- Máquina de Estados Finitos para el Perro ---
int       estadoPerro = 0;      // 0=reposo, 1=caminar, 2=girar
float     patasDelanteras = 0.0f;
float     patasTraseras = 0.0f;
float     cabeza = 0.0f;
float     cola = 0.0f;
glm::vec3 posicionPerro(0.0f, 0.0f, 0.0f);
float     rotacionPerro = 0.0f;
bool      paso = false;         // Controla la dirección del movimiento de las patas

// Definición del recorrido por el pasto
const float DIST_ETAPA[5] = {
    2.35f,              // Etapa 0: Avance inicial
    2.35f,              // Etapa 1
    4.70f,              // Etapa 2
    4.70f,              // Etapa 3
    3.3234f             // Etapa 4: Retorno a la posición inicial
};

// Ángulos de giro al terminar cada etapa
const float GIRO_ETAPA[5] = {
    -90.0f,
    -90.0f,
    -90.0f,
    -135.0f, 
     45.0f   
};

int   etapaRecorrido = 0;
float distRecorrida = 0.0f;
float rotAcumulada = 0.0f;

const float VEL_GIRO = 1.0f;
const float VEL_RESET_PATAS = 0.5f;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Animacion maquina de estados lopez Lopez Jose Rodrigo", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

    // Carga de modelos
    Model DogBody((char*)"Models/DogBody.obj");
    Model HeadDog((char*)"Models/HeadDog.obj");
    Model DogTail((char*)"Models/TailDog.obj");
    Model F_RightLeg((char*)"Models/F_RightLegDog.obj");
    Model F_LeftLeg((char*)"Models/F_LeftLegDog.obj");
    Model B_RightLeg((char*)"Models/B_RightLegDog.obj");
    Model B_LeftLeg((char*)"Models/B_LeftLegDog.obj");
    Model Piso((char*)"Models/piso.obj");
    Model Ball((char*)"Models/ball.obj");

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    lightingShader.Use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);


    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();
        Animation(); // Actualiza la lógica de la máquina de estados y rotaciones

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        lightingShader.Use();
        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);

        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Iluminación
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);

        glm::vec3 lightColor;
        lightColor.x = abs(sin(glfwGetTime() * Light1.x));
        lightColor.y = abs(sin(glfwGetTime() * Light1.y));
        lightColor.z = sin(glfwGetTime() * Light1.z);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));

        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

        glm::mat4 view = camera.GetViewMatrix();

        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 model(1);
        glm::mat4 modelTemp(1);

        // Dibujar Piso
        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Piso.Draw(lightingShader);

        // Dibujar Cuerpo del Perro (Base para las demás partes)
        model = glm::mat4(1);
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
        modelTemp = model = glm::translate(model, posicionPerro);
        modelTemp = model = glm::rotate(model, glm::radians(rotacionPerro), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        DogBody.Draw(lightingShader);

        // Partes anexas al perro (se basan en modelTemp del cuerpo)
        model = modelTemp;
        model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
        model = glm::rotate(model, glm::radians(cabeza), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        HeadDog.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
        model = glm::rotate(model, glm::radians(cola), glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        DogTail.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
        model = glm::rotate(model, glm::radians(patasDelanteras), glm::vec3(-1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        F_LeftLeg.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
        model = glm::rotate(model, glm::radians(patasDelanteras), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        F_RightLeg.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(0.082f, -0.046f, -0.218f));
        model = glm::rotate(model, glm::radians(patasTraseras), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B_LeftLeg.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
        model = glm::rotate(model, glm::radians(patasTraseras), glm::vec3(-1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B_RightLeg.Draw(lightingShader);

        // Dibujar Pelota (Con transparencia)
        model = glm::mat4(1);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
        model = glm::rotate(model, glm::radians(rotacionPelota), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Ball.Draw(lightingShader);
        glDisable(GL_BLEND);
        glBindVertexArray(0);

        lampShader.Use();
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        model = glm::mat4(1);
        model = glm::translate(model, pointLightPositions[0]);
        model = glm::scale(model, glm::vec3(0.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(FORWARD, deltaTime);

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera.ProcessKeyboard(BACKWARD, deltaTime);

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(LEFT, deltaTime);

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (keys[GLFW_KEY_T]) pointLightPositions[0].x += 0.01f;
    if (keys[GLFW_KEY_G]) pointLightPositions[0].x -= 0.01f;
    if (keys[GLFW_KEY_Y]) pointLightPositions[0].y += 0.01f;
    if (keys[GLFW_KEY_H]) pointLightPositions[0].y -= 0.01f;
    if (keys[GLFW_KEY_U]) pointLightPositions[0].z -= 0.1f;
    if (keys[GLFW_KEY_J]) pointLightPositions[0].z += 0.01f;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }

    if (keys[GLFW_KEY_SPACE])
    {
        active = !active;
        Light1 = active ? glm::vec3(0.2f, 0.8f, 1.0f) : glm::vec3(0);
    }

    if (keys[GLFW_KEY_N])
        animarPelota = !animarPelota;

    // Iniciar recorrido del perro (Tecla B)
    if (key == GLFW_KEY_B && action == GLFW_PRESS && estadoPerro == 0)
    {
        posicionPerro = glm::vec3(0.0f, 0.0f, 0.0f);
        rotacionPerro = 0.0f;
        patasDelanteras = patasTraseras = cabeza = cola = 0.0f;
        paso = false;
        etapaRecorrido = 0;
        distRecorrida = 0.0f;
        rotAcumulada = 0.0f;
        estadoPerro = 1; // Cambiar a estado "Caminar"
    }

    // Detener recorrido y reiniciar (Tecla X)
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {
        estadoPerro = 0;
        etapaRecorrido = 0;
        distRecorrida = 0.0f;
        rotAcumulada = 0.0f;
        patasDelanteras = patasTraseras = cabeza = cola = 0.0f;
        paso = false;
    }
}

// Maquina de estados y animacion
void Animation()
{
    if (animarPelota)
        rotacionPelota += 0.4f;

    if (animarPerroLibre)
        rotacionPerroLibre -= 0.6f;

    // Estado 0: Reposo (No hace nada)
    if (estadoPerro == 0)
        return;

    // Estado 1: Caminar en línea recta
    if (estadoPerro == 1)
    {
        // Animación de péndulo para las extremidades
        if (!paso)
        {
            patasDelanteras += 0.5f;
            patasTraseras += 0.5f;
            cabeza += 0.5f;
            cola += 0.5f;
            if (patasTraseras > 15.0f) paso = true;
        }
        else
        {
            patasDelanteras -= 0.5f;
            patasTraseras -= 0.5f;
            cabeza -= 0.5f;
            cola -= 0.5f;
            if (patasTraseras < -15.0f) paso = false;
        }

        // Avance según la rotación actual del perro
        float rad = glm::radians(rotacionPerro);
        posicionPerro.x += 0.003f * sinf(rad);
        posicionPerro.z += 0.003f * cosf(rad);
        distRecorrida += 0.003f;

        // Comprobar si ya recorrió la distancia de la etapa actual
        if (distRecorrida >= DIST_ETAPA[etapaRecorrido])
        {
            distRecorrida = 0.0f;
            rotAcumulada = 0.0f;
            estadoPerro = 2; // Cambiar a estado "Girar"
        }
    }
    // Estado 2: Girar en las esquinas
    else if (estadoPerro == 2)
    {
        float giroObjetivo = GIRO_ETAPA[etapaRecorrido];
        float absGiro = fabs(giroObjetivo);
        float signo = (giroObjetivo < 0.0f) ? -1.0f : 1.0f;

        // Antes de girar, regresar las patas a la posición neutral (0.0)
        if (patasDelanteras > 0.0f)
        {
            patasDelanteras -= VEL_RESET_PATAS;
            patasTraseras -= VEL_RESET_PATAS;
            cabeza -= VEL_RESET_PATAS;
            cola -= VEL_RESET_PATAS;
            if (patasDelanteras < 0.0f) patasDelanteras = patasTraseras = cabeza = cola = 0.0f;
        }
        else if (patasDelanteras < 0.0f)
        {
            patasDelanteras += VEL_RESET_PATAS;
            patasTraseras += VEL_RESET_PATAS;
            cabeza += VEL_RESET_PATAS;
            cola += VEL_RESET_PATAS;
            if (patasDelanteras > 0.0f) patasDelanteras = patasTraseras = cabeza = cola = 0.0f;
        }

        // Aplicar el giro de forma progresiva
        float inc = VEL_GIRO;
        if (rotAcumulada + inc > absGiro)
            inc = absGiro - rotAcumulada; // Ajuste final para no pasarse del ángulo

        rotacionPerro += inc * signo;
        rotAcumulada += inc;

        // Comprobar si el giro se completó
        if (rotAcumulada >= absGiro)
        {
            // Redondear para evitar errores de precisión al girar
            rotacionPerro = roundf(rotacionPerro / 45.0f) * 45.0f;

            // Pasar a la siguiente etapa del recorrido
            if (etapaRecorrido < 4)
            {
                etapaRecorrido++;
            }
            else
            {
                // Si ya terminó la última etapa, reiniciar todo
                etapaRecorrido = 0;
                posicionPerro = glm::vec3(0.0f, 0.0f, 0.0f);
                rotacionPerro = 0.0f;
            }

            rotAcumulada = 0.0f;
            distRecorrida = 0.0f;
            paso = false;
            estadoPerro = 1; // Volver al estado "Caminar"
        }
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = (GLfloat)xPos;
        lastY = (GLfloat)yPos;
        firstMouse = false;
    }

    GLfloat xOffset = (GLfloat)xPos - lastX;
    GLfloat yOffset = lastY - (GLfloat)yPos;

    lastX = (GLfloat)xPos;
    lastY = (GLfloat)yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}