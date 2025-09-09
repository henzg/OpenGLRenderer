#version 330 core
out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;
uniform vec3 DcOffset, amp, freq, phase;

vec3 palette(float t)
{
    vec3 a = DcOffset;
    vec3 b = amp;
    vec3 c = freq;
    vec3 d = phase;
    return a + b * cos(6.28318*(c*t+d));
}

void main() {
    vec2 uv = (gl_FragCoord.xy * 2.0 - iResolution.xy) / iResolution.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);
    
    for(float i = 0.0; i<6.0; i++){
        uv = fract(uv * 1.5) - 0.5;
        float d = length(uv) * exp(-length(uv0));
        vec3 col = palette(length(uv0) + i*4 + iTime*.4);
        d = sin(d*8.f + iTime)/8.f;
        d = abs(d);
        d = pow(0.0098 / d, 2.0);

        finalColor += col * d;
    } 
    FragColor = vec4(finalColor, 1.0f);
}
