#pragma once

#include <string>

const std::string defaultVertexCode = R"(
#version 460 core
layout (location = 0) in vec3 v_vertexPosition;
layout (location = 1) in vec4 v_vertexColor;
layout (location = 2) in vec2 v_vertexTexCoord;
layout (location = 3) in float v_vertexTexId;
layout (location = 4) in vec3 v_vertexNormal;

out vec3 g_vertexPosition;
out vec4 g_vertexColor;
out vec2 g_vertexTexCoord;
out float g_vertexTexId;
out mat4 g_modelTransform;

out float g_fogVisibility;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

uniform int u_flipTexture;

uniform float u_fogDensity;
uniform float u_fogGradient;

void main()
{
    if (u_flipTexture == 1){
        g_vertexTexCoord = vec2(v_vertexTexCoord.x, 1.0f-v_vertexTexCoord .y);
    }else{
        g_vertexTexCoord = v_vertexTexCoord;
    }
    g_vertexColor = vec4(v_vertexColor.x/255.0f, v_vertexColor.g/255.0f, v_vertexColor.b/255.0f, v_vertexColor.a/255.0f);
    g_vertexTexId = v_vertexTexId;
    g_vertexPosition = v_vertexPosition;
    g_modelTransform = u_model;

    vec4 worldPosition = u_model * vec4(v_vertexPosition, 1.0f);
    vec4 positionRelativeToCam = u_view * worldPosition;
    gl_Position = u_projection * positionRelativeToCam;

    float distance = length(positionRelativeToCam.xyz);
    g_fogVisibility = exp(-pow((distance*u_fogDensity), u_fogGradient));
    g_fogVisibility = clamp(g_fogVisibility, 0.0, 1.0);

}
)";

const std::string defaultGeometryCode = R"(

#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 g_vertexPosition[3];
in vec4 g_vertexColor[3];
in vec2 g_vertexTexCoord[3];
in float g_vertexTexId[3];
in mat4 g_modelTransform[3];

in float g_fogVisibility[3];

out vec4 f_vertexColor;
out vec2 f_vertexTexCoord;
out float f_vertexTexId;

out float f_fogVisibility;
out vec3 f_surfaceNormal;

void main() {
    vec3 edge1 = g_vertexPosition[1] - g_vertexPosition[0];
    vec3 edge2 = g_vertexPosition[2] - g_vertexPosition[0];

    vec3 normal = normalize(cross(edge1, edge2));
    mat3 normalMatrix = transpose(inverse(mat3(g_modelTransform[0])));
    f_surfaceNormal = normalize(normalMatrix * normal);

    for (int i = 0; i < 3; ++i) {
        f_vertexColor = g_vertexColor[i];
        f_vertexTexCoord = g_vertexTexCoord[i];
        f_vertexTexId = g_vertexTexId[i];

        f_fogVisibility = g_fogVisibility[i];

        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }

    EndPrimitive();
}


)";

const std::string defaultFragmentCode = R"(
#version 460 core
out vec4 FragColor;

in vec4 f_vertexColor;
in vec2 f_vertexTexCoord;
in float f_vertexTexId;

in vec3 f_surfaceNormal;
in float f_fogVisibility;

uniform vec4 u_modelColor;

uniform vec3 u_lightDirection;
uniform vec3 u_lightColor;
uniform float u_lightAmbient;
uniform vec3 u_fogColor;

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

    //----------------Lighting----------------//

    vec3 unitNormal = normalize( f_surfaceNormal );
    vec3 unitLightDir = -normalize( u_lightDirection );

    float nDotl = dot(unitNormal, unitLightDir);
    float brightness = max((nDotl+1.0f)/2.05, u_lightAmbient);
    vec3 diffuse = brightness * u_lightColor;

    outColor = outColor * vec4(diffuse, 1.0f);
    outColor = mix(vec4(u_fogColor, 1.0), outColor, f_fogVisibility);

    FragColor = outColor;

}
)";

const std::string instanceVertexCode = R"(
#version 460 core
layout (location = 0) in vec3 v_vertexPosition;
layout (location = 1) in vec4 v_vertexColor;
layout (location = 2) in vec2 v_vertexTexCoord;
layout (location = 3) in float v_vertexTexId;
layout (location = 4) in vec3 v_vertexNormal;
layout (location = 5) in mat4 v_instanceModel;
layout (location = 9) in vec4 v_instanceColor;

out vec3 g_vertexPosition;
out vec4 g_vertexColor;
out vec2 g_vertexTexCoord;
out float g_vertexTexId;
out mat4 g_modelTransform;

out float g_fogVisibility;

uniform mat4 u_projection;
uniform mat4 u_view;

uniform int u_flipTexture;

uniform float u_fogDensity;
uniform float u_fogGradient;

void main()
{
    if (u_flipTexture == 1){
        g_vertexTexCoord = vec2(v_vertexTexCoord.x, 1.0f-v_vertexTexCoord .y);
    }else{
        g_vertexTexCoord = v_vertexTexCoord;
    }
    // g_vertexColor = vec4(v_vertexColor.x/255.0f, v_vertexColor.g/255.0f, v_vertexColor.b/255.0f, v_vertexColor.a/255.0f);
    g_vertexColor = vec4(v_instanceColor.r/255.0f, v_instanceColor.g/255.0f, v_instanceColor.b/255.0f, v_instanceColor.a/255.0f);
    g_vertexTexId = v_vertexTexId;
    g_vertexPosition = v_vertexPosition;
    g_modelTransform = v_instanceModel;

    vec4 worldPosition = v_instanceModel * vec4(v_vertexPosition, 1.0f);
    // vec4 worldPosition = mat4(1) * vec4(v_vertexPosition, 1.0f);
    vec4 positionRelativeToCam = u_view * worldPosition;
    gl_Position = u_projection * positionRelativeToCam;

    float distance = length(positionRelativeToCam.xyz);
    g_fogVisibility = exp(-pow((distance*u_fogDensity), u_fogGradient));
    g_fogVisibility = clamp(g_fogVisibility, 0.0, 1.0);

}
)";

const std::string skyboxVertexCode = R"(

#version 460 core
layout (location = 0) in vec3 v_vertexPosition;
layout (location = 2) in vec2 v_vertexTexCoord;

out vec2 f_vertexTexCoord;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
    f_vertexTexCoord = vec2(v_vertexTexCoord.x, 1.0f-v_vertexTexCoord .y);

    gl_Position = u_projection * u_view * vec4(v_vertexPosition, 1.0f);
}

)";

const std::string skyboxFragmentCode = R"(
#version 460 core
out vec4 FragColor;

in vec2 f_vertexTexCoord;

uniform sampler2D u_texture;

void main()
{
    FragColor = texture(u_texture, f_vertexTexCoord);
}
)";
