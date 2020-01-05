## Automatic Take-off For FlightGear Simulator

Welcome to our program's repo, we've added a bunch of usefull instructions and information to help you with your first setup. The main purpose of this repo is for a course project (Algorithmic Programming).

* **How does it work?** Run the program and then the simulator.
* **What is the goal of this project?** An assignment to study tcp-socket server/client, implementing command pattern and more..

## Instructions for how to use, and test the code
**LINUX USERS:**\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*1.* Install FlightGear simulator software from your software manager/terminal.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*2.* Go to ***"/usr/share/games/flightgear/Protocol"*** on your machine. (note: you  might want to open the folder with &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;root privillages).\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*3.* Copy ***"generic_small.xml"*** file from this repo to folder.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*4.* Compile the above files.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*5.* Open up FlightGear app and go to settings.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*6.* Under **"Additional Settings"** add the following:\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*6.a* *--telnet=socket,in,10,127.0.0.1,5402,tcp*\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*6.b* *--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small*\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*NOTE*: make sure there are'nt any whitespaces or chars sneaking in there!*

## Big thanks to Dr Eliahu Khalastchi for making the XML file

## GitHub repository:
https://github.com/dorefaeli/AlgorithmicProgrammingProject

## Contact us

If you have any suggestions\questions please feel free to contact us at : *dorefaeli@gmail.com*
