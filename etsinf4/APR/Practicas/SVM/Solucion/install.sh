#! /bin/bash
git clone https://github.com/cjlin1/libsvm
sudo apt install -y liboctave-dev
cd libsvm/matlab
octave --eval "make"
cp svmtrain.mex ../.. && cp svmpredict.mex ../..
cd ../..
rm -r libsvm