FROM amazonlinux
COPY 7171_lgi.sh .
RUN chmod ugo+x 7171_lgi.sh
CMD ./7171_lgi.sh