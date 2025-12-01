#include<iostream>
#include"glad/glad.h"
#include"GLFW/glfw3.h"

#include"Shader.h"
#include"glMath.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


float vertices[] = {
	// vertices          // normals
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f
};


unsigned int indices[] = {
    0, 1, 2,  2, 3, 0, // Back
    4, 5, 6,  6, 7, 4, // Front
    4, 7, 3,  3, 0, 4, // Left
    5, 6, 2,  2, 1, 5, // Right
    3, 2, 6,  6, 7, 3, // Top
    0, 1, 5,  5, 4, 0  // Bottom
};

GLuint compileShader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}


int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Blinn Phong Lighting Model", NULL, NULL);

	if (!window) {

		std::cerr << "Cannot Make the window" << std::endl;

	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

		std::cerr << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	Shader shaderProgram("vertexShader.vert", "fragmentShader.frag");

    

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);






	while (!glfwWindowShouldClose(window)) {

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    shaderProgram.use();



        mat4 projection = mat4::perspective(
            radians(45.0f),                       // fov
            (float)SCR_WIDTH / (float)SCR_HEIGHT, // aspect
            0.1f,                                 // zNear
            100.0f                                // zFar
        );

        // 2. View (lookAt)
        mat4 view = mat4::lookAt(
            vec3(0.0f, 1.0f, 4.0f),  // eye
            vec3(0.0f, 0.0f, 0.0f),  // center
            vec3(0.0f, 1.0f, 0.0f)   // up
        );

        // 3. Model (rotate)
        mat4 model = mat4::identity();
        model = model * mat4::rotate(
            radians((float)glfwGetTime() * 30.0f),
            vec3(0.0f, 1.0f, 0.0f)
        );

        shaderProgram.setMat4("model", model);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    

    glfwTerminate();

	return 0;

}