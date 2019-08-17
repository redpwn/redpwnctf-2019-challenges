FROM alpine:3.10

WORKDIR /usr/src/app
COPY feud-images.js /usr/src/app/
RUN apk update && apk add nodejs-current

EXPOSE 80
CMD [ "node", "/usr/src/app/feud-images.js" ]
