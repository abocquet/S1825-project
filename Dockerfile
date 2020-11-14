FROM gcc:4.9
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN gcc -o main.out *.c -lpthread -lm -fopt-info-vec-all
CMD ["./main.out"]