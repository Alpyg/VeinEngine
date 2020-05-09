#version 400 core
layout(location = 0) out vec4 color;

struct Material {
	sampler2D diffuse;
	vec4 color;
	sampler2D specular;
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float outerCutOff;
};

struct LightConstants {
	float constant;
	float linear;
	float quadratic;
};

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_UV;

#define NR_MAX_LIGHTS 1
uniform vec3 u_ViewPos;
uniform Material u_Material;
uniform DirLight u_DirLight;
uniform PointLight u_PointLights[NR_MAX_LIGHTS];
uniform SpotLight u_SpotLights[NR_MAX_LIGHTS];
uniform LightConstants u_Constants;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main()
{
	vec3 normal = normalize(v_Normal);
	vec3 viewDir = normalize(u_ViewPos - v_Position);


	vec3 result = CalcDirLight(u_DirLight, normal, viewDir);
	
	for (int i = 0; i < NR_MAX_LIGHTS; i++) {
		result += CalcPointLight(u_PointLights[i], normal, viewDir);
		result += CalcSpotLight(u_SpotLights[i], normal, viewDir);
	}

	color = vec4(result, 1.0f) * u_Material.color;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_UV));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, v_UV));
	vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_UV));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - v_Position);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    // attenuation
    float distance = length(light.position - v_Position);
    float attenuation = 1.0 / (u_Constants.constant + u_Constants.linear * distance + u_Constants.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_UV));
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, v_UV));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_UV));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - v_Position);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    // attenuation
    float distance = length(light.position - v_Position);
    float attenuation = 1.0 / (u_Constants.constant + u_Constants.linear * distance + u_Constants.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_UV));
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, v_UV));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_UV));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}