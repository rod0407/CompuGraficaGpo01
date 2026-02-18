//Práctica2                                 Lopez Lopez Jose Rodrigo
//Fecha de entrega: 18 de Febrero de 2026   320098446    

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas 2D Lopez Lopez Jose Rodrigo", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
        // 1. Pico superior: C, D, E
    -0.68f,  0.63f, 0.0f,   1.0f, 0.0f, 0.0f,
    -0.34f,  0.41f, 0.0f,   1.0f, 0.0f, 0.0f,
    -0.37f,  0.35f, 0.0f,   1.0f, 0.0f, 0.0f,

    // 2. Pico inferior: C, E, F
    -0.68f,  0.63f, 0.0f,   0.8f, 0.0f, 0.0f,
    -0.37f,  0.35f, 0.0f,   0.8f, 0.0f, 0.0f,
    -0.35f,  0.28f, 0.0f,   0.8f, 0.0f, 0.0f,

    // 3. Cabeza superior: D, G, E
    -0.34f,  0.41f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.21f,  0.37f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.37f,  0.35f, 0.0f,   0.0f, 1.0f, 0.0f,

    // 4. Cabeza media: G, H, E
    -0.21f,  0.37f, 0.0f,   0.0f, 0.8f, 0.0f,
    -0.13f,  0.33f, 0.0f,   0.0f, 0.8f, 0.0f,
    -0.37f,  0.35f, 0.0f,   0.0f, 0.8f, 0.0f,

    // 5. Cabeza base: E, H, F
    -0.37f,  0.35f, 0.0f,   0.0f, 0.6f, 0.0f,
    -0.13f,  0.33f, 0.0f,   0.0f, 0.6f, 0.0f,
    -0.35f,  0.28f, 0.0f,   0.0f, 0.6f, 0.0f,

    // 6. Cuello: F, H, I
    -0.35f,  0.28f, 0.0f,   0.0f, 0.0f, 1.0f,
    -0.13f,  0.33f, 0.0f,   0.0f, 0.0f, 1.0f,
    -0.35f,  0.16f, 0.0f,   0.0f, 0.0f, 1.0f,

    // 7. Garganta: H, J, I
    -0.13f,  0.33f, 0.0f,   1.0f, 1.0f, 0.0f,
    -0.05f,  0.20f, 0.0f,   1.0f, 1.0f, 0.0f,
    -0.35f,  0.16f, 0.0f,   1.0f, 1.0f, 0.0f,

    // 8. Pecho superior: J, K, I
    -0.05f,  0.20f, 0.0f,   0.0f, 1.0f, 1.0f,
    -0.06f,  0.10f, 0.0f,   0.0f, 1.0f, 1.0f,
    -0.35f,  0.16f, 0.0f,   0.0f, 1.0f, 1.0f,

    // 9. Pecho medio: I, K, L
    -0.35f,  0.16f, 0.0f,   1.0f, 0.0f, 1.0f,
    -0.06f,  0.10f, 0.0f,   1.0f, 0.0f, 1.0f,
    -0.35f,  0.02f, 0.0f,   1.0f, 0.0f, 1.0f,

    // 10. Pecho base: L, K, M
    -0.35f,  0.02f, 0.0f,   1.0f, 0.5f, 0.0f,
    -0.06f,  0.10f, 0.0f,   1.0f, 0.5f, 0.0f,
    -0.29f, -0.20f, 0.0f,   1.0f, 0.5f, 0.0f,

    // 11. Torso: K, U, M
    -0.06f,  0.10f, 0.0f,   0.5f, 0.0f, 0.5f,
     0.12f, -0.18f, 0.0f,   0.5f, 0.0f, 0.5f,
    -0.29f, -0.20f, 0.0f,   0.5f, 0.0f, 0.5f,

    // 12. Vientre superior: M, U, V
    -0.29f, -0.20f, 0.0f,   0.4f, 0.2f, 0.0f,
     0.12f, -0.18f, 0.0f,   0.4f, 0.2f, 0.0f,
    -0.14f, -0.39f, 0.0f,   0.4f, 0.2f, 0.0f,

    // 13. Vientre base: V, U, Z
    -0.14f, -0.39f, 0.0f,   0.0f, 0.5f, 0.0f,
     0.12f, -0.18f, 0.0f,   0.0f, 0.5f, 0.0f,
     0.00f, -0.40f, 0.0f,   0.0f, 0.5f, 0.0f,

     // 14. Espalda baja: Z, U, W
      0.00f, -0.40f, 0.0f,   0.0f, 0.5f, 0.5f,
      0.12f, -0.18f, 0.0f,   0.0f, 0.5f, 0.5f,
      0.20f, -0.31f, 0.0f,   0.0f, 0.5f, 0.5f,

     // 15. Ala base: U, N, W
       0.12f, -0.18f, 0.0f,   1.0f, 0.7f, 0.0f,
       0.37f,  0.28f, 0.0f,   1.0f, 0.7f, 0.0f,
       0.20f, -0.31f, 0.0f,   1.0f, 0.7f, 0.0f,

     // 16. Ala pluma 1: N, U, T
       0.37f,  0.28f, 0.0f,   0.5f, 0.5f, 0.0f,
       0.12f, -0.18f, 0.0f,   0.5f, 0.5f, 0.0f,
       0.37f, -0.06f, 0.0f,   0.5f, 0.5f, 0.0f,

     // 17. Ala pluma 2: N, T, S
       0.37f,  0.28f, 0.0f,   0.0f, 0.0f, 0.5f,
       0.37f, -0.06f, 0.0f,   0.0f, 0.0f, 0.5f,
       0.47f,  0.05f, 0.0f,   0.0f, 0.0f, 0.5f,

     // 18. Ala pluma 3: N, S, R
       0.37f,  0.28f, 0.0f,   1.0f, 0.5f, 0.5f,
       0.47f,  0.05f, 0.0f,   1.0f, 0.5f, 0.5f,
       0.51f,  0.09f, 0.0f,   1.0f, 0.5f, 0.5f,

     // 19. Ala pluma 4: N, R, Q
       0.37f,  0.28f, 0.0f,   0.5f, 0.0f, 0.0f,
       0.51f,  0.09f, 0.0f,   0.5f, 0.0f, 0.0f,
       0.59f,  0.25f, 0.0f,   0.5f, 0.0f, 0.0f,

     // 20. Ala pluma 5: N, Q, O
       0.37f,  0.28f, 0.0f,   1.0f, 0.8f, 0.0f,
       0.59f,  0.25f, 0.0f,   1.0f, 0.8f, 0.0f,
       0.57f,  0.37f, 0.0f,   1.0f, 0.8f, 0.0f,

     // 21. Punta ala: O, Q, P
       0.57f,  0.37f, 0.0f,   0.5f, 0.0f, 0.5f,
       0.59f,  0.25f, 0.0f,   0.5f, 0.0f, 0.5f,
       0.68f,  0.41f, 0.0f,   0.5f, 0.0f, 0.5f,

     // 22. Cola base: Z, W, A1
       0.00f, -0.40f, 0.0f,   0.7f, 0.7f, 0.7f,
       0.20f, -0.31f, 0.0f,   0.7f, 0.7f, 0.7f,
       0.33f, -0.54f, 0.0f,   0.7f, 0.7f, 0.7f,

     // 23. Cola pluma 1: W, B1, A1
       0.20f, -0.31f, 0.0f,   0.2f, 0.2f, 0.2f,
       0.48f, -0.53f, 0.0f,   0.2f, 0.2f, 0.2f,
       0.33f, -0.54f, 0.0f,   0.2f, 0.2f, 0.2f,

     // 24. Cola punta: A1, B1, C1
       0.33f, -0.54f, 0.0f,   0.4f, 0.3f, 0.1f,
       0.48f, -0.53f, 0.0f,   0.4f, 0.3f, 0.1f,
       0.59f, -0.63f, 0.0f,   0.4f, 0.3f, 0.1f
	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(10);
        //glDrawArrays(GL_POINTS,0,20);
        
        //glDrawArrays(GL_LINES,0,4);
        //glDrawArrays(GL_LINE_LOOP,1,4);
        
        //glDrawArrays(GL_TRIANGLES,2,3);
		glDrawArrays(GL_TRIANGLES,0,72);
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}