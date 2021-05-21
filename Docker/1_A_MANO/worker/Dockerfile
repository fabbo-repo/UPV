FROM tsr2021/ubuntu-zmq
COPY ./2worker.js /myworker.js

#CMD node myworker NEED_BROKER_URL
CMD node myworker tcp://172.17.0.2:9999
