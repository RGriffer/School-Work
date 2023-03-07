1. What is a docker container? 
A Docker container image is a lightweight, standalone, executable package of software that includes 
everything needed to run an application: code, runtime, system tools, system libraries and settings.

2. What is the difference between a container and a virtual machine? 
containers provide a way to virtualize an OS so that multiple workloads can run on a single OS instance. 
With VMs, the hardware is being virtualized to run multiple OS instances.

3. What is the purpose of a Dockerfile?
A Dockerfile is a text document that contains all the commands a user could call on the command line to assemble an image.

4. What is the purpose of a requirements.txt file?
the requirements.txt file is used in the Dockerfile to build the image with the packages.

5. What is the purpose of a docker-compose.yml file?
A docker-compose.yml is a config file for docker-compose. it allows to deploy, combine and configure multiple docker-container at the same time.

6. What is the difference between a docker image and docker container?
A Docker image is a read-only, inert template that comes with instructions for deploying containers.
A Docker container is a virtualized runtime environment that provides isolation capabilities for separating 
the execution of applications from the underpinning system. It’s an instance of a Docker image.

7. What command can be used to create an image from a Dockerfile?
The docker build command builds Docker images from a Dockerfile

8. What command will start a docker container?
The docker start command
$ docker container start [OPTIONS] CONTAINER [CONTAINER...]

9. What command will stop a docker container?
The docker stop command
docker stop [CONTAINER]

10. What command will remove a docker container? Image?
docker rm, docker rmi

11. What command will list all running docker containers? all containers?
docker container ls, docker container ls -a

12. What command will list all docker images?
docker image ls -a

13. What command do you use to deploy docker containers using information in the dockercompose.yml file?
docker-compose up [OPTIONS]

14. How can you specify in the docker-compose.yml file that you want docker containers to use the hosts network?
set network_mode to "host" in the docker-compose.yml file

15. How can you specify in the docker-compose.yml file where the Dockerfile for a particular container is found?
Edit the build line to the location of the desired dockerfile is.

