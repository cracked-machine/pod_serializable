FROM ubuntu:latest

ARG USER=user
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update -y && apt install -y \
    sudo\
    make\
    git\
    build-essential\
    cmake \
    gdb \
    gdbserver \
    clangd \
    python3 \
    locales

RUN locale-gen en_GB.UTF-8 && update-locale

RUN useradd -m $USER && echo "$USER:$USER" | chpasswd && adduser $USER sudo
RUN echo "user            ALL = (ALL) NOPASSWD: ALL" >> /etc/sudoers
CMD /bin/bash