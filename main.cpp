#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

int main(){
	// start GL context and O/S window
	if(!glfwInit()){
	fprintf(stderr,"ERROR: could not start GLFW3\n");
	return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640,480,"Chequerboard",NULL,NULL);
	if(!window){
	fprintf(stderr,"ERROR: could not open window with GLFW3\n");
	glfwTerminate();
	return 1;
	}

	glfwMakeContextCurrent(window);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n",version);
	
	glEnable(GL_CULL_FACE);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	// vertices, shaders, etc go here

	GLfloat vertex_buffer[] = {
	// vertices that make up front of cube
	-0.5f, -0.5f,  0.5f,  //0
	-0.5f,  0.5f,  0.5f,  //1
	 0.5f, -0.5f,  0.5f,  //2
	 0.5f,  0.5f,  0.5f   //3
	// vertices that make up back of cube 
	-0.5f, -0.5f, -0.5f,  //4
	-0.5f,  0.5f, -0.5f,  //5
	 0.5f, -0.5f, -0.5f,  //6
	 0.5f,  0.5f, -0.5f   //7
	};

	GLuint element_buffer_length = 36;
	GLuint element_buffer[]{
	// indices that make up front of cube
	0,1,2,  
	1,3,2,  
	// indices that make up right of cube
	3,2,6,
	7,6,3,
	// indices that make up left of cube
	0,1,4,
	5,4,1,
	// indices that make up back of cube
	4,5,6,
	7,6,5,
	// indices that make up bottom of cube
	0,4,2,
	2,6,4,
	// indices that make up top of cube
	1,5,3,
	5,7,3
	};

	// vertex buffer object
	GLuint vbo = 0;
	// create the buffer
	glGenBuffers(1,&vbo);
	// bind the buffer and transfer data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*24,vertex_buffer,GL_STATIC_DRAW);
	
	// element buffer object
	GLuint ebo = 0; 
	// create the buffer
	glGenBuffers(1,&ebo);
	// bind the buffer and transfar data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*element_buffer_length, element_buffer, GL_STATIC_DRAW); 

	GLuint vao = 0;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);	

	// set up the vertex shader
	const char* vertex_shader = "#version 130\n" "in vec3 vp;" 
	"void main (){" " gl_Position = vec4(vp,1.0);"
	"}";

	// set up the fragment shader
	const char* fragment_shader = "#version 130\n" "out vec4 frag_colour;"
	"void main(){" " frag_colour = vec4(1.0,1.0,1.0,1.0);"
	"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs,1,&vertex_shader,NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs,1,&fragment_shader,NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();	
	glAttachShader(shader_programme,fs);
	glAttachShader(shader_programme,vs);
	glLinkProgram(shader_programme);

	

	// the drawing loop
	while (!glfwWindowShouldClose(window)){
	// set the colour of the drawing surface and clear it
	glClearColor(0.2,0.5,0.8,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_programme);
	glBindVertexArray(vao);

	GLuint position_attrib = glGetAttribLocation(shader_programme, "vp");

	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glVertexAttribPointer(position_attrib,3,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(position_attrib);

	// draw points 0-3 from the current bound VAO with current in-use shader
//	glDrawArrays(GL_TRIANGLES,0,3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glDrawElements(GL_TRIANGLES,element_buffer_length,GL_UNSIGNED_SHORT,(void*)0);
	// update other events like input handling
	glfwPollEvents();
	// put the stuff we've been drawing onto the display
	glfwSwapBuffers(window);
}

	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}



