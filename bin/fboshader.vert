#version 330

layout (location = 0) in vec2 v_coord;
uniform sampler2D fbo_texture;
varying vec2 f_texcoord;
varying vec2 v_blurTexCoords[14];

uniform bool vertical;

void main(void) {
    gl_Position = vec4(v_coord, 0.0, 1.0);
    f_texcoord = (v_coord + 1.0) / 2.0;

    if (vertical) {
        v_blurTexCoords[ 0] = f_texcoord + vec2(0.0, -0.028);
        v_blurTexCoords[ 1] = f_texcoord + vec2(0.0, -0.024);
        v_blurTexCoords[ 2] = f_texcoord + vec2(0.0, -0.020);
        v_blurTexCoords[ 3] = f_texcoord + vec2(0.0, -0.016);
        v_blurTexCoords[ 4] = f_texcoord + vec2(0.0, -0.012);
        v_blurTexCoords[ 5] = f_texcoord + vec2(0.0, -0.008);
        v_blurTexCoords[ 6] = f_texcoord + vec2(0.0, -0.004);
        v_blurTexCoords[ 7] = f_texcoord + vec2(0.0,  0.004);
        v_blurTexCoords[ 8] = f_texcoord + vec2(0.0,  0.008);
        v_blurTexCoords[ 9] = f_texcoord + vec2(0.0,  0.012);
        v_blurTexCoords[10] = f_texcoord + vec2(0.0,  0.016);
        v_blurTexCoords[11] = f_texcoord + vec2(0.0,  0.020);
        v_blurTexCoords[12] = f_texcoord + vec2(0.0,  0.024);
        v_blurTexCoords[13] = f_texcoord + vec2(0.0,  0.028);
    } else {
    	v_blurTexCoords[ 0] = f_texcoord + vec2(-0.028, 0.0);
        v_blurTexCoords[ 1] = f_texcoord + vec2(-0.024, 0.0);
        v_blurTexCoords[ 2] = f_texcoord + vec2(-0.020, 0.0);
        v_blurTexCoords[ 3] = f_texcoord + vec2(-0.016, 0.0);
        v_blurTexCoords[ 4] = f_texcoord + vec2(-0.012, 0.0);
        v_blurTexCoords[ 5] = f_texcoord + vec2(-0.008, 0.0);
        v_blurTexCoords[ 6] = f_texcoord + vec2(-0.004, 0.0);
        v_blurTexCoords[ 7] = f_texcoord + vec2( 0.004, 0.0);
        v_blurTexCoords[ 8] = f_texcoord + vec2( 0.008, 0.0);
        v_blurTexCoords[ 9] = f_texcoord + vec2( 0.012, 0.0);
        v_blurTexCoords[10] = f_texcoord + vec2( 0.016, 0.0);
        v_blurTexCoords[11] = f_texcoord + vec2( 0.020, 0.0);
        v_blurTexCoords[12] = f_texcoord + vec2( 0.024, 0.0);
        v_blurTexCoords[13] = f_texcoord + vec2( 0.028, 0.0);
    }

}