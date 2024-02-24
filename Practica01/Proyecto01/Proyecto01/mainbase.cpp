#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glew.h>
#include <glfw3.h>

const int WIDTH = 800, HEIGHT = 600;
float R, G, B;

void initializeColor() {
    // Generar valores aleatorios para R, G y B en el rango [0, 1]
    R = (float)rand() / RAND_MAX;
    G = (float)rand() / RAND_MAX;
    B = (float)rand() / RAND_MAX;
}

int main() {
    // Inicialización de GLFW
    if (!glfwInit()) {
        printf("Falló inicializar GLFW");
        glfwTerminate();
        return 1;
    }

    // Asignando variables de GLFW y propiedades de ventana
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Crear ventana
    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1 Ejercicio 1", NULL, NULL);
    if (!mainWindow) {
        printf("Fallo en crearse la ventana con GLFW");
        glfwTerminate();
        return 1;
    }

    // Obtener tamaño de buffer
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Asignar contexto
    glfwMakeContextCurrent(mainWindow);

    // Permitir nuevas extensiones
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("Falló inicialización de GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Asignar viewport
    glViewport(0, 0, bufferWidth, bufferHeight);
    printf("Version de OpenGL: %s \n", glGetString(GL_VERSION));
    printf("Marca: %s \n", glGetString(GL_VENDOR));
    printf("Renderer: %s \n", glGetString(GL_RENDERER));
    printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Inicializar color inicial aleatorio
    srand(time(NULL)); // Inicializar generador de números aleatorios
    initializeColor();

    float intervaloCambio = 2.0f;
    float contador = 0.0f;

    while (!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();
        contador += 0.01f;

        if (contador >= intervaloCambio) {
            // Cambiar color aleatoriamente cada 2 segundos
            initializeColor();
            contador = 0.0f;
        }

        glClearColor(R, G, B, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}