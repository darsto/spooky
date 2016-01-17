package tk.approach.android.spookytom;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * A part of Spooky Tom project.
 * Created by Darek Stojaczyk.
 */
public class GLView extends GLSurfaceView {
    private GLRenderer renderer;

    public GLView(Context context) {
        super(context);
        setEGLContextClientVersion(2);
        renderer = new GLRenderer();
        setRenderer(renderer);
    }
}