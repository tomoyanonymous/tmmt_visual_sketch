#version 150

//uniform vec2 u_mouse;
uniform vec2 resolution;
uniform float scale;
//in vec2 texCoordVarying;
uniform float time;

out vec4 outputColor;

// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

// 2D Noise based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
    (c - a)* u.y * (1.0 - u.x) +
    (d - b) * u.x * u.y;
}

void main() {
    vec2 st = gl_FragCoord.xy/resolution;

    // Scale the coordinate system to see
    // some noise in action
    vec2 pos = vec2(st*7.);

    // Use the noise function
    float r = noise(pos+time)+random(pos)*0.01;
    float g = noise(pos+0.1+time)+random(pos)*0.01;
    float b = noise(pos+0.2+time)+random(pos)*0.01;

    outputColor = vec4(r,g,b,1.0);
}


