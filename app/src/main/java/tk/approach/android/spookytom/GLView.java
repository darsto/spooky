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

    private int normalizeMotionAction(int action) {
        if (action == MotionEvent.ACTION_POINTER_DOWN) return 0;
        if (action == MotionEvent.ACTION_POINTER_UP) return 1;
        if (action == MotionEvent.ACTION_CANCEL) return 1;
        return action;
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        if (this.renderer.getJniBridge() != null) {
            if (e.getActionMasked() == MotionEvent.ACTION_MOVE) {
                for (int i = 0; i < e.getPointerCount(); i++) {
                    this.renderer.getJniBridge().handleTouch(e.getPointerId(i), normalizeMotionAction(e.getActionMasked()), e.getX(i), e.getY(i));
                }
            } else {
                this.renderer.getJniBridge().handleTouch(e.getPointerId(e.getActionIndex()), normalizeMotionAction(e.getActionMasked()), e.getX(e.getActionIndex()), e.getY(e.getActionIndex()));
            }
        }
        return true;
    }
}