FROM ubuntu:16.04

RUN apt update && apt install -y \
  make \
  g++ \
  git \
  wget

WORKDIR /tmp/gtest
ENV CXXFLAGS="-DGTEST_HAS_PTHREAD=0"
RUN git clone https://github.com/google/googletest.git /tmp/gtest \
    && echo ${pwd} \
    && cd /tmp/gtest/googletest/make \
    && make all

WORKDIR /tmp/drmemory
RUN apt update && apt install -y \
    g++-multilib \
    && wget -O dl.tar.gz "https://github.com/DynamoRIO/drmemory/releases/download/release_1.11.0/DrMemory-Linux-1.11.0-2.tar.gz" \
    && tar -xvzf dl.tar.gz

WORKDIR /build
RUN mv /tmp/drmemory/DrMemory-Linux-1.11.0-2 /build/drmemory

ENV PATH=$PATH:/build/drmemory/bin

WORKDIR /build/gtest/lib
RUN cp /tmp/gtest/googletest/make/gtest_main.a /build/gtest/lib \
    && cp -r /tmp/gtest/googletest/include /build/gtest/

RUN rm -rf /tmp

WORKDIR /build/src
ADD src/ /build/src