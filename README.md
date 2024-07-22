# Donate
[Please consider donating to help the project](https://www.paypal.com/donate/?hosted_button_id=HDFNAB5DC9F2L)

# Playing
Simply download the latest release, and load the .nds file in your prefered NDS emulator! To play on the actual NDS, there are numerous sources online on how to do this. Google "How to play NDS homebrew" or search it up on YouTube.
# Building
**NOTE:** Currently you have to run clean every time you build. Hope to fix that soon-ish.
This project is built using make, and the [devkitpro toolkit](https://devkitpro.org/).

### Podman Docker Image
Building with a [docker image](https://hub.docker.com/r/devkitpro/devkitarm) is recommended. However it's recommended that you use podman to run the container.

To build with podman run the following commands from the project's base directory:
```
podman pull docker.io/devkitpro
./run_build_podman.sh
```

### Docker Image
You can build with docker instead, though you need root permissions.
```
docker pull devkitpro/devkitarm
sudo docker run -v ./:/home/$WHOAMI/GitRepos/AncientsGame docker.io/devkitpro/devkitarm sh -c "export PATH=\$PATH:/opt/devkitpro/devkitARM/bin/ && cd /home/$WHOAMI/GitRepos/AncientsGame && make clean nds"
```

### Devkitpro Toolkit
**WARNING**: You may be missing some dependencies, and I don't know what they might be at the moment. So if your build fails, just download whatever is needed by reading the error messages.

Alternatively you can download devkitpro's devkitarm toolchain and install it locally.
Follow the [install instructions](https://devkitpro.org/wiki/Getting_Started)

Make sure $DEVKITPRO and $DEVKITARM are defined (as per the instructions) and the following to PATH:
```
/opt/devkitpro/devkitARM/bin/ 
```

Then you should be able to run the following from the project's base directory:
```
make clean nds
```

# Contributing
Older git commits have code style instructions, but the older READMEs felt a bit manifesto-like with my rants about OOP. So I will be updating the code style soon. For now, if you make a pull request I'll just refactor things as needed.

# Discord
You can join the discord [here](https://discord.gg/VkzbCGyGRF)
