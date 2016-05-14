#include <iostream>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <X11/Xlib.h>
#include <cstdlib>

using namespace std;

EGLSurface window;
EGLDisplay display;

GLuint LoadShader(const char *shaderSrc, GLenum type)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);
	if(shader == 0)	
		return 0;

	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);
	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1)	
		{
			char* infoLog = static_cast<char*>(malloc(sizeof(char) * infoLen));
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			cout << "Error compiling shader: " << infoLog << endl;
			
			free(infoLog);
		}

	glDeleteShader(shader);
	return 0;
	}

	return shader;
}

int Init()
{
	GLchar vShaderStr[] =
		"attribute vec4 vPosition;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vPosition;\n"
		"}\n";


	GLchar fShaderStr[] = 
		"precision mediump float;\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	// Load the vertex/fragment shaders
	vertexShader = LoadShader(vShaderStr, GL_VERTEX_SHADER);
	fragmentShader = LoadShader(fShaderStr, GL_FRAGMENT_SHADER);

	// Create the program object
	programObject = glCreateProgram();
	if(programObject == 0)
		return 0;
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	// Bind vPosition to attribute 0
	glBindAttribLocation(programObject, 0, "vPosition");

	// Link the program
	glLinkProgram(programObject);

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1)
		{
			char* infoLog = static_cast<char*>(malloc(sizeof(char) * infoLen));
			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			cout << "Error linking program: " << infoLog << endl;
			free(infoLog);
		}
		glDeleteProgram(programObject);
		return 0;
	}
	else
	{
		glUseProgram(programObject);
	}

	return 1;

}

