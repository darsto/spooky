#version 120

attribute vec2 v_coord;
uniform sampler2D fbo_texture;
varying vec2 f_texcoord;
varying vec2 v_blurTexCoords[14];

uniform bool vertical;

void main(void) {
    gl_Position = vec4(v_coord, 0.0, 1.0);
    f_texcoord = (v_coord + 1.0) / 2.0;

/*    float blur = 0.2;
    if (vertical) {
        v_blurTexCoords[ 0] = f_texcoord + vec2(0.0, -0.028 * blur);
        v_blurTexCoords[ 1] = f_texcoord + vec2(0.0, -0.024 * blur);
        v_blurTexCoords[ 2] = f_texcoord + vec2(0.0, -0.020 * blur);
        v_blurTexCoords[ 3] = f_texcoord + vec2(0.0, -0.016 * blur);
        v_blurTexCoords[ 4] = f_texcoord + vec2(0.0, -0.012 * blur);
        v_blurTexCoords[ 5] = f_texcoord + vec2(0.0, -0.008 * blur);
        v_blurTexCoords[ 6] = f_texcoord + vec2(0.0, -0.004 * blur);
        v_blurTexCoords[ 7] = f_texcoord + vec2(0.0,  0.004 * blur);
        v_blurTexCoords[ 8] = f_texcoord + vec2(0.0,  0.008 * blur);
        v_blurTexCoords[ 9] = f_texcoord + vec2(0.0,  0.012 * blur);
        v_blurTexCoords[10] = f_texcoord + vec2(0.0,  0.016 * blur);
        v_blurTexCoords[11] = f_texcoord + vec2(0.0,  0.020 * blur);
        v_blurTexCoords[12] = f_texcoord + vec2(0.0,  0.024 * blur);
        v_blurTexCoords[13] = f_texcoord + vec2(0.0,  0.028 * blur);
    } else {
    	v_blurTexCoords[ 0] = f_texcoord + vec2(-0.028 * blur, 0.0);
        v_blurTexCoords[ 1] = f_texcoord + vec2(-0.024 * blur, 0.0);
        v_blurTexCoords[ 2] = f_texcoord + vec2(-0.020 * blur, 0.0);
        v_blurTexCoords[ 3] = f_texcoord + vec2(-0.016 * blur, 0.0);
        v_blurTexCoords[ 4] = f_texcoord + vec2(-0.012 * blur, 0.0);
        v_blurTexCoords[ 5] = f_texcoord + vec2(-0.008 * blur, 0.0);
        v_blurTexCoords[ 6] = f_texcoord + vec2(-0.004 * blur, 0.0);
        v_blurTexCoords[ 7] = f_texcoord + vec2( 0.004 * blur, 0.0);
        v_blurTexCoords[ 8] = f_texcoord + vec2( 0.008 * blur, 0.0);
        v_blurTexCoords[ 9] = f_texcoord + vec2( 0.012 * blur, 0.0);
        v_blurTexCoords[10] = f_texcoord + vec2( 0.016 * blur, 0.0);
        v_blurTexCoords[11] = f_texcoord + vec2( 0.020 * blur, 0.0);
        v_blurTexCoords[12] = f_texcoord + vec2( 0.024 * blur, 0.0);
        v_blurTexCoords[13] = f_texcoord + vec2( 0.028 * blur, 0.0);
    }*/

}