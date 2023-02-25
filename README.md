# sweng-project-23-2023
Simulated Trading Exchange using FIX protocol


<h2> Installing Library and adding to project </h2>

Go to this link: https://quickfixengine.org/c/download/

Download the zip file version
 
Extract files. Open root folder and then open lib folder. We want the quickfix.lib file. Copy and paste into the repo/libs folder to add it to our project. Everyone will need to do this on their machines as the lib file is too big to commit.

<h2> Building and running </h2>

This proceeds assuming you have make and cmake installed. How to check: open terminal and enter `make --version` and  `cmake --version`. If version prints out then you're good to go. if you get an error means they're not installed.

From here its pretty simple to run the project. open terminal. navigate to the repo root directory. then enter `make`. The project builds the executables aswell as bunch of files needed to build in the build folder.

now to run the project, simply enter `make run` in the root directory. project runs and 2 windows should open up with connection establishing between the 2.

From here, the ball is in your court reader. 

documentation: https://quickfixengine.org/c/documentation/
