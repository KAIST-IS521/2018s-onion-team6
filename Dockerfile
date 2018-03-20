FROM ubuntu:latest
MAINTAINER onion <k1rh4.lee@gmail.com>

###### SERVER SETTING ########
RUN apt-get update
RUN apt-get install -y openssh-server


########### USER CREATE #############
#RUN useradd -d /home/guest guest -s /bin/bash
RUN useradd -d /home/jff jff -s /bin/bash
RUN mkdir /home/jff

RUN echo "jff:jffhappy" | chpasswd jff


########## HOME DIR SETTING #############
RUN chown -R root:jff /home/jff
RUN chmod 750 /home/jff

###### PROB  SETUP #####
ADD ./CLIENT/client /home/jff/client
ADD ./private.key /home/jff/private.key
####### XINETD SETTING
#ADD ./SET/load.xinetd /etc/xinetd.d/load
ADD ./start.sh /start.sh


#VOLUME ["/home/guest"]

WORKDIR /home/jff

EXPOSE 20000
ENTRYPOINT /start.sh



