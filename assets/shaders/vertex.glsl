#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;

uniform float delta_colour = 1.0;

out vec3 colorVS;

void main(){
    delta_colour = 0.1;
    colorVS = colorRGB;
    colorVS.x = colorVS.x + 0.1;
    colorVS.y = colorVS.y + 0.1;
    colorVS.z = colorVS.z + 0.1;

    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
