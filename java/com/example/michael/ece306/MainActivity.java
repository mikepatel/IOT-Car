package com.example.michael.ece306;

import android.app.Activity;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Switch;
import android.widget.Toast;
import java.net.URL;

public class MainActivity extends Activity {

    // declare inputs
    EditText ip;
    Switch switch_iotBL;
    //Switch switch_finish;
    ImageButton upButton;
    ImageButton downButton;
    ImageButton leftButton;
    ImageButton rightButton;
    ImageButton musicButton;
    String ipAddress;
    Handler handler;
    Runnable runnableUp;
    Runnable runnableDown;
    Runnable runnableLeft;
    Runnable runnableRight;
    final static int RUNNABLETIME = 100;
    final static String HTTP = "http://";
    final static String Fcommand = "/output.cgi?text=.F&submit=Submit";
    final static String Bcommand = "/output.cgi?text=.B&submit=Submit";
    final static String Lcommand = "/output.cgi?text=.L&submit=Submit";
    final static String Rcommand = "/output.cgi?text=.R&submit=Submit";
    final static String Mcommand = "/output.cgi?text=.M&submit=Submit";
    final static String Ncommand = "/output.cgi?text=.N&submit=Submit";
    MediaPlayer mp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // identify GUI elements
        ip = (EditText) findViewById(R.id.editText_ip);
        switch_iotBL = (Switch) findViewById(R.id.switch_iotBL);
        //switch_finish = (Switch) findViewById(R.id.switch_finish);
        upButton = (ImageButton) findViewById(R.id.imageButton_up);
        downButton = (ImageButton) findViewById(R.id.imageButton_down);
        leftButton = (ImageButton) findViewById(R.id.imageButton_left);
        rightButton = (ImageButton) findViewById(R.id.imageButton_right);
        musicButton = (ImageButton) findViewById(R.id.imageButton_music);

