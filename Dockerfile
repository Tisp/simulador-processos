FROM gcc
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN make
CMD ["./simulador", "2", "tests/test_1", "blabla", "d"]
