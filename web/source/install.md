---
title: Install
keywords:
- keyword 1
- keyword 2
lang: en

toc: true
# select which part of the navigation bar should be active
navbar_install: true
---

Install in Ubuntu (Launchpad)
-----------------------------

Astade for Ubuntu is available at [Launchpad](https://launchpad.net/~astade). There you can find two package archives for stable releases and for daily builds. Just follow the Launchpad instructions on how to add the archive of your choice to your system.

Here is the short version for the stable release archive:

```
sudo apt-add-repository ppa:astade/
release
sudo apt-get update
sudo apt-get install astade
```

That's all.

Behind a proxy you need:

```
export http_proxy=http://<proxy>:<port>
export https_proxy=http://<proxy>:<port>
sudo -E apt-add-repository ppa:astade/release
```

For adding the ppa.

Install in Debian
-----------------

To install Astade in Debian add the following lines to your /etc/apt/sources.list (resp. the sources.list.d/astade.list):

```
deb http://ppa.launchpad.net/astade/daily/ubuntu/ devel main
deb-src http://ppa.launchpad.net/astade/daily/ubuntu/ devel main
```

Afterwards you can run (as usual):

```
apt-get update
apt-get install astade
```

Voila. 
