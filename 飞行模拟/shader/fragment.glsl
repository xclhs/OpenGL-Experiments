#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
        vec3 specular;
    float shininess;
};

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};//定向光

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};



#define NR_POINT_LIGHTS 4//结构体数组

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;
uniform Material material;
uniform SpotLight spotLight;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir);
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos-FragPos);

    //第一阶段：定向光照
    vec3 result = CalcDirLight(dirLight,norm,viewDir);
    //第二阶段：点光源
    for(int i=0;i<NR_POINT_LIGHTS;i++)
    result += CalcPointLight(pointLights[i],norm,FragPos,viewDir);

    //聚光
    result+=CalcSpotLight(spotLight,norm,FragPos,viewDir);
    FragColor=vec4(result,1.0);
}
//定向光源
vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir){
    //normal:规范化后的顶点坐标
    //light:
    //观察视角：
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal,lightDir),0.0);
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec  = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    //环境光
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
    vec3 specular = light.specular * spec * material.specular;
    return (ambient+diffuse+specular);

}

//点光源
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
    vec3 lightDir = normalize(light.position-fragPos);//与实际方向相反
    //漫反射着色
    float diff = max(dot(normal,lightDir),0.0);
    //镜面光着色
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    //衰减
    float distance = length(light.position-fragPos);
    float attenuation = 1.0/(light.constant+light.linear*distance+light.quadratic*(distance*distance));
    //合并结果
    vec3 ambient = light.ambient*vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
    vec3 specular = light.specular*spec*material.specular;

    ambient*=attenuation;
    diffuse*=attenuation;
    specular*=attenuation;
    return (ambient+diffuse+specular);
}

vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
    //漫反射着色
    vec3 lightDir = normalize(light.position-fragPos);
    float diff = max(dot(normal,lightDir),0.0);
    //镜面光着色
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    //边缘柔化
    float theta = dot(lightDir,normalize(-light.direction));
    float epsilon=(light.cutOff-light.outerCutOff);
    float intensity=clamp((theta-light.outerCutOff)/epsilon,0.0,1.0);

    //衰退
    float distance = length(light.position-FragPos);
    float attenuation = 1.0/(light.constant+light.linear*distance+light.quadratic*(distance*distance));

    //合并结果
    vec3 ambient = light.ambient*texture(material.diffuse,TexCoords).rgb;
    vec3 diffuse = light.diffuse*diff*texture(material.diffuse,TexCoords).rgb;
    vec3 specular = light.specular*spec*material.specular;

    diffuse*=intensity;
    specular*=intensity;

    ambient*=attenuation;
    diffuse*=attenuation;
    specular*=attenuation;
    return (ambient+diffuse+specular);
}