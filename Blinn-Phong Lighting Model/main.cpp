#include<iostream>
#include"glad/glad.h"
#include"GLFW/glfw3.h"

#include"Shader.h"
#include"glMath.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


float vertices[] = {
     -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

    // front face (z = 0.5) normal (0,0,1)
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,

    // left face (x = -0.5) normal (-1,0,0)
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,

    // right face (x = 0.5) normal (1,0,0)
     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,

     // top face (y = 0.5) normal (0,1,0)
     -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
      0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,

     // bottom face (y = -0.5) normal (0,-1,0)
     -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
      0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f
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
	Shader lightShader("lightVertex.vert", "lightFragment.frag");

    

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int lightVBO, lightVAO;
	glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    glBindVertexArray(0);




	while (!glfwWindowShouldClose(window)) {

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	    shaderProgram.use();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// lighting uniforms
        vec3 lightPos = vec3(
            2.0f * cos(glfwGetTime()),
            1.0f,
            2.0f * sin(glfwGetTime())
        );
        vec3 viewPos(0.0f, 1.0f, 4.0f);   
        vec3 lightColor(1.0f, 0.0f, 0.0f);
        vec3 objectColor(0.9f, 0.3f, 0.3f);

		shaderProgram.setVec3("lightPos", lightPos);
		shaderProgram.setVec3("viewPos", viewPos);
		shaderProgram.setVec3("lightColor", lightColor);
		shaderProgram.setVec3("objectColor", objectColor);


		//transformation matrices uniforms
        mat4 projection = mat4::perspective(
            radians(45.0f),                       
            (float)SCR_WIDTH / (float)SCR_HEIGHT, 
            0.1f,                                 
            100.0f                                
        );

        // 2. View (lookAt)
        mat4 view = mat4::lookAt(
            vec3(0.0f, 1.0f, 4.0f),  
            vec3(0.0f, 0.0f, 0.0f),  
            vec3(0.0f, 1.0f, 0.0f)   
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
        glDrawArrays(GL_TRIANGLES, 0, 36);


        mat4 lightModel = mat4::identity();
        lightModel = lightModel * mat4::translate(lightPos);
        lightModel = lightModel * mat4::scale(vec3(0.2f));
       
        lightShader.use();
		lightShader.setMat4("model", lightModel);
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		lightShader.setVec3("lightColor", lightColor);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
         

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    

    glfwTerminate();

	return 0;

}