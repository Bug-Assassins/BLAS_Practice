#wget https://codeload.github.com/xianyi/OpenBLAS/legacy.zip/v0.2.11
unzip xianyi-OpenBLAS-v0.2.11-0-ga7126c2.zip
cd xianyi-OpenBLAS-ea8d4e3
sudo apt-get install gfortran
make && make install