void draw()
{
	/*
	GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
							-0.5f, -0.5f, 0.0f,
							0.5f, -0.5f, 0.0f};*/
							
GLfloat vVertices[720] = 
{
0, -1, 0, 
0.425323, -0.850654, 0.309011, 
-0.162456, -0.850654, 0.499995, 
0.723607, -0.44722, 0.525725, 
0.425323, -0.850654, 0.309011, 
0.850648, -0.525736, 0, 
0, -1, 0, 
-0.162456, -0.850654, 0.499995, 
-0.52573, -0.850652, 0, 
0, -1, 0, 
-0.52573, -0.850652, 0, 
-0.162456, -0.850654, -0.499995, 
0, -1, 0, 
-0.162456, -0.850654, -0.499995, 
0.425323, -0.850654, -0.309011, 
0.723607, -0.44722, 0.525725, 
0.850648, -0.525736, 0, 
0.951058, 0, 0.309013, 
-0.276388, -0.44722, 0.850649, 
0.262869, -0.525738, 0.809012, 
0, 0, 1, 
-0.894426, -0.447216, 0, 
-0.688189, -0.525736, 0.499997, 
-0.951058, 0, 0.309013, 
-0.276388, -0.44722, -0.850649, 
-0.688189, -0.525736, -0.499997, 
-0.587786, 0, -0.809017, 
0.723607, -0.44722, -0.525725, 
0.262869, -0.525738, -0.809012, 
0.587786, 0, -0.809017, 
0.723607, -0.44722, 0.525725, 
0.951058, 0, 0.309013, 
0.587786, 0, 0.809017, 
-0.276388, -0.44722, 0.850649, 
0, 0, 1, 
-0.587786, 0, 0.809017, 
-0.894426, -0.447216, 0, 
-0.951058, 0, 0.309013, 
-0.951058, 0, -0.309013, 
-0.276388, -0.44722, -0.850649, 
-0.587786, 0, -0.809017, 
0, 0, -1, 
0.723607, -0.44722, -0.525725, 
0.587786, 0, -0.809017, 
0.951058, 0, -0.309013, 
0.276388, 0.44722, 0.850649, 
0.688189, 0.525736, 0.499997, 
0.162456, 0.850654, 0.499995, 
-0.723607, 0.44722, 0.525725, 
-0.262869, 0.525738, 0.809012, 
-0.425323, 0.850654, 0.309011, 
-0.723607, 0.44722, -0.525725, 
-0.850648, 0.525736, 0, 
-0.425323, 0.850654, -0.309011, 
0.276388, 0.44722, -0.850649, 
-0.262869, 0.525738, -0.809012, 
0.162456, 0.850654, -0.499995, 
0.894426, 0.447216, 0, 
0.688189, 0.525736, -0.499997, 
0.52573, 0.850652, 0, 
0.52573, 0.850652, 0, 
0.162456, 0.850654, -0.499995, 
0, 1, 0, 
0.52573, 0.850652, 0, 
0.688189, 0.525736, -0.499997, 
0.162456, 0.850654, -0.499995, 
0.688189, 0.525736, -0.499997, 
0.276388, 0.44722, -0.850649, 
0.162456, 0.850654, -0.499995, 
0.162456, 0.850654, -0.499995, 
-0.425323, 0.850654, -0.309011, 
0, 1, 0, 
0.162456, 0.850654, -0.499995, 
-0.262869, 0.525738, -0.809012, 
-0.425323, 0.850654, -0.309011, 
-0.262869, 0.525738, -0.809012, 
-0.723607, 0.44722, -0.525725, 
-0.425323, 0.850654, -0.309011, 
-0.425323, 0.850654, -0.309011, 
-0.425323, 0.850654, 0.309011, 
0, 1, 0, 
-0.425323, 0.850654, -0.309011, 
-0.850648, 0.525736, 0, 
-0.425323, 0.850654, 0.309011, 
-0.850648, 0.525736, 0, 
-0.723607, 0.44722, 0.525725, 
-0.425323, 0.850654, 0.309011, 
-0.425323, 0.850654, 0.309011, 
0.162456, 0.850654, 0.499995, 
0, 1, 0, 
-0.425323, 0.850654, 0.309011, 
-0.262869, 0.525738, 0.809012, 
0.162456, 0.850654, 0.499995, 
-0.262869, 0.525738, 0.809012, 
0.276388, 0.44722, 0.850649, 
0.162456, 0.850654, 0.499995, 
0.162456, 0.850654, 0.499995, 
0.52573, 0.850652, 0, 
0, 1, 0, 
0.162456, 0.850654, 0.499995, 
0.688189, 0.525736, 0.499997, 
0.52573, 0.850652, 0, 
0.688189, 0.525736, 0.499997, 
0.894426, 0.447216, 0, 
0.52573, 0.850652, 0, 
0.951058, 0, -0.309013, 
0.688189, 0.525736, -0.499997, 
0.894426, 0.447216, 0, 
0.951058, 0, -0.309013, 
0.587786, 0, -0.809017, 
0.688189, 0.525736, -0.499997, 
0.587786, 0, -0.809017, 
0.276388, 0.44722, -0.850649, 
0.688189, 0.525736, -0.499997, 
0, 0, -1, 
-0.262869, 0.525738, -0.809012, 
0.276388, 0.44722, -0.850649, 
0, 0, -1, 
-0.587786, 0, -0.809017, 
-0.262869, 0.525738, -0.809012, 
-0.587786, 0, -0.809017, 
-0.723607, 0.44722, -0.525725, 
-0.262869, 0.525738, -0.809012, 
-0.951058, 0, -0.309013, 
-0.850648, 0.525736, 0, 
-0.723607, 0.44722, -0.525725, 
-0.951058, 0, -0.309013, 
-0.951058, 0, 0.309013, 
-0.850648, 0.525736, 0, 
-0.951058, 0, 0.309013, 
-0.723607, 0.44722, 0.525725, 
-0.850648, 0.525736, 0, 
-0.587786, 0, 0.809017, 
-0.262869, 0.525738, 0.809012, 
-0.723607, 0.44722, 0.525725, 
-0.587786, 0, 0.809017, 
0, 0, 1, 
-0.262869, 0.525738, 0.809012, 
0, 0, 1, 
0.276388, 0.44722, 0.850649, 
-0.262869, 0.525738, 0.809012, 
0.587786, 0, 0.809017, 
0.688189, 0.525736, 0.499997, 
0.276388, 0.44722, 0.850649, 
0.587786, 0, 0.809017, 
0.951058, 0, 0.309013, 
0.688189, 0.525736, 0.499997, 
0.951058, 0, 0.309013, 
0.894426, 0.447216, 0, 
0.688189, 0.525736, 0.499997, 
0.587786, 0, -0.809017, 
0, 0, -1, 
0.276388, 0.44722, -0.850649, 
0.587786, 0, -0.809017, 
0.262869, -0.525738, -0.809012, 
0, 0, -1, 
0.262869, -0.525738, -0.809012, 
-0.276388, -0.44722, -0.850649, 
0, 0, -1, 
-0.587786, 0, -0.809017, 
-0.951058, 0, -0.309013, 
-0.723607, 0.44722, -0.525725, 
-0.587786, 0, -0.809017, 
-0.688189, -0.525736, -0.499997, 
-0.951058, 0, -0.309013, 
-0.688189, -0.525736, -0.499997, 
-0.894426, -0.447216, 0, 
-0.951058, 0, -0.309013, 
-0.951058, 0, 0.309013, 
-0.587786, 0, 0.809017, 
-0.723607, 0.44722, 0.525725, 
-0.951058, 0, 0.309013, 
-0.688189, -0.525736, 0.499997, 
-0.587786, 0, 0.809017, 
-0.688189, -0.525736, 0.499997, 
-0.276388, -0.44722, 0.850649, 
-0.587786, 0, 0.809017, 
0, 0, 1, 
0.587786, 0, 0.809017, 
0.276388, 0.44722, 0.850649, 
0, 0, 1, 
0.262869, -0.525738, 0.809012, 
0.587786, 0, 0.809017, 
0.262869, -0.525738, 0.809012, 
0.723607, -0.44722, 0.525725, 
0.587786, 0, 0.809017, 
0.951058, 0, 0.309013, 
0.951058, 0, -0.309013, 
0.894426, 0.447216, 0, 
0.951058, 0, 0.309013, 
0.850648, -0.525736, 0, 
0.951058, 0, -0.309013, 
0.850648, -0.525736, 0, 
0.723607, -0.44722, -0.525725, 
0.951058, 0, -0.309013, 
0.425323, -0.850654, -0.309011, 
0.262869, -0.525738, -0.809012, 
0.723607, -0.44722, -0.525725, 
0.425323, -0.850654, -0.309011, 
-0.162456, -0.850654, -0.499995, 
0.262869, -0.525738, -0.809012, 
-0.162456, -0.850654, -0.499995, 
-0.276388, -0.44722, -0.850649, 
0.262869, -0.525738, -0.809012, 
-0.162456, -0.850654, -0.499995, 
-0.688189, -0.525736, -0.499997, 
-0.276388, -0.44722, -0.850649, 
-0.162456, -0.850654, -0.499995, 
-0.52573, -0.850652, 0, 
-0.688189, -0.525736, -0.499997, 
-0.52573, -0.850652, 0, 
-0.894426, -0.447216, 0, 
-0.688189, -0.525736, -0.499997, 
-0.52573, -0.850652, 0, 
-0.688189, -0.525736, 0.499997, 
-0.894426, -0.447216, 0, 
-0.52573, -0.850652, 0, 
-0.162456, -0.850654, 0.499995, 
-0.688189, -0.525736, 0.499997, 
-0.162456, -0.850654, 0.499995, 
-0.276388, -0.44722, 0.850649, 
-0.688189, -0.525736, 0.499997, 
0.850648, -0.525736, 0, 
0.425323, -0.850654, -0.309011, 
0.723607, -0.44722, -0.525725, 
0.850648, -0.525736, 0, 
0.425323, -0.850654, 0.309011, 
0.425323, -0.850654, -0.309011, 
0.425323, -0.850654, 0.309011, 
0, -1, 0, 
0.425323, -0.850654, -0.309011, 
-0.162456, -0.850654, 0.499995, 
0.262869, -0.525738, 0.809012, 
-0.276388, -0.44722, 0.850649, 
-0.162456, -0.850654, 0.499995, 
0.425323, -0.850654, 0.309011, 
0.262869, -0.525738, 0.809012, 
0.425323, -0.850654, 0.309011, 
0.723607, -0.44722, 0.525725, 
0.262869, -0.525738, 0.809012, 
};
/*
	GLfloat vVertices[42*3] = 
	{
		0.000000, -1.000000, 0.000000,
0.723607, -0.447220, 0.525725,
-0.276388, -0.447220, 0.850649,
-0.894426, -0.447216, 0.000000,
-0.276388, -0.447220, -0.850649,
0.723607, -0.447220, -0.525725,
 0.276388, 0.447220, 0.850649,
 -0.723607, 0.447220, 0.525725,
 -0.723607, 0.447220, -0.525725,
 0.276388, 0.447220, -0.850649,
 0.894426, 0.447216, 0.000000,
 0.000000, 1.000000, 0.000000,
 -0.162456, -0.850654, 0.499995,
 0.425323, -0.850654, 0.309011,
 0.262869, -0.525738, 0.809012,
 0.850648, -0.525736, 0.000000,
 0.425323, -0.850654, -0.309011,
 -0.525730, -0.850652, 0.000000,
 -0.688189, -0.525736, 0.499997,
 -0.162456, -0.850654, -0.499995,
 -0.688189, -0.525736, -0.499997,
 0.262869, -0.525738, -0.809012,
 0.951058, 0.000000, 0.309013,
 0.951058, 0.000000, -0.309013,
 0.000000, 0.000000, 1.000000,
 0.587786, 0.000000, 0.809017,
 -0.951058, 0.000000, 0.309013,
 -0.587786, 0.000000, 0.809017,
 -0.587786, 0.000000, -0.809017,
 -0.951058, 0.000000, -0.309013,
 0.587786, 0.000000, -0.809017,
 0.000000, 0.000000, -1.000000,
 0.688189, 0.525736, 0.499997,
 -0.262869, 0.525738, 0.809012,
 -0.850648, 0.525736, 0.000000,
 -0.262869, 0.525738, -0.809012,
 0.688189, 0.525736, -0.499997,
 0.162456, 0.850654, 0.499995,
 0.525730, 0.850652, 0.000000,
 -0.425323, 0.850654, 0.309011,
 -0.425323, 0.850654, -0.309011,
 0.162456, 0.850654, -0.499995
	};
*/
	glViewport(0, 0, 1024, 768);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 240);
	eglSwapBuffers(display, window);
	while(1){}

}

