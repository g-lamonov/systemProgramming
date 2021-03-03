RUN apt update && apt-get install build-essential -y && apt-get install gcc-multilib -y
COPY 7171_lgi_helloworld.s .
RUN gcc -m32 -fno-pie -no-pie 7171_lgi_helloworld.s -o 7171lgi -g
CMD ./7171lgi

