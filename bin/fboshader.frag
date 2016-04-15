uniform sampler2D fbo_texture;
uniform float offset;
varying vec2 f_texcoord;
varying vec2 v_blurTexCoords[14];

uniform vec2 uResolution;

uniform int lightPointsNum;
uniform vec2 lightPoints[50];
uniform float scale;
uniform float colorfulness;

void main(void) {
    vec2 texcoord = f_texcoord;
    //texcoord.x += sin(texcoord.y * 4.0*2.0*3.14159 + offset) / 500.0;
    //gl_FragColor = texture2D(fbo_texture, texcoord);

    gl_FragColor = texture2D(fbo_texture, texcoord);

    vec3 average = vec3(gl_FragColor.r + gl_FragColor.g + gl_FragColor.b) / 3.0;
    gl_FragColor.rgb = mix(average, gl_FragColor.rgb, colorfulness);

    vec2 position = gl_FragCoord.xy;
    float dist;
    float alpha = 0.0;
    for (int i = 0; i < lightPointsNum; i++) {
        dist = distance(position, lightPoints[i]) / scale;
        alpha += clamp(2.0 - dist, 0.0, 3.0) / 8.0;
    }
    float screenDist = distance(position, uResolution * 0.5) / min(uResolution.x, uResolution.y);
    gl_FragColor.a *= clamp(1.0 - screenDist * 0.5, 0.75, 0.9);
    gl_FragColor.xyz += alpha;

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