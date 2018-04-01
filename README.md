# 2018s-onion-team6

## greeting
```
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                     _ _____ _____    ___        _             
                    | |  ___|  ___|  / _ \ _ __ (_) ___  _ __  
                 _  | | |_  | |_    | | | | '_ \| |/ _ \| '_ \ 
                | |_| |  _| |  _|   | |_| | | | | | (_) | | | |
                 \___/|_|   |_|      \___/|_| |_|_|\___/|_| |_|
                                                               
                __  __                                           
               |  \/  | ___  ___ ___  __ _ _ __   __ _  ___ _ __ 
               | |\/| |/ _ \/ __/ __|/ _` | '_ \ / _` |/ _ \ '__|
               | |  | |  __/\__ \__ \ (_| | | | | (_| |  __/ |   
               |_|  |_|\___||___/___/\__,_|_| |_|\__, |\___|_|   
                                                 |___/           
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
```

## Abstract

## Table of contents
* [Getting Started](#getting-started)
  * [PGP key](#gpg-key)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Running the App](#getting-started)
  * [In local](#in-local)
  * [In docker](#in-docker)
* [Usage](#usage)
* [Authors](#authors)

## Getting Started

### PGP key

If you don't have the PGP key, you should make it. </br>
And you have to export your private key to `private.key` file.

```
# Generate a new keypair
$ gpg --gen-key

# Export private key to file
$ gpg --export-secret-keys -a > private.key
```

### Prerequisites

We compile our program with `clang`

```
$ sudo apt-get install clang-5.0
```

You can test our messenger in `docker`

```
$ sudo apt-get update
$ sudo apt-get install curl
$ curl -sSL https://get.docker.com/ | sh

# verify installation
$ sudo docker run hello-world
```

### Installation

```
# Clone this repository
$ git clone https://github.com/KAIST-IS521/2018s-onion-team6.git

# Go into the repository
$ cd 2018s-onion-team6.git

# Install dependencies
$ ./setup.sh

# Build 
$ make
```

## Running the App

### In local

```
# Run the app
$ ./build/onion
```

### In docker

```
# Build docker image
$ ./1_build_docker.sh ${1}  //$1 is prepared private key number (1~6).

# Run it as one container
$ ./2_container_docker.sh ${CONTAINER_NAME}
```

## Usage

```
 USAGE : # [COMMAND]
           {help}                        : print usage
           {send} {GIT_ID}               : send message
                            -> {MESSAGE} : input message
           {ls}                          : show received message list
           {cat} {GIT_ID}                : print recvived message
           {id}                          : show my info
           {w}                           : show member list
           {exit}                        : program exit

```

## Authors
 * Team JFF [Just For Fun]
   * Soohun Kim (L)
   * Sunnyeo Park
   * Sangsup Lee
   * Hyungseok Han (TA)
