# Makefile for docker container with SSH server/X11 client

IMAGE_TAG = ssh-x:master


# Docker commands
D_RUN = docker run
D_BUILD = docker build
D_EXEC = docker exec
D_NETWORK = docker network
D_RM_IMAGE = docker image rm

# Dockerfile Locations
TAC_MC_DOCKERFILE = Dockerfile

all: build run
	
# Build the image using Dockerfile
build: 
	$(D_BUILD) \
	-t $(IMAGE_TAG) \
	-f $(TAC_MC_DOCKERFILE) \
	.

# Pressing ^C will kill this container; use ^P then ^Q to detach.
run: build
	@echo ctrl-P then ctrl-Q to detach.
	$(D_RUN) \
	-p 22:22 \
	--rm \
	--env DISPLAY=host.docker.internal:0 \
	-it $(IMAGE_TAG)

clean:
	$(D_RM_IMAGE) -f $(IMAGE_TAG)
