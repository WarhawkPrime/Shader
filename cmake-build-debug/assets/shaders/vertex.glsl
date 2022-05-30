#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;

uniform float delta_colour;

uniform mat4 model_m;

out vec3 colorVS;

void main(){

    colorVS = colorRGB;

    colorVS.z = colorVS.z + delta_colour;

    gl_Position = model_m * vec4(pos.x, pos.y, pos.z, 1.0) ;
}
