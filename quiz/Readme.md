# QUIZ APP



# Installations
- [SimulIDE](https://simulide.com/p/downloads/): Last Stable Version (1.1.0)
- [Arduino](https://www.arduino.cc/en/software/#legacy-ide-18x): Legacy IDE (1.8.X). We need the Legacy IDE, as SimulIDE only support older versions

# Setting Up SimulIDE with Arduino 
- load an arduino from `Components>Micro>Arduino`
- now creat new `.ino` file on the code editor at left side
    or click on `📁+` icon ![new_file](./imgs/new_file.png)
- after the file is created, click on gear icon, just above the 
  file name you just created ![gear](./imgs/tscreen.png)
- and now click on `compiler setting`
- and in `Tool Path` choose the folder, where the `arduino-builder` executable is located ![compiler](imgs/compiler.png)
      - not the `arduino-builder` is located inside the folder where
        you unziped/installed the Arduino, pick the folder not the actual executable
- [Optionally] If you are trying to use, external libaries or tools
  then in, the `Custom Libary Path` select the path to the libary  
- now you can compile and run, normally



