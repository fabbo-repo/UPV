FROM tsr2021/ubuntu-zmq
COPY ./2client.js /myclient.js

#CMD node myclient NEED_BROKER_URL
CMD for i in {1..10}; do  node myclient tcp://172.17.0.2:9998; done