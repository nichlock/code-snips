FROM ubuntu:latest

## Run Installs ###############################################################
# These are run first to avoid having to re-run them on file edits/rebuilds
# Update apt
RUN apt-get update
# Text editor
RUN apt-get -y install nano
# Networking tools
RUN apt-get -y install net-tools
RUN apt-get -y install iputils-ping
# SSH server
RUN apt-get -y install openssh-server
# X11 server
RUN apt-get -y install x11-apps

## General System Setup #######################################################
# Variables used later 
ENV ROOT_PWD=r
# Print container ID at start.
RUN echo "cat /etc/hostname" >> /startup.sh

## SSH/X11 Setup ##############################################################
# RUN mkdir -p /var/run/sshd
# Authorize SSH connection with root account by changing a setup file
RUN echo "echo PermitRootLogin yes >> /etc/ssh/sshd_config" >> /startup.sh
# Assign a password to root
RUN echo "echo root:${ROOT_PWD} | chpasswd" >> /startup.sh
# Starts service
RUN echo "service ssh restart" >> /startup.sh

## Helpers ####################################################################
# Colors bash prompt so that the container ID is more visible
RUN echo "PS1='\[\033[0m\]\u@\[\033[1;32m\]\h\[\033[0m\]:\[\033[1;34m\]\w\[\033[0m\]\\$ '" >> /root/.bashrc
# Keeps container running
RUN echo "tail -f /dev/null" >> /startup.sh

## Startup ####################################################################
# At run, this will execute any command set up previously by echoing into it.
ENTRYPOINT ["/bin/bash"]
CMD ["/startup.sh"]
