#version 410 core

in vec3 fPos;
in vec3 fNormal;

uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 ambientColor;
uniform float ambientIntensity;

out vec4 fragColor;

void main()
{
    vec3 normal = normalize(fNormal);
    vec3 lightDirection = normalize(lightPosition - fPos);
    float diffuseMagnitude = max(dot(normal, lightDirection), 0.0);

    vec3 diffuse = diffuseMagnitude * lightColor;
    vec3 ambient = ambientColor * ambientIntensity;

    vec3 resultColor = color * (ambient + diffuse);
    fragColor = vec4(resultColor, 1.0);
}