        // Attach listeners to switches
        CompoundButton.OnCheckedChangeListener switchListener = new CompoundButton.OnCheckedChangeListener(){
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked){
                ipAddress = ip.getText().toString();
                switch(buttonView.getId()){
                    case R.id.switch_iotBL:
                        // IOT/Black Line switch
                        if(isChecked){
                            // IOT -> Black Line
                            //switch_finish.setChecked(false); // set Finish (IOT) OFF
                            Toast.makeText(getApplicationContext(), "To Black Line...", Toast.LENGTH_SHORT).show();

                            // sending IOT -> Black Line Command
                            new AsyncTask<Void, Void, Void>(){
                                protected void onPreExecute(){
                                    super.onPreExecute();
                                }

                                @Override
                                protected Void doInBackground(Void... params) {
                                    try{
                                        String site = HTTP + ipAddress + Mcommand;
                                        System.out.println(site);
                                        new URL(site).openStream();

                                    } catch (Exception e){
                                        System.out.println(e.toString());
                                    }
                                    return null;
                                }
                            }.execute();
                        }
                        else{
                            // IOT
                            // sending drive with IOT command
                            Toast.makeText(getApplicationContext(), "To IOT...", Toast.LENGTH_SHORT).show();
                            new AsyncTask<Void, Void, Void>(){
                                protected void onPreExecute(){
                                    super.onPreExecute();
                                }

                                @Override
                                protected Void doInBackground(Void... params) {
                                    try{
                                        String site = HTTP + ipAddress + Ncommand;
                                        System.out.println(site);
                                        new URL(site).openStream();

                                    } catch (Exception e){
                                        System.out.println(e.toString());
                                    }
                                    return null;
                                }
                            }.execute();
                        }
                        break;
                    /*
                    case R.id.switch_finish:
                        // Finish switch
                        if(isChecked){
                            // Black Line -> IOT
                            switch_iotBL.setChecked(false); // set Black Line OFF
                            Toast.makeText(getApplicationContext(), "Finishing with IOT...", Toast.LENGTH_SHORT).show();
                        }
                        else{
                            //
                        }
                        break;
                        */
                }
            }

        };
        switch_iotBL.setOnCheckedChangeListener(switchListener);
        //switch_finish.setOnCheckedChangeListener(switchListener);

        // Repeat action
        handler = new Handler();

        // Perform Up Direction -- Sending Forward Command
        runnableUp = new Runnable() {
            @Override
            public void run() {
                ipAddress = ip.getText().toString();

                new AsyncTask<Void, Void, Void>(){
                    protected void onPreExecute(){
                        super.onPreExecute();
                    }

                    @Override
                    protected Void doInBackground(Void... params) {
                        try{
                            String site = HTTP + ipAddress + Fcommand;
                            System.out.println(site);
                            new URL(site).openStream();

                        } catch (Exception e){
                            System.out.println(e.toString());
                        }
                        return null;
                    }
                }.execute();
                handler.postDelayed(runnableUp, RUNNABLETIME);
            }
        };

        // Perform Down Direction -- Sending Backward Command
        runnableDown = new Runnable() {
            @Override
            public void run() {
                ipAddress = ip.getText().toString();

                new AsyncTask<Void, Void, Void>(){
                    protected void onPreExecute(){
                        super.onPreExecute();
                    }

                    @Override
                    protected Void doInBackground(Void... params) {
                        try{
                            String site = HTTP + ipAddress + Bcommand;
                            System.out.println(site);
                            new URL(site).openStream();

                        } catch (Exception e){
                            System.out.println(e.toString());
                        }
                        return null;
                    }
                }.execute();
                handler.postDelayed(runnableDown, RUNNABLETIME);
            }
        };

        // Perform Left Direction -- Sending Left Command
        runnableLeft = new Runnable() {
            @Override
            public void run() {
                ipAddress = ip.getText().toString();

                new AsyncTask<Void, Void, Void>(){
                    protected void onPreExecute(){
                        super.onPreExecute();
                    }

                    @Override
                    protected Void doInBackground(Void... params) {
                        try{
                            String site = HTTP + ipAddress + Lcommand;
                            System.out.println(site);
                            new URL(site).openStream();

                        } catch (Exception e){
                            System.out.println(e.toString());
                        }

                        return null;
                    }

                }.execute();
                handler.postDelayed(runnableLeft, RUNNABLETIME);
            }
        };

        // Perform Right Direction -- Sending Right Command
        runnableRight = new Runnable() {
            @Override
            public void run() {
                ipAddress = ip.getText().toString();

                new AsyncTask<Void, Void, Void>(){
                    protected void onPreExecute(){
                        super.onPreExecute();
                    }

                    @Override
                    protected Void doInBackground(Void... params) {
                        try{
                            String site = HTTP + ipAddress + Rcommand;
                            System.out.println(site);
                            new URL(site).openStream();

                        } catch (Exception e){
                            System.out.println(e.toString());
                        }

                        return null;
                    }

                }.execute();
                handler.postDelayed(runnableRight, RUNNABLETIME);
            }
        };

        // ADD TOUCH LISTENERS to Image Buttons (direction Buttons)
        upButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        handler.postDelayed(runnableUp, RUNNABLETIME);
                        break;

                    case MotionEvent.ACTION_UP:
                        handler.removeCallbacks(runnableUp);
                        break;
                }
                return false;
            }
        });

        downButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        handler.postDelayed(runnableDown, RUNNABLETIME);
                        break;

                    case MotionEvent.ACTION_UP:
                        handler.removeCallbacks(runnableDown);
                        break;
                }
                return false;
            }
        });

        leftButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        handler.postDelayed(runnableLeft, RUNNABLETIME);
                        break;

                    case MotionEvent.ACTION_UP:
                        handler.removeCallbacks(runnableLeft);
                        break;
                }
                return false;
            }
        });

        rightButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        handler.postDelayed(runnableRight, RUNNABLETIME);
                        break;

                    case MotionEvent.ACTION_UP:
                        handler.removeCallbacks(runnableRight);
                        break;
                }
                return false;
            }
        });

        try{
            mp = new MediaPlayer();
            AssetFileDescriptor afd = getAssets().openFd("hooked.mp3");
            mp.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());
            mp.prepare();

        } catch (Exception e){
            System.out.println(e.toString());
        }

        musicButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Play Music
                if(mp.isPlaying()){
                    mp.pause();
                }
                else{
                    mp.start();
                }
            }
        });

    } // end of onCreate()

} // end of MainActivity()
