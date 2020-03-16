Goal: The gold for this project is creating a maze like environment. The robot will start at the top left corner and explore the maze until find the exit.

Key challenges and how they were addressed: The robot is easy to get stucked in the maze. I let the robot rotate in random direction when it gets stucked. It is really hard for the robot to find the exit since the maze is complex and the robot is not intelligent. When the robot get stucked or hit the wall, I select the direction of the exit as the primary option to rotate.

How to install and run the code: 
1.Do docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.1 bash to start the docker image environment.
2.cd Project to enter into the directory.
3.Do esm start to run the environment.
4.Do make to compile the code.
5.Do enviro to run the project.
6.Go to http://localhost to see the running project.

How to use the project: When the project is running, you can see the maze and the robot starting at the top left corner. Then the robot will move automatically to find the exit, which is the red line on the top right of the maze.

Sources of information or code used: https://github.com/klavins/EEP520-W20/tree/master/week_8/wanderers I use the code of waderer.json to write the robot. Then I follow the wanderer.h to find strategies to move forward and rotate.