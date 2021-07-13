# ROS_Programing

## Settings
- intel Core i5 7000
- Ubuntu 20.04 Desktop
- Docker 

## Set up Docker on Ubuntu
> https://qiita.com/tkyonezu/items/0f6da57eb2d823d2611d
1. Update the package index
```sh
$ sudo apt-get update
```

2. Install the requisite software
```sh
$ sudo apt-get install -y apt-transport-https ca-certificates curl software-properties-common
```

3. Install a GPG public key
```sh
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
```
- Now we will check the fingerprint of the public key.
```sh
$ sudo apt-key fingerprint
/etc/apt/trusted.gpg
--------------------
pub   rsa4096 2017-02-22 [SCEA]
      9DC8 5822 9FC7 DD38 854A  E2D8 8D81 803C 0EBF CD88
uid           [ unknown] Docker Release (CE deb) <docker@docker.com>
sub   rsa4096 2017-02-22 [S]

/etc/apt/trusted.gpg.d/ubuntu-keyring-2012-archive.gpg
------------------------------------------------------
pub   rsa4096 2012-05-11 [SC]
      790B C727 7767 219C 42C8  6F93 3B4F E6AC C0B2 1F32
uid           [ unknown] Ubuntu Archive Automatic Signing Key (2012) <ftpmaster@ubuntu.com>

/etc/apt/trusted.gpg.d/ubuntu-keyring-2012-cdimage.gpg
------------------------------------------------------
pub   rsa4096 2012-05-11 [SC]
      8439 38DF 228D 22F7 B374  2BC0 D94A A3F0 EFE2 1092
uid           [ unknown] Ubuntu CD Image Automatic Signing Key (2012) <cdimage@ubuntu.com>

/etc/apt/trusted.gpg.d/ubuntu-keyring-2018-archive.gpg
------------------------------------------------------
pub   rsa4096 2018-09-17 [SC]
      F6EC B376 2474 EDA9 D21B  7022 8719 20D1 991B C93C
uid           [ unknown] Ubuntu Archive Automatic Signing Key (2018) <ftpmaster@ubuntu.com>
```

4. Setting up the apt repository
- x86_64 
```sh
$ sudo add-apt-repository \
   "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
   $(lsb_release -cs) \
   stable"
```

5. Install docker-ce
```sh
$ sudo apt-get update
$ sudo apt-get install -y docker-ce
```
- Check the version.
```sh
$ docker version
Client: Docker Engine - Community
 Version:           20.10.7
 API version:       1.41
 Go version:        go1.13.15
 Git commit:        f0df350
 Built:             Wed Jun  2 11:56:38 2021
 OS/Arch:           linux/amd64
 Context:           default
 Experimental:      true

Server: Docker Engine - Community
 Engine:
  Version:          20.10.7
  API version:      1.41 (minimum version 1.12)
  Go version:       go1.13.15
  Git commit:       b0f5bc3
  Built:            Wed Jun  2 11:54:50 2021
  OS/Arch:          linux/amd64
  Experimental:     false
 containerd:
  Version:          1.4.6
  GitCommit:        d71fcd7d8303cbf684402823e425e9dd2e99285d
 runc:
  Version:          1.0.0-rc95
  GitCommit:        b9ee9c6314599f1b4a7f497e1f1f856fe433d3b7
 docker-init:
  Version:          0.19.0
  GitCommit:        de40ad0
```

## Give the authority to create containers to a specific user.
- You can access the container in Visual Studio Code by giving the permission to create the container to the user you want to use.

- Check the docker group.
```sh
$ cat /etc/group | grep docker
```

- Create a docker group if there is no docker group (run as root).
```sh
# sudo groupadd docker
```

- Add myself to the dokcer group.
```sh
$ sudo usermod -aG docker (username)
```

- Check the docker group.
```sh
$ cat /etc/group | grep docker
docker:x:998:(username)
```
