#!/bin/bash
export WHOAMI=$(whoami)
podman run -v ./:/home/$WHOAMI/GitRepos/AncientsGame docker.io/devkitpro/devkitarm sh -c "export PATH=\$PATH:/opt/devkitpro/devkitARM/bin/ && cd /home/$WHOAMI/GitRepos/AncientsGame && make clean nds -e FLAGS=\"$1\""
