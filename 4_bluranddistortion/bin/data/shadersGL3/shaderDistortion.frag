#version 150

uniform sampler2DRect tex0;
uniform float distAmnt;
uniform float distdist;
uniform float time;
in vec2 texCoordVarying;
out vec4 outputColor;

// Gaussian weights from http://dev.theomader.com/gaussian-kernel-calculator/

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

void main()
{

    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    vec3 hsb = vec3(0.0,0.0,0.0);
    
	color += 0.05* texture(tex0, texCoordVarying + distdist*vec2(-1.0, 0.0));
    color += 0.05 * texture(tex0, texCoordVarying +  distdist*vec2(0.0, 1.0));
    color += 0.05 * texture(tex0, texCoordVarying +  distdist*vec2(1.0, 0.0));
	color += 0.05 * texture(tex0, texCoordVarying +  distdist*vec2(0.0, -1.0));
    color += 0.22 * texture(tex0, texCoordVarying +  distdist*vec2(-1.0, 1.0));
    color += 0.2 * texture(tex0, texCoordVarying +  distdist*vec2(1.0, 1.0));
    color += 0.23 * texture(tex0, texCoordVarying +  distdist*vec2(1.0, -1.0));
    color += 0.2 * texture(tex0, texCoordVarying +  distdist*vec2(-1.0, -1.0));
    hsb = rgb2hsb(color.xyz);
    
    hsb.r  =mod(hsb.x+0.02,360.0);
    hsb.g  +=0.1;

    color = vec4(hsb2rgb(hsb),0.7) ;
//    color.b +=0.1;

    color.r =float(color.r>0.9)*(1-color.r) *distAmnt*5;
    color.g =float(color.g>0.9)*(1-color.g) *distAmnt*5;
    color.b =float(color.b>0.9)*(1-color.b) *distAmnt*5;
    color += texture(tex0, texCoordVarying + vec2(0.0, 0.0));

    color.a=0.95;
//    color = texture(tex0, texCoordVarying + vec2(0.0, 0));


//    hsb.b -= 0.001;
//    hsb.g = atan(hsb.g*1.7)*1.2;
    
    

    outputColor = color;
}
