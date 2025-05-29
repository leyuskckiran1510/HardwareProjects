# QUIZ Hardware
Hardware setups for quiz programs.
![Quiz Image](imgs/quiz.png)



# Installations
- [SimulIDE](https://simulide.com/p/downloads/): Last Stable Version (1.1.0)
- [Arduino](https://www.arduino.cc/en/software/#legacy-ide-18x): Legacy IDE (1.8.X). We need the Legacy IDE, as SimulIDE only support older versions

# Setting Up SimulIDE with Arduino 
> credits to [pcotret](https://github.com/pcotret/), for amazing [guide](https://pcotret.github.io/simulide/) on this 
- load an arduino from `Components>Micro>Arduino`
- now creat new `.ino` file on the code editor at left side
    or click on `📁+` icon ![new_file](./imgs/new_file.png)
- after the file is created, click on gear icon, just above the 
  file name you just created ![gear](./imgs/tscreen.png)
- and now click on `compiler setting`
- and in `Tool Path` choose the folder, where the `arduino-builder` executable is located ![compiler](imgs/compiler.png)
      
      not the `arduino-builder` is located inside the folder where
        you unziped/installed the Arduino, pick the folder not the actual executable
- [Optionally] If you are trying to use, external libaries or tools
  then in, the `Custom Libary Path` select the path to the libary  
- now you can compile and run, normally


# Running the project
- open the `quiz_hardware.sim1` in SimulIDE
- and open the `main.ino` in code editor
- now you can compile and run, the project
  > you have click on loadfirmware icon, only compiling dosenot
  > do the job, so directly click on loadfirmware, this will do compilation and other part
 