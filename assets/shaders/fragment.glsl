#version 330 core

in vec3 colorVS;

//fragment shader output
out vec4 color;

void main(){

    if (colorVS.y < 1)
    {
    colorVS.y += 0.5f;
    }
    else {
    colorVS.y = 0.0f;
    }

    color = vec4(colorVS.x, colorVS.y, colorVS.z, 1.0);
}
