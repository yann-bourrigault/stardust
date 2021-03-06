# Développer en local

Le code du robot est en [ROS Melodic](http://wiki.ros.org/melodic/Installation).

Afin d'avoir un environnement simple d'emploi, l'installation d'Ubuntu version 18 et uniquement cette version est conseillé.

Trois techniques :
- Installer Ubuntu 18 via une machine virtuelle (le plus simple)
- Installer Ubuntu 18 sur son ordinateur en dual boot (plus rapide)

Chacun est libre de l'installer comme il le préfère et comme il le sent.

## Installation Ubuntu 18

Aller sur [Ubuntu realease](http://releases.ubuntu.com/bionic/) et télécharger l'ISO
Installer sur votre ordinateur (VM, barebone, dual boot, ...)

Attention, il est conseillé d'avoir ou d'allouer au moins 20Go de disque et 4Go de RAM.

Penser à installer les outils de virtualisations (VMWare tools pour VMWare par exemple) pour optimiser la performance si vous avez choisi d'utiliser une VM.

Exemple pour VMWare :

```bash
sudo apt install open-vm-tools
```

## Installation de ROS et du projet

### Installation de ROS

Avant d'installer ROS, mettre à jour votre système :

```bash
sudo apt update
sudo apt upgrade
sudo reboot
```

Ouvrir une console et installer ROS :

```bash
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
sudo apt-get update
sudo apt-get install \
	ros-melodic-desktop-full \
	ros-melodic-gazebo-plugins \
	ros-melodic-hector-gazebo-plugins \
	ros-melodic-gazebo-ros-control
sudo apt install python-wstool mesa-utils
sudo rosdep init
rosdep update
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

### Installation du code source du projet

Récupérer les sources depuis github :

```bash
cd ~
sudo apt-get install git
git clone https://github.com/julienbayle/stardust
```

Récupérer les dépendances et compiler :

```bash
~/stardust/scripts/update.sh
```

## Compiler une modification

Compiler les sources et mettre à jour les raccourcis et l'autocomplétion bash pour le projet :

```bash
cd ~/stardust/ros/
catkin_make
source devel/setup.bash
```

ou 

```bash
~/stardust/scripts/update.sh
```

## Démarage de l'environnement de simulation

```bash
roslaunch sd_main sim.launch
```
## Se connecter au robot

Générer des clés SSH pour le poste de développement (uniquement si pas déjà fait) :

```bash
ssh-keygen
```

Déclarer les enregistrements DNS du ou des robot sur le poste de développement (sudo vi /etc/hosts) :
```bash
192.168.10.163	stardust_r1
192.168.10.162	stardust_r2
```

Copier la clé SSH vers les robots afin de ne pas avoir à taper de code lors de la connexion SSH :
```bash
ssh-copy-id ubuntu@stardust_r1
ssh-copy-id ubuntu@stardust-r2
```

Récupérer l'environnement de cross compilation ARM :
```shell
./scripts/download-rpi-sysroot.sh -s ubuntu@stardust_r1
```

Déployer le code local sur un robot :
```shell
./scriptsdeploy-rpi.sh -remote-hostname=stardust_r1 --version=stardust_v1 --robot-name=r1 --build
```

[Détails et explications sur la cross compilation et la commande deploy-rpi.sh](cross_compilation_raspberry.md).

