package tk.approach.android.spookytom;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity {
        /** The OpenGL surface on which we draw */
        private GLView surfaceView;

        /**
         * Set up the activity.
         */
        @Override
        public void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            JniBridge.resources = this.getResources();
            requestWindowFeature(Window.FEATURE_NO_TITLE);
            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
            getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

            surfaceView = new GLView(this);
            setContentView(surfaceView);
        }

        /**
         * Restart drawing of the OpenGL surface.
         */
        @Override
        protected void onResume() {
            super.onResume();
            surfaceView.onResume();
        }

        /**
         * Pause drawing of the OpenGL surface.
         */
        @Override
        protected void onPause() {
            super.onPause();
            surfaceView.onPause();
        }
    }
