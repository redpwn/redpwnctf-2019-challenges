FROM redis:5.0.5-alpine3.10

WORKDIR /usr/src/app
COPY redis.conf dump.rdb /usr/local/etc/redis/
COPY red-pwn-is.js package.json yarn.lock run.sh /usr/src/app/
RUN apk update && apk add curl nodejs-current yarn
RUN yarn

EXPOSE 80
CMD [ "sh", "/usr/src/app/run.sh" ]
