FROM ubuntu
RUN apt update && apt-get install build-essential -y && apt-get install gcc-multilib -y
COPY lab3_lgi.cpp .
RUN gcc -fno-pie -no-pie lab3_lgi.cpp -o lab3_lgi -g -lstdc++
CMD ./lab3_lgi