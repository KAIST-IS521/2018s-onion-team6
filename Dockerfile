FROM ubuntu:latest
MAINTAINER onion <k1rh4.lee@gmail.com>

###### SERVER SETTING ########
RUN apt-get update

########### USER CREATE #############
RUN useradd -d /home/jff jff -s /bin/bash
RUN mkdir /home/jff
RUN mkdir /home/jff/MEMBER


########## HOME DIR SETTING #############
RUN chown -R root:jff /home/jff
RUN chmod -R 777 /home/jff


###### PROB  SETUP #####
ADD ./BUILD/onion /home/jff/onion
ADD ./private.key /home/jff/private.key


#VOLUME ["/home/guest"]

WORKDIR /home/jff

