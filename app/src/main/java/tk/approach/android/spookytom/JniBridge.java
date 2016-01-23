package tk.approach.android.spookytom;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;

import java.io.IOException;
import java.io.InputStream;

/**
 * A part of Spooky Tom project.
 * Created by Darek Stojaczyk.
 */
public class JniBridge {

    static {
        System.loadLibrary("c003_game");
    }

    public native void init();

    public native void resize(int width, int height);

    public native void tick();

    public native void handleTouch(int i, int action, float x, float y);

    public void loadTexture() { //TODO
        int textureId = R.drawable.terrain;//TODO load
        int[] texturenames = new int[1];
        GLES20.glGenTextures(1, texturenames, 0);
        Bitmap tempBitmap;
        InputStream is = resources.openRawResource(textureId);
        try {
            tempBitmap = BitmapFactory.decodeStream(is);
        } finally {
            try {
                is.close();
            } catch (IOException e) {
                // Ignore.
            }
        }
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0 + lastTexId);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, texturenames[lastTexId]);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, tempBitmap, 0);
        tempBitmap.recycle();
        lastTexId++;
        //return textureId;
    }

    private int lastTexId = 0;

    public static Resources resources;//TODO
}
