#version 150

//uniform vec2 u_mouse;
uniform sampler2DRect tex0;
uniform sampler2DRect cat;
uniform vec2 resolution;
uniform vec2 pickpoint;
uniform vec2 mouse;


in vec2 texCoordVarying;
uniform float time;
uniform float offset;
uniform float direction;

out vec4 outputColor;
float PI = 3.14159265;
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
float additive(float amp,float phase,vec2 freq,vec2 normpos){
    vec2 st = gl_FragCoord.xy;
//    float real = amp*cos(phase);
//    float imag = amp*sin(phase);
    float xfreq,yfreq;
    xfreq=(normpos.x)*freq.x;
    yfreq=(normpos.y)*freq.y;
    return amp *cos(2*PI*(xfreq+yfreq)+phase);

//    return amp *cos(2*PI*(xfreq)+phase)*cos(2*PI*(yfreq)+phase);
}
bool isswap(vec2 pos,vec2 pos2){
    float b1 = rgb2hsb(texture(tex0,pos).rgb).b;
    float b2 = rgb2hsb(texture(tex0,pos2).rgb).b;

    return (b1>0.3 ^^ b2>0.3)^^ b1>b2;
}
vec3 isswaprgb(vec2 pos,vec2 pos2){
    return vec3(texture(tex0,pos).r > texture(tex0,pos2).r,
                texture(tex0,pos).g > texture(tex0,pos2).g,
                texture(tex0,pos).b > texture(tex0,pos2).b);
}
void main() {
    float t = floor(pickpoint.x);
    bool rgbmode =false;
    vec2 st = gl_FragCoord.xy;
    bool d = direction>0;
    vec2 st2 = (d)?vec2(st.x+1,st.y):vec2(st.x,st.y+1);
    vec2 st3 = (d)?vec2(st.x-1,st.y):vec2(st.x,st.y-1);
    vec4 color = vec4(0,0,0,1);
//    bool isswap = rgb2hsb(pix1.rgb).b >rgb2hsb(pix2.rgb).b;
    
    float pos =floor( (d)? st.x : st.y );
    float cycle = floor(offset);
    bool pickornot = mod(pos+t, 3)<=0;
    pickornot = pickornot &&( mod(pos,cycle) !=0)&&noise(vec3(t/40,st))>0.15;
    bool pickornot2 = mod(floor(pos+t), 3)<=1;
    pickornot2 = pickornot2 && (mod(pos,cycle)!=1)&&noise(vec3(t/40,st))>0.15;
    
    if(rgbmode){//rgb mode
        if(pickornot){
            color.r = (isswaprgb(st,st2).r>0)? texture(tex0,st2).r:texture(tex0,st).r;
            color.g = (isswaprgb(st,st2).g>0)? texture(tex0,st2).g:texture(tex0,st).g;
            color.b = (isswaprgb(st,st2).b>0)? texture(tex0,st2).b:texture(tex0,st).b;
        }else if(pickornot2){
            color.r = (!(isswaprgb(st,st3).r>0))? texture(tex0,st3).r:texture(tex0,st).r;
            color.g = (!(isswaprgb(st,st3).g>0))? texture(tex0,st3).g:texture(tex0,st).g;
            color.b = (!(isswaprgb(st,st3).b>0))? texture(tex0,st3).b:texture(tex0,st).b;
        }else{
            color.rgb = texture(tex0,st).rgb;
        }
    }else{//brightness mode
    if(pickornot){
        color.rgb = (isswap(st,st2))? texture(tex0,st2).rgb:texture(tex0,st).rgb;
    }else if(pickornot2){
        color.rgb = (!isswap(st,st3))? texture(tex0,st3).rgb:texture(tex0,st).rgb;
    }else{//compare the brightness
        color.rgb = texture(tex0,st).rgb;
    }
    }
    outputColor = vec4(color);
//    outputColor=vec4(pickpoint.x/700,pickpoint.y/700,st.x/resolution.x,1.0);
}
