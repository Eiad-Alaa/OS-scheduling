FROM ubuntu:latest

RUN apt-get update && apt-get install -y g++ make


WORKDIR /app

COPY ./makefile /app/makefile
COPY ./*.cpp /app/
COPY ./Algorithms /app/Algorithms


RUN make

CMD ["./lab6"]