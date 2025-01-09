#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <cassert>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

const int Width = 800;
const int Height = 600;

std::array<glm::vec3, 3> Translacao(std::array<glm::vec3, 3> triangulo) {
  glm::mat4 identidade = glm::identity<glm::mat4>();
  glm::vec3 fatorTranslacao{ 0.5f, 0.5f, 0.5f };
  glm::mat4 matrizTranslacao = glm::translate(identidade, fatorTranslacao);

  std::array<glm::vec3, 3> novoTriangulo = {
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, 0.0f},
  };

  for (int i = 0; i < triangulo.size(); i++) {
    glm::vec3& vetor = triangulo[i];
    glm::vec4 vetor4D(vetor, 1.0f);
    vetor4D = matrizTranslacao * vetor4D;
    novoTriangulo[i] = glm::vec3(vetor4D);
  }

  return novoTriangulo;
}

std::array<glm::vec3, 3> Escala(std::array<glm::vec3, 3> triangulo) {
  glm::mat4 identidade = glm::identity<glm::mat4>();
  glm::vec3 fatorEscala{ 1.5f, 1.5f, 1.0f };  // Fator de escala ajustado
  glm::mat4 matrizEscala = glm::scale(identidade, fatorEscala);

  std::array<glm::vec3, 3> novoTriangulo = {
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, 0.0f},
  };

  for (int i = 0; i < triangulo.size(); i++) {
    glm::vec3& vetor = triangulo[i];
    glm::vec4 vetor4D(vetor, 1.0f);
    vetor4D = matrizEscala * vetor4D;
    novoTriangulo[i] = glm::vec3(vetor4D);
  }

  return novoTriangulo;
}

std::array<glm::vec3, 3> Rotacao(std::array<glm::vec3, 3> triangulo) {
  constexpr float angulo = glm::radians(45.0f);
  glm::vec3 eixoRotacao{ 1, 0, 0 };
  glm::mat4 identidade = glm::identity<glm::mat4>();
  glm::mat4 matrizRotacao = glm::rotate(identidade, angulo, eixoRotacao);

  std::array<glm::vec3, 3> novoTriangulo = {
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, 0.0f},
  };

  for (int i = 0; i < triangulo.size(); i++) {
    glm::vec3& vetor = triangulo[i];
    glm::vec4 vetor4D(vetor, 1.0f);
    vetor4D = matrizRotacao * vetor4D;
    novoTriangulo[i] = glm::vec3(vetor4D);
  }

  return novoTriangulo;
}

std::array<glm::vec3, 3> Reflexao(std::array<glm::vec3, 3> triangulo) {
  glm::mat4 matrizReflexao = glm::mat4(1.0f);
  matrizReflexao[1][1] = -1.0f;

  std::array<glm::vec3, 3> novoTriangulo = {
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, 0.0f},
  };

  for (int i = 0; i < triangulo.size(); i++) {
    glm::vec3& vetor = triangulo[i];
    glm::vec4 vetor4D(vetor, 1.0f);
    vetor4D = matrizReflexao * vetor4D;
    novoTriangulo[i] = glm::vec3(vetor4D);
  }

  return novoTriangulo;
}

void ProcessoJanela(std::string nomeJanela, std::array<glm::vec3, 3> triangulo) {
  GLFWwindow* window = glfwCreateWindow(Width, Height, nomeJanela.c_str(), nullptr, nullptr);
  assert(window);
  glfwMakeContextCurrent(window);
  assert(glewInit() == GLEW_OK);

  GLuint vBuffer;
  glGenBuffers(1, &vBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangulo), triangulo.data(), GL_STATIC_DRAW);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
    glVertexAttribPointer(0, triangulo.size() ,GL_FLOAT,GL_FALSE,0,nullptr);

    glDrawArrays(GL_TRIANGLES, 0, triangulo.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glDeleteBuffers(1, &vBuffer);
}

int main() {
  assert(glfwInit() == GLFW_TRUE);

  std::array<glm::vec3, 3> triangulo = {
    glm::vec3{-0.5f,-0.5f,0.0f},
    glm::vec3{0.5f,-0.5f,0.0f},
    glm::vec3{0.0f,0.5f,0.0f},
  };

  std::array<glm::vec3, 3> trianguloTransformado = {
    glm::vec3{0.0f,0.0f,0.0f},
    glm::vec3{0.0f,0.0f,0.0f},
    glm::vec3{0.0f,0.0f,0.0f},
  };

  glm::mat4 MatrizModel = glm::identity<glm::mat4>();

  glm::vec3 Eye{ 10,10,10 };
  glm::vec3 Center{ 0,0,0 };
  glm::vec3 Up{ 0,1,0 };

  glm::mat4 MatrizView = glm::lookAt(Eye, Center, Up);

  ProcessoJanela("Triangulo Original", triangulo);

  trianguloTransformado = Translacao(triangulo);
  ProcessoJanela("Triangulo Transladado", trianguloTransformado);

  trianguloTransformado = Escala(triangulo);
  ProcessoJanela("Triangulo Escalado", trianguloTransformado);

  trianguloTransformado = Rotacao(triangulo);
  ProcessoJanela("Triangulo Rotacionado", trianguloTransformado);

  trianguloTransformado = Reflexao(triangulo);
  ProcessoJanela("Triangulo Refletido", trianguloTransformado);

  glfwTerminate();
  return 0;
}
