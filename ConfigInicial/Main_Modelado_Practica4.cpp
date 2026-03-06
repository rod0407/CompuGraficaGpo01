//Practica4									Lopez Lopez Jose Rodrigo
//Fecha de entrega: 5 de Marzo de 2026		320098446

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 1200, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico Lopez Lopez Jose Rodrigo", nullptr, nullptr);

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

	// --- 1. DEFINICIÓN DE VÉRTICES ---

	// Cuerpo (Café Claro)
	float vertices[] = {
		-0.5f, -0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f, -0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f,  0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f, -0.5f,  0.5f,  0.8f, 0.5f, 0.15f,

		-0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f,  0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.15f,

		 0.5f, -0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f, -0.5f,  0.5f,  0.8f, 0.5f, 0.15f,

		-0.5f,  0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f,  0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f, -0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f,  0.5f,  0.5f,  0.8f, 0.5f, 0.15f,

		-0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f, -0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f, -0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f, -0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.15f,

		-0.5f,  0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f,  0.5f,  0.5f,  0.8f, 0.5f, 0.15f,
		-0.5f,  0.5f, -0.5f,  0.8f, 0.5f, 0.15f,
	};

	// Orejas (Café Oscuro)
	float vertices_orejas[] = {
		-0.5f, -0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f, -0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f,  0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f, -0.5f,  0.5f,  0.55f, 0.30f, 0.10f,

		-0.5f, -0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f, -0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f,  0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f, -0.5f, -0.5f,  0.55f, 0.30f, 0.10f,

		 0.5f, -0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f, -0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f, -0.5f,  0.5f,  0.55f, 0.30f, 0.10f,

		-0.5f,  0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f,  0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f, -0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f, -0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f, -0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f,  0.5f,  0.5f,  0.55f, 0.30f, 0.10f,

		-0.5f, -0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f, -0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f, -0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f, -0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f, -0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f, -0.5f, -0.5f,  0.55f, 0.30f, 0.10f,

		-0.5f,  0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f, -0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		 0.5f,  0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f,  0.5f,  0.5f,  0.55f, 0.30f, 0.10f,
		-0.5f,  0.5f, -0.5f,  0.55f, 0.30f, 0.10f
	};

	// Cola (Café Muy Oscuro)
	float vertices_cola[] = {
		-0.5f, -0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f, -0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f,  0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f, -0.5f,  0.5f,  0.35f, 0.15f, 0.05f,

		-0.5f, -0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f, -0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f,  0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f, -0.5f, -0.5f,  0.35f, 0.15f, 0.05f,

		 0.5f, -0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f, -0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f, -0.5f,  0.5f,  0.35f, 0.15f, 0.05f,

		-0.5f,  0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f,  0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f, -0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f, -0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f, -0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f,  0.5f,  0.5f,  0.35f, 0.15f, 0.05f,

		-0.5f, -0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f, -0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f, -0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f, -0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f, -0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f, -0.5f, -0.5f,  0.35f, 0.15f, 0.05f,

		-0.5f,  0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f, -0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		 0.5f,  0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f,  0.5f,  0.5f,  0.35f, 0.15f, 0.05f,
		-0.5f,  0.5f, -0.5f,  0.35f, 0.15f, 0.05f
	};

	// Cubo blanco
	float vertices_blanco[] = {
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,

		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f
	};

	// Cubo negro
	float vertices_negro[] = {
		-0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,

		-0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,

		 0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,

		-0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,

		-0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,

		-0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f
	};


	GLuint VAO[5], VBO[5];
	glGenVertexArrays(5, VAO);
	glGenBuffers(5, VBO);

	float* arreglos_vertices[] = { vertices, vertices_orejas, vertices_cola, vertices_blanco, vertices_negro };
	size_t tamanos_arreglos[] = { sizeof(vertices), sizeof(vertices_orejas), sizeof(vertices_cola), sizeof(vertices_blanco), sizeof(vertices_negro) };

	for (int i = 0; i < 5; i++) {
		glBindVertexArray(VAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, tamanos_arreglos[i], arreglos_vertices[i], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);


	while (!glfwWindowShouldClose(window)) {

		Inputs(window);
		glfwPollEvents();
		glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();

		glm::mat4 view = glm::mat4(1);
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 model;

		glBindVertexArray(VAO[0]);//Cubos café claro

		// Espalda baja
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.25f, -0.1f));
		model = glm::scale(model, glm::vec3(0.4f, 0.3f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Espalda alta
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -0.1f));
		model = glm::scale(model, glm::vec3(0.4f, 0.3f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cabeza
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.75f, 0.1f));
		model = glm::scale(model, glm::vec3(0.38f, 0.35f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Muslo Izquierdo
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, -0.15f));
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Muslo Derecho
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.2f, 0.2f, -0.15f));
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas delanteras
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.15f, 0.35f, 0.2f));
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.15f, 0.35f, 0.2f));
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(VAO[3]);//Cubos blancos

		// Pecho
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.4f, 0.16f));
		model = glm::scale(model, glm::vec3(0.25f, 0.4f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Parte blanca de la cabeza
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.82f, 0.12f));
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 0.36f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Hocico 
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.65f, 0.3f));
		model = glm::scale(model, glm::vec3(0.25f, 0.2f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas delanteras
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.15f, 0.1f, 0.22f));
		model = glm::scale(model, glm::vec3(0.16f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.15f, 0.1f, 0.22f));
		model = glm::scale(model, glm::vec3(0.16f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas traseras
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.075f, 0.0f));
		model = glm::scale(model, glm::vec3(0.16f, 0.15f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.2f, 0.075f, 0.0f));
		model = glm::scale(model, glm::vec3(0.16f, 0.15f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(VAO[1]);//Cubos cafe oscuro

		// Oreja Izquierda
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.22f, 0.65f, 0.05f));
		model = glm::scale(model, glm::vec3(0.1f, 0.3f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Oreja Derecha
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.22f, 0.65f, 0.05f));
		model = glm::scale(model, glm::vec3(0.1f, 0.3f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(VAO[4]);//Cubos negros

		// Nariz
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.7f, 0.45f));
		model = glm::scale(model, glm::vec3(0.15f, 0.08f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo Izquierdo
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.12f, 0.75f, 0.28f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo Derecho
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.12f, 0.75f, 0.28f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(VAO[2]);//Cubos cafes muy oscuro

		// Cola
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.35f, -0.32f));
		model = glm::scale(model, glm::vec3(0.08f, 0.2f, 0.08f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(5, VAO);
	glDeleteBuffers(5, VBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot -= 0.4f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot += 0.4f;
}