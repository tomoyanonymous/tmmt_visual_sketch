#version 150

//uniform vec2 u_mouse;
uniform vec2 resolution;
uniform float scale;
uniform float rgbcorel;
//in vec2 texCoordVarying;
uniform float time;

out vec4 outputColor;

float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    return mix(a, b, u.x) +
    (c - a)* u.y * (1.0 - u.x) +
    (d - b) * u.x * u.y;
}

void main() {
    vec2 st = gl_FragCoord.xy;
    vec2 center = resolution/2;
    float radius;
    // Scale the coordinate system to see
    // some noise in action
    
    float rectsize = max(length(center-vec2(st.x,center.y)),length(center-vec2(center.x,st.y)) );
    
    float brightness =  1-pow(min(20/ (1+0.1*rectsize),1 ),10);
    
    
    outputColor = vec4(brightness,brightness,brightness,1.0);
}


