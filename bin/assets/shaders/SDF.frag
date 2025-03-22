#version 410 core
out vec4 FragColor;
in vec2 fragCoord;

layout(std140) uniform Generic{
    vec2 resolution;
    float time;
}generic;

layout(std140) uniform Ray{
    vec3 position;
    vec3 forward;
    vec3 right;
    vec3 up;
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
    vec3 surfaceColor;
    vec4 position; // use only x,y,z
    vec4 rotation; // use only x,y,z
    vec4 radius; // use only x
    vec4 halfExtents; // use x,y,z
};

layout(std140) uniform ShapeBlock {
    SDFShapeDataStruct shapes[30];
};

uniform int shapeCount;
uniform float cameraFarClip=100;

mat2 rotate2D(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

// Signed Distance Function for shapes
float sdfSphere(vec3 p, vec3 center, float radius) {
    return length(p - center) - radius;
}

float sdfBox(vec3 p, vec3 center, vec3 halfExtents, vec3 rotationDegrees) {
    vec3 q = p - center; // Translate to origin
    vec3 rotation = radians(rotationDegrees); // Convert to radians

    q.xz = rotate2D(rotation.y) * q.xz;  // Rotate around Y-axis
    q.yz = rotate2D(rotation.x) * q.yz;  // Rotate around X-axis
    q.xy = rotate2D(rotation.z) * q.xy;  // Rotate around Z-axis

    vec3 d = abs(q) - halfExtents;
    return min(max(d.x, max(d.y, d.z)), 0.0) + length(max(d, 0.0));
}

float sdfCylinder(vec3 p, vec3 center, float radius, float halfHeight, vec3 rotationDegrees) {
    vec3 q = p - center;
    vec3 rotation = radians(rotationDegrees);

    q.xz = rotate2D(rotation.y) * q.xz;  // Rotate around Y-axis
    q.yz = rotate2D(rotation.x) * q.yz;  // Rotate around X-axis
    q.xy = rotate2D(rotation.z) * q.xy;  // Rotate around Z-axis

    vec2 d = vec2(
    length(q.xz) - radius,  // Radial distance
    abs(q.y) - halfHeight   // Height limit
    );
    return max(d.x, d.y); // Keeps both height and radial limit
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

float sceneSDF(vec3 p, out int objectIndex) {
    float result = 1e6;
    objectIndex = -1; //default to indicate no shape.
    for (int i = 0; i < shapeCount; i++) {
        float d = 1e6;
        vec3 rotation = shapes[i].rotation.xyz;
        if (shapes[i].type.x == 1) { // Sphere
            d = sdfSphere(p, shapes[i].position.xyz, shapes[i].radius.x);
        }
        else if (shapes[i].type.x == 2) { // Box
            d = sdfBox(p, shapes[i].position.xyz, shapes[i].halfExtents.xyz,rotation);
        }
        else if (shapes[i].type.x == 3) { // Cylinder
            d = sdfCylinder(p, shapes[i].position.xyz, shapes[i].radius.x, shapes[i].halfExtents.y,rotation);
        }

        if(d < result)
            objectIndex = i;

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
float rayMarch(vec3 origin, vec3 direction,int steps, out vec3 hitPos, out int objectIndex) {
    float t = 0.0;
    objectIndex = -1;
    for (int i = 0; i < steps; i++) {
        hitPos = origin + t * direction;
        float d = sceneSDF(hitPos, objectIndex);
        if (d < 0.001f) {return t;}
        t += d;
        if (t > cameraFarClip) break;
    }
    return -1.0;
}

vec3 estimateNormal(vec3 p) {
    float h = 0.0001;
    int objectId; //throw this, we don't really use this here
    return normalize(vec3(
    sceneSDF(p + vec3(h, 0, 0), objectId) - sceneSDF(p - vec3(h, 0, 0), objectId),
    sceneSDF(p + vec3(0, h, 0), objectId) - sceneSDF(p - vec3(0, h, 0), objectId),
    sceneSDF(p + vec3(0, 0, h), objectId) - sceneSDF(p - vec3(0, 0, h), objectId)
    ));
}

void main() {
    vec2 uv = (gl_FragCoord.xy - 0.5 * generic.resolution) / generic.resolution.y;

    vec3 rayOrigin = ray.position;

    // compute world space properly to keep correct aspect.
    // this was a pain to figure out
    vec3 forward = normalize(ray.forward);
    vec3 right = normalize(ray.right);
    vec3 up = normalize(ray.up);
    vec3 rayDirection = normalize(forward + uv.x * right + uv.y * up); // Apply correct deviation

    vec3 hitPos;
    int objectIndex;
    float t = rayMarch(rayOrigin, rayDirection,100, hitPos, objectIndex);
    vec3 ambient = lighting.ambientColor;
    vec3 surfaceColor = shapes[objectIndex].surfaceColor;

    if (t > 0.0) {
        vec3 normal = estimateNormal(hitPos);
        vec3 sunDir = normalize(lighting.sunDirection);
        float sunContrib = max(dot(normal, sunDir), 0.0);
        vec3 diffuse = sunContrib * lighting.sunColor;
        FragColor = vec4(vec3(diffuse + ambient) * surfaceColor, 1.0);
    } else {
        FragColor = vec4(vec3(0.15, 0.15, 0.15), 1.0);
    }
}