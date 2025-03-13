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

//alignment is annoying
struct SDFShapeDataStruct {
    ivec4 type; // only use x (0-> none, 1-> sphere, 2-> box)
    ivec3 operation; //only use x (0->none, 1->union, 2-> intersection, 3-> subtraction)
    vec4 position; // use only x,y,z
    vec4 radius; // use only x
    vec4 halfExtents; // use x,y,z
};

layout(std140) uniform ShapeBlock {
    SDFShapeDataStruct shapes[10];
};

uniform int shapeCount;
uniform float cameraFarClip=100;

// Signed Distance Function for shapes
float sdfSphere(vec3 p, vec3 center, float radius) {
    return length(p - center) - radius;
}

float sdfBox(vec3 p, vec3 center, vec3 halfExtents) {
    vec3 d = abs(p - center) - halfExtents; // Distance outside the box
    return min(max(d.x, max(d.y, d.z)), 0.0) + length(max(d, 0.0)); // Handle inside and outside cases
}

// Boolean Operations
float sdfUnion(float d1, float d2) {
    return min(d1, d2);
}

float sdfIntersection(float d1, float d2) {
    return max(d1, d2);
}

float sdfSubtraction(float d1, float d2) {
    return max(d1, -d2);
}

float sdfCylinder(vec3 p, vec3 center, float radius, float halfHeight) {
    vec2 d = vec2(
    length(p.xz - center.xz) - radius,  // Radial distance
    abs(p.y - center.y) - halfHeight    // Vertical distance from the center
    );
    return max(d.x, d.y); // Ensures the cylinder is properly capped at top and bottom
}
float sceneSDF(vec3 p) {
    float result = 1e6;
    for (int i = 0; i < shapeCount; i++) {
        float d = 1e6;
        if (shapes[i].type.x == 1) { // Sphere
            d = sdfSphere(p, shapes[i].position.xyz, shapes[i].radius.x);
        }
        else if (shapes[i].type.x == 2) { // Box
            d = sdfBox(p, shapes[i].position.xyz, shapes[i].halfExtents.xyz);
        }
        else if (shapes[i].type.x == 3) { // Cylinder
            d = sdfCylinder(p, shapes[i].position.xyz, shapes[i].radius.x, shapes[i].halfExtents.y);
        }

        // Apply Boolean operations
        if (shapes[i].operation.x == 0) {  // Union
            result = sdfUnion(result, d);
        }
        else if (shapes[i].operation.x == 1) {  // Intersection
            result = sdfIntersection(result, d);
        }
        else if (shapes[i].operation.x == 2) {  // Subtraction
            result = sdfSubtraction(result, d);
        }
    }
    return result;
}

// Ray Marching function
float rayMarch(vec3 origin, vec3 direction,int steps, out vec3 hitPos) {
    float t = 0.0;
    for (int i = 0; i < steps; i++) {
        hitPos = origin + t * direction;
        float d = sceneSDF(hitPos);
        if (d < 0.001f) return t;
        t += d;
        if (t > cameraFarClip) break;
    }
    return -1.0;
}

vec3 estimateNormal(vec3 p) {
    float h = 0.0001;
    return normalize(vec3(
    sceneSDF(p + vec3(h, 0, 0)) - sceneSDF(p - vec3(h, 0, 0)),
    sceneSDF(p + vec3(0, h, 0)) - sceneSDF(p - vec3(0, h, 0)),
    sceneSDF(p + vec3(0, 0, h)) - sceneSDF(p - vec3(0, 0, h))
    ));
}

void main() {
    vec2 uv = (gl_FragCoord.xy - 0.5 * generic.resolution) / generic.resolution.y;
    vec3 rayOrigin = ray.position;
    vec3 rayDirection = normalize(ray.direction + vec3(uv, -1));

    vec3 hitPos;
    float t = rayMarch(rayOrigin, rayDirection,100, hitPos);
    vec3 ambient = lighting.ambientColor;

    if (t > 0.0) {
        vec3 normal = estimateNormal(hitPos);
        vec3 sunDir = normalize(lighting.sunDirection);
        float sunContrib = max(dot(normal, sunDir), 0.0);
        vec3 diffuse = sunContrib * lighting.sunColor;
        FragColor = vec4(vec3(diffuse + ambient), 1.0);
    } else {
        FragColor = vec4(vec3(0.105, 0.212, 0.482), 1.0);
    }
}