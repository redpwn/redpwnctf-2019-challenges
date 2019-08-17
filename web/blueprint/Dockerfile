FROM alpine:3.10

WORKDIR /usr/src/app
COPY blueprint.js flag.js package.json yarn.lock /usr/src/app/
RUN apk update && apk add nodejs-current yarn
RUN yarn

EXPOSE 80
CMD [ "node", "/usr/src/app/blueprint.js" ]
