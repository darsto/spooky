//
// Created by dar on 11/21/15.
//

#ifndef C003_TEXTURE_H
#define C003_TEXTURE_H

#include <string>
#include <GLES2/gl2.h>

using namespace std;

enum ETextureFiltering
{
    TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
    TEXTURE_FILTER_MAG_BILINEAR, // Bilinear criterion for magnification
    TEXTURE_FILTER_MIN_NEAREST, // Nearest criterion for minification
    TEXTURE_FILTER_MIN_BILINEAR, // Bilinear criterion for minification
    TEXTURE_FILTER_MIN_NEAREST_MIPMAP, // Nearest criterion for minification, but on closest mipmap
    TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
    TEXTURE_FILTER_MIN_TRILINEAR, // Bilinear criterion for minification on two closest mipmaps, then averaged
};

class Texture
{
public:
    void createFromData(unsigned char* bData, int a_iWidth, int a_iHeight, int a_iBPP, GLenum format, bool bGenerateMipMaps = false);
    bool loadTexture2D(string a_sPath, bool bGenerateMipMaps = false);
    void bindTexture(int iTextureUnit = 0);

    void setFiltering(int a_tfMagnification, int a_tfMinification);

    void setSamplerParameter(GLenum parameter, GLenum value);

    int getMinificationFilter();
    int getMagnificationFilter();

    int getWidth();
    int getHeight();
    int getBPP();

    void releaseTexture();

    Texture();
private:
    int iWidth, iHeight, iBPP; // Texture width, height, and bytes per pixel
    GLuint uiTexture; // Texture name
    GLuint uiSampler; // Sampler name
    bool bMipMapsGenerated;

    int tfMinification, tfMagnification;

    string sPath;
};


#endif //C003_TEXTURE_H
