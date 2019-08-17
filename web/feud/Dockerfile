FROM buildkite/puppeteer

WORKDIR /usr/src/app
COPY feud.js keys.js package.json yarn.lock /usr/src/app/
RUN yarn
RUN apt update && apt install -y libcap2-bin && setcap 'cap_net_bind_service=+ep' /usr/local/bin/node
RUN adduser --disabled-password --gecos "" ctf
USER ctf

EXPOSE 80
CMD [ "node", "/usr/src/app/feud.js" ]
