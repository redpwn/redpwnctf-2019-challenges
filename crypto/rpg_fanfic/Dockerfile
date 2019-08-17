FROM ubuntu

RUN apt-get update && apt-get install -y \
    python \
    xinetd \
 && rm -rf /var/lib/apt/lists/*

COPY ctf.xinetd /etc/xinetd.d/ctf

COPY game.py /

CMD ["xinetd", "-dontfork"]

EXPOSE 3455

