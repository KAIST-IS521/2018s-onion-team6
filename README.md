# 2018s-onion-team6

## Abstract

## Table of contents
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Authors](#authors)

## Getting Started

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

# build
$ make
```

## Usage

### GPG key

If you don't have the GPG key, you should make it.
And you should export your private key to `private.key` file.

```
# Generate a new keypair
$ gpg --gen-key

# Export private key to file
$ gpg --export-secret-keys -a > private.key
```

### In local

```
# Run the app
$ ./build/onion
```

### In docker

```
# Build docker image
$ ./

# Run it as one container
$ ./
```

## Authors
 * Team JFF [Just For Fun]
   * Soohun Kim (L)
   * Sunnyeo Park
   * Sangsup Lee
   * Hyungseok Han (TA)