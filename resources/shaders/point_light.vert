#version 330 core

// Координаты вершины
layout (location = 0) in vec3 aPos;
// Компоненты нормали к вершине
layout (location = 1) in vec3 aNormal;
// Текстурные координаты вершины
layout (location = 2) in vec2 aTexCoords;

// Матрица модели
uniform mat4 model;
// Матрица вида 
uniform mat4 view;
// Матрица проекции
uniform mat4 projection;

// Нормаль для фрагментного шейдера
out vec3 Normal;
// Положение фрагмента в мировых координатах
out vec3 FragPos;
// Текстурные координаты для фрагментного шейдера
out vec2 TexCoords;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0); 
   FragPos = vec3(model * vec4(aPos, 1.0));     
   Normal = mat3(transpose(inverse(model))) * aNormal;

   TexCoords = aTexCoords;
}