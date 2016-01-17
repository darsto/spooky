package tk.approach.android.spookytom;

/**
 * A part of Spooky Tom project.
 * Created by Darek Stojaczyk.
 */
public class JniBridge {

    static {
        System.loadLibrary("c003");
    }

    public static native void init();

    public static native void resize(int width, int height);

    public static native void tick();

    public static native void handleTouch(int i, int x, int y);
}
