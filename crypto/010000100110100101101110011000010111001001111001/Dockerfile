FROM ubuntu

RUN apt-get update && apt-get install -y \
    python3 \
    xinetd \
 && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y python3-pip

RUN pip3 install pycrypto

COPY ctf.xinetd /etc/xinetd.d/ctf

COPY chall.py flag.txt /

CMD ["xinetd", "-dontfork"]

EXPOSE 3455