EGLBoolean InitializeWindow(EGLNativeWindowType surface_id, EGLNativeDisplayType display_id)
{
	const EGLint configAttributes[] = 
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_DEPTH_SIZE,24,
		EGL_NONE
	};

	const EGLint contextAttributes[]=
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	display = eglGetDisplay(display_id);
	if (display == EGL_NO_DISPLAY)
	{
		
		cout << "Fail to get the native display!" << endl;
		return EGL_FALSE;
	}

	EGLint major,minor;
	//EGLBoolean eglInitialize(EGLDisplay display, EGLint* majorVersion, EGLint* minorVersion);  
	if (!eglInitialize(display,&major,&minor))
	{
	
		cout << "Fail to initialize the EGL !" << endl;
		return EGL_FALSE;
	}
	else
	{
		
		cout << "The version of EGL is: " << major <<" . " << minor <<endl;
	}

	EGLConfig config;
	EGLint ConfigNum;
	if (!eglChooseConfig(display, configAttributes, &config, 1, &ConfigNum))
	{
		return EGL_FALSE;
	}

	//EGLSurface eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
	//			  EGLNativeWindowType win,
	//			  const EGLint *attrib_list);

	
	window = eglCreateWindowSurface(display, config, surface_id, NULL);
	if (window == EGL_NO_SURFACE)
	{
		return EGL_FALSE;
	}

	//eglCreateContext(EGLDisplay dpy, EGLConfig config,
	//		    EGLContext share_context,
	//		    const EGLint *attrib_list);
	EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttributes);
	if (context == EGL_NO_CONTEXT)
	{
		return EGL_FALSE;
	}

	//eglMakeCurrent(EGLDisplay dpy, EGLSurface draw,
	//		  EGLSurface read, EGLContext ctx);
	if (!eglMakeCurrent(display, window, window, context))
	{
		return EGL_FALSE;
	}

	return EGL_TRUE;
}

int main(int argc, char* argv[])
{
	Display *x_display;
	
	x_display = XOpenDisplay(NULL);
	int screen = DefaultScreen(x_display);

	Window win = XCreateSimpleWindow(x_display, RootWindow(x_display, screen), 0, 0, DisplayWidth(x_display, screen), DisplayHeight(x_display, screen), 0, 0, WhitePixel(x_display,screen) );
	XMapWindow(x_display,win);

	if (!InitializeWindow(win, x_display))
	{
		
		cout << "Intiallize the EGL window Fail!" << endl;
		return 1;
	}

	Init();
	draw();
	return 1;
}