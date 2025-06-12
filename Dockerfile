FROM gcc:13 AS base
WORKDIR /usr/src/app

FROM base AS client-build
COPY client/udp-echo-client.c .
run gcc udp-echo-client.c -o client

FROM base AS server-build
COPY server/udp-echo-server.c .
RUN gcc udp-echo-server.c -o server

FROM debian:bookworm-slim AS client
COPY --from=client-build /usr/src/app/client /usr/local/bin/client
CMD [ "client" ]

FROM debian:bookworm-slim AS server
COPY --from=server-build /usr/src/app/server /usr/local/bin/server
CMD [ "server" ]