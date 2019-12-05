# IMACUBES


### How to build

To learn more about how to use CMake, vector-of-bools has a great series of videos https://www.youtube.com/watch?v=6aiV7Z9NRhk&list=PLK6MXr8gasrGmIiSuVQXpfFuE1uPT615s&index=5
Since I'm a nice guy (but only towards those who use Windows and Visual Studio) here are a few more explanations :

#### On windows : using Visual Studio 2019

First make sure you have CMake 3.8 or higher installed : https://cmake.org/download/

Then add a 'build' folder inside 'IMACUBES', go into that folder and open a command prompt (to do so you can simply select the filepath, replace it by 'cmd' and press enter !)

<p align="center">
<img src="doc/readmeImg/01-cmdSelectFilepath.png" height="300px">
<img src="doc/readmeImg/02-cmdType.png" height="300px">
</p>

Then you just have to type this in the command prompt :

```bash
cmake ..
```

(btw you will have to type the same command each time you add a file/folder to the project to regenerate the CMakeCache and the solution)

It should automatically generate the visual studio solution and all it needs. You can now double-clic on 'IMACUBES.sln' and the project will open in Visual Studio.

<p align="center">
<img src="doc/readmeImg/03-openSolution.png" height="300px">
</p>

Now right-click on IMACUBES and select 'Set as StartUp Project'. Finally click on that lovely green triangle and you're done ! The project should build and execute just fine :wink: 

<p align="center">
<img src="doc/readmeImg/04-selectStartupProject.png" height="300px">
<img src="doc/readmeImg/05-launch.png" height="300px">
</p>
