#pragma once

#include <string>

const std::string defaultVertexCode = R"(
#version 460 core
layout (location = 0) in vec3 v_vertexPos;
layout (location = 1) in vec4 v_vertexColor;
layout (location = 2) in vec2 v_vertexTexCoord;
layout (location = 3) in float v_vertexTexId;

out vec4 f_vertexColor;
out vec2 f_vertexTexCoord;
out flat float f_vertexTexId;

uniform mat4 u_mvp;
uniform int u_flipTexture;

void main()
{
    //flip y tex coords cause sfml loads from top to bottom
    //while opengl read bottom to top
    if (u_flipTexture == 1){
        f_vertexTexCoord = vec2(v_vertexTexCoord.x, 1.0f-v_vertexTexCoord .y);
    }else{
        f_vertexTexCoord = v_vertexTexCoord;
    }
    f_vertexColor = vec4(v_vertexColor.x/255.0f, v_vertexColor.g/255.0f, v_vertexColor.b/255.0f, v_vertexColor.a/255.0f);
    f_vertexTexId = v_vertexTexId;

    gl_Position = u_mvp * vec4(v_vertexPos, 1.0f);
}
)";

const std::string defaultFragmentCode = R"(
#version 460 core
out vec4 FragColor;

in vec4 f_vertexColor;
in vec2 f_vertexTexCoord;
in flat float f_vertexTexId;

uniform vec4 u_modelColor;

//TODO: size may need to change depending of gpu
uniform sampler2D u_textures[16];

void main()
{
    vec4 outColor;

    uint textureId = int(round(f_vertexTexId));
    vec4 sampleColor = texture(u_textures[textureId], f_vertexTexCoord);

    if (sampleColor.a < 0.03f){
        discard;
    }

    if (sampleColor.a > 0.03f){
        outColor = sampleColor * f_vertexColor * u_modelColor;
    }else{
        outColor = f_vertexColor * u_modelColor;
    }

    // outColor.r = 1.0f-f_vertexTexId;
    // outColor.g = 1.0f-f_vertexTexId;
    // outColor.b = 1.0f-f_vertexTexId;
    // outColor.a = 1;

    FragColor = outColor;

}
)";
