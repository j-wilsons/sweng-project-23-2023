# sweng-project-23-2023
Simulated Trading Exchange using FIX protocol


<h2> Running app locally </h2>

To run the app locally, we have to create a docker subnet and connect 2 containers to it. These 2 containers will mimic a Client and Server.
First make sure you have this repo cloned and Docker is installed and running

<h3> Creating Local Network </h3>

Open a terminal and enter this command:

```
docker network create --driver=bridge --subnet=172.21.0.0/16 picotcd
```
What this did is create a subnetwork called *picotcd* with the ip addresses 172.21.0.0 to 172.21.255.255
We need this so the client and server can communicate

if you run `docker network inspect picotcd` it'll show you network info and what containers are connected to it. For now the `"Containers":{}` field should be empty

<h3> Creating Image </h3>

Open a terminal and navigate to where you have the repo cloned.
Once at repo directory enter this command:
```
docker build -t swengpico .
```
and yes the fullstop is important

This command used the DockerFile in our repo to build an image called swengpico. An image is like a template which containers copy from. The dockerfile has configurations to use Ubuntu and a C++ compiler to effectively let us run C code in any containers we create with this image.

<h3> Creating containers </h3>

Now we have our image created. On the Docker app, you should see swengpico listed in the "images" section. 

Normally creating containers means creating a private space in your drive where you can run another operating system and run programs without interference from the rest of your computer. This is good for testing programs but annoying when you actually need to interact with the rest of your computer.

So instead we create a container with a **bind mount**. This mounts a file or directory on the host machine into the container. What this means for us is that our containers will have access to the code in this repo. yes i know very cool

We'll start with the client. To create a container from this image do this command:

```
docker run --name Client -it --mount type=bind,source=<ABSOLUTE PATH TO REPO DIRECTORY>,target=/usr/src --network=picotcd swengpico
```

e.g for me it looks like: `docker run --name Client -it --mount type=bind,source=C:/Users/Sultan/Documents/coding/Cpp/sweng-project-23-2023,target=/usr/src --network=picotcd swengpico`

So in short we created and started a container called Client which has a bind mount located at wherever your repo directory and our container is connected to the local network picotcd, using the image swengpico.

If the command ran successfully it means you are currently in the container terminal. if you enter `dir` you should see your repo directory 

Now we do the exact same for Server.  Open a new terminal and enter the same command as above but with the name Server:
```
docker run --name Server -it --mount type=bind,source=<ABSOLUTE PATH TO REPO DIRECTORY>,target=/usr/src --network=picotcd swengpico
```
Now both containers are running and connected to the network picotcd. To check, run `docker network inspect picotcd` in another terminal and check the `'Containers'` field.

<h3> Running the app </h3>

In the Server container, navigate to src. if you run `dir` you'll see the client and server code file. 
Running the command: 
```
g++ server.cpp -o serverExec
```
compiles the code in server.cpp into an executable called serverExec

enter this command to run the executable:

```
./serverExec
```

if no errors are returned server is now waiting for communication from client

Now onto the client. Same process.
In the client container, compile and run client.cpp by using `g++ client.cpp -o clientExec` and `./clientExec`

If no errors return, client and server should have talked to each other and printed their responses.