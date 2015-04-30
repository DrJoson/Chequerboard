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

	GLfloat white_vertex_buffer[] = {
	// first white cube
	// vertices that make up front of cube
	-0.5f, -0.5f,  0.5f,  //0
	-0.5f,  0.0f,  0.5f,  //1
	 0.0f, -0.5f,  0.5f,  //2
	 0.0f,  0.0f,  0.5f   //3
	// vertices that make up back of cube 
	-0.5f, -0.5f, -0.5f,  //4
	-0.5f,  0.0f, -0.5f,  //5
	 0.0f, -0.5f, -0.5f,  //6
	 0.0f,  0.0f, -0.5f,  //7
	// second white cube
	// vertices that make up front of cube
	 0.0f, -0.5f, -0.5f,  //8
	 0.0f,  0.0f, -0.5f,  //9
	 0.5f, -0.5f, -0.5f,  //10
	 0.5f,  0.0f, -0.5f,  //11
	// vertices that make up back of cube 
	 0.0f, -0.5f, -1.0f,  //12
	 0.0f,  0.0f, -1.0f,  //13
	 0.5f, -0.5f, -1.0f,  //14
	 0.5f,  0.0f, -1.0f   //15
	};

	GLfloat black_vertex_buffer[] = {
	// first black cube
	// vertices that make up front of cube
	 0.0f, -0.5f,  0.5f,  //0
	 0.0f,  0.0f,  0.5f,  //1
	 0.5f, -0.5f,  0.5f,  //2
	 0.5f,  0.0f,  0.5f,  //3
	// vertices that make up back of cube 
	 0.0f, -0.5f, -0.5f,  //4
	 0.0f,  0.0f, -0.5f,  //5
	 0.5f, -0.5f, -0.5f,  //6
	 0.5f,  0.0f, -0.5f,  //7
	// second black cube
	// vertices that make up front of cube
	-0.5f, -0.5f, -0.5f,  //8
	-0.5f,  0.0f, -0.5f,  //9
	 0.0f, -0.5f, -0.5f,  //10
	 0.0f,  0.0f, -0.5f,  //11
	// vertices that make up back of cube 
	-0.5f, -0.5f, -1.0f,  //12
	-0.5f,  0.0f, -1.0f,  //13
	 0.0f, -0.5f, -1.0f,  //14
	 0.0f,  0.0f, -1.0f   //15
	};

	GLuint white_element_buffer_length = 72;
	GLuint white_element_buffer[]{
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
	5,7,3,
	// second white cube
	// indices that make up front of cube
	8,9,10,  
	9,11,10,  
	// indices that make up right of cube
	11,10,14,
	15,14,11,
	// indices that make up left of cube
	8,9,12,
	13,12,9,
	// indices that make up back of cube
	12,13,14,
	15,14,13,
	// indices that make up bottom of cube
	8,12,10,
	10,14,12,
	// indices that make up top of cube
	9,13,11,
	13,15,11
	};

	GLuint black_element_buffer_length = 72;
	GLuint black_element_buffer[]{
	// first black cube
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
	5,7,3,
	// second black cube
	// indices that make up front of cube
	8,9,10,  
	9,11,10,  
	// indices that make up right of cube
	11,10,14,
	15,14,11,
	// indices that make up left of cube
	8,9,12,
	13,12,9,
	// indices that make up back of cube
	12,13,14,
	15,14,13,
	// indices that make up bottom of cube
	8,12,10,
	10,14,12,
	// indices that make up top of cube
	9,13,11,
	13,15,11
	};

	// white vertex buffer object
	GLuint wvbo = 0;
	// create the buffer
	glGenBuffers(1,&wvbo);
	// bind the buffer and transfer data
	glBindBuffer(GL_ARRAY_BUFFER, wvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*48,white_vertex_buffer,GL_STATIC_DRAW);

	// black vertex buffer object
	GLuint bvbo = 0;
	// create the buffer
	glGenBuffers(1,&bvbo);
	// bind the buffer and transfer data
	glBindBuffer(GL_ARRAY_BUFFER, bvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*48,black_vertex_buffer,GL_STATIC_DRAW);
	
	// white element buffer object
	GLuint webo = 0; 
	// create the buffer
	glGenBuffers(1,&webo);
	// bind the buffer and transfar data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, webo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*white_element_buffer_length, white_element_buffer, GL_STATIC_DRAW); 

	// black element buffer object
	GLuint bebo = 0; 
	// create the buffer
	glGenBuffers(1,&bebo);
	// bind the buffer and transfar data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*black_element_buffer_length, black_element_buffer, GL_STATIC_DRAW); 

	GLuint vao = 0;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,wvbo);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,bvbo);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,webo);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,bebo);

	// set up the vertex shader
	const char* vertex_shader = "#version 130\n" "in vec3 vp;" 
	"void main (){" " gl_Position = vec4(vp,1.0);"
	"}";

	// set up the white fragment shader
	const char* white_fragment_shader = "#version 130\n" "out vec4 frag_colour;"
	"void main(){" " frag_colour = vec4(1.0,1.0,1.0,1.0);"
	"}";

	// set up the black fragment shader
	const char* black_fragment_shader = "#version 130\n" "out vec4 frag_colour;"
	"void main (){" " frag_colour = vec4(0.0,0.0,0.0,1.0);"
	"}";

	GLuint wvs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(wvs,1,&vertex_shader,NULL);
	glCompileShader(wvs);

	GLuint bvs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(bvs,1,&vertex_shader,NULL);
	glCompileShader(bvs);

	GLuint wfs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(wfs,1,&white_fragment_shader,NULL);
	glCompileShader(wfs);

	GLuint bfs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(bfs,1,&black_fragment_shader,NULL);
	glCompileShader(bfs);	

	GLuint shader_programme1 = glCreateProgram();	
	glAttachShader(shader_programme1,wfs);
	glAttachShader(shader_programme1,wvs);
	glLinkProgram(shader_programme1);

	GLuint shader_programme2 = glCreateProgram();	
	glAttachShader(shader_programme2,bfs);
	glAttachShader(shader_programme2,bvs);
	glLinkProgram(shader_programme2);
	

	// the drawing loop
	while (!glfwWindowShouldClose(window)){
	// set the colour of the drawing surface and clear it
	glClearColor(0.2,0.5,0.8,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_programme1);
	glBindVertexArray(vao);

	GLuint position_attrib = glGetAttribLocation(shader_programme1, "vp");

	glBindBuffer(GL_ARRAY_BUFFER,wvbo);
	glVertexAttribPointer(position_attrib,3,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(position_attrib);

	// draw all elements with current in-use shader
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,webo);
	glDrawElements(GL_TRIANGLES,white_element_buffer_length,GL_UNSIGNED_SHORT,(void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER,bvbo);
	glVertexAttribPointer(position_attrib,3,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(position_attrib);
	glUseProgram(shader_programme2);
	glDrawElements(GL_TRIANGLES,black_element_buffer_length,GL_UNSIGNED_SHORT,(void*)0);

	// update other events like input handling
	glfwPollEvents();
	// put the stuff we've been drawing onto the display
	glfwSwapBuffers(window);
}

	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}



