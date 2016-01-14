#version 120

uniform sampler2D fbo_texture;
uniform float offset;
varying vec2 f_texcoord;
varying vec2 v_blurTexCoords[14];

uniform vec2 uResolution;

uniform int lightPointsNum;
uniform vec2 lightPoints[50];
uniform float scale;

void main(void) {
    vec2 texcoord = f_texcoord;
    //texcoord.x += sin(texcoord.y * 4.0*2.0*3.14159 + offset) / 100.0;
    gl_FragColor = texture2D(fbo_texture, texcoord);

    vec2 position = gl_FragCoord.xy;
    float dist;
    float alpha = 1.0;
    for (int i = 0; i < lightPointsNum; i++) {
        dist = distance(position, lightPoints[i]) / scale;
        alpha += clamp(1.4 - dist * 0.4, 0.0, 1/alpha/alpha) / 2.5;
    }
    float screenDist = distance(position, uResolution * 0.5) / min(uResolution.x, uResolution.y);
    gl_FragColor.a *= clamp(1.0 - screenDist * 0.5, 0.6, 1.0);
    gl_FragColor.xyz *= min(alpha, 1.5);

    /*gl_FragColor = vec4(0.0);
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 0])*0.0044299121055113265;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 1])*0.00895781211794;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 2])*0.0215963866053;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 3])*0.0443683338718;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 4])*0.0776744219933;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 5])*0.115876621105;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 6])*0.147308056121;
    gl_FragColor += texture2D(fbo_texture, texcoord         )*0.159576912161;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 7])*0.147308056121;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 8])*0.115876621105;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[ 9])*0.0776744219933;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[10])*0.0443683338718;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[11])*0.0215963866053;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[12])*0.00895781211794;
    gl_FragColor += texture2D(fbo_texture, v_blurTexCoords[13])*0.0044299121055113265;*/
}