
# Mini BitTorrent

## Compilation
For Ubuntu you can skip the following steps as you already have the OpenSSL pre-install and configured to use with `gcc`

#### For MacOS
If you do not have OpenSSL installed you will need to install it:
```
brew install openssl
```

We also need to create symbolic links for the OpenSSL header files and the binaries so that `gcc` can find them.
```
ln -s /usr/local/opt/openssl\@1.1/include/openssl /usr/local/include/
ln -s /usr/local/opt/openssl\@1.1/lib/* /usr/local/lib/
ln -s /usr/local/opt/openssl\@1.1/bin/* /usr/local/bin/
```

You can check that you have everything working correctly by running a [test](src/shatest.cpp). 
```
g++ shatest.cpp -lssl -lcrypto -o Test
./Test
```
This should return the string `0a4d55a8d778e5022fab701977c5d840bbc486d0` which is the SHA1 digest of the string "Hello World".


