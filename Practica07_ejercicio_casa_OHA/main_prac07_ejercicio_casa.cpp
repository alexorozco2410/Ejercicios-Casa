/* ----------------   Práctica 7 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Alumno: Orozco Hernandez ALexis ---------------*/
/*-----------------  Ejercicio casa  ---------------------*/
/*--------------------  Grupo 04  --------------------------*/
/*-----------------  Version VS 2017  ----------------------*/
#include "esfera.h"
#include "camera.h"

Esfera my_sphere(1.0);
/*
flechas
arriba: posiciona la fuente de luz arriiba del atomo
derecha: posiciona la fuente de luz a la derecha del atomo
izquierda: posiciona la fuente de luz a la izquierda del atomo
abajo: posiciona la fuente de luz abajo del atomo

J aumenta el valor de la cordenada en X de la fuente de luz
J+SHIFT diminuye el valor de la cordenada en X de la fuente de luz

K aumenta el valor de la cordenada en Y de la fuente de luz
K+SHIFT diminuye el valor de la cordenada en Y de la fuente de luz

L aumenta el valor de la cordenada en Z de la fuente de luz
L+SHIFT diminuye el valor de la cordenada en Z de la fuente de luz

M posiciona la fuente de luz en el centro (donde esta el atomo)
*/


void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, lightVAO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;


void myData(void);
void display(void);
void getResolution(void);
void animate(void);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -5.0f,
		rotX = 0.0f,
		movLX = 0.0f,
		movLY = 0.0f,
		movLZ = 0.0f;

//Lighting
//glm::vec3 lightPos(movLX, movLY, movLZ);

float	sol = 0.0f,
year = 0.0f,
day = 0.0f,
moon = 0.0f,
mars_year = 0.0f,
jupiter_year = 0.0f,
mercurio = 0.0f,
venus = 0.0f,
tierra = 0.00,
marte = 0.0f,
jupiter = 0.0f,
saturno = 0.0f,
urano = 0.0f,
neptuno = 0.0f;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,//
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//To configure Second Objecto to represet Light
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void animate(void)
{
	sol += 0.5f;
	mercurio += 1.5f;
	venus += 1.5f;
	tierra += 1.5f;
	marte += 1.1f;
	jupiter += 1.1f;
	saturno += 1.0f;
	urano += 1.0f;
	neptuno += 1.0f;
}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	//Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_light_Gouraud.vs", "shaders/shader_light_Gouraud.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	projectionShader.use();
	glm::vec3 lightPos(movLX, movLY, movLZ);
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("lightPos", lightPos);

	// create transformations and Projection
	glm::mat4 temp01 = glm::mat4(1.0f); //Temp
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to inlcude Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders}
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	//Colocar código aquí
	/*
	model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.9f, 0.2f, 0.2f));
	model = glm::rotate(model, glm::radians(sol), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere
	//glDrawArrays(GL_TRIANGLES, 0, 36);	//Light
	*/

	model = glm::mat4(1.0f); //inicializa la matriz para comenzar desde el origen (en este caso coincide con el sol que esta en el origen)
	//model = glm::rotate(model, glm::radians(mercurio), glm::vec3(-0.5, -0.1, 1));//genera el movimiento de traslacion, porque en este rotate model esta en el origen
	//model = glm::translate(model, glm::vec3(3, 0, 0));//s4e mueve 3 unidades a la derecha
	//model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0, 1, 0));//indica sobre que eje se hara la rotacion
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));													   //suponiendo que le pongamos una luna a mercurio
	temp01 = model;
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere	//mercurio


	//mercurio
	model = glm::mat4(1.0f); //inicializa la matriz para comenzar desde el origen (en este caso coincide con el sol que esta en el origen)
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(-0.5, -0.1, 1));//genera el movimiento de traslacion, porque en este rotate model esta en el origen
	model = glm::translate(model, glm::vec3(3, 0, 0));//s4e mueve 3 unidades a la derecha
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0, 1, 0));//indica sobre que eje se hara la rotacion
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));													   //suponiendo que le pongamos una luna a mercurio
	temp01 = model;
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere	//mercurio


	//venus
	//venus
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(venus), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-3.0, 0, 0));
	model = glm::rotate(model, glm::radians(venus), glm::vec3(1, 0, 0));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.8f, 0.2f, 0.0f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//venus


	//tierra
	//earth
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(tierra), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0.0, 0, 4.0));
	model = glm::rotate(model, glm::radians(tierra), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.0f, 0.0f, 0.8f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();//earth


	//
	//marte
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(marte), glm::vec3(0, 1, -0.5));
	model = glm::translate(model, glm::vec3(0, 0, -4.0));
	model = glm::rotate(model, glm::radians(marte), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	temp01 = model; //temporal esta en el centro de marte
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.7f, 0.3f, 0.1f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//marte


	//jupiter
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(jupiter), glm::vec3(-1.2, 0.0, -0.5));
	model = glm::translate(model, glm::vec3(0.0, 4.2, 0));
	model = glm::rotate(model, glm::radians(jupiter), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	temp01 = model; //temporal esta en el centro de jupiter
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.4f, 0.8f, 0.2f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();


	//saturno
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(saturno), glm::vec3(-0.5, -0.1, -1));
	model = glm::translate(model, glm::vec3(0.0, -4.5, 0));
	model = glm::rotate(model, glm::radians(saturno), glm::vec3(0, 1, 0));
	temp01 = model; //temporal esta en el centro de saturno
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 0.55f, 0.65f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();



	// urano
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(urano), glm::vec3(-0.5, 0.1, 1));
	model = glm::translate(model, glm::vec3(4.7, 0, 0));
	model = glm::rotate(model, glm::radians(urano), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	temp01 = model; //temporal esta en el centro de urano
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.0f, 0.5f, 0.8f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();



	//neptuno
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(neptuno), glm::vec3(0, -1, 0.5));
	model = glm::translate(model, glm::vec3(0.0, 0, -4.5));
	model = glm::rotate(model, glm::radians(neptuno), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	temp01 = model; //temporal esta en el centro de neptuno
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.4f, 0.0f, 0.8f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();


	lampShader.use();//esto es para indicar que shader se va a usar y poder cambiar entre shaders
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(1.5f));
	lampShader.setMat4("model", model);
	my_sphere.render();	//Sphere

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light


	//glBindVertexArray(0);

}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 7", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        // input
        // -----
        my_input(window);
		animate();

        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		movLY = 20.0f;
		movLX = 0.0f;
	}
		
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		movLY = -20.0f;
		movLX = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		movLX = -20.0f;
		movLY = 0.0f;
	}
		
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		movLX = 20.0f;
		movLY = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		movLX = 0.0f;
		movLY = 0.0f;
		movLZ = 0.0f;
	}


	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			movLX -= 0.5f;
		}
		else {
			movLX += 0.5f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			movLY -= 0.5f;
		}
		else {
			movLY += 0.5f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			movLZ -= 0.5f;
		}
		else {
			movLZ += 0.5f;
		}
	}
	

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

/*
shader light vertices

version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
gl_Position = projection * view * model * vec4(aPos, 1.0f);

FragPos = vec3(model * vec4(aPos, 1.0f)); 
Normal = mat3(transpose(inverse(model))) * aNormal; 
}
*/