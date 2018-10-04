#version 150

//uniform vec2 u_mouse;
uniform sampler2DRect tex0;

uniform vec2 resolution;
uniform float scale;
in vec2 texCoordVarying;
uniform float time;

out vec4 outputColor;

vec3 rgb2hsb( in vec3 c ){
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz),
                 vec4(c.gb, K.xy),
                 step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r),
                 vec4(c.r, p.yzx),
                 step(p.x, c.r));
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)),
                d / (q.x + e),
                q.x);
}

//  Function from Iñigo Quiles
//  https://www.shadertoy.com/view/MsS3Wc
vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}
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
float mod289(float x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 mod289(vec4 x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 perm(vec4 x){return mod289(((x * 34.0) + 1.0) * x);}

float noise(vec3 p){
    vec3 a = floor(p);
    vec3 d = p - a;
    d = d * d * (3.0 - 2.0 * d);
    
    vec4 b = a.xxyy + vec4(0.0, 1.0, 0.0, 1.0);
    vec4 k1 = perm(b.xyxy);
    vec4 k2 = perm(k1.xyxy + b.zzww);
    
    vec4 c = k2 + a.zzzz;
    vec4 k3 = perm(c);
    vec4 k4 = perm(c + 1.0);
    
    vec4 o1 = fract(k3 * (1.0 / 41.0));
    vec4 o2 = fract(k4 * (1.0 / 41.0));
    
    vec4 o3 = o2 * d.z + o1 * (1.0 - d.z);
    vec2 o4 = o3.yw * d.x + o3.xz * (1.0 - d.x);
    
    return o4.y * d.y + o4.x * (1.0 - d.y);
}


void main() {
    vec2 st = gl_FragCoord.xy;
vec2 center = resolution/2.0;

    // Use the noise function
    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
//    vec2 center = resolution/2.0;
    float modulation =atan(sin(time*4)*1.2)*0.02+0.005;
    vec2 noisefield = 2*(vec2(0.7*(noise(vec3(st/20,1+time/20))-0.5), noise(vec3(st/20,100+time/20))-0.8 ));
    float amnt=0;

    for(int i =6;i<7;i++){
    
    vec2 ires = 100*i/resolution;
    color.r += (1.0/(scale*20*(i*2+1.0)))* texture(tex0,st+ires*scale*noisefield*1.0).r;
    color.g += (1.0/(scale*20*(i*2+1.0)))* texture(tex0,st+ires*scale*noisefield*1.0002).g;
    color.b += (1.0/(scale*20*(i*2+1.0)))* texture(tex0,st+ires*scale*noisefield*1.0005).b;
    color.a += (1.0/(scale*20*(i*2+1.0)))* texture(tex0,st+ires*scale*noisefield*1.1).a;
    amnt +=(1.0/(scale*20*(i*2+1.0)));
    }
    
    color/=amnt;
    
    vec4 colordiff =vec4(0,0,0,0.7);
    colordiff.rgb = (texture(tex0,vec2(st.x+0.,st.y)).rgb-texture(tex0,vec2(st.x-1,st.y)).rgb)+(texture(tex0,vec2(st.x,st.y+0.)).rgb-texture(tex0,vec2(st.x,st.y-1)).rgb);
    
    
    outputColor = color+colordiff*0.025;
}


