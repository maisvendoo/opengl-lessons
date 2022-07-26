#version 330 core

struct Material
{
	sampler2D diffuse;
	vec3 specular;
	float shininess;	
};

uniform Material material;

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;	
};

uniform Light light;

in vec3 Normal;
out vec4 FragColor;

uniform vec3 objectColor;

uniform vec3 viewPos;

in vec3 FragPos;

in vec2 TexCoords;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  (spec * material.specular) * light.specular;

    // Result fragment color
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}