// Add this at the top of the RazorEdge version of texture.glsl
#define RAZOREDGE_SHADER
#type vertex
#version 420 core

layout(location = 0) in vec3 a_WorldPosition;
layout(location = 1) in vec3 a_LocalPosition;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_Thickness;
layout(location = 4) in float a_Fade;
layout(location = 5) in int a_EntityID;

uniform mat4 u_ViewProjection;

out vec3 v_LocalPosition;
out vec4 v_Color;
out float v_Thickness;
out float v_Fade;
flat out int v_EntityID;

void main()
{
    v_LocalPosition = a_LocalPosition;
    v_Color = a_Color;
    v_Thickness = a_Thickness;
    v_Fade = a_Fade;
    v_EntityID = a_EntityID;

    gl_Position = u_ViewProjection * vec4(a_WorldPosition, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

in vec3 v_LocalPosition;
in vec4 v_Color;
in float v_Thickness;
in float v_Fade;
flat in int v_EntityID;

void main()
{
    // Calculate distance from the center
    float distance = length(v_LocalPosition);

    // Create a smooth circular fade effect
    float circle = smoothstep(1.0, 1.0 - v_Thickness, 1.0 - distance);
    circle *= smoothstep(v_Thickness + v_Fade, v_Thickness, distance);

  
    // Discard pixels outside the circle
    if (circle <= 0.0)
        discard;

    // Set output color with alpha modulated by circle value
    o_Color = v_Color;
    o_Color.a *= circle;

    // Output entity ID for picking or other effects
    o_EntityID = v_EntityID;
}	 