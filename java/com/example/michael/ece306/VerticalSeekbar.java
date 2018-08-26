package com.example.michael.ece306;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.widget.SeekBar;

/**
 * Created by Michael on 11/16/2016.
 */

public class VerticalSeekbar extends SeekBar {
    public VerticalSeekbar(Context context) {
        super(context);
    }

    public VerticalSeekbar(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }

    public VerticalSeekbar(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    protected void onDraw(Canvas c){
        c.rotate(-90);
        c.translate(-getHeight(), 0);
        super.onDraw(c);
    }
}
