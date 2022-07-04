#version 330 core
layout (location = 0) in vec3 pos;  //v geometric vertices
layout (location = 1) in vec2 vt;   //texture vertices
layout (location = 2) in vec3 aNormal;  //vn vertex normals
//layout (location = 3) in vec3 f;       //face


uniform mat4 model_m;
uniform mat4 view_m;
uniform mat4 projection_m;

uniform vec3 camPos;


out vec3 lightDir;
out vec3 viewDir;
out vec3 FragPos;
out vec3 Normal;

out vec2 TexCoords;

void main(){

    FragPos = vec3(model_m * vec4(pos, 1.0));
    Normal = mat3(transpose(inverse(model_m))) * aNormal;

    gl_Position =  projection_m * view_m * model_m * vec4(pos, 1.0);

    viewDir = normalize(camPos - FragPos);

    TexCoords = vt;
}
