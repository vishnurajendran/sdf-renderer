#version 410 core
out vec4 FragColor;
in vec2 fragCoord;

layout(std140) uniform Generic{
    vec2 resolution;
    float time;
}generic;

layout(std140) uniform Ray{
    vec3 position;
    vec3 direction;
}ray;

layout(std140) uniform Lighting {
    vec3 ambientColor;
    vec3 sunDirection;
    vec3 sunColor;
}lighting;


// Signed Distance Function for a sphere
float sdfSphere(vec3 centre, float radius) {
    return length(centre) - radius;
}

// Estimate normals using gradient approximation
vec3 estimateNormal(vec3 point) {
    float h = 0.001;
    return normalize(vec3(
    sdfSphere(point + vec3(h, 0, 0), 0.5) - sdfSphere(point - vec3(h, 0, 0), 0.5),
    sdfSphere(point + vec3(0, h, 0), 0.5) - sdfSphere(point - vec3(0, h, 0), 0.5),
    sdfSphere(point + vec3(0, 0, h), 0.5) - sdfSphere(point - vec3(0, 0, h), 0.5)
    ));
}

// Ray Marching function
float rayMarch(vec3 origin, vec3 direction, out vec3 hitPos) {
    float t = 0.0;
    for (int i = 0; i < 100; i++) {
        hitPos = origin + t * direction;
        float d = sdfSphere(hitPos, 0.5);
        if (d < 0.001) return t;
        t += d;
        if (t > 10.0) break;
    }
    return -1.0;
}

void main() {
    vec2 uv = (gl_FragCoord.xy - 0.5 * generic.resolution) / generic.resolution.y;
    vec3 rayOrigin = ray.position;
    vec3 rayDirection = normalize(ray.direction + vec3(uv, -1));

    vec3 hitPos;
    float t = rayMarch(rayOrigin, rayDirection, hitPos);
    vec3 ambient = lighting.ambientColor;

    if (t > 0.0) {

        vec3 normal = estimateNormal(hitPos);
        vec3 sunDir = lighting.sunDirection;
        float sunContrib = max(dot(normal, sunDir), 0.0);
        vec3 diffuse = sunContrib * lighting.sunColor;
        FragColor = vec4(vec3(diffuse + ambient), 1.0);

    } else {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}