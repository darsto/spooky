package tk.approach.android.spookytom;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

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

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        this.renderer.getJniBridge().handleTouch(e.getActionIndex(), e.getAction(), e.getX(e.getActionIndex()), e.getY(e.getActionIndex()));
        return true;
    }
}