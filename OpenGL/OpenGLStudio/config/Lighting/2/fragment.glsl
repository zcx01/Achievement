#version 330 core

out vec4 color;

in vec3 Normal;         //接收顶点着色器传递的法向量
in vec3 FragPos;        //物体在世界坐标的位置
uniform vec3 lightPos;  //光源的位置
uniform vec3 viewPos;   //相机的位置-（摄像机的位置）
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{


     //计算环境光照
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;



    //-------------计算漫反射---（法向量 * 光的方向向量）
    //[1]、计算光源和片段位置之间的的方向向量（单位向量）
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);//光的方向向量（定向光线）

    //[2]、对法向量（norm）和定向光线（lightDir）进行点乘
    float diff = max(dot(norm,lightDir),0.0);//max保证不能为负数

    //[3]、得到漫反射的分量
    vec3  diffuse = diff * lightColor;

    //-------------计算镜面光照(让它不要产生过度的影响)
    float specularStrength = 0.5;//镜面强度

    //[1]、观察者的方向向量
    vec3 viewDir = normalize(viewPos - FragPos);

    //[2]、以法向量为轴，把光线的向量对称翻转
    vec3 reflectDir = reflect(-lightDir, norm);

    //[3]、求翻转后的项目和观察者的方向向量点乘；32是高光的反光度、一个物体的反光度越高，反射光的能力越强，散射得越少，高光点就会越小
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;



    //----------将漫反射分量+环境关照分量相加
    vec3 result = (ambient+diffuse+specular) * objectColor;

    color = vec4(result,1.0);
}


