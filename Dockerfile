FROM ubuntu:bionic 
#pull ubuntu
FROM gcc:latest
#pull gcc

RUN apt-get update && apt-get -y install gcc cmake

ADD . /usr/src

WORKDIR /usr/src

EXPOSE 5555

#RUN g++ client.cpp -o client

CMD ["/bin/bash"]