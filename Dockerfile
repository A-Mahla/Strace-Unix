FROM	amd64/ubuntu:jammy

RUN	apt-get update && apt-get install -y \
	gcc \
	clang \
	libc6-dev-i386 \
	git \
	make \
	man \
	vim \
	strace

WORKDIR	/tmp

COPY	. .
