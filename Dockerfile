# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
FROM gcc:11.4.0 as build

WORKDIR /usr/src/echobot
COPY . .
RUN cmake .
RUN make -j4
CMD ./echobot