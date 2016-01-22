package tk.approach.android.spookytom;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * A part of Spooky Tom project.
 * Created by Darek Stojaczyk.
 */
public class GLRenderer implements GLSurfaceView.Renderer {

	private JniBridge jniBridge = null;

    @Override
    public void onSurfaceCreated(GL10 unused, EGLConfig config) {
        this.jniBridge = new JniBridge();
        this.jniBridge.init();
    }

    @Override
    public void onSurfaceChanged(GL10 unused, int width, int height) {
        this.jniBridge.resize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 unused) {
        this.jniBridge.tick();
    }
}
