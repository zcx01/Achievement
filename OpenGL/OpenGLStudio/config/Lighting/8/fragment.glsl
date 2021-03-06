#version 330 core




//物体材质的颜色
struct Material {
    sampler2D diffuse;   //漫反射光照下物体的颜色
    sampler2D specular;  //镜面光照对物体的颜色影响
    float shininess; //影响镜面高光的散射/半径-
};





//定向光
struct DirLight  {
    vec3 direction;//一个方向

    vec3 ambient;   //环境光照的强度
    vec3 diffuse;   //漫反射光照的强度
    vec3 specular;  //镜面光照的强度
};


//点光源
struct PointLight {
    vec3 position;//世界空间位置

    float constant;//常数项(保证分母永远不会比1小),一般为1.0
    float linear;//一次项,线性的方式减少强度
    float quadratic;//二次项,以二次递减的方式减少强度

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//聚光
struct SpotLight {
    vec3 position;//世界空间位置
    vec3 direction;//一个方向
    float cutOff;//切光角
    float outerCutOff;//外切光角

    float constant;//常数项(保证分母永远不会比1小),一般为1.0
    float linear;//一次项,线性的方式减少强度
    float quadratic;//二次项,以二次递减的方式减少强度

    vec3 ambient;  //环境光照的强度
    vec3 diffuse;  //漫反射光照的强度
    vec3 specular; //镜面光照的强度
};


out vec4 color;

in vec3 Normal;         //接收顶点着色器传递的法向量
in vec3 FragPos;        //物体在世界坐标的位置
in vec2 TexCoords;
uniform vec3 viewPos;   //相机的位置-（摄像机的位置）
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[4];
uniform DirLight dirLight;
uniform SpotLight spotLight;
uniform Material material;

//计算定向光
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture2D(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture2D(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

//计算点光源
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                 light.quadratic * (distance * distance));
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture2D(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture2D(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

//计算聚光
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    //漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    //镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    //聚光
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    //合并
    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}


void main()
{
    // 法向量属性
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    // 第一阶段：定向光照
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // 第二阶段：点光源
    for(int i = 0; i < 4; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // 第三阶段：聚光
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    color = vec4(result, 1.0);

}


