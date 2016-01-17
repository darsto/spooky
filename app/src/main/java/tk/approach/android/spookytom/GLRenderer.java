package tk.approach.android.spookytom;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * A part of Spooky Tom project.
 * Created by Darek Stojaczyk.
 */
public class GLRenderer implements GLSurfaceView.Renderer {

    @Override
    public void onSurfaceCreated(GL10 unused, EGLConfig config) {
        JniBridge.init();
    }

    @Override
    public void onSurfaceChanged(GL10 unused, int width, int height) {
        JniBridge.resize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 unused) {
        JniBridge.tick();
    }
}