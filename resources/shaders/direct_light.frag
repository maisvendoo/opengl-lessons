#version 330 core

//-----------------------------------------------------------------------------
//      Структура материала
//-----------------------------------------------------------------------------
struct Material
{
	sampler2D diffuse;     // Диффузная карта (текстура)
	sampler2D specular;    // Карта отражения
	float shininess;	   // Значение коэффициента отражения
};

uniform Material material;

//-----------------------------------------------------------------------------
//      Параметры источника света
//-----------------------------------------------------------------------------
struct DirectLight
{
    // Положение
	vec3 direction;

    // Рассеянное освещение
	vec3 ambient;
    // Диффузное освещение
	vec3 diffuse;
    // Отраженный свет
	vec3 specular;	
};

uniform DirectLight light;

// Нормаль к фрагменту (из вершинного шейдера)
in vec3 Normal;
// Цвет фрагмента
out vec4 FragColor;

// Положение камеры (наблюдателя)
uniform vec3 viewPos;

// Положение фрагмента
in vec3 FragPos;

// Текстурные координаты фрагмента
in vec2 TexCoords;

void main()
{
    // Ambient (действие рассеяного света на фрагмент)
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // Diffuse (дейсвие диффузного света на фрагмент)
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // Specular (отраженный свет)
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  light.specular * spec * vec3(texture(material.specular, TexCoords));

    // Result fragment color (суммарное значение цвета фрагмента)
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